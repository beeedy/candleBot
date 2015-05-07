#include "fft.h"

#include "LCD.h"

// Globals
short imaginaryNumbers[FFT_SIZE];
short realNumbers[FFT_SIZE];

void fft_init()
{
    // Config port as analog
    ANCON3 = 0b00100000;

    // setup in 12bit mode, 14TAD per reading
    ADCON1Hbits.MODE12 = 1;

    // configure reference voltages to be the rails
    PVCFG0 = 0;
    PVCFG1 = 0;
    NVCFG0 = 0;

    // configure TAD to be 64x the instruction clock ( 250KHz )
    ADCON3L = 0x3F;

    // configure analog pin AN14 as an input
    ANSEL14 = 1;
    TRISHbits.TRISH6 = 1;
    ADCHS0L = 0x0E; //Sample A
    ADCHS0H = 0x0E; //Sample B

    // enable ADC
    ADON = 1;

    // give time for ADC to stabalize
    delay_us(50);

    LCD_printString(0,0, "Starting\nFHT");

    while(1)
    {
        SAMP = 1;
        while(!DONE);
        LCD_printString(0,0, "Ana:%i",ADCBUF0);
    }


    /*
    ADCSS0L = 0;
    ADCSS0H = 0;
    ADCSS1L = 0;
    ADCSS1H = 0;

    CSS14 = 1; // enable AN14

    CH0SA0 = 0;
    CH0SA1 = 1;
    CH0SA2 = 1;
    CH0SA3 = 1;
    CH0SA4 = 0;

    CH0NA0 = 0;
    CH0NA1 = 0;
    CH0NA2 = 0;

    ALTS = 0;


    ADRC = 1;   //Enable RC clock for A/D
    ANSEL22 = 1;
    ADON = 1; 	// Enable A/D
    MODE12 = 1;     // Set A/D to 12bit mode
    CSCNA = 1;
    FORM0 = 1;      // Read in signed decimal mode
    FORM1 = 0;
    ASAM = 1;       // Autostart conversion
    PVCFG0 = 0;     // use external AVDD for reference
    PVCFG1 = 0;
    NVCFG0 = 0;     // use external AVSS for reference
    BUFREGEN = 1;   // use specific reg for A/D
    CSCNA = 0;      // does not scan inputs
    */
}

void fft_fix(short fr[], short fi[], short m)
{
	long int mr = 0, nn, i, j, l, k, istep, n;
	short qr, qi, tr, ti, wr, wi;

        /*
	n = 1 << m;
	nn = n - 1;
        */

        nn = m - 1;

        switch(m)
        {
            case 0:
                m = 0;
                break;

            case 2:
                m = 1;
                break;

            case 4:
                m = 2;
                break;

            case 8:
                m = 3;
                break;

            case 16:
                m = 4;
                break;

            case 32:
                m = 5;
                break;

            case 64:
                m = 6;
                break;

            case 128:
                m = 7;
                break;

            case 256:
                m = 8;
                break;

            default:
                return;
        }

	/* max FFT size = N_WAVE */
	//if (n > N_WAVE) return -1;

	/* decimation in time - re-order data */
	for (m=1; m<=nn; ++m)
	{
		l = n;
		do
		{
			l >>= 1;
		} while (mr+l > nn);

		mr = (mr & (l-1)) + l;
		if (mr <= m) continue;

		tr = fr[m];
		fr[m] = fr[mr];
		fr[mr] = tr;

		ti = fi[m];
		fi[m] = fi[mr];
		fi[mr] = ti;
	}

	l = 1;
	k = LOG2_N_WAVE-1;

	while (l < n)
	{
		/*
		  fixed scaling, for proper normalization --
		  there will be log2(n) passes, so this results
		  in an overall factor of 1/n, distributed to
		  maximize arithmetic accuracy.

		  It may not be obvious, but the shift will be
		  performed on each data point exactly once,
		  during this pass.
		*/

		// Variables for multiplication code
		long int c;
		short b;

		istep = l << 1;
		for (m=0; m<l; ++m)
		{
			j = m << k;
			/* 0 <= j < N_WAVE/2 */
			wr =  SineWave[j+N_WAVE/4];
			wi = -SineWave[j];

			wr >>= 1;
			wi >>= 1;

			for (i=m; i<n; i+=istep)
			{
				j = i + l;

				// Here I unrolled the multiplications to prevent overhead
				// for procedural calls (we don't need to be clever about
				// the actual multiplications since the pic has an onboard
				// 8x8 multiplier in the ALU):

				// tr = FIX_MPY(wr,fr[j]) - FIX_MPY(wi,fi[j]);
				c = ((long int)wr * (long int)fr[j]);
				c = c >> 14;
				b = c & 0x01;
				tr = (c >> 1) + b;

				c = ((long int)wi * (long int)fi[j]);
				c = c >> 14;
				b = c & 0x01;
				tr = tr - ((c >> 1) + b);


				// ti = FIX_MPY(wr,fi[j]) + FIX_MPY(wi,fr[j]);
				c = ((long int)wr * (long int)fi[j]);
				c = c >> 14;
				b = c & 0x01;
				ti = (c >> 1) + b;


				c = ((long int)wi * (long int)fr[j]);
				c = c >> 14;
				b = c & 0x01;
				ti = ti + ((c >> 1) + b);

				qr = fr[i];
				qi = fi[i];
				qr >>= 1;
				qi >>= 1;

				fr[j] = qr - tr;
				fi[j] = qi - ti;
				fr[i] = qr + tr;
				fi[i] = qi + ti;
			}
		}

		--k;
		l = istep;
	}
}


void fft_collectData()
{
    short i = 0;

    for (i = 0; i < FFT_SIZE; i++)
    {
        // Perform the ADC conversion
        // Select the desired ADC and start the conversion

        // Wait for the ADC conversion to complete
        while(DONE == 0);

        // Get the 12-bit ADC result and adjust the virtual ground of 2.5V
        // back to 0Vs to make the input wave centered correctly around 0
        // (i.e. -512 to +512)
        //ReadADC() should return val
        realNumbers[i] =  ((ADCBUF0Hbits.ADCBUF0H << 8) + (ADCBUF0Lbits.ADCBUF0L)) - 512;

        // Set the imaginary number to zero
        imaginaryNumbers[i] = 0;

        // This delay is calibrated using an oscilloscope according to the
        // output on RA1 to ensure that the sampling periods are correct
        // given the overhead of the rest of the code and the ADC sampling
        // time.
        //
        // If you change anything in this loop or use the professional
        // (optimised) version of Hi-Tech PICC18, you will need to re-
        // calibrate this to achieve an accurate sampling rate.
        //__delay_us(7);
    }
}


void fft_execute()
{
    fft_fix(realNumbers, imaginaryNumbers, FFT_SIZE);

    // Take the absolute value of the FFT results

    // Note: The FFT routine returns 'complex' numbers which consist of
    // both a real and imaginary part.  To find the 'absolute' value
    // of the returned data we have to calculate the complex number's
    // distance from zero which requires a little pythagoras and therefore
    // a square-root calculation too.  Since the PIC has multiplication
    // hardware, only the square-root needs to be optimised.



    
    long place, root;
    for (int k=0; k < 32; k++)
    {
        realNumbers[k] = (realNumbers[k] * realNumbers[k] + imaginaryNumbers[k] * imaginaryNumbers[k]);

        // Now we find the square root of realNumbers[k] using a very
        // fast (but compiler dependent) integer approximation:
        // (adapted from: http://www.codecodex.com/wiki/Calculate_an_integer_square_root)
        place = 0x40000000;
        root = 0;

        if (realNumbers[k] > 0) // Ensure we don't have a negative number
        {
            while (place > realNumbers[k]) place = place >> 2;

            while (place)
            {
                if (realNumbers[k] >= root + place)
                {
                    realNumbers[k] -= root + place;
                    root += place * 2;
                }
                root = root >> 1;
                place = place >> 2;
            }
        }
        realNumbers[k] = root;
    }
    
}

int fft_readAnalog()
{
    return ((ADCBUF0Hbits.ADCBUF0H << 8) + (ADCBUF0Lbits.ADCBUF0L)) - 512;
}
