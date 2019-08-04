// MelodyNode.cpp
// MelodyNode class implementation
//	for genetic algorithm
// By: Ari Brown
// Nov. 28, 2016

#include <iostream>
using namespace std;

#include "../include/melody.h"
#include "../include/MelodyNode.h"
#include "../include/parameters/constants.h"
#include "../include/parameters/options.h"
#include "../include/score.h"

/* Default constructor
Args: none
Return: none
*/
MelodyNode::MelodyNode()
{
	// initialize
        fitness = 0;
        mom = NULL;
        dad = NULL;
        children_made = 0;

        // score the melody
        Score score(&melody);
        fitness = score.get_score();
}

/* Constructor used for breeding,
	creates melodyNode from parents 
Args: pointers to mom and dad MelodyNodes
Return: none
*/
MelodyNode::MelodyNode(MelodyNode *m, MelodyNode *d)
{
        Melody new_mel(m->melody, d->melody);
        melody = new_mel;
        mom = m;
        dad = d;
        children_made = 0;
         // score the melody
        Score score(&melody);
        fitness = score.get_score();

        m->update_child(this);
        d->update_child(this);   
}

/* Destructor
Args: none
Return: none
*/
MelodyNode::~MelodyNode()
{
	// free heap memory
}

/* print
Args: none
Return: none
*/
void MelodyNode::print()
{
        cout << "****MELODYNODE****" << endl;
        cout << "Fitness: " << fitness << endl;
        melody.print_melody();
        cout << "Mom: " << mom << endl;
        cout << "Dad: " << dad << endl;

        for (int i = 0; i < children_made; i++)
        {
                cout << "Child " << i + 1 << ": " << children[i] << endl;
        }
        cout << "******************" << endl;
}

/* print parents
Args: none
Return: none
*/
void MelodyNode::print_parents()
{
        if (mom == NULL || dad == NULL)
        {
                cout << "Cannot get parent: oldest gen" << endl;
        }
        else
        {
                cout << "--- MOM ---" << endl;
                mom->melody.print_melody();
                cout << "--- DAD ---" << endl; 
                dad->melody.print_melody();
                cout << "-----------" << endl;
        }
}

/* print children
Args: none
Return: none
*/
void MelodyNode::print_children()
{
	if (children_made == 0)
	{
		cout << "No children to print" << endl;
	}
	for (int i = 0; i < children_made; i++)
	{
		children[i]->print();
	}
}

/* Fill in a child in the Node
Args: pointer to MelodyNode child
Return: none
*/
void MelodyNode::update_child(MelodyNode *child)
{
	// make sure max children hasn't been reached
        if (children_made >= MAX_CHILDREN)
        {
                throw runtime_error("too many children");
        }
        else
        {
                children[children_made] = child;
                children_made++;
        }
}

/* get pointer to mom node
Args: none
Return: MelodyNode pointer
*/
MelodyNode* MelodyNode::get_mom()
{
	return mom;
}

/* get pointer to dad node
Args: none
Return: MelodyNode pointer
*/
MelodyNode* MelodyNode::get_dad()
{
	return dad;
}

/* Get the fitness of the melody
Args: none
Return: integer score
*/
int MelodyNode::get_fitness()
{
	return fitness;
}

/* Get pointer to the melody
Args: none
Return: pointer to Melody
*/
Melody* MelodyNode::get_melody()
{
	return &melody;
}

/* Set the parents to NULL,
	used to update oldest generation
Args: none
Return: none
*/
void MelodyNode::set_parents_NULL()
{
	mom = NULL;
	dad = NULL;
}

/* Assignment operator
Args: reference to a MelodyNode
Return: reference to a MelodyNode
*/
MelodyNode& MelodyNode::operator=(MelodyNode &node)
{
	// check if it is the same node
        if (this == &node)
        {
                return *this;
        }

        // ensure data gets copied
        melody = node.melody;
        fitness = node.fitness;
        children_made = node.children_made;
        mom = node.mom;
        dad = node.dad;
        for (int i = 0; i < MAX_CHILDREN; i++)
        {
                children[i] = node.children[i];
        }

        return *this;
}

/* Check if a child can be added to this MelodyNode
Args: none
Return: boolean
*/
bool MelodyNode::can_add_child()
{
	if (children_made < MAX_CHILDREN)
	{
		return true;
	}
	else
	{
		return false;
	}
}

