#include <xc.h>                 //  processor SFR definitions
#include <sys/attribs.h>        //  __ISR macro

// DEVCFG0
#pragma config DEBUG = OFF          //  no debugging
#pragma config JTAGEN = OFF         //  no jtag
#pragma config ICESEL = ICS_PGx1    //  use PGED1 and PGEC1
#pragma config PWP = OFF            //  no write protect
#pragma config BWP = OFF            //  no boot write protect
#pragma config CP = OFF             //  no code protect

//  DEVCFG1
#pragma config FNOSC = PRIPLL       //  use primary oscillator with pll
#pragma config FSOSCEN = OFF        //  turn off secondary oscillator
#pragma config IESO = OFF           //  no switching clocks
#pragma config POSCMOD = HS         //  high speed crystal mode
#pragma config OSCIOFNC = OFF       //  disable secondary osc
#pragma config FPBDIV = DIV_1       //  divide sysclk freq by 1 for peripheral bus clock
#pragma config FCKSM = CSDCMD       //  do not enable clock switch
#pragma config WDTPS = PS1048576    //  use slowest wdt
#pragma config WINDIS = OFF         //  wdt no window mode
#pragma config FWDTEN = OFF         //  wdt disabled
#pragma config FWDTWINSZ = WINSZ_25 //  wdt window at 25%

//  DEVCFG2 - get the sysclk clock to 48MHz from the 8MHz crystal
#pragma config FPLLIDIV = DIV_2     //  divide input clock to be in range 4-5MHz
#pragma config FPLLMUL = MUL_24     //  multiply clock after FPLLIDIV
#pragma config FPLLODIV = DIV_2     //  divide clock after FPLLMUL to get 48MHz
#pragma config UPLLIDIV = DIV_12    //  divider for the 8MHz input clock, then multiplied by 12 to get 48MHz for USB
#pragma config UPLLEN = ON          //  USB clock on


//  DEVCFG3
#pragma config USERID = 0       //  some 16bit userid, doesn't matter what
#pragma config PMDL1WAY = OFF   //  allow multiple reconfigurations
#pragma config IOL1WAY = OFF    //  allow multiple reconfigurations
#pragma config FUSBIDIO = ON    //  USB pins controlled by USB module
#pragma config FVBUSONIO = ON   //  USB BUSON controlled by USB module

#include "spi.h"                //  spi library w/ appropriate configurations
#include "waves.h"              //  wave code specific to hw4
#define DELAYTIME 25000         //  delay time of 25000 * 40 ns = 1000000 ns = 1 ms

void delay(void);

int main() {

    __builtin_disable_interrupts();

    //  set the CP0 CONFIG register to indicate that kseg0 is cacheable (0x3)
    __builtin_mtc0(_CP0_CONFIG, _CP0_CONFIG_SELECT, 0xa4210583);

    //  0 data RAM access wait states
    BMXCONbits.BMXWSDRM = 0x0;

    //  enable multi vector interrupts
    INTCONbits.MVEC = 0x1;

    //  disable JTAG to get pins back
    DDPCONbits.JTAGEN = 0;

    //  do your TRIS and LAT commands here
    /*
    TRISAbits.TRISA4 = 0;	//  A4 (LED) = output
	TRISBbits.TRISB4 = 1;	//  B4 (BUTTON) = input
	LATAbits.LATA4 = 1;		//  Turn on LED as default
    */
    init_SPI1();    //  initialize spi1
    sinwave();      //  create sin wave vector
    triwave();      //  create tri wave vector
    
    __builtin_enable_interrupts();
    
    //  loop should cycle through sin and tri vectors infinitely
    
    int sincount = 0;   //  counters to keep track of sin and tri vec indexing
    int tricount = 0;
    char channel;
    
    while(1) { 
        // send sin wave to channel A
        channel = 0;
        setVoltage(channel,sinvec[sincount]);
        
        //  send tri wave to channel B
        channel = 1;
        setVoltage(channel,trivec[tricount]);
        
        sincount++;
        tricount++;
        
        if  (sincount==SINLEN) {
            sincount = 0;       //  reset sincount to start next sin wave period 
        }
        if  (tricount==TRILEN) {
            tricount = 0;       //  reset tricount to start next tri wave period
        }
        
        delay;
    }
}

void delay(void)    {                       //  delay function using DELAYTIME
    _CP0_SET_COUNT() = 0;
    while   (_CP0_GET_COUNT<DELAYTIME)  {
        ;
    }
}
