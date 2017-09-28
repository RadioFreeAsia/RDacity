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