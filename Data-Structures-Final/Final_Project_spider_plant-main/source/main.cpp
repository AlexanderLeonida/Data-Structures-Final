#include "../headers/City.h"
#include <iostream>
#include <fstream>
#include <ctime> // srand
using std::ofstream;
using std::cout;
using std::endl;

int main(){
    //the name of the outputfile
    //we changed this
    std::string description = "20x20_Replace_Notraffic_RushHour";  
    //the size of the grid
    //we changed this
    int gridSize = 20;
    //the algorithm type for traffic
    int trafficAlgorithmType = 1;
    //seed for randomness
    int seed = time(NULL);
    //whether traffic is being replaced or not in the simulation. 
    bool replaceTraffic = true;
    //setting starting and ending points 
    //we changed these
    int lowXStart = 0;
    int highXStart = 1;
    int lowYStart = 0;
    int highYStart = gridSize;
    int lowXEnd = gridSize - 1;
    int highXEnd = gridSize;
    int lowYEnd = 0;
    int highYEnd = gridSize;


    ofstream file;
    //this is where the file is opened. if the file does not exist, it is created. 
    file.open("./OutputFiles/" + description + ".csv", std::ios::binary | std::ios::out);
    // checks that file path can be opened
    if(!file.is_open()){
        cout << "file failed to open";
    }
    //writes the description of the file being created to the top of the inside of file
    file << description << std::endl;
    //writes the headers for the different columns of the output
    file << "Number of Tracked Cars, Algorithm 1, Algorithm 2, Algorithm 3" << endl;
    //holds the data of the different number of cars being tracked. 
    //Ex. carsNumber[0] would mean that either there is 1 total car in the City, or that is how many cars we are tracking in the City, or both.
    int carsNumber[] = {1,2,3,4,6,8,12,16,24,32,48,64,96,128,192,256,384,512,768,1024};
    //goees through each element in carsNumber
    //this means we will track each number of cars in carsNumber because carsNumber size is 20
    for(int i = 0; i < 20; i++){
        //writes the number of cars into the file
        file << carsNumber[i];
        //loops through the different algorithm types
        for(int carAlgorithmType = 1; carAlgorithmType < 4; carAlgorithmType++){
            //pass in different carAlgorithmTypes into the simulation
            City c = City(gridSize, carsNumber[i], carsNumber[i], carAlgorithmType, trafficAlgorithmType, seed, replaceTraffic, lowXStart, highXStart, lowYStart, highYStart, lowXEnd, highXEnd, lowYEnd, highYEnd);
            file << "," << c.simulate();
        }
        //new line
        file << endl;
    }
    //close the file
    file.close();
    
}