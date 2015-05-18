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


void wiiCams_findCandleCords(int *processedDataL, int *processedDataR,
                        int *x, int *y)
{
    //These arrays could be optimized out if we do not care about all the light
    //sources we find.
    int xTemp[4];
    int yTemp[4];
    unsigned char pointIntensity[4];

    unsigned char minX = 1023;
    unsigned char minY = 1023;

    int xSend = 0;
    int ySend = 0;

    unsigned char candleIndex = 0;
    unsigned char pointsDetected = 0;
    unsigned char maxIntensity = 0;


    for(int i = 0; i <= 3; i++)
    {
        pointIntensity[i] = 0;  // set the array to a known value
        xTemp[i] = 0;
        yTemp[i] = 0;
    }

    for(int i = 0; i <= 3; i++)
    {
       if(processedDataL[i*3+1] != 1023)
       {
           for(int j = 0; j <= 3; j++)
           {
               //UART_transmitString(USB, "checking...\n\r");
               if(processedDataR[j*3+1] != 1023 && (ABS((processedDataL[i*3+1] - processedDataR[j*3+1])) < WII_Y_TOLERANCE))
               {
                   //oh shit we found a match!
                   pointsDetected++;
                   double theta1, theta2, alpha;

                   //UART_transmitString(USB, "found something\r");

                   //theta1 = abs(90.0 - (180.0/3.14159)*atan2(((2*processedDataL[i*3] - 1023)*TAN_FOV_2),1024));
                   //theta2 = abs(90.0 - (180.0/3.14159)*atan2(((2*processedDataR[j*3] - 1023)*TAN_FOV_2),1024));
                   
                   //alpha = (WII_CAM_DISTANCE_APART * sin((3.14159/180.0)*(theta2))) / sin((3.14159/180.0)*(180.0 - theta1 - theta2));

                   //yTemp[i] = (int)(-1)*(sin((3.14159/180.0)*theta1)*alpha);
                   //xTemp[i] = (int)(WII_CAM_DISTANCE_APART - (cos((3.14159/180.0)*theta1)*alpha));

                   //alpha = abs((WII_CAM_DISTANCE_APART * sin((3.14159/180.0)*(theta2)) * sin((3.14159/180.0)*(theta1))) / sin((3.14159/180.0)*(180.0 - theta1 - theta2)));

                   //yTemp[i] = (int)abs((sin((3.14159/180.0)*theta1)*alpha));
                   //xTemp[i] = (int)(((double)yTemp[i])*cos((3.14159/180.0)*theta1)/sin((3.14159/180.0)*theta1) - 1.25);

                   //*y = (int)abs((sin((3.14159/180.0)*theta1)*alpha));
                   //*x = (int)(((double)yTemp[i])*cos((3.14159/180.0)*theta1)/sin((3.14159/180.0)*theta1) - 1.25);
                   *y = processedDataL[i*3];
                  // *x = (processedDataL[i*3] + processedDataR[i*3]) >> 1;   // sends back average x position in the frame
                   *x = processedDataR[i*3];
                  // pointIntensity[i] = (processedDataL[i*3 + 2] + processedDataR[j*3 + 2]) >> 1;    // average intensity

                   //enableInterrupts();
                   // UART_transmitString(USB, "x: %i  y: %i          \r", *x, *y);
                   // disableInterrupts();

               }
           }
       }
    }
    /*
    if(pointsDetected == 0)
    {
        enableInterrupts();
        UART_transmitString(USB, "NO CANDLE HERE\r", xSend, ySend);
        disableInterrupts();
    }
    else {
        for(int i = 0; i <= pointsDetected; i++)
        {
            if(maxIntensity < pointIntensity[i])
            {
                maxIntensity = pointIntensity[i];
                candleIndex = i;
            }
        }
        (*y) = yTemp[candleIndex];
        (*x) = xTemp[candleIndex];

        xSend = xTemp[candleIndex];
        ySend = abs(yTemp[candleIndex]);

        enableInterrupts();
        //UART_transmitString(USB, "rawxL: %i rawxR: %i rawyL: %i rawyR: %i x: %i  y: %i \n\r",(int)processedDataL[candleIndex*3],
        //    (int)processedDataR[candleIndex*3],(int)processedDataL[candleIndex*3 + 1], (int)processedDataR[candleIndex*3 + 1], xSend, ySend);
        //UART_transmitString(USB, "x: %i  y: %i          \r", xSend, ySend);
        disableInterrupts();
    }*/
}



signed char wiiCams_findCandle(int *processedDataL, int *processedDataR)
{
    //These arrays could be optimized out if we do not care about all the light
    //sources we find.

    for(int i = 0; i <= 3; i++)
    {
       if(processedDataL[i*3+1] != 1023)
       {
           for(int j = 0; j <= 3; j++)
           {
               if(processedDataR[j*3+1] != 1023 && (ABS((processedDataL[i*3+1] - processedDataR[j*3+1])) < WII_Y_TOLERANCE))
               {
                   //oh shit we found a match!
                   return(1);
               }
           }
       }
   return(0);
   }
}


signed char wiiCams_driveToCandle()
{
    // control flow:

    //     -if it can't see the candle, look up
    //     -if it still can't see the candle, look down
    //     -grab image data
    //     -calculate angle needed to correct itself
    //     -drive a small-ish distance
    //     -check the color sensor
    //     -if it has found the circle, text
    //     -else, loop back to beginning
//    signed int candleError = 0;
//    unsigned char rawDataLeft[12], rawDataRight[12];
//    int processedDataLeft[12], processedDataRight[12];
//    signed char retVals[12];
//    int x, y = 0;
//    int rightX, leftX = 0;
//
//    motorDrive_setSpeeds(0, 0);
//
//    wiiCams_read(WII_CAM_LEFT, rawDataLeft);
//    wiiCams_read(WII_CAM_RIGHT, rawDataRight);
//
//    wiiCams_processData(rawDataLeft, processedDataLeft);
//    wiiCams_processData(rawDataRight, processedDataRight);
//
//    if( !(wiiCams_findCandle(processedDataLeft, processedDataRight)) )
//    {
//        UART_transmitByte(PIXY, 30); // move cameras up
//        delay_ms(200);
//
//        // recheck
//        wiiCams_read(WII_CAM_LEFT, rawDataLeft);
//        wiiCams_read(WII_CAM_RIGHT, rawDataRight);
//
//        wiiCams_processData(rawDataLeft, processedDataLeft);
//        wiiCams_processData(rawDataRight, processedDataRight);
//
//        if( !(wiiCams_findCandle(processedDataLeft, processedDataRight)) )
//        {
//            UART_transmitByte(PIXY, 12); // move cameras down
//            delay_ms(200);
//
//            wiiCams_read(WII_CAM_LEFT, rawDataLeft);
//            wiiCams_read(WII_CAM_RIGHT, rawDataRight);
//
//            wiiCams_processData(rawDataLeft, processedDataLeft);
//            wiiCams_processData(rawDataRight, processedDataRight);
//
//            if( !(wiiCams_findCandle(processedDataLeft, processedDataRight)) )
//            {
//                UART_transmitByte(PIXY, 20);
//                delay_ms(200);
//                wiiCams_read(WII_CAM_LEFT, rawDataLeft);
//                wiiCams_read(WII_CAM_RIGHT, rawDataRight);
//
//                wiiCams_processData(rawDataLeft, processedDataLeft);
//                wiiCams_processData(rawDataRight, processedDataRight);
//
//                if( !(wiiCams_findCandle(processedDataLeft, processedDataRight)) )
//                {
//                    // we lost the candle
//                    return(-1);
//                }
//            }
//        }
//    } // end checking if we can see the candle
//
//    UART_transmitByte(PIXY, 20);
//    delay_ms(200);
//    wiiCams_findCandleCords(processedDataLeft, processedDataRight, &rightX, &leftX);
//    candleError = rightX - (1024 - leftX);
//    //enableInterrupts();
//    //UART_transmitString(USB, "rightX: %i leftX: %i \n\r", (int)rightX, (int)leftX);
//    //UART_transmitString(USB, "candleError: %i \n\r", (int)(candleError >> 3));
//    //disableInterrupts();
//
//    motorDrive_setSpeeds(60-(candleError / 8), 60+(candleError / 8));
//    delay_ms(50);
//    //motorDrive_drive(20, 14);   // drive forward 15 cm
//
//    colorSensor_read(READ_CLEAR, retVals);
//    UART_transmitString(USB, "Color Sensor: %i \n\r", (int)(retVals[0] | (retVals[1] << 8)));
//    //delay_s(1);
//
//    if(((int)(((retVals[0] | (retVals[1] << 8))) > 700)))
//    {
//        // we've found the white circle!
//        UART_transmitString(USB, "found and got it white\n\r", (int)(retVals[0] | (retVals[1] << 8)));
//        motorDrive_setSpeeds(0, 0);
//        return(1);
//    }
//    else
//    {
//        return(0);  // we haven't found the circle yet.
//    }

    

}
