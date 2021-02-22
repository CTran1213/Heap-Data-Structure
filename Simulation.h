#pragma once
#include <iostream>
#include <random>
#include <vector>
#include <cmath>
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
   vector<int> bots_;
};