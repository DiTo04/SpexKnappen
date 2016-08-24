/*
	Jukebox - A class for playing music throw a Piezo speaker.
	created by Aiman and David
*/

#include "Arduino.h"
#include "Jukebox.h"

Jukebox::Jukebox(int pietzoPin){
	pinMode(pietzoPin, OUTPUT);
  	_pin = pietzoPin;
  	_a = 2272;
  	_b = 4545;

}

void Jukebox::playMelody(int SongNr){
	playTone(_a, 1000);
	playTone(_b, 1000);
	playTone(_a, 1000);
	playTone(_b, 1000);
}

void Jukebox::playTone(int tone, int duration){
	duration *= 1000L; //Convert to micro
	for(long i = 0; i<duration; i+=tone*2){
		digitalWrite(_pin,HIGH);
		delayMicroseconds(tone);
		digitalWrite(_pin,LOW);
		delayMicroseconds(tone);
	}
}
