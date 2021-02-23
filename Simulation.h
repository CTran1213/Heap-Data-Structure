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
   Simulation(int takers, int avgCalls, int avgService, int numBots);

   
   bool runSimulation();

private:
   int callTakers_;
   int avgCallsPerSec_;
   int avgServiceTime_;
   int numBots_;
   int currentTime_;
   PrioQueue events_;
   queue<Event> waitList_;
   bool generateCallers();
   bool processEvent(Event call);
};