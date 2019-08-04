// score.h
// Scoring class definition for genetic algorithm
// 	for music composition
// By: Ari Brown
// Nov. 28, 2016

#ifndef SCORE_H_INCLUDED
#define SCORE_H_INCLUDED

#include "melody.h"

class Score {

	public:
		// constructor computes score from melody pointer
		Score(Melody *melody);

		// default constructor/destructor
		Score(); 
		~Score();

		// pass in a new melody to calculate score
		void reinitialize(Melody *melody);

		// get the resulting score
		int get_score();

	private:
		// the score
		int total_score;

		// calculates the melody's score, with helper functions
		void calculate(Melody *melody);

			// diatonic fitness
			int analyze_diatonic_fit(Melody *melody);

			// analyze smoothness with octave
			int analyze_smoothness(Melody *melody);

			// analyze chord progression for favored patterns
			int analyze_progression(Melody *melody);

			//analyze rhytmic distribution on strong and weak beats
			int analyze_rhytmic_distribution(Melody *melody);

			//analyze thematic material based on 3 possible forms
			int analyze_theme(Melody *melody);

};

#endif