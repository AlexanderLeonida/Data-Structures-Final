#include "../headers/Algorithm2.h"
#include "../headers/City.h"
#include "../headers/AlgorithmObject.h"
#include <climits> // INT_MAX

Algorithm2::Algorithm2(const Node* const & startNode, const Node* const & endNode) : MovementAlgorithm(startNode, endNode){
    path = init();
}

Direction Algorithm2::getNextMove(){
    //check if the path is empty. if it is, we can assume the car has made it to it's destination, and we can return Direction::none. 
    //if the path is empty, and the car is not at it's destination, something has went terribly wrong
    if(path.empty()){
        return Direction::none;
    }
    //holds var for top of stack (next move)
    Direction ret = path.top();
    //removes next move from path var
    path.pop();
    //return next move
    return ret;
}

Algorithm2::Algorithm2(const MovementAlgorithm* const & other) : MovementAlgorithm(other){}

void Algorithm2::initList(list<AlgorithmObject> &li){
    // sets our temporary Node to the top left of the grid
    const Node* temp = startingNode;
    //if the X position of the node is not on the very left, move it left
    while(temp->getXPosition() > 0){
        temp = temp->move(Direction::west);
    }
    //if the Y position of the node is not on the very top, move it up
    while(temp->getYPosition() > 0){
        temp = temp->move(Direction::north);
    }

    li.push_back(AlgorithmObject(startingNode, Direction::none, 0));
    // temp in the upper left corner
    const Node* temp2 = temp;
    //checks every row in grid
    for(int i = 0; i < temp->getGridSize(); i++){
        temp = temp2;
        //checks every column in row in grid
        for(int j = 0; j < temp->getGridSize(); j++){
            //if the temp node != starting node, set it's value to infinity
            if(temp != startingNode){            
                //setting the "unknown" distance between the starting node and every other node as 'infinity' for case of Dijkstras algorithm
                li.push_back(AlgorithmObject(temp, Direction::none, INT_MAX));
            }
            //moving the temporary node one spot to the right every iteration, except for the last Node (because then it would go out of bounds)
            //in this way, we are essentially checking every single Node on a specific horizontal line in the City
            if(j != temp->getGridSize() - 1){
                temp = temp->move(Direction::east);
            }
        }
        //moving the temporary node one spot to down every iteration, except for the last Node (because then it would go out of bounds)
        //in this way, we are essentially checking every single Node on row in the City
        if(i != temp->getGridSize() - 1){
            temp2 = temp2->move(Direction::south);
        }
    }
}

void Algorithm2::initVec(list<AlgorithmObject> &li, vector<AlgorithmObject> &vec){
    //loops until either the AlgorithmObject's currentNode is equal to the endingNode, or until the list is empty (in which case there's a huge problem)
    while(li.front().currentNode != endingNode){
        //sets current var to the AlgorithmObject's currentNode attribute
        const Node* current = li.front().currentNode;
        //run updateAndSort for each possible direction of the Node. See updateAndSort for more information
        updateAndSort(current, Direction::north, li);
        updateAndSort(current, Direction::east, li);
        updateAndSort(current, Direction::south, li);
        updateAndSort(current, Direction::west, li);
        //pushback the front of the list to the vector to be used for our algorithm
        vec.push_back(li.front());
        li.pop_front();
    }
}

void Algorithm2::initStack(const AlgorithmObject &first, vector<AlgorithmObject> &vec, stack<Direction> &stk){
    //hold ptr to first node
    const Node* storedNode = first.currentNode;
    //hold first direction of first node
    Direction storedDirection = first.dir;
    //use for vec
    vector<AlgorithmObject>::iterator itr;
    //node only has == defined
    while(!(storedNode == startingNode)){
        //push direction of algorithm object
        stk.push(storedDirection);
        if(int(storedDirection) % 2 == 1){
            storedDirection = Direction(int(storedDirection) - 1);
        } else {
            storedDirection = Direction(int(storedDirection) + 1);
        }
        //move the node in its specified direction 
        storedNode = storedNode->move(storedDirection);
        //find where the node is now, and store its new direction 
        //if it reached a new node, its direction will be different
        itr = find(vec.begin(), vec.end(), storedNode);
        storedDirection = itr->dir;
    }  
}

stack<Direction> Algorithm2::init() {
    //contianers to be passed in 
    list<AlgorithmObject> li = list<AlgorithmObject>();
    vector<AlgorithmObject> vec = vector<AlgorithmObject>();
    stack<Direction> stk = stack<Direction>();
    //initialize the list
    initList(li);
    //so we can initialize the vector
    initVec(li, vec);
    //so we can initialize the stack of directions for our car
    initStack(li.front(), vec, stk);
    return stk;
}

void Algorithm2::updateAndSort(const Node* const & currentNode, Direction dir, list<AlgorithmObject> & li) {
    int weight = currentNode->getWeight(dir);
    //checks if the curentNode can move in the passed in direction
    //if we can't updateAndSort does nothing
    if(currentNode->isValid(dir)){
        // itrator to where the movement will take us
        list<AlgorithmObject>::iterator itr = find(li.begin(), li.end(), currentNode->move(dir));
        //checking if the iterator actually found something in the list. if it didn't, the iterator would have went through the whole list and stopped at .end()
        if(itr != li.end()){
            //set newweight var to weight of currentNode's moving direction plus the weight of the currentNode
            int newWeight = weight + find(li.begin(), li.end(), currentNode)->weight;
            //checks if the previous weight to get to the spot we are at specified by AlgorithmObject is more than the newWeight we just checked
            //change everything
            if(itr->weight > newWeight){
                //reassign all variables for our algorithm object 
                //(we found a new better path to get to this new Node)
                itr->dir = dir;
                itr->weight = newWeight;
                sort(li, itr);
            }
        }
    }
}

void Algorithm2::sort(list<AlgorithmObject> & li, list<AlgorithmObject>::iterator outOfPlace) {
    //checking if the iterator is pointing to the beginning of the list
    //if it is, it's not out of place and there's nothing to remove so we return 
    if(outOfPlace == li.begin()){
        return;
    }
    //create a new iterator object that will hold the spot of the outOfPlace iterator. 
    list<AlgorithmObject>::iterator toBeRemoved = outOfPlace;
    //AlgorithmObject to be removed is the dereferenced iterator
    AlgorithmObject theElement = *outOfPlace;
    //holding the weight of the Algorithm object
    int theWeight = outOfPlace->weight;
    //loop until we get to the beginning of the list
    while(outOfPlace != li.begin()){
        //increments outOfPlace iterator in the conditional
        //checks if the weight of the original outOfPlace iterator is greater than the weight of the new outOfPlace iterator
        if(theWeight >= (--outOfPlace)->weight){
            //if it is we remove the original outOfPlace object from the list
            li.erase(toBeRemoved);
            //and insert the outOfPlace iterator back in one spot in front of the other iterator we checked
            li.insert(++outOfPlace, theElement);
            return;
        }
    }
    //remove the iterator from the list
    li.erase(toBeRemoved);
    //add it to the front of the list
    li.push_front(theElement);
}

template <typename ItrType>
ItrType Algorithm2::find(ItrType start, ItrType end, const Node* const & value) {
    //goes through itrtype container, in this case a list and vector
    while(start != end){
        //if the current node of the start is the same as the value being passed in (ptrs)
        if(start->currentNode == value){
            //return the iterator we found the value at
            return start;
        }
        //if not, keep searching through the container
        start++;
    }
    //if it's not there, return end. start is now end. the way this is called in scope of this prorgram means it's a vec or l.end(), outside the scope of the container
    return start;
}