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

#ifndef __medWizardWaitButtonsOp_H__
#define __medWizardWaitButtonsOp_H__

//----------------------------------------------------------------------------
// Include:
//----------------------------------------------------------------------------
#include "medCommonDefines.h"
#include "mafOp.h"

//----------------------------------------------------------------------------
// forward references :
//----------------------------------------------------------------------------
class mafGui;
class mafEvent;
class mafGUIPicButtons;

/** 
  class name: medWizardWaitButtonsOp
  Simple op with only an next-step button create to insert pause during wizards.
*/
class MED_COMMON_EXPORT medWizardWaitButtonsOp: public mafOp
{
public:
  enum ID_OKCANCELBUTTONS {
	  ID_OK_CANCEL_BUTTONS = 9000,
	  ID_OK = 0,
	  ID_CANCEL = 1,
  };
  /** constructor */
  medWizardWaitButtonsOp(const wxString &label = "Go to text step\n");
  /** destructor */
  ~medWizardWaitButtonsOp();

  /** RTTI macro*/
  mafTypeMacro(medWizardWaitButtonsOp, mafOp);

  /** clone the object and retrieve a copy*/
  mafOp* Copy();

  /** Return true for the acceptable vme type. */
  bool Accept(mafNode *node);

  /** Builds operation's interface. */
  void OpRun();
  
  /**Event management*/
  void OnEvent(mafEventBase *maf_event);
protected:

  mafGUIPicButtons *m_OkCancelButtons;
};
#endif
