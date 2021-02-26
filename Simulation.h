//Simulation.h
//Catherine Tran ID: 2021829, 2/26/21
//The purpose of this class is to simulate the E911 DDoS attack for 1hr. It uses a priority 
//queue to store the calls place and their end times. It also uses a queue as a waitlist. 
//The simulation first starts by accepting the given numbers from the command line, then 
//when runSimulation is called, calls are generated, the calls are processed, then the 
//average time a call lasted is printed to the console.
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
   //The constructor. Takes in the number of call takers, the number of avgcalls 
   //per hour, the average service rate, and the number of bot callers
   Simulation(int takers, double avgCalls, double avgService, int numBots);

   //This function runs the E911 DDoS Simulation. It first generates the real callers and bot callers, then processes each 
   //event(call) in the priority queue. Finally, it prints the average total service time a real call took during the simulation.
   //Precondition: None
   //Postcondition: outputs the average time for a legit call. Priority Queue is empty
   //Functions called: generateCallers(): This function generates the bot and real callers and adds them 
   //to the priority queue based on the time the calls start
   //processEvent(Event e): If the call/event passed in is an arrival time, create a depature time event then 
   //enqueue that to the pq. If its a departure time, calculate the service time for that caller/event
   bool runSimulation();

private:
   //Number of call takers available. Used to see if an arrival event can be processed
   int callTakers_;

   //Number of calls per second. Used to find the interval between each call during the simulation
   double avgCallsPerSec_;

   //How long a call lasts. Used to find the average service rate.
   double avgServiceRate_;

   //Number of bot callers
   int numBots_;

   //Number of legitmate callers created
   int items_;

   //The pervious call time. Used to calculate how long a call was in the waitlist
   double previousCallTime_ ;

   //Average total service time. Is outputted at the end of simulation which 
   //shows how long a legit call lasted when the simulation ran
   double averageTotalServiceTime_;

   //Priority Queue that holds the events/call. It holds arrival times and departure times
   PrioQueue events_;

   //Waitlist that holds calls when there are no calltakers available
   queue<Event> waitList_;

   //This function uses uniform distribution to create bot callers that get added to the pq,
   //exponential distribution to find how long a real call will take, and poisson/exponential 
   //distribution to create real callers and add them to the pq.
   //Precondition: User inputted calls per hour, average service rate, and number of bots
   //Postconiditon: The priority queue is filled with bot callers and real callers. Returns true
   bool generateCallers();

   //This function processes the event/call based on if the call is an arrival time/legit call, 
   //a bot caller, a bot departure time/service ended, or a legit call departure time/service ended.
   //Precondition: There are events/calls in the priority queue
   //Postcondition: The priority queue is empty and returns true
   //Functions used: Uses the arrivalTime(event, bool) to make a calltaker unavailable and create 
   //a service ended/departure time for the call
   //Uses the departTime(event) function to calculate how long a real call lasted
   bool processEvent(Event& call);

   //This function marks a calltaker as unavailable by substracting from the total number of calltakers, 
   //then it calculates how long a call was in the waitlist if the call was in a waitlist then it creates 
   //a departure event for the call
   //Precondition: There is an event in the priority queue or waitlist
   //Postcondition: Returns true and a departure event is created and added to the priority queue. callTakers_ - 1.
   bool arrivalTime(Event& call, bool wait);

   //This function Calculates how long a call took if it was a legit call
   //Precondition: There is a departure event/call in the priority queue
   //Postcondition: AverageTotalServiceTime_ is updated, callTakers_++, and returns true
   bool departTime(Event& call);
};