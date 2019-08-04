// otherfuncs.h
// Definitions of some simple functions
// 	that could be used in many classes
// By: Ari Brown
// Nov. 28, 2016

#ifndef OTHERFUNCS_H_INCLUDED
#define OTHERFUNCS_H_INCLUDED

// convert pitch number (0-11) to string
std::string pitch_to_string(int pitch);


int tournament_selection(int pop[], int size, int k);

// select index based on array of probabilities
int roulette_wheel(float array[], int size);

// check if a scale degree (0-11) fits in a key
bool is_diatonic(int scale_degree);

// checks if an integer is in an array of integers
bool in_array(int integer, int array[], int array_size);

// COULD BE UPDATED
// int pick_from_best(float array[], int size);

#endif