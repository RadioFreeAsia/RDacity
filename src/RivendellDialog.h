/**********************************************************************
  Rdacity: A Digital Audio Editor powered by Audacity(R)

  RivendellDialog.h

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

#ifndef RIVENDELLDIALOGH
#define RIVENDELLDIALOGH

#include <wx/dialog.h>
#ifdef _WIN32
#include <mysql.h>
#else
#include <mysql/mysql.h>
#endif

#include "Track.h"

#define wxID_LENGTH                     1000
#define wxID_ORIGIN                     1001
#define wxID_TITLE                      1002
#define wxID_STARTDATE                  1003
#define wxID_ENDDATE                    1004
#define wxID_YEAR                       1005
#define wxID_ARTIST                     1006
#define wxID_ALBUM                      1007
#define wxID_LABEL                      1008
#define wxID_CLIENT                     1009
#define wxID_AGENCY                     1010
#define wxID_DESCRIPTION                1011
#define wxID_CARTNUMBER                 1012
#define wxID_CUTNUMBER                  1013
#define wxID_GROUP                      1014
#define wxID_BROWSE                     1015
// definitions for radiobox control
#define DATEENABLED_ON			0
#define DATEENABLED_OFF			1
#define wxID_CLEAR			1017
#define wxID_EVERGREEN                  1018

class wxTextCtrl;
class wxChoice;
class wxRadioBox; //FIXME, is this needed?

class RivendellDialog:public wxDialog 
{
    DECLARE_DYNAMIC_CLASS(RivendellDialog)

public:
    RivendellDialog(wxWindow * parent, MYSQL *db, bool saveSelection);
    virtual ~RivendellDialog();
   
    void OnBrowse(wxCommandEvent & event);
    void OnOK(wxCommandEvent & event);
    void OnChoiceGroup(wxCommandEvent & event);
    void OnChange(wxCommandEvent & event);
    void OnCartNumberChange(wxCommandEvent & event);
    void OnEvergreenChange(wxCommandEvent & event);
    void OnClear(wxCommandEvent & event);
    void PopulateDialog(int cartId=-1, int cutId=-1);
    bool Chk_Ascii(const char * chk_string);
    void Export_Failure( const char *cutname, const wxString msg);
	bool Get_Rivendell_1_Parameters(int * format, int * channel,	int * samplerate);
	bool Get_Rivendell_2_Parameters(int * format, int * channel,
	    	int * samplerate, const char rivHost[],	const char rivticket[]);
    bool Chk_Title(char * Title);
    bool Chk_Label(char * Label);
    bool Chk_Album(char * Album);
    bool Chk_Artist(char * Artist);
    bool Chk_Client( char * Client);
    bool Chk_Agency( char * Agency);
    bool Chk_Description( char * Description);
    bool Compute_Length(double * length);
    void Process_Riv_2(wxString groupString);
    bool Check_Start_End_Date( wxString * sdate, wxString * edate);
    void Set_Year(wxString * year);
    bool Verify_Update( unsigned long  cartnum, unsigned long * cutnum,
		const char host[], const char user[],
		const char passwd[], const char rivticket[]);

private:   
    wxChoice        *mChoiceGroup;
    MYSQL           *mDb;
    bool            mSaveSelection;
  
public:
    DECLARE_EVENT_TABLE()
};

#endif


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
