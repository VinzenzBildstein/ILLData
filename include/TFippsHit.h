#ifndef FIPPSHIT_H
#define FIPPSHIT_H

/** \addtogroup Detectors
 *  @{
 */

#include <cstdio>
#include <cmath>

#include "TVector3.h"

#include "TFragment.h"
#include "TChannel.h"

class TFippsHit : public TDetectorHit {
public:
   TFippsHit();
   TFippsHit(const TFippsHit&);
   TFippsHit(const TFragment&);
   ~TFippsHit() override;

public:
   /////////////////////////  Getters	/////////////////////////////////////
   Double_t GetNoCTEnergy(Option_t* opt = "") const;

   /////////////////////////  Recommended Functions/////////////////////////

   /////////////////////////		/////////////////////////////////////

   static bool CompareEnergy(const TFippsHit*, const TFippsHit*); //!<!
   void        Add(const TDetectorHit*) override;             //!<!

public:
   void Clear(Option_t* opt = "") override;       //!<!
   void Print(Option_t* opt = "") const override; //!<!
   void Copy(TObject&) const override;            //!<!
   void Copy(TObject&, bool) const override;      //!<!

   TVector3 GetPosition(double dist) const override; //!<!
   TVector3 GetPosition() const override;

private:
   Double_t GetDefaultDistance() const { return 110.; }

   /// \cond CLASSIMP
   ClassDefOverride(TFippsHit, 2); // Information about a FIPPS Hit
   /// \endcond
};
/*! @} */
#endif
