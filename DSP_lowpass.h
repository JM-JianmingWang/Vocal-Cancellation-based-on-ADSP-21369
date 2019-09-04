
#ifndef __DSP_LOWPASS__
#define __DSP_LOWPASS__

typedef struct
{
  float in;
  float out;
  float g;
  int rIndex;
  int wIndex;
  int delaysize;
  float *buffer;
} struct_lp;


extern void lp_init(struct_lp *data, float *buffer_lp, int delaysize, float gain);
extern void lp(struct_lp *data, float sig);

#endif
