// GenerationPopulation.cpp
// Implementation for sequence that stores MelodyNodes
// By: Ari Brown
// Nov. 28, 2016

#include<iostream>
#include <string>
using namespace std;

#include "../include/parameters/options.h"
#include "../include/GenerationPopulation.h"
#include "../include/melody.h"
#include "../include/parameters/constants.h"
#include "../include/MelodyNode.h"

/* GenerationPopulation
 * Purpose: Default Constructor,
 *      creates empty sequence
 * Parameters: none
 * Return: none
 */
GenerationPopulation::GenerationPopulation()
{
        init();

        // fill generation in randomly
        for (int i = 0; i < NUM_MELODIES; i++)
        {
                MelodyNode child;
                insertAtBack(child);
        }
}

/* Constructor used to breed new generation 
from older generation
Args: reference to parent generation
Return: none
*/
GenerationPopulation::GenerationPopulation
(GenerationPopulation &generation)
{
        init();

        // new array of probabilities for picking parents
        //float probabilities[NUM_MELODIES];

        float* probabilities = new float[NUM_MELODIES];

        // get total score
        int score = 0;
        for (int i = 0; i < generation.count; i++)
        {
                score += generation.elementAt(i)->
                get_fitness();
        }

        // fill probabilities of picking melodies, based on old gen
        for (int i = 0; i < generation.count; i++)
        {
                int fitness = generation.elementAt(i)->get_fitness();
                probabilities[i] = fitness / ((float) score);
        }
        
        // fill the melodies in this generation by breeding
        for (int i = 0; i < NUM_MELODIES; i++)
        {
                // pick two parent melodies

                int momIndex = roulette_wheel(probabilities, 
                        generation.count);
                int dadIndex = roulette_wheel(probabilities, 
                        generation.count);


                // ensure MAX_CHILDREN hasn't been reached, and that
                // the parents are not the same
                while (!generation.array[momIndex].can_add_child() 
                        || !generation.array[dadIndex].can_add_child() 
                        || momIndex == dadIndex)
                {
                        momIndex = roulette_wheel(probabilities, 
                                generation.count);
                        dadIndex = roulette_wheel(probabilities, 
                                generation.count);
                }

                // generate a child
                MelodyNode child(&(generation.array[momIndex]),
                        &(generation.array[dadIndex]));

                // copy the child to memory
                insertAtBack(child);
        }
        delete[] probabilities;
}

/* Initialize class data
Args: none
Return: none
*/
void GenerationPopulation::init()
{
        capacity = 10;
        count = 0;
        array = new MelodyNode[capacity];
}

/* ~GenerationPopulation
 * Purpose: Destructor
 * Parameters: none
 * Return: none
 */
GenerationPopulation::~GenerationPopulation()
{
        // delete dynamic memory
	delete [] array;
}

/* size
 * Purpose: reveal the amount of MelodyNodes
 *      in the sequence
 * Parameters: none
 * Return: integer amount of MelodyNodes
 */
int GenerationPopulation::size()
{
        return count; 
}

/* elementAt
 * Purpose: get melodyNode pointer at a given index 
 * Parameters: integer index
 * Return: a MelodyNode
 */
MelodyNode* GenerationPopulation::elementAt(int index)
{
        // make sure the requested index is within range
        if (index >= count) {throw runtime_error("Out of range");}
        return &(array[index]);
}

/* insertAtBack
 * Purpose: insert a MelodyNode at the end of sequence
 * Parameters: a MelodyNode
 * Return: none
 */
void GenerationPopulation::insertAtBack(MelodyNode &node)
{
        // check if enough capacity
        if (count == capacity)
        {
                expand();
        }

        // add MelodyNode and increment size
        array[count] = node;
        count++;
}

/* expand
 * Purpose: expand the dynamic array to twice the size
 * Parameters: none
 * Return: none
 */
void GenerationPopulation::expand()
{
        // temporary sequence twice the size
        MelodyNode *temp = new MelodyNode[capacity*2];

        // copy everything over
        for (int counter = 0; counter < count; counter++)
        {
                temp[counter] = array[counter]; 
        }
        
        // delete the old sequence
        delete [] array;

        // updte capacity
        capacity = capacity*2;
        
        // update pointer
        array = temp;

}

/* Print the population
Args: none
Return: none
*/
void GenerationPopulation::print()
{
        cout << "----------- GENERATION ---------" << endl;
	for (int i = 0; i < count; i++)
	{
                cout << "Melody " << i+1 << ":" << endl;
                cout << "Mom: " << array[i].get_mom() << endl;
                cout << "Dad: " << array[i].get_dad() << endl;
		array[i].get_melody()->print_melody();
	}
        cout << "--------------------------------" << endl;
}

/* Get a pointer to the best melodyNode in the generation
Args: none
Return: MelodyNode pointer
*/
MelodyNode* GenerationPopulation::get_best_melody()
{
        //confronta tutti gli elementi col primo (top_melodyNode)
	MelodyNode* top_melodyNode = &(array[0]);  
	int top_score = top_melodyNode->get_fitness();

	for (int i = 0; i < count; i++)
	{
		if (array[i].get_fitness() > top_score)
		{
			top_melodyNode = &(array[i]);
			top_score = array[i].get_fitness();
		}
	}

	return top_melodyNode;
}

/* Assignment operator
Args: reference to a population
Return: reference to a population
*/
GenerationPopulation& GenerationPopulation::operator=
(GenerationPopulation &gen)
{
        // eliminate unnecessary work
        if (this == &gen)
        {
                return *this;
        }
        
        // delete the current melody information
        delete [] array;

        // shallow copies
        capacity = gen.capacity;
        count = gen.count;
        
        // deep copy
        array = new MelodyNode[capacity];
        for (int i = 0; i < count; i++)
        {
                array[i] = gen.array[i];
        }

        return *this;

}

/* Set the parents of the whole
        generaton to NULL, used to update
        oldest generation
Args: none
Return: none
*/
void GenerationPopulation::set_parents_NULL()
{
        for (int i = 0; i < count; i++)
        {
                array[i].set_parents_NULL();
        }
}
