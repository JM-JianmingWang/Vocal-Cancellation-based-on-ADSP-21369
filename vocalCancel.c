/********************************************************************************************
 * vocalCancel.c         //References: [1] GitHub User @adsp-21369-reverb, "VisualDSP-Echo" *
 ********************************************************************************************/
#include "DSP.h"
#include "DSP_highpass.h"
#include "DSP_lowpass.h"
//#include "convolution.h"

// define size of delaylines for each module

#define delaysize_hp1 1
#define delaysize_hp2 1
#define delaysize_hp3 1
#define delaysize_hp4 1
#define delaysize_hp5 1
#define delaysize_hp6 1

#define delaysize_lp1 1
#define delaysize_lp2 1
#define delaysize_lp3 1
#define delaysize_lp4 1
#define delaysize_lp5 1
#define delaysize_lp6 1

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ CREATE FILTER STRUCTS + global buffers ~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// always add 1 sample for write/read index offset


struct_hp hp1;
float buffer_hp1[delaysize_hp1+1];

struct_lp lp1;
float buffer_lp1[delaysize_lp1+1];

struct_hp hp2;
float buffer_hp2[delaysize_hp2+1];

struct_lp lp2;
float buffer_lp2[delaysize_lp2+1];

struct_hp hp3;
float buffer_hp3[delaysize_hp3+1];

struct_lp lp3;
float buffer_lp3[delaysize_lp3+1];

struct_hp hp4;
float buffer_hp4[delaysize_hp4+1];

struct_lp lp4;
float buffer_lp4[delaysize_lp4+1];

struct_hp hp5;
float buffer_hp5[delaysize_hp4+1];

struct_lp lp5;
float buffer_lp5[delaysize_lp4+1];

struct_hp hp6;
float buffer_hp6[delaysize_hp4+1];

struct_lp lp6;
float buffer_lp6[delaysize_lp4+1];


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ CREATE GLOBAL VARIABLES ~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
float In;
//float hp_result;       //for convolution
//float lp_result;       //for convolution

// -------------------------------------------------
// ~~~ Init Filter Structs ~~~
// -------------------------------------------------

void vocalCancel_init(void)
{

  hp_init(&hp1, buffer_hp1, delaysize_hp1, bandwidth_h);
	lp_init(&lp1, buffer_lp1, delaysize_lp1, bandwidth_l);
  hp_init(&hp2, buffer_hp2, delaysize_hp2, bandwidth_h);
	lp_init(&lp2, buffer_lp2, delaysize_lp2, bandwidth_l);
  hp_init(&hp3, buffer_hp3, delaysize_hp3, bandwidth_h);
	lp_init(&lp3, buffer_lp3, delaysize_lp3, bandwidth_l);
  hp_init(&hp4, buffer_hp4, delaysize_hp4, bandwidth_h);
	lp_init(&lp4, buffer_lp4, delaysize_lp4, bandwidth_l);
  hp_init(&hp5, buffer_hp5, delaysize_hp5, bandwidth_h);
	lp_init(&lp5, buffer_lp5, delaysize_lp5, bandwidth_l);
  hp_init(&hp6, buffer_hp6, delaysize_hp6, bandwidth_h);
	lp_init(&lp6, buffer_lp6, delaysize_lp6, bandwidth_l);

}


// -------------------------------------------------
// ~~~ Main DSP Path ~~~
// -------------------------------------------------
void vocalCancel_highpass(float *rightChannel, float *leftChannel)
{
	int i;

	for(i=0; i<NUM_SAMPLES/2; i++)
	{
		In = (leftChannel[i] + rightChannel[i])/2;

		hp(&hp1, In);
		
		hp(&hp2, hp1.out);	

		hp(&hp3, hp2.out);
		
		hp(&hp4, hp3.out);
		
		hp(&hp5, hp4.out);
		
		hp(&hp6, hp5.out);
		
		
		//function1(hp5.out);            //for convolution
		//function2(hp6.out);            //for convolution
		//convolution(hp_result);        //for convolution
		
		
		leftChannel[i] = hp6.out; //+ hp_result;        <---//for convolution
		rightChannel[i] = hp6.out; //+ hp_result;       <---//for convolution
        //different hp(hp1 to hp6) will have different cancellation effect
	}

}


void vocalCancel_lowpass(float *rightChannel, float *leftChannel)
{
	int i;

	for(i=0; i<NUM_SAMPLES/2; i++)
	{
	    In = (leftChannel[i] + rightChannel[i])/2;
	    
		lp(&lp1, In);

		lp(&lp2, lp1.out);

		lp(&lp3, lp2.out);

		lp(&lp4, lp3.out);
		
		lp(&lp5, lp4.out);
		
		lp(&lp6, lp5.out);
		

		//function1(lp5.out);            //for convolution
		//function2(lp6.out);            //for convolution
		//convolution(lp_result);        //for convolution
		
		
		leftChannel[i] = lp6.out;  //+ lp_result;       <---//for convolution
		rightChannel[i] = lp6.out; //+ lp_result;       <---//for convolution
		//different lp(lp1 to lp6 or even more) will have different cancellation effect. The higher one you use, the stronger effect will have, but more detail will lose.
        //I think lp3 or lp4 is the best in some songs that most music details are preserved. However, in some songs, you need to use lp6 or add LPF(s) for better cancellation. Be careful about the uncomfortable bass!
	}

}








