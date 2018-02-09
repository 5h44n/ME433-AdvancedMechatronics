// sin and tri wave functions for HW4
// Shaan Savarirayan
// 1.31.2018

#include <waves.h>

#define pi 3.14159
#define SINLEN 100
#define TRILEN 200

static volatile unsigned short sinwave
static volatile unsigned short triwave

void sinwave(void) {
	for (int i=0,i<SINLEN,i++)	{
		sinwave[i] = 127.5*sin((double)2*PI*i/(SINLEN))+127.5;
	}
	return sinwave;
}

void triwave(void)  {	
    for (int i=0; i<TRILEN; i++){
		triwave[i] = 255*((double)i/TRILEN);
    }
    return triwave;
}





