/**********************************************************************
  Rdacity: A Digital Audio Editor powered by Audacity(R)

  MyProgressThread.h

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

#ifndef MYPROGRESSTHREAD_H
#define MYPROGRESSTHREAD_H
#include "wx/thread.h"

class MyProgressThread : public wxThread
{

public:
	MyProgressThread();
	virtual ~MyProgressThread();
	virtual void *Entry();

}; 

#endif