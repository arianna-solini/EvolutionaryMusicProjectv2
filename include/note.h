// note.h
// Note class definition, an abstraction
//      for the melodic composition GA
// By: Ari Brown
// Nov. 28, 2016

/* 
- A Note includes a pitch, duration, register (octave), and whether 
        rest or not
- An arbitrary number "key_num" is a value based on pitch and register,
         say from
        a keyboard-like layout
- A scale degree labels the note 0-11 in relation to the given key's 
        starting note
        as defined in constants.h
- The Note class can manage its own mutations
*/

#ifndef NOTE_H_INCLUDED
#define NOTE_H_INCLUDED

class Note{
        public:       
                Note(); // randomly initializes quarter note
                ~Note();

                // assignment operator
                Note& operator=(Note &note);

                //// Getters ////
                int get_key_num();
                float get_duration();
                int get_scale_degree();
                int get_pitch();
                bool get_diatonic();
                int get_octave();
                bool get_rest();

                //// Setters ////
                void set_duration(float dur); // 1.0 is a whole note
                void set_pitch(int p); // takes 0-11
                void set_octave(int o); // takes 1-5
                
                void set_key_num(int k);
                void set_scale_degree(int s);
                // takes in "up" or "down"
                void transpose_oct(string direction);  

                // tries a certain number of times to mutate --> CAMBIATO, ORA PROVA UNA VOLTA
                void mutate();

                /* Mutates a note
                takes in numbers 1-7, mutation types:
                        1. half step up
                        2. half step down
                        3. whole step up
                        4. whole step down
                        5. octave up
                        6. octave down
                        7. flip rest
                */
                void mutate(int num);

                // update computes the key num and scale degree
                // after any changes to the note
                void update();

                // helpers to update:
                void compute_key_num();
                void update_scale_degree();

                // format example: c#3-0.25(2 -0)
                // c#3, quarter note, scale degree 2, not rest
                void print_note();
                

        private:
                // Note data members
                float duration;
                int pitch;
                int octave;
                bool rest;
                int key_num;
                int scale_degree;

                // assigns rest
                bool decide_if_rest(float probability);
};

#endif
