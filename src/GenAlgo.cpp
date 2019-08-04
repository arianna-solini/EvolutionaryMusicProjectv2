// GenAlgo.cpp
// Genetic Algorithm class implementation
// 	for melodic composition
// By: Ari Brown
// Nov. 28, 2016

#include <iostream>
using namespace std;

#include "../include/parameters/options.h"
#include "../include/GenAlgo.h"
#include "../include/melody.h"
#include "../include/parameters/constants.h"
#include "../include/GenerationPopulation.h"
#include "../include/GenerationQueue.h"
//#include "../include/melody2midi.h"
#include "../include/melody2sonic.h"

/* Default Constructor
Args: none
Return: none
*/
GenAlgo::GenAlgo()
{
	// create and store first generation
	GenerationPopulation gen0;
	generations.insertAtBack(gen0);
}

/* Destructor
Args: none
Return: none
*/
GenAlgo::~GenAlgo()
{
	// free heap memory
}

/* Run the genetic algorithm
Args: none
Return: none
*/
void GenAlgo::run()
{
	GenerationPopulation *current_gen = generations.get_last_added();

	for (int i = 0; i < ITERATIONS; i++)
	{
		if (i % 1000 == 0) {
                        cout << "GENERATION: " << i << " SCORE: "
			<< current_gen->get_best_melody()
			->get_fitness() << " forma: " << current_gen->get_best_melody()
			->get_melody()->get_form_used() << endl;
		}

		// save the best melody
		if (current_gen->get_best_melody()->get_fitness() > 
			best_melody_overall.get_fitness())
		{
			best_melody_overall = *(current_gen->
				get_best_melody());
		}

		// create a next generation from the current
		// qui viene fatta la selezione/creazione dei figli (sempre di cardinalità NUM_MELODIES)
		GenerationPopulation next_gen(*current_gen);

		// insert new generation into the queue
		generations.insertAtBack(next_gen);

		// update the current generation
		current_gen = generations.get_last_added();
		
	}

	// print best melody
	current_gen->get_best_melody()->get_melody()->
	print_melody();





	// save the top melody in sonic text data
	melody2sonic(current_gen->get_best_melody()->
		get_melody(), OUTPUT_FILE);

	// save parents
	if (current_gen->get_best_melody()->get_mom() != NULL)
	{
		melody2sonic(current_gen->get_best_melody()->
			get_mom()->get_melody(), OUTPUT_FILE + "_mom");
	}
	if (current_gen->get_best_melody()->get_dad() != NULL)
	{
		melody2sonic(current_gen->get_best_melody()->
			get_dad()->get_melody(), OUTPUT_FILE + "_dad");
	}

	// save grandparents
	if (current_gen->get_best_melody()->get_mom() != NULL)
	{
		if (current_gen->get_best_melody()->get_mom()
			->get_mom() != NULL)
		{
			melody2sonic(current_gen->
				get_best_melody()->get_mom()->get_mom()->get_melody(), OUTPUT_FILE + "_grandma1");
		}
	}
	if (current_gen->get_best_melody()->get_mom() != NULL)
	{
		if (current_gen->get_best_melody()->get_mom()
			->get_dad() != NULL)
		{
			melody2sonic(current_gen->get_best_melody()
				->get_mom()->get_dad()->
				get_melody(), OUTPUT_FILE + "_grandpa1");
		}
	}
	if (current_gen->get_best_melody()->get_dad() != NULL)
	{
		if (current_gen->get_best_melody()->
			get_dad()->get_mom() != NULL)
		{
			melody2sonic(current_gen->get_best_melody()->
				get_dad()->get_mom()->
				get_melody(), OUTPUT_FILE + "_grandma2");
		}
	}
	if (current_gen->get_best_melody()->get_dad() != NULL)
	{
		if (current_gen->get_best_melody()->get_dad()->
			get_dad() != NULL)
		{
			melody2sonic(current_gen->get_best_melody()->
				get_dad()->get_dad()->
				get_melody(), OUTPUT_FILE + "_grandpa2");
		}
	}

	// save the best overall
	melody2sonic(best_melody_overall.get_melody(),
	 OUTPUT_FILE + "_best_overall");
}



