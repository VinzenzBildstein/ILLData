#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cassert>

#include "TLstEvent.h"

TLstEvent::TLstEvent()
{
   // Default constructor
   fData.resize(0);
}

void TLstEvent::Copy(TObject& rhs) const
{
   // Copies the entire TLstEvent.
   static_cast<TLstEvent&>(rhs).fData = fData;
}

TLstEvent::TLstEvent(const TLstEvent& rhs) : TRawEvent()
{
   // Copy ctor.
   rhs.Copy(*this);
}

TLstEvent::~TLstEvent()
{
   Clear();
}

TLstEvent& TLstEvent::operator=(const TLstEvent& rhs)
{
   if(&rhs != this) {
      Clear();
   }

   rhs.Copy(*this);
   return *this;
}

void TLstEvent::Clear(Option_t*)
{
   // Clears the TLstEvent.
   fData.clear();
}

void TLstEvent::SetData(std::vector<char>& buffer)
{
   // Sets the data in the TLstEvent as the data argument passed into
   // this function.
   fData = buffer;
   SwapBytes(false);
}

uint32_t TLstEvent::GetDataSize() const
{
   return fData.size();
}

char* TLstEvent::GetData()
{
   // returns the allocated data.
   return fData.data();
}

void TLstEvent::Print(const char* option) const
{
   /// Print data held in this class.
   /// \param [in] option If 'a' (for "all") then the raw data will be
   /// printed out too.
   ///

   std::cout << "Event start:" << std::endl;
   if(option[0] == 'a') {
      for(size_t i = 0; i < fData.size() / 4; ++i) {
         std::cout << hex(((uint32_t*)fData.data())[i], 8) << std::endl;
         if(i % 10 == 9) {
            std::cout << std::endl;
         } else {
            std::cout << " ";
         }
      }
   }
}

using BYTE = uint8_t;

/// Byte swapping routine.
///
#define QWORD_SWAP(x)                            \
   {                                             \
      BYTE _tmp;                                 \
      _tmp                = *((BYTE*)(x));       \
      *((BYTE*)(x))       = *(((BYTE*)(x)) + 7); \
      *(((BYTE*)(x)) + 7) = _tmp;                \
      _tmp                = *(((BYTE*)(x)) + 1); \
      *(((BYTE*)(x)) + 1) = *(((BYTE*)(x)) + 6); \
      *(((BYTE*)(x)) + 6) = _tmp;                \
      _tmp                = *(((BYTE*)(x)) + 2); \
      *(((BYTE*)(x)) + 2) = *(((BYTE*)(x)) + 5); \
      *(((BYTE*)(x)) + 5) = _tmp;                \
      _tmp                = *(((BYTE*)(x)) + 3); \
      *(((BYTE*)(x)) + 3) = *(((BYTE*)(x)) + 4); \
      *(((BYTE*)(x)) + 4) = _tmp;                \
   }

/// Byte swapping routine.
///
#define DWORD_SWAP(x)                            \
   {                                             \
      BYTE _tmp;                                 \
      _tmp                = *((BYTE*)(x));       \
      *((BYTE*)(x))       = *(((BYTE*)(x)) + 3); \
      *(((BYTE*)(x)) + 3) = _tmp;                \
      _tmp                = *(((BYTE*)(x)) + 1); \
      *(((BYTE*)(x)) + 1) = *(((BYTE*)(x)) + 2); \
      *(((BYTE*)(x)) + 2) = _tmp;                \
   }

/// Byte swapping routine.
///
#define WORD_SWAP(x)                             \
   {                                             \
      BYTE _tmp;                                 \
      _tmp                = *((BYTE*)(x));       \
      *((BYTE*)(x))       = *(((BYTE*)(x)) + 1); \
      *(((BYTE*)(x)) + 1) = _tmp;                \
   }

int TLstEvent::SwapBytes(bool)
{
   return 1;
}

// end
