/**********************************************************************

  Rdacity: A Digital Audio Editor powered by Audacity(R)

  RivendellDialog.cpp

  This effort was sponsored work by Radio Free Asia   
	https://github.com/RadioFreeAsia/rdacity
  John Penovich <penovichj@rfa.org> - cleanup
  Henry Riverah
  Federico Grau
  Todd Baker  <bakert@rfa.org> <toadybarker@gmail.com>

  (C) Copyright August 7, 2016 Todd Baker <bakert@rfa.org>

     This program is free software; you can redistribute it and/or
     modify it under the terms of the GNU General Public License version 2
     as published by the free Software foundation.

     This program is distrbuted in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MECHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
     General Public License for more details

     You should have received a copy of the GNU General Public
     License along with this program, if not,  write to the Free Software
     Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA
**********************************************************************/

#include <fstream>
#include <math.h>
#include <wx/dialog.h>
#include <wx/html/htmlwin.h>
#include <wx/button.h>
#include <wx/dcclient.h>
#include <wx/gdicmn.h>
#include <wx/imaglist.h>
#include <wx/sizer.h>
#include <wx/statbmp.h>
#include <wx/statusbr.h>
#include <wx/string.h>
#include <wx/intl.h>
#include <wx/wfstream.h>
#include <wx/listctrl.h>
#include <wx/checkbox.h>
#include <wx/progdlg.h>
#include <wx/menuitem.h>
#include <wx/utils.h>
#include <wx/dir.h>
#include <wx/radiobox.h>
#include <wx/checkbox.h>

#include <wx/filefn.h>


#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#ifndef HOST_NAME_MAX
	#define HOST_NAME_MAX 255
#endif


#include "export/Export.h"
#include "export/ExportPCM.h"
#include "Project.h"
#include "RivendellDialog.h"
#include "RivendellConfig.h"
#include "RivendellBrowseDialog.h"
#include "RivendellDialog.h"
#include "RivendellLoginDialog.h"
#include "RivendellUtils.h"

#include "widgets/ProgressDialog.h"

#include "MyProgressThread.h"
#include "rivendell/rd_import.h"
#include "rivendell/rd_editcart.h"
#include "rivendell/rd_editcut.h"
#include "rivendell/rd_listcart.h"
#include "rivendell/rd_listcut.h"
#include "rivendell/rd_addcut.h"
#include "rivendell/rd_listsystemsettings.h"
#include "rivendell/rd_getversion.h"
#include "rivendell/rd_getuseragent.h"
#include "Audacity.h"
#include "Mix.h" //NEW

//#include "Uni_Buffer.h"

// This is to handle Unicode Conversion of strings
#define WX2UNI(s) ((const char *)s.ToUTF8())

BEGIN_EVENT_TABLE(RivendellDialog, wxDialog)
   EVT_BUTTON(wxID_BROWSE, RivendellDialog::OnBrowse)
   EVT_BUTTON(wxID_OK, RivendellDialog::OnOK)
   EVT_BUTTON(wxID_CLEAR, RivendellDialog::OnClear)
   EVT_CHOICE(wxID_GROUP, RivendellDialog::OnChoiceGroup)
   EVT_CHECKBOX(wxID_EVERGREEN, RivendellDialog::OnEvergreenChange)
   EVT_TEXT(wxID_CARTNUMBER,RivendellDialog::OnCartNumberChange)
   END_EVENT_TABLE()

IMPLEMENT_CLASS(RivendellDialog, wxDialog)

RivendellDialog::RivendellDialog(wxWindow * parent, MYSQL *db, bool saveSelection)
:  wxDialog(parent, -1, _("Export to Rivendell, User: ") + riv_getuser(),
		wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxWANTS_CHARS)
{
	mDb = db;
	
	mSaveSelection = saveSelection;

	MYSQL_RES *result;
	MYSQL_ROW row;

	int numRows;
	wxString query;
	wxString chk_Desc;

	wxBoxSizer *mainBoxSizer = new wxBoxSizer( wxVERTICAL );

   // Create the internal flexgrids and box sizers.
	wxFlexGridSizer  *topGridSizer = new wxFlexGridSizer(1, 2,0); 
	wxStaticBoxSizer *cutinfoBoxSizer = new wxStaticBoxSizer(new wxStaticBox(this, -1, wxT("CUT Information"), 
		wxDefaultPosition, wxDefaultSize, 0, wxT("")), wxVERTICAL);
   
   wxFlexGridSizer  *cutGridSizer = new wxFlexGridSizer( 2, 0, 0 );
   wxFlexGridSizer  *dateGridSizer = new wxFlexGridSizer( 3, 0, 0 );
   wxBoxSizer       *cutBoxSizer = new wxBoxSizer( wxHORIZONTAL );
   wxBoxSizer       *descBoxSizer = new wxBoxSizer( wxHORIZONTAL );
   
   // Create description text box and label.
   // Attempt to Filter Out the Unicode Characters fro Description Field
   
   wxTextValidator AsciiValid(wxFILTER_ASCII);
   wxStaticText *cutDescBox = new wxStaticText( this, -1, _("Description:"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT );
   wxTextCtrl   *mTxtDescription = new wxTextCtrl( this, 
	   wxID_DESCRIPTION,
	   wxT(""),
	   wxDefaultPosition,
	   wxSize(360,-1),
	   0);
       //,
	   //wxTextValidator(wxFILTER_ASCII,&chk_Desc),
	   //wxTextCtrlNameStr);
   mTxtDescription->SetMaxLength(64);
   mTxtDescription->SetValidator(AsciiValid);

   // Old Code
   // wxTextCtrl   *mTxtUserDefined = new wxTextCtrl( this, wxID_DESCRIPTION, wxT(""), wxDefaultPosition, wxSize(360,-1), 0 );
   //mTxtUserDefined->SetMaxLength(64);

   // Create Evergreen Box
   wxBoxSizer *evergreenBoxSizer = new wxBoxSizer(wxVERTICAL );

   wxCheckBox* evergreenCheckBox = new wxCheckBox(this,wxID_EVERGREEN,wxT("Cut Is EVERGREEN"),wxDefaultPosition,wxDefaultSize);
   evergreenCheckBox->SetValue(false);
   evergreenBoxSizer->Add(evergreenCheckBox, 1, wxEXPAND| wxALL,3);

   // Create box sizer, start date text box and label
   wxBoxSizer   *SDateBoxSizer = new wxBoxSizer( wxHORIZONTAL );
   wxDateTime datetmp; // temporary variable to check date.
  // wxAnyStrPtr *rctmp; // temporary return code holder   This appears to be a WxWidget 3.0.2 change! toady
   wxDateTime StartDate;

   query.Printf(_T("select curdate()"));
   mysql_query(mDb,query.mb_str());
   result = mysql_store_result(mDb);
   if (mysql_num_rows(result) != 1) {           //This should Never happen
	    StartDate = wxDateTime::Now();
   } else {
       row = mysql_fetch_row(result);
	   datetmp.ParseFormat(wxString(row[0],wxConvUTF8), _T("%Y-%m-%d"));
       if (datetmp.IsValid()) {
	     StartDate = datetmp ;
	   } else {
         StartDate = wxDateTime::Now();
		}
   }
//   wxDateTime StartDate = wxDateTime::Now();
   wxString SDate = StartDate.Format(_T("%m/%d/%Y"));
   wxStaticText *SDateText = new wxStaticText( this, -1, _("Start Date:"), wxDefaultPosition, wxDefaultSize, 0 );
   wxTextCtrl   *mTxtStartDate = new wxTextCtrl( this, wxID_STARTDATE, SDate, wxDefaultPosition, wxSize(100,-1), 0 );
   int mEndDateDays = 30;     // The default End Air Date is 30 days after start
   RivendellCfg->ParseInt("DefaultAirDays","NumberOfDays", mEndDateDays);

     // Create box sizer, end date text box and label
   wxDateTime EndDate =( StartDate + wxDateSpan::Days(mEndDateDays));
   wxString EDate = EndDate.Format(_T("%m/%d/%Y"));
   wxBoxSizer	 *EDateBoxSizer = new wxBoxSizer( wxHORIZONTAL );
   wxStaticText *EDateText = new wxStaticText( this, -1, _("End Date:"), wxDefaultPosition, wxDefaultSize, 0 );
   wxTextCtrl   *mTxtEndDate = new wxTextCtrl( this, wxID_ENDDATE, EDate, wxDefaultPosition, wxSize(100,-1), 0 );
   
   // Add the desc box and label to the box sizer.
	descBoxSizer->Add(cutDescBox, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );
   descBoxSizer->Add(mTxtDescription, 0, wxALIGN_CENTER|wxALL, 5 );

   cutGridSizer->Add(descBoxSizer, 0, wxALIGN_CENTER|wxALL, 5);

   // Add the start date box and label to the box sizer.
   SDateBoxSizer->Add( SDateText, 0, wxALIGN_CENTER|wxALL, 5 );
   SDateBoxSizer->Add( mTxtStartDate, 0, wxALIGN_CENTER|wxALL, 5 );
    
   // Add the end date box and label to the box sizer.
   EDateBoxSizer->Add( EDateText, 0, wxALIGN_CENTER|wxALL, 5 );
   EDateBoxSizer->Add( mTxtEndDate, 0, wxALIGN_CENTER|wxALL, 5 );
   
   // Add the box sizers to the grid.
   dateGridSizer->Add(SDateBoxSizer, 0, wxALIGN_CENTER|wxALL, 5 );
   dateGridSizer->Add(EDateBoxSizer, 0, wxALIGN_CENTER|wxALL, 5 );
   
   // Add the grids to the static box sizer
   cutinfoBoxSizer->Add(cutGridSizer, 0, wxALIGN_CENTER);
   cutinfoBoxSizer->Add(evergreenBoxSizer, 0, wxALIGN_CENTER);
   cutinfoBoxSizer->Add(dateGridSizer, 0, wxALIGN_CENTER);
   cutinfoBoxSizer->Add(485, 0);

   cutBoxSizer->Add(cutinfoBoxSizer);

   topGridSizer->Add(cutBoxSizer, 0, wxALL, 10);
   // topGridSizer->Add(rightSizer, 0, wxTOP | wxBOTTOM | wxRIGHT, 10);

   mainBoxSizer->Add(topGridSizer, 0, wxALL, 10);
   SetSizerAndFit(mainBoxSizer);
  

	// Create the internal flexgrids and box sizers.
   wxFlexGridSizer *bottomGridSizer = new wxFlexGridSizer(1, 2, 0); 
   wxStaticBoxSizer *cartinfoBoxSizer = new wxStaticBoxSizer(new wxStaticBox(this, -1, wxT("CART Information"), 
													 wxDefaultPosition, wxDefaultSize, 0, wxT("")), wxVERTICAL);
   
   wxFlexGridSizer *cartGridSizer = new wxFlexGridSizer( 2, 0, 0 );
   wxBoxSizer       *cartBoxSizer = new wxBoxSizer( wxHORIZONTAL );
   wxFlexGridSizer *cartgroupGridSizer = new wxFlexGridSizer( 4, 0, 0 );
   wxBoxSizer *cartgroupBoxSizer = new wxBoxSizer( wxHORIZONTAL );
   wxStaticText *groupText = new wxStaticText( this, -1, _("Group:"), wxDefaultPosition, wxDefaultSize, 0 );
		
	// mysql query to get group names
  
   query.Printf(_T("select GROUP_NAME from USER_PERMS where USER_NAME = '%s' ORDER BY GROUP_NAME "), 
                riv_getuser().c_str() );
   // FIXME: should sterilize contents of riv_getusr() before sending to sql.
   mysql_query(mDb, query.mb_str());
   result = mysql_store_result(mDb);
   numRows = mysql_num_rows(result);

   wxString *stringGroups = new wxString[numRows];

   int i = 0;
   while ((row = mysql_fetch_row(result))) {
      stringGroups[i] = wxString(row[0], wxConvUTF8);
      i++;
   }

   mysql_free_result(result);

    
   wxChoice *mChoiceGroup = new wxChoice( this, wxID_GROUP, wxDefaultPosition, wxSize(-1,-1), numRows, stringGroups, 0 );
   mChoiceGroup->SetSelection(0);    
   delete[] stringGroups;
    
   cartgroupBoxSizer->Add(groupText, 0, wxALIGN_CENTER|wxALL, 5 );
   cartgroupBoxSizer->Add(mChoiceGroup, 0, wxALIGN_CENTER|wxALL, 5 );
   cartgroupGridSizer->Add(cartgroupBoxSizer, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

   wxBoxSizer *cartnumBoxSizer = new wxBoxSizer( wxHORIZONTAL );
   wxStaticText *cartnumText = new wxStaticText( this, -1, _("Cart Number:"), wxDefaultPosition, wxDefaultSize, 0 );
   cartnumBoxSizer->Add(cartnumText, 0, wxALIGN_CENTER|wxALL, 5 );

   // Build numeric validator
   wxTextValidator validator(wxFILTER_INCLUDE_CHAR_LIST);
   wxArrayString list;
   wxString valid_chars(wxT("0123456789"));
   size_t len = valid_chars.Length();
   for (size_t i = 0; i<len; i++)
   list.Add(wxString(valid_chars.GetChar(i)));
   validator.SetIncludes(list);

   wxTextCtrl *mTxtCartNumber = new wxTextCtrl( this, wxID_CARTNUMBER, wxT(""), wxDefaultPosition, wxSize(80,-1), 0 ,validator);
   cartnumBoxSizer->Add(mTxtCartNumber, 0, wxALIGN_CENTER|wxALL, 5 );
   cartgroupGridSizer->Add(cartnumBoxSizer, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

#ifndef USE_ONECUTPERCART
   wxBoxSizer *cutidBoxSizer = new wxBoxSizer( wxHORIZONTAL );
   wxStaticText *cutidText = new wxStaticText( this, -1, _("Cut Number:"), wxDefaultPosition, wxDefaultSize, 0 );
   cutidBoxSizer->Add(cutidText, 0, wxALIGN_CENTER|wxALL, 5 );

   wxTextCtrl *mTxtCutId = new wxTextCtrl( this, wxID_CUTNUMBER, wxT(""), wxDefaultPosition, wxSize(60,-1), 0 ,validator);
   cutidBoxSizer->Add(mTxtCutId, 0, wxALIGN_CENTER|wxALL, 5 );
   cartgroupGridSizer->Add(cutidBoxSizer, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
#endif

   wxButton *buttonText = new wxButton( this, wxID_BROWSE, _("Browse"), wxDefaultPosition, wxDefaultSize, 0 );
   cartgroupGridSizer->Add(buttonText, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
   //cartgroupGridSizer->Add(buttonText, 0, wxALIGN_CENTER|wxALL, 5 );
   cartinfoBoxSizer->Add(cartgroupGridSizer, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

   // create and add cart metadata text fields to cartGridSizer
   wxStaticText *titleText = new wxStaticText( this, -1, _("Title:"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
   cartGridSizer->Add(titleText, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

   wxTextCtrl *mTxtTitle = new wxTextCtrl( this, wxID_TITLE, wxT(""), wxDefaultPosition, wxSize(360,-1), 0 );
   mTxtTitle->SetMaxLength(255);
   mTxtTitle->SetValidator(AsciiValid);
   cartGridSizer->Add(mTxtTitle, 0, wxALIGN_CENTER|wxALL, 5 );

	wxStaticText *artistText = new wxStaticText( this, -1, _("Artist:"), wxDefaultPosition, wxDefaultSize, 0 );
   cartGridSizer->Add(artistText, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

   wxTextCtrl *mTxtArtist = new wxTextCtrl( this, wxID_ARTIST, wxT(""), wxDefaultPosition, wxSize(360,-1), 0 );
   mTxtArtist->SetMaxLength(255);
   cartGridSizer->Add(mTxtArtist, 0, wxALIGN_CENTER|wxALL, 5 );

   wxStaticText *yearText = new wxStaticText( this, -1, _("Year Released:"), wxDefaultPosition, wxDefaultSize, 0 );
   cartGridSizer->Add(yearText, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

   wxTextCtrl *mTxtYear = new wxTextCtrl( this, wxID_YEAR, wxT(""), wxDefaultPosition, wxSize(40,-1), 0 ,validator);
   mTxtYear->SetMaxLength(4);
   cartGridSizer->Add(mTxtYear, 0, wxALIGN_LEFT|wxALL, 5 );

   wxStaticText *albumText = new wxStaticText( this, -1, _("Album:"), wxDefaultPosition, wxDefaultSize, 0 );
   cartGridSizer->Add(albumText, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

   wxTextCtrl *mTxtAlbum = new wxTextCtrl( this, wxID_ALBUM, wxT(""), wxDefaultPosition, wxSize(360,-1), 0 );
   mTxtAlbum->SetMaxLength(255);
   cartGridSizer->Add(mTxtAlbum, 0, wxALIGN_CENTER|wxALL, 5 );

   wxStaticText *labelText = new wxStaticText( this, -1, _("Record Label:"), wxDefaultPosition, wxDefaultSize, 0 );
   cartGridSizer->Add(labelText, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

   wxTextCtrl *mTxtRecordLabel = new wxTextCtrl( this, wxID_LABEL, wxT(""), wxDefaultPosition, wxSize(360,-1), 0 );
   mTxtRecordLabel->SetMaxLength(64);
   cartGridSizer->Add(mTxtRecordLabel, 0, wxALIGN_CENTER|wxALL, 5 );

   wxStaticText *clientText = new wxStaticText( this, -1, _("Client:"), wxDefaultPosition, wxDefaultSize, 0 );
   cartGridSizer->Add(clientText, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

   wxTextCtrl *mTxtClient = new wxTextCtrl( this, wxID_CLIENT, wxT(""), wxDefaultPosition, wxSize(360,-1), 0 );
   mTxtClient->SetMaxLength(64);
   cartGridSizer->Add(mTxtClient, 0, wxALIGN_CENTER|wxALL, 5 );

   wxStaticText *agencyText = new wxStaticText( this, -1, _("Agency:"), wxDefaultPosition, wxDefaultSize, 0 );
   cartGridSizer->Add(agencyText, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

   wxTextCtrl *mTxtAgency = new wxTextCtrl( this, wxID_AGENCY, wxT(""), wxDefaultPosition, wxSize(360,-1), 0 );
   mTxtAgency->SetMaxLength(64);
   cartGridSizer->Add( mTxtAgency, 0, wxALIGN_CENTER|wxALL, 5 );

	cartinfoBoxSizer->Add(cartGridSizer, 0, wxALIGN_CENTER);
   cartinfoBoxSizer->Add(485, 0);
   	
	// OK, Cancel & Clear buttons
	wxGridSizer *buttonGridSizer = new wxGridSizer( 3, 0, 60 );

   wxButton *okButton = new wxButton( this, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
   buttonGridSizer->Add(okButton, 0, wxALIGN_CENTER|wxALL, 5 );

   wxButton *cancelButton = new wxButton( this, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
   buttonGridSizer->Add(cancelButton, 0, wxALIGN_CENTER|wxALL, 5 );

	wxButton *clearButton = new wxButton( this, wxID_CLEAR, _("Clea&r"), wxDefaultPosition, wxDefaultSize, 0 );
   buttonGridSizer->Add(clearButton, 0, wxALIGN_RIGHT|wxALL, 5 );
   
   cartBoxSizer->Add(cartinfoBoxSizer, 0, wxALIGN_CENTER|wxALL, 3 );
   bottomGridSizer->Add(cartBoxSizer, 0, wxALIGN_CENTER);      
   mainBoxSizer->Add(bottomGridSizer, 0, wxALIGN_CENTER|wxALL, 3 );
   mainBoxSizer->Add(buttonGridSizer, 0, wxALIGN_CENTER|wxALL, 3 );
        
   SetSizerAndFit(mainBoxSizer);
    
   PopulateDialog();
}    


RivendellDialog::~RivendellDialog()
{
}

void RivendellDialog::OnClear(wxCommandEvent & event)
{
    MYSQL_RES *result;
    MYSQL_ROW row;
    wxDateTime StartDate;
    wxString	query;
	wxDateTime datetmp; // temporary variable to check date.
    //wxChar * rctmp; // temporary return code holder

    ((wxTextCtrl*)FindWindow(wxID_DESCRIPTION))->Clear();
    ((wxTextCtrl*)FindWindow(wxID_STARTDATE))->Enable(true);
    ((wxTextCtrl*)FindWindow(wxID_ENDDATE))->Enable(true);
    query.Printf(_T("select curdate()"));
	mysql_query(mDb,query.mb_str());
	result = mysql_store_result(mDb);
	if (mysql_num_rows(result) != 1) {           //This should Never happen
	    StartDate = wxDateTime::Now();
        wxString SDate = StartDate.Format(_T("%m/%d/%Y"));
		((wxTextCtrl*)FindWindow(wxID_STARTDATE))->SetValue(SDate);
	} else {
	    row = mysql_fetch_row(result);
		datetmp.ParseFormat(wxString(row[0],wxConvUTF8), _T("%Y-%m-%d"));
		if (datetmp.IsValid()) {
		    StartDate = datetmp ;
		} else {
            StartDate = wxDateTime::Now();
		}
		((wxTextCtrl *)FindWindow(wxID_STARTDATE))->SetValue(datetmp.Format(_T("%m/%d/%Y")));
	}
    int mEndDateDays = 30;     // The default End Air Date is 30 days after start
    RivendellCfg->ParseInt("DefaultAirDays","NumberOfDays", mEndDateDays);
    wxDateTime EndDate =( StartDate + wxDateSpan::Days(mEndDateDays));
    wxString EDate = EndDate.Format(_T("%m/%d/%Y"));
    (((wxCheckBox*)FindWindow(wxID_EVERGREEN))->SetValue(false)); 
	((wxTextCtrl*)FindWindow(wxID_EVERGREEN))->Enable(false);
	((wxTextCtrl*)FindWindow(wxID_ENDDATE))->SetValue(EDate);
    ((wxTextCtrl*)FindWindow(wxID_CARTNUMBER))->Clear();
#ifndef USE_ONECUTPERCART
	((wxTextCtrl*)FindWindow(wxID_CUTNUMBER))->Clear();
#endif
    ((wxTextCtrl*)FindWindow(wxID_TITLE))->Clear();
    ((wxTextCtrl*)FindWindow(wxID_ARTIST))->Clear();
    ((wxTextCtrl*)FindWindow(wxID_YEAR))->Clear();
    ((wxTextCtrl*)FindWindow(wxID_ALBUM))->Clear();
    ((wxTextCtrl*)FindWindow(wxID_LABEL))->Clear();
    ((wxTextCtrl*)FindWindow(wxID_CLIENT))->Clear();
    ((wxTextCtrl*)FindWindow(wxID_AGENCY))->Clear();
}

//  If Cart Number is edited - Cut Number must be blanked
void RivendellDialog::OnCartNumberChange(wxCommandEvent & event)
{
#ifndef USE_ONECUTPERCART
    if (((wxTextCtrl*)FindWindow(wxID_CARTNUMBER))->IsModified())
    {
        ((wxTextCtrl*)FindWindow(wxID_CUTNUMBER))->Clear();
    }
#endif
}

void RivendellDialog::OnEvergreenChange(wxCommandEvent & event)
{
    MYSQL_RES *result;
    MYSQL_ROW row;
    wxDateTime StartDate;
    wxString	query;
	wxDateTime datetmp; // temporary variable to check date.
    //wxChar * rctmp; // temporary return code holder

    ((wxTextCtrl*)FindWindow(wxID_EVERGREEN))->Enable(false);

	if (((wxCheckBox *)FindWindow(wxID_EVERGREEN))->GetValue() == true) {
	    ((wxTextCtrl*)FindWindow(wxID_STARTDATE))->SetValue(_T(""));
            ((wxTextCtrl*)FindWindow(wxID_ENDDATE))->SetValue(_T(""));
            ((wxTextCtrl*)FindWindow(wxID_STARTDATE))->Enable(false);
            ((wxTextCtrl*)FindWindow(wxID_ENDDATE))->Enable(false);
	return;
	}

	if (((wxCheckBox *)FindWindow(wxID_EVERGREEN))->GetValue() == false) {
	    // All Start End Dates use current Database Server Date
            query.Printf(_T("select curdate()"));
	    mysql_query(mDb,query.mb_str());
	    result = mysql_store_result(mDb);
	    if (mysql_num_rows(result) != 1) {           //This should Never happen
		StartDate = wxDateTime::Now();
                wxString SDate = StartDate.Format(_T("%m/%d/%Y"));
		((wxTextCtrl*)FindWindow(wxID_STARTDATE))->SetValue(SDate);
	    } else {
		row = mysql_fetch_row(result);
        datetmp.ParseFormat(wxString(row[0],wxConvUTF8), _T("%Y-%m-%d"));
		if (datetmp.IsValid()) {
                    StartDate = datetmp ;
		} else {
                    StartDate = wxDateTime::Now();
		}
	((wxTextCtrl *)FindWindow(wxID_STARTDATE))->SetValue(datetmp.Format(_T("%m/%d/%Y")));
	}
	    int mEndDateDays = 30; // The default End Air Date is 30 days
        RivendellCfg->ParseInt("DefaultAirDays","NumberOfDays", mEndDateDays);
		wxDateTime EndDate =( (StartDate + wxDateSpan::Days(mEndDateDays)) );
        wxString EDate = EndDate.Format(_T("%m/%d/%Y"));
		((wxTextCtrl*)FindWindow(wxID_ENDDATE))->SetValue(EDate);
        ((wxTextCtrl*)FindWindow(wxID_STARTDATE))->Enable(true);
        ((wxTextCtrl*)FindWindow(wxID_ENDDATE))->Enable(true);
        ((wxTextCtrl*)FindWindow(wxID_EVERGREEN))->Enable(false);
	}
}

void RivendellDialog::OnChange(wxCommandEvent & event)
{

    if ( ((wxCheckBox *)FindWindow(wxID_EVERGREEN))->GetValue() == true) {
        ((wxTextCtrl*)FindWindow(wxID_STARTDATE))->Clear();
        ((wxTextCtrl*)FindWindow(wxID_ENDDATE))->Clear();
        ((wxTextCtrl*)FindWindow(wxID_STARTDATE))->Enable(false);
        ((wxTextCtrl*)FindWindow(wxID_ENDDATE))->Enable(false);
        ((wxTextCtrl*)FindWindow(wxID_EVERGREEN))->Enable(false);
    }
}

void RivendellDialog::OnChoiceGroup(wxCommandEvent & event)
{
		//int selection = mChoiceGroup->GetSelection();
		//selection++; 
}

void RivendellDialog::PopulateDialog(int cartId, int cutId)
{	
   wxDateTime datetmp; // temporary variable to check date.
   //wxChar * rctmp; // temporary return code holder
   wxString EvergreenOn;

   if (cartId == -1){
      cartId = RivendellCfg->GetCartOpened();
	}
   
   if (cutId == -1){
      cutId = RivendellCfg->GetCutOpened();
    }
   
    if (cartId != -1) {
      wxString	selection;
      selection.Printf(_("%06d_%03d"), cartId, cutId);

      MYSQL_RES *result;
      MYSQL_ROW row;
      wxDateTime StartDate;
      wxString	query;

      query.Printf(_T("select TITLE,YEAR,ARTIST,ALBUM,LABEL,CLIENT,AGENCY,GROUP_NAME from CART where NUMBER=%d"), cartId);
      mysql_query(mDb, query.mb_str());
      result = mysql_store_result(mDb);
      if (mysql_num_rows(result) != 1)
      {
         ((wxTextCtrl*)FindWindow(wxID_CARTNUMBER))->Clear();
#ifndef USE_ONECUTPERCART
         ((wxTextCtrl*)FindWindow(wxID_CUTNUMBER))->Clear();
#endif
		 return;		
      }
      row = mysql_fetch_row(result);

      ((wxTextCtrl*)FindWindow(wxID_TITLE))->SetValue(wxString(row[0], wxConvUTF8));
	  datetmp.ParseFormat(wxString(row[1], wxConvUTF8), _T("%Y-%m-%d"));
	  if (datetmp.IsValid()){
		  ((wxTextCtrl*)FindWindow(wxID_YEAR))->SetValue(datetmp.Format(_("%Y")));
	  } else {
		  ((wxTextCtrl*)FindWindow(wxID_YEAR))->SetValue(_T("")); 
	  }
      ((wxTextCtrl*)FindWindow(wxID_ARTIST))->SetValue(wxString(row[2], wxConvUTF8));
      ((wxTextCtrl*)FindWindow(wxID_ALBUM))->SetValue(wxString(row[3], wxConvUTF8));
      ((wxTextCtrl*)FindWindow(wxID_LABEL))->SetValue(wxString(row[4], wxConvUTF8));
      ((wxTextCtrl*)FindWindow(wxID_CLIENT))->SetValue(wxString(row[5], wxConvUTF8));
      ((wxTextCtrl*)FindWindow(wxID_AGENCY))->SetValue(wxString(row[6], wxConvUTF8));
	  ((wxChoice*)FindWindow(wxID_GROUP))->SetStringSelection(wxString(row[7], wxConvUTF8));

      mysql_free_result(result);

      query.Printf(_T("select DESCRIPTION,START_DATETIME,END_DATETIME,EVERGREEN from CUTS where CUT_NAME=\"%s\""), 
         selection.c_str());
      // FIXME: should sterilize contents of selection before sending to sql.

      mysql_query(mDb, query.mb_str());
      result = mysql_store_result(mDb);
      if (mysql_num_rows(result) != 1) {
         ((wxTextCtrl*)FindWindow(wxID_CARTNUMBER))->Clear();
#ifndef USE_ONECUTPERCART
         ((wxTextCtrl*)FindWindow(wxID_CUTNUMBER))->Clear();
#endif
         return;		
      }
      row = mysql_fetch_row(result);

      ((wxTextCtrl*)FindWindow(wxID_DESCRIPTION))->SetValue(wxString(row[0], wxConvUTF8));

      if (strcmp(row[3],"Y") == 0)  {
          ((wxCheckBox*)FindWindow(wxID_EVERGREEN))->SetValue(true);
          ((wxTextCtrl*)FindWindow(wxID_STARTDATE))->SetValue(_T(""));
          ((wxTextCtrl*)FindWindow(wxID_ENDDATE))->SetValue(_T(""));
          ((wxTextCtrl*)FindWindow(wxID_EVERGREEN))->Enable(false);
          ((wxTextCtrl*)FindWindow(wxID_STARTDATE))->Enable(false);
          ((wxTextCtrl*)FindWindow(wxID_ENDDATE))->Enable(false);
          ((wxTextCtrl*)FindWindow(wxID_CARTNUMBER))->Enable(false); 
#ifndef USE_ONECUTPERCART
          ((wxTextCtrl*)FindWindow(wxID_CUTNUMBER))->Enable(false); 
#endif
      } else {
          ((wxCheckBox*)FindWindow(wxID_EVERGREEN))->SetValue(false);
          ((wxTextCtrl*)FindWindow(wxID_EVERGREEN))->Enable(false);
          ((wxTextCtrl*)FindWindow(wxID_STARTDATE))->Enable(true);
          ((wxTextCtrl*)FindWindow(wxID_ENDDATE))->Enable(true);
          
          // All Start End Dates use current Database Server Date
	  mysql_free_result(result);
          query.Printf(_T("select curdate()"));
          mysql_query(mDb,query.mb_str());
          result = mysql_store_result(mDb);
          if (mysql_num_rows(result) != 1) {           //This should Never happen
	      StartDate = wxDateTime::Now();
              wxString SDate = StartDate.Format(_T("%m/%d/%Y"));
	      ((wxTextCtrl*)FindWindow(wxID_STARTDATE))->SetValue(SDate);
	  } else {
	      row = mysql_fetch_row(result);
	      datetmp.ParseFormat(wxString(row[0],wxConvUTF8), _T("%Y-%m-%d"));
	      if (datetmp.IsValid()) {
                  StartDate = datetmp;
              } else {
                  StartDate = wxDateTime::Now();
	      }
	      ((wxTextCtrl *)FindWindow(wxID_STARTDATE))->SetValue(StartDate.Format(_T("%m/%d/%Y")));
	  }
	  int mEndDateDays = 30; // The default End Air Date is 30 days
          RivendellCfg->ParseInt("DefaultAirDays","NumberOfDays", mEndDateDays);
	  wxDateTime EndDate =( (StartDate + wxDateSpan::Days(mEndDateDays)) );
          wxString EDate = EndDate.Format(_T("%m/%d/%Y"));
	  ((wxTextCtrl*)FindWindow(wxID_ENDDATE))->SetValue(EDate);
	  mysql_free_result(result);
      }
      wxString	cartNumber; 
      wxString	cutNumber; 
      cartNumber.Printf(_T("%06d"), cartId);
      cutNumber.Printf(_T("%03d"), cutId);

      ((wxTextCtrl*)FindWindow(wxID_CARTNUMBER))->SetValue(cartNumber);
	  #ifndef USE_ONECUTPERCART
        ((wxTextCtrl*)FindWindow(wxID_CUTNUMBER))->SetValue(cutNumber);
	  #endif
	} else {
        ((wxTextCtrl*)FindWindow(wxID_CARTNUMBER))->Clear();
	    #ifndef USE_ONECUTPERCART
		  ((wxTextCtrl*)FindWindow(wxID_CUTNUMBER))->Clear();
	    #endif
        ((wxCheckBox*)FindWindow(wxID_EVERGREEN))->SetValue(false);
        ((wxTextCtrl*)FindWindow(wxID_EVERGREEN))->Enable(false);
	}
}


void RivendellDialog::OnBrowse(wxCommandEvent & event)
{
    RivendellBrowseDialog dlog(this, mDb);
    if (dlog.ShowModal() == wxID_OK)
    {
     wxString	selection = dlog.GetSelection(RD_BROWSE_CUT_NAME);
     
     int		cartId,
                 cutId;
     sscanf(selection.mb_str(), "%d_%d", &cartId, &cutId);
    
	 PopulateDialog(cartId, cutId);
    } else
     ((wxTextCtrl*)FindWindow(wxID_CARTNUMBER))->Clear();
}

void RivendellDialog::OnOK(wxCommandEvent & event)
{
    //
    // Checks for required fields on the form.
    if (((wxTextCtrl*)FindWindow(wxID_TITLE))->GetValue().IsEmpty()) {
      wxMessageBox(_("Empty Title"), _("Rivendell"), wxICON_ERROR|wxOK);
      return;
    }
    if (((wxTextCtrl*)FindWindow(wxID_DESCRIPTION))->GetValue().IsEmpty()) {
      wxMessageBox(_("Empty Description"), _("Rivendell"), wxICON_ERROR|wxOK);
      return;
    }
	
    // Checks for valid cart range.
    wxString groupString = ((wxChoice*)FindWindow(wxID_GROUP))->GetStringSelection();

	if (groupString.IsEmpty())
	{
		wxMessageBox(_("      Cannot Export \n No Valid Group Selected"), _("Rivendell"), wxICON_ERROR|wxOK);
        return;
	}

	Process_Riv_Export(groupString);
	return;
    
}


// This checks for Ascii - and also doesn't allow first character as space
//  Todd BAKER   01-05-16
bool RivendellDialog::Chk_Ascii(const char* chk_string)
{
    for (int i = 0 ; *chk_string != '\0' ; i++, chk_string++)
    {
        if ((i == 0) && (*chk_string == 32))
        {
	    return false;
        }
	if ((*chk_string>127) || (*chk_string < 0))
	{
	    return false;
	}
    }
    return true;
}	
void RivendellDialog::Export_Failure(const char * cutname, const wxString msg)
{
	wxString query;

	if (strlen(cutname) > 0)
	{
		query.Printf("update CUTS set LENGTH = 0, VALIDITY=0, SUN=\"N\",MON=\"N\",TUE=\"N\",WED=\"N\", \
					 	    THU=\"N\",FRI=\"N\",SAT=\"N\" where CUT_NAME = \"%s\"", cutname);
		mysql_query(mDb, query.mb_str());
	}

	wxMessageBox(_(msg), _("Rivendell"), wxICON_ERROR | wxOK);
	return;
}
bool RivendellDialog::Chk_Title(char * Title)
{

    wxString hold_Title = ((wxTextCtrl*)FindWindow(wxID_TITLE))->GetValue().wx_str();
    if (!Chk_Ascii(WX2UNI(hold_Title)))
    {
        wxMessageBox(_("Error: Illegal Character(s) detected in Title!\nCheck For Spaces at Beginning"),
            _("Rivendell"), wxICON_ERROR|wxOK);
        return false;
    }
	strcpy(Title, WX2UNI(hold_Title));
	
    return true;
}
bool RivendellDialog::Chk_Artist(char * Artist)
{

    wxString hold_Artist = ((wxTextCtrl*)FindWindow(wxID_ARTIST))->GetValue().wx_str();
    if (!Chk_Ascii(WX2UNI(hold_Artist)))
    {
        wxMessageBox(_("Error: Illegal Character(s) detected in Artist!\nCheck For Spaces at Beginning"),
            _("Rivendell"), wxICON_ERROR|wxOK);
        return false;
    }
	strcpy(Artist, WX2UNI(hold_Artist));

    return true;
}

bool RivendellDialog::Chk_Album(char * Album)
{
    wxString hold_Album = ((wxTextCtrl*)FindWindow(wxID_ALBUM))->GetValue().wx_str();
    if (!Chk_Ascii(WX2UNI(hold_Album)))
    {
        wxMessageBox(_("Error: Illegal Character(s) detected in Album!\nCheck For Spaces at Beginning"),
            _("Rivendell"), wxICON_ERROR|wxOK);
        return false;
    }
	strcpy(Album, WX2UNI(hold_Album));

    return true;
}

bool RivendellDialog::Chk_Label(char * Label)
{
    wxString hold_Label = ((wxTextCtrl*)FindWindow(wxID_LABEL))->GetValue().wx_str();
    if (!Chk_Ascii(WX2UNI(hold_Label)))
    {
        wxMessageBox(_("Error: Illegal Character(s) detected in Label!\nCheck For Spaces at Beginning"),
            _("Rivendell"), wxICON_ERROR|wxOK);
        return false;
    }
	strcpy(Label, WX2UNI(hold_Label));

    return true;
}

bool RivendellDialog::Chk_Client( char * Client)
{
    wxString hold_Client = ((wxTextCtrl*)FindWindow(wxID_CLIENT))->GetValue().wx_str();
    if (!Chk_Ascii(WX2UNI(hold_Client)))
    {
	wxMessageBox(_("Error: Illegal Character(s) detected in Client!\nCheck For Spaces at Beginning"),
	    _("Rivendell"), wxICON_ERROR|wxOK);
        return false;
    }
	strcpy(Client, WX2UNI(hold_Client));

    return true;
}

bool RivendellDialog::Chk_Agency( char * Agency)
{
    wxString hold_Agency = ((wxTextCtrl*)FindWindow(wxID_AGENCY))->GetValue().wx_str();
    if (!Chk_Ascii(WX2UNI(hold_Agency)))
    {
	wxMessageBox(_("Error: Illegal Character(s) detected in Agency!\nCheck For Spaces at Beginning"),
	    _("Rivendell"), wxICON_ERROR|wxOK);
	return false;
    }
	strcpy(Agency, WX2UNI(hold_Agency));

    return true;
}

bool RivendellDialog::Chk_Description( char * Description)
{
    wxString hold_Description = ((wxTextCtrl*)FindWindow(wxID_DESCRIPTION))->GetValue().wx_str();
    if (!Chk_Ascii(WX2UNI(hold_Description)))
    {
        wxMessageBox(_("Error: Illegal Character(s) detected in Description!\nCheck For Spaces at Beginning"),
            _("Rivendell"), wxICON_ERROR|wxOK);
        return false;
    }
	strcpy(Description, WX2UNI(hold_Description));

    return true;
}

bool RivendellDialog::Get_Rivendell_2_Parameters(int * format,
	int * channels,
	int * samplerate,
	const char rivHost[],
	const char ticket[])
{
	char str[255];
	char *endPtr;
	int webResult;
	unsigned numrecs = 0;
	struct rd_system_settings *system_settings = 0;

	// Set RDACITY_VERSION STRING
	char RDACITY_VERSION_STRING[255] = RDACITY_VERSION;
	//Add Rivendell C Library Info
	strcat(RDACITY_VERSION_STRING, RD_GetUserAgent());
	strcat(RDACITY_VERSION_STRING, RD_GetVersion());

	if (!RivendellCfg->ParseString("DefaultContentParameters", "DefaultFormat", str))
	{
		wxMessageBox(_("Unable to find DefaultFormat in rd configuration"), _("Rivendell"), wxICON_ERROR | wxOK);
		return false;
	}
	else
	{
		*format = strtol(str, &endPtr, 10);
	}

	if (!RivendellCfg->ParseString("DefaultContentParameters", "DefaultChannels", str))
	{
		wxMessageBox(_("Unable to find DefaultChannels in rd configuration"), _("Rivendell"), wxICON_ERROR | wxOK);
		return false;
	}
	else
	{
		*channels = strtol(str, &endPtr, 10);
	}

	webResult = RD_ListSystemSettings(&system_settings,
		rivHost,
		"",
		"",
		ticket,
		RDACITY_VERSION_STRING,
		&numrecs);
	if (webResult < 0)
	{
		wxMessageBox(_("Unable to find DefaultSampRate in rd configuration"), _("Rivendell"), wxICON_ERROR | wxOK);
		return false;
	}

	if ((webResult < 200 || webResult > 299) &&
		(webResult != 0))
	{
		switch (webResult)
		{
		case 403:
			wxMessageBox(_("Please Try Again \n Authentification Credentials Failed \n"), _("Rivendell"), wxICON_ERROR | wxOK);
			return false;
		default:
			wxMessageBox(_("Error Attempting to Read Default Sample Rate from DB!\n"), _("Rivendell"), wxICON_ERROR | wxOK);
			return false;
		}
	}

	if (numrecs == 1)
	{
		*samplerate = system_settings[numrecs - 1].sample_rate;
	}
	else
	{
		return false;
	}
	return true;
}

void RivendellDialog::Process_Riv_Export(wxString groupString)
{

    double length = 0.0;    //Figure out the length below;
    int format=0;
    int channels=0;
    int samplerate=0;
    char	soundsDir[255];  // FIXME: make this a wxString.
    wxString fName;
    char rivHost[255];     //The Rivendell Host - Web API Call will user
    char rivUser[255]; // The Rivendell User to use for Web Call
    int webResult;
    int result;
    int create_flag = 0;
    unsigned long cartNewNumber = 0;
    unsigned long cutNewNumber = 1;
    wxString holdCutId;
    struct rd_cartimport *cartimport=0;
    struct rd_cart *carts=0;
    struct rd_cut *cuts=0;
    unsigned numrecs = 0;
    wxString cutName;
	wxString msg;
    char rivTicket[41]="";
    char rivPass[33] = "";
		
	// Set RDACITY_VERSION STRING
	char RDACITY_VERSION_STRING[255] = RDACITY_VERSION;
	//Add Rivendell C Library Info
	strcat(RDACITY_VERSION_STRING, RD_GetUserAgent());
	strcat(RDACITY_VERSION_STRING, RD_GetVersion());

    AudacityProject *p = GetActiveProject();

	// Date checking (Start and End).
	/* FIXME: add checking for sane date values and possibly "TOD" "TFN"
	since right now only proper formatting is checked*/
	wxString sDate;
	wxString eDate;
	if (!Check_Start_End_Date(&sDate, &eDate))
		return;


    // Calculate cart number for content.
    if (((wxTextCtrl*)FindWindow(wxID_CARTNUMBER))->GetValue().IsEmpty() ||
        !((wxTextCtrl*)FindWindow(wxID_CARTNUMBER))->GetValue().ToULong(&cartNewNumber))
    {
        cartNewNumber=0;
        cutNewNumber=0;
        create_flag = 1;
    }
    else
    {
		#ifndef USE_ONECUTPERCART
        if (((wxTextCtrl*)FindWindow(wxID_CUTNUMBER))->GetValue().IsEmpty() ||
           (!((wxTextCtrl*)FindWindow(wxID_CUTNUMBER))->GetValue().ToULong(&cutNewNumber)) )
        {        // This has a Cart Number but NO Cut Number!
 	    wxMessageBox(_("Cart Number Must have A Cut Number"), _("Rivendell"), wxICON_ERROR|wxOK);
            return;
        }
	    #endif
    }


    if (!RivendellCfg->ParseString("RivendellWebHost", "Rivhost", rivHost))
    {
	Export_Failure( "", (_("The Export FAILED !Incorrect 2.0 Configuration !")));
	return;
    }
	wxString username = RivUtils->Get_System_User();

	strcpy(rivUser, username.c_str());

	char *ticket_ptr;
	ticket_ptr = &rivTicket[0];

	if (!RivUtils->Get_Current_Ticket(ticket_ptr))
	{
		if (!RivUtils->Rivendell_Login(this, &ticket_ptr, rivUser))
			return;
	}
	else
	{
		if (!RivUtils->Validate_Ticket(rivHost, ticket_ptr))
		{
			if (!RivUtils->Rivendell_Login(this, &ticket_ptr, rivUser))
				return;
		}
	}
	
    if (cartNewNumber !=0)  // Check that they want to Overwrite
    {
        if (!Verify_Update(cartNewNumber, &cutNewNumber,
		rivHost, rivUser, rivPass, rivTicket ))
	    return;
    }
    cutName.Printf(_T("%06d_%03d"), (int)cartNewNumber, (int)cutNewNumber);
    //
    // Get Rivendell Parameters
    //
    if (!Get_Rivendell_2_Parameters( &format, &channels, 
			&samplerate, rivHost, ticket_ptr))
        return;

    // Do the work required to export.

    int exportstatus = 0; 
    ExportPlugin * e;
    e = New_ExportPCM();
 
    // Retrieve destination sound dir from the configuration file.
    if (!RivendellCfg->ParseString("Cae", "AudioRoot", soundsDir)) 
    {
        wxMessageBox(_("Unable to find AudioRoot in rd configuration"), _("Rivendell"), wxICON_ERROR|wxOK);
        return;
    }
    #ifdef _WIN32
        fName.Printf(_T("%s\\%s.wav"), wxString(soundsDir, wxConvLocal).c_str() ,cutName.c_str());
    #else
        fName.Printf(_T("%s%s.wav"), wxString(soundsDir, wxConvLocal).c_str(), cutName.c_str());
    #endif
    
    // Create a mixerspec object to be used on the export below.
    MixerSpec * ms;
    ms = new MixerSpec( 1, 2 );
       
    p->AS_SetRate(samplerate); 
    if (mSaveSelection)
    {
      exportstatus = e->Export(p, channels, fName, true, p->GetSel0(), p->GetSel1(), ms, 0,format);
    }
    else
    {
      exportstatus = e->Export(p, channels, fName, false, 0.f, p->GetTracks()->GetEndTime(), ms, 0,format);
    }
    p->AS_SetRate(samplerate);
    EndModal(wxID_OK);

// Need to check exportstatus and if failed turn all days OFF
// Change Validity to Zero, Length to Zero
    
    if (exportstatus != 1)  
    {
	Export_Failure( cutName.c_str(),
	    (_("The Export appears to have FAILED !!!")));
	return;
    }
	
    if (!Compute_Length(&length))
    {
        wxMessageBox(_("Export Appears to have ZERO Length"), _("Rivendell"), wxICON_ERROR|wxOK);

        return;
    }
    // Sterilize content from GUI dialog before sending it to SQL.
    char rd_title[513*4];    // sized for mysql_real_escape_string() to be ((len * 2) * 4)+1  (for Unicode too).
    char rd_artist[513*4];
    char rd_album[513*4];
    char rd_label[129*4];
    char rd_client[129*4];
    char rd_agency[129*4];
    char rd_description[129*4];

    if (!Chk_Title(&rd_title[0]))
       return;

    if (!Chk_Artist(&rd_artist[0]))
       return;

    if (!Chk_Album(&rd_album[0]))
        return;

    if (!Chk_Label(&rd_label[0]))
        return;

    if (!Chk_Client(&rd_client[0]))
        return;

    if (!Chk_Agency(&rd_agency[0]))
        return;
    
    if (!Chk_Description(&rd_description[0]))
        return;

	// Set Year
	wxString year;
	year = ((wxTextCtrl*)FindWindow(wxID_YEAR))->GetValue();
	int rd_year = wxAtoi(year);

	// Start Progress Bar In Another Thread
    MyProgressThread* myprogressthread = new MyProgressThread();
	
    webResult = RD_ImportCart(&cartimport,
        rivHost,
    	rivUser,
	    rivPass,
		rivTicket,
		cartNewNumber,
		cutNewNumber,
		(unsigned)1,
		0,
		0,
		0,
		create_flag,
		groupString.c_str(),  
		rd_title,
		fName,
		RDACITY_VERSION_STRING,
		&numrecs);

	// Kill the progress Thread
	myprogressthread->Delete();
	myprogressthread->Wait();
	delete myprogressthread;
 
	if (webResult < 0)
	{
            Export_Failure( "", (_("The Export FAILED ! Server Error !")));
	    return;
	}
 
	if ((webResult < 200 || webResult > 299) &&
		(webResult != 0))
	{
	    switch (webResult) 
            {
		case 404:
			msg.Printf("Export Failure: %s", cartimport[0].error_string);
		    Export_Failure("",
			(_(msg)));
			return;
		case 403:
			wxMessageBox(_("Please Try Again \n Authentification Credentials Failed \n"), _("Rivendell"), wxICON_ERROR | wxOK);
			return;
		case  401:
		    Export_Failure( "",
			(_("The Export FAILED ! Unauthorized or Cart out of Range")));
			return;
		default:
		    Export_Failure( cutName.c_str(),
			(_("The Export FAILED ! Server Error !")));
			return;
            }
	}
	
	if (numrecs == 1)
    { 
        cartNewNumber = cartimport[numrecs - 1].cart_number;
        cutNewNumber =  cartimport[numrecs - 1].cut_number;
    }
    cutName.Printf(_T("%06d_%03d"), (int)cartNewNumber, (int)cutNewNumber);
        
    //  Edit Cart Update
    struct edit_cart_values edit_cart;
    memset(&edit_cart,0,sizeof(struct edit_cart_values));
    edit_cart.use_cart_title = 1;
    strcpy( edit_cart.cart_title, rd_title);
    edit_cart.use_cart_artist = 1;
    strcpy( edit_cart.cart_artist,rd_artist);
    edit_cart.use_cart_album = 1;
    strcpy( edit_cart.cart_album, rd_album);
    edit_cart.use_cart_label = 1;
    strcpy( edit_cart.cart_label, rd_label);
    edit_cart.use_cart_client = 1;
    strcpy( edit_cart.cart_client, rd_client);
    edit_cart.use_cart_agency = 1;
    strcpy( edit_cart.cart_agency, rd_agency);
	edit_cart.use_cart_year = 1;
	edit_cart.cart_year = rd_year;
	result= RD_EditCart(&carts,
        edit_cart,
        rivHost,
        rivUser,
        rivPass,
	    rivTicket,
        cartNewNumber,
		RDACITY_VERSION_STRING,
        &numrecs);
	if ((result< 200 || result > 299) &&
        (result != 0))
    {
        switch(result) 
		{
            case 400:
		        Export_Failure( cutName.c_str(),
			    (_("Edit Cart Failure: 400 Error !")));
                return;
            case 404:
		       Export_Failure( cutName.c_str(),
                   (_("Edit Cart Failure: Possible Duplicate Cart Error !")));
	           return;
            default:
		       Export_Failure( cutName.c_str(),
                   (_("Edit Cart FAILED ! Unknown  Error !")));
               return;
        }        
    }
        
    //Edit Cut Update
    struct edit_cut_values edit_cut;
    memset(&edit_cut,0,sizeof(struct edit_cut_values));
    edit_cut.use_cut_description=1;
    strcpy(edit_cut.cut_description,rd_description);
	edit_cut.use_cut_start_datetime = 1;
	edit_cut.cut_start_datetime.tm_year = (wxAtoi(sDate.Mid(1, 4)) - 1900);
	edit_cut.cut_start_datetime.tm_mon = (wxAtoi(sDate.Mid(6, 2)) - 1);
	edit_cut.cut_start_datetime.tm_mday = wxAtoi(sDate.Mid(9, 2));
	edit_cut.use_cut_end_datetime = 1;
	edit_cut.cut_end_datetime.tm_year = (wxAtoi(eDate.Mid(1, 4)) - 1900);
	edit_cut.cut_end_datetime.tm_mon = (wxAtoi(eDate.Mid(6, 2)) - 1);
	edit_cut.cut_end_datetime.tm_mday = wxAtoi(eDate.Mid(9, 2));


    result= RD_EditCut(&cuts,
        edit_cut,
        rivHost,
        rivUser,
        rivPass,
	    rivTicket,
        cartNewNumber,
        cutNewNumber,
		RDACITY_VERSION_STRING,
        &numrecs);
	if ((result< 200 || result > 299) &&
        (result != 0))
    {
        switch(result) 
		{
           case 400:
                Export_Failure( cutName.c_str(),
                    (_("The Export FAILED ! 400 Error !")));
                return;
           case 404:
               Export_Failure( cutName.c_str(),
                   (_("The Export FAILED ! 404 Error !")));
               return;
           default:
               Export_Failure( cutName.c_str(),
                   (_("The Export FAILED ! Unknown  Error !")));
               return;
        }
    }
    return;
}

bool RivendellDialog::Compute_Length(double * length)
{

    AudacityProject *p = GetActiveProject();

    //
    //         Figure out length allowing for Muted track(s)
    //
    if (mSaveSelection)
    {
	TrackList *tracks = p->GetTracks();
	TrackListIterator iter1(tracks);
	Track *tr = iter1.First();
	double max = 0.0;
	while (tr) 
        {
            if ( (tr->GetKind() == Track::Wave) &&
               (tr->GetSelected()) &&
               (!tr->GetMute() ) ) 
            {
                if (max < tr->GetEndTime())
                {
                    max= tr->GetEndTime();
                }
	    }
	    tr = iter1.Next();
	}
	if (max < (p->GetSel1() - p->GetSel0()))
	{
            *length = max;
	}
	else
	{
            *length = p->GetSel1() - p->GetSel0();
	}
    }
    else
    {
        TrackList *tracks = p->GetTracks();
	TrackListIterator iter1(tracks);
	Track *tr = iter1.First();
	double max = 0.0;
	while (tr) 
        {
            if ( (tr->GetKind() == Track::Wave) &&
               (!tr->GetMute() ) ) 
            {
                if (max < tr->GetEndTime())
                {
                    max= tr->GetEndTime();
                }
	    }
            tr = iter1.Next();
	}
	*length = max;
    }

    // Checking that there IS actually something to export (length not zero)...
    if (length == 0)
    {
        wxString message;
        wxString titlebox;
        if(mSaveSelection)
        {
            message = _("There is no Audio Selected to be Exported \nCheck for Muted Track(s).");
            titlebox = _("Unable to Export Selection to Rivendell");
        }
        else
        {
            message = _("There is no Audio to be Exported \nCheck for Muted Track(s).");
            titlebox = _("Unable to Export to Rivendell");
        }

        wxMessageBox(message,
            titlebox,
            wxICON_ERROR|wxOK);
        return false;
    }

    return true;
}
bool RivendellDialog::Check_Start_End_Date( wxString * sdate, wxString * edate)
{
    wxDateTime datetmp = wxDateTime::Now(); // temporary variable to check date.
    wxDateTime datetmp2 = wxDateTime::Now(); // temp variable for checking dates
    bool errorflag; // errorflag for messagebox if dates have improper length

    if (((wxCheckBox *)FindWindow(wxID_EVERGREEN))->GetValue() == true) {
        *sdate = _T("NULL");
        *edate = _T("NULL");
    } else {	
        // Verify valid format for Start Date.
        errorflag = false;
        *sdate = ((wxTextCtrl*)FindWindow(wxID_STARTDATE))->GetValue();
        if (sdate->length() == 8) { 		
			if (!datetmp.ParseFormat(*sdate, _T("%m/%d/%y"))) {
				errorflag = true;
			}
        } else if (sdate->length() == 10) {
			if (!datetmp.ParseFormat(*sdate, _T("%m/%d/%Y"))) {
				errorflag = true;
			}
        } else {
            errorflag = true;
		}

        if (errorflag == true) {
            wxMessageBox(_("Start Date Format Error (MM/DD/YYYY)"), _("Rivendell"), wxICON_ERROR|wxOK);
            return false;
            }
        // Format sDate for the Database
        *sdate = datetmp.Format(_T("\"%Y-%m-%d\""));

        // Verify valid format for End Date.
        errorflag = false;
        *edate = ((wxTextCtrl*)FindWindow(wxID_ENDDATE))->GetValue();
        if (edate->length() == 8) { 		
			if (!datetmp2.ParseFormat(*edate, _T("%m/%d/%y"))) {
				errorflag = true;
			}
        } else if (edate->length() == 10) {
			if (!datetmp2.ParseFormat(*edate, _T("%m/%d/%Y"))) {
				errorflag = true;
			}
		} else {
            errorflag = true;
        }

        if (errorflag == true) {
            wxMessageBox(_("End Date Format Error (MM/DD/YYYY)"), _("Rivendell"), wxICON_ERROR|wxOK);
            return false;
        }
        // Format eDate for the Database
        *edate = datetmp2.Format(_T("\"%Y-%m-%d\""));

		// Verify Start Date not Greater than End Date
	    if (datetmp >= datetmp2)  {
            wxMessageBox(_("      Start Date Cannot be Greater Than or Equal To End Date"), _("Rivendell"), wxICON_ERROR|wxOK);
            return false;
	    }
    }
    return true;
} 

bool RivendellDialog::Verify_Update( unsigned long  cartnum, unsigned long * cutnum,
		const char host[], const char user[],
		const char rivpass[], const char rivticket[])
{

    struct rd_cart *cart=0;
    struct rd_cut *cut=0;
    unsigned numrecs;

   wxString msg;

   // Set RDACITY_VERSION STRING
   char RDACITY_VERSION_STRING[255] = RDACITY_VERSION;
   //Add Rivendell C Library Info
   strcat(RDACITY_VERSION_STRING, RD_GetUserAgent());
   strcat(RDACITY_VERSION_STRING, RD_GetVersion());

    int result = RD_ListCart( &cart,
	host,
	user,
	rivpass,
	rivticket,
	cartnum,
	RDACITY_VERSION_STRING,
	&numrecs);
    if (result == 0)
    {
        int result2 = RD_ListCut( &cut,
	    host,
	    user,
	    rivpass,
	    rivticket,
	    cartnum,
	    *cutnum,
		RDACITY_VERSION_STRING,
	    &numrecs);
        if (result2 == 0)    //WE Verify the update
        {
            int answer = wxMessageBox(_("WARNING! You are about to overwrite an existing file - are you sure?"), _("Rivendell"), wxYES_NO|wxICON_EXCLAMATION);
            if (wxNO == answer) 
                return false;
            else
                return true;
        }
        else
        {            //This generates a new Cut Number for the CART
	    #ifndef USE_ONECUTPERCART
            if (result2 == 404)
            {                                        // CUT Doesn't Exist - Add it now
                result2 = RD_AddCut( &cut,
                    host,
                    user,
                    rivpass,
	            rivticket,
                    cartnum,
					RDACITY_VERSION_STRING,
                    &numrecs);
	        if (result2 < 0)
		{
                    wxMessageBox(_("System Error Adding Cut! - Aborting"), 
                        _("Rivendell"), wxICON_ERROR|wxOK);
                    return false;
		}
                if ((result2< 200 || result2 > 299) &&
       	   	    (result2 != 0))
  		{
    		    switch(result) {
			case 404:
			    wxMessageBox(_("Error: Unable to Add Cut! - UnAuthorized"), 
                                _("Rivendell"), wxICON_ERROR|wxOK);
                    	    return false;
			break;
			default:
                            wxMessageBox(_("Unknown System Error - Aborting"), 
                                _("Rivendell"), wxICON_ERROR|wxOK);
                            return false;
		    }
                }
                *cutnum = cut->cut_cut_number;
	        return true;
            }
            else
            {
                wxMessageBox(_("Unknown System Error - Aborting"), 
                    _("Rivendell"), wxICON_ERROR|wxOK);
                return false;
            }   
		#else

			*cutnum = 1;
        #endif
		}
    }
    else   // Cart Doesn't Exist! Cannot do it this way!
    {
        wxMessageBox(_("Error: Clear Cart Number to Create Cart!"),
            _("Rivendell"), wxICON_ERROR|wxOK);
        return false;
    }
    //  Should not ever get here!
    return true;
}
