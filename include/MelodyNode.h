// MelodyNode.h
// MelodyNode class definition
// 	for genetic algorithm
// By: Ari Brown
// Nov. 28, 2016

#ifndef MELODYNODE_H_INCLUDED
#define MELODYNODE_H_INCLUDED

#include "parameters/constants.h"
#include "melody.h"

class MelodyNode {
	public:
		// Default constructor
	        MelodyNode();
	        // Constructor used to breed from parents
	        MelodyNode(MelodyNode *m, MelodyNode *d);
	        // Default destructor
	        ~MelodyNode();

	        // print functions to display data
	        void print();
	        void print_parents();
	        void print_children();

	        // check if the number of max children was reached
	        bool can_add_child();

	        // used to add a child pointer to node
	        void update_child(MelodyNode *child);

	        // assignment operator
	        MelodyNode& operator=(MelodyNode &node);

	        // get pointers to parents
	        MelodyNode* get_mom();
	        MelodyNode* get_dad();

	        // get the melody's fitness
	        int get_fitness();

	        // get pointer to the melody
	        Melody* get_melody();

	        // set the melody's parents to NULL
	        void set_parents_NULL();

	private:
		// the melody contained by the node
		Melody melody;

		// the melody's fitness
		int fitness;

		// pointers to parents
		MelodyNode *mom;
		MelodyNode *dad;

		// pointers to children
		MelodyNode *children[MAX_CHILDREN];

		// count children 
		int children_made;
};

#endif