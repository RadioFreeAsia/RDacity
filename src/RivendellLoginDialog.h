/**********************************************************************
  Rdacity: A Digital Audio Editor powered by Audacity(R)

  RivendellLoginDialog.h

  This effort was sponsored work by Radio Free Asia   
	https://github.com/RadioFreeAsia/rdacity
  
  Todd Baker  <bakert@rfa.org> <toadybarker@gmail.com>

  (C) Copyright April 17, 2017 Todd Baker <bakert@rfa.org>

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

#ifndef RIVENDELLLOGINDIALOGH
#define RIVENDELLLOGINDIALOGH

#include <wx/wx.h>
#include <rivendell\rd_createticket.h>

#define wxID_USERNAME                     1001
#define wxID_PASSWORD                     1002

class RivendellLoginDialog:public wxDialog
{
	DECLARE_DYNAMIC_CLASS(RivendellLoginDialog)

public:
	RivendellLoginDialog(wxWindow *parent, const char rivUser[]);
	// Destructor
	virtual ~RivendellLoginDialog();
	struct rd_ticketinfo GetTicket();


private:
	wxStaticText* m_usernameLabel;
	wxStaticText* m_passwordLabel;
	wxTextCtrl* m_usernameEntry;
	wxTextCtrl* m_passwordEntry;
	wxButton* m_buttonLogin;
	wxButton* m_buttonQuit;
	wxMessageDialog *dlg;
	struct rd_ticketinfo *created_ticket_info=0;


private:
	void OnQuit(wxCommandEvent& event);
	void OnLogin(wxCommandEvent& event);
private:
	DECLARE_EVENT_TABLE()

	enum
	{
		BUTTON_Login = wxID_HIGHEST + 1
	};
};


#endif
