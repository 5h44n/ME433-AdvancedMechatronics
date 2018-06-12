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

float getTemp(unsigned char * data) {           // convert, scale temp 
    signed short x = data[1]<<8 | data[0];
    return (x/16)+25.0;
}

float readGyroX(unsigned char * data) {         // convert, scale x gyro value 
    signed short x = data[3]<<8 | data[2];
    return x*(1000.0/32767.0);
}

float readGyroY(unsigned char * data) {         // convert, scale y gyro value 
    signed short y = data[5]<<8 | data[4];
    return y*(1000.0/32767.0);
}

float readGyroZ(unsigned char * data) {         // convert, scale z gyro value 
    signed short z = data[7]<<8 | data[6];
    return z*(1000.0/32767.0);
}

float readAccX(unsigned char * data) {          // convert, scale x-acceleration 
    signed short x = data[9]<<8 | data[8];
    return x*(2.0/32767.0);
}

float readAccY(unsigned char * data) {          // convert, scale y-acceleration 
    signed short y = data[11]<<8 | data[10];
    return y*(2.0/32767.0);
}

float readAccZ(unsigned char * data) {          // convert, scale z-acceleration 
    signed short z = data[13]<<8 | data[12];
    return z*(2.0/32767.0);
}


