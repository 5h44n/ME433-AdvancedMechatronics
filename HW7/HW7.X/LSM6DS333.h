#ifndef LSM6DS333_H
#define	LSM6DS333_H

#define ADD 0b1101010               // 7 bit imu chip address
#define WRITE 0                     // write bit
#define READ 1                      // read bit

void LSM6DS333_init(void);
unsigned char IMU_getValue(unsigned char r);


#endif	/* LSM6DS333_H */

