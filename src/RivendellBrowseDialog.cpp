/**********************************************************************

  Rdacity: A Digital Audio Editor powered by Audacity(R)

  RivendellBrowseDialog.cpp

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
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

//#include <windows.h>
#include "./export/ExportPCM.h"
#include "Project.h"
#include "RivendellBrowseDialog.h"
#include "RivendellConfig.h"
#include "Audacity.h"

#include <string.h>

#define ID_LISTCTRL             1000
#define ID_GROUP                1001
#define ID_FILTER               1002
#define ID_NEXT                 1003
#define ID_SORT                 1004

#define WX2UNI(s) ((const char *)s.ToUTF8())

BEGIN_EVENT_TABLE(RivendellBrowseDialog, wxDialog)
   EVT_BUTTON(wxID_OK, RivendellBrowseDialog::OnOK)
   EVT_LIST_ITEM_ACTIVATED(ID_LISTCTRL, RivendellBrowseDialog::OnOKList)
   EVT_LIST_COL_CLICK(ID_LISTCTRL,RivendellBrowseDialog::OnColClick)
   EVT_CHOICE(ID_GROUP, RivendellBrowseDialog::OnChoiceGroup)
   EVT_CHOICE(ID_SORT, RivendellBrowseDialog::OnChoiceSort)
   EVT_TEXT(ID_FILTER, RivendellBrowseDialog::OnSearchText)
   EVT_BUTTON(ID_NEXT, RivendellBrowseDialog::OnNext)
END_EVENT_TABLE()

IMPLEMENT_CLASS(RivendellBrowseDialog, wxDialog)



RivendellBrowseDialog::RivendellBrowseDialog(wxWindow * parent, MYSQL *db)
:  wxDialog(parent, -1, _("Rivendell Browse, User: ") + riv_getuser(db),
         wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxWANTS_CHARS | wxRESIZE_BORDER)
{
   mLastSearchIdx = 0;
   mDb = db;
   MYSQL_RES *result;
   MYSQL_ROW row;
   wxString query;
   wxString *stringGroups;
   wxString *sortByChoices;
   int i;
   int numRows;
   curSortState = NOCLICKS;

   // Generate browse dialog GUI.
   wxBoxSizer* item0 = new wxBoxSizer( wxVERTICAL );
   wxFlexGridSizer *item3 = new wxFlexGridSizer( 4, 0, 0 );
   wxBoxSizer *item2 = new wxBoxSizer( wxHORIZONTAL );
   wxBoxSizer *sortBy = new wxBoxSizer( wxHORIZONTAL );

   wxBoxSizer *item8 = new wxBoxSizer( wxHORIZONTAL );
    
   wxStaticText *item6 = new wxStaticText( this, -1, _("Search:"), wxDefaultPosition, wxDefaultSize, 0 );
   item8->Add( item6, 0, wxALIGN_CENTER|wxALL, 5 );

   wxTextCtrl *item7 = new wxTextCtrl( this, ID_FILTER, _(""), wxDefaultPosition, wxSize(200,-1), 0 );
   item8->Add( item7, 0, wxALIGN_CENTER|wxALL, 5 );
   wxButton *item10 = new wxButton( this, ID_NEXT, _("Next"), wxDefaultPosition, wxDefaultSize, 0 );
   item8->Add( item10, 0, wxALIGN_CENTER|wxALL, 5 );
    
   // Populate valid groups corresponding to the Rivendell user.
   wxStaticText *item9 = new wxStaticText( this, -1, _("Group:"), wxDefaultPosition, wxDefaultSize, 0 );
   item2->Add( item9, 0, wxALIGN_CENTER|wxALL, 5 );

   query.Printf(_("select GROUP_NAME from USER_PERMS where USER_NAME = '%s' ORDER BY GROUP_NAME "), 
                riv_getuser(mDb).c_str() );
   // FIXME: should sterilize contents of riv_getusr() before sending to sql.
   mysql_query(mDb, query.mb_str());
   result = mysql_store_result(mDb);
   numRows = mysql_num_rows(result);
   stringGroups = new wxString[numRows+1];
   stringGroups[0] = _("ALL");
   i = 1;
   while ((row = mysql_fetch_row(result)))
   {
      stringGroups[i] = wxString(row[0], wxConvUTF8);
      i++;
   }
   mysql_free_result(result);
    
   wxChoice *mChoiceGroup = new wxChoice( this, ID_GROUP, wxDefaultPosition, wxSize(-1,-1), numRows+1, stringGroups, 0 );
   mChoiceGroup->SetSelection(0);    
   // Remove stringGroups memory because we dont need it 
   //(FIXME: commmented out because this may still be in use by

   // delete[] stringGroups;

   // Populate the Sort By List
   wxStaticText  *sortByLabel = new wxStaticText( this, -1, _("Sort By:"), wxDefaultPosition, wxDefaultSize, 0 );
   sortBy->Add( sortByLabel, 0, wxALIGN_CENTER|wxALL,5 );
   sortByChoices = new wxString[3];
   sortByChoices[0] = _("Cart Title" );
   sortByChoices[1] = _("Cut Description" );
   sortByChoices[2] = _("Cart_Cut Number" );
   wxChoice *mChoiceOrder = new wxChoice( this, ID_SORT, wxDefaultPosition, wxSize(-1,-1), 3, sortByChoices, 0 );
   mChoiceOrder->SetSelection(0);
 
   // Continue with generating the rest of browse dialog GUI.

   item2->Add( mChoiceGroup, 0, wxALIGN_CENTER|wxALL, 5 );
   item3->Add( item2, 0, wxALIGN_CENTER|wxALL, 5 );

   sortBy->Add( mChoiceOrder, 0, wxALIGN_CENTER|wxALL, 5 );
   item3->Add( sortBy, 0, wxALIGN_CENTER|wxALL, 5 );
   
   
    
   item3->Add( item8, 0, wxALIGN_CENTER|wxALL, 5 );
    
   item0->Add( item3, 0, wxALIGN_CENTER|wxALL, 5 );

   wxListCtrl *item1 = new MyListCtrl( this, ID_LISTCTRL, wxDefaultPosition, wxSize(610,220), wxLC_REPORT|wxLC_VIRTUAL|wxSUNKEN_BORDER|wxLC_SINGLE_SEL, mRecs);
   item1->InsertColumn(0, _("Cart Title"),wxLIST_FORMAT_LEFT, 250);
   item1->InsertColumn(1, _("Cut Description"),wxLIST_FORMAT_LEFT, 250);
   item1->InsertColumn(2, _("Cart Cut Number"),wxLIST_FORMAT_LEFT, 150);
    
   wxGridSizer *item37 = new wxGridSizer( 2, 0, 100 );

   wxButton *item38 = new wxButton( this, wxID_OK, _("OK"), wxDefaultPosition, wxDefaultSize, 0 );
   item37->Add( item38, 0, wxALIGN_CENTER|wxALL, 5 );

   wxButton *item39 = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
   item37->Add( item39, 0, wxALIGN_CENTER|wxALL, 5 );


   // Populate list contents from Rivendell database.
   GetRivendellData();

   item1->SetItemCount(mRecs.size());
   item0->Add( item1, 1, wxEXPAND|wxALIGN_CENTER|wxALL, 5 );
   item0->Add( item37, 0, wxALIGN_CENTER|wxALL, 5 );

   SetAutoLayout(true);
   SetSizerAndFit(item0);
}    


RivendellBrowseDialog::~RivendellBrowseDialog()
{
   
   for (int i = 0; i < (int)mRecs.size(); i++)
   {
      if (mRecs[i].mDescription)
         free(mRecs[i].mDescription);
      if (mRecs[i].mTitle)
         free(mRecs[i].mTitle);
   }
   mRecs.clear();
   
   //ClearRivendellData();
}


void RivendellBrowseDialog::GetRivendellData()
{
   MYSQL_RES *result;
   MYSQL_ROW row;

   int i;
   int status;
   char *endPtr;
          
   wxString groupString = ((wxChoice*)FindWindow(ID_GROUP))->GetStringSelection();
   wxString sortString =  ((wxChoice*)FindWindow(ID_SORT))->GetStringSelection();
   wxString query;
   wxString sortby;
   wxString group_list;

   char holdString[400];
   char holdSortString[25];

  // AudacityProject::InitRivendellDatabase(mDb);
         
   // Building Order By clause
   if (sortString == (_("Cart Title")) )
         strcpy(holdSortString,"C2.TITLE");
   if (sortString == _("Cut Description") )
         strcpy(holdSortString,"C1.DESCRIPTION");
   if (sortString == _("Cart_Cut Number") )
         strcpy(holdSortString,"C1.CUT_NAME");
   if (curSortState == SORTREV) 
	     strcat(holdSortString," DESC");
   
   //FIXME: we want to delete the strings below as cleanup after we're done with them
   sortby = wxString(holdSortString,wxConvUTF8);

   // Building Group list
   if (groupString != _("ALL")) {
	   query.Printf(_("select C1.CART_NUMBER,C1.CUT_NAME,C1.DESCRIPTION,C2.TITLE from CUTS C1, CART C2 where C2.GROUP_NAME = \"%s\" AND C2.TYPE = 1 AND  C1.CART_NUMBER = C2.NUMBER  order by %s"), groupString.c_str(),sortby.c_str());
   }
   else {
      query.Printf(_("select GROUP_NAME from USER_PERMS where USER_NAME = \"%s\" ORDER BY GROUP_NAME "),
            riv_getuser(mDb).c_str() );
      mysql_query(mDb, query.mb_str());
      result = mysql_store_result(mDb);
      i = 0;
      strcpy (holdString,"IN (\'");
      while ((row = mysql_fetch_row(result)))
      {
         if (i != 0) strcat(holdString, "\', \'");     // Not First Group add ', at end
         strcat(holdString, row[0]);
         i++;
      }
      strcat (holdString," \')");                 // Add the quote parenthesis to end
      group_list = wxString(holdString,wxConvUTF8);
      mysql_free_result(result);

      query.Printf(_("select C1.CART_NUMBER,C1.CUT_NAME,C1.DESCRIPTION,C2.TITLE from CUTS C1, CART C2 where C2.GROUP_NAME %s AND C2.TYPE = 1 AND C1.CART_NUMBER = C2.NUMBER order by %s"),group_list.c_str(),sortby.c_str());
   }


   status = mysql_query(mDb, query.mb_str());
   if (status == 0)
   {
		result = mysql_store_result(mDb);
		while ((row = mysql_fetch_row(result))) {
			S_RivRec rec;
			rec.mCartNumber = strtol(row[0], &endPtr, 10);
			strncpy(rec.mCutName, row[1], 19);
			rec.mCutName[19] = 0x00;
			if (row[2]) {
				rec.mDescription = (char*)malloc(strlen(row[2])+1);
				strcpy(rec.mDescription, row[2]);
			} else {
				rec.mDescription = NULL;
			}
			if (row[3]) {
				rec.mTitle = (char*)malloc(strlen(row[3])+1);
				strcpy(rec.mTitle, row[3]);
			} else {
				rec.mTitle = NULL;
			}
         	mRecs.push_back(rec);
		}
		//FIXME: moved free result from here down
   }
   mysql_free_result(result);
}

void RivendellBrowseDialog::OnChoiceSort(wxCommandEvent & event)
{
   if (ClearRivendellData()){
      GetRivendellData();
      ((MyListCtrl*)FindWindow(ID_LISTCTRL))->DeleteAllItems();
      ((MyListCtrl*)FindWindow(ID_LISTCTRL))->SetItemCount(mRecs.size());
   }
}


void RivendellBrowseDialog::OnChoiceGroup(wxCommandEvent & event)
{
   if (ClearRivendellData()){
      GetRivendellData();
      ((MyListCtrl*)FindWindow(ID_LISTCTRL))->DeleteAllItems();
      ((MyListCtrl*)FindWindow(ID_LISTCTRL))->SetItemCount(mRecs.size());
   }
}

bool RivendellBrowseDialog::ClearRivendellData()
{
   //Check for mysql connection
   if (mysql_ping(mDb)) {
      wxMessageBox(_("Connection lost, please try again.\n If this persists contact Helpdesk"),
		           _("Rivendell mySQL"), wxICON_ERROR|wxOK);
      return false;
   }
   for (int i = 0; i < (int)mRecs.size(); i++)
   {
      if (mRecs[i].mDescription)
         free(mRecs[i].mDescription);
      if (mRecs[i].mTitle)
         free(mRecs[i].mTitle);
   }
   mRecs.clear();
   return true;
}


#ifdef _WIN32
char* strcasestr(const char *haystack, const char *needle)
{
   int hlen = strlen(haystack);
   int nlen = strlen(needle);

   while (hlen-- >= nlen) {
      if (!_strnicmp(haystack, needle, nlen))
         return (char*)haystack;
      haystack++;
   }
   return NULL;
}
#endif


void RivendellBrowseDialog::OnSearchText(wxCommandEvent & event)
{
    MyListCtrl *listCtrl = ((MyListCtrl*)FindWindow(ID_LISTCTRL));
    char srText[100];
    // This is not Unicode Complaint code!
	//strncpy(srText, ((wxTextCtrl*)FindWindow(ID_FILTER))->GetValue().mb_str(), 99);

	wxString hold_Filter = ((wxTextCtrl*)FindWindow(ID_FILTER))->GetValue().wx_str();
    strncpy(srText, WX2UNI(hold_Filter), 99);
    srText[99] = 0x00;
    wxString stringCartNum;

    for (int i = 0; i < (int)mRecs.size(); i++) 
	{
        stringCartNum = wxString::Format(wxT("%d"),mRecs[i].mCartNumber);
        if ((mRecs[i].mDescription && strcasestr(mRecs[i].mDescription, srText)) ||
            (mRecs[i].mTitle && strcasestr(mRecs[i].mTitle, srText)) ||
	 	   (mRecs[i].mCartNumber && strcasestr(stringCartNum.mb_str(),srText)) )
        {
           listCtrl->EnsureVisible(i);
           listCtrl->SetItemState(i, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
           return;
        } 
    } 
}


void RivendellBrowseDialog::OnNext(wxCommandEvent & event)
{
    MyListCtrl *listCtrl = ((MyListCtrl*)FindWindow(ID_LISTCTRL));

    char srText[100];
    // This is not Unicode Complaint code!
 	//strncpy(srText, ((wxTextCtrl*)FindWindow(ID_FILTER))->GetValue().mb_str(), 99);

	wxString hold_Filter = ((wxTextCtrl*)FindWindow(ID_FILTER))->GetValue().wx_str();
    strncpy(srText, WX2UNI(hold_Filter), 99);
    srText[99] = 0x00;
    wxString stringCartNum;

    for (int i = mLastSearchIdx; i < (int)mRecs.size(); i++) 
	{
	   stringCartNum = wxString::Format(wxT("%d"),mRecs[i].mCartNumber);
       if ((mRecs[i].mDescription && strcasestr(mRecs[i].mDescription, srText)) ||
           (mRecs[i].mTitle && strcasestr(mRecs[i].mTitle, srText)) ||
	 	  (mRecs[i].mCartNumber && strcasestr(stringCartNum.mb_str(),srText)) )
       {
          listCtrl->EnsureVisible(i);
          listCtrl->SetItemState(i, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
          mLastSearchIdx = i + 1;
          return;
       }
    }
    mLastSearchIdx = 0;
}


wxString MyListCtrl::OnGetItemText(long item, long column) const
{
   switch (column)
   {
   case 0: //title
      return wxString(mRecs[item].mTitle, wxConvUTF8);
   case 1: //description
      return wxString(mRecs[item].mDescription, wxConvUTF8);
   case 2: //name
      return wxString(mRecs[item].mCutName, wxConvUTF8);
   }
   return wxString(_(""));
}


wxString RivendellBrowseDialog::GetSelection(int field_code)
{
   int item = ((wxListCtrl*)FindWindow(ID_LISTCTRL))->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
   wxListItem     row_info;  
   wxString       cell_contents_string;

   row_info.m_itemId = item;
   row_info.m_col = field_code;
   row_info.m_mask = wxLIST_MASK_TEXT;
   ((wxListCtrl*)FindWindow(ID_LISTCTRL))->GetItem( row_info );

   return row_info.GetText();
}

void RivendellBrowseDialog::OnOK(wxCommandEvent & event)
{
   int item = ((wxListCtrl*)FindWindow(ID_LISTCTRL))->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
   if (item == -1) {
      EndModal(wxID_CANCEL);
      return;
   }

   EndModal(wxID_OK);
return;
}

void RivendellBrowseDialog::OnOKList(wxListEvent & event)
{
   int item = ((wxListCtrl*)FindWindow(ID_LISTCTRL))->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
   if (item == -1) {
      EndModal(wxID_CANCEL);
      return;
   }

   EndModal(wxID_OK);
}
void RivendellBrowseDialog::OnColClick(wxListEvent & event)
{
	int col = event.GetColumn();
    wxChoice *mChoiceOrder = ((wxChoice*)FindWindow(ID_SORT));
    if (ClearRivendellData()){	
	    if ((curSortState == NOCLICKS) && col != mChoiceOrder->GetCurrentSelection()) {  //different col always fwd first time
		    curSortState = SORTFRWD;
	    } else { 
		    if (curSortState == NOCLICKS) {                      // NO clicks but same column so reverse
			    curSortState = SORTREV;
		    } else {                                            
			    if (col != mChoiceOrder->GetCurrentSelection()) {  // new columns is always forward
				    curSortState = SORTFRWD;
				    } else {
					    if (curSortState == SORTFRWD) {
						    curSortState = SORTREV;
					    } else {
						    curSortState = SORTFRWD;
				    }
			    }
		    }
	    }
	    switch ( col )
	    {
		    case 0:
                mChoiceOrder->SetSelection(0);
			    break;
	    	case 1:
		    	mChoiceOrder->SetSelection(1);
				break;
			case 2:
				mChoiceOrder->SetSelection(2);
				break;
			default:
				return;
		}
   		GetRivendellData();
	   ((MyListCtrl*)FindWindow(ID_LISTCTRL))->DeleteAllItems();
	   ((MyListCtrl*)FindWindow(ID_LISTCTRL))->SetItemCount(mRecs.size());
	   mLastSearchIdx = 0;
    }
return;
}
				



// Indentation settings for Vim and Emacs and unique identifier for Arch, a
// version control system. Please do not modify past this point.
//
// Local Variables:
// c-basic-offset: 3
// indent-tabs-mode: nil
// End:
//
// vim: et sts=3 sw=3
// arch-tag: xxx
