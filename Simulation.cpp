//Simulation.cpp
//Catherine Tran ID: 2021829, 2/26/21
//Implemention of simulation.h
//The purpose of this class is to simulate the E911 DDoS attack for 1hr. It uses a priority 
//queue to store the calls place and their end times. It also uses a queue as a waitlist. 
//The simulation first starts by accepting the given numbers from the command line, then 
//when runSimulation is called, calls are generated, the calls are processed, then the 
//average time a call lasted is printed to the console.
#include "Simulation.h"

//The constructor. Takes in the number of call takers, the number of avgcalls 
//per hour, the average service rate, and the number of bot callers
Simulation::Simulation(int takers, double avgCalls, double avgService, int numBots)
{
   callTakers_ = takers;
   avgCallsPerSec_ = avgCalls / 3600.0;
   avgServiceRate_ = 1/avgService;
   numBots_ = numBots;
   averageTotalServiceTime_ = 0;
   items_ = 0;
   previousCallTime_ = 0;
}

//This function runs the E911 DDoS Simulation. It first generates the real callers and bot callers, then processes each 
//event(call) in the priority queue. Finally, it prints the average total service time a real call took during the simulation.
//Precondition: None
//Postcondition: outputs the average time for a legit call. Priority Queue is empty
//Functions called: generateCallers(): This function generates the bot and real callers and adds them 
//to the priority queue based on the time the calls start
//processEvent(Event e): If the call/event passed in is an arrival time, create a depature time event then 
//enqueue that to the pq. If its a departure time, calculate the service time for that caller/event
bool Simulation::runSimulation()
{
   //Generates callers and adds them to the priority queue
   generateCallers();

   while (!events_.isEmpty()){
      //Invariant: There are still events/calls left in the pq
      Event e = events_.peek();
      processEvent(e);
      events_.dequeue();
   }

   //Now that the simulation is "over", the average total service time for a legit call is calculated
   averageTotalServiceTime_ /= items_;
   cout << "Average Time for a legit call: " << averageTotalServiceTime_ << endl;
   return true;
}

//This function uses uniform distribution to create bot callers that get added to the pq,
//exponential distribution to find how long a real call will take, and poisson/exponential 
//distribution to create real callers and add them to the pq.
//Precondition: User inputted calls per hour, average service rate, and number of bots
//Postconiditon: The priority queue is filled with bot callers and real callers. Returns true
bool Simulation::generateCallers()
{
   //BEGINNING OF VARIABLES

   //Variables used for Uniform Distribution to create bot callers
   int number; //The arrival time of a bot caller
   default_random_engine generator; //Generator
   uniform_int_distribution<int> uniform(1, 3600); //Distribution

   //Variables used for Exponential Distribution to find the average time a real call takes
   double avgTime; //Time a real call takes
   default_random_engine gen2; //generator                   
   exponential_distribution<double> expDist1(avgServiceRate_); //distribution
   
   //Variables used for Exponential Distribution to create real callers
   double theInterval; //Interval between real calls
   double nextCallTime = 0; //Time of the next call
   double previousCallTime = 0; //Time of a previous call
   default_random_engine gen; //generator
   exponential_distribution<double> expDist2(avgCallsPerSec_); //distribution

   //END OF VARIABLES

   //Uniform Distribution to create bot callers
   //Creates an event with the time found from the uniform distribution and 
   //uses the "B" keyword to signal this event is a bot caller. The bot calls last 
   //for 6 seconds and dont have extra time currently.
   for (int i = 0; i < numBots_; i++){
      //Invariant: There are more bot times that can be added to the pq
      number = uniform(generator); //Returns int in range [1,3600]
      Event e = Event("B", number, 6, 0);
      events_.enqueue(e);
   } 

   //Exponential Distribution to find the average time a real call takes
   avgTime = (ceil(expDist1(gen2)));

   //Since there isn't a max number for the avgTime, we need to make sure it doesnt go above 3600
   while (avgTime > 3600){
      avgTime = (ceil(expDist1(gen2)));
   }

   //First real caller being added to the pq. First call starts at time 0, uses the keyword 
   //"A" to signal that it is a normal caller, uses the time found from exponential 
   //distribution for the service length, and has no extra time.
   Event first = Event("A", 0, avgTime, 0);
   events_.enqueue(first);
   items_++;

   //Exponential Distribution to create real callers
   while (nextCallTime <= 3600){
      //Invariant: There are still calls that can be created and added to the pq that are < 3600
      theInterval = (ceil(expDist2(gen)));
      avgTime = (ceil(expDist1(gen2)));
      while (avgTime > 3600){
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

//This function processes the event/call based on if the call is an arrival time/legit call, 
//a bot caller, a bot departure time/service ended, or a legit call departure time/service ended.
//Precondition: There are events/calls in the priority queue
//Postcondition: The priority queue is empty and returns true
//Functions used: Uses the arrivalTime(event, bool) to make a calltaker unavailable and create 
//a service ended/departure time for the call
//Uses the departTime(event) function to calculate how long a real call lasted
bool Simulation::processEvent(Event& call)
{
   if ((call.getEventType().compare("A") == 0 || call.getEventType().compare("B") == 0) && callTakers_ != 0){ //call taker available and caller is real or a bot
      arrivalTime(call, false);
   }
   else if ((call.getEventType().compare("A") == 0 || call.getEventType().compare("B") == 0) && callTakers_ == 0){ //call taker is not available and caller is real or a bot
      waitList_.push(call);
   }
   else if (call.getEventType().compare("DB") == 0 || call.getEventType().compare("D") == 0) //service ended event/departure event
   {
      departTime(call);

      //The time the last call ended. This number is used to calculate how long a call/event was in the waitlist
      previousCallTime_ = call.getTime();

      //Since a call taker is now available, the next call/event in the waitlist 
      //is dealt with if there is a call in the waitlist
      if (!waitList_.empty()){
         Event temp = waitList_.front();
         arrivalTime(temp, true);
         waitList_.pop();
      }
   }
   return true;
}

//This function marks a calltaker as unavailable by substracting from the total number of calltakers, 
//then it calculates how long a call was in the waitlist if the call was in a waitlist then it creates 
//a departure event for the call
//Precondition: There is an event in the priority queue or waitlist
//Postcondition: Returns true and a departure event is created and added to the priority queue. callTakers_ - 1.
bool Simulation::arrivalTime(Event& call, bool wait)
{
   //BEGINNING OF VARIABLES

   //The time an event/call ends
   double departTime;

   //How long an event/call was in the waitlist
   double extraTime;

   //END OF VARIABLES

   callTakers_--;

   //Extra time is added if a caller was in the wait list
   if (wait){
      extraTime = previousCallTime_ - call.getTime();
   }
   else{
      extraTime = 0;
   }

   //The time the call is going to end
   departTime = call.getTime() + call.getServiceLength() + extraTime;

   if (call.getEventType().compare("A") == 0){ //departure time/service ended event for a legit caller
   Event e = Event("D", departTime, call.getServiceLength(), extraTime);
      events_.enqueue(e);
   }
   else{  //departure time/service ended event for a bot caller
      Event e = Event("DB", departTime, call.getServiceLength(), extraTime);
      events_.enqueue(e);
   }
   return true;
}

//This function Calculates how long a call took if it was a legit call
//Precondition: There is a departure event/call in the priority queue
//Postcondition: AverageTotalServiceTime_ is updated, callTakers_++, and returns true
bool Simulation::departTime(Event& call)
{
   callTakers_++;

   //Only adds the service time if the event was a legit call, not a bot call
   if (call.getEventType().compare("D") == 0){
      averageTotalServiceTime_ += call.getTotalServiceTime();
   }
   return true;
}