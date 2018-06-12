#ifndef LSM6DS33_H
#define	LSM6DS33_H

#define ADD 0b1101010               // 7 bit imu chip address, weridly not what repo specified
#define WRITE 0                     // write bit
#define READ 1                      // read bit

void LSM6DS33_init(void);
unsigned char IMU_getValue(unsigned char);

#endif	/* LSM6DS33_H */
