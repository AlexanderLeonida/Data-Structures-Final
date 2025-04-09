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
// Car represents a car driving around the city
// Car will have a starting Node and a ending Node. It will drive through the city until it reaches the ending Node
// This will cause traffic for the other cars in the city
//
////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Node.h"
#include "Node.h"
#include "MovementAlgorithm.h"
#include "Algorithm1.h"
#include "Algorithm2.h"
#include "Algorithm3.h"
class Car {
    private:
        // number of ticks it took since the car got to the Node it's at
        int ticksOnPath;
        // how far the car moves along the path between nodes. ex. speed = 0.2 so number of ticks it would take
        // to get to the next Node would be 1/0.2 = 5 ticks
        // we will always round down to the nearest whole number
        // must be between (0.0-1.0]
        double speed;
        // Node the car is currently at
        Node* currentNode;
        // Node the car is moving to during this tick
        Node* nextNode;
        // Node the car is going to end at
        Node* endingNode; 
        // measured in ticks taken to get to the endingNode
        // once currentNode == endingNode, total time will stop changing
        int totalTime;
        // number of ticks required to reach the next intersection
        // calulated by taking the amount of traffic on a path and dividing it by the speed of  the car
        int ticksNeededOnCurrentPath;
        // pointer to the MovementAlgorithm the car will use to decide it's movements
        // MovementAlgorithm is an abstract base class, so this pointer will really be pointing to a derived class
        MovementAlgorithm* algorithm;
        // Direction the car is moving in at this tick
        // currentNode.move(movementDirection) will return nextNode
        Direction movementDirection;

        int algorithmType;

    public:
        // argumented constructor for Car
        // param currentNode - starting Node of the Car
        // param endingNode - where the car will end
        // param speed - the speed of the car in units/tick. 0 < speed <= 1
        // param algorithmType - the version of the movement algorithm this car will have. 
        //                          EX: algorithmType = 2 means the car will use Algorithm2
        //                          algorithmType ∈ {1,2,3}
        Car(Node* & startNode, Node* & endNode, double speed, int algorithmType);

        // copy constructor
        Car(const Car & other);

        //assignment operator implicitly calls copy constructor
        Car& operator=(Car other);

        //deconstructor
        ~Car();
        // updates the totalTime and ticksOnPath
        // if the car has reached it's the end of the path, recalculates the movementDirection and nextNode of the car
        //      updates the weights of the directions the the car is moving in and just left
        //      recalulates ticksNeededOnCurrentPath and resets ticksOnPath
        // represents the car moving forward in time by 1 tick
        void update();

        // returns true iff currentNode == endingNode
        bool isFinished() const;

        // returns the number of ticks (totalTime) the car travled
        int getTime() const;
};