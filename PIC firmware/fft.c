#include "fft.h"

#include "LCD.h"

// Globals
short imaginaryNumbers[FFT_SIZE];
short realNumbers[FFT_SIZE];

void fft_init()
{
    // Config port as analog
    ANCON3 = 0b00100000;

    // Config to wait for SAMP and be hardware stopped
    ADCON1L = 0x70;

    // don't use scanning
    ADCSS0H = 0;

    // TAD set
    ADCON3H = 0x1;

    // configure TAD to be 64x the instruction clock ( 250KHz )
    ADCON3L = 0x54;

    // setup in 12bit mode, 14TAD per reading
    ADCON1Hbits.MODE12 = 0;

    // configure reference voltages to be the rails
    PVCFG0 = 0;
    PVCFG1 = 0;
    NVCFG0 = 0;

    // configure analog pin AN14 as an input
    ANSEL14 = 1;
    TRISHbits.TRISH6 = 1;
    ADCHS0L = 0x0E; //Sample A
    ADCHS0H = 0x0E; //Sample B

    ADCON2L = 0;

    // enable ADC
    ADON = 1;

    // give time for ADC to stabalize
    delay_us(50);
}

void fft_fix()
{
	long int mr = 0, nn, i, j, l, k, istep, n, shift;
	short qr, qi, tr, ti, wr, wi, m = 6;


	n = 1 << m;
	nn = n - 1;

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

		tr = realNumbers[m];
		realNumbers[m] = realNumbers[mr];
		realNumbers[mr] = tr;
		ti = imaginaryNumbers[m];
		imaginaryNumbers[m] = imaginaryNumbers[mr];
		imaginaryNumbers[mr] = ti;
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
				c = ((long int)wr * (long int)realNumbers[j]);
				c = c >> 14;
				b = c & 0x01;
				tr = (c >> 1) + b;

				c = ((long int)wi * (long int)imaginaryNumbers[j]);
				c = c >> 14;
				b = c & 0x01;
				tr = tr - ((c >> 1) + b);

				// ti = FIX_MPY(wr,fi[j]) + FIX_MPY(wi,fr[j]);
				c = ((long int)wr * (long int)imaginaryNumbers[j]);
				c = c >> 14;
				b = c & 0x01;
				ti = (c >> 1) + b;

				c = ((long int)wi * (long int)realNumbers[j]);
				c = c >> 14;
				b = c & 0x01;
				ti = ti + ((c >> 1) + b);

				qr = realNumbers[i];
				qi = imaginaryNumbers[i];
				qr >>= 1;
				qi >>= 1;

				realNumbers[j] = qr - tr;
				imaginaryNumbers[j] = qi - ti;
				realNumbers[i] = qr + tr;
				imaginaryNumbers[i] = qi + ti;
			}
		}

		--k;
		l = istep;
	}
}


void fft_collectData()
{
    short i = 0;

    TRISFbits.TRISF2 = 0;

    disableInterrupts();
    for (i = 0; i < FFT_SIZE; i++)
    {
        // Perform the ADC conversion
        // Select the desired ADC and start the conversion
        SAMP = 1;

        // Wait for the ADC conversion to complete

        while(!DONE);
        DONE = 0;
        
        asm("NOP\nNOP\nNOP\nNOP");

        // Get the 12-bit ADC result and adjust the virtual ground of 2.5V
        // back to 0Vs to make the input wave centered correctly around 0
        // (i.e. -128 to +127)
        //ReadADC() should return val
        realNumbers[i] =  ADCBUF0 - 512;

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
    enableInterrupts();
}


void fft_execute()
{
    fft_fix();

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

            if (realNumbers[k] >= 0) // Ensure we don't have a negative number
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

int fft_maxFreq()
{
    short maxVal = 0;
    int maxFreq = 0;

    for(int i = 1; i < 32; i++)
    {
        if(realNumbers[i] > maxVal)
        {
            maxVal = realNumbers[i];
            maxFreq = i * SAMP_FREQ / 32;
        }
    }

    return maxFreq;
}

int fft_readAnalog()
{
    return ((ADCBUF0Hbits.ADCBUF0H << 8) + (ADCBUF0Lbits.ADCBUF0L)) - 512;
}

short fft_readBin(int i)
{
    return realNumbers[i];
}
