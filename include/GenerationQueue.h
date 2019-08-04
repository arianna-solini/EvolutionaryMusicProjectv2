// GenerationQueue.h
// Queue that stores generations of melodies
// 	for genetic algorithm for music composition
// By: Ari Brown
// Nov. 28, 2016

#ifndef GENERATIONQUEUE_H_INCLUDED
#define GENERATIONQUEUE_H_INCLUDED

#include "melody.h"
#include "GenerationPopulation.h"
#include "MelodyNode.h"

class GenerationQueue {
        public:
                // constructors and destructors
                GenerationQueue();
                ~GenerationQueue();

                // display the queue's data
                void print();

                // insert a generation
                void insertAtBack(GenerationPopulation 
                	&generation);

                // get a certain generation's pointer in the queue
                GenerationPopulation* elementAt(int index);

                // get pointer to the last added population
                GenerationPopulation* get_last_added();
        
        private:
                // get the next index in the circular buffer
                int next_index(int index);

                // set the parents of the oldest generation to NULL
                void update_oldest_gen();

                // check if the queue is full
                bool full();

                // check if the index is within back-front range
                bool check_range(int index);

                // array holding populations
                GenerationPopulation *array;

                // array related data
                int front;
                int back;
                int capacity;
                int count;

};

#endif
