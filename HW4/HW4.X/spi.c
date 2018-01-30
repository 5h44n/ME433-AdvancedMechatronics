// SPI initialization and basic communication functionality
// Shaan Savarirayan
// 1.29.2018

#include <proc/p32mx250f128b.h>
#include "spi.h"

#define CS LATBbits.LATB15  // chip select pin


//  SPI initialization function
void initSPI1(void) {
    SPI1CON = 0;                            // turn off and reset SPI
    SDI1Rbits.SDI1R = 0100;                 //  B8 is SDI
    SS1Rbits.SS1R = 0000;                   //  A0 is SS1 (not used)
    
    TRISAbits.TRISA0 = 0;                   // set SS1 to output
    ANSELAbits.ANSA0 = 0;                   // set SS1 to digital
    LATAbits.LATA0 = 1;                     // initialize SS1 as high 
    
    SPI1BUF;                                // clear rx buffer by reading from it
    SPI1BRG = 0x1;                          // fastest baud rate, 20 MHz [SPI1BRG = (80000000/2*desired)-1]
    SPI1STATbits.SPIROV = 0;                // clear overflow bit
    SPI1CONbits.ON = 1;                     // turn on SPI1
   
}

// SPI communication functions

// general SPI communication, reading the rx buffer
unsigned char spi_io(unsigned char o) {
  SPI1BUF = o;
  while(!SPI1STATbits.SPIRBF) {             // wait to receive the byte
    ;
  }
  return SPI1BUF;
}

// communication function tailored to MCP4902 DAC 
unsigned short MCPdata(unsigned short channel, unsigned short data) {
    unsigned short mcpdata;
    mcpdata = 0;                        // initialize data as 0
    mcpdata = (mcpdata | data) << 4;    // melds mcpdata and data, shifting data to most significant bits
    set
}

// sets channel and voltage using MCPdata
void setVoltage(char channel, char voltage) {
    CS = 0;                             // initialize chip select as low to begin communication
    
    
    
}

