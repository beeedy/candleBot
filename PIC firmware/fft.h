/*                            ____________ _____
                             |  ___|  ___|_   _|
                             | |_  | |_    | |
                             |  _| |  _|   | |
                             | |   | |     | |
                             \_|   \_|     \_/

 * File:   fft.h
 * Author: Broderick Carlin
 *
 * This file is handles the on board FFT/FHT which is responsible for taking the
 * input from an electret microphone and performing a Forier transform in real
 * time to produce a frequency spectrum chart that can be analyzed to check for
 * specific frequencies. This specific iteration has a Nyquist frequency of
 * 10KHz and has an accuracy of ~312Hz. For this application this is more that
 * adequete, however only slight modifications would need to be made to
 * drasticly increase the accuracy or frequency range, bearing in mind that
 * these changes would greatly reduce the processors performace aswell.
 *
 * -------------------------------Function List---------------------------------
 * void fft_init();
 * void fft_fix();
 * void fft_collectData();
 * void fft_execute();
 * int fft_maxFreq();
 * short fft_readBin(int);
 *
 *
 * ---------------------------Function Descriptions-----------------------------
 * void fft_init()
 *      This function is responsible for intializing the analog input in its
 *      entirety. To avoid overflows occuring during the execution of the FFT,
 *      the ADC is setup in 10bit mode even though 12bit mode is possible. For
 *      our specific purpose 10bit is more than capable of producing the results
 *      we require so switching to 12bit mode would only slow down the FFT. This
 *      function does not return any values.
 *
 * void fft_fix()
 *      This function performs the FFT calulations based off of the raw data
 *      collected from the external microphone circuitry. This function pulls
 *      its data from the global arrays containing complex numbers and
 *      overwrites the FFT data into the same arrays. Once this function has
 *      completed the two global arrays will contain the complex results that
 *      will need further computation to convert into fully real values. These
 *      complex values correspond to magnitude of frequency bins coorelating
 *      to the frequency composition of the sampled audio signal. This funtion
 *      does not directly return any values, but instead modifies the globals.
 *
 * void fft_collectData()
 *      This function records N numbers of analog values corresponding to the
 *      time domain amplitude of an audio signal being sampled by the on board
 *      microphone circuitry. The number of samples recorded is controled by the
 *      define value FFT_SIZE, and it is important to note that this value must
 *      be a power of two for optimization reasons. This function records these
 *      samples at 20KHz which then coorelates to a Nyquist frequency of 10KHz.
 *      For our specific purpose this function samples 64 values, which will
 *      allow us to achieve 32 frequency bins through the FFT. This allows us
 *      to achieve an accuracy of 10KHz / 32 = ~312Hz. This function does not
 *      directly return any values, but instead modifies the globals.
 *
 * void fft_execute()
 *      This function, when called, performs all the tasks required to execute
 *      a full FFT. This function begins by calling fft_collectData() to sample
 *      the neccessary number of audio amplitude samples, followed by a call to
 *      fft_fix() to perform the FFT on the sampled audio. Following these two
 *      calls, this function converts the magnitude and phase value for each of
 *      the frequency bins into a magnitude that can be more easily used to
 *      compare multipul frequency bins side by side. The user should only ever
 *      use this function when they want to perform a FFT as it handles all the
 *      neccessary functionality. The magnitude of each of the frequency bins is
 *      stored in the first 32 slots of the realNumbers[] array, with slot 0
 *      corresponding to low frequency and slot 31 being the highest frequency.
 *      It should be noted that the value in slot 0 is not valid data and should
 *      be ignored as it is an artifact of the FFT. This function does not
 *      directly return any values, but instead modifies the globals.
 *
 * int fft_maxFreq()
 *      This function returns the estimated fundamental frequency of the audio
 *      sample that was acted upon by the FFT. It is important that the function
 *      fft_execute() is called immedietly before this to gaurentee the accuracy
 *      of the results. This function returns the estimated fundamental 
 *      fundamental frequency in Hz and for this specific setup is only accurate
 *      to ~312Hz. Further accuracy could be achieved my interpolating between
 *      various bins, however this has not been implemented as that amount of
 *      precision is not needed for this application.
 *
 * short fft_readBin(int)
 *      This function returns a raw value that is stored in the realNumbers[]
 *      global array. The position of the bin of interested is passed to this
 *      function and must be between 1 and FFT_SIZE/2 or else this function will
 *      return 0. It is important that fft_execute() is called immedietly before
 *      this function to guarentee the accuracy of the returned value.
 *
 *
 * Originally Written by:     Tom Roberts          11/08/89
 * Made portable:             Malcolm Slaney       12/15/94 malcolm@interval.com
 * Enhanced:                  Dimitrios P. Bouras  06/14/06 dbouras@ieee.org
 * Ported to PIC18F:          Simon Inns           01/04/11
 * Modified for PIC18F97J94:  Broderick Carlin     05/07/15

Copyright (c) 2015 Broderick Carlin & Tyler Holmes

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef FFT_H
#define	FFT_H

#include <xc.h>
#include "GlobalDefines.h"
#include "delays.h"

// Definitions
#define N_WAVE      1024    // full length of SineWave[]
#define LOG2_N_WAVE 10      // log2(N_WAVE)
#define FFT_SIZE 64         // Number of samples to collect for FFT (power of 2)
    
const short SineWave[N_WAVE-N_WAVE/4] = {
      0,    201,    402,    603,    804,   1005,   1206,   1406,
   1607,   1808,   2009,   2209,   2410,   2610,   2811,   3011,
   3211,   3411,   3611,   3811,   4011,   4210,   4409,   4608,
   4807,   5006,   5205,   5403,   5601,   5799,   5997,   6195,
   6392,   6589,   6786,   6982,   7179,   7375,   7571,   7766,
   7961,   8156,   8351,   8545,   8739,   8932,   9126,   9319,
   9511,   9703,   9895,  10087,  10278,  10469,  10659,  10849,
  11038,  11227,  11416,  11604,  11792,  11980,  12166,  12353,
  12539,  12724,  12909,  13094,  13278,  13462,  13645,  13827,
  14009,  14191,  14372,  14552,  14732,  14911,  15090,  15268,
  15446,  15623,  15799,  15975,  16150,  16325,  16499,  16672,
  16845,  17017,  17189,  17360,  17530,  17699,  17868,  18036,
  18204,  18371,  18537,  18702,  18867,  19031,  19194,  19357,
  19519,  19680,  19840,  20000,  20159,  20317,  20474,  20631,
  20787,  20942,  21096,  21249,  21402,  21554,  21705,  21855,
  22004,  22153,  22301,  22448,  22594,  22739,  22883,  23027,
  23169,  23311,  23452,  23592,  23731,  23869,  24006,  24143,
  24278,  24413,  24546,  24679,  24811,  24942,  25072,  25201,
  25329,  25456,  25582,  25707,  25831,  25954,  26077,  26198,
  26318,  26437,  26556,  26673,  26789,  26905,  27019,  27132,
  27244,  27355,  27466,  27575,  27683,  27790,  27896,  28001,
  28105,  28208,  28309,  28410,  28510,  28608,  28706,  28802,
  28897,  28992,  29085,  29177,  29268,  29358,  29446,  29534,
  29621,  29706,  29790,  29873,  29955,  30036,  30116,  30195,
  30272,  30349,  30424,  30498,  30571,  30643,  30713,  30783,
  30851,  30918,  30984,  31049,  31113,  31175,  31236,  31297,
  31356,  31413,  31470,  31525,  31580,  31633,  31684,  31735,
  31785,  31833,  31880,  31926,  31970,  32014,  32056,  32097,
  32137,  32176,  32213,  32249,  32284,  32318,  32350,  32382,
  32412,  32441,  32468,  32495,  32520,  32544,  32567,  32588,
  32609,  32628,  32646,  32662,  32678,  32692,  32705,  32717,
  32727,  32736,  32744,  32751,  32757,  32761,  32764,  32766,
  32767,  32766,  32764,  32761,  32757,  32751,  32744,  32736,
  32727,  32717,  32705,  32692,  32678,  32662,  32646,  32628,
  32609,  32588,  32567,  32544,  32520,  32495,  32468,  32441,
  32412,  32382,  32350,  32318,  32284,  32249,  32213,  32176,
  32137,  32097,  32056,  32014,  31970,  31926,  31880,  31833,
  31785,  31735,  31684,  31633,  31580,  31525,  31470,  31413,
  31356,  31297,  31236,  31175,  31113,  31049,  30984,  30918,
  30851,  30783,  30713,  30643,  30571,  30498,  30424,  30349,
  30272,  30195,  30116,  30036,  29955,  29873,  29790,  29706,
  29621,  29534,  29446,  29358,  29268,  29177,  29085,  28992,
  28897,  28802,  28706,  28608,  28510,  28410,  28309,  28208,
  28105,  28001,  27896,  27790,  27683,  27575,  27466,  27355,
  27244,  27132,  27019,  26905,  26789,  26673,  26556,  26437,
  26318,  26198,  26077,  25954,  25831,  25707,  25582,  25456,
  25329,  25201,  25072,  24942,  24811,  24679,  24546,  24413,
  24278,  24143,  24006,  23869,  23731,  23592,  23452,  23311,
  23169,  23027,  22883,  22739,  22594,  22448,  22301,  22153,
  22004,  21855,  21705,  21554,  21402,  21249,  21096,  20942,
  20787,  20631,  20474,  20317,  20159,  20000,  19840,  19680,
  19519,  19357,  19194,  19031,  18867,  18702,  18537,  18371,
  18204,  18036,  17868,  17699,  17530,  17360,  17189,  17017,
  16845,  16672,  16499,  16325,  16150,  15975,  15799,  15623,
  15446,  15268,  15090,  14911,  14732,  14552,  14372,  14191,
  14009,  13827,  13645,  13462,  13278,  13094,  12909,  12724,
  12539,  12353,  12166,  11980,  11792,  11604,  11416,  11227,
  11038,  10849,  10659,  10469,  10278,  10087,   9895,   9703,
   9511,   9319,   9126,   8932,   8739,   8545,   8351,   8156,
   7961,   7766,   7571,   7375,   7179,   6982,   6786,   6589,
   6392,   6195,   5997,   5799,   5601,   5403,   5205,   5006,
   4807,   4608,   4409,   4210,   4011,   3811,   3611,   3411,
   3211,   3011,   2811,   2610,   2410,   2209,   2009,   1808,
   1607,   1406,   1206,   1005,    804,    603,    402,    201,
      0,   -201,   -402,   -603,   -804,  -1005,  -1206,  -1406,
  -1607,  -1808,  -2009,  -2209,  -2410,  -2610,  -2811,  -3011,
  -3211,  -3411,  -3611,  -3811,  -4011,  -4210,  -4409,  -4608,
  -4807,  -5006,  -5205,  -5403,  -5601,  -5799,  -5997,  -6195,
  -6392,  -6589,  -6786,  -6982,  -7179,  -7375,  -7571,  -7766,
  -7961,  -8156,  -8351,  -8545,  -8739,  -8932,  -9126,  -9319,
  -9511,  -9703,  -9895, -10087, -10278, -10469, -10659, -10849,
 -11038, -11227, -11416, -11604, -11792, -11980, -12166, -12353,
 -12539, -12724, -12909, -13094, -13278, -13462, -13645, -13827,
 -14009, -14191, -14372, -14552, -14732, -14911, -15090, -15268,
 -15446, -15623, -15799, -15975, -16150, -16325, -16499, -16672,
 -16845, -17017, -17189, -17360, -17530, -17699, -17868, -18036,
 -18204, -18371, -18537, -18702, -18867, -19031, -19194, -19357,
 -19519, -19680, -19840, -20000, -20159, -20317, -20474, -20631,
 -20787, -20942, -21096, -21249, -21402, -21554, -21705, -21855,
 -22004, -22153, -22301, -22448, -22594, -22739, -22883, -23027,
 -23169, -23311, -23452, -23592, -23731, -23869, -24006, -24143,
 -24278, -24413, -24546, -24679, -24811, -24942, -25072, -25201,
 -25329, -25456, -25582, -25707, -25831, -25954, -26077, -26198,
 -26318, -26437, -26556, -26673, -26789, -26905, -27019, -27132,
 -27244, -27355, -27466, -27575, -27683, -27790, -27896, -28001,
 -28105, -28208, -28309, -28410, -28510, -28608, -28706, -28802,
 -28897, -28992, -29085, -29177, -29268, -29358, -29446, -29534,
 -29621, -29706, -29790, -29873, -29955, -30036, -30116, -30195,
 -30272, -30349, -30424, -30498, -30571, -30643, -30713, -30783,
 -30851, -30918, -30984, -31049, -31113, -31175, -31236, -31297,
 -31356, -31413, -31470, -31525, -31580, -31633, -31684, -31735,
 -31785, -31833, -31880, -31926, -31970, -32014, -32056, -32097,
 -32137, -32176, -32213, -32249, -32284, -32318, -32350, -32382,
 -32412, -32441, -32468, -32495, -32520, -32544, -32567, -32588,
 -32609, -32628, -32646, -32662, -32678, -32692, -32705, -32717,
 -32727, -32736, -32744, -32751, -32757, -32761, -32764, -32766,
};
  

void fft_init();
void fft_fix();
void fft_collectData();
void fft_execute();
int fft_maxFreq();
short fft_readBin(int);

#endif

