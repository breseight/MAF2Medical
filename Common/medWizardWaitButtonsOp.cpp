/*=========================================================================

 Program: MAF2Medical
 Module: medWizardWaitButtonsOp
 Authors: Gianluigi Crimi
 
 Copyright (c) B3C
 All rights reserved. See Copyright.txt or
 http://www.scsitaly.com/Copyright.htm for details.

 This software is distributed WITHOUT ANY WARRANTY; without even
 the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "mafDefines.h" 
//----------------------------------------------------------------------------
// NOTE: Every CPP file in the MAF must include "mafDefines.h" as first.
// This force to include Window,wxWidgets and VTK exactly in this order.
// Failing in doing this will result in a run-time error saying:
// "Failure#0: The value of ESP was not properly saved across a function call"
//----------------------------------------------------------------------------


#include "medWizardWaitButtonsOp.h"
#include "mafDecl.h"
#include "mafEvent.h"
#include "mafEvent.h"
#include "mafGUI.h"
#include "mafGUIPicButtons.h" 


//----------------------------------------------------------------------------
// Constants :
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
mafCxxTypeMacro(medWizardWaitButtonsOp);
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
medWizardWaitButtonsOp::medWizardWaitButtonsOp(const wxString &label) :
mafOp(label)
//----------------------------------------------------------------------------
{
  m_OpType	= OPTYPE_OP;
  m_Canundo = true;
  m_OkCancelButtons = NULL;
}
//----------------------------------------------------------------------------
medWizardWaitButtonsOp::~medWizardWaitButtonsOp( ) 
//----------------------------------------------------------------------------
{
}
//----------------------------------------------------------------------------
mafOp* medWizardWaitButtonsOp::Copy()   
//----------------------------------------------------------------------------
{
	return new medWizardWaitButtonsOp(m_Label);
}
//----------------------------------------------------------------------------
bool medWizardWaitButtonsOp::Accept(mafNode *node)
//----------------------------------------------------------------------------
{
  //can accept everytime
  return true;
}
//----------------------------------------------------------------------------
void medWizardWaitButtonsOp::OpRun()   
//----------------------------------------------------------------------------
{
  m_Gui = new mafGUI(this);
  m_Gui->Divider();
  
  m_Gui->Label("");
  m_Gui->Label("");
  m_Gui->Label("");
  m_Gui->Label("");
  m_Gui->Label("");
  m_Gui->Label("");
  m_Gui->Label("");
  m_Gui->Label("");

  //exit op button
  //m_Gui->TwoButtons(wxCANCEL,wxOK,"Cancel","To next step");
  m_OkCancelButtons = new mafGUIPicButtons(m_Gui, ID_OK_CANCEL_BUTTONS, 2, 2);
  m_OkCancelButtons->SetListener(this);
  std::vector<wxString> pictures2;
  pictures2.push_back("OK_OPERATION");
  pictures2.push_back("CANCEL_OPERATION");
  m_OkCancelButtons->SetPictureVector(pictures2);
  m_OkCancelButtons->SetButtonsType(mafGUIPicButtons::ID_BUTTON);
  m_OkCancelButtons->Create();
  m_OkCancelButtons->SetToolTip(0, _("Ok"));
  m_OkCancelButtons->SetToolTip(1, _("Cancel"));
  m_Gui->Add(m_OkCancelButtons,0,wxLEFT);
    
  m_Gui->Divider();

  ShowGui();
}


//----------------------------------------------------------------------------
void medWizardWaitButtonsOp::OnEvent(mafEventBase *maf_event)
//----------------------------------------------------------------------------
{
  if (mafEvent *e = mafEvent::SafeDownCast(maf_event))
  {
    switch(e->GetId())
    {
	case ID_OK_CANCEL_BUTTONS:
		{
			if(e->GetArg() == ID_OK) {
				//exit operation
				HideGui();
				mafEventMacro(mafEvent(this,OP_RUN_OK));
			} else if(e->GetArg() == ID_CANCEL) {
				HideGui();
				mafEventMacro(mafEvent(this,OP_RUN_CANCEL));
			}
		}
	break;
	default:
		mafEventMacro(*e);
		break; 
    }
  }
}