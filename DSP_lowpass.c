//References: [1] GitHub User @adsp-21369-reverb, "VisualDSP-Echo"

#include "tt.h"
#include <stdlib.h>
#include "DSP.h"
#include "DSP_lowpass.h"

//#pragma file_attr("prefersMem=external")

void lp_init(struct_lp *data, float *buffer_lp, int delaysize, float gain)
{
        data->in = 0;
        data->out = 0;
        data->g = gain;
        data->rIndex = 1; // points at first+1 buffer element     
        data->wIndex = 0; // points at first buffer element        
        data->delaysize = delaysize+1;
        data->buffer = buffer_lp; // pointer to buffer array
        
        //data->buffer = (float *)calloc(data->delaysize, sizeof(float));
		//data->buffer = (float *)malloc(data->delaysize * sizeof(float));
        
        // clear buffer at init, commented out due to calloc instead of malloc
        int i;
        for(i=0; i < data->delaysize; i++)
        data->buffer[i] = 0;
}

void lp(struct_lp *data, float sig)
{

	            data->in = sig;
                data->out = sig * data->g + data->buffer[data->rIndex] * (1-data->g);
                data->buffer[data->wIndex] = data->out;

                data->rIndex++;
                data->wIndex++;

                if(data->rIndex >= data->delaysize)
                data->rIndex=0;

                if(data->wIndex >= data->delaysize)
                data->wIndex=0;
                           
}



