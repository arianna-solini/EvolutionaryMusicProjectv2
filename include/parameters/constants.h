// constants.h
// Constant definitions for Genetic Algorithm
// By: Ari Brown
// Nov. 28, 2016

#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

////////////////////////////////////////////////////////////////
//////////////////////// MUSIC THEORY //////////////////////////
////////////////////////////////////////////////////////////////

//// notes ////
enum NotePitches 
{
        C,
        CS,
        D,
        DS,
        E,
        F,
        FS,
        G,
        GS,
        A,
        AS,
        B,
        TOTAL_PITCHES
};

// quarter note length
const float QUARTER = 0.25;

// patterns of chords defined by chord number (1-7)
const int CHORD_PATTERN_AMOUNT = 12;
const int chord_patterns [CHORD_PATTERN_AMOUNT][3] = {

        // resolving on tonic
        {4, 5, 1},
        {2, 5, 1},
        {6, 5, 1},
        {1, 5, 1},
        {5, 5, 1},

        // resolving on dominant
        {1, 5, 5},
        {1, 4, 5},
        {1, 2, 5},
        {6, 4, 5},
        {1, 1, 5},

        // predominant
        {6, 4, 2},

        // other
        {1, 2, 3}
};

//pitch 0-11
const int TWO_CHORD_AMOUNT = 1;
const int two_note_pattern[TWO_CHORD_AMOUNT][2] = {

        //sensibile che sale alla tonica
        {11,1}
        
        //se ne possono aggiungere altre
};

////////////////////////////////////////////////////////////////
//////////////////////// CHANCES ///////////////////////////////
////////////////////////////////////////////////////////////////

const float CHANCE_OF_REST = 0.1;

// make sure that these add to 1
//const float CHANCE_OF_LONG_SHORT = 0.3;
const float CHANCE_OF_LONG_SHORT = 0.6;
//const float CHANCE_OF_SHORT_LONG = 0.1;
const float CHANCE_OF_SHORT_LONG = 0.1;
//const float CHANCE_OF_SPLIT_EVEN = 0.6;
const float CHANCE_OF_SPLIT_EVEN = 0.3;

//const float SMOOTHING_CHANCE = 0.3;
const float SMOOTHING_CHANCE = 0.5;
const float RHYTHMIC_REDISTRIBUTION_CHANCE = 0.8;
const float NOTE_MUTATION_CHANCE = 0.4;

const float THEME_CHANCE = 0.8;

const int SMOOTHING_ATTEMPTS = 10;
const int RHYTHMIC_REDISTRIBUTION_ATTEMPTS = 10;

////////////////////////////////////////////////////////////////
//////////////////////// SCORING ///////////////////////////////
////////////////////////////////////////////////////////////////

// points assigned to notes in the key
const int DIATONIC_WEIGHT = 100;

// points assigned to recognizing a chord progression
const int CHORD_PROGRESSION_REWARD = 20;

// points assigned if melody starts/ends on tonic note
const int TONIC_ENDPOINTS = 30;

// points assigned to smoothness based on absolute pitch
const int SMOOTHNESS_POINTS = 1;

// points assigned to good rhytmic distribution (note or pause)
const int STRONG_BEAT_LONG = 10; // > 0.25

//points assigned to recognition of a pattern (theme)
const int THEME_POINTS = 40;
//const float MONO_CHOSEN = 5;
//const float BI_CHOSEN = 5;
//const float TRI_CHOSEN = 5;

//points assigned to sensible resolving on tonic
const int SENSIBLE_POINTS = 50;

////////////////////////////////////////////////////////////////
//////////////////////// OTHER PARAMETERS //////////////////////
////////////////////////////////////////////////////////////////

const int MONO_WINDOW = 13;
const int BI_TRI_WINDOW = 10;

const float PROG_POW_BASE = 2.0;

// mutation of melody by smoothing random segment
const int SMOOTHING_WINDOW = 4; 

// window used to combine melody segments in breeding
const int ALLELE_WINDOW = 10;

// amount of times one note can be altered rhythmically
const int RHYTHMIC_ALTERATIONS = 5;


// amount notes looked at to identify three note chord
const int CHORD_WINDOW = 4; 
// amount of notes that don't have to match in window
//const int CHORD_ERRORS = 1; 
// amount of notes that have to be distinct in window
//const int DISTINCT_NOTES = 3; 


const int MAX_CHILDREN = 40; // max amount of children a MelodyNode can have

//const int ELITIST_SIZE = 3; // num top notes in pick_from_best

const int MIDI_CORRECTION = 24; // offset to midi numbers


// enable all debugging print statements
const bool DEBUG_MODE = false;

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

#endif
