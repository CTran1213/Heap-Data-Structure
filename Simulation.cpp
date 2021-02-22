#include "Simulation.h"

Simulation::Simulation(int takers, int avgCalls, int avgService, int numBots)
{
   callTakers_ = takers;
   avgCallsPerSec_ = avgCalls / 3600;
   avgServiceTime_ = avgService;
   numBots_ = numBots;
   
   //Uniform Distribution to create bot callers
   default_random_engine generator;
   int number;
   uniform_int_distribution<int> uniform(1, 3600);

   for (int i = 0; i < numBots_; i++)
   {
      number = uniform(generator);
      bots_[i] = number;
   }

   //Exponential Distribution to create real callers
   int theInterval;
   int nextCallTime = 0;
   default_random_engine gen;
   exponential_distribution<double> expDist(avgCallsPerSec_);

   theInterval = int(ceil(expDist(generator)));
   while (nextCallTime <= 3600)
   {
      nextCallTime = nextCallTime + theInterval;
      
   }
}

bool Simulation::runSimulation()
{
   
   return true;
}