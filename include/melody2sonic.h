// melody2sonic.h
// output Sonic Pi

#ifndef MELODY2SONIC_H_INCLUDED
#define MELODY2SONIC_H_INCLUDED

#include "melody.h"
#include <string>



// convert a melody into midi translatable data and save file
void melody2sonic(Melody *melody, std::string filename);

#endif
