/*=========================================================================

 Program: MAF2Medical
 Module: medWizardSelectionBlockImages
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
#include "medWizardBlockImagesSelection.h"

#include "mafTagArray.h"
#include "mafNode.h"
#include "medGUISelectionImagesDialog.h"


//----------------------------------------------------------------------------
medWizardBlockImagesSelection::medWizardBlockImagesSelection(const char *name):medWizardBlockSelection(name)
//----------------------------------------------------------------------------
{
  //setting default values
  m_SelectedChoice=0;
}

//----------------------------------------------------------------------------
medWizardBlockImagesSelection::~medWizardBlockImagesSelection()
//----------------------------------------------------------------------------
{

}

//----------------------------------------------------------------------------
void medWizardBlockImagesSelection::ExcutionBegin()
//----------------------------------------------------------------------------
{
  medWizardBlock::ExcutionBegin();

  //Generating required wxstring choice array
  wxString *choices = new wxString[m_Choices.size()];

  for(int i=0;i<m_Choices.size();i++)
    choices[i]=m_Choices[i].label;

  //Show Modal window
  medGUISelectionImagesDialog amsg(NULL, 5, wxID_ANY, _(m_Title.c_str()), "Select:");
  int w,h;
  mafGetFrame()->GetPosition(&w,&h);
  wxSize size = mafGetFrame()->GetSize();
  wxPoint defPos = wxDefaultPosition;
  wxSize defSize = wxDefaultSize;
  amsg.SetPosition(wxPoint(defPos.x, defPos.y));

  std::vector<wxString> tooltips;
  for(int i=0;i<m_Choices.size();i++) {
	  tooltips.push_back(m_Choices[i].label);
  }

  amsg.Initialize(m_ImageList, tooltips);
  
  
  m_SelectedChoice = amsg.ShowModal();

  //User has pessed cancel
  if (m_SelectedChoice<0)
    Abort();

  //free mem 
  delete[] choices;  
}
