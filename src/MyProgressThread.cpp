/**********************************************************************
  Rdacity: A Digital Audio Editor powered by Audacity(R)

  MyProgressThread.cpp

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

#include "wx/thread.h"
#include "wx/gauge.h"
#include "wx/frame.h"
#include "MyProgressThread.h"


/*   This process displays a wait - processing window                 *
 *    The window is killed by the calling process when the caller     *
 *    is finished doing the processing. We do this for Rivendell      *
 *    Imports and Exports so User knows that it's still busy.         */

MyProgressThread::MyProgressThread() : wxThread(wxTHREAD_JOINABLE)
{
	if (wxTHREAD_NO_ERROR == Create()) {
		Run();
	}
}

MyProgressThread::~MyProgressThread()
{
}

wxThread::ExitCode MyProgressThread::Entry()
{
	wxFrame* frame = new wxFrame(NULL, wxID_ANY, _("Rivendell Transfering File - Please Wait"));
	frame->CenterOnParent();
	frame->Show(true);
	wxGauge * myGauge = new wxGauge(frame, wxID_ANY, 300, wxDefaultPosition, wxDefaultSize, wxGAUGE_EMULATE_INDETERMINATE_MODE);
	myGauge->CenterOnParent();
	
	myGauge->Pulse();
		// do something here that takes a long time
		// it's a good idea to periodically check TestDestroy()
	while (!TestDestroy()) {
		wxMilliSleep(10);
		myGauge->Pulse();
	}
	delete myGauge;
	delete frame;

	return static_cast<ExitCode>(NULL);
}
