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

   default_random_engine gen2;                    
   exponential_distribution<double> expDist1(887/3600.0);

   double avgTime = (ceil(expDist1(gen2)));
   cout << expDist1(gen2)<< endl;
   
   return 0;
}
