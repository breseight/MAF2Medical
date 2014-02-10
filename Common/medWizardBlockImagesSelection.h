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

#ifndef __medWizardBlockImagesSelection_H__
#define __medWizardBlockImagesSelection_H__

//----------------------------------------------------------------------------
// includes :
//----------------------------------------------------------------------------
#include "medCommonDefines.h"
#include "medWizardBlockSelection.h"
#include <vector>

//----------------------------------------------------------------------------
// forward reference
//----------------------------------------------------------------------------

/**
  Class Name: medWizardSelectionBlockImages.
  Class for create a multiple choice switch inside wizard graph
*/
class MED_COMMON_EXPORT medWizardBlockImagesSelection : public medWizardBlockSelection
{
public:

  /** Default constructor */
  medWizardBlockImagesSelection(const char *name);

  /** Default destructor */
  ~medWizardBlockImagesSelection();

  void AddImage(wxString imageName) {m_ImageList.push_back(imageName);};

protected:
  /** Starts the execution of the block */
  virtual void ExcutionBegin();

  std::vector < wxString > m_ImageList; 

};

#endif