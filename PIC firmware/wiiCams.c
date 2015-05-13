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

void wiiCams_execute(char *x, char *y)
{
    char leftData[12];
    char rightData[12];

    if(wiiCams_read(WII_CAM_LEFT, leftData) != 0 || wiiCams_read(WII_CAM_RIGHT, rightData) != 0)
    {
        *x = -1;
        *y = -1;
        return;
    }

    int cookedLeftData[12];
    int cookedRightData[12];

    wiiCams_processData(&leftData, &cookedLeftData);
    wiiCams_processData(&rightData, &cookedRightData);

    wiiCams_findCandle(&cookedLeftData, &cookedRightData, x, y);
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

    processedData[0] = 1023 - (rawData[0] | ((rawData[2] & 0b00110000) << 4));   // x1
    processedData[1] = 1023 - (rawData[1] | ((rawData[2] & 0b11000000) << 2));   // y1
    processedData[2] = rawData[2] & 0x0F;                               // size1

    processedData[3] = 1023 - (rawData[3] | ((rawData[5] & 0b00110000) << 4));   // x2
    processedData[4] = 1023 - (rawData[4] | ((rawData[5] & 0b11000000) << 2));   // y2
    processedData[5] = rawData[5] & 0x0F;                               // size2

    processedData[6] = 1023 - (rawData[6] | ((rawData[8] & 0b00110000) << 4));   // x3
    processedData[7] = 1023 - (rawData[7] | ((rawData[8] & 0b11000000) << 2));   // y3
    processedData[8] = rawData[8] & 0x0F;                               // size3

    processedData[9] = 1023 - (rawData[9] | ((rawData[11] & 0b00110000) << 4));  // x4
    processedData[10] = 1023 - (rawData[10] | ((rawData[11] & 0b11000000) << 2));// y4
    processedData[11] = rawData[11] & 0x0F;                             // size4
}

void wiiCams_sendData(unsigned char *processedData, unsigned char keyFrame) {

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
                        unsigned char *x, unsigned char *y)
{
    //These arrays could be optimized out if we do not care about all the light
    //sources we find.
    unsigned char xTemp[4];
    unsigned char yTemp[4];

    unsigned char minX = 1023;
    unsigned char minY = 1023;

    for(int i = 0; i <= 3; i++)
    {
       if(processedDataL[i*3+1] != 1023)
       {
           for(int j = 0; j <= 3; j++)
           {
               if(processedDataR[j*3+1] != 1023 && ABS((processedDataL[i*3+1] - processedDataR[j*3+1])) < WII_Y_TOLERANCE)
               {
                   //oh shit we found a match!

                   double theta1, theta2, alpha;

                   theta1 = 90 - atan2((2*processedDataL[i*3] - 1023)*TAN_FOV_2,1024);
                   theta2 = 90 - atan2((-2*processedDataR[i*3] - 1023)*TAN_FOV_2,1024);

                   alpha = WII_CAM_DISTANCE_APART * sin(theta2) / sin(180.0 - theta1 - theta2);

                   yTemp[i] = (int)(sin(theta1)*alpha);
                   xTemp[i] = (int)(WII_CAM_DISTANCE_APART - (cos(theta1)*alpha));

                   if(minY > yTemp[i])
                   {
                       minY = yTemp[i];
                       minX = xTemp[i];
                   }
               }
           }
       }
    }

    *x = minX;
    *y = minY;
}

    // do math with theta, processedDataL[3*leftBlob] (x1),
    // processedDataL[3*leftBlob + 1] (y1), processedDataL[3*rightBlob] (x2),
    // processedDataR[3*rightBlob + 1] (y2)



