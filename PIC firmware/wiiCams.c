/*   _    _ _ _   ___________   _____
    | |  | (_|_) |_   _| ___ \ /  __ \
    | |  | |_ _    | | | |_/ / | /  \/ __ _ _ __ ___   ___ _ __ __ _ ___
    | |/\| | | |   | | |    /  | |    / _` | '_ ` _ \ / _ \ '__/ _` / __|
    \  /\  / | |  _| |_| |\ \  | \__/\ (_| | | | | | |  __/ | | (_| \__ \
     \/  \/|_|_|  \___/\_| \_|  \____/\__,_|_| |_| |_|\___|_|  \__,_|___/

 * File:   wiiCams.h
 * Author: Tyler Holmes and Broderick Carlin
 */

#include "wiiCams.h"

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
    {
        enableInterrupts();
        return -1;//retVal;
    }

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
    {
        enableInterrupts();
        return -2;//retVal;
    }

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
    {
        enableInterrupts();
        return -3;//retVal;
    }

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
    {
        enableInterrupts();
        return -4;//retVal;
    }

    enableInterrupts();
    delay_ms(100);
    disableInterrupts();

    I2C_open(WII_CAM_LEFT);
    retVal += I2C_write(WII_CAM_LEFT, WII_CAM_ADR);
    retVal += I2C_write(WII_CAM_LEFT, 0x33);
    retVal += I2C_write(WII_CAM_LEFT, 0x03);
    I2C_close(WII_CAM_LEFT);
    if(retVal != 0)
    {
        enableInterrupts();
        return -5;//retVal;
    }

    enableInterrupts();
    delay_ms(100);
    disableInterrupts();

    I2C_open(WII_CAM_LEFT);
    retVal += I2C_write(WII_CAM_LEFT, WII_CAM_ADR);
    retVal += I2C_write(WII_CAM_LEFT, 0x30);
    retVal += I2C_write(WII_CAM_LEFT, 0x08);
    I2C_close(WII_CAM_LEFT);
    if(retVal != 0)
    {
        enableInterrupts();
        return -6;//retVal;
    }

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
    {
        enableInterrupts();
        return -7;//retVal;
    }

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
    {
        enableInterrupts();
        return -8;//retVal;
    }

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
    {
        enableInterrupts();
        return -9;//retVal;
    }

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
    {
        enableInterrupts();
        return -10;//retVal;
    }

    enableInterrupts();
    delay_ms(100);
    disableInterrupts();

    I2C_open(WII_CAM_RIGHT);
    retVal += I2C_write(WII_CAM_RIGHT, WII_CAM_ADR);
    retVal += I2C_write(WII_CAM_RIGHT, 0x33);
    retVal += I2C_write(WII_CAM_RIGHT, 0x03);
    I2C_close(WII_CAM_RIGHT);
    if(retVal != 0)
    {
        enableInterrupts();
        return -11;//retVal;
    }

    enableInterrupts();
    delay_ms(100);
    disableInterrupts();

    I2C_open(WII_CAM_RIGHT);
    retVal += I2C_write(WII_CAM_RIGHT, WII_CAM_ADR);
    retVal += I2C_write(WII_CAM_RIGHT, 0x30);
    retVal += I2C_write(WII_CAM_RIGHT, 0x08);
    I2C_close(WII_CAM_RIGHT);
    if(retVal != 0)
    {
        enableInterrupts();
        return -12;//retVal;
    }

    enableInterrupts();
    delay_ms(100);

    return retVal;

}


signed char wiiCams_read(unsigned char camera, unsigned char *rawData)
{
    signed char retVal;

    I2C_open(camera);
    retVal = I2C_write(camera, WII_CAM_ADR);
    retVal += I2C_write(camera, 0x37);
    I2C_close(camera);

    delay_us(25);

    I2C_open(camera);
    retVal += I2C_write(camera, WII_CAM_ADR | 0x01);
    for(unsigned char i = 0; i < 7; i++) {
        retVal += I2C_read(camera, (rawData + i), ACK);
    }
    retVal += I2C_read(camera, rawData + 7, NAK);
    I2C_close(camera);

    delay_us(25);

    I2C_open(camera);
    retVal += I2C_write(camera, WII_CAM_ADR | 0x01);
    for(unsigned char i = 8; i < 11; i++) {
        retVal += I2C_read(camera, (rawData + i), ACK);
    }
    retVal += I2C_read(camera, rawData + 11, NAK);
    I2C_close(camera);

    return retVal;
}

void wiiCams_processData(unsigned char *rawData, int *processedData)
{

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

                   theta1 = 90 - atan2(((2*processedDataL[i*3] - 1023)*TAN_FOV_2),1024);
                   theta2 = 90 - atan2(((-2*processedDataR[i*3] - 1023)*TAN_FOV_2),1024);

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
}