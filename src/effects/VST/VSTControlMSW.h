/**********************************************************************

  Audacity: A Digital Audio Editor

  VSTControlMSW.h

  Leland Lucius

**********************************************************************/

#ifndef AUDACITY_VSTCONTROLMSW_H
#define AUDACITY_VSTCONTROLMSW_H

#include <Windows.h>

#include <wx/control.h>

#include "aeffectx.h"

class VSTControl : public VSTControlBase
{
public:
   VSTControl();
   ~VSTControl();

   bool Create(wxWindow *parent, VSTEffectLink *link);

private:
   HANDLE mHwnd;
};

#endif
