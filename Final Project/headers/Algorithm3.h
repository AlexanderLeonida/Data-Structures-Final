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
//  Algorithm 3 will determine the best path to take at the very start of the simulation and update the best path to take every tick of the simulation
//  After determining which path is most optimal, it will insert the elements in that path into a stack
//  Then we pop from the stack to get know which Node to go to next
//  This path updates based on the weights between each other Nodes in the graph
//  This class implements Algorithm2's algorithm, but runs it recurringly
//
////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "../headers/MovementAlgorithm.h"
#include "../headers/Algorithm2.h"

class Algorithm3 : public MovementAlgorithm{
    public:
        Algorithm3(const Node* const & startNode, const Node* const & endNode);
        //creates an algorithm 2 object
        //uses algorithm 2's stack of Car moves, and pops off from the front of this stack
        //moves the car in the specified direction of this move, so when this method is recalled, a new algorithm 2 object is created with different values
        //therefore updating the algorithm 2 getNextMove() to account for new instances of traffic every time this method is called
        Direction getNextMove();

        // copy constructor for a MovementAlgorithm pointer
        Algorithm3(const MovementAlgorithm* const & other);
};