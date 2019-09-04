///////////////////////////////////////////////////////////////////////////////////////
//NAME:     SPORTisr.c (Block-based Talkthrough)
//DATE:     7/29/05
//PURPOSE:  Talkthrough framework for sending and receiving samples to the AD1835.
//
//USAGE:    This file contains SPORT0 Interrupt Service Routine. Three buffers are used
//          for this example. One is filled by the ADC, another is sent to the DAC, and
//          the final buffer is processed. Each buffer rotates between these functions
//          upon each SP0 interrupt received.
///////////////////////////////////////////////////////////////////////////////////////
/*
   Here is the mapping between the SPORTS and the DACS
   ADC -> DSP  : SPORT0A : I2S
   DSP -> DAC1 : SPORT1A : I2S
   DSP -> DAC2 : SPORT1B : I2S
   DSP -> DAC3 : SPORT2A : I2S
   DSP -> DAC4 : SPORT2B : I2S
*/

#include "tt.h"
#include <stdio.h>

extern unsigned int Block_A[NUM_SAMPLES] ;
extern unsigned int Block_B[NUM_SAMPLES] ;
extern unsigned int Block_C[NUM_SAMPLES] ;

extern unsigned int OFFSET ;

    //Pointer to the blocks

unsigned int *src_pointer[3] = {Block_A,
                                Block_C,
                                Block_B};

// Counter to choose which buffer to process
int int_cntr=2;
// Semaphore to indicate to main that a block is ready for processing
//int blockReady=0;
int blockReady=0;

// Semaphore to indicate to the isr that the processing has not completed before the
// buffer will be overwritten.
//int isProcessing=0;
int isProcessing=0;

//If the processing takes too long, the program will be stuck in this infinite loop.
void ProcessingTooLong(void)
{
    while(1);
}

void TalkThroughISR(int sig_int)
{
    /*if(isProcessing)
        ProcessingTooLong();*/

    //Increment the block pointer
    int_cntr++;
    int_cntr %= 3;

    blockReady = 1;

}
