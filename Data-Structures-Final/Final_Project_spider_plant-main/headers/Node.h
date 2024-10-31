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
// Node represents an intersection in the city. Cars travel to and from Nodes. 
// Each Node holds the number of cars traveling away from it during each tick
// Each Node also holds where it is relative to the city, and can access other Node's in the city
//
////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Direction.h"
#include <list>

class Node{
    private:
        // the number of cars traveling away from the node during each tick. 
        // this number is directly proportional to the number of ticks it will take a car to clear this 'path' between Nodes
        // the value at index i of the array represents the weight (number of cars) traveling in that Direction (0 = north, etc)
        int weights[4];

        // x position of the node in 'grid' (left most column is 0)
        // equal to the column number of the node in 'grid'
        int xPos;

        // y position of the node in 'grid' (top most row is 0)
        // equal to the row number of the node in 'grid'
        int yPos;

        // square 2d array containing all Nodes
        // *this should be located at grid[yPos][xPos]
        Node*** grid;

        // number of elements in a row of 'grid'
        int gridSize;
    public:

        // default constructor sets variables to invalid numbers
        // should NEVER be explicitly called
        Node();

        // argumented constructor used to create a Node
        //param grid - square 2d array containing all Nodes in the City
        //param gridSize - number of elements in a row of 'grid'
        //param xPosition - x position of this in 'grid'. Should be equal to the column number of *this in 'grid'
        //param yPosition - y position of this in 'grid'. Should be equal to the row number of *this in 'grid'
        Node(Node*** & grid, int gridSize, int xPosition, int yPosition);

        // adds 'value' to the wieght in the 'dir' direction
        // throws std::invalid_argument if 'dir' is not a valid Direction
        // throws std::invalid_argument if a weight is negative after the function call
        // param value - the increase or decrease to the desired weight
        // param dir - the weight to be changed
        void updateWeight(int value, const Direction & dir);

        // throws std::invalid_argument if 'dir' is not a valid Direction
        // param dir - the direction of travel we want the weight for
        // return - the wieght in direction 'dir'
        int getWeight(const Direction & dir) const;

        // takes in Direction that the car is moving in 
        // returns true if car can move in passed in direction (if car does not fall of the grid)
        // returns false if, if the car moves in specified direction, it will move out of bounds of the city
        bool isValid(const Direction & dir) const;

        // returns xPos
        int getXPosition() const;

        // returns YPos
        int getYPosition() const;

        // returns gridSize
        int getGridSize() const;

        // returns a Node breference in the direction dir
        // throws std::out_of_range if a movement in 'dir' would move out of bounds
        // throws std::invalid_argument if 'dir' is not a valid Direction
        // param dir - Direction we wish to move in
        // return - Node one spot away from *this in the direction 'dir'. The Node returns by reference, so the Node will actually move after this method is called.
        Node*& move(const Direction & dir) const;

        // equality operator
        // param other - Node we want to compare to *this
        // return - true if 'other' has the same xPos and yPos as *this, false otherwise
        bool operator==(const Node & other) const;
        // non equality operator
        // param other - Node we want to compare to *this
        // return - true if 'other' does not have the same xPos and yPos as *this, false otherwise
        bool operator!=(const Node & other) const;
};