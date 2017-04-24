/**********************************************************************
  Rdacity: A Digital Audio Editor powered by Audacity(R)

  RivendellBrowseDialog.h

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

#ifndef RIVENDELLBROWSEDIALOGH
#define RIVENDELLBROWSEDIALOGH

#include <wx/dialog.h>
#ifdef _WIN32
#include <mysql.h>
#else
#include <mysql/mysql.h>
#endif

#include <vector>

#define RD_BROWSE_CART_TITLE 0
#define RD_BROWSE_CUT_DESC 1
#define RD_BROWSE_CUT_NAME 2

struct S_RivRec
{
   char *mTitle;
   char *mDescription;
   char mCutName[20];
   int  mCartNumber;
};

enum sortState { NOCLICKS, SORTFRWD, SORTREV };

typedef  std::vector<S_RivRec> T_RivRecs;

class MyListCtrl: public wxListCtrl
{
public:
    MyListCtrl(wxWindow *parent,
               const wxWindowID id,
               const wxPoint& pos,
               const wxSize& size,
               long style, T_RivRecs &recs)
        : wxListCtrl(parent, id, pos, size, style),
          mRecs(recs)
        {
          mRecs = recs;
        };

private:
    virtual wxString OnGetItemText(long item, long column) const;
    
    T_RivRecs &mRecs;
};

class RivendellBrowseDialog:public wxDialog 
{
   DECLARE_DYNAMIC_CLASS(RivendellDialog)

public:
   RivendellBrowseDialog(wxWindow * parent, MYSQL *db);
   virtual ~RivendellBrowseDialog();

   void OnOK(wxCommandEvent & event);
   void OnOKList(wxListEvent & event);
   void OnChoiceGroup(wxCommandEvent & event);
   void OnChoiceSort(wxCommandEvent & event);
   void OnSearchText(wxCommandEvent & event);
   void OnNext(wxCommandEvent & event);
   void OnColClick(wxListEvent & event);
  
	/*
	 * Accessor method to retrieve the user selection from the browsedialog.
    *
    * @param field_code - int with a code for the field to retrieve. Currently
    *                     defines by constants:
    *                      #define RD_BROWSE_CART_TITLE 0
    *                      #define RD_BROWSE_CUT_DESC 1
    *                      #define RD_BROWSE_CUT_NAME 2
    *                     NOTE: these match up with the columns in the browse
    *                     dialog box wxListItem!
    *
    * @return wxString with the requested field.
    */
   wxString GetSelection(int field_code);

private:
   void GetRivendellData();
   bool ClearRivendellData();

   MYSQL     *mDb;
   T_RivRecs mRecs;
   int       mLastSearchIdx;
   sortState curSortState;
public:
   DECLARE_EVENT_TABLE()
};

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
