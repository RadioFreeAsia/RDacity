/**********************************************************************

Rdacity: A Digital Audio Editor powered by Audacity(R)

RivendellUtils.h

This effort was sponsored work by Radio Free Asia
https://github.com/RadioFreeAsia/rdacity
Todd Baker  <bakert@rfa.org> <toadybarker@gmail.com>

(C) Copyright April 19, 2017 Todd Baker <bakert@rfa.org>

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

#ifndef RIVENDELLUTILSH
#define RIVENDELLUTILSH

#define RDACITY_VERSION "rdacity/2.1.2.20 (Windows-7) "

class RivendellUtils
{

public:
	RivendellUtils(void);
	~RivendellUtils(void);

	wxString Get_System_User();
	bool Validate_Ticket(const char rivhost[],
                    		const char chk_ticket[]);
	bool Get_Current_Ticket(char *returned_ticket);
	bool Rivendell_Login(wxWindow * caller,char *ticket[], const char rivUser[]);

};

extern	RivendellUtils	*RivUtils;

#endif     //End Of RIVENDELLUTILSH