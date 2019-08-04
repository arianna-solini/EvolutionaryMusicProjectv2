// GenerationQueue.cpp
// Implementation for circular queue that stores generations
//	of melodies, only stores a certain amount.
//	If full, when one is pushed, oldest is popped
// By: Ari Brown
// Nov. 28, 2016


#include<iostream>
#include <string>
using namespace std;

#include "../include/parameters/options.h"
#include "../include/GenerationQueue.h"
#include "../include/melody.h"
#include "../include/MelodyNode.h"

/* GenerationQueue
 * Purpose: Default Constructor,
 *      creates empty sequence
 * Parameters: none
 * Return: none
 */
GenerationQueue::GenerationQueue()
{
        capacity = GENERATIONS_SAVED;
        front = 0;
        back = 0;
        count = 0;
        array = new GenerationPopulation[capacity];
}

/* ~GenerationQueue
 * Purpose: Destructor
 * Parameters: none
 * Return: none
 */
GenerationQueue::~GenerationQueue()
{
        // delete dynamic memory
       	delete [] array;
}

/* elementAt
 * Purpose: reveal the GenerationPopulation at a certain index 
 * Parameters: integer index
 * Return: a GenerationPopulation pointer
 */
GenerationPopulation* GenerationQueue::elementAt(int index)
{
	if (!check_range(index))
	{
		throw runtime_error("elementAt index out of range");
	}
        return &(array[index]);
}

/* checks if an index is between the front and back
Args: integer index
Return: boolean
*/
bool GenerationQueue::check_range(int index)
{
	int i = front;
	bool found = false;

	if (full())
	{
		return true;
	}

	while (i != back)
	{
		if (i == index)
		{
			found = true;
		}
		i = next_index(i);
	}

	return found;
}

/* insertAtBack
 * Purpose: insert a GenerationPopulation at the end of sequence
 * Parameters: a GenerationPopulation
 * Return: none
 */
void GenerationQueue::insertAtBack(GenerationPopulation &generation)
{
        // the circular queue is full, overwrite data
        if (count == capacity)
        {
        	array[back] = generation;
        	front = next_index(front);
        	back = next_index(back);
        }

        // the circular queue isn't full yet, add data
	if (count < capacity)
	{
        	array[back] = generation;
        	back = next_index(back);
        	count++;
	}

        // sets the parents of the oldest generation 
        // to NULL once the queue is full
        update_oldest_gen();
}

/* Tells if the generation queue is filled to its capacity
Args: none
Return: boolean
*/
bool GenerationQueue::full()
{
	if (count == capacity && front == back)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

/* Gets the next index and deals with wrapping around in 
	the circular queue
Args: current index integer
Return: next index integer
*/
int GenerationQueue::next_index(int index)
{
	if (index < 0 || index >= capacity)
	{
		throw runtime_error("no possible index");
	}
	if (index == capacity - 1)
	{
		return 0;
	}
	else
	{
		return index + 1;
	}
}

/* prints out all generations in the queue
Args: none
Return: none
*/
void GenerationQueue::print()
{

	cout << "--------- QUEUE --------" << endl;
	cout << "*** Oldest ***" << endl;

	cout << "GEN: " << endl;
	int i = front;
	array[i].print();
	i = next_index(i);

	while (i != back)
	{
		cout << "GEN: " << endl;
		array[i].print();
		i = next_index(i);
	}

	cout << "*** Newest ***" << endl;
}

/* Get pointer to the last generation added, for altering
	it's children information and breeding purposes
Args: none
Return: pointer to GenerationPopulation
*/
GenerationPopulation* GenerationQueue::get_last_added()
{
	// get the last added index
	int latest_index = back;
	if (back > 0)
	{
		latest_index--;
	}
	if (back == 0)
	{
		latest_index = count - 1;
	}

	return &(array[latest_index]);
}

/* Set all parents to NULL in the oldest generation,
	once the queue is full
Args: none
Return: none
*/
void GenerationQueue::update_oldest_gen()
{
	if (full())
	{
		array[back].set_parents_NULL();
	}
}
