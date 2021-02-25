#pragma once
#include <iostream>
#include <random>
#include <vector>
#include <cmath>
#include "PrioQueue.h"
#include <queue>
using namespace std;

class Simulation
{
public:
   Simulation(int takers, double avgCalls, double avgService, int numBots);

   
   bool runSimulation();

private:
   int callTakers_;
   double avgCallsPerSec_;
   double avgServiceRate_;
   int numBots_;
   int items_;
   double previousCallTime_ ;
   double averageTotalServiceTime_;
   PrioQueue events_;
   queue<Event> waitList_;
   bool generateCallers();
   bool processEvent(Event& call);
   bool arrivalTime(Event& call, bool wait);
   bool departTime(Event& call);
};