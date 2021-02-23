#include "Simulation.h"

Simulation::Simulation(int takers, int avgCalls, int avgService, int numBots)
{
   callTakers_ = takers;
   avgCallsPerSec_ = avgCalls / 3600;
   avgServiceTime_ = avgService;
   numBots_ = numBots;
   currentTime_ = 0;
}



bool Simulation::runSimulation()
{
   
   return true;
}

bool Simulation::generateCallers()
{
   //Uniform Distribution to create bot callers
   default_random_engine generator;
   int number;
   uniform_int_distribution<int> uniform(1, 3600);

   for (int i = 0; i < numBots_; i++)
   {
      number = uniform(generator);
      Event e = Event("B", number, 6, 0);
      events_.enqueue(e);
   }

   //Exponential Distribution to find the average time a real call takes
   default_random_engine gen2;                    
   exponential_distribution<double> expDist1(1/avgServiceTime_);

   avgServiceTime_ = int(ceil(expDist1(gen2)));

   //Exponential Distribution to create real callers
   int theInterval;
   int nextCallTime = 0;
   default_random_engine gen;
   exponential_distribution<double> expDist2(avgCallsPerSec_);

   Event first = Event("A", 0, avgServiceTime_, 0);
   events_.enqueue(first);
   theInterval = int(ceil(expDist2(gen)));
   while (nextCallTime <= 3600)
   {
      nextCallTime = nextCallTime + theInterval;
      Event e = Event("A", nextCallTime, avgServiceTime_, 0);
      events_.enqueue(e);
   }

   return true;
}

bool Simulation::processEvent(Event call)
{
   int departTime;
   if (call.getEventType().compare("D") != 0 && callTakers_ != 0)
   {
      if (call.getEventType().compare("B") == 0)
      {
         callTakers_--;
         departTime = call.getTime() + call.getServiceLength();
         Event e = Event("B", departTime, call.getServiceLength(), 0);
         events_.enqueue(e);
      }
      else
      {
         callTakers_--;
         departTime = call.getTime() + call.getServiceLength();
         Event e = Event("D", departTime, call.getServiceLength(), 0);
         events_.enqueue(e);
      }
   }
   else if (call.getEventType().compare("D") != 0 && callTakers_ == 0)
   {
      waitList_.push(call);
   }
   else
   {
      
   }
   return true;
}