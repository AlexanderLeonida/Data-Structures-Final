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
// Resources used: https://en.cppreference.com/w/cpp/language/enum
//
//
// Collaborators:
//
// Purpose of class:
// Direction represents a direction on a flat 2D array 
// It is assumed that the location [0][0] in this 2D array is in the north-west direction
// By implementing a Direction object, we allow for the allocating 
//
////////////////////////////////////////////////////////////////////////////////////////

#pragma once

enum class Direction{
    north = 0,
    south = 1,
    east = 2, 
    west = 3,
    none = 4
};