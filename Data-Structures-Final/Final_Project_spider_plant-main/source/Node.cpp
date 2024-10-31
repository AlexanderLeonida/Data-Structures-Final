#include "../headers/Node.h"
#include <stdexcept>

Node::Node(){
    // sets values to impossible values
    // this should never be explicitly called
    for(int i = 0; i < 4; i++){
        weights[i] = -1;
    }
    gridSize = -1;
    xPos = -1;
    yPos = -1;
}

Node::Node(Node*** & grid, int gridSize, int xPosition, int yPosition){
    // sets all weights to 1 because there are no cars on the road, but each road takes some time to travel down
    for(int i = 0; i < 4; i++){
        weights[i] = 1;
    }
    // copies remaining data in
    this->grid = grid;
    this->gridSize = gridSize;
    xPos = xPosition;
    yPos = yPosition;
}

void Node::updateWeight(int value, const Direction & dir){
    // if the move is none, don't do anything
    if(int(dir) == 4){
        return;
    }
    // if the dir is not a valid direction, throw an exception
    if(int(dir) < 0 || int(dir) > 3){
        throw std::invalid_argument("Argument was not a valid Direction");
    }
    // add value to weight
    weights[int(dir)] += value;
    // if the weight is negative, there are negative cars on the road
    // throw an exception
    if(weights[int(dir)] < 1){
        throw std::invalid_argument("Can not have a non-positive weight.");
    }
}

int Node::getWeight(const Direction & dir) const {
    // if the dir is not a valid direction, throw an exception
    if(int(dir) < 0 || int(dir) > 3){
        throw std::invalid_argument("Argument was not a valid Direction");
    }

    // return the weight
    return weights[int(dir)];
}

int Node::getXPosition() const{
    return xPos;
}

int Node::getYPosition() const{
    return yPos;
}

int Node::getGridSize() const{
    return gridSize;
}

bool Node::isValid(const Direction & dir) const{
    // switch the direction with the appropriate Node
    switch(dir){
        // if we are moving north
        case Direction::north:
            // if *this stays in range with this move
            if(yPos - 1 >= 0){
                // return true
                return true;
            } else {
                // otherwise, it is out of bounds and return false
                return false;
            } 
            break;
        // if we are moving west
        case Direction::west:
            // if *this stays in range with this move
            if(xPos - 1 >= 0){
                // return true
                return true;
            } else {
                // otherwise, it is out of bounds and return false
                return false;
            } 
            break;
        // if we are moving south
        case Direction::south:
            // if *this stays in range with this move
            if(yPos + 1 < gridSize){
                // return true
                return true;
            } else {
                // otherwise, it is out of bounds and return false
                return false;
            } 
            break;
        // if we are moving east
        case Direction::east:
            // if *this stays in range with this move
            if(xPos + 1 < gridSize){
                // return true
                return true;
            } else {
                // otherwise, it is out of bounds and return false
                return false;
            } 
            break;
        // if we are not moving
        case Direction::none:
            // not moving will always result in bounds
            return true;
    }

    // if none of the cases matched 'dir', it was an invalid Direction
    // throw an exception
    throw std::invalid_argument("Argument was not a valid Direction");
}

Node*& Node::move(const Direction & dir) const{
    // if the direction takes us out of bounds, throw an exception
    if(!isValid(dir)){
        throw std::out_of_range("Tried to move out of bounds of Grid");
    }
    // switch the direction with the appropriate Node
    switch(dir){
        // if we are moving north
        case Direction::north:
                // return the value one up from *this
                return grid[yPos - 1][xPos];
            break;
        // if we are moving west
        case Direction::west:
                // return the value one to the right from *this
                return grid[yPos][xPos - 1];
            break;
        // if we are moving south
        case Direction::south:
                // return the value one down from *this
                return grid[yPos + 1][xPos];
            break;
        // if we are moving east
        case Direction::east:
                // return the value one down from *this
                return grid[yPos][xPos + 1];
            break;
    }
    // the passed direction was Direction::none, so we return where we are
    return grid[yPos][xPos];
}

bool Node::operator==(const Node & other) const{
    // return true if the xPos and yPos of 'other' and *this match eachother
    return other.xPos == this->xPos && other.yPos == this->yPos;
}

bool Node::operator!=(const Node & other) const{
    // return true if the xPos and yPos of 'other' and *this do NOT match eachother
    return !(*this == other);
}