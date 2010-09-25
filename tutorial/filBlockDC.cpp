/*	Gamma - Generic processing library
	See COPYRIGHT file for authors and license information
	
	Tutorial:		Filter / BlockDC
	Description:	This shows how DC blocking can be used to eliminate
					unwanted zero/low frequencies.
*/

#include "tutorial.h"

Sine<> osc(440);		// The signal we want to hear
Sine<> oscLow(0.1);		// Unwanted low-frequency component
BlockDC<> blockDC;

Accum<> tmr(1./4,2);
int blockingOn = 1;

void audioCB(AudioIOData& io){

	for(int i=0; i<io.framesPerBuffer(); ++i){
		
		if(tmr()){
			blockingOn ^= 1;
			printf("DC blocking %s\n", blockingOn?"on":"off");
		}
		
		// Generate a sine wave plus a very low frequency oscillation
		float s = osc() + oscLow();
		
		// Do DC blocking?
		if(blockingOn) s = blockDC(s);
		
		// Simulate clipping on the DAC
		s = scl::clipS(s) * 0.2;
			
		io.out(0)[i] = io.out(1)[i] = s;
	}
}

RUN(audioCB);


