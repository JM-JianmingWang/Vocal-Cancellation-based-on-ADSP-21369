///////////////////////////////////////////////////////////////////////////////////////
//NAME:     main.c (Vocal Cancellation)
//DATE:     2019.8.22
//PURPOSE:  Use HPF and LPF to cut vocal sound.
//
//USAGE:    This file contains the main routine calls functions to set up the talkthrough
//          routine. It receives an input signal from the ADC via SPORT0A. Then use HPF, subtraction and LPF to cut vocal sound.            
//          Finally, outputs to DAC's via SPORT1A, SPORT1B, SPORT2A, and SPORT2B.
//
//References: [1] GitHub User @adsp-21369-reverb, "VisualDSP-Echo"     [2] Analog Devices, Inc. "C Block-based talkthrough" Example
////////////////////////////////////////////////////////////////////////////////////////

#include "tt.h"
#include "DSP.h"

void main(void)
{

    //Initialize PLL to run at CCLK= 331.776 MHz & SDCLK= 165.888 MHz.
    //SDRAM is setup for use, but cannot be accessed until MSEN bit is enabled
    InitPLL_SDRAM();

    vocalCancel_init(); //vocal cancellation main function
    
    // Setting up IRQ0 and IRQ1
    SetupIRQ01();

    // Need to initialize DAI because the sport signals need to be routed
    InitSRU();

    // This function will configure the codec on the kit
    Init1835viaSPI();

    interrupt (SIG_SP0, TalkThroughISR);
    interrupt (SIG_IRQ0, Irq0ISR);
    interrupt (SIG_IRQ1, Irq1ISR);

    // Finally setup the sport to receive / transmit the data
    InitSPORT();
    

    
    // Be in infinite loop and do nothing until done.
    for(;;)
    {
     while(blockReady)
         processBlock(src_pointer[int_cntr]);
        
    }

}
