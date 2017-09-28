/**********************************************************************

Rdacity: A Digital Audio Editor powered by Audacity(R)

RivendellUtils.cpp

This effort was sponsored work by Radio Free Asia
https://github.com/RadioFreeAsia/rdacity

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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include <wx/filename.h>
#include <wx/msgdlg.h>

//toady added config stuff
#include <wx/config.h>
#include "PlatformCompatibility.h"


#ifndef _WIN32
#include <pwd.h>
#endif

#include "RivendellUtils.h"
#include "RivendellLoginDialog.h"
#include "rivendell/rd_audiostore.h"
#include "rivendell/rd_getversion.h"
#include "rivendell/rd_getuseragent.h"

RivendellUtils *RivUtils;

RivendellUtils::RivendellUtils(void)
{}

RivendellUtils::~RivendellUtils(void)
{}

wxString RivendellUtils::Get_System_User()
{
	// Initialize to default Rivendell userid "user", in case unable to get credentials.
	const wxString default_username = _T("user");
	wxString username = default_username;

#ifdef _WIN32
	TCHAR tusername[255];
	DWORD tusername_bufsize = 255;
	bool rc;

	rc = (bool)GetUserName(tusername, &tusername_bufsize);
	if (rc) username = wxString(tusername, wxConvUTF8);
#else /* not _WINDOWS */
	uid_t user_uid;
	struct passwd * user_passwd;

	user_uid = getuid();
	user_passwd = getpwuid(user_uid);
	if (user_passwd != NULL) 
		username = wxString(user_passwd->pw_name, wxConvUTF8);
#endif
	return username;

}



bool RivendellUtils::Validate_Ticket(const char rivhost[],
	const char chk_ticket[])
{
	int result;
	char user[] = "";
	char pass[] = "";
	struct rd_audiostore *audiosto;
	unsigned numrecs;

	// Set RDACITY_VERSION STRING
	char RDACITY_VERSION_STRING[255] = RDACITY_VERSION;
	//Add Rivendell C Library Info
	strcat(RDACITY_VERSION_STRING, RD_GetUserAgent());
	strcat(RDACITY_VERSION_STRING, RD_GetVersion());

	result = RD_AudioStore(&audiosto,
		rivhost,
		user,
		pass,
		chk_ticket,
		RDACITY_VERSION_STRING,
		&numrecs);
	if (result < 0) {
		wxMessageBox(_("Failure - Major Error during Web Call! Result Code < 0"),
			_("Rivendell Web API"), wxICON_ERROR | wxOK);
		return false;
	}

	if ((result < 200 || result > 299) &&
		(result != 0))
	{
		switch (result) {
		case 400:
			wxMessageBox(_("Failure - Internal Error!! AudioStore\n"),
				_("Rivendell Web API"), wxICON_ERROR | wxOK);
			return false;
		case 403:
			//wxMessageBox(_("Ticket Invalid/Expired - Authentification Required\n"));
			return false;
		default:
			wxMessageBox(_("Ticket Validation Failed. Unknown Error\n"),
				_("Rivendell Web API"), wxICON_ERROR | wxOK);
			return false;
		}
	}
	return true;
}

bool RivendellUtils::Get_Current_Ticket(char *returned_ticket)
{
	wxString current_tkt;
	wxString cur_tkt_exp;
	wxString newticket;
	wxString message;
	wxConfig config(wxT("Rivendell"), wxT("Radio Free Asia"));

	//toady testing
	//config.DeleteAll();
	if (config.Read(wxT("TicketString"), &current_tkt))
	{
		// Set DEBUG_TKT to 1 for debugging
#ifdef  DEBUG_TKT  
		message.Printf(_T("Ticket found : %s \n"), current_tkt.c_str());
		wxMessageBox(_(message), _("Rivendell"), wxICON_ERROR | wxOK);
#endif
		strcpy(returned_ticket, current_tkt.c_str());
		return true;
	}
	return false;    //No Ticket Exists
}

bool RivendellUtils::Rivendell_Login(wxWindow *caller,char *rivTicket[], const char rivUser[])
{
	wxConfig config(wxT("Rivendell"), wxT("Radio Free Asia"));

	rd_ticketinfo cur_tkt_info = { 0 };
	RivendellLoginDialog login(caller, rivUser);

	if (login.ShowModal() == wxID_OK)
	{
		cur_tkt_info = login.GetTicket();
		strcpy(rivTicket[0], cur_tkt_info.ticket);
		wxString ticket;
		ticket = wxString(rivTicket[0], wxConvUTF8);
		config.Write(wxT("TicketString"), ticket);
		return true;
	}
	else
	{
		wxMessageBox(_(" Login Was Unsuccessful"), ("Rivendell"), wxICON_ERROR | wxOK);
		strcpy(rivTicket[0], "");
		return false;
	}
}
