// options.h
// options definitions for genetic algorithm
// By: Ari Brown
// Nov. 28, 2016

#ifndef OPTIONS_H_INCLUDED
#define OPTIONS_H_INCLUDED

#include "constants.h"

////////////////////////////////////////////////////////////////
//////////////////////// DEFAULT OPTIONS ///////////////////////
////////////////////////////////////////////////////////////////

extern int NOTE_AMOUNT; // per melody

extern int NUM_MELODIES; // per generation

// iterations of genetic algorithm
extern int ITERATIONS;

// amount of data available in the queue
extern int GENERATIONS_SAVED;

// musical key to compose in
extern int KEY;

// output file to save midi translatable data
extern std::string OUTPUT_FILE;

// form for melodies
extern std::string FORM_MUSIC;

// selection mechanism
extern std::string CHOOSE_MODE;

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

#endif