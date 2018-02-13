// sin and tri wave functions for HW4
// Shaan Savarirayan
// 1.31.2018

#include <waves.h>
#include <math.h>

#define pi 3.14159
#define SINLEN 100
#define TRILEN 200

static volatile unsigned short sinvec;
static volatile unsigned short trivec;

void sinwave(void)  {
	for (int i=0; i<SINLEN; i++)  {
		sinvec[i] = 127.5*sin((double)2*PI*i/(SINLEN))+127.5;   //  creates 10 Hz sin wave 
	}
	return sinvec;
}

void triwave(void)  {	
    for (int j=0; j<TRILEN; j++)    {
		trivec[j] = 255*((double)j/TRILEN);                     //  creates 5 Hz tri wave
    }
    return trivec;
}





