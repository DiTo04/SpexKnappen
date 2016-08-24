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
	char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
	for(int i = 0; i < 8; i++) {
		playNote(names[i],500);
	}
}

void Jukebox::playNote(char note, int duration){
	char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
	int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956};
	// play the tone corresponding to the note name
	for (int i = 0; i < 8; i++) {
	  if (names[i] == note) {
	    playTone(tones[i], duration);
	  }
	}
}

void Jukebox::playTone(int tone, int duration){
	//duration *= 1000; //Convert to micro
	for(long i = 0; i<duration*1000L; i+=tone*2){
		digitalWrite(_pin,HIGH);
		delayMicroseconds(tone);
		digitalWrite(_pin,LOW);
		delayMicroseconds(tone);
	}
}
