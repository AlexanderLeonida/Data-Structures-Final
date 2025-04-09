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
//  Algorithm 2 will determine the best path to take at the very start of the simulation by using 
//  an implementation of Dijkstras algorithm. 
//  After determining which path is most optimal, it will insert the elements in that path into a stack.
//  Then we pop from the stack to get know which Node to go to next.
//
////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "../headers/MovementAlgorithm.h"
#include "../headers/AlgorithmObject.h"
#include <stack>
#include <list>
#include <vector>
using std::stack;
using std::list;
using std::vector;

class Algorithm2 : public MovementAlgorithm{
    protected:
        //takes in a node, a direction it's moving in, and a list of Algorithm Objects
        //method will update weight of Algorithm object if there is another path that has a lower weight to get to it
        //will resort the list of algorithm objects based on new assigned weights
        void updateAndSort(const Node* const & currentNode, Direction dir, list<AlgorithmObject> & li);
        //goes through container from starting point to ending point parameters until value param is found
        //returns iterator at specified point if value is found
        //if value is not found from starting point to ending point, iterator to the ending point is returned
        //to run through an entire container Ex. vector, pass in vector.begin() for the start param, vector.end() for the end param, and the value of the object being looked for within the vector
        //This method only looks for Nodes pointers, so containers must be of Node pointer type
        template <typename ItrType>
        ItrType find(ItrType start, ItrType end, const Node* const & value);
        //param li is a list of algorithm objects to be used in algorithms 2 and 3
        //param outOfPlace is an iterator of the algorithmObject which is out of place
        //sorts the list of algorithms objects from AlgorithmObject's weight from lowest to highest
        //to be used in the updateAndSort method
        void sort(list<AlgorithmObject> & li, list<AlgorithmObject>::iterator outOfPlace);
        //initializes list to be used for algorithms 2 and 3
        //li will end up with AlgorithmObjets holding Nodes of places all across the City with weights of infinity
        //li is to be initialized for the initVec() method
        void initList(list<AlgorithmObject> &li);
        //initializes vector to be used for algorithms 2 and 3
        //li param is a list with AlgorithmObject pointing to all Nodes across the City with infinity weights (except for the currentNode whos weight is 0).
        //reverses the order of the list into a vector
        //vec is to be initalized for initStack() method
        void initVec(list<AlgorithmObject> &li, vector<AlgorithmObject> &vec);
        //param vec is a vector of Algorithm Objects to be pushed to stk param
        //first param is the current Algorithm Object we are looking at. It is holds the currentNode value of startingNode. It's weight to get to itself is 0
        //method initializes the stack of moves to be used for the Car to get to its destination
        void initStack(const AlgorithmObject & first, vector<AlgorithmObject> &vec, stack<Direction> &stk);
        //calls initStack() implicitly, returns the stack of moves for the Car to get to its ending point
        //sets this return value to MovementAlgorithm's stack inside of the constructor
        //called within constructor
        stack<Direction> init();
        
    public:
        //calls init() and initializes stack of car moves
        Algorithm2(const Node* const & startNode, const Node* const & endNode);
        //pops off the top of stk which was initialized in the constructor 
        Direction getNextMove();

        // copy constructor for a MovementAlgorithm pointer
        Algorithm2(const MovementAlgorithm* const & other);
};