#ifndef FIPPSTACHIT_H
#define FIPPSTACHIT_H

/** \addtogroup Detectors
 *  @{
 */

/////////////////////////////////////////////////////////////////
///
/// \class TFippsTACHit
///
/// This is class that contains the information about a TAC
/// hit. This class is used to find energy, time, etc.
///
/////////////////////////////////////////////////////////////////

#include <cstdio>
#include <cmath>

#include "TFragment.h"
#include "TChannel.h"
#include "TGraph.h"

#include "TVector3.h"

#include "TDetectorHit.h"

class TFippsTACHit : public TDetectorHit {
public:
   TFippsTACHit();
   ~TFippsTACHit() override;
   TFippsTACHit(const TFippsTACHit&);
   TFippsTACHit(const TFragment& frag) : TDetectorHit(frag) {}

   Double_t GetTempCorrectedCharge(TGraph* correction_graph) const;
   Double_t TempCorrectedCharge(TGraph* correction_graph) const;
   Double_t GetTempCorrectedEnergy(TGraph* correction_graph) const;

   void Clear(Option_t* opt = "") override;         //!<!
   void Print(Option_t* opt = "") const override;   //!<!
   void Print(std::ostream& out) const override;
   void Copy(TObject&) const override;         //!<!
   void Copy(TObject&, bool) const override;   //!<!

   /// \cond CLASSIMP
   ClassDefOverride(TFippsTACHit, 2)   // Stores the information for a TACrHit
   /// \endcond
};
/*! @} */
#endif
