#include "../headers/Algorithm3.h"

Algorithm3::Algorithm3(const Node* const & startNode, const Node* const & endNode) : MovementAlgorithm(startNode, endNode){}

Algorithm3::Algorithm3(const MovementAlgorithm* const & other) : MovementAlgorithm(other){}

Direction Algorithm3::getNextMove(){
    //creates an algorithm 2 object
    //algorithm 3 is basically an updating algorithm 2, so every time getNextMove is called we create a new algorithm 2 object based on new data
    //algorithm 2 will change 'every time' this method is called because of the reinitialization that occurs in that class
    Algorithm2 alg = Algorithm2(startingNode, endingNode);
    //get the next move based on this new algorithm 2 object
    Direction dir = alg.getNextMove();
    //move the starting node in that direction. changes for the next call of this method
    startingNode = startingNode->move(dir);
    return dir;
}
