///////////////////////////////////////////////////////////////////////////////////////
//NAME:     initSPORT.c (Block-based Talkthrough)
//DATE:     7/29/05
//PURPOSE:  Talkthrough framework for sending and receiving samples to the AD1835.
//
//USAGE:    This file uses SPORT0 to receive data from the ADC and transmits the
//			data to the DAC's via SPORT1A, SPORT1B, SPORT2A and SPORT2B.
//			DMA Chaining is enabled
//
////////////////////////////////////////////////////////////////////////////////////////

#include "tt.h"
#define DAC4
/*
   Here is the mapping between the SPORTS and the DACS
   ADC -> DSP  : SPORT0A : I2S
   DSP -> DAC1 : SPORT1A : I2S
   DSP -> DAC2 : SPORT1B : I2S
   DSP -> DAC3 : SPORT2A : I2S
   DSP -> DAC4 : SPORT2B : I2S
*/

unsigned int PCI = 0x00080000 ;
unsigned int OFFSET = 0x00080000 ;

// TCB blocks for Chaining
//Each block will be used for:
//      Filling from the ADC
//      Processing filled data
//      Sending to DAC
//
//Each one is doing only one of these steps for each SPORT interrupt.

//For this example the startup state is
// Start to 1st interrupt: Block_A is filled first, Block_C is sent
// 1st int to 2nd int: Block_C filled, Block_A processed, Block_B sent
// 2nd int to 3rd int: Block_B filled, Block_C processed, Block_A sent
// 3rd int to 4th int: Block_A filled, Block_B processed, Block_C sent
unsigned int Block_A[NUM_SAMPLES] ;
unsigned int Block_B[NUM_SAMPLES] ;
unsigned int Block_C[NUM_SAMPLES] ;

//Set up the TCBs to rotate automatically
int TCB_Block_A[4] = { 0, sizeof(Block_A), 1, 0};;
int TCB_Block_B[4] = { 0, sizeof(Block_B), 1, 0};
int TCB_Block_C[4] = { 0, sizeof(Block_C), 1, 0};

void InitSPORT()
{
    //Proceed from Block A to Block C
    TCB_Block_A[0] = (int) TCB_Block_C + 3 - OFFSET + PCI ;
    TCB_Block_A[3] = (unsigned int) Block_A - OFFSET ;

    //Proceed from Block B to Block A
    TCB_Block_B[0] = (int) TCB_Block_A + 3 - OFFSET + PCI ;
    TCB_Block_B[3] = (unsigned int) Block_B - OFFSET ;

    //Proceed from Block C to Block B
    TCB_Block_C[0] = (int) TCB_Block_B + 3 - OFFSET + PCI ;
    TCB_Block_C[3] = (unsigned int) Block_C - OFFSET ;

    //Clear the Mutlichannel control registers
    *pSPMCTL0 = 0;
    *pSPMCTL1 = 0;
    *pSPMCTL2 = 0;
    *pSPCTL0 = 0 ;
    *pSPCTL1 = 0 ;
    *pSPCTL2 = 0 ;

    //============================================================
    //
    // Configure SPORT 0 for input from ADC
    //
    //------------------------------------------------------------


    *pSPCTL0 = (OPMODE | SLEN24 | SPEN_A | SCHEN_A | SDEN_A);

    // Enabling Chaining
    // Block A will be filled first
    *pCPSP0A = (unsigned int) TCB_Block_A - OFFSET + 3 ;

    //============================================================
    //
    // Configure SPORTs 1 & 2 for output to DACs 1-4
    //
    //------------------------------------------------------------

    #ifdef DAC1
    *pSPCTL1 = (SPTRAN | OPMODE | SLEN24 | SPEN_A | SCHEN_A | SDEN_A) ;
    // write to DAC1
    *pCPSP1A = (unsigned int) TCB_Block_C - OFFSET + 3 ;
    #endif

    #ifdef DAC2
    *pSPCTL1 |= (SPTRAN | OPMODE | SLEN24 | SPEN_B | SCHEN_B | SDEN_B) ;
    // write to DAC2
    *pCPSP1B = (unsigned int) TCB_Block_C - OFFSET + 3 ;
    #endif

    #ifdef DAC3
    *pSPCTL2 = (SPTRAN | OPMODE | SLEN24 | SPEN_A | SCHEN_A | SDEN_A) ;
    // write to DAC3
    *pCPSP2A = (unsigned int) TCB_Block_C - OFFSET + 3 ;
    #endif

    #ifdef DAC4
    *pSPCTL2 |= (SPTRAN | OPMODE | SLEN24 | SPEN_B | SCHEN_B | SDEN_B) ;
    // write to DAC4
    *pCPSP2B = (unsigned int) TCB_Block_C - OFFSET + 3 ;
    #endif


}
