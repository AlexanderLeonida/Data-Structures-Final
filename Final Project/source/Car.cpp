#include "../headers/Car.h"
#include <typeinfo> // dynamic cast in copy constructor
Car::Car(Node* & startNode, Node* & endNode, double speed, int algorithmType){
    ticksOnPath = 0;
    totalTime = 0;
    ticksNeededOnCurrentPath = 1;
    this->speed = speed;
    currentNode = startNode;
    endingNode = endNode;
    this->algorithmType = algorithmType;
    //sets algorithm instance var to one of the three algorithms we made based on the algorithm type that was passed in
    switch(algorithmType){
        case 1:
            algorithm = new Algorithm1(startNode, endingNode);
            break;
        case 2:
            algorithm = new Algorithm2(startNode, endingNode);
            break;        
        case 3:
            algorithm = new Algorithm3(startNode, endingNode);
            break;        
    }
    //set movement direction to wherever we ned to move next
    movementDirection = algorithm->getNextMove();
    //set nextNode to whereever we are currently moving to
    nextNode = currentNode->move(movementDirection);
    currentNode->updateWeight(1, movementDirection);
}

Car::~Car(){
   delete algorithm;
}

Car& Car::operator=(Car other){
    std::swap(*this, other);
    return *this;
}

Car::Car(const Car & other){
    // copy values in
    this->ticksOnPath = other.ticksOnPath;
    this->speed = other.speed;
    this->currentNode = other.currentNode;
    this->nextNode = other.nextNode;
    this->endingNode = other.endingNode;
    this->totalTime = other.totalTime;
    this->ticksNeededOnCurrentPath = other.ticksNeededOnCurrentPath;
    this->movementDirection = other.movementDirection;
    this->algorithmType = other.algorithmType;

    // create a new algorithm object to avoid double deallocation
    const std::type_info& id = typeid(*(other.algorithm)); // https://en.cppreference.com/w/cpp/language/typeid
    if(id == typeid(Algorithm1)){ 
        // https://en.cppreference.com/w/cpp/language/dynamic_cast
        this->algorithm = dynamic_cast<MovementAlgorithm *>(new Algorithm1(other.algorithm));
    }
    else if(id == typeid(Algorithm2)){
        this->algorithm = dynamic_cast<MovementAlgorithm *>(new Algorithm2(other.algorithm));
    }
    else if(id == typeid(Algorithm3)){
        this->algorithm = dynamic_cast<MovementAlgorithm *>(new Algorithm3(other.algorithm));
    }
}
 
void Car::update(){
    //checks if the car has made it to the ending node. if it has, return immediately
    //so that the car doesn't continue to increment ticks if it's finished
    if(isFinished()){
        return;
    }
    //checks if the car is not at it's next node yet (on the path between nodes or moving to the next node)
    if (ticksNeededOnCurrentPath > ticksOnPath){
        totalTime++; //increment total time 
        ticksOnPath++; //increment time on path so that the car can eventually move OFF of the path
        return;
    }
    //if we made it past the last conditional, we can assume the car has made it to a new node
    //update the weight of the node from direction we came from. -1 means 1 car has left that path, and there is 1 less traffic now
    currentNode->updateWeight(-1, movementDirection);
    //set our current node to the node we just made it to 
    currentNode = nextNode;
    if(isFinished()){
        return;
    }
    //find a new 'next node' to go to and set it to movement direction
    //we now know which way we're going to hit our next node based on the algorithm
    movementDirection = algorithm->getNextMove();
    //move in that direction.
    nextNode = currentNode->move(movementDirection);
    //setting ticks needd on current path to the current node's weight and dividing it by speed. 
    //aka how much time in traffic it takes to get to the next node (lets say 6), then dividng it by the cars speed (lets say 2), then this would take 6/2=3 ticks. )
    ////////////////////////////////////////////////////////////////////////////
    ticksNeededOnCurrentPath = int(currentNode->getWeight(movementDirection));
    ////////////////////////////////////////////////////////////////////////////
    //once we set our next node a tick has gone by, and we increment time
    totalTime++;
    //now there's a car on the path to the next node it's going to, and we increase the traffic in that direction by 1
    currentNode->updateWeight(1, movementDirection);
    //there's now been one tick on the path
    ticksOnPath = 1;
}

bool Car::isFinished() const{
    //checks if the car has made it to its destination 
    return currentNode == endingNode;
}

int Car::getTime() const{
    //returns total time car has been on the track for
    return totalTime;
}
