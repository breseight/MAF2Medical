/*=========================================================================
  Program:   Multimod Application Framework
  Module:    $RCSfile: medGUISelectionImagesDialog.h,v $
  Language:  C++
  Date:      $Date: 2009-10-29 15:15:00 $
  Version:   $Revision: 1.4.2.2 $
  Authors:   Daniele Giunchi
==========================================================================
  Copyright (c) 2002/2004
  CINECA - Interuniversity Consortium (www.cineca.it) 
=========================================================================*/

#ifndef __medGUISelectionImagesDialog_H__
#define __medGUISelectionImagesDialog_H__

#include "mafGUIDialog.h"
#include <wx/imaglist.h>
class breGUIListCtrl;

class medGUISelectionImagesDialog : public mafGUIDialog
{
public:
	medGUISelectionImagesDialog(wxWindow* parent, int timeout, wxWindowID id, const wxString& title, const wxString& name = "dialogBox", const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE);
	~medGUISelectionImagesDialog();

	void Initialize();
	void RegisterAllImages(const std::vector<wxString> &images);
	void AddEntry(wxString entry, int iconIndex);

	/** 
  Virtual functions called to terminate ShowModal - these can be redefined without providing the Event Table. 
  called when a ShowModal stage end with ok - in general is called by an 'OK' button -- */
  virtual void OnSelect(wxCommandEvent &event);
  virtual void OnCloseWindow(wxCloseEvent &event);

private:
      
      

	  void nvOnSelect(wxCommandEvent &event)        {OnSelect(event);};  
	  breGUIListCtrl *m_List;
	  DECLARE_EVENT_TABLE()
};

#endif
