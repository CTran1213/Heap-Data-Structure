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
	
   Event a = Event("A", 3, 3,0);
   Event b= Event("A", 5, 3,0);
   Event c = Event("A", 2, 6,0);

   PrioQueue x;
   x.enqueue(a);
   x.enqueue(b);
   x.enqueue(c);

   x.dequeue();
   x.enqueue(a);
   x.Display();

   return 0;
}
