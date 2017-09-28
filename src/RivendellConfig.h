/**********************************************************************

  Rdacity: A Digital Audio Editor powered by Audacity(R)

  RivendellConfig.h

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

#ifdef _WIN32
#define strcasecmp stricmp
#endif

#ifndef RIVENDELLCONFIGH
#define RIVENDELLCONFIGH

//#define WINRIVCFG "C:\\Program Files\\SalemRadioLabs\\rivendell\\rd.ini"
#define WINRIVCFG "c:\\Program Files (x86)\\Audacity_RFA\\Portable Settings\\rd.ini"
#define POSIXRIVCFG "/etc/rdacity/rd.ini"
#ifdef _WIN32
#include <mysql.h>
#else
#include <mysql/mysql.h>
#endif
//
//WINRRIVCFG is overlaid with the executabledir\PortableSetting dir if possible..


class RivendellConfig
{
		char	*m_Data;
		int		m_Size;

		int		m_CartOpened,
					m_CutOpened;

		char*	FindSection(const char *_Section);
public:
		RivendellConfig(void);
		~RivendellConfig(void);
		
		bool	LoadConfig(char *_FileName);
		bool	ParseInt(const char *_Section, const char *_Name, int &_Val);
		bool	ParseString(const char *_Section, const char *_Name, char *_Str);
		
		int		GetCartOpened(void); 
		int		GetCutOpened(void); 
		
		void	SetCartOpened(int _Cart) { m_CartOpened = _Cart; };
		void	SetCutOpened(int _Cut) { m_CutOpened = _Cut; };
};

extern	RivendellConfig	*RivendellCfg;


/**
 * Utility method to retrieve the OS username.
 *
 * @return wxString with username.  Defaults to "user" on error.
 */
wxString riv_getuser();


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
