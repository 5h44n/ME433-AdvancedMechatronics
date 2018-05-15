#include <xc.h>                 //  processor SFR definitions
#include <sys/attribs.h>        //  __ISR macro
#include <stdio.h>

#include "pic32config.h"        //  PIC32 configuration pragma values
#include "ILI9163C.h"           //  LCD helper file

#define DELAYTIME 4800000       //  24MHz/5hz = 4,800,000

void delay(void);

int main() {

    __builtin_disable_interrupts();

    // set the CP0 CONFIG register to indicate that kseg0 is cacheable (0x3)
    __builtin_mtc0(_CP0_CONFIG, _CP0_CONFIG_SELECT, 0xa4210583);

    // 0 data RAM access wait states
    BMXCONbits.BMXWSDRM = 0x0;

    // enable multi vector interrupts
    INTCONbits.MVEC = 0x1;

    // disable JTAG to get pins back
    DDPCONbits.JTAGEN = 0;

    // do your TRIS and LAT commands here
    /*
    TRISAbits.TRISA4 = 0;	//  A4 (LED) = output
	TRISBbits.TRISB4 = 1;	//  B4 (BUTTON) = input
	LATAbits.LATA4 = 1;		//  Turn on LED as default
    */
    
    SPI1_init();                    //  initialize SPI
    LCD_init();                     //  initialize LCD
    LCD_clearScreen(BACKGROUND);    //  initialize screen as white
    __builtin_enable_interrupts();
    
    char message[25],fpsstr[25];    //  buffer storage for Hello World and live fps reading
    int integer = 0;                //  initialize integer to be incremented
    float fps = 0.0;                //  tracking frames per second
    
    while(1)    {
        _CP0_SET_COUNT(0);
        
        sprintf(message,"Hello World %d!",integer);
        LCD_writeString(28,32,message,RED);
        LCD_progressBar(28,50,integer,BLUE);
        
        fps = 24000000/_CP0_GET_COUNT();
        sprintf(fpsstr,"frames/sec: %1.2f", fps);
        LCD_writeString(28,70,fpsstr,MAGENTA);
        integer++;
        
        if(integer >= 10)  {
            integer = 0;
        }
        
        delay();
    }
}
void delay(void)    {                  //  delay function
    _CP0_SET_COUNT(0);
    while   (_CP0_GET_COUNT()<DELAYTIME)  {
        ;
    }
}
