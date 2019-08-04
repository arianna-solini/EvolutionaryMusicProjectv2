// score.cpp
// Scoring function implementation for genetic algorithm
// 	for music composition
// By: Ari Brown
// Nov. 28, 2016

#include<iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

#include "../include/parameters/options.h"
#include "../include/score.h"
#include "../include/melody.h"
#include "../include/note.h"
#include "../include/otherfuncs.h"
#include "../include/parameters/constants.h"
#include "../include/commonfuncs.h"


/* Score class default constructor 
Args: None
Return: None
*/
Score::Score()
{}

/* scores a melody line using all scoring helper functions
Args: a pointer to a Melody
Return: none
*/
Score::Score(Melody *melody)
{
	calculate(melody);
}

/* reinitalize, pass in new melody to score
Args: a pointer to a melody
Return: none
*/
void Score::reinitialize(Melody *melody)
{
	calculate(melody);
}

/* calculate the melody's score
Args: pointer to a Melody
Return: none
*/
void Score::calculate(Melody *melody)
{
	total_score = 0;
	total_score += analyze_diatonic_fit(melody);
	total_score += analyze_smoothness(melody);

	total_score += analyze_progression(melody);

	total_score += analyze_rhytmic_distribution(melody);
	total_score += analyze_theme(melody);
}

/* Score class destructor
Args: None
Return: None
*/
Score::~Score()
{
	// delete heap allocated memory
	//delete [] chord_progression;
}

/* Get the calculated score for a melody
Args: None
Return: integer score
*/
int Score::get_score()
{
	return total_score;
}

/* Assigns subscore based on the presence of a theme (or form) in the melody
Args: pointer to a Melody
Return: integer
*/
int Score::analyze_theme(Melody *melody)
{
	if(melody->get_form_used().length() != 0)
	{
		return 20*pow(PROG_POW_BASE, 7);
	}
	else
	{
		return 0;
	}
	
}

/* assigns subscore based on how many notes fit in the key
	Weight of importance of diatonic notes is defined in constants.h
Args: pointer to a Melody
Return: integer subscore
*/
int Score::analyze_diatonic_fit(Melody *melody)
{
	int score = 0;
	int mel_size = melody->get_size();

	for (int i = 0; i < mel_size; i++)
	{
		// make sure the note isn't a rest
		if (!melody->note_at(i).get_rest())
		{
			int scale_degree = melody->note_at(i).get_scale_degree();
			if (is_diatonic(scale_degree))
			{
				score += DIATONIC_WEIGHT;
			}
		}
	}
	return score;
}

int Score::analyze_progression(Melody *melody)
{
	int score = 0;

	// check start and end notes
	if (melody->note_at(0).get_scale_degree() == 0 
		&& !melody->note_at(0).get_rest()) 
		{score += TONIC_ENDPOINTS;}
	if (melody->note_at(melody->get_size() - 1).
		get_scale_degree() == 0 && !melody->
		note_at(melody->get_size() - 1).get_rest()) 
		{score += TONIC_ENDPOINTS;}

	int num_matches = 0;
	// split into 3-note windows to check against defined progressions
	for (int i = 0; i < melody->get_size() - 2; i++)
	{
		int window [3] = {melody->note_at(i).get_scale_degree(), 
			melody->note_at(i+1).get_scale_degree(),
			melody->note_at(i+2).get_scale_degree()};

		for (int j = 0; j < CHORD_PATTERN_AMOUNT; j++)
		{
			if (window[0] == chord_patterns[j][0]
				&& window[1] == chord_patterns[j][1]
				&& window[2] == chord_patterns[j][2])
			{
				// aumenta lo score in modo esponenziale quando trova una sequenza di accordi che seguono i pattern
				// = 20*2^num_match
				//--> lo valuta molto (ci può stare)
				score += 
				(CHORD_PROGRESSION_REWARD 
					* pow(PROG_POW_BASE, num_matches));
				num_matches++;
			}
		}
	}

	//check sensible note
	for (int i=0; i< melody->get_size() - 1; i++)
	{
		int window_check[2] = {melody->note_at(i).get_pitch(), melody->note_at(i+1).get_pitch()};
		for(int j=0; j < TWO_CHORD_AMOUNT; j++){
			if(window_check[0] == two_note_pattern[j][0]
			&& window_check[1]== two_note_pattern[j][1])
				score += SENSIBLE_POINTS;
		}
	}
	return score;
}

/* Assign subscore based on smoothness of note and octave
Args: pointer to a Melody
Return: integer subscore
*/
int Score::analyze_smoothness(Melody *melody)
{
	int score = 0;
	int mel_size = melody->get_size();
	for (int i = 0; i < mel_size - 1; i++) // goes til 
		// second to last note
	{
		// whole or half steps, using the keynum number
		if (!melody->note_at(i).get_rest() 
			&& !melody->note_at(i+1).get_rest()
			&& abs(melody->note_at(i).get_key_num()
			 - melody->note_at(i+1).get_key_num()) <= 2)
		{
			score += SMOOTHNESS_POINTS;
		}

	}

	return score;
}

/* Assign subscore based on a good rhytmic distribution rule (based on the fact we have a 4/4 time signature): 
	1)long duration on strong beats
	2)short duration on weak beats
Args: pointer to a melody
Return: integer
*/
int Score::analyze_rhytmic_distribution(Melody *melody)
{
	int mel_size = melody->get_size();
	int note_iterator = 0;

	int time = 0;
	int count = 0;
	int score = 0;
	while (note_iterator < mel_size)
	{
		// get the note
		Note note = melody->note_at(note_iterator);
		
		if (note.get_rest())
		{
			if(time == count*0.25 && count%2 != 0)
			{
				if(note.get_duration() > 0.25)
					score += STRONG_BEAT_LONG;
			}
			count++;
			time = time + note.get_duration();
			
		}
		else
		{
			// note on
			if(time == count*0.25 && count%2 != 0)
			{
				if(note.get_duration() > 0.25)
					score += STRONG_BEAT_LONG;
			}
			count++;
			time = time + note.get_duration();
			
		}
		note_iterator++;
		
	}
	return score;
}
