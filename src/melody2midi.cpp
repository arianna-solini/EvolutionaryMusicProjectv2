// melody2midi.cpp
// Class outputing text file to be read by 
//	the Seq object in MaxMSP, which will convert notes to midi
// By: Ari Brown
// Date: November 28, 2016

#include <iostream>
#include <fstream>
using namespace std;

#include "../include/melody.h"
#include "../include/melody2midi.h"
#include "../include/note.h"
#include "../include/parameters/constants.h"
#include "../include/parameters/options.h"

/* Convert a melody line to a text file of MIDI data,
	that can then be translated by MAXMSP into midi
Args: string output filename, pointer to Melody
Return: none
*/
void melody2midi(Melody *melody, std::string filename)
{
	filename = filename + ".txt";

	const char* char_string = filename.c_str();

	// open filestream
	ofstream output(char_string, std::ofstream::out);

	int mel_size = melody->get_size();
	int note_iterator = 0;

	int time = 0; // 2000 tics => whole note

	while (note_iterator < mel_size)
	{
		// get the note
		Note note = melody->note_at(note_iterator);
		
		// if rest, increment time
		if (note.get_rest())
		{
			time = time + (int)(note.get_duration() * 2000);
		}
		// add the note if not rest
		else
		{
			// note on
			output << time << " " << 144 
			<< " " << note.get_key_num() + MIDI_CORRECTION 
			<< " " << 112 << "; " << endl;

			// note off
			output << time + (int) 
			(note.get_duration() * 2000) << " " << 144 
			<< " " << note.get_key_num() + MIDI_CORRECTION 
			<< " " << 0 << "; " << endl;

			// update time
			time += (int) (note.get_duration() * 2000);
		}
		note_iterator++;
	}

	// close the text file
	output.close();
}

