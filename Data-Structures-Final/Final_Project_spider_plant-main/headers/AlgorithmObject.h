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
// Algorithm Object class is used for our implementation of Dijkstras algorithm. 
// For this algorithm, we need to keep track of the Node we're currently checking, the direction it is moving in, and the weight of the current Node.
//
////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "../headers/Node.h"
#include "../headers/Direction.h"

struct AlgorithmObject{
    //holds currrent Node the object is at
    const Node* const currentNode;
    //holds the direction that the object is traveling at
    Direction dir;
    //holds the weight of the Node
    int weight;
    //default constructor
    AlgorithmObject() : currentNode(nullptr), dir(Direction()), weight(int()) {}
    //fully argumented constructor
    //param currentNode_ = currentNode
    //param dir_ = dir
    //param weight_ = weight
    AlgorithmObject(const Node* const currentNode_ , Direction dir_ , int weight_) : currentNode(currentNode_), dir(dir_), weight(weight_) {}
};