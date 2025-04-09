//////////////////////////////////////////////////////////////////////////////////////
//
// Name: Noah Dunham, Alex Leonida
// Date: 5/4/2024, modified 5/4/2024
// Course Code: CS-273-1
//
// License: CS273 students at whitworth may edit this file but not share this
// file electronically with other students.
//
// Copyright (C) Noah Dunham, Alex Leonida
//
// Resources used:
//
//
// Collaborators:
//
// Purpose of class:
// City represents the place in which Nodes and Cars are held. 
// A City will be comprised of Nodes, and Nodes will be comprised of dynamically moving Cars.
// Each City holds the total number of Cars inside of it
// Each Node also holds the list of Cars that we are tracking, and the list of Cars which are being used for traffic
// Each City will hold cars in different places. They will act functionally similar, but one list of cars we will be keeping track of.
// The other cars in the city will be used as traffic for the other cars. 
//
////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "../headers/Car.h"
#include "../headers/Direction.h"
#include "../headers/Node.h"

#include <list>
using std::list;

class City{
    private:
        // holds size of grid
        int gridSize;
        // a double array of Nodes
        Node*** grid;
        // list of cars we are running 1 of 3 algorithms on 
        list<Car> cars;
        // list of cars that will populate the grid. these will all be running on algorithm 1
        list<Car> traffic;


        // algorithm we want the tracked cars to use. Must be ∈ {1,2,3}. 1 means the car will use Algorithm1, 2 means Algorithm2, etc
        int carAlgorithmType;
        // algorithm we want the traffic (nontracked) to use. Must be ∈ {1,2,3}. 1 means the car will use Algorithm1, 2 means Algorithm2, etc
        int trafficAlgorithmType;
        // number of cars we want to track in the simulation
        int numberOfTrackedCars;
        // true to replace cars with a new random car when a traffic/tracked car reaches it's destination, false to not and decrease the number of cars on the road.
        bool replaceTraffic;
        // lower bound on the X coordinates a car (traffic/tracked) can start at. Inclusive. 0 <= lowXStart <= highXStart
        int lowXStart;
        // upper bound on the X coordinates a car (traffic/tracked) can start at. Exclusive. lowXStart <= highXStart <= gridSize
        int highXStart;
        // lower bound on the Y coordinates a car (traffic/tracked) can start at. Inclusive. 0 <= lowYStart <= highYStart
        int lowYStart;
        // upper bound on the Y coordinates a car (traffic/tracked) can start at. Exclusive. lowYStart <= highYStart <= gridSize
        int highYStart;
        // lower bound on the X coordinates a car (traffic/tracked) can end at. Inclusive. 0 <= lowXEnd <= highXEnd
        int lowXEnd;
        // upper bound on the X coordinates a car (traffic/tracked) can end at. Exclusive. lowXEnd <= highXEnd <= gridSize
        int highXEnd;
        // lower bound on the Y coordinates a car (traffic/tracked) can end at. Inclusive. 0 <= lowYEnd <= highYEnd
        int lowYEnd;
        // upper bound on the Y coordinates a car (traffic/tracked) can end at. Exclusive. lowYEnd <= highYEnd <= gridSize
        int highYEnd;

        // generates and returns a random integer in the range [low,high)
        // assumes srand() initialized elsewhere 
        int genRandom(int low, int high);

        // initializes the 'grid' with Nodes with weights = 1
        // intended to be called from the constructor
        void initGrid();

        // creates a new untracked car within the ranges to be added to the grid
        void generateTrafficCar();

        // creates a new tracked car within the ranges to be added to the grid
        void generateTrackedCar();

    public:
        /// Creates a City object. 
        /// The coordinates are locations in a 2D array with [0][0] representing the north west most Node. 
        /// If you do not follow bounds placed on these variables, you will most likely have an exception thrown by the program OR you will recieve an output caused by undefined behavior.
        /// @param gridSize size of the Grid we want to create. Grid will be a square
        /// @param numberOfTrackedCars number of cars we want to track in the simulation
        /// @param totalNumberofCars number of cars we want to track + initial number of cars we have as traffic. Number of cars on the raod will decrease over time if replaceTraffic is false
        /// @param carAlgorithmType algorithm we want the tracked cars to use. Must be ∈ {1,2,3}. 1 means the car will use Algorithm1, 2 means Algorithm2, etc
        /// @param trafficAlgorithmType algorithm we want the traffic (nontracked) to use. Must be ∈ {1,2,3}. 1 means the car will use Algorithm1, 2 means Algorithm2, etc
        /// @param seed number to seed srand(). Only changing algorithm tytpes and keeping everything else constant across objects will garentee the same initial conditions
        /// @param replaceTraffic true to replace cars with a new random car when a traffic/tracked car reaches it's destination, false to not and decrease the number of cars on the road.
        /// @param lowXStart lower bound on the X coordinates a car (traffic/tracked) can start at. Inclusive. 0 <= lowXStart < highXStart
        /// @param highXStart upper bound on the X coordinates a car (traffic/tracked) can start at. Exclusive. lowXStart < highXStart <= gridSize
        /// @param lowYStart lower bound on the Y coordinates a car (traffic/tracked) can start at. Inclusive. 0 <= lowYStart < highYStart
        /// @param highYStart upper bound on the Y coordinates a car (traffic/tracked) can start at. Exclusive. lowYStart < highYStart <= gridSize
        /// @param lowXEnd lower bound on the X coordinates a car (traffic/tracked) can end at. Inclusive. 0 <= lowXEnd < highXEnd
        /// @param highXEnd upper bound on the X coordinates a car (traffic/tracked) can end at. Exclusive. lowXEnd < highXEnd <= gridSize
        /// @param lowYEnd lower bound on the Y coordinates a car (traffic/tracked) can end at. Inclusive. 0 <= lowYEnd < highYEnd
        /// @param highYEnd upper bound on the Y coordinates a car (traffic/tracked) can end at. Exclusive. lowYEnd < highYEnd <= gridSize
        City(int gridSize, int numberOfTrackedCars, int totalNumberofCars, int carAlgorithmType, int trafficAlgorithmType, int seed, bool replaceTraffic, int lowXStart, int highXStart, int lowYStart, int highYStart, int lowXEnd, int highXEnd, int lowYEnd, int highYEnd);

        // runs a simulation on the grid of Nodes
        // all Car objects in list<Cars> cars attribute will start and end at their designated spots in this simulaiton
        // we will keep track of how many ticks it took each car to get to the end, and divide this number by the average number of cars in the simulation 
        // returns the average number of ticks taken by all of the cars
        double simulate();

        // deconstructor
        ~City();
};
