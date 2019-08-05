// melody.cpp
// Class containing one melody
//      for melody composition genetic algorithm
// By: Ari Brown
// Nov. 28, 2016

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <string>
using namespace std;

#include "../include/parameters/options.h"
#include "../include/melody.h"
#include "../include/commonfuncs.h"
#include "../include/parameters/constants.h"
#include "../include/otherfuncs.h"
#include "../include/GenAlgo.h"

/* initializes a new melody based on breeding
        of two parent melodies
Args: a reference to a mom melody and a reference to a dad melody
Return: none
*/

Melody::Melody(Melody &mom, Melody &dad)
{
        notes = new Note[NOTE_AMOUNT]; // template
        capacity = NOTE_AMOUNT;
        count = NOTE_AMOUNT;
        rhythmic_alteration_count = 0;
        num_match = 0;

        //form_used="BBBBBBBBBB";

        int note_counter = 0;
       /* while (note_counter < count)
        {
                int method = random_int(1, 4);

                // mom - pitch, mom - rhythm
                if (method == 1)
                {
                        copy_section(mom, note_counter, 
                            note_counter, "all", ALLELE_WINDOW);
                }
                // mom - pitch, dad - rhythm
                if (method == 2)
                {
                        copy_section(mom, note_counter, 
                            note_counter, "pitch", ALLELE_WINDOW);
                        copy_section(dad, note_counter, 
                            note_counter, "rhythm", ALLELE_WINDOW);
                }
                // mom - rhythm, dad - pitch
                if (method == 3)
                {
                        copy_section(mom, note_counter, 
                            note_counter, "rhythm", ALLELE_WINDOW);
                        copy_section(dad, note_counter, 
                            note_counter, "pitch", ALLELE_WINDOW);
                }
                // dad - pitch, dad - rhythm
                if (method == 4)
                {
                        copy_section(dad, note_counter, 
                            note_counter, "all", ALLELE_WINDOW);
                }

                note_counter += ALLELE_WINDOW;
        }*/
        int method = random_int(1,4);
        //mamma - note; padre - ritmo
        if(method == 1)
        {
                while(note_counter < count)
                {
                        notes[note_counter].set_pitch( mom.notes[note_counter].get_pitch());
                        notes[note_counter].set_octave( mom.notes[note_counter].get_octave());
                        notes[note_counter].set_duration( dad.notes[note_counter].get_duration());
                        notes[note_counter].update();
                        note_counter++;
                }
        }
        //padre - note; madre - ritmo
        if(method == 2)
        {
                while(note_counter < count)
                {
                        notes[note_counter].set_pitch( dad.notes[note_counter].get_pitch());
                        notes[note_counter].set_octave( dad.notes[note_counter].get_octave());
                        notes[note_counter].set_duration( mom.notes[note_counter].get_duration());
                        notes[note_counter].update();
                        note_counter++;
                }

        }

        //madre - tutto
        if(method == 3)
        {
                while(note_counter < count)
                {
                        notes[note_counter].set_pitch( mom.notes[note_counter].get_pitch());
                        notes[note_counter].set_octave( mom.notes[note_counter].get_octave());
                        notes[note_counter].set_duration( mom.notes[note_counter].get_duration());
                        notes[note_counter].update();
                        note_counter++;
                }
        }

        //padre - tutto
        if(method == 4)
        {
                while(note_counter < count)
                {
                        notes[note_counter].set_pitch( dad.notes[note_counter].get_pitch());
                        notes[note_counter].set_octave( dad.notes[note_counter].get_octave());
                        notes[note_counter].set_duration( dad.notes[note_counter].get_duration());
                        notes[note_counter].update();
                        note_counter++;
                }
        }

        // mutate the newly created melody
        mutate();
        
}

/* Copies a section of one melody into this instance's melody. Options:
        - copies the rhythm only
        - copies the pitch only
        - copies all of the note information
Args: Melody reference, integer start point, integer start point in this instance,
        option string: "rhythm", "pitch", or "all", and integer window size
Return: none
*/
void Melody::copy_section(Melody &parent, int parent_start, 
    int child_start, std::string option, int window)
{
        if (parent_start < 0 || parent_start >= parent.count 
            || child_start < 0 || child_start >= count)
        {
                throw runtime_error("parent or child index out of range");
        }

        int i_parent = parent_start;
        int i_child = child_start;
        while (i_parent < parent_start + window && i_parent 
            < parent.count && i_child < count)
        {
                if (option == "all")
                {
                        notes[i_child] = parent.notes[i_parent];
                }   
                if (option == "rhythm")
                {
                        notes[i_child].set_duration
                        ( parent.notes[i_parent].get_duration() );
                }  
                if (option == "pitch")
                {
                        notes[i_child].set_pitch
                        ( parent.notes[i_parent].get_pitch() );
                        notes[i_child].set_octave
                        ( parent.notes[i_parent].get_octave() );
                        notes[i_child].update();
                }

                i_parent++;
                i_child++;
        }
}

/* redistributes two random adjacent notes rhythmically
        re-edit the timing based on one of three way:
        split even-even, split 25-75%, split 75-25%
Args: integer first note
Returns: none
*/
void Melody::rhythmical_redistribution(int first_note)
{
        if (first_note < 0 || first_note > NOTE_AMOUNT-1)
        {
                throw runtime_error
                ("index in rhythmical_redistribution out of range");
        }

        // decide which way to redistribute rhythm using roulette wheel
        float chance_array [] = {CHANCE_OF_SPLIT_EVEN, CHANCE_OF_LONG_SHORT, 
                CHANCE_OF_SHORT_LONG};

        int selection = roulette_wheel(chance_array, 3);

        // chance the rhythm
        if (selection == 0)
        {
                notes[first_note].set_duration(0.25);
                notes[first_note+1].set_duration(0.25);
        }
        if (selection == 1)
        {
                notes[first_note].set_duration(0.375);
                notes[first_note+1].set_duration(0.125);
        }
        if (selection == 2)
        {
                notes[first_note].set_duration(0.125);
                notes[first_note+1].set_duration(0.375);
        }
        rhythmic_alteration_count++;

}

/* Melody constructor
        creates an array of random notes
        initializes the melody's score to zero
Args: none
Returns: none
*/
Melody::Melody()
{
        notes = new Note[NOTE_AMOUNT];
        capacity = NOTE_AMOUNT;
        count = NOTE_AMOUNT;
        rhythmic_alteration_count = 0;
        //form_used="AAAAAAAAAAAAAA";
}
/* destructor
Args: none
Returns: none
*/
Melody::~Melody()
{
        delete [] notes;
}

/* copy constructor
Args: a reference to a melody class
Returns: none
*/
Melody::Melody(Melody &melody)
{
        capacity = melody.capacity;
        count = melody.count;

        notes = new Note[count];
        for (int i = 0; i < count; i++)
        {
                // everything in note class is static
                // data and so shallow copy will suffice
                notes[i] = melody.notes[i];
        }

        //form_used="AAAAAAAAAAAAAA";
}
/* assignment operator
        copies info of melody passed in to this class instance
Args: a reference to a melody
Returns: none
*/
Melody& Melody::operator=(Melody &melody)
{
        // eliminate unnecessary work
        if (this == &melody)
        {
                return *this;
        }

        // delete the current melody information
        delete []notes;

        // shallow copies
        capacity = melody.capacity;
        count = melody.count;
        form_used = melody.form_used;

        // deep copy
        notes = new Note[count];
        for (int i = 0; i < count; i++)
        {
                // everything in note class is static
                // data and so shallow copy will suffice
                notes[i] = melody.notes[i];
        }

        return *this;

}
/* prints the melody by printing each note
Args: none
Returns: none
*/
void Melody::print_melody()
{
    cout << "------------ Melody ------------" << endl;
        for (int i = 0; i < count; i++)
        {
                 cout << "      "; notes[i].print_note();
                 cout << endl;
        }
    cout << "--------------------------------" << endl;
}


/* smooths a certain amount of notes, window defined
        in constants.h. Calculates average key num
        and transposes the notes to be as close
        to the average as possible
Args: integer starting note
Returns: none
*/
void Melody::smooth_by_average(int first_note)
{
        // sum total key_num, divide by number of notes
        int average = 0;
        int i = first_note;
        while(i < SMOOTHING_WINDOW + first_note && i < count)
        {
                average += notes[i].get_key_num(); 
                i++;
        }
        average = average / (i - first_note);

        // adjust the octaves
        int j = first_note;

        // amount of notes to be adjusted w/o segfault
        // i is the where last loop stopped, the window's last note
        while(j < i)
        {
                while (abs(average - notes[j].get_key_num()) > 12)
                {
                        if (average - notes[j].get_key_num() >= 0)
                        {
                                notes[j].transpose_oct("up");
                                notes[j].update();
                        }
                        if (average - notes[j].get_key_num() < 0)
                        {
                                notes[j].transpose_oct("down");
                                notes[j].update();
                        }
                }
                j++;
        }
}

/* smooths a certain amount of notes, places next note nearest
        to its previous note iteratively. Window defined in constants.h
Args: integer starting note
Returns: none
*/
void Melody::smooth_by_increment(int first_note)
{
        int i = first_note;

        while(i < SMOOTHING_WINDOW + first_note &&  i < count - 1)
        {
                while (abs(notes[i].get_key_num() - notes[i+1].get_key_num()) > 12)
                {
                        if (notes[i].get_key_num() - notes[i+1].get_key_num() >= 0)
                        {
                                notes[i+1].transpose_oct("up");
                                notes[i+1].update();
                        }
                        if (notes[i].get_key_num() - notes[i+1].get_key_num() < 0)
                        {
                                notes[i+1].transpose_oct("down");
                                notes[i+1].update();
                        }
                }
                i++;
        }
}

/* get a note reference using melody indexing
Args: integer index
Returns: Note pointer
*/
Note Melody::note_at(int index)
{
        if (index < 0 || index >= count)
        {
                throw runtime_error("note at, index out of range");
        }
        else 
        {
            return notes[index];
        }
}

/* get the melody size
Args: none
Returns: integer size
*/
int Melody::get_size()
{
        return count;
}

/* expand the amount of notes in melody
Args: none
Returns: none
*/
void Melody::expand()
{
        Note *temp = new Note[capacity*2];

        for (int i = 0; i < count; i++)
        {
                temp[i] = notes[i];
        }

        delete []notes;

        capacity = capacity * 2;

        notes = temp;
}

/* call mutation functions for melody and notes
Args: none
Return: none
*/
void Melody::mutate()
{
        // try to mutate a random note
        //Note n = notes[random_int(0, count-1)];
        //n.set_pitch(random_int(0,11)); n.update();

        // Smoothing
        for (int i = 0; i < SMOOTHING_ATTEMPTS; i++)
        {
                if (random_int(1, 100) <= (int) (SMOOTHING_CHANCE * 100))
                {
                        // decide which smoothing method
                        if(random_int(1, 2) == 1)
                        {
                                smooth_by_increment(random_int(0, count-1));
                        }
                        else
                        {
                                smooth_by_average(random_int(0, count-1));
                        }
                }
        }
        //arriva fino a 5 redistribuzioni ritmiche all'interno di una melodia (anche se l'if dentro al for è falso)
        //TODO: forse da semplificare
        if (rhythmic_alteration_count < RHYTHMIC_ALTERATIONS)
        {
            // rhythmic redistribution
            for (int i = 0; i < RHYTHMIC_REDISTRIBUTION_ATTEMPTS; i++)
            {
                    if (random_int(1, 100) <= (int)
                     (RHYTHMIC_REDISTRIBUTION_CHANCE * 100))
                    {
                            rhythmical_redistribution(random_int(0, count-2));
                    }
            }
        }

        if(random_int(1, 100) <= (int) (THEME_CHANCE * 100))
            thematic_generation(random_int(1,3));

}



// COULD BE ADDED:

/*subdivides a chosen note in a random way
Args: note index
Return: none
void Melody::subdivide(int first_note)
{
        // TODO    
}

/* generates thematic material, copies one part of the melody
        and imposes either the rhtyhm or intervalic 
        content onto a different part of the melody
Args: integer
Returns: none
*/
void Melody::thematic_generation(int form)
{

        /*
        si possono fare diverse forme/temi:
        1) Forma monopartita: 1 tema A che si ripete
        2) Forma bipartita: 2 temi AB alternati A-variazioneA-B-variazioneB
        3) Forma tripartita: 2 temi AB alternati A-B-A
        */
        int mono_capacity = MONO_WINDOW;
        int general_capacity = BI_TRI_WINDOW; 
        Note *theme_window_mono= new Note[mono_capacity];
        Note *theme_window = new Note[general_capacity];
        int k=0;

        //forma monopartita
        //if(form == "MONOPARTITA")
        if(form == 1)
        {
                for(int i=0; i<mono_capacity; i++){
                        theme_window_mono[i]= notes[i];
                }
                int first_note = mono_capacity;
                while(first_note+mono_capacity <= count)
                { 
                        
                        form_used = "MONOPARTITA";
                        k=0;
                        for(int j=first_note;j<first_note + mono_capacity;j++)
                        {
                                notes[j] = theme_window_mono[k];
                                k++;
                        }
                        first_note = first_note + mono_capacity;
                }
               
        }
        k=0;
        //if(form == "BIPARTITA" || form == "TRIPARTITA")
        if((form == 2) || (form == 3))
        {
                for(int i=0; i<general_capacity; i++){
                        theme_window[i]= notes[i];
                }
                //forma bipartita
                if(form == 2)
                {
                        form_used = "BIPARTITA";
                        int variation = random_int(1,11);
                        for(int j=general_capacity;j<general_capacity*2;j++)
                        {
                                notes[j] = theme_window[k];
                                if(notes[j].get_octave() < 5)
                                        notes[j].set_pitch(notes[j].get_pitch()+variation);
                                else
                                        notes[j].set_pitch(notes[j].get_pitch()-variation);  
                                notes[j].update();
                                k++;

                        }

                        delete []theme_window;
                        theme_window = new Note[general_capacity];
                        //tema B
                        k=0;
                        for(int i=count - (general_capacity*2); i<count - general_capacity; i++){
                                theme_window[k]= notes[i];
                                k++;
                        }
                        k=0;
                        for(int j=count - general_capacity;j<count;j++)
                        { 
                                notes[j] = theme_window[k];
                                if(notes[j].get_octave() < 5)
                                        notes[j].set_pitch(notes[j].get_pitch()+variation);
                                else
                                        notes[j].set_pitch(notes[j].get_pitch()-variation);
                                
                                notes[j].update();
                                k++;
                                
                                      
                        }

                }
                //forma tripartita
                //if(form == "TRIPARTITA")
                if(form == 3)
                {
                        delete []theme_window;
                        theme_window = new Note[general_capacity];
                        for(int i=0; i<general_capacity; i++){
                                theme_window[i]= notes[i];
                        }
                        form_used = "TRIPARTITA";
                        k=0;
                        for(int j=count - general_capacity;j<count;j++)
                        {
                                notes[j] = theme_window[k];
                                k++;     

                        }

                }

        }
        delete []theme_window;
        delete []theme_window_mono;

}

string Melody::get_form_used(){
        return form_used;
}

void Melody::set_form_used(string form){
        form_used = form;
}

void Melody::set_num_match(int num){
        num_match = num;
}
int Melody::get_num_match(){
        return num_match;
}

