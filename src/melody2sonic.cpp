// melody2sonic.cpp
// By: Laura&Aria
// Date: May 8, 2019

#include <iostream>
#include <fstream>
using namespace std;

#include "../include/melody.h"
#include "../include/melody2sonic.h"
#include "../include/note.h"
#include "../include/parameters/constants.h"
#include "../include/parameters/options.h"

/* Convert a melody line to a text file of Sonic data,
Args: string output filename, pointer to Melody
Return: none
*/
void melody2sonic(Melody *melody, std::string filename)
{
	filename = filename + ".txt";

	const char* char_string = filename.c_str();

	// open filestream
	ofstream output(char_string, std::ofstream::out);

	int mel_size = melody->get_size();
	int note_iterator = 0;

	int time = 0; // 2000 tics => whole note

	output << "use_synth :piano" << endl;
	output << "#Forma musicale: " << melody->get_form_used() << endl;
    output << "#Num match: " << melody->get_num_match() << endl;
	while (note_iterator < mel_size)
	{
		// get the note
		Note note = melody->note_at(note_iterator);
		
		// if rest, increment time
		if (note.get_rest())
		{
			output << "#pausa" << endl;
			output << "sleep " << note.get_duration()*2 << endl;
			time = time + (int)(note.get_duration() * 2000);
		}
		// add the note if not rest
		else
		{
			// note on
			output << "play " << note.get_key_num() + MIDI_CORRECTION << ", sustain: " << note.get_duration()*2 << endl;

			output << "sleep " << note.get_duration()*2 << endl;

			time = time + note.get_duration();
			
		}
		note_iterator++;
	}

	// close the text file
	output.close();
}

