#include "../headers/Algorithm1.h"

Algorithm1::Algorithm1(const Node* const & startNode, const Node* const & endNode) : MovementAlgorithm(startNode, endNode){
    path = init();
}

stack<Direction> Algorithm1::init() {
    //initializinig all values
    stack<Direction> temp = stack<Direction>();
    const Node* tempNode = startingNode;
    //runs until we have our stack completely full of moves for our car to make
    while(tempNode != endingNode){
        //add Direction for the next best move to make to temp stack
        temp.push(getOneMove(tempNode));
        //set tempNode to the next move that you just added
        //temp is a stack, so we add a move to the top of the stack, and then access the top (the move we just added)
        //by moving the tempNode in this way, we will eventually get to the ending location based on our getOneMove method
        tempNode = tempNode->move(temp.top());
    }
    //reverse order of stack because stacks are FILO, and queues are FIFO. 
    stack<Direction> final_ = stack<Direction>();
    //for every Direction in temp
    while(!temp.empty()){
        //add the top element from temp stack to the final stack
        final_.push(temp.top());
        //remove from the top element from temp
        temp.pop();
    }
    return final_;
}

Algorithm1::Algorithm1(const MovementAlgorithm* const & other) : MovementAlgorithm(other){}

Direction Algorithm1::getNextMove(){
    //checks if the path var is empty. if it is, we know that the is either at it's destination, or something has went terribly wrong
    if(path.empty()){
        return Direction::none;
    }
    //holds variable for the next direction to move to 
    Direction d = path.top();
    //removes the next move from the stack because we are going to the car in this direction
    path.pop();
    //return the next direction we're going to move to
    return d;
}

Direction Algorithm1::getOneMove(const Node* & currentNode) {
    //holds the direction we're returning in variable
    Direction ans;
    //move until we are at the same x position as the ending position 
    if (currentNode->getXPosition() == endingNode->getXPosition()){
        //if we are below the y positiion we move north (we will eventually hit the ending node because we are on the same x position and incrementing up to the final node destination)
        if (currentNode->getYPosition() < endingNode->getYPosition()){
            ans = Direction::south;
        }else{
            ans = Direction::north;
        }
    }
    //if we are to the left of the ending Node (not the same x position)
    else if (currentNode->getXPosition() < endingNode->getXPosition()){
        //move west
        ans = Direction::east;
    } else{
        //else move east because we are on the left
        ans = Direction::west;
    }
    return ans;
}