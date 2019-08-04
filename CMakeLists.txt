cmake_minimum_required(VERSION 3.14)
project(EvolutionaryMusicProject)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native")

add_executable(EvolutionaryMusicProject
        src/main.cpp
        include/GenAlgo.h
        include/commonfuncs.h
        include/GenerationPopulation.h
        include/GenerationQueue.h
        include/melody2midi.h
        include/melody2sonic.h
        include/melody.h
        include/MelodyNode.h
        include/note.h
        include/otherfuncs.h
        include/score.h
        include/parameters/constants.h
        include/parameters/options.h
        src/commonfuncs.cpp
        src/GenerationPopulation.cpp
        src/GenerationQueue.cpp
        src/melody2midi.cpp
        src/melody2sonic.cpp
        src/melody.cpp
        src/MelodyNode.cpp
        src/note.cpp
        src/otherfuncs.cpp
        src/score.cpp
        src/GenAlgo.cpp
        )