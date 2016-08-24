/*
	Jukebox - A class for playing music throw a Piezo speaker.
	created by Aiman and David
*/

#include "Arduino.h"

#ifndef Jukebox_h
#define Jukebox_h

class Jukebox {
	public:
		Jukebox(int pietzoPin);
		void playMelody(int SongNr);

	private:
	    int _pin;
	    int _a;
	    int _b;
	    int _c;
	    void playTone(int tone, int duration);
};

#endif
