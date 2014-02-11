/*=========================================================================

 Program: MAF2Medical
 Module: medWizardSelectionBlock
 Authors: Gianluigi Crimi
 
 Copyright (c) B3C
 All rights reserved. See Copyright.txt or
 http://www.scsitaly.com/Copyright.htm for details.

 This software is distributed WITHOUT ANY WARRANTY; without even
 the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "medDefines.h" 
//----------------------------------------------------------------------------
// NOTE: Every CPP file in the MAF must include "mafDefines.h" as first.
// This force to include Window,wxWidgets and VTK exactly in this order.
// Failing in doing this will result in a run-time error saying:
// "Failure#0: The value of ESP was not properly saved across a function call"
//----------------------------------------------------------------------------

#include "medDecl.h"
#include "medWizardBlockInformation.h"
#include "mafGUIDialog.h"
#include "mafGUI.h"
#include <wx/image.h>
#include <wx/statline.h>
#include "mafGUIPicButton.h"
#include "mafGUIPicButtons.h"



#define max(a,b)  (((a) > (b)) ? (a) : (b))



//----------------------------------------------------------------------------
medWizardBlockInformation::medWizardBlockInformation(const char *name):medWizardBlock(name)
//----------------------------------------------------------------------------
{
  //setting image on top by default
  m_HorizontalImage=true;
  m_ImagesPath=(mafGetApplicationDirectory() + "\\WizardImages\\").c_str();
  m_ButtonInfoType = BUTTON_CLASSIC;
  m_Dialog = NULL;
}

//----------------------------------------------------------------------------
medWizardBlockInformation::~medWizardBlockInformation()
//----------------------------------------------------------------------------
{
}

//----------------------------------------------------------------------------
void medWizardBlockInformation::SetWindowTitle( const char *Title )
//----------------------------------------------------------------------------
{
  //setting the name of the window title
  m_Title=Title;
}


//----------------------------------------------------------------------------
void medWizardBlockInformation::SetDescription( const char *description )
//----------------------------------------------------------------------------
{
  //set the description showed to the user
  m_Description=description;
}



//----------------------------------------------------------------------------
void medWizardBlockInformation::ExcutionBegin()
//----------------------------------------------------------------------------
{
  medWizardBlock::ExcutionBegin();

  //Create event for communication
  mafEvent e=mafEvent(this,WIZARD_INFORMATION_BOX_SHOW_GET);

  //Ask upward to the wizard manager if information box shows is enabled
  mafEventMacro(e);

  //read value
  m_ShowBoxes=e.GetBool();
 
  //Show information box only if is enabled in options
  if (m_ShowBoxes)
  {
    medWizardBlock::ExcutionBegin();
    mafGUIPicButton *previewImageButton;

    wxBoxSizer *mainVertSizer = new wxBoxSizer(wxVERTICAL);
    m_Dialog = new mafGUIDialog(m_Title,mafRESIZABLE);
    wxBoxSizer * mainInfoSizer;
  
    //Setting the frames order base
    if (m_HorizontalImage)
      mainInfoSizer = new wxBoxSizer(wxVERTICAL);
    else
      mainInfoSizer = new wxBoxSizer(wxHORIZONTAL);
  
    //check if there is an image to show
    if (m_ImageFilename != "")
    {
      wxImage *previewImage;
      wxBitmap *previewBitmap;
    
      //load and show the image
      previewImage=new wxImage();
      wxString imgPath=m_ImagesPath;
      imgPath=imgPath+m_ImageFilename;
      previewImage->LoadFile(imgPath.c_str(), wxBITMAP_TYPE_ANY );

      previewBitmap=new wxBitmap(*previewImage);
      previewImageButton=new mafGUIPicButton(m_Dialog,previewBitmap,-1);
      mainInfoSizer->Add(previewImageButton, 0,wxALL | wxALIGN_CENTER, 5);
      delete previewBitmap;
    }
  
  
    //Creating the static text area
    wxStaticText* guiLabel = new wxStaticText(m_Dialog, -1, m_Description,wxPoint(-1,-1),wxSize(-1,-1),wxALIGN_LEFT);
    wxFont fixedFont= guiLabel->GetFont();

    //setting font to fixed size to avoid wx non-sense 
    fixedFont.SetFamily(wxFONTFAMILY_MODERN);
    fixedFont.SetFaceName("Courier");
    guiLabel->SetFont(fixedFont);
    
    const char *charPointer=m_Description.c_str();
    int xsize=0,ysize=0,currentX;
    int x,y;
  

    x=guiLabel->GetCharWidth()-1;
    y=guiLabel->GetCharHeight();
    
    //Calculating space required by text area
    while (*charPointer!='\0')
    {
      currentX=0;
      while (*charPointer!='\n' && *charPointer!='\0')
      {
        charPointer++;
        currentX+=x;
      }
      xsize=max(xsize,currentX);
      ysize+=y;
      charPointer++;
    }

    //setting the min size for the area
    guiLabel->SetMinSize(wxSize(xsize,ysize));

  
    //merging sizers into m_Dialog
    wxStaticBoxSizer * modelSizer = new wxStaticBoxSizer(wxVERTICAL,m_Dialog,m_BoxLabel);
    modelSizer->Add(guiLabel,0,wxALL|wxEXPAND,5);
    mainInfoSizer->Add(modelSizer,0,wxALL|wxEXPAND,5);
  
    mainVertSizer->Add(mainInfoSizer,0,wxTOP|wxLEFT|wxRIGHT|wxEXPAND, 15);
    
    
    mainVertSizer->Add(new wxStaticLine(m_Dialog,-1),0,wxEXPAND | wxALL, 7);
    

    wxBoxSizer *buttonSizer =  new wxBoxSizer( wxHORIZONTAL );

    //Creating button stuff to disable information box 
    //and ok button
    mafGUI *checkGUI=new mafGUI(this);
    checkGUI->Bool(WIZARD_INFO_SHOW_ID,"Show information boxes",&m_ShowBoxes,true);
	checkGUI->Enable(WIZARD_INFO_SHOW_ID, false);
    checkGUI->Reparent(m_Dialog);
    

	wxWindow *okButton = NULL;
	if(m_ButtonInfoType == BUTTON_CLASSIC) {
        okButton = new wxButton(m_Dialog,wxID_OK,"Ok");
	} else if(m_ButtonInfoType == BUTTON_IMAGE) {
		okButton = new mafGUIPicButtons(m_Dialog, wxID_OK, 1, 1);
		((mafGUIPicButtons*)okButton)->SetListener(this);
		std::vector<wxString> picturesInteractor;
		picturesInteractor.push_back("OK_OPERATION");
		((mafGUIPicButtons*)okButton)->SetPictureVector(picturesInteractor);
		((mafGUIPicButtons*)okButton)->Create();
        ((mafGUIPicButtons*)okButton)->SetToolTip(0, _("Ok"));
	}
    
	buttonSizer->Add(checkGUI,0,wxLEFT,5);
	buttonSizer->AddStretchSpacer(1);
	buttonSizer->AddStretchSpacer(1);
	buttonSizer->Add(okButton,1,wxLEFT,5);
	buttonSizer->AddStretchSpacer(2);
	buttonSizer->AddStretchSpacer(2);
    

    mainVertSizer->Add(buttonSizer,0,wxEXPAND,5);
    m_Dialog->Add(mainVertSizer,0,wxEXPAND);
	
	m_Dialog->Fit();
    //show m_Dialog
	wxSize s = mafGetFrame()->GetSize();
	wxPoint p = mafGetFrame()->GetPosition();
	int posX = p.x + s.GetWidth() * .5 - m_Dialog->GetSize().GetWidth() * .5 ;
	int posY = p.y + s.GetHeight() * .5 - m_Dialog->GetSize().GetHeight() * .5;
	m_Dialog->SetPosition(wxPoint(posX, posY));
    m_Dialog->ShowModal();
  }
}

//----------------------------------------------------------------------------
void medWizardBlockInformation::SetImage( const char *imageFilename )
//----------------------------------------------------------------------------
{
  //
  m_ImageFilename=imageFilename;
}


//----------------------------------------------------------------------------
void medWizardBlockInformation::SetBoxLabel( const char *label )
//----------------------------------------------------------------------------
{
  //Set the label of the box
  m_BoxLabel=label;
}

//----------------------------------------------------------------------------
void medWizardBlockInformation::SetImagePositionToTop()
//----------------------------------------------------------------------------
{
  m_HorizontalImage=true;
}

//----------------------------------------------------------------------------
void medWizardBlockInformation::SetImagePositionToLeft()
//----------------------------------------------------------------------------
{
  m_HorizontalImage=false;
}


//----------------------------------------------------------------------------
void medWizardBlockInformation::OnEvent( mafEventBase *maf_event )
//----------------------------------------------------------------------------
{
  if (mafEvent *e = mafEvent::SafeDownCast(maf_event))
  {
    switch(e->GetId())
    {
    case WIZARD_INFO_SHOW_ID:
      {
        //Forward up event to update persistent settings
        mafEventMacro(mafEvent(this,WIZARD_INFORMATION_BOX_SHOW_SET,(bool)m_ShowBoxes));
      }
      break;
	case wxID_OK:
		if(m_Dialog) {
			m_Dialog->Close();
		}
		break;
    default:
      //All event will be forwarded up
      mafEventMacro(*e);
      break;
    } // end switch case
  }
}


