#include "../headers/MovementAlgorithm.h"

MovementAlgorithm::MovementAlgorithm(const Node* const & startNode, const Node* const & endNode){
     endingNode = endNode;
     startingNode = startNode;
}

MovementAlgorithm::MovementAlgorithm(const MovementAlgorithm* const & other){
     // copy all the values in
     this->endingNode = other->endingNode;
     this->startingNode = other->startingNode;
     this->path = other->path;
}
