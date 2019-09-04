///////////////////////////////////////////////////////////////////////////////////////
//NAME:     tt.h
//DATE:     7/29/05
//PURPOSE:  Header file with definitions use in the C-based talkthrough examples
//
////////////////////////////////////////////////////////////////////////////////////////
#ifndef _TT_H_
#define _TT_H_

#include <cdef21369.h>
#include <def21369.h>
#include <signal.h>

#define NUM_SAMPLES 2 // was 1024 in original blockbased talkthrough

// Function prototypes for this talkthrough code

extern void InitPLL_SDRAM(void);
extern void processBlock(unsigned int *);

extern void InitSRU(void);
extern void Init1835viaSPI(void);

extern void InitSPORT(void);
extern void TalkThroughISR(int);
extern void ClearSPORT(void);

extern void SetupSPI1835 (void) ;
extern void DisableSPI1835 (void) ;
extern void Configure1835Register (int i) ;
extern unsigned int Get1835Register (int i) ;

extern void SetupIRQ01 (void) ;
extern void Irq0ISR (int i) ;
extern void Irq1ISR (int i) ;

extern void Delay (int i) ;

extern int isProcessing;
extern int blockReady;
extern unsigned int *src_pointer[3];
extern int int_cntr;

#endif
