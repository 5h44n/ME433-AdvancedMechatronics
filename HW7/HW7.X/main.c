#include <xc.h>                     //  processor SFR definitions
#include <sys/attribs.h>            //  __ISR macro
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "config.h"
#include "ILI9163C.h"
#include "LSM6DS33.h"
#include "i2c.h"

#define DELAYTIME 4800000           //  delay at 5 Hz
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
	LED = 1;                //  Turn on LED as default
    
    SPI1_init();
    LCD_init();
    LSM6DS33_init();
    
    __builtin_enable_interrupts();
    
    LCD_clearScreen(BACKGROUND);
    
    /*
    int x;
    char buffer[20];
    x = IMU_getValue(0x0F);                             //  WHO_AM_I = 0x0F
    sprintf(buffer, "who am i: %d", x);
    LCD_writeString(30, 30, buffer, RED);
    */
    
    unsigned char dataraw[14];
    signed short datap[7];
    float xacc, yacc;
    char xlen, ylen;
    char message[50];
    
    while (1)   {  
        i2c_read_multiple(ADD,0x20,dataraw,14);         //  starts at 0x20 = OUT_TEMP_L and reads 14 registers
        
        int i;
        for(i=0; i < 7; i++)  {                         //  convert data from unsigned short to signed shorts
            datap[i] = dataraw[(2*i)+1];                //  store high byte
            datap[i] = (datap[i] << 8) | dataraw[2*i];  //  shift high byte, or with low byte
        }
        
        xacc = (float)(datap[4])*(2.0/32757.0);         //  scale acceleration values to range from -1 to 1;
        yacc = (float)(datap [5])*(2.0/32757.0);
        
        xlen = abs(xacc*50.0);
        ylen = abs(yacc*50.0);
        
        
        
        sprintf(message,"x''= %1.1f",xacc);         //  datap = [temp gx gy gz ax ay az]
        LCD_writeString(5,10,message,BLACK);
        sprintf(message,"y'' = %1.1f",yacc);
        LCD_writeString(5,20,message,RED);
        /*
        sprintf(message,"xtest= %d  ",datap[4]);         
        LCD_writeString(5,40,message,BLACK);
        sprintf(message,"ytest = %d  ",datap[5]);
        LCD_writeString(5,50,message,RED);
        */
        
        //                                   LCD_drawCross(xacc,yacc,MAGENTA);
        
        LED = !LED;                                 //  just an indicator 
        delay();
    }
    return 0;
}

void delay(void)    {                               //  delay function
    _CP0_SET_COUNT(0);
    while   (_CP0_GET_COUNT()<DELAYTIME)  {;}
}