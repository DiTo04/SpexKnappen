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
  int length1 = 15; // the number of notes
  char notes1[] = "ccggaagffeeddc "; // a space represents a rest
  int beats1[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
  int tempo1 = 300;
  if(SongNr == 1){
    for (int i = 0; i < length1; i++) {
        if (notes1[i] == ' ') {
          delay(beats1[i] * tempo1); // rest
        } else {
          playNote(notes1[i], beats1[i] * tempo1);
        }
    
        // pause between notes
        delay(tempo1 / 2); 
    }
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
