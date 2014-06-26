#ifndef _TYPES_H_
#define _TYPES_H_
 
#if PLATFORM_ANDROID

////////////////////////////////////////////
//
// Chars
//
////////////////////////////////////////////
typedef  char             char8_t;
typedef  unsigned char    uchar8_t;
 
////////////////////////////////////////////
//
// Signed Integers
//
////////////////////////////////////////////
//typedef  char      int8_t;
typedef  short     int16_t;
typedef  int      int32_t;
typedef  long long     int64_t;
 
////////////////////////////////////////////
//
// Unsigned Integers
//
////////////////////////////////////////////
typedef  unsigned char    uint8_t;
typedef  unsigned short    uint16_t;
typedef  unsigned int    uint32_t;
typedef  unsigned long long   uint64_t;
 
////////////////////////////////////////////
//
// Floats
//
////////////////////////////////////////////
typedef  float      float32_t;
typedef  double     float64_t;
 
////////////////////////////////////////////
//
// Booleans
//
////////////////////////////////////////////
typedef  unsigned char    bool8_t;
typedef  unsigned short    bool16_t;
typedef  unsigned int    bool32_t;
typedef  unsigned long long   bool64_t;
 
#ifdef TRUE
#undef TRUE
#endif
#define  TRUE      1
 
#ifdef FALSE
#undef FALSE
#endif
#define  FALSE     0
 
////////////////////////////////////////////
//
// Pointers
//
////////////////////////////////////////////
 
#ifdef NULL
#undef NULL
#endif
#define  NULL     0
 
// Define _STDINT_H to prevent compiler clashes from that file being included elsewhere
//#define _STDINT_H
 
#elif PLATFORM_WINDOWS
#include <cstdint>
 
////////////////////////////////////////////
//
// Chars
//
////////////////////////////////////////////
typedef  char      char8_t;
typedef  unsigned char    uchar8_t;
 
////////////////////////////////////////////
//
// Floats
//
////////////////////////////////////////////
typedef  float      float32_t;
typedef  double     float64_t;
 
////////////////////////////////////////////
//
// Booleans
//
////////////////////////////////////////////
typedef  unsigned char    bool8_t;
typedef  unsigned short    bool16_t;
typedef  unsigned int    bool32_t;
typedef  unsigned long long   bool64_t;
 
#ifdef TRUE
#undef TRUE
#endif
#define  TRUE      1
 
#ifdef FALSE
#undef FALSE
#endif
#define  FALSE     0
 
////////////////////////////////////////////
//
// Pointers
//
////////////////////////////////////////////
#ifdef NULL
#undef NULL
#endif
#define  NULL      0

#else
#error ("Unsupported platform")
#endif
 
#endif