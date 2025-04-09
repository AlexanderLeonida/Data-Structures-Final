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
// moves two directions, makes one turn
// goes east/west first, then north or south
//
////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "../headers/MovementAlgorithm.h"

class Algorithm1 : public MovementAlgorithm{
    private:
        //returns the direction for the next move
        //by returning oneMove (the next 'best' move) according the the Algorithm, we can add this direction to the stack<Direction> path variable
        //by popping from the stack we can getNextMove(), and find our way through the grid in this way
        Direction getOneMove(const Node* & currentNode);
        //returns stack of moves in order to get from the Car's starting Node the ending Node
        //we set the return value of this method to path var in MovementAlgorithm
        stack<Direction> init();
    public:
        Algorithm1(const Node* const & startNode, const Node* const & endNode);
        //pops from the top of the stack which was initalized in init() to get the next move for the car
        Direction getNextMove();

        // copy constructor for a MovementAlgorithm pointer
        Algorithm1(const MovementAlgorithm* const & other);
};