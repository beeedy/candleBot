/*
 * Wii Remote IR sensor  test sample code  by kako
 * modified output for Wii-BlobTrack program by RobotFreak
 * adapted for use with the PIC18F97J94 by Tyler Holmes
 *
 *
 *
 *
 *
 *
 *
 *
 */

#include "wiiCams.h"
#define INSTRUCTION_DELAY 10

/*
signed char wiiCams_init() {

    signed char retVal = 0;

    I2C_open(WII_CAM_LEFT);
    retVal = I2C_write(WII_CAM_LEFT, WII_CAM_ADR);  // call out to Wii_cam, write
    if(retVal != 0)
        return retVal;
    retVal += I2C_write(WII_CAM_LEFT, 0x30);
    retVal += I2C_write(WII_CAM_LEFT, 0x01);
    I2C_close(WII_CAM_LEFT);
    enableInterrupts();
    delay_ms(INSTRUCTION_DELAY);
    disableInterrupts();

    I2C_open(WII_CAM_LEFT);
    retVal = I2C_write(WII_CAM_LEFT, WII_CAM_ADR);  // call out to Wii_cam, write
    if(retVal != 0)
        return retVal;
    retVal += I2C_write(WII_CAM_LEFT, 0x30);
    retVal += I2C_write(WII_CAM_LEFT, 0x08);
    I2C_close(WII_CAM_LEFT);
    enableInterrupts();
    delay_ms(INSTRUCTION_DELAY);
    disableInterrupts();

    I2C_open(WII_CAM_LEFT);
    retVal = I2C_write(WII_CAM_LEFT, WII_CAM_ADR);  // call out to Wii_cam, write
    if(retVal != 0)
        return retVal;
    retVal += I2C_write(WII_CAM_LEFT, 0x06);
    retVal += I2C_write(WII_CAM_LEFT, 0x90);
    I2C_close(WII_CAM_LEFT);
    enableInterrupts();
    delay_ms(INSTRUCTION_DELAY);
    disableInterrupts();

    I2C_open(WII_CAM_LEFT);
    retVal = I2C_write(WII_CAM_LEFT, WII_CAM_ADR);  // call out to Wii_cam, write
    if(retVal != 0)
        return retVal;
    retVal += I2C_write(WII_CAM_LEFT, 0x08);
    retVal += I2C_write(WII_CAM_LEFT, 0xC0);
    I2C_close(WII_CAM_LEFT);
    enableInterrupts();
    delay_ms(INSTRUCTION_DELAY);
    disableInterrupts();

    I2C_open(WII_CAM_LEFT);
    retVal = I2C_write(WII_CAM_LEFT, WII_CAM_ADR);  // call out to Wii_cam, write
    if(retVal != 0)
        return retVal;
    retVal += I2C_write(WII_CAM_LEFT, 0x1A);
    retVal += I2C_write(WII_CAM_LEFT, 0x40);
    I2C_close(WII_CAM_LEFT);
    enableInterrupts();
    delay_ms(INSTRUCTION_DELAY);
    disableInterrupts();

    I2C_open(WII_CAM_LEFT);
    retVal = I2C_write(WII_CAM_LEFT, WII_CAM_ADR);  // call out to Wii_cam, write
    if(retVal != 0)
        return retVal;
    retVal += I2C_write(WII_CAM_LEFT, 0x33);
    retVal += I2C_write(WII_CAM_LEFT, 0x33);
    I2C_close(WII_CAM_LEFT);
    enableInterrupts();
    delay_ms(10*INSTRUCTION_DELAY);

    disableInterrupts();

 /////////////////////////// Left Wii Cam Initialized!!!!!!! ///////////////

    I2C_open(WII_CAM_RIGHT);
    retVal = I2C_write(WII_CAM_RIGHT, WII_CAM_ADR);  // call out to Wii_cam, write
    if(retVal != 0)
        return retVal;
    retVal += I2C_write(WII_CAM_RIGHT, 0x30);
    retVal += I2C_write(WII_CAM_RIGHT, 0x01);
    I2C_close(WII_CAM_RIGHT);
    enableInterrupts();
    delay_ms(INSTRUCTION_DELAY);
    disableInterrupts();

    I2C_open(WII_CAM_RIGHT);
    retVal = I2C_write(WII_CAM_RIGHT, WII_CAM_ADR);  // call out to Wii_cam, write
    if(retVal != 0)
        return retVal;
    retVal += I2C_write(WII_CAM_RIGHT, 0x30);
    retVal += I2C_write(WII_CAM_RIGHT, 0x08);
    I2C_close(WII_CAM_RIGHT);
    enableInterrupts();
    delay_ms(INSTRUCTION_DELAY);
    disableInterrupts();

    I2C_open(WII_CAM_RIGHT);
    retVal = I2C_write(WII_CAM_RIGHT, WII_CAM_ADR);  // call out to Wii_cam, write
    if(retVal != 0)
        return retVal;
    retVal += I2C_write(WII_CAM_RIGHT, 0x06);
    retVal += I2C_write(WII_CAM_RIGHT, 0x90);
    I2C_close(WII_CAM_RIGHT);
    enableInterrupts();
    delay_ms(INSTRUCTION_DELAY);
    disableInterrupts();

    I2C_open(WII_CAM_RIGHT);
    retVal = I2C_write(WII_CAM_RIGHT, WII_CAM_ADR);  // call out to Wii_cam, write
    if(retVal != 0)
        return retVal;
    retVal += I2C_write(WII_CAM_RIGHT, 0x08);
    retVal += I2C_write(WII_CAM_RIGHT, 0xC0);
    I2C_close(WII_CAM_RIGHT);
    enableInterrupts();
    delay_ms(INSTRUCTION_DELAY);
    disableInterrupts();

    I2C_open(WII_CAM_RIGHT);
    retVal = I2C_write(WII_CAM_RIGHT, WII_CAM_ADR);  // call out to Wii_cam, write
    if(retVal != 0)
        return retVal;
    retVal += I2C_write(WII_CAM_RIGHT, 0x1A);
    retVal += I2C_write(WII_CAM_RIGHT, 0x40);
    I2C_close(WII_CAM_RIGHT);
    enableInterrupts();
    delay_ms(INSTRUCTION_DELAY);
    disableInterrupts();

    I2C_open(WII_CAM_RIGHT);
    retVal = I2C_write(WII_CAM_RIGHT, WII_CAM_ADR);  // call out to Wii_cam, write
    if(retVal != 0)
        return retVal;
    retVal += I2C_write(WII_CAM_RIGHT, 0x33);
    retVal += I2C_write(WII_CAM_RIGHT, 0x33);
    I2C_close(WII_CAM_RIGHT);
    enableInterrupts();
    delay_ms(10*INSTRUCTION_DELAY);
    disableInterrupts();

 ////////////////// Right Wii Cam Initialized!!!!!!! /////////////////////////

    return retVal;
}
*/


/*
 * wiiCams_read reads the values from the given camera and stores them in the
 * array that was passed to them. The array must be 16 indeces minimum of type
 * unsigned char.
 *
 *
 */

/*

signed char wiiCams_read(unsigned char camera, int *intensityDataX,
        int *intensityDataY) {

    signed char retVal, s = 0;
    unsigned char data[16];
    disableInterrupts();
    I2C_open(camera);
    retVal = I2C_write(camera, WII_CAM_ADR);
    retVal += I2C_write(camera, 0x36);            // I'm assuming pointing the wii's clock pointer to the right place
    I2C_close(camera);
    if(retVal != 0)
        return retVal;

    I2C_open(camera);
    for(unsigned char x = 0; x < 15; x++) {
        retVal += I2C_read(camera, (data + x), ACK );          // stores data in given index of data
        if(retVal != 0) {
            I2C_close(camera);
            return retVal;
        }
    }
    retVal += I2C_read(camera, (data + 15), NAK);
    I2C_close(camera);

    if(retVal != 0)
        return retVal;
    
    intensityDataX[0] = data[1];
    intensityDataY[0] = data[2];
    s   = data[3];
    intensityDataX[0] += (s & 0x30) <<4;
    intensityDataY[0] += (s & 0xC0) <<2;

    intensityDataX[1] = data[4];
    intensityDataY[1] = data[5];
    s   = data[6];
    intensityDataX[1] += (s & 0x30) <<4;
    intensityDataY[1] += (s & 0xC0) <<2;

    intensityDataX[2] = data[7];
    intensityDataY[2] = data[8];
    s   = data[9];
    intensityDataX[2] += (s & 0x30) <<4;
    intensityDataY[2] += (s & 0xC0) <<2;

    intensityDataX[3] = data[10];
    intensityDataY[3] = data[11];
    s   = data[12];
    intensityDataX[3] += (s & 0x30) <<4;
    intensityDataY[3] += (s & 0xC0) <<2;
    enableInterrupts();
    return retVal;
}

*/

/*
 * http://procrastineering.blogspot.com/2008/09/working-with-pixart-camera-directly.html
 *
 Initialize:

write(hex): B0 30 01
wait 100ms
write(hex): B0 00 00 00 00 00 00 00 90 //sensitivity part 1
wait 100ms
write (hex): B0 07 00 41 //sensitivity part 2
wait 100ms
write(hex): B0 1A 40 00 //sensitivity part 3
wait 100ms
write(hex): B0 33 03 //sets the mode
wait 100ms
write(hex): B0 30 08
wait 100ms
 *
 *
 *
 * Reading:

write(hex): B0 37 //prepare for reading
wait 25us
write(hex): B1 //read request
read 8 bytes
wait 380us
write(hex): B1 //read request
read 4 bytes

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
        return retVal;

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
        return retVal;

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
        return retVal;

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
        return retVal;

    enableInterrupts();
    delay_ms(100);
    disableInterrupts();

    I2C_open(WII_CAM_LEFT);
    retVal += I2C_write(WII_CAM_LEFT, WII_CAM_ADR);
    retVal += I2C_write(WII_CAM_LEFT, 0x33);
    retVal += I2C_write(WII_CAM_LEFT, 0x03);
    I2C_close(WII_CAM_LEFT);
    if(retVal != 0)
        return retVal;

    enableInterrupts();
    delay_ms(100);
    disableInterrupts();

    I2C_open(WII_CAM_LEFT);
    retVal += I2C_write(WII_CAM_LEFT, WII_CAM_ADR);
    retVal += I2C_write(WII_CAM_LEFT, 0x30);
    retVal += I2C_write(WII_CAM_LEFT, 0x08);
    I2C_close(WII_CAM_LEFT);
    if(retVal != 0)
        return retVal;

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
        return retVal;

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
        return retVal;

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
        return retVal;

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
        return retVal;

    enableInterrupts();
    delay_ms(100);
    disableInterrupts();

    I2C_open(WII_CAM_RIGHT);
    retVal += I2C_write(WII_CAM_RIGHT, WII_CAM_ADR);
    retVal += I2C_write(WII_CAM_RIGHT, 0x33);
    retVal += I2C_write(WII_CAM_RIGHT, 0x03);
    I2C_close(WII_CAM_RIGHT);
    if(retVal != 0)
        return retVal;

    enableInterrupts();
    delay_ms(100);
    disableInterrupts();

    I2C_open(WII_CAM_RIGHT);
    retVal += I2C_write(WII_CAM_RIGHT, WII_CAM_ADR);
    retVal += I2C_write(WII_CAM_RIGHT, 0x30);
    retVal += I2C_write(WII_CAM_RIGHT, 0x08);
    I2C_close(WII_CAM_RIGHT);
    if(retVal != 0)
        return retVal;

    enableInterrupts();
    delay_ms(100);
    disableInterrupts();


}


signed char wiiCams_read(unsigned char camera, unsigned char *rawData) {

    /*
     *
write(hex): B0 37 //prepare for reading
wait 25us
write(hex): B1 //read request
read 8 bytes
wait 380us
write(hex): B1 //read request
read 4 bytes
     *
     */
    I2C_open(camera);
    I2C_write(camera, WII_CAM_ADR);
    I2C_write(camera, 0x37);
    I2C_close(camera);

    enableInterrupts();
    delay_us(25);
    disableInterrupts();

    I2C_open(camera);
    I2C_write(camera, WII_CAM_ADR | 0x01);
    for(unsigned char i = 0; i < 7; i++) {
        I2C_read(camera, (rawData + i), ACK);
    }
    I2C_read(camera, rawData + 7, NAK);
    I2C_close(camera);

    enableInterrupts();
    delay_us(25);
    disableInterrupts();

    I2C_open(camera);
    I2C_write(camera, WII_CAM_ADR | 0x01);
    for(unsigned char i = 8; i < 11; i++) {
        I2C_read(camera, (rawData + i), ACK);
    }
    I2C_read(camera, rawData + 11, NAK);
    I2C_close(camera);
}