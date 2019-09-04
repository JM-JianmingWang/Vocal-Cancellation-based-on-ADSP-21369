#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "convolution.h"
#include "DSP_lowpass.h"


float function1(float x1)   //h * f, h convolute f. I don't know why there will be an error if I put two functions together, such as h = x1*x2.
{
	float h;
	h = x1;  
	
	return h;
}

float function2(float x2)
{
	float f;
	f = x2;  
	
	return f;
}



int convolution(float itglResult)
{
	int i;
	float N = 10000;
	int a = 0x8000;      //minus infinite for int, can also be 0x80000000
	int b = 0x7FFF;      //plus infinite for int, can also be 0x7FFFFFFF

	
	for (i=0; i<=N; i++)
	{
		itglResult = itglResult + function1(a + ((b - a) / N) * i) * ((b - a) / N) * function2(a + ((b - a) / N) * i) * ((b - a) / N);       //not correct, it should be (function1*function2) and then do the integration
	}
	
	return 0;	
   	
}







