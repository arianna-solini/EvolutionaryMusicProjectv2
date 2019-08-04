// GenerationPopulation.h
// Sequence that stores MelodyNodes and the MelodyNode definition
// By: Ari Brown
// Nov. 28, 2016

#ifndef GENERATIONPOPULATION_H_INCLUDED
#define GENERATIONPOPULATION_H_INCLUDED

#include "melody.h"
#include "parameters/constants.h"
#include "MelodyNode.h"

class GenerationPopulation {
        public:
                // default constructor
                GenerationPopulation();
                // constructor used to breed 
                // next generation from parents
                GenerationPopulation(GenerationPopulation 
                        &generation);
                // default destructor
                ~GenerationPopulation();

                // assignment operator
                GenerationPopulation& operator=
                (GenerationPopulation &gen);
        
                // display data
                void print();

                // get size of generation
                int size();

                // get a certain MelodyNode pointer in 
                // the generation
                MelodyNode* elementAt(int index);

                // get pointer to the best melody 
                // in the generation
                MelodyNode* get_best_melody();

                // insert a melodyNode to the generation
                void insertAtBack(MelodyNode 
                	&node);

                // set all MelodyNode parents of 
                // the generation
                // to NULL (used to update oldest saved generation)
                void set_parents_NULL();
        
        private:
                // used to expand amount in generation
                void expand();

                // used by constructor
                void init();

                // private data
                MelodyNode *array;
                int capacity;
                int count;
};

#endif
