#include "TFipps.h"
#include "TFippsHit.h"
#include "Globals.h"
#include <cmath>
#include <iostream>

TFippsHit::TFippsHit()
   : TDetectorHit()
{
   // Default Ctor. Ignores TObject Streamer in ROOT < 6.
#if ROOT_VERSION_CODE < ROOT_VERSION(6, 0, 0)
   Class()->IgnoreTObjectStreamer(kTRUE);
#endif
   Clear();
}

TFippsHit::TFippsHit(const TFippsHit& rhs) : TDetectorHit()
{
   // Copy Ctor. Ignores TObject Streamer in ROOT < 6.
   Clear();
   rhs.Copy(*this);
}

TFippsHit::TFippsHit(const TFragment& frag) : TDetectorHit(frag)
{
}

TFippsHit::~TFippsHit() = default;

void TFippsHit::Copy(TObject& rhs) const
{
   TDetectorHit::Copy(rhs);
}

void TFippsHit::Copy(TObject& obj, bool) const
{
   Copy(obj);
}

void TFippsHit::Clear(Option_t* opt)
{
   // Clears the information stored in the TFippsHit.
   TDetectorHit::Clear(opt);   // clears the base (address, position and waveform)
}

void TFippsHit::Print(Option_t*) const
{
   // Prints the Detector Number, Crystal Number, Energy, Time and Angle.
   Print(std::cout);
}

void TFippsHit::Print(std::ostream& out) const
{
   std::ostringstream str;
   str << "Fipps Detector: " << GetDetector() << std::endl;
   str << "Fipps Crystal:  " << GetCrystal() << std::endl;
   str << "Fipps Energy:   " << GetEnergy() << std::endl;
   str << "Fipps hit time: " << GetTime() << std::endl;
   str << "Fipps hit TV3 theta: " << GetPosition().Theta() * 180. / 3.141597 << "\tphi: " << GetPosition().Phi() * 180. / 3.141597 << std::endl;
   out << str.str();
}

TVector3 TFippsHit::GetPosition(double dist) const
{
   return TFipps::GetPosition(GetDetector(), GetCrystal(), dist);
}

TVector3 TFippsHit::GetPosition() const
{
   return GetPosition(GetDefaultDistance());
}

bool TFippsHit::CompareEnergy(const TFippsHit* lhs, const TFippsHit* rhs)
{
   return (lhs->GetEnergy() > rhs->GetEnergy());
}

void TFippsHit::Add(const TDetectorHit* hit)
{
   const TFippsHit* fippsHit = dynamic_cast<const TFippsHit*>(hit);
   if(fippsHit == nullptr) {
      throw std::runtime_error("trying to add non-fipps hit to fipps hit!");
   }
   // add another griffin hit to this one (for addback),
   // using the time and position information of the one with the higher energy
   if(!CompareEnergy(this, fippsHit)) {
      SetCfd(fippsHit->GetCfd());
      SetTime(fippsHit->GetTime());
      // SetPosition(fippsHit->GetPosition());
      SetAddress(fippsHit->GetAddress());
   }
   SetEnergy(GetEnergy() + fippsHit->GetEnergy());
   // this has to be done at the very end, otherwise GetEnergy() might not work
   SetCharge(0);
   // KValue is somewhate meaningless in addback, so I am using it as an indicator that a piledup hit was added-back RD
   if(GetKValue() > fippsHit->GetKValue()) {
      SetKValue(fippsHit->GetKValue());
   }
}

Double_t TFippsHit::GetNoCTEnergy(Option_t*) const
{
   TChannel* chan = GetChannel();
   if(chan == nullptr) {
      Error("GetEnergy", "No TChannel exists for address 0x%08x", GetAddress());
      return 0.;
   }
   return chan->CalibrateENG(Charge(), GetKValue());
}
