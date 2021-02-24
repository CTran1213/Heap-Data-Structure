#include "Simulation.h"

Simulation::Simulation(int takers, int avgCalls, int avgService, int numBots)
{
   callTakers_ = takers;
   avgCallsPerSec_ = avgCalls / 3600;
   avgServiceRate_ = 1/avgService;
   numBots_ = numBots;
}



bool Simulation::runSimulation()
{
   generateCallers();
   // Event a = Event("A", 1, 3,0);
   // Event b= Event("A", 2, 3,0);
   // Event c = Event("A", 3, 3,0);
   // events_.enqueue(a);
   // events_.enqueue(b);
   // events_.enqueue(c);
   // items_ = 3;
   // callTakers_ = 1;

   while (!events_.isEmpty())
   {
      Event e = events_.peek();
      processEvent(e);
      events_.dequeue();
   }

   averageTotalServiceTime_ /= items_;
   cout << "Average Time for a legit call: " << averageTotalServiceTime_ << endl;
   return true;
}

bool Simulation::generateCallers()
{
   //Uniform Distribution to create bot callers
   int number;
   default_random_engine generator;
   uniform_int_distribution<int> uniform(1, 3600);

   for (int i = 0; i < numBots_; i++)
   {
      number = uniform(generator);
      Event e = Event("B", number, 6, 0);
      events_.enqueue(e);
   }

   //Exponential Distribution to find the average time a real call takes
   default_random_engine gen2;                    
   exponential_distribution<double> expDist1(avgServiceRate_);

   int avgTime = int(ceil(expDist1(gen2)));
   cout << avgTime << endl;
   // //Exponential Distribution to create real callers
   // int theInterval;
   // int nextCallTime = 0;
   // default_random_engine gen;
   // exponential_distribution<double> expDist2(avgCallsPerSec_);

   // Event first = Event("A", 0, avgTime, 0);
   // events_.enqueue(first);
   // items_++;
   // theInterval = int(ceil(expDist2(gen)));
   // while (nextCallTime <= 3600)
   // {
   //    nextCallTime = nextCallTime + theInterval;
   //    Event e = Event("A", nextCallTime, avgTime, 0);
   //    items_++;
   //    events_.enqueue(e);
   // }
   return true;
}

bool Simulation::processEvent(Event& call)
{
   if ((call.getEventType().compare("A") == 0 || call.getEventType().compare("B") == 0) && callTakers_ != 0)
   {
      arrivalTime(call, false);
   }
   else if ((call.getEventType().compare("A") == 0 || call.getEventType().compare("B") == 0) && callTakers_ == 0)
   {
      waitList_.push(call);
   }
   else if (call.getEventType().compare("DB") == 0 || call.getEventType().compare("D") == 0)
   {
      departTime(call);
      previousCallTime_ = call.getTime();
      if (!waitList_.empty())
      {
         Event temp = waitList_.front();
         arrivalTime(temp, true);
         waitList_.pop();
      }
   }
   return true;
}

bool Simulation::arrivalTime(Event& call, bool wait)
{
   int departTime;
   int extraTime;
   callTakers_--;

   if (wait)
   {
      extraTime = previousCallTime_ - call.getTime();
   }
   else
   {
      extraTime = 0;
   }

   departTime = call.getTime() + call.getServiceLength() + extraTime;

   if (call.getEventType().compare("A") == 0)
   {
      Event e = Event("D", departTime, call.getServiceLength(), extraTime);
      events_.enqueue(e);
   }
   else
   {
      Event e = Event("DB", departTime, call.getServiceLength(), extraTime);
      events_.enqueue(e);
   }
   return true;
}

bool Simulation::departTime(Event& call)
{
   callTakers_++;
   if (call.getEventType().compare("D") == 0)
   {
      averageTotalServiceTime_ += call.getTotalServiceTime();
   }
   return true;
}