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

#include "GlobalDefines.h"
#include "I2C.h"


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
    delay_ms(10);
    disableInterrupts();

    I2C_open(WII_CAM_LEFT);
    retVal = I2C_write(WII_CAM_LEFT, WII_CAM_ADR);  // call out to Wii_cam, write
    if(retVal != 0)
        return retVal;
    retVal += I2C_write(WII_CAM_LEFT, 0x30);
    retVal += I2C_write(WII_CAM_LEFT, 0x08);
    I2C_close(WII_CAM_LEFT);
    enableInterrupts();
    delay_ms(10);
    disableInterrupts();

    I2C_open(WII_CAM_LEFT);
    retVal = I2C_write(WII_CAM_LEFT, WII_CAM_ADR);  // call out to Wii_cam, write
    if(retVal != 0)
        return retVal;
    retVal += I2C_write(WII_CAM_LEFT, 0x06);
    retVal += I2C_write(WII_CAM_LEFT, 0x90);
    I2C_close(WII_CAM_LEFT);
    enableInterrupts();
    delay_ms(10);
    disableInterrupts();

    I2C_open(WII_CAM_LEFT);
    retVal = I2C_write(WII_CAM_LEFT, WII_CAM_ADR);  // call out to Wii_cam, write
    if(retVal != 0)
        return retVal;
    retVal += I2C_write(WII_CAM_LEFT, 0x08);
    retVal += I2C_write(WII_CAM_LEFT, 0xC0);
    I2C_close(WII_CAM_LEFT);
    enableInterrupts();
    delay_ms(10);
    disableInterrupts();

    I2C_open(WII_CAM_LEFT);
    retVal = I2C_write(WII_CAM_LEFT, WII_CAM_ADR);  // call out to Wii_cam, write
    if(retVal != 0)
        return retVal;
    retVal += I2C_write(WII_CAM_LEFT, 0x1A);
    retVal += I2C_write(WII_CAM_LEFT, 0x40);
    I2C_close(WII_CAM_LEFT);
    enableInterrupts();
    delay_ms(10);
    disableInterrupts();

    I2C_open(WII_CAM_LEFT);
    retVal = I2C_write(WII_CAM_LEFT, WII_CAM_ADR);  // call out to Wii_cam, write
    if(retVal != 0)
        return retVal;
    retVal += I2C_write(WII_CAM_LEFT, 0x33);
    retVal += I2C_write(WII_CAM_LEFT, 0x33);
    I2C_close(WII_CAM_LEFT);
    enableInterrupts();
    delay_ms(10);
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
    delay_ms(10);
    disableInterrupts();

    I2C_open(WII_CAM_RIGHT);
    retVal = I2C_write(WII_CAM_RIGHT, WII_CAM_ADR);  // call out to Wii_cam, write
    if(retVal != 0)
        return retVal;
    retVal += I2C_write(WII_CAM_RIGHT, 0x30);
    retVal += I2C_write(WII_CAM_RIGHT, 0x08);
    I2C_close(WII_CAM_RIGHT);
    enableInterrupts();
    delay_ms(10);
    disableInterrupts();

    I2C_open(WII_CAM_RIGHT);
    retVal = I2C_write(WII_CAM_RIGHT, WII_CAM_ADR);  // call out to Wii_cam, write
    if(retVal != 0)
        return retVal;
    retVal += I2C_write(WII_CAM_RIGHT, 0x06);
    retVal += I2C_write(WII_CAM_RIGHT, 0x90);
    I2C_close(WII_CAM_RIGHT);
    enableInterrupts();
    delay_ms(10);
    disableInterrupts();

    I2C_open(WII_CAM_RIGHT);
    retVal = I2C_write(WII_CAM_RIGHT, WII_CAM_ADR);  // call out to Wii_cam, write
    if(retVal != 0)
        return retVal;
    retVal += I2C_write(WII_CAM_RIGHT, 0x08);
    retVal += I2C_write(WII_CAM_RIGHT, 0xC0);
    I2C_close(WII_CAM_RIGHT);
    enableInterrupts();
    delay_ms(10);
    disableInterrupts();

    I2C_open(WII_CAM_RIGHT);
    retVal = I2C_write(WII_CAM_RIGHT, WII_CAM_ADR);  // call out to Wii_cam, write
    if(retVal != 0)
        return retVal;
    retVal += I2C_write(WII_CAM_RIGHT, 0x1A);
    retVal += I2C_write(WII_CAM_RIGHT, 0x40);
    I2C_close(WII_CAM_RIGHT);
    enableInterrupts();
    delay_ms(10);
    disableInterrupts();

    I2C_open(WII_CAM_RIGHT);
    retVal = I2C_write(WII_CAM_RIGHT, WII_CAM_ADR);  // call out to Wii_cam, write
    if(retVal != 0)
        return retVal;
    retVal += I2C_write(WII_CAM_RIGHT, 0x33);
    retVal += I2C_write(WII_CAM_RIGHT, 0x33);
    I2C_close(WII_CAM_RIGHT);
    enableInterrupts();
    delay_ms(10);
    disableInterrupts();

 ////////////////// Right Wii Cam Initialized!!!!!!! /////////////////////////

    return retVal;
}



/*
 * wiiCams_read reads the values from the given camera and stores them in the
 * array that was passed to them. The array must be 16 indeces minimum of type
 * unsigned char.
 *
 *
 */

signed char wiiCams_read(unsigned char camera, unsigned char *intensityData) {

    signed char retVal = 0;
    unsigned char data[16];
    I2C_open(camera);
    retVal = I2C_write(camera, WII_CAM_ADR);
    if(retVal != 0)
        return retVal;

    I2C_write(camera, 0x36);            // I'm assuming pointing the wii's clock pointer to the right place
    I2C_close(camera);

    I2C_open(camera);
    for(unsigned char x = 0; x < 15; x++) {
        I2C_read(camera, (data + x), ACK );          // stores data in given index of data
    }

    I2C_read(camera, (data + 15), NAK);
    /*
    Ix[0] = data_buf[1];
    Iy[0] = data_buf[2];
    s   = data_buf[3];
    Ix[0] += (s & 0x30) <<4;
    Iy[0] += (s & 0xC0) <<2;

    Ix[1] = data_buf[4];
    Iy[1] = data_buf[5];
    s   = data_buf[6];
    Ix[1] += (s & 0x30) <<4;
    Iy[1] += (s & 0xC0) <<2;

    Ix[2] = data_buf[7];
    Iy[2] = data_buf[8];
    s   = data_buf[9];
    Ix[2] += (s & 0x30) <<4;
    Iy[2] += (s & 0xC0) <<2;

    Ix[3] = data_buf[10];
    Iy[3] = data_buf[11];
    s   = data_buf[12];
    Ix[3] += (s & 0x30) <<4;
    Iy[3] += (s & 0xC0) <<2; */

    return retVal;
}

