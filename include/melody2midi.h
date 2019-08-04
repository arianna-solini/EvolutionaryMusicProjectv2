// melody2midi.h
// Class outputing text file to be read by 
//	the Seq object in MaxMSP, which will convert notes to midi
// By: Ari Brown
// Date: November 28, 2016

#ifndef MELODY2MIDI_H_INCLUDED
#define MELODY2MIDI_H_INCLUDED

#include "melody.h"

// convert a melody into midi translatable data and save file
void melody2midi(Melody *melody, std::string filename);

#endif
