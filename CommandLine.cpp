//CommandLine.cpp
//Catherine Tran ID: 2021829, 2/26/21
//The purpose of this program is to simulate the E911 DDoS Attacks. Uniform distribution 
//will be used to generate bot callers and poisson/exponential distribution will be used 
//to generate real calls and the average service time. A priority queue will be used to 
//hold theses calls/events. A queue will be used as a waiting list for the calls/events.
//This program simulates the E911 DDoS Attacks and will be used to test how the average 
//total service time will change depending on the number of bots. The inputs for this test will
// be 28 call takers, 246 call/hr, an average of 120 seconds to serve a legitimate call, and 
//the number of bots (the test variable) being {0, 100, 1000, 2000, 3000, 6000, 10000}. The 
//simulation will run 7 seven times, and we will see how the average total service time changes.
//The program’s input data is 4 things from the command line. The first input is the number of call 
//takers. The second input is the average number of legitimate calls per hour. This number will
//need to be divided by 3600 to get average calls per second. The third input is the average 
//legitimate call service time in seconds. This number will be used to generate real calls. 
//The reciprocal of this input lambda(s) which will be used for the service time exponential 
//distribution. The fourth input, the final input, is the number of bots. The simulation is 
//supposed to simulate 1hr, so the range of a bot call will show up between 1 to 3600 seconds.
//The output of the program is the average total service time for a legitimate call (time from when a 
//caller calls and hangs up). A graph plotting different number of bots and the average total service 
//time is expected in the submission, but not included in the program. The data from the graph comes 
//from running the program/simulation 7 times and will be graphed on excel and submitted with the program.
//Some errors to watch out for is if there are not enough command line arguments. A CERR would state 
//“Too many or too little arguments”. The time being generated for bots, real callers, and service time 
//should be less than 3600 so that should be checked when times are being generated.

#include "Simulation.h"
#include <iostream>
#include <random>
using namespace std;

#include <iostream>
using namespace std;

int main (int argc, char * const argv[]) {
   if (argc == 5)
   {
      int takers = stoi(argv[1]);
      double avgCalls = stoi(argv[2]);
      double avgService = stoi(argv[3]);
      int numBots = stoi(argv[4]);
      Simulation s = Simulation(takers, avgCalls, avgService, numBots);
      s.runSimulation();
   }
   else
   {
      cerr << "ERROR: Too many or too little arguments" << endl;
   } 
   return 0;
}
