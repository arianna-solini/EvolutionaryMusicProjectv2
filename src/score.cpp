// score.cpp
// Scoring function implementation for genetic algorithm
// 	for music composition
// By: Ari Brown
// Nov. 28, 2016

#include<iostream>
#include <cstdlib>
#include <cmath>
#include <string>

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
Score::Score() {}

/* scores a melody line using all scoring helper functions
Args: a pointer to a Melody
Return: none
*/
Score::Score(Melody *melody) {
    calculate(melody);
}

/* reinitalize, pass in new melody to score
Args: a pointer to a melody
Return: none
*/
void Score::reinitialize(Melody *melody) {
    calculate(melody);
}

/* calculate the melody's score
Args: pointer to a Melody
Return: none
*/
void Score::calculate(Melody *melody) {
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
Score::~Score() {
    // delete heap allocated memory
    //delete [] chord_progression;
}

/* Get the calculated score for a melody
Args: None
Return: integer score
*/
int Score::get_score() {
    return total_score;
}

/* Assigns subscore based on the presence of a theme (or form) in the melody
Args: pointer to a Melody
Return: integer
*/
/*
int Score::analyze_theme(Melody *melody) {
    int score = 0;
    if (melody->get_form_used().length() != 0) {
        score = THEME_POINTS * pow(PROG_POW_BASE, 7); // da sostituire con num_match()
        if(melody->get_form_used() == FORM_MUSIC)
            score = score * THEME_POINTS;
    } else {
        //do nothing
    }
    return score;

}*/

int Score::analyze_theme(Melody *melody)

{

    int mono_capacity = MONO_WINDOW;
    int general_capacity = BI_TRI_WINDOW;

    float score_mono = 0;
    float score_bi = 0;
    float score_tri = 0;
    int num_match_mono = 0;
    int num_match_bi = 0;
    int num_match_tri = 0;

    int mel_size = melody->get_size();
    Note *theme_window_mono = new Note[mono_capacity];
    Note *theme_window = new Note[general_capacity];



    int k=0;

    for(int i=0; i<mono_capacity; i++){

        Note n = melody->note_at(i);
        theme_window_mono[i] = n;

    }

    //forma monopartita

    k=0;

    num_match_mono = 0;

    int first_note = mono_capacity;
    while(first_note <= mel_size)
    {
        k=0;


        int end =  first_note + mono_capacity;
        if(first_note+mono_capacity > mel_size){
            end = mel_size;
        }

        for(int j=first_note;j<end;j++)
        {
            if((melody->note_at(j).get_key_num() == theme_window_mono[k].get_key_num()) && (melody->note_at(j).get_duration() == theme_window_mono[k].get_duration()))
                num_match_mono++;

            k++;
        }
        first_note = first_note + mono_capacity;
    }

    score_mono = THEME_POINTS + (num_match_mono/4);
    score_mono =  score_mono* pow(PROG_POW_BASE, (score_mono/4));
    k=0;

    for(int i=0; i<general_capacity; i++){

        Note n = melody->note_at(i);
        theme_window[i] = n;

    }
    //forma bipartita

    //tema A

    int variationA = melody->note_at(general_capacity).get_key_num() - theme_window[0].get_key_num();

    k=1;
    for(int j=general_capacity+1;j<general_capacity*2;j++)

    {

        if(abs(melody->note_at(j).get_key_num() - theme_window[k].get_key_num()) == variationA

           && melody->note_at(j).get_duration() == theme_window[k].get_duration())

            num_match_bi++;

        k++;

    }



    delete []theme_window;

    theme_window = new Note[general_capacity];

    //tema B

    k=0;

    for(int i=(mel_size - (general_capacity*2)); i<(mel_size - general_capacity); i++){

        Note n = melody->note_at(i);
        theme_window[k] = n;

        k++;

    }

    k=0;

    int variationB = melody->note_at(mel_size - general_capacity).get_key_num() - theme_window[0].get_key_num();

    k=1;
    for(int j=(mel_size - general_capacity)+1;j<mel_size;j++)

    {

        if(abs(melody->note_at(j).get_key_num() - theme_window[k].get_key_num()) == variationB

           && melody->note_at(j).get_duration() == theme_window[k].get_duration())

            num_match_bi++;

        k++;

    }
    score_bi = THEME_POINTS + (num_match_bi/2);
    score_bi =  score_bi * pow(PROG_POW_BASE, (num_match_bi/2));
    //forma tripartita

    k=0;


    for(int i=0; i<general_capacity; i++){

        Note n = melody->note_at(i);
        theme_window[i] = n;

    }

    num_match_tri = 0;
    k=0;

    for(int j=mel_size - general_capacity;j<mel_size;j++)

    {

        if(melody->note_at(j).get_key_num() == theme_window[k].get_key_num()

           && melody->note_at(j).get_duration() == theme_window[k].get_duration())

            num_match_tri++;

        k++;



    }
    score_tri = THEME_POINTS + num_match_tri;
    score_tri =  score_tri*pow(PROG_POW_BASE, num_match_tri);


    string FORM_CONFRONTO="";
/* confronto trovo il massimo*/

    int max = 0;

    if (score_bi >= score_tri){

        max = score_bi;
        FORM_CONFRONTO="BIPARTITA";
        melody->set_form_used("BIPARTITA");
        melody->set_num_match(num_match_bi);
    }

    else{

        max = score_tri;
        FORM_CONFRONTO="TRIPARTITA";
        melody->set_form_used("TRIPARTITA");
        melody->set_num_match(num_match_tri);
    }

    if(score_mono > max){

        max = score_mono;
        FORM_CONFRONTO="MONOPARTITA";
        melody->set_form_used("MONOPARTITA");
        melody->set_num_match(num_match_mono);
    }


    if(FORM_MUSIC == FORM_CONFRONTO)

        max=max*THEME_POINTS*THEME_POINTS*THEME_POINTS;
    delete [] theme_window;
    delete [] theme_window_mono;



    return max;
}

/* assigns subscore based on how many notes fit in the key
	Weight of importance of diatonic notes is defined in constants.h
Args: pointer to a Melody
Return: integer subscore
*/
int Score::analyze_diatonic_fit(Melody *melody) {
    int score = 0;
    int mel_size = melody->get_size();

    for (int i = 0; i < mel_size; i++) {
        // make sure the note isn't a rest
        if (!melody->note_at(i).get_rest()) {
            int scale_degree = melody->note_at(i).get_scale_degree();
            if (is_diatonic(scale_degree)) {
                score += DIATONIC_WEIGHT;
            }
        }
    }
    return score;
}

int Score::analyze_progression(Melody *melody) {
    int score = 0;

    // check start and end notes
    if (melody->note_at(0).get_scale_degree() == 0
        && !melody->note_at(0).get_rest()) { score += TONIC_ENDPOINTS; }
    if (melody->note_at(melody->get_size() - 1).
            get_scale_degree() == 0 && !melody->
            note_at(melody->get_size() - 1).get_rest()) { score += TONIC_ENDPOINTS; }

    int num_matches = 0;
    // split into 3-note windows to check against defined progressions
    for (int i = 0; i < melody->get_size() - 2; i++) {
        int window[3] = {melody->note_at(i).get_scale_degree(),
                         melody->note_at(i + 1).get_scale_degree(),
                         melody->note_at(i + 2).get_scale_degree()};

        for (int j = 0; j < CHORD_PATTERN_AMOUNT; j++) {
            if (window[0] == chord_patterns[j][0]
                && window[1] == chord_patterns[j][1]
                && window[2] == chord_patterns[j][2]) {
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
    for (int i = 0; i < melody->get_size() - 1; i++) {
        int window_check[2] = {melody->note_at(i).get_pitch(), melody->note_at(i + 1).get_pitch()};
        for (int j = 0; j < TWO_CHORD_AMOUNT; j++) {
            if (window_check[0] == two_note_pattern[j][0]
                && window_check[1] == two_note_pattern[j][1])
                score += SENSIBLE_POINTS;
        }
    }
    return score;
}

/* Assign subscore based on smoothness of note and octave
Args: pointer to a Melody
Return: integer subscore
*/
int Score::analyze_smoothness(Melody *melody) {
    int score = 0;
    int mel_size = melody->get_size();
    for (int i = 0; i < mel_size - 1; i++) // goes til
        // second to last note
    {
        // whole or half steps, using the keynum number
        if (!melody->note_at(i).get_rest()
            && !melody->note_at(i + 1).get_rest()
            && abs(melody->note_at(i).get_key_num()
                   - melody->note_at(i + 1).get_key_num()) <= 2) {
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
int Score::analyze_rhytmic_distribution(Melody *melody) {
    int mel_size = melody->get_size();
    int note_iterator = 0;

    int time = 0;
    int count = 0;
    int score = 0;
    while (note_iterator < mel_size) {
        // get the note
        Note note = melody->note_at(note_iterator);

        if (note.get_rest()) {
            if (time == count * 0.25 && count % 2 != 0) {
                if (note.get_duration() > 0.25)
                    score += STRONG_BEAT_LONG;
            }
            count++;
            time = time + note.get_duration();

        } else {
            // note on
            if (time == count * 0.25 && count % 2 != 0) {
                if (note.get_duration() > 0.25)
                    score += STRONG_BEAT_LONG;
            }
            count++;
            time = time + note.get_duration();

        }
        note_iterator++;

    }
    return score;
}
