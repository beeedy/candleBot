/* 
 * File:   i2c.h
 * Author: froe0466
 *
 * Created on April 22, 2015, 8:05 AM
 */

#ifndef I2C_JIMMY_H
#define	I2C_JIMMY_H

#ifdef	__cplusplus
extern "C" {
#endif

void i2c_Port_Init (void);
void i2c_Init(void);
void i2c_Wait(void);
void i2c_Start(void);
void i2c_Restart(void);
void i2c_Stop(void);
void i2c_Write(unsigned char data);
void i2c_Command(unsigned char deviceAddress,unsigned char reg, unsigned char command);
char i2c_Read(unsigned char deviceAddress, unsigned char reg);

#ifdef	__cplusplus
}
#endif

#endif	/* I2C_JIMMY_H */

