/* 
 * File:   i2c.h
 * Author: shaan.savarirayan
 *
 * Created on May 2, 2018
 */

#ifndef I2C_H
#define	I2C_H

void initExpander(void);
void setExpander(char pin, char level);
char getExpander(void);