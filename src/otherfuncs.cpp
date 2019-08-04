// otherfuncs.cpp
// Implementation of some simple functions
// 	that could be used in many classes
// By: Ari Brown
// Nov. 28, 2016
#include <iostream>

using namespace std;


#include "../include/parameters/options.h"
#include "../include/otherfuncs.h"
#include "../include/parameters/constants.h"
#include "../include/commonfuncs.h"

/* Music theory lookup to convert a pitch's number
	(0-11) to a printable string
Args: integer pitch (0-11)
Return: string pitch label
*/

std::string pitch_to_string(int pitch)
{
	std::string pitch_string = "";

	// sharp keys
	if (KEY == C
		|| KEY == G
		|| KEY == D
		|| KEY == A
		|| KEY == E
		|| KEY == B)
	{
		if (pitch == 0) {pitch_string = "c";}
	        if (pitch == 1) {pitch_string = "c#";}
	        if (pitch == 2) {pitch_string = "d";}
	        if (pitch == 3) {pitch_string = "d#";}
	        if (pitch == 4) {pitch_string = "e";}
	        if (pitch == 5) {pitch_string = "f";}
	        if (pitch == 6) {pitch_string = "f#";}
	        if (pitch == 7) {pitch_string = "g";}
	        if (pitch == 8) {pitch_string = "g#";}
	        if (pitch == 9) {pitch_string = "a";}
	        if (pitch == 10) {pitch_string = "a#";}
	        if (pitch == 11) {pitch_string = "b";}
	}
      
      	// flat keys
	if (KEY == F
                || KEY == AS
                || KEY == DS
                || KEY == GS
                || KEY == CS
                || KEY == FS)
        {
		if (pitch == 0) {pitch_string = "c";}
        	if (pitch == 1) {pitch_string = "db";}
	        if (pitch == 2) {pitch_string = "d";}
	        if (pitch == 3) {pitch_string = "eb";}
	        if (pitch == 4) {pitch_string = "e";}
	        if (pitch == 5) {pitch_string = "f";}
	        if (pitch == 6) {pitch_string = "gb";}
	        if (pitch == 7) {pitch_string = "g";}
	        if (pitch == 8) {pitch_string = "ab";}
	        if (pitch == 9) {pitch_string = "a";}
	        if (pitch == 10) {pitch_string = "bb";}
	        if (pitch == 11) {pitch_string = "b";}
        }

        return pitch_string;
}

/* Picks an index given an array of probabilities,
	roulette wheel style (higher probabilities are
	more likely to get picked)
Args: array of floats and integer array size
Return: integer index
Note: array of float numbers must add to one
*/

int tournament_selection(int pop[], int size, int k) {

    int best = -1;
    for (int i = 0; i < k; i++) {
        int ind = random_int(1, size);
        if ((best == -1) || pop[ind] > pop[best])
            best = ind;

    }

    return best;
}

int roulette_wheel(float array[], int size)
{
	// resolution of chance: 100000
	int chance = random_int(1, 100000);
	
	int counter = 0;
	int slice_sum = 0;

	// select index as if each chance had proportional
	// windows that added to 100000
	bool done = false;
	while (!done)
	{
		slice_sum += (int)(array[counter] * 100000.0);
		counter++;
		done = (slice_sum >= chance || counter >= size);
	}

	return counter-1;
}


/* Checks whether a scale degree is in the
	7 note scale of the key
Args: integer scale degree (0-11)
Return: boolean
*/
bool is_diatonic(int scale_degree)
{
	if (scale_degree == 0
		|| scale_degree == 2
		|| scale_degree == 4
		|| scale_degree == 5
		|| scale_degree == 7
		|| scale_degree == 9
		|| scale_degree == 11)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/* Checks whether an integer is
	in an array of integers
Args: integer, array of integers, array size
Return: boolean
*/
bool in_array(int integer, int array[], int array_size)
{
	bool included = false;

	for (int i = 0; i < array_size; i++)
	{
		if (array[i] == integer)
		{
			included = true;
		}
	}

	return included;
}

// COULD BE UPDATED
/* picks random melody from the best 10
int pick_from_best(float array[], int size)
{
	int best[ELITIST_SIZE];
	int used = 0;

	while (used < ELITIST_SIZE)
	{
		int best_score = 0;
		int best_index = 0;
		for (int i = 0; i < size; i++)
		{	
			// check if the index is already in top 10
			bool found = false;
			for (int j = 0; j < used; j++)
			{
				if (i == best[j])
				{
					found = true;
				}
			}

			if (!found && (int) (array[i] * 100000) > best_score)
			{
				best_index = i;
				best_score = (int) (array[i] * 100000);
			}
		}
		best[used] = best_index;
		used++;
	}

	int pick = random_int(0, ELITIST_SIZE - 1);
	return best[pick];
}*/
