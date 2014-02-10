/*=========================================================================
  Program:   Multimod Application Framework
  Module:    $RCSfile: medSelectionImagesDialog.h,v $
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

#include "medGuiDefines.h"
#include "mafGUIDialog.h"
#include <wx/imaglist.h>

class mafGUIPicButtons;

class MED_GUI_EXPORT medGUISelectionImagesDialog : public mafGUIDialog
{
public:
	enum {
        ID_SELECTION_BUTTON = 1000,
	};
	medGUISelectionImagesDialog(wxWindow* parent, int timeout, wxWindowID id, const wxString& title, const wxString& name = "dialogBox", const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE);
	~medGUISelectionImagesDialog();

	void Initialize(std::vector<wxString> &images, std::vector<wxString> &tooltips);
	
	/** 
  Virtual functions called to terminate ShowModal - these can be redefined without providing the Event Table. 
  called when a ShowModal stage end with ok - in general is called by an 'OK' button -- */
  virtual void OnCloseWindow(wxCloseEvent &event);
  /*virtual*/ virtual void OnEvent(mafEventBase *maf_event);

private:
	mafGUIPicButtons *m_SelectionButtons;

	unsigned short m_ButtonClicked;
};

#endif
