/**********************************************************************

  Rdacity: A Digital Audio Editor powered by Audacity(R)

  RivendellConfig.cpp

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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include <wx/filename.h>
#include <wx/msgdlg.h>
#include "PlatformCompatibility.h"

#include <mysql.h>


#ifndef _WIN32
#include <pwd.h>
#endif

#include "Project.h"

#include "RivendellConfig.h"

RivendellConfig	*RivendellCfg;


RivendellConfig::RivendellConfig(void)
{
	m_CartOpened = m_CutOpened = -1;
}

RivendellConfig::~RivendellConfig(void)
{

	if ((m_CartOpened != -1) && (m_CutOpened != -1)) 
	{
		free(m_Data);
	}
}

bool	RivendellConfig::LoadConfig(char *_FileName)
{
    //  We will attempt to get the exe path so we can find
    //  The Portable Settings directory relative to that.
    //  This used to be hard coded so if all else fails
    //  will use the hard coded path for source of rd.ini file.
    // This is Windows only - Linux uses /etc/rdacity/rd.ini
    //
	wxFileName exePath(PlatformCompatibility::GetExecutablePath());
	wxString   holdFilePath;
    #if defined(__WXMAC__)
    // This removes (for instance) "Audacity.app/Contents/MacOSX"
    exePath.RemoveLastDir();
    exePath.RemoveLastDir();
    exePath.RemoveLastDir();
    #endif
    wxFileName portablePrefsPath(exePath.GetPath(), wxT("Portable Settings"));
	
	FILE *f;
    #if !defined(__WXMSW__)
    //    Linux or Mac uses /etc/rdacity/rd.ini 
    //
        f = fopen(_FileName, "r");
        
        if (!f)
        {
           wxMessageBox(_("Unable to find rivendell configuration File\n rd.ini not in /etc/rdacity directory!"),
                        _("Rivendell Configuration"), wxICON_ERROR | wxOK);
                return false;
        }

    #else
    //   Windows uses executable directory / Portable Settings/rd.ini
    //
	if (wxDirExists(portablePrefsPath.GetFullPath()))
        {
        // Use "Portable Settings" folder
        holdFilePath = portablePrefsPath.GetFullPath();
		holdFilePath += _("\\rd.ini");
		f = fopen(holdFilePath.mb_str(wxConvUTF8),"r");
	}
	else
	{
		// No Longer using hard coded rd.ini use exe path!
		wxMessageBox(_("Unable to find Portable Settings Directory !"),
			_("Rivendell Configuration"), wxICON_ERROR | wxOK);
		return false;
	}
	if (!f)
	{
		wxMessageBox(_("Unable to find rivendell configuration \n./Portable Settings/rd.ini not in executable directory!"),
			_("Rivendell Configuration"), wxICON_ERROR | wxOK);
		return false;
	}
    #endif

    fseek(f, 0, SEEK_END);
    m_Size = ftell(f);
    m_Data = (char*)malloc(m_Size);
    fseek(f, 0, SEEK_SET);
    fread(m_Data, m_Size, 1, f);
    fclose(f);	
    return true;
}

char*	RivendellConfig::FindSection(const char *_Section)
{

	char *ptr = m_Data;
	char	section[51];
	
	while (ptr < m_Data + m_Size)
	{
		if (*ptr == '[')
		{
			if (sscanf(++ptr, "%[^]]\n", section) == 1 &&
					!strcasecmp(section, _Section))
			{
				while (*ptr++ != '\n');
				return ptr;
			}
		}
		
		while (*ptr++ != '\n');
	}
	
	return NULL;
}

bool	RivendellConfig::ParseInt(const char *_Section, const char *_Name, int &_Val)
{
	//toady
	//return true;
	
	char *ptr = m_Data;
	if (!(ptr = FindSection(_Section)))
		return false;
		
	char	var[50];
	while (ptr < m_Data + m_Size && *ptr != '[')
	{
		if (sscanf(ptr, "%[^=]s", var) == 1 && !strcasecmp(var, _Name))
		{
			while (*ptr++ != '=');
			return (sscanf(ptr, "%d\n", &_Val) == 1);
		}
		while (*ptr++ != '\n');
	}
	return false;
}

bool	RivendellConfig::ParseString(const char *_Section, const char *_Name, char *_Str)
{
	//toady 2
	//return true;

	char *ptr = m_Data;
	if (!(ptr = FindSection(_Section)))
		return false;
		
	char	var[256];
	while (ptr < m_Data + m_Size && *ptr != '[')
	{
		if (sscanf(ptr, "%[^=]s", var) == 1 && !strcasecmp(var, _Name))
		{
			while (*ptr++ != '=');   // empty loop to search for end of _Name
			sscanf(ptr, "%s\n", _Str);
			return true;
		}
		while (*ptr++ != '\n');
	}
	return false;
}

int		RivendellConfig::GetCartOpened(void) 
{ 
	int		cartId;
	int     cutId;
	int		rc;

	if (m_CartOpened == -1)
	{
		AudacityProject *p = GetActiveProject();
		rc = sscanf(p->GetName().mb_str(), "%d_%d", &cartId, &cutId);
		if (rc == 2)
		{
			m_CartOpened = cartId;
			// Populate the cut id if it was not already present.
			if (m_CutOpened == -1)
			{
				m_CutOpened = cutId;
			}
		}
	}
	return m_CartOpened; 
}

int		RivendellConfig::GetCutOpened(void) 
{ 
	int		cartId;
	int     cutId;
	int		rc;

	if (m_CutOpened == -1)
	{
		AudacityProject *p = GetActiveProject();
		rc = sscanf(p->GetName().mb_str(), "%d_%d", &cartId, &cutId);
		if (rc == 2)
		{
			m_CutOpened = cutId;
			// Populate the cart id if it was not already present.
			if (m_CartOpened == -1)
			{
				m_CartOpened = cartId;
			}
		}
	}
	return m_CutOpened; 
}

wxString	riv_getuser(MYSQL *db)
{
   const wxString default_username = _T("user"); // Initialize to default Rivendell userid "user", in case unable to get credentials.
   //const wxString default_username = _T("guest"); 
	  // Initialize to Rivendell userid "guest", in case unable to get credentials. If there is no such user in 
      // the Rivendell database, no files will be returned on browse; while an error dialog is presented on export
   //const wxString default_username = _T("user");   //Rivendell 2.0 testing toady
   wxString username = default_username;
   wxString query;
   MYSQL_RES *result;

   #ifdef _WIN32
   TCHAR tusername[255];
   DWORD tusername_bufsize = 255;
   bool rc;

   rc = (bool) GetUserName(tusername, &tusername_bufsize );
   if (rc) {
      //username = default_username;
      username = wxString(tusername, wxConvUTF8);
   }
#else /* not _WINDOWS */
   uid_t user_uid;
   struct passwd * user_passwd;

   user_uid = getuid();
   user_passwd = getpwuid(user_uid);
   if (user_passwd != NULL) {
      username = wxString(user_passwd->pw_name, wxConvUTF8);
   }
#endif /* not _WINDOWS */

   // Ensure the OS username is a valid Rivendell user.
   query.Printf(_T("select LOGIN_NAME from USERS where LOGIN_NAME=\"%s\""), username.c_str());
   // FIXME: should sterilize contents of riv_getusr() before sending to sql.
   mysql_query(db, query.mb_str());
   result = mysql_store_result(db);
   if (mysql_num_rows(result) != 1) {
      username = default_username;
   }
   mysql_free_result(result);

   return username;
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
