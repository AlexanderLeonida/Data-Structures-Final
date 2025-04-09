# User Manual for Final_Project_Spider_Plant
Noah Dunham and Alex Leonida

**Choose Only One Option**
1. Table of Contents Steps 1-2
2. Table of Contents Step 3

**Do Not Do Both**

## Table of Contents
**[Troubleshooting](#troubleshooting)**
1. [Running the Program](#section-1-running-the-program)
2. [Interpreting Results](#section-2-interpreting-results)
3. [Create Output Files](#section-3-create-output-files)
4. [Reset](#reset)


## Troubleshooting
If you follow the manual and at any point you feel that you are at the wrong step
1. Reread the last instruction in the manual. Did you miss something?
2. If the terminal is blank, is the terminal stuck, or is the program still running?
3. [Double check](#variables) the order of the parameters being input into the creation of a City Object  
4. Is the [simulate() method](#simulate) being printed to the terminal via std::cout?
5. If you are somehow stuck in an **INFINITE** loop, press "fn" + "c" or "control" + "c" to end the process and try to [run](#section-1-running-the-program) the program again with different values.
6. If everything went wrong, reset [main.cpp](../source/main.cpp) to one of it's original states [here](#reset)


## Section 1: Running the Program
### Overview
1. If you have not already, read the [documentation](./documentation.md) file.
2. Creating a City requires many decisions, and all are [required](#variables) for the creation of this object.
3. [Insert](#create-a-city) values decided upon into program. Create City object!
4. [Simulate](#simulate) the City you created!

### Variables
1. gridSize
   * This will be an integer of minimum 2. This integer will represent both the height and length of this City. Choosing a size of 2 for the City will result in a 2 x 2 square grid as the shape of the City.
   * **IMPORTANT**: Do *NOT* create a size 1 City. This will result in the breaking of the program. There should be little reason to create a size 1 City for the purposes of this application. If there is a reason to create a size 1 City, assume that the travel time from the starting Node to the ending Node is 0.
2. numberOfTrackedCars
   * This will be a positive integer. This integer will be the number of cars being tracked in the simulation. These cars will determine the output of the simulation; the average time it takes for these cars to reach their destination.
3. totalNumberOfCars
   * This will be a positive integer, larger than numberOfTrackedCars. This integer will be the total number of cars in the simulation including both Cars being tracked, and Cars not being tracked. If the (replaceTraffic) parameter is set to 'true', this number will stay constant.
4. carAlgorithmType
   * This will be an integer from 1-3.
       * Selecting 1 will set all of the cars being tracked to an algorithm that has no knowledge about the traffic within the City, and will naively move in only two directions before reaching the destination.
       * Selecting 2 will set all of the cars being tracked to an algorithm which has knowledge of the traffic within the City only at the beginning of the simulation. With this knowledge, the car will move in the most optimal path towards it's destination regardless of the changes in traffic.
       * Selecting 3 will set all of the cars being tracked to an algorithm which has knowledge of the traffic within the city the during the entire simulation. With this knowledge, the car will move in the most optimal next move while considering the traffic as well.
5. trafficAlgorithmType
   * This will be an integer from 1-3.
       * The three options are the same are carAlgorithmType
6. seed
   * This will be an integer.
       * This seed will determine the randomness of the cars within the simulation
       * Use time(NULL) for a different random value each simulation
7. replaceTraffic
   * This will be a boolean (true or false)
       * If true: Each time a Car reaches its destination, a traffic Car will spawn in to replace the one that just left. With this in mind, the total number of Cars will stay constant throughout the entire simulation. This will lead to a more stable tracking of the time it takes for Cars to get to their destination.
       * If false: Each time a Car reaches its destination, no other Cars will spawn. With this in mind,the total number of Cars will decrease throughout the simulation. This will lead to an exponential decrease in the time it takes tracked Cars to get to their destination.
       * **IMPORTANT**: Do *NOT* select 'true' for this variable if numberOfTrackedCars = 0 within the City, and where the totalNumberOfCars > O. This will result in the breaking of the program.
8. lowXStart
   * This will be an integer between 0 and gridSize - 1, and must be lower than highXStart
       * Represents the lowest X value that a Car can start on the grid
9. highXStart
   * This will be an integer between 0 and gridSize - 1, and must be higher than lowXStart
       * Represents the highest X value that a Car can start on the grid
10. lowYStart
   * This will be an integer between 0 and gridSize - 1, and must be lower than highYStart
       * Represents the lowest Y value that a Car can start on the grid
11. highYStart
   * This will be an integer between 0 and gridSize - 1, and must be higher than lowYStart
       * Represents the highest Y value that a Car can start on the grid
12. lowXEnd
   * This will be an integer between 0 and gridSize - 1, and must be lower than highXEnd
       * Represents the lowest X value that a Car can end on the grid
13. highXEnd
   * This will be an integer between 0 and gridSize - 1, and must be higher than lowXEnd
       * Represents the highest X value that a Car can end on the grid
12. lowYEnd
   * This will be an integer between 0 and gridSize - 1, and must be lower than highYEnd
       * Represents the lowest Y value that a Car can end on the grid
13. highYEnd
   * This will be an integer between 0 and gridSize - 1, and must be higher than lowYEnd
       * Represents the highest Y value that a Car can end on the grid


### Create A City
Insert values decided upon seperated by a comma into the City constructor to create a City object.
An example is shown below
```cpp
City c1 = City(7, 5000, 5000, 1, 1, 1, true, 0, 5, 0, 5, 0, 5, 0, 5);
//or
City c1(7, 5000, 5000, 1, 1, 1, true, 0, 5, 0, 5, 0, 5, 0, 5);
```
In this example, c1 is the name of the City, and the variables passed in are based on the 13 decisions chosen above. These decisions are placed into the constructor in order. In this example, the gridSize for the City c1 will be 7 (a 7 x 7 grid), and the replaceTraffic variable will be set to 'true'.

### Simulate
After inserting values into City, and creating the City object, simulate the City by calling the simulate() method.
An example is shown below
```cpp
//Creating the City object
City c1 = City(7, 5000, 5000, 1, 1, 1, true, 0, 5, 0, 5, 0, 5, 0, 5);
//Running the simulation
cout << c1.simulate() << endl;
```
In this example, c1 is the name of the City being created, and we are calling the simulate method on this city. Because the simulate method does not inherently print anything out to the console itself, we need to print out the simulate method. If there is a *problem* using the cout statement, type the following at the top of the program
```cpp
#include<iostream>
using std::cout;
using std::endl;
```

## Section 2: Interpreting Results
The program should have printed out a double within the console. The output shown showcases the average time it took for the Cars being tracked to get to their destination based on the values that you chose during the creation of the City. 

Comparing, and contrasting different combinations of these Cities will lead to interesting results. 

## Section 3: Create Output Files
If you have not already, read the [documentation](./documentation.md) file. This will describe the different parameters being used to create files. 

1. Enter [main.cpp](../source/main.cpp)
2. Change desired parameters from line 10-31 of this file
   * Understand, and then follow the naming conventions as described in the [documentation](./documentation.md) file
3. **if** you wish to create more traffic than tracked cars in this simulation, go [here](#create-more-traffic)
4. Run the program
   * Build the program
   * Run the program
   * A file should be created under the 'OutputFiles' folder. 
5. Analyze results
   * Reference the [documentation](./documentation.md) file for more information if needed. 

### Create More Traffic
On line 56 of [main.cpp](../source/main.cpp), it should look like this
```cpp
City c = City(gridSize, carsNumber[i], carsNumber[i], carAlgorithmType, trafficAlgorithmType, seed, replaceTraffic, lowXStart, highXStart, lowYStart, highYStart, lowXEnd, highXEnd, lowYEnd, highYEnd);
```
If it does not, find the line that looks like this. 
Once this line is located, notice that there are two 'carsNumber[i]' parameters within the City constructor. Choose the second parameter, and multiply it by an integer. It should look like this

```cpp
City c = City(gridSize, carsNumber[i], carsNumber[i]*5, carAlgorithmType, trafficAlgorithmType, seed, replaceTraffic, lowXStart, highXStart, lowYStart, highYStart, lowXEnd, highXEnd, lowYEnd, highYEnd);
```
In doing so, you have just created more traffic within the City than the number of Cars that are being tracked. Because traffic is the total number of cars within the City - the number of tracked cars, in reality, this would be a 400% traffic to Car ratio.

## Reset
Everything went wrong. It happens. 
Copy and paste this code into [main.cpp](../source/main.cpp) if you were attempting Table of Contents Steps 1-2
```cpp
#include "../headers/City.h"
#include <iostream>
#include <ctime> // srand
using std::cout;
using std::endl;

int main(){
   City c = City(5, 10, 10, 3, 1, time(NULL), true, 1, 2, 1, 2, 3, 4, 3, 4);
   c.simulate();
}
```

Copy and paste this code into [main.cpp](../source/main.cpp) if you were attempting Table of Contents Step 3
```cpp
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
```