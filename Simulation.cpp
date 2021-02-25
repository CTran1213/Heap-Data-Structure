#include "Simulation.h"

Simulation::Simulation(int takers, double avgCalls, double avgService, int numBots)
{
   callTakers_ = takers;
   avgCallsPerSec_ = avgCalls / 3600.0;
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
   cout << "test1" << endl;
   for (int i = 0; i < numBots_; i++)
   {
      number = uniform(generator);
      Event e = Event("B", number, 6, 0);
      events_.enqueue(e);
   }
   
   //Exponential Distribution to find the average time a real call takes
   double avgTime;
   default_random_engine gen2;                    
   exponential_distribution<double> expDist1(avgServiceRate_);

   avgTime = (ceil(expDist1(gen2)));
   while (avgTime > 3600)
   {
      avgTime = (ceil(expDist1(gen2)));
   }
   
   //Exponential Distribution to create real callers
   double theInterval;
   double nextCallTime = 0;
   double previousCallTime = 0;
   default_random_engine gen;
   exponential_distribution<double> expDist2(avgCallsPerSec_);

   Event first = Event("A", 0, avgTime, 0);
   events_.enqueue(first);
   items_++;
   
   while (nextCallTime <= 3600)
   {
      theInterval = (ceil(expDist2(gen)));
      avgTime = (ceil(expDist1(gen2)));
      while (avgTime > 3600)
      {
         avgTime = (ceil(expDist1(gen2)));
      }
      nextCallTime = previousCallTime + theInterval;
      previousCallTime = nextCallTime;
      Event e = Event("A", nextCallTime, avgTime, 0);
      items_++;
      events_.enqueue(e);
   }

   return true;
}

bool Simulation::processEvent(Event& call)
{
   if ((call.getEventType().compare("A") == 0 || call.getEventType().compare("B") == 0) && callTakers_ != 0) //call taker available and caller is real or a bot
   {
      arrivalTime(call, false);
   }
   else if ((call.getEventType().compare("A") == 0 || call.getEventType().compare("B") == 0) && callTakers_ == 0) //call taker is not available and caller is real or a bot
   {
      waitList_.push(call);
   }
   else if (call.getEventType().compare("DB") == 0 || call.getEventType().compare("D") == 0) //service ended event/ departure event
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
   double departTime;
   double extraTime;
   callTakers_--;

   //Extra time is added if a caller was in the wait list
   if (wait)
   {
      extraTime = previousCallTime_ - call.getTime();
   }
   else
   {
      extraTime = 0;
   }

   departTime = call.getTime() + call.getServiceLength() + extraTime;

   if (call.getEventType().compare("A") == 0) //departure time/service ended event for a legit caller
   {
      Event e = Event("D", departTime, call.getServiceLength(), extraTime);
      events_.enqueue(e);
   }
   else  //departure time/service ended event for a bot caller
   {
      Event e = Event("DB", departTime, call.getServiceLength(), extraTime);
      events_.enqueue(e);
   }
   return true;
}

//Calculates how long a call took if it was a legit call
bool Simulation::departTime(Event& call)
{
   callTakers_++;
   if (call.getEventType().compare("D") == 0)
   {
      averageTotalServiceTime_ += call.getTotalServiceTime();
   }
   return true;
}