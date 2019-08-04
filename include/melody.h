// melody.h
// Melody class definition, an abstraction
//      for the melodic composition GA
// By: Ari Brown
// Nov. 28, 2016

/*
- A Melody contains an array of notes
- A Melody can be initalized randomly, copied, or breeded by
        passing in references to two parent melodies
- The Melody class can also manage its own mutations
*/

#ifndef MELODY_H_INCLUDED
#define MELODY_H_INCLUDED

#include "note.h"
#include "otherfuncs.h"

#include <string>

class Melody {
        public:
                // Default constructor/destructor
                Melody();
                ~Melody();

                // copy constructor
                Melody(Melody &melody);

                // constructor used to breed from mom and dad
                Melody(Melody &mom, Melody &dad);

                // assignment operator
                Melody& operator=(Melody &melody);

                // get a pointer to a specific note in the melody
                Note note_at(int index);

                // get the size of the melody
                int get_size();

                //getter theme
                string get_form_used();
                void set_form_used(string form);
                
                // display the melody
                void print_melody();
                int get_num_match();
                void set_num_match(int num);


        private:
                // array of notes in melody
                Note *notes;
                
                // array related data
                int capacity;
                int count;

                //theme related data
                string form_used;
                int num_match;

                // expand amount of notes
                void expand();

                // mutate the melody, with helper functions
                void mutate();
                        void rhythmical_redistribution(int first_note);
                        void subdivide(int first_note); // TODO
                        void thematic_generation(int form);
                        void smooth_by_average(int first_note);
                        void smooth_by_increment(int first_note);

                // copies a window of parent's trait 
                // (either rhythm or pitch) to child
                void copy_section(Melody &parent, int parent_start, 
                        int child_start, std::string option, int window);
                int rhythmic_alteration_count;
};

#endif
