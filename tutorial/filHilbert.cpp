/*	Gamma - Generic processing library
	See COPYRIGHT file for authors and license information
	
	Tutorial:		Filter / Hilbert
	Description:	This demonstrates how one can frequency shift a signal
					by using a Hilbert transform. This is as good of an
					approximation as one can get starting from a real-valued
					signal.
*/

#include "tutorial.h"

LFO<> osc(100);
LFO<> shiftMod(0.1);
Hilbert<> hil;
Quadra<> shifter(100);

void audioCB(AudioIOData& io){
	using namespace gam::rnd;
	for(unsigned i=0; i<io.framesPerBuffer(); i++){

		float s = osc.up()*0.1;

		// The Hilbert transform returns a complex number
		Complex<float> c = hil(s);
		
		// Perform a frequency shift
		shifter.freq(shiftMod.hann()*1000);
		c *= shifter();
		
		// Output the real and imaginary components
		float s0 = c.r;
		float s1 = c.i;
	
		io.out(0)[i] = s0;
		io.out(1)[i] = s1;
	}
}

RUN(audioCB);
