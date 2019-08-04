// note.cpp
// Note class implementation, an abstraction
//      for the melodic composition GA
// By: Ari Brown
// Nov. 28, 2016

#include <iostream>
#include <time.h>
#include <string>
using namespace std;

#include "../include/parameters/options.h"
#include "../include/otherfuncs.h"
#include "../include/parameters/constants.h"
#include "../include/note.h"
#include "../include/commonfuncs.h"

/* Default Constructor
        * initializes note to a random pitch between 1-12
        and a random octave between 1-5
        * decides whether note is a rest based on a chance
Args: none
Return: none
*/

Note::Note()
{
        rest = decide_if_rest(CHANCE_OF_REST);
        duration = QUARTER;
        pitch = random_int(0, 11);
        //valutare se considerare solo due ottave
        octave = random_int(1, 5);
        update();
}
/* destructor
Args: None
Return: None
*/
Note::~Note()
{
        // no heap allocated memory
}
/* decide if the note is a rest
        based on a given chance (between 0 and 1)
Args: float chance value
Return: a boolean
*/

/* assignment operator
        copies info of note passed in to this class instance
Args: a reference to a note
Returns: none
*/
Note& Note::operator=(Note &note)
{
        // eliminate unnecessary work
        if (this == &note)
        {
                return *this;
        }

        // shallow copies
        rest = note.rest;
        duration = note.duration;
        pitch = note.pitch;
        octave = note.octave;
        key_num = note.key_num;
        scale_degree = note.scale_degree;

        return *this;

}

bool Note::decide_if_rest(float probability)
{
        int chance = random_int(1, 100);
        if (chance <= (int)(probability * 100)) {return true;}
        else {return false;}
}

/* computes the "key number," an arbitrary
        number used to distinctly identify notes
        based on their pitch and register, so notes
        across any range can be compared
Args: none 
Return: none (saves this number in the class)
*/
void Note::compute_key_num()
{
        // conversion to piano key numbering
        key_num = (octave * 12) - (12 - pitch);
}

void Note::mutate()
{
        if (random_int(1, 100) <= (int) (NOTE_MUTATION_CHANCE * 100))
        {
                //tipi di mutazione
                mutate(random_int(1, 7));
        }
}

/* mutate a note, randomly one of the seven types
        mutation types:
        * move note half step up or down
        * move note whole step up or down
        # move note octave up or down
        * flip whether rest
Args: integer number (1-7), signifies type of edit
Return: none
*/
void Note::mutate(int num)
{
        
        if (num <= 0 || num > 7)
        {
                throw runtime_error("no mutation type");
        }
        
        //////////// half step edit ////////
        // up
        if (num == 1) {
                if (pitch < 11) {pitch++;}
                else {pitch = 0;}
        }
        // down
        if (num == 2) {
                if (pitch > 0) {pitch--;}
                else {pitch = 11;}
        }

        //////// whole step edit /////////
        // up
        if (num == 3) {
                if (pitch < 10) {pitch += 2;}
                else if (pitch == 10) {pitch = 0;}
                else if (pitch == 11) {pitch = 1;}
        }
        // down
        if (num == 4) {
                if (pitch > 1) {pitch -= 2;}
                else if (pitch == 1) {pitch = 11;}
                else if (pitch == 0) {pitch = 10;}
        }
        
        //////////// octave edit //////////////
        // up
        if (num == 5) {
                if (octave < 5) {octave++;} 
                else {octave = 1;}
        }
        // down
        if (num == 6) {
                if (octave > 1) {octave--;}
                else {octave = 5;}
        }

        ////////// flip rest //////////
        if (num == 7 && random_int(1, 100) <= (int) 
            (CHANCE_OF_REST * 100)) {
                rest = !rest;
        }

        update(); // update equivalent key number and scale degree 
}
/* get the key number, arbitrary number
        used to compare notes by both pitch and octave
Args: none
Return: integer
*/
int Note::get_key_num()
{
        return key_num;
}

/* transpose the note by an octave
Args: direction string, "up" or "down"
Return: none
*/
void Note::transpose_oct(string direction)
{
        if (direction == "up")
        {
                octave++;
        }
        if (direction == "down")
        {
                octave--;
        }
        update();
}
/* get the note duration
        scale: whole note is 1.0
Args: none
Return: float number
*/
float Note::get_duration()
{
        return duration;
}
/* set the note duration, if the note has been altered
    less than a certain amount of times
Args: float number
Return: none
*/
void Note::set_duration(float dur)
{
         duration = dur;
}
/* get the scale degree
        the scale degree is the note number 0-11
        offset by the key, where 1 is the tonic pitch in the key
Args: none
Return: integer scale degree (0-11)
*/
int Note::get_scale_degree()
{
        return scale_degree;
}

/* given the key as defined in constants.h, determine the scale degree
Args: none
Return: none
*/
void Note::update_scale_degree()
{
        // the key is stored in constants.h, a number 0-11 
        // given the key, determine what scale degree the note is
        if (pitch >= KEY)
        {
                /*cout << "Pitch: " << pitch << endl;
                cout << "Key: " << KEY << endl;*/
                scale_degree = pitch - KEY;
        }
        if (pitch < KEY)
        {
               /*  cout << "Pitch: " << pitch << endl;
                cout << "Key: " << KEY << endl;*/
                scale_degree = 12 - (KEY - pitch);
        }
}
/* print_note, prints out the note for debugging
        format example: c#3-0.25(2 -0)
        Is a c#3 that is a quarter note,
        and it is scale degree 2 in the key of B,
        not a rest
Args: none
Return: none
*/
void Note::print_note()
{ 
        cout << pitch_to_string(pitch);
        cout << octave << " Duration: " << 
        duration << " (Rest: " << rest << ") ";
}
/* updates the key number and scale degree information
        after changes to the note
Args: none
Return: none
*/
void Note::update()
{
        compute_key_num();
        update_scale_degree();
}

/* get the pitch of a note
Args: none
Return: integer (0-11)
*/
int Note::get_pitch()
{
        return pitch;
}

/* get whether the note fits in the key's scale
Args: none
Return: boolean
*/
bool Note::get_diatonic()
{
        if (scale_degree == 0
                || scale_degree == 2
                || scale_degree == 4
                || scale_degree == 5
                || scale_degree == 7
                || scale_degree == 9
                || scale_degree == 11
                )
        {
                return true;
        }
        else
        {
                return false;
        }
}

/* set pitch
Args: int pitch (0-11)
Return: none
*/
void Note::set_pitch(int p)
{
        if (p < 0 || p > 11)
        {
                // do nothing
        }
        else
        {
                pitch = p;
                update();
        }
}

/* set octave
Args: integer octave (1-5)
Return: none
*/
void Note::set_octave(int o)
{
        if (o < 0 || o > 5)
        {
                // do not change the octave
        }
        else
        {
                octave = o;
                update();
        }
}

/* get octave
Args: none
Return: integer octave
*/
int Note::get_octave()
{
        return octave;
}

/* gets whether the note is a rest or not
Args: none
Return: boolean (true is rest)
*/
bool Note::get_rest()
{
        return rest;
}

void Note::set_key_num(int k){
    key_num = k;    
}

void Note::set_scale_degree(int s){
        scale_degree = s;
}
