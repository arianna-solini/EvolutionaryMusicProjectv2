// GenAlgo.h
// Genetic Algorithm class definition
// 	for melodic composition
// By: Ari Brown
// Nov. 28, 2016

#ifndef GENALGO_H_INCLUDED
#define GENALGO_H_INCLUDED

#include "parameters/options.h"
#include "GenerationQueue.h"
#include "score.h"
#include "MelodyNode.h"

class GenAlgo {
	public:
		// Default constructor/destructor
		GenAlgo();
		~GenAlgo();

		// used to run the genetic algorithm
		void run();
	private:

		// the genetic algorithm stores a certain
		// amount of generations at any given time
		// in this queue
		GenerationQueue generations;

		MelodyNode best_melody_overall;
};

#endif