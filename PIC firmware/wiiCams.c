/*
 * Wii Remote IR sensor  test sample code  by kako
 * modified output for Wii-BlobTrack program by RobotFreak
 * adapted for use with the PIC18F97J94 by Tyler Holmes
 *
 *
 *
 */

#include "wiiCams.h"
#include "UART.h"
#include "LCD.h"

#define CANDLE_TOLERANCE 5

/*
 * http://procrastineering.blogspot.com/2008/09/working-with-pixart-camera-directly.html
 *
 * This yeilds one sample from the camera containing 12 bytes, 3 for each of the
 * 4 potential points. The format of the data will be the Extended Mode
 * (X,Y, Y 2-msb, X 2-msb, Size 4-bits)
 *
 */

signed char wiiCams_init() {

    signed char retVal = 0;

 //////////////////////////// LEFT WII CAM INITIALIZATION /////////////////////

    disableInterrupts();
    I2C_open(WII_CAM_LEFT);
    retVal += I2C_write(WII_CAM_LEFT, WII_CAM_ADR);
    retVal += I2C_write(WII_CAM_LEFT, 0x30);
    retVal += I2C_write(WII_CAM_LEFT, 0x01);
    I2C_close(WII_CAM_LEFT);
    if(retVal != 0)
        return -1;//retVal;

    enableInterrupts();
    delay_ms(100);
    disableInterrupts();

    I2C_open(WII_CAM_LEFT);
    retVal += I2C_write(WII_CAM_LEFT, WII_CAM_ADR);
    retVal += I2C_write(WII_CAM_LEFT, 0x00);
    retVal += I2C_write(WII_CAM_LEFT, 0x00);
    retVal += I2C_write(WII_CAM_LEFT, 0x00);
    retVal += I2C_write(WII_CAM_LEFT, 0x00);
    retVal += I2C_write(WII_CAM_LEFT, 0x00);
    retVal += I2C_write(WII_CAM_LEFT, 0x00);
    retVal += I2C_write(WII_CAM_LEFT, 0x00);
    retVal += I2C_write(WII_CAM_LEFT, 0x90);
    I2C_close(WII_CAM_LEFT);
    if(retVal != 0)
        return -2;//retVal;

    enableInterrupts();
    delay_ms(100);
    disableInterrupts();

    I2C_open(WII_CAM_LEFT);
    retVal += I2C_write(WII_CAM_LEFT, WII_CAM_ADR);
    retVal += I2C_write(WII_CAM_LEFT, 0x07);
    retVal += I2C_write(WII_CAM_LEFT, 0x00);
    retVal += I2C_write(WII_CAM_LEFT, 0x41);
    I2C_close(WII_CAM_LEFT);
    if(retVal != 0)
        return -3;//retVal;

    enableInterrupts();
    delay_ms(100);
    disableInterrupts();

    I2C_open(WII_CAM_LEFT);
    retVal += I2C_write(WII_CAM_LEFT, WII_CAM_ADR);
    retVal += I2C_write(WII_CAM_LEFT, 0x1A);
    retVal += I2C_write(WII_CAM_LEFT, 0x40);
    retVal += I2C_write(WII_CAM_LEFT, 0x00);
    I2C_close(WII_CAM_LEFT);
    if(retVal != 0)
        return -4;//retVal;

    enableInterrupts();
    delay_ms(100);
    disableInterrupts();

    I2C_open(WII_CAM_LEFT);
    retVal += I2C_write(WII_CAM_LEFT, WII_CAM_ADR);
    retVal += I2C_write(WII_CAM_LEFT, 0x33);
    retVal += I2C_write(WII_CAM_LEFT, 0x03);
    I2C_close(WII_CAM_LEFT);
    if(retVal != 0)
        return -5;//retVal;

    enableInterrupts();
    delay_ms(100);
    disableInterrupts();

    I2C_open(WII_CAM_LEFT);
    retVal += I2C_write(WII_CAM_LEFT, WII_CAM_ADR);
    retVal += I2C_write(WII_CAM_LEFT, 0x30);
    retVal += I2C_write(WII_CAM_LEFT, 0x08);
    I2C_close(WII_CAM_LEFT);
    if(retVal != 0)
        return -6;//retVal;

    enableInterrupts();
    delay_ms(100);
    disableInterrupts();



 //////////////////////////// RIGHT WII CAM INITIALIZATION /////////////////////

    disableInterrupts();
    I2C_open(WII_CAM_RIGHT);
    retVal += I2C_write(WII_CAM_RIGHT, WII_CAM_ADR);
    retVal += I2C_write(WII_CAM_RIGHT, 0x30);
    retVal += I2C_write(WII_CAM_RIGHT, 0x01);
    I2C_close(WII_CAM_RIGHT);
    if(retVal != 0)
        return -7;//retVal;

    enableInterrupts();
    delay_ms(100);
    disableInterrupts();

    I2C_open(WII_CAM_RIGHT);
    retVal += I2C_write(WII_CAM_RIGHT, WII_CAM_ADR);
    retVal += I2C_write(WII_CAM_RIGHT, 0x00);
    retVal += I2C_write(WII_CAM_RIGHT, 0x00);
    retVal += I2C_write(WII_CAM_RIGHT, 0x00);
    retVal += I2C_write(WII_CAM_RIGHT, 0x00);
    retVal += I2C_write(WII_CAM_RIGHT, 0x00);
    retVal += I2C_write(WII_CAM_RIGHT, 0x00);
    retVal += I2C_write(WII_CAM_RIGHT, 0x00);
    retVal += I2C_write(WII_CAM_RIGHT, 0x90);
    I2C_close(WII_CAM_RIGHT);
    if(retVal != 0)
        return -8;//retVal;

    enableInterrupts();
    delay_ms(100);
    disableInterrupts();

    I2C_open(WII_CAM_RIGHT);
    retVal += I2C_write(WII_CAM_RIGHT, WII_CAM_ADR);
    retVal += I2C_write(WII_CAM_RIGHT, 0x07);
    retVal += I2C_write(WII_CAM_RIGHT, 0x00);
    retVal += I2C_write(WII_CAM_RIGHT, 0x41);
    I2C_close(WII_CAM_RIGHT);
    if(retVal != 0)
        return -9;//retVal;

    enableInterrupts();
    delay_ms(100);
    disableInterrupts();

    I2C_open(WII_CAM_RIGHT);
    retVal += I2C_write(WII_CAM_RIGHT, WII_CAM_ADR);
    retVal += I2C_write(WII_CAM_RIGHT, 0x1A);
    retVal += I2C_write(WII_CAM_RIGHT, 0x40);
    retVal += I2C_write(WII_CAM_RIGHT, 0x00);
    I2C_close(WII_CAM_RIGHT);
    if(retVal != 0)
        return -10;//retVal;

    enableInterrupts();
    delay_ms(100);
    disableInterrupts();

    I2C_open(WII_CAM_RIGHT);
    retVal += I2C_write(WII_CAM_RIGHT, WII_CAM_ADR);
    retVal += I2C_write(WII_CAM_RIGHT, 0x33);
    retVal += I2C_write(WII_CAM_RIGHT, 0x03);
    I2C_close(WII_CAM_RIGHT);
    if(retVal != 0)
        return -11;//retVal;

    enableInterrupts();
    delay_ms(100);
    disableInterrupts();

    I2C_open(WII_CAM_RIGHT);
    retVal += I2C_write(WII_CAM_RIGHT, WII_CAM_ADR);
    retVal += I2C_write(WII_CAM_RIGHT, 0x30);
    retVal += I2C_write(WII_CAM_RIGHT, 0x08);
    I2C_close(WII_CAM_RIGHT);
    if(retVal != 0)
        return -12;//retVal;

    enableInterrupts();
    delay_ms(100);
    disableInterrupts();

    return retVal;

}


signed char wiiCams_read(unsigned char camera, unsigned char *rawData) {

    signed char retVal;

    I2C_open(camera);
    retVal = I2C_write(camera, WII_CAM_ADR);
    retVal += I2C_write(camera, 0x37);
    I2C_close(camera);

    enableInterrupts();
    delay_us(25);
    disableInterrupts();

    I2C_open(camera);
    retVal += I2C_write(camera, WII_CAM_ADR | 0x01);
    for(unsigned char i = 0; i < 7; i++) {
        retVal += I2C_read(camera, (rawData + i), ACK);
    }
    retVal += I2C_read(camera, rawData + 7, NAK);
    I2C_close(camera);

    enableInterrupts();
    delay_us(25);
    disableInterrupts();

    I2C_open(camera);
    retVal += I2C_write(camera, WII_CAM_ADR | 0x01);
    for(unsigned char i = 8; i < 11; i++) {
        retVal += I2C_read(camera, (rawData + i), ACK);
    }
    retVal += I2C_read(camera, rawData + 11, NAK);
    I2C_close(camera);

    return retVal;
}

/*
 * This yeilds one sample from the camera containing 12 bytes, 3 for each of the
 * 4 potential points. The format of the data will be the Extended Mode
 * (X,Y, Y 2-msb, X 2-msb, Size 4-bits)
 *
 */



void wiiCams_processData(unsigned char *rawData, int *processedData) {

    processedData[0] = rawData[0] | ((rawData[2] & 0b00110000) << 4);   // x1
    processedData[1] = rawData[1] | ((rawData[2] & 0b11000000) << 2);   // y1
    processedData[2] = rawData[2] & 0x0F;                               // size1

    processedData[3] = rawData[3] | ((rawData[5] & 0b00110000) << 4);   // x2
    processedData[4] = rawData[4] | ((rawData[5] & 0b11000000) << 2);   // y2
    processedData[5] = rawData[5] & 0x0F;                               // size2

    processedData[6] = rawData[6] | ((rawData[8] & 0b00110000) << 4);   // x3
    processedData[7] = rawData[7] | ((rawData[8] & 0b11000000) << 2);   // y3
    processedData[8] = rawData[8] & 0x0F;                               // size3

    processedData[9] = rawData[9] | ((rawData[11] & 0b00110000) << 4);  // x4
    processedData[10] = rawData[10] | ((rawData[11] & 0b11000000) << 2);// y4
    processedData[11] = rawData[11] & 0x0F;                             // size4
}

void wiiCams_sendData(int *processedData, unsigned char keyFrame) {

    if(keyFrame == 1) {
        UART_transmitByte(USB, (char)42);
        UART_transmitByte(USB, (char)42);
    }
    UART_transmitByte(USB, ((processedData[0]  >> 2) & 0x00FF) );
    UART_transmitByte(USB, ((processedData[1]  >> 2) & 0x00FF) );
    UART_transmitByte(USB, ((processedData[3]  >> 2) & 0x00FF) );
    UART_transmitByte(USB, ((processedData[4]  >> 2) & 0x00FF) );
    UART_transmitByte(USB, ((processedData[6]  >> 2) & 0x00FF) );
    UART_transmitByte(USB, ((processedData[7]  >> 2) & 0x00FF) );
    UART_transmitByte(USB, ((processedData[9]  >> 2) & 0x00FF) );
    UART_transmitByte(USB, ((processedData[10] >> 2) & 0x00FF) );
}

void wiiCams_findCandle(int *processedDataL, int *processedDataR,
        unsigned char angle, unsigned char *x, unsigned char *y, unsigned char *z) {

    unsigned char leftBlob = 0;
    unsigned char rightBlob = 0;

    for(char i = 0; i < 4; i++)
    {
        if(processedDataL[3*i+1] < 1023)
        {
            for(char x = 0; x < 4; x++)
            {
                if(processedDataL[3*i+1] >= processedDataR[3*x+1] - CANDLE_TOLERANCE ||
                        processedDataL[3*i+1] >= processedDataR[3*x+1] + CANDLE_TOLERANCE )
                {
                    leftBlob = i;
                    rightBlob = x;
                    break;
                }
            }
        }
        if(leftBlob != 0) {
            break;
        }
    }
    enableInterrupts();
    if(leftBlob != 0) {
        LCD_printString(0, 0, "CANDLE: \nDETECTED");
    }
    else {
        LCD_printString(0, 0, "No \n Candle");
    }
    disableInterrupts(); 
}

    // do math with theta, processedDataL[3*leftBlob] (x1),
    // processedDataL[3*leftBlob + 1] (y1), processedDataL[3*rightBlob] (x2),
    // processedDataR[3*rightBlob + 1] (y2)



/*

 Debug code:

unsigned char rawDataL[12];
unsigned char rawDataR[12];
int processedDataL[12];
int processedDataR[12];

 signed char retVal = 0;
    while(1) {
        disableInterrupts();
        retVal = wiiCams_read(WII_CAM_LEFT, rawDataL);
        retVal += wiiCams_read(WII_CAM_RIGHT, rawDataR);
        wiiCams_processData(rawDataL, processedDataL);
        wiiCams_processData(rawDataR, processedDataR);
        enableInterrupts();
        if(retVal != 0) {
            LCD_printString(0, 0, "wii Cam\nreadFail");
            UART_transmitString(USB, "FAILURE");
        }
        else {
            UART_transmitString(USB, " ___1___  ___2___\n\r");
            for(unsigned char i = 0; i < 4; i++) {
                UART_transmitString(USB, "(%i, ", (int)processedDataL[3*i]);
                UART_transmitString(USB, "%i)  ", (int)processedDataL[3*i + 1]);
                UART_transmitString(USB, "s: %i  ", (int)processedDataL[3*i + 2]);

                UART_transmitString(USB, "(%i, ", (int)processedDataR[3*i]);
                UART_transmitString(USB, "%i)  ", (int)processedDataR[3*i + 1]);
                UART_transmitString(USB, "s: %i  \n\r", (int)processedDataR[3*i + 2]);
            }
            wiiCams_sendData(processedDataL, ACK);
            wiiCams_sendData(processedDataR, NAK);
        }
        delay_ms(10);
    }


 */