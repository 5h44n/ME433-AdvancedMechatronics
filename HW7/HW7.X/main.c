#include <xc.h>                     //  processor SFR definitions
#include <sys/attribs.h>            //  __ISR macro
#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "ILI9163C.h"

#define DELAYTIME 1200000           //   
#define LED LATAbits.LATA4          //  easy access to LED

void delay(void);

int main()    {
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
    TRISAbits.TRISA4 = 0;	//  A4 (LED) = output
	TRISBbits.TRISB4 = 1;	//  B4 (BUTTON) = input
	LED = 1;		//  Turn on LED as default
  
    
    // allow I2C
    ANSELBbits.ANSB2 = 0;
    ANSELBbits.ANSB3 = 0;
    
    SPI1_init();
    LCD_init();
    i2c_master_setup();
    LSM6DS333_init();
    
    LCD_clearScreen(BACKGROUND);
    
    __builtin_enable_interrupts();
   
    char x;
    char buffer[20];
    x = IMU_getValue(0x0F);
    sprintf(buffer, "who: %i", x);
    LCD_writeString(45, 45, buffer, GREEN);
    
    while (1)   {
   
    }
    
    return 0;
}

void delay(void)    {                  //  delay function
    _CP0_SET_COUNT(0);
    while   (_CP0_GET_COUNT()<DELAYTIME)  {
        ;
    }
}