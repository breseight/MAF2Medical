/*=========================================================================
Program:   Multimod Application Framework
Module:    $RCSfile: medOpSegmentationRegionGrowingLocalAndGlobalThreshold.h,v $
Language:  C++
Date:      $Date: 2009-10-30 10:49:38 $
Version:   $Revision: 1.1.2.2 $
Authors:   Matteo Giacomoni
==========================================================================
Copyright (c) 2009
SCS s.r.l. - BioComputing Competence Centre (www.scsolutions.it - www.b3c.it)

MafMedical Library use license agreement

The software named MafMedical Library and any accompanying documentation, 
manuals or data (hereafter collectively "SOFTWARE") is property of the SCS s.r.l.
This is an open-source copyright as follows:
Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:
* Redistributions of source code must retain the above copyright notice, 
this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright notice, 
this list of conditions and the following disclaimer in the documentation and/or 
other materials provided with the distribution.
* Modified source versions must be plainly marked as such, and must not be misrepresented 
as being the original software.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 'AS IS' 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
ARE DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR 
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND 
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

MafMedical is partially based on OpenMAF.
=========================================================================*/

#ifndef __medOpSegmentationRegionGrowingLocalAndGlobalThreshold_H__
#define __medOpSegmentationRegionGrowingLocalAndGlobalThreshold_H__

//----------------------------------------------------------------------------
// Include :
//----------------------------------------------------------------------------
#include "mafOp.h"

//----------------------------------------------------------------------------
// forward references :
//----------------------------------------------------------------------------
class mafVMEVolumeGray;
class mafGUILutSlider;
class mafGUIHistogramWidget;
class vtkImageData;

//----------------------------------------------------------------------------
// medOpSegmentationRegionGrowingLocalAndGlobalThreshold :
//----------------------------------------------------------------------------
/** 

*/
class medOpSegmentationRegionGrowingLocalAndGlobalThreshold: public mafOp
{
public:

  medOpSegmentationRegionGrowingLocalAndGlobalThreshold(wxString label = "Region Growing");
  ~medOpSegmentationRegionGrowingLocalAndGlobalThreshold(); 

  mafTypeMacro(medOpSegmentationRegionGrowingLocalAndGlobalThreshold, mafOp);

  mafOp* Copy();

  void OnEvent(mafEventBase *maf_event);

  /** Return true for the acceptable vme type. */
  /*virtual*/ bool Accept(mafNode* vme);

  /** Builds operation's interface by calling CreateOpDialog() method. */
  /*virtual*/ void OpRun();

  /** Execute the operation. */
  /*virtual*/ void OpDo();

  /** Makes the undo for the operation. */
  /*virtual*/ void OpUndo();

protected:
  
  /** Create the operation gui */
  void CreateGui();

  /** Perform the local segmentation */
  void LocalSegmentation();

  void MorphologicalMathematics();

  /** Update progress bar value */
  void UpdateProgressBar();

  //GUI Stuff
  double m_LowerLabel;
  double m_UpperLabel;
  int m_SphereRadius;
  mafGUILutSlider *m_SliderLabels;
  mafGUILutSlider *m_SliderThresholds;
  mafGUI *m_GuiLabels;

  mafGUIHistogramWidget *m_Histogram;

  mafVMEVolumeGray *m_VolumeInput; //<<<Input volume
  mafVMEVolumeGray *m_VolumeOutputMorpho; //<<<Output volume
  mafVMEVolumeGray *m_VolumeOutputRegionGrowing; //<<<Output volume

  vtkImageData *m_SegmentedImage;
  vtkImageData *m_MorphoImage;

};
#endif