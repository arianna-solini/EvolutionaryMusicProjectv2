// main.cpp
// main implementation for running the 
//	genetic algorithm to compose melody lines
// By: Ari Brown
// Nov. 28, 2016


#include <iostream>
#include <string>
using namespace std;

#include "../include/GenAlgo.h"

// function declarations
void start_message();
void assign_defaults();
void user_options();
void options();

///// extern variables /////
// (options to be initialized)
int NOTE_AMOUNT;
int NUM_MELODIES;
int ITERATIONS;
int GENERATIONS_SAVED;
int KEY;
std::string OUTPUT_FILE;
std::string FORM_MUSIC;
std::string CHOOSE_MODE;
////////////////////////////


//////////////////////// Main //////////////////////////

int main () 
{
	//screen_clear();
	start_message();
	assign_defaults();
	options();

	GenAlgo melody_breeder;
	melody_breeder.run();

	return 0;
}

///////////////////// Functions ////////////////////////

void start_message()
{
	cout << endl << endl;
	cout << "	GENEITC ALGORITHM FOR MUSIC COMPOSITION" << endl;
	cout << "	By: Ari Brown" << endl;
	cout << "	Created: Nov. 28, 2016" << endl;
	cout << endl << endl;
}

void assign_defaults()
{
	NOTE_AMOUNT = 60;
	NUM_MELODIES = 50;
	ITERATIONS = 10000;
	GENERATIONS_SAVED = 5;
	KEY = C;
	OUTPUT_FILE = "../outputSonic/Best_Melody";
    CHOOSE_MODE = "roulette";
	//FORM_MUSIC = "TRIPARTITA";
}

void options()
{
	cout << "	----------- DEFAULT OPTIONS -----------" << endl;
	cout << "	# Note Amount: 60" << endl;
	cout << "	# Number of Melodies: 50" << endl;
	cout << "	# Number of Iterations: 10000" << endl;
	cout << "	# Generations Saved: 5" << endl;
	cout << "	# Musical Key: C" << endl;
	cout << "	# Output File Name: Best_Melody" << endl;
    cout << "	# Selection Mechanism: roulette" << endl;
	//cout << "	# Form of the melodies: TRIPARTITA" << endl;

	string response;
	cout <<"Use default options? Type \"yes\" or \"no\": " << endl;
	cin >> response;

	if (response == "no")
	{
		user_options();
	}
}

void user_options()
{
	cout << endl;
	cout << "	------------ PICK PARAMTERS -----------" << endl;
	// replace_prompt("	# Amount of notes per melody: ", NOTE_AMOUNT);

	int integer;
	string str;

	cout << "	# Note Amount: ";
		cin >> integer;
		NOTE_AMOUNT = integer;

	cout << "	# Number of Melodies: ";
		cin >> integer;
		NUM_MELODIES = integer;

	cout << "	# Number of Iterations: ";
		cin >> integer;
		ITERATIONS = integer;	

	cout << "	# Generations Saved: ";
		cin >> integer;
		GENERATIONS_SAVED = integer;

	cout << "	# Musical Key (C, C#, D, D#...): ";
		cin >> str;
		if (str == "C") {KEY = C;} if (str == "C#") {KEY = CS;}
		if (str == "D") {KEY = D;} if (str == "D#") {KEY = DS;}
		if (str == "E") {KEY = E;} if (str == "F") {KEY = F;}
		if (str == "F#") {KEY = FS;} if (str == "G") {KEY = G;}
		if (str == "G#") {KEY = GS;} if (str == "A") {KEY = A;}
		if (str == "A#") {KEY = AS;} if (str == "B") {KEY = B;}

	cout << "	# Output File Name: ";
		cin >> str;
		OUTPUT_FILE = "../outputSonic/" + str;

    cout << "	# Selection Mechanism (roulette, tournament): ";
        cin >> str;
        if(str == "tournament") {CHOOSE_MODE = "tournament";}
        if(str == "roulette") {CHOOSE_MODE = "roulette";}

	/*cout << "	# Form of the melodies (MONO, BI, TRI): ";
		cin >> str;
		if(str == "MONO") { FORM_MUSIC = "MONOPARTITA";}
		if(str == "BI") { FORM_MUSIC = "BIPARTITA";}
		if(str == "TRI") { FORM_MUSIC = "TRIPARTITA";}*/

}