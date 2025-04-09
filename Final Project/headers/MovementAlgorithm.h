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
// Abstract base class 
// MovementAlgorithm represents a algorithm to navigate through the City given a current position and ending position
//
////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "../headers/Node.h"
#include <stack>
using std::stack;

class MovementAlgorithm {

    protected:
        // Node that we want the car to end at
        const Node* endingNode;
        // Node that we want the car to start at
        const Node* startingNode;
        //a stack which holds the order ot moves to the Car's final destination. 
        //Popping off of the front of the stack will give us the Car's next move
        stack<Direction> path;

    public:
        // constructor
        // param startNode - the Node we want the car to start at
        // param endNode - the Node we want the car to end at
        MovementAlgorithm(const Node* const & startNode, const Node* const & endNode);

        // copy constructor for a MovementAlgorithm pointer
        MovementAlgorithm(const MovementAlgorithm* const & other);

        // calculates the next Direction the car should move in
        ////////////////////////////////////////////////////////////////
        // return - the Direction the car should move in to reach endingNode
        virtual Direction getNextMove() = 0;
};