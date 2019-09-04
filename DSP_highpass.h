#ifndef __DSP_HIGHPASS__
#define __DSP_HIGHPASS__

typedef struct
{
  float in;
  float out;
  float g;
  int rIndex;
  int wIndex;
  int delaysize;
  float *buffer;
} struct_hp;


extern void hp_init(struct_hp *data, float *buffer_hp, int delaysize, float gain);
extern void hp(struct_hp *data, float sig);

#endif