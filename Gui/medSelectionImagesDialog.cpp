/*=========================================================================
  Program:   Multimod Application Framework
  Module:    $RCSfile: medGUISelectionImagesDialog.cpp,v $
  Language:  C++
  Date:      $Date: 2009-05-14 12:27:49 $
  Version:   $Revision: 1.4.2.2 $
  Authors:   Daniele Giunchi
==========================================================================
  Copyright (c) 2002/2004
  CINECA - Interuniversity Consortium (www.cineca.it) 
=========================================================================*/

//----------------------------------------------------------------------------
// NOTE: Every CPP file in the MAF must include "mafDefines.h" as first.
// This force to include Window,wxWidgets and VTK exactly in this order.
// Failing in doing this will result in a run-time error saying:
// "Failure#0: The value of ESP was not properly saved across a function call"
//----------------------------------------------------------------------------

#include "medGUISelectionImagesDialog.h"
#include "breDefines.h"
#include "breGUIListCtrl.h"
#include "breGUIDictionaryWidget.h"
#include "mafGUIButton.h"
#include "mafGUIValidator.h"
enum DIALOG_BUTTONS {
	ID_SELECT_BUTTON,
};
//----------------------------------------------------------------------------
// Event Table:
//----------------------------------------------------------------------------
BEGIN_EVENT_TABLE(medGUISelectionImagesDialog, mafGUIDialog)
  EVT_BUTTON(ID_SELECT_BUTTON, medGUISelectionImagesDialog::nvOnSelect)

END_EVENT_TABLE()



//----------------------------------------------------------------------------
medGUISelectionImagesDialog::medGUISelectionImagesDialog( wxWindow* parent, int timeout, wxWindowID id, const wxString& title, const wxString& name, const wxPoint& pos, const wxSize& size, long style)
	: mafGUIDialog("Select User Mode", mafCLOSEWINDOW)
//----------------------------------------------------------------------------
{
	m_List = new breGUIListCtrl(this,id,false,true);
}
//----------------------------------------------------------------------------
medGUISelectionImagesDialog::~medGUISelectionImagesDialog()
	//----------------------------------------------------------------------------
{

}
//----------------------------------------------------------------------------
void medGUISelectionImagesDialog::Initialize()
//----------------------------------------------------------------------------
{
	wxString imagesPath;
#ifdef _DEBUG
	imagesPath = BRESEIGHTAPP_DATA_DIR;
	imagesPath.Append("/");
#else
	imagesPath = (mafGetApplicationDirectory() + "\\data\\wizards\\images\\").c_str();
#endif
	wxStaticBitmap *selectMode = new wxStaticBitmap(this, -1, wxBitmap(imagesPath + "HeaderSelection.bmp", wxBITMAP_TYPE_BMP));

	std::vector<wxString> columnNames;
	columnNames.push_back("Options");

	m_List->SetListener(this);
	m_List->SetSize(wxSize(300,300));
	m_List->Reset(); // clear columns
	m_List->InitializeColumns(columnNames,300);
	

	mafGUIButton  *close =    new mafGUIButton(this, ID_SELECT_BUTTON , "Next", wxDefaultPosition ,wxSize(80,20));
	close->SetValidator(mafGUIValidator(this,ID_SELECT_BUTTON,close));

	wxBoxSizer *h_sizer1 =  new wxBoxSizer( wxHORIZONTAL );
	h_sizer1->Add(selectMode,     1,wxEXPAND | wxALL,5);

	wxBoxSizer *h_sizer2 =  new wxBoxSizer( wxHORIZONTAL );
	h_sizer2->Add(m_List,     2, wxEXPAND | wxALL,5);


	wxBoxSizer *h_sizer3 =  new wxBoxSizer( wxHORIZONTAL );
	h_sizer3->Add(close,     1, wxCENTER,5);
	// 	h_sizer2->Add(noWizard,     0,wxEXPAND | wxALL,5);

	wxBoxSizer *v_sizer =  new wxBoxSizer( wxVERTICAL );
	v_sizer->Add(h_sizer1,     1,wxEXPAND | wxALL,5);
	v_sizer->Add(h_sizer2,     3,wxEXPAND | wxALL,5);
	v_sizer->Add(h_sizer3,     1,wxEXPAND | wxALL,5);

	this->Add(v_sizer, 1, wxEXPAND);


	this->Fit();
	this->FitInside();
}
//----------------------------------------------------------------------------
void medGUISelectionImagesDialog::RegisterAllImages(const std::vector<wxString> &images)
//----------------------------------------------------------------------------
{
	for (int i = 0; i < images.size(); ++i) {
		m_List->AddImage(images[i]);
	}
}
//----------------------------------------------------------------------------
void medGUISelectionImagesDialog::AddEntry(wxString entry, int iconIndex)
//----------------------------------------------------------------------------
{
	bool result = m_List->AddItem(m_List->GetNumberOfItems(), entry);
	m_List->SelectItem(m_List->GetSelectedItem()==-1?0:m_List->GetSelectedItem() );
	m_List->SetItemIcon(m_List->GetNumberOfItems() - 1, (ITEM_ICONS)iconIndex);
}

//----------------------------------------------------------------------------
void medGUISelectionImagesDialog::OnSelect(wxCommandEvent &event)
//----------------------------------------------------------------------------
{
	TransferDataFromWindow();
	SetReturnCode(m_List->GetSelectedItem());  
	Show(false);
}

//----------------------------------------------------------------------------
void medGUISelectionImagesDialog::OnCloseWindow(wxCloseEvent &event)
	//----------------------------------------------------------------------------
{
	// --- note about wxDialog::OnCloseWindow

	// We'll send a Cancel message by default, which may close the dialog.
	// Check for looping if the Cancel event handler calls Close().

	// Note that if a cancel button and handler aren't present in the dialog,
	// nothing will happen when you close the dialog via the window manager, or
	// via Close(). We wouldn't want to destroy the dialog by default, since
	// the dialog may have been created on the stack. However, this does mean
	// that calling dialog->Close() won't delete the dialog unless the handler
	// for wxID_CANCEL does so. So use Destroy() if you want to be sure to
	// destroy the dialog. The default OnCancel (above) simply ends a modal
	// dialog, and hides a modeless dialog.

	//SIL. 20-4-2005: 
	//So, in normal windows the close buttons destroy the window (Close -> CloseWindow -> Destroy )
	//in dialogs the close button calls Show(false) and don't call Destroy by default.
	//This is reasonable, because the user can call dlg.Show again.

	//So, The close button should call Cancel
	//Cancel should not destroy the window - just hide it
	//To know when the window is destroyed - override Destroy.
	TransferDataFromWindow();
	SetReturnCode(m_List->GetSelectedItem());  
	Show(false);
}