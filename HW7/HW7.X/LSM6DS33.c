// helper functions to operate LSM6DS333 chip on PIC32

#include <xc.h>                     //  processor SFR definitions
#include <sys/attribs.h>            //  __ISR macro
#include <stdio.h>
#include <stdlib.h>

#include "LSM6DS33.h"

void LSM6DS33_init(){
    ANSELBbits.ANSB2 = 0;
    ANSELBbits.ANSB3 = 0;
    i2c_master_setup();
    
    // initialize accelerometer
    i2c_master_start();
    i2c_master_send(ADD << 1 | WRITE);      //  write mode
    i2c_master_send(0x10);                  //  CTRL1_XL = 0x10 (accelerometer)
    i2c_master_send(0x82);                  //  ODR_XL = 0b1000 (1.66kHz)
                                            //  FS_XL = 0b00 (2g), BW_XL = 0b10 (100Hz)
    i2c_master_stop();
    
    // initialize gyroscope
    i2c_master_start();
    i2c_master_send(ADD << 1 | WRITE);      //  write mode
    i2c_master_send(0x11);                  //  CTRL2_G = 0x11 (gyroscope)
    i2c_master_send(0x88);                  //  ODR_G = 0b1000 (1.66kHz), FS_G = 0b10 (1000 dps)
                                            //  FS_125 = 0 (disabled), bit 0 = 0 (must set 0)
    i2c_master_stop();
    
    // initialize multi register read capability
    i2c_master_start();
    i2c_master_send(ADD << 1 | WRITE);      //  write mode
    i2c_master_send(0x12);                  //  0x12 = CTRL3_C
    i2c_master_send(0x04);                  //  default = 0x04, IF_INC = 1 (default),enables multi read
    i2c_master_stop();
}

unsigned char IMU_getValue(unsigned char r)  {
    i2c_master_start(); 
    i2c_master_send(((ADD << 1) | WRITE));  //  write mode
    i2c_master_send(r);                     
    i2c_master_restart(); 
    i2c_master_send(((ADD << 1) | READ));   //  read mode
    unsigned char v = i2c_master_recv();    
    i2c_master_ack(1);                      
    i2c_master_stop();                      
    return v;
}
