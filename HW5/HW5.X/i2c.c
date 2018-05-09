// i2c helper functions
#include<xc.h>
#include<sys/attribs.h>     // __ISR macro

#define ADD 0x20                // I2C2 7 bit address from data sheet, A2-A0 set to low
#define WRITE 0                 // write bit
#define READ 1                  // read bit

void i2c_master_setup(void) {
  I2C2BRG = 231;                // I2CBRG = [1/(2*Fsck) - PGD]*Pblck - 2 
                                // look up PGD for your PIC32
  I2C2CONbits.ON = 1;           // turn on the I2C1 module
}

// Start a transmission on the I2C bus
void i2c_master_start(void) {
    I2C2CONbits.SEN = 1;            // send the start bit
    while(I2C2CONbits.SEN) { ; }    // wait for the start bit to be sent
}

void i2c_master_restart(void) {     
    I2C2CONbits.RSEN = 1;           // send a restart 
    while(I2C2CONbits.RSEN) { ; }   // wait for the restart to clear
}

void i2c_master_send(unsigned char byte) {  // send a byte to slave
  I2C2TRN = byte;                           // if an address, bit 0 = 0 for write, 1 for read
  while(I2C2STATbits.TRSTAT) { ; }          // wait for the transmission to finish
  if(I2C2STATbits.ACKSTAT) {                // if this is high, slave has not acknowledged
  // ("I2C2 Master: failed to receive ACK\r\n");
  }
}

unsigned char i2c_master_recv(void) { // receive a byte from the slave
    I2C2CONbits.RCEN = 1;             // start receiving data
    while(!I2C2STATbits.RBF) { ; }    // wait to receive the data
    return I2C2RCV;                   // read and return the data
}

void i2c_master_ack(int val) {        // sends ACK = 0 (slave should send another byte)
                                      // or NACK = 1 (no more bytes requested from slave)
    I2C2CONbits.ACKDT = val;          // store ACK/NACK in ACKDT
    I2C2CONbits.ACKEN = 1;            // send ACKDT
    while(I2C2CONbits.ACKEN) { ; }    // wait for ACK/NACK to be sent
}

void i2c_master_stop(void) {          // send a STOP:
  I2C2CONbits.PEN = 1;                // comm is complete and master relinquishes bus
  while(I2C2CONbits.PEN) { ; }        // wait for STOP to complete
}

void initExpander(void) {
                                            //  I2C2 initialization, configures i/o expander pins
    i2c_master_start();                     
    i2c_master_send(((ADD << WRITE) | 0));  //  write
    i2c_master_send(0x00);                  //  IODIR register
    i2c_master_send(0xF0);                  //  set G0-3 = output, G4-7 = inputs
    i2c_master_stop();
}

void setExpander(char pin, char level){
    i2c_master_start();                     
    i2c_master_send(((ADD << 1) | WRITE));  //  write
    i2c_master_send(0x09);                  //  GPIO register
    i2c_master_send(level << pin);          //  write the desired level to the desired pin
    i2c_master_stop();                      
}

char getExpander(void)  {
    unsigned char result;
    i2c_master_start();
    i2c_master_send(((ADD << 1) | WRITE));  //  write
    i2c_master_send(0x09);                  //  GPIO register
    i2c_master_restart();                   
    i2c_master_send(((ADD << 1) | READ));   //  read
    result = i2c_master_recv();             //  save read data
    i2c_master_ack(1);                      //  acknowledge receipt
    i2c_master_stop();                      
    return result;
}
