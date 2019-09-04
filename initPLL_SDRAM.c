/********************************************************************************************
**
**  File:   initPLL.c
**  Date:   7-29-05
**  Author: SH
**  Use:    Initialize the DSP PLL for the required CCLK and HCLK rates.
**  Note:   CLKIN will be 24.576 MHz from an external oscillator.  The PLL is programmed
**          to generate a core clock (CCLK) of 331.776 MHz - PLL multiplier = 27 and
**          divider = 2.
**
*********************************************************************************************/
#include <def21369.h>
#include <cdef21369.h>

void InitPLL_SDRAM(){

/********************************************************************************************/

int i, pmctlsetting;

//Change this value to optimize the performance for quazi-sequential accesses (step > 1)
#define SDMODIFY 1

    pmctlsetting= *pPMCTL;
    pmctlsetting &= ~(0xFF); //Clear

    // CLKIN= 24.576 MHz, Multiplier= 27, Divisor= 1, INDIV=1, CCLK_SDCLK_RATIO= 2.
    // Core clock = (24.576 MHz * 27) /2 = 331.776 MHz
    pmctlsetting= SDCKR2|PLLM27|INDIV|DIVEN;
    *pPMCTL= pmctlsetting;
    pmctlsetting|= PLLBP;
    *pPMCTL= pmctlsetting;

    //Wait for around 4096 cycles for the pll to lock.
    for (i=0; i<4096; i++)
          asm("nop;");

    *pPMCTL ^= PLLBP;       //Clear Bypass Mode
    *pPMCTL |= (CLKOUTEN);  //and start clkout


    // Programming SDRAM control registers and enabling SDRAM read optimization
    // CCLK_SDCLK_RATIO= 2.5
    // RDIV = ((f SDCLK X t REF )/NRA) - (tRAS + tRP )
    // (166*(10^6)*64*(10^-3)/4096) - (7+3) = 2583

    *pSDRRC= (0xA17)|(SDMODIFY<<17)|SDROPT;

    //===================================================================
    //
    // Configure SDRAM Control Register (SDCTL) for PART MT48LC4M32B2
    //
    //  SDCL3  : SDRAM CAS Latency= 3 cycles
    //  DSDCLK1: Disable SDRAM Clock 1
    //  SDPSS  : Start SDRAM Power up Sequence
    //  SDCAW8 : SDRAM Bank Column Address Width= 8 bits
    //  SDRAW12: SDRAM Row Address Width= 12 bits
    //  SDTRAS7: SDRAM tRAS Specification. Active Command delay = 7 cycles
    //  SDTRP3 : SDRAM tRP Specification. Precharge delay = 3 cycles.
    //  SDTWR2 : SDRAM tWR Specification. tWR = 2 cycles.
    //  SDTRCD3: SDRAM tRCD Specification. tRCD = 3 cycles.
    //
    //--------------------------------------------------------------------

    *pSDCTL= SDCL3|DSDCLK1|SDPSS|SDCAW8|SDRAW12|SDTRAS7|SDTRP3|SDTWR2|SDTRCD3;

    // Note that MS2 & MS3 pin multiplexed with flag2 & flag3.
    // MSEN bit must be enabled to access SDRAM, but LED7 cannot be driven with sdram
    *pSYSCTL |=MSEN;

    // Mapping Bank 2 to SDRAM
    // Make sure that jumper is set appropriately so that MS2 is connected to
    // chip select of 16-bit SDRAM device
    *pEPCTL |=B2SD;
    *pEPCTL &= ~(B0SD|B1SD|B3SD);

    //===================================================================
    //
    // Configure AMI Control Register (AMICTL0) Bank 0 for the ISSI IS61LV5128
    //
    //  WS2 : Wait States = 2 cycles
    //  HC1  : Bus Hold Cycle (at end of write access)= 1 cycle.
    //  AMIEN: Enable AMI
    //  BW8  : External Data Bus Width= 8 bits.
    //
    //--------------------------------------------------------------------

    //SRAM Settings
    *pAMICTL0 = WS2|HC1|AMIEN|BW8;

    //===================================================================
    //
    // Configure AMI Control Register (AMICTL) Bank 1 for the AMD AM29LV08
    //
    //  WS23 : Wait States= 23 cycles
    //  AMIEN: Enable AMI
    //  BW8  : External Data Bus Width= 8 bits.
    //
    //--------------------------------------------------------------------

    //Flash Settings
    *pAMICTL1 = WS23|AMIEN|BW8;

}

