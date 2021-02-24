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
      int avgCalls = stoi(argv[2]);
      int avgService = stoi(argv[3]);
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
