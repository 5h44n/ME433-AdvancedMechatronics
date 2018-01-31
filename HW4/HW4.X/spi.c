// SPI initialization and basic communication functionality
// Shaan Savarirayan
// 1.29.2018

#include <proc/p32mx250f128b.h>
#include "spi.h"

#define CS LATBbits.LATB15  // chip select pin


//  SPI initialization function
void initSPI1(void) {
    SPI1CON = 0;                            // turns off and resets SPI
    SDI1Rbits.SDI1R = 0100;                 //  B8 is SDI
    SS1Rbits.SS1R = 0000;                   //  A0 is SS1 (not used)
    
    TRISAbits.TRISA0 = 0;                   // sets SS1 to output
    ANSELAbits.ANSA0 = 0;                   // sets SS1 to digital
    LATAbits.LATA0 = 1;                     // initializes SS1 as high 
    
    SPI1BUF;                                // clears rx buffer by reading from it
    SPI1BRG = 0x1;                          // fastest baud rate, 20 MHz [SPI1BRG = (80000000/2*desired)-1]
    SPI1STATbits.SPIROV = 0;                // clears overflow bit
    SPI1CONbits.MSTEN = 1;                  // master mode
	SPI1CONbits.CKE = 1;                    // data changes when clock goes from hi to lo
    SPI1CONbits.ON = 1;                     // turns on SPI1
   
}

// SPI communication functions

// general SPI communication, sends a byte 
unsigned char SPI1_io(unsigned char data) {
  SPI1BUF = data;
  while(!SPI1STATbits.SPIRBF) {             // waits to receive the byte
    ;
  }
  return SPI1BUF;
}

// communication function tailored to MCP4902 DAC 
unsigned short MCPdata(unsigned char channel, unsigned char data) {
    unsigned short mcpdata;                 // mcpdata is 16 bit word sent to DAC
    mcpdata = 0;                            // initialize as 0
    mcpdata = (mcpdata | data) << 4;        // melds mcpdata and data, shifting data to msb for data
    mcpdata = mcpdata | 0x7000;             // sets last three config bits to 1
    mcpdata = mcpdata | (channel << 15);    // melds mcpdata and channel, shifting channel to msb for config
    return mcpdata;                         // return mcpdata to be read
}

// sets channel and voltage using MCPdata
void setVoltage(char channel, char voltage) {           // channel: 0 = A, 1 = B
    CS = 0;                                             // initialize chip select as low to begin communication
    SPI1_io((MCPdata(channel,voltage) & 0xFF00) >> 8);  // sends the first 8 bits of 16 bit mcpdata (spi1_io reads only a byte at a time)
    SPI1_io(MCPdata(channel,voltage) & 0x00FF);         // sends second half of mcpdata
    CS = 1;                                             // chip select to high to end communication
}

