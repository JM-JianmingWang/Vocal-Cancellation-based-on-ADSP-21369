#ifndef __DSP__
#define __DSP__

#include "tt.h"
#include "DSP_highpass.h"
#include "DSP_lowpass.h"


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ DEFINE GLOBAL CONSTANTS ~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define FS 48000 // DACFS48 set in init1835viaSPI.c

#define bandwidth_l 0.05
#define bandwidth_h 0.0002



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ EXTERN VARIABLES ~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ...



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ FUNCTION PROTOTYPES ~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

extern void vocalCancel_init(void);
extern void vocalCancel_highpass(float *rightChannel, float *leftChannel);
extern void vocalCancel_lowpass(float *rightChannel, float *leftChannel);

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ FILTER STRUCTS ~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
extern struct_hp hp1;
extern struct_hp hp2;
extern struct_hp hp3;
extern struct_hp hp4;
extern struct_hp hp5;
extern struct_hp hp6;


extern struct_lp lp1;
extern struct_lp lp2;
extern struct_lp lp3;
extern struct_lp lp4;
extern struct_lp lp5;
extern struct_lp lp6;

#endif
