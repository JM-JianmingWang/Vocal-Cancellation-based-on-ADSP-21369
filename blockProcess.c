//References: [1] GitHub User @adsp-21369-reverb, "VisualDSP-Echo"

#include "tt.h"
#include "DSP.h"
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */

#pragma misra_func(time)
clock_t start_t, end_t, total_t;
float clocks, timer;

void Block_Fixed_To_Float( int * Fixed_In, float * Float_Out_R, float * Float_Out_L );
void Block_Float_To_Fixed( int * Fixed_Out, float * Float_In_R, float * Float_In_L );

void processBlock(unsigned int *block_ptr)
{
    int i;
    static float leftChannel[NUM_SAMPLES/2];
    static float rightChannel[NUM_SAMPLES/2];
    float leftDry[NUM_SAMPLES/2];
    float rightDry[NUM_SAMPLES/2];

    start_t = clock();	// start timer

    //Clear the Block Ready Semaphore
    blockReady = 0;

    //Set the Processing Active Semaphore before starting processing
    isProcessing = 1;


    Block_Fixed_To_Float((int *) block_ptr, rightChannel, leftChannel);

    for(i=0; i<NUM_SAMPLES/2;i++)
    {
    	leftDry[i] = leftChannel[i];
    	rightDry[i] = rightChannel[i];
    }


    vocalCancel_highpass(rightChannel, leftChannel);


    for(i=0; i<NUM_SAMPLES/2;i++)
    {
    	leftChannel[i] = 10*leftDry[i] - 10*rightDry[i];
    	rightChannel[i] = 10*leftDry[i] - 10*rightDry[i];
    }
    
    
    vocalCancel_lowpass(rightChannel, leftChannel);
    

    Block_Float_To_Fixed((int *) block_ptr, rightChannel, leftChannel);



    //Clear the Processing Active Semaphore after processing is complete
    isProcessing = 0;

    clocks = CLOCKS_PER_SEC;
    end_t = clock();	// end timer
    total_t = end_t - start_t;	// compute process cycles
	  timer = ((double) (total_t))/CLOCKS_PER_SEC;	// compute process time

}

void Block_Fixed_To_Float( int * Fixed_In, float * Float_Out_R, float * Float_Out_L )
	{
	int i;
	#pragma SIMD_for
	for (i=0;i<NUM_SAMPLES/2;i++)
	{
		Float_Out_R[i] = ((float) (Fixed_In[2*i]<<8)) * (1.0/2147483648.0);
		Float_Out_L[i] = ((float) (Fixed_In[2*i+1]<<8)) * (1.0/2147483648.0);
	}
}

void Block_Float_To_Fixed( int * Fixed_Out, float * Float_In_R, float * Float_In_L )
{
	int i;
	#pragma SIMD_for
	for (i=0;i<NUM_SAMPLES/2;i++)
	{
		Fixed_Out[2*i] = ((int) (2147483648.0*Float_In_R[i]))>>8;
		Fixed_Out[2*i+1] = ((int) (2147483648.0*Float_In_L[i]))>>8;
	}
}
