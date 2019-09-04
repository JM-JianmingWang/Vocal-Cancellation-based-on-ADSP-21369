///////////////////////////////////////////////////////////////////////////////////////
//NAME:     irqprocess.c (Block-based Talkthrough)
//DATE:     7/29/05
//PURPOSE:  Talkthrough framework for sending and receiving samples to the AD1835.
//
//USAGE:    This file contains the setup routine for IRQ0 and IRQ1, as well as the
//          interrupt service routine for handling each of the IRQ's. The ISR for
//          each button accesses the codec setting and adjusts the volume via SPI
//
////////////////////////////////////////////////////////////////////////////////////////
#include "tt.h"
#include "ad1835.h"

void SetupIRQ01 ()
{
    //Enable the pins as IRQ0 and IRQ1
    *pSYSCTL|= IRQ0EN | IRQ1EN;
    asm ("#include <def21369.h>") ;
    //Set the IRQ pins to be edge sensitive
    asm ("bit set mode2 IRQ0E;") ;
    asm ("bit set mode2 IRQ1E;") ;
}

void Irq0ISR (int i)
{
    int leftDAC4Vol, rightDAC4Vol ;

    // IRQ0 is used to decrease volume
    SetupSPI1835 () ;
    leftDAC4Vol = Get1835Register (RD | DACVOL_L4) ;
    rightDAC4Vol = Get1835Register (RD | DACVOL_R4) ;

    // Now decrease by a step size of 0x3F
    leftDAC4Vol -= 0x3F ;
    rightDAC4Vol -= 0x3F ;

    if (leftDAC4Vol > 0)
        Configure1835Register (WR | DACVOL_L4 | leftDAC4Vol) ;

    if (rightDAC4Vol > 0)
        Configure1835Register (WR | DACVOL_R4 | rightDAC4Vol) ;

    DisableSPI1835 () ;
}

void Irq1ISR (int i)
{
    int leftDAC4Vol, rightDAC4Vol ;

    // IRQ1 is used to decrease volume
    SetupSPI1835 () ;
    leftDAC4Vol = Get1835Register (RD | DACVOL_L4) ;
    rightDAC4Vol = Get1835Register (RD | DACVOL_R4) ;

    // Now decrease by a step size of 0x3F
    leftDAC4Vol += 0x3F ;
    rightDAC4Vol += 0x3F ;

    if (leftDAC4Vol < 0x3FF)
        Configure1835Register (WR | DACVOL_L4 | leftDAC4Vol) ;

    if (rightDAC4Vol < 0x3FF)
        Configure1835Register (WR | DACVOL_R4 | rightDAC4Vol) ;

    DisableSPI1835 () ;
}
