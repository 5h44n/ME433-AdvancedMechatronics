/* 
 * File:   spi.h
 * Author: shaan.savarirayan
 *
 * Created on January 15, 2018, 6:42 PM
 */

#ifndef SPI_H
#define	SPI_H

#define CS LATAbits.LATA0  // chip select pin


void initSPI1(void);
unsigned char SPI1_io(unsigned char data);
unsigned short MCPdata(unsigned char channel, unsigned char data);
void setVoltage(char channel,unsigned char voltage);

#endif	/* SPI_H */
 
