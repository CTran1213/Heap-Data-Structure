#include "Simulation.h"
#include <iostream>
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
   }
   else
   {
      cerr << "ERROR: Too many or too little arguments" << endl;
   }
	
   default_random_engine generator;
   int number;
   vector<int> bots_;
   uniform_int_distribution<int> uniform(1, 3600);

   for (int i = 0; i < 10; i++)
   {
      number = uniform(generator);
      bots_.push_back(number);
   }

   for (int i = 0; i < 10; i++)
   {
      cout << bots_[i] << endl;
   }
   return 0;
}
