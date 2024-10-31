#include "../headers/City.h"
#include <random>

int City::genRandom(int low, int high){
    if(high == low){
        return low;
    }
    return (rand() % (high - low)) + low;
}

City::City(int gridSize, int numberOfTrackedCars, int totalNumberofCars, int carAlgorithmType, int trafficAlgorithmType, int seed, bool replaceTraffic, int lowXStart, int highXStart, int lowYStart, int highYStart, int lowXEnd, int highXEnd, int lowYEnd, int highYEnd){
    // copies values into the object
    this->gridSize = gridSize;
    this->numberOfTrackedCars = numberOfTrackedCars;
    this->carAlgorithmType = carAlgorithmType;
    this->highXEnd = highXEnd;
    this->highXStart = highXStart;
    this->highYEnd = highYEnd;
    this->highYStart = highYStart;
    this->lowXEnd = lowXEnd;
    this->lowYEnd = lowYEnd;
    this->lowXStart = lowXStart;
    this->lowYStart = lowYStart;
    this->replaceTraffic = replaceTraffic;
    this->trafficAlgorithmType = trafficAlgorithmType;

    // seeds srand() for genRandom() calls later
    srand(seed);
    // initializes grid
    initGrid();

    // creates traffic before tracked cars
    for(int i = 0; i < totalNumberofCars - numberOfTrackedCars; i++){
        generateTrafficCar();
    }
    // creates the tracked cars
    for(int i = 0; i < numberOfTrackedCars; i++){
        generateTrackedCar();
    }

}

void City::generateTrackedCar(){
    //generates random values for the starting and ending values of the cars
    int startx = genRandom(lowXStart, highXStart);
    int starty = genRandom(lowYStart, highYStart);
    int endx = genRandom(lowXEnd, highXEnd);
    int endy = genRandom(lowYEnd, highYEnd);
    //checking if user has created a grid larger than size 1, but is setting the starting and ending values to that if it was a City of size 1
    if(startx == endx && starty == endy ){
        //this will recursively explode if the grid is size 1
        generateTrackedCar();
        return;
    }
    //adding a new car to be tracked in the simulation in the new specified starting and ending position
    //each time this method is called, a 'new' value from genRandom() will be returned
    cars.push_back(Car(grid[starty][startx], grid[endy][endx], (((double)genRandom(0,5))*0.1) + 0.5, carAlgorithmType));
}

void City::generateTrafficCar(){
    //generating starting and ending values between the specified parameters entered into the City object upon creation 
    int startx = genRandom(lowXStart, highXStart);
    int starty = genRandom(lowYStart, highYStart);
    int endx = genRandom(lowXEnd, highXEnd);
    int endy = genRandom(lowYEnd, highYEnd);
    //will explode stack recursively in a 1 x 1 grid
    if(startx == endx && starty == endy ){
        generateTrafficCar();
        return;
    }
    traffic.push_back(Car(grid[starty][startx], grid[endy][endx], (((double)genRandom(0,5))*0.1) + 0.5, carAlgorithmType));
}

void City::initGrid(){
    //pointer to our 2d grid of the City
    Node*** array = new Node**[gridSize];
    for(int i = 0; i < gridSize; i++){
        //reinitializing grid in a new variable
        array[i] = new Node*[gridSize];
    }
    //shallow copy, we don't need to deallocate memory for array, just grid
    grid = array;
    //parsing through the entire 2D array we just created memory space for
    for(int row = 0; row < gridSize; row++){
        for(int col = 0; col < gridSize; col++){
            //populating the spaces in the array to Node object with its xPosition and yPosition inside of it 
            grid[row][col] = new Node(grid, gridSize, col, row);
        }
    }
}

double City::simulate(){
    //bubble sort sort of structure
    bool allDone = false;
    while(!allDone){
        allDone = true;
        //runs through our list of cars and updates each of them
        for(list<Car>::iterator itr = cars.begin(); itr != cars.end(); itr++){
            bool finished = itr->isFinished();
            itr->update();
            //if the car has not reached it's destination, run the loop again 
            if(!itr->isFinished()){
                allDone = false;
            //if the car has reached it's destination check if we're supposed to replace it with a traffic car
            //and if the simulation is not finished
            //if both are true, generate a new traffic car
            } else if(replaceTraffic && !finished){
                generateTrafficCar();
            }
        }
        //checks all of the traffic cars
        for(list<Car>::iterator itr = traffic.begin(); itr != traffic.end(); itr++){
            //update the traffic aswell, so they know where they're going too. 
            //last time we updated the states of the cars we are keeping track of, this time we update the states of the traffic
            itr->update();
            //if traffic car is finished
            if(itr->isFinished()){
                list<Car>::iterator temp = itr;
                itr--;
                //delete the traffic car that reached its end point
                traffic.erase(temp);
                //and make a new one
                if(replaceTraffic){
                    //only if replaceTraffic is true
                    generateTrafficCar();
                }
            }
        }
    }


    //keeps track of the total number of ticks it took all of our cars being tracked to get to where they needed to get to 
    int count = 0;
    for(list<Car>::iterator itr = cars.begin(); itr != cars.end(); itr++){
        //add each cars total time to count variable
        count += itr->getTime();
    }   
    //return the total number of time it took all of our cars to get to their destination by the number of cars
    //this is essentially the average number of ticks it took each car to get to it's destination (of the ones tht we were tracking)
    return (double)count / (double)numberOfTrackedCars;
}

City::~City(){
    //deallocate memory
    for(int i = 0; i < gridSize; i++){
        for(int j = 0; j < gridSize; j++){
            delete grid[i][j];
        }
        delete[] grid[i];
    }
    delete[] grid;
}