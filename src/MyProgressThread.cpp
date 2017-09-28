#include "wx/thread.h"
#include "wx/gauge.h"
#include "wx/frame.h"
#include "MyProgressThread.h"


/*   This process displasy a wait - processing window                 *
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
