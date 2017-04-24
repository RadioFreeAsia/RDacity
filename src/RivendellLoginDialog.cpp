/**********************************************************************

  Audacity: A Digital Audio Editor

  RivendellLoginDialog.cpp

  This work is for the RDACITY version of Audacity
  
      This module will use the login credentials to call
	  the CreateTicket function in Rivendell C API.

  Todd Baker  <bakert@rfa.org> 
  
**********************************************************************/

#include <wx/dialog.h>
#include <wx/button.h>
#include <wx/string.h>

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "RivendellConfig.h"

#include "RivendellLoginDialog.h"
#include "rivendell/rd_createticket.h"




BEGIN_EVENT_TABLE(RivendellLoginDialog, wxDialog)
EVT_BUTTON(wxID_EXIT, RivendellLoginDialog::OnQuit)
EVT_BUTTON(BUTTON_Login, RivendellLoginDialog::OnLogin)
END_EVENT_TABLE()


IMPLEMENT_CLASS(RivendellLoginDialog, wxDialog)


RivendellLoginDialog::RivendellLoginDialog(wxWindow * parent,const char rivUser[])
: wxDialog(parent,-1, _("Rivendell Login"),
wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxWANTS_CHARS | wxRESIZE_BORDER)
{
	wxPanel *panel = new wxPanel(this, wxID_ANY);

	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer *hbox1 = new wxBoxSizer(wxHORIZONTAL);
	m_usernameLabel = new wxStaticText(panel, wxID_ANY, wxT("Username: "), wxDefaultPosition, wxSize(70, -1));
	hbox1->Add(m_usernameLabel, 0);

	m_usernameEntry = new wxTextCtrl(panel, wxID_USERNAME);
	((wxTextCtrl*)FindWindow(wxID_USERNAME))->SetValue(wxString(rivUser, wxConvUTF8));
	((wxTextCtrl*)FindWindow(wxID_USERNAME))->Enable(false);
	hbox1->Add(m_usernameEntry, 1);
	vbox->Add(hbox1, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
	
	wxBoxSizer *hbox2 = new wxBoxSizer(wxHORIZONTAL);
	m_passwordLabel = new wxStaticText(panel, wxID_ANY, wxT("Password: "), wxDefaultPosition, wxSize(70, -1));
	hbox2->Add(m_passwordLabel, 0);

	m_passwordEntry = new wxTextCtrl(panel, wxID_PASSWORD, wxString(""),
		wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
	hbox2->Add(m_passwordEntry, 1);
	vbox->Add(hbox2, 0, wxEXPAND | wxLEFT | wxTOP | wxRIGHT, 10);

	wxBoxSizer *hbox3 = new wxBoxSizer(wxHORIZONTAL);
	m_buttonLogin = new wxButton(panel, BUTTON_Login, wxT("Login"));
	m_buttonLogin->SetDefault();
	hbox3->Add(m_buttonLogin);

	m_buttonQuit = new wxButton(panel, wxID_EXIT, ("Quit"));
	hbox3->Add(m_buttonQuit);
	vbox->Add(hbox3, 0, wxALIGN_RIGHT | wxTOP | wxRIGHT | wxBOTTOM, 10);

	panel->SetSizer(vbox);
	Centre();
}

RivendellLoginDialog::~RivendellLoginDialog() 
{
}

void RivendellLoginDialog::OnQuit(wxCommandEvent& event)
{
	EndModal(wxID_CANCEL);
	return;
}

void RivendellLoginDialog::OnLogin(wxCommandEvent& event)
{
	wxString username = m_usernameEntry->GetValue();
	wxString password = m_passwordEntry->GetValue();
	char rivHost[255];     //The Rivendell Host - Web API Call will user
	unsigned numrecs;
	int result;

	if (!RivendellCfg->ParseString("RivendellWebHost", "Rivhost", rivHost))
	{
		wxMessageBox(wxT("The RDLogin FAILED !Incorrect RivHost Configuration !"), wxT("Error"), wxICON_WARNING);
		EndModal(wxID_CANCEL);
		return;
	}

	if (username.empty() || password.empty()) {
		wxMessageBox(wxT("Password cannot be Empty!"), wxT("Warning!"), wxICON_WARNING);
		return;
	}
	else 
	{
		result = RD_CreateTicket(&created_ticket_info,
			rivHost,
			username.c_str(),
			password.c_str(),
			&numrecs);

		if (result == 0)
		{
			EndModal(wxID_OK);
			return;
		}
		else
		{
			if (result == 403)
			{
				wxMessageBox(wxT(" Login Authentification Failed!"), wxT("Warning!"), wxICON_WARNING);
				((wxTextCtrl*)FindWindow(wxID_PASSWORD))->Clear();
				return;
			}
		}
	}
}


struct rd_ticketinfo  RivendellLoginDialog::GetTicket()
{
	return *created_ticket_info;

}
