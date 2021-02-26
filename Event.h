//Event.h
//Catherine Tran ID: 2021829, 2/26/21
//The purpose of the class is to create an Event object. The event object are 
//calls in the simulation. The object stores the event type 
//("A", "D", "B" or "DB"), the time of the event, how long the event lasted, and how long 
//the event was in the waitlist. Each data memeber in this class is accessible through 
//getters, but cannot be changed
#pragma once
#include <iostream>
using namespace std;

class Event
{
   //This function outputs to the console the time of the event. 
   //This was used during testing, and can be used in the future if I want to improve the program in any way.
   //Precondition: none
   //Postcondition: outputs the time of the event
   friend ostream& operator<<(ostream &outStream, const Event &e);

public:
   //Constructor. Sets the eventType, time of the event, service time 
   //of the event, and how long the event was in the waitlist
   Event(string eventType, double time, double serviceTime, double extraTime);

   //This function returns the type of event ("A", "D", "B" or "DB")
   //Precondition: none
   //Postcondition: Returns the event type
   string getEventType() const;

   //This function returns the time of the event
   //Preconiditon: none
   //Postcondition: returns the time
   double getTime() const;

   //This function returns how long the call is supposed to last
   //Precondition: none
   //postcondition: returns the service length
   double getServiceLength() const;

   //This function returns how long the call was in the waitlist
   //Precondition: none
   //postcondition: returns the extra time
   double getExtraTime() const;

   //This function returns the overall total service time of the event/call
   //Precondition: none
   //Postcondition: returns the total service time
   double getTotalServiceTime() const;

   //This function compares an event based on the time it occurs
   //Precondition: none
   //Postcondition: returns true this time is less than the time passed in, false if greater then
   bool operator<(const Event &e1) const;

   //This function compares an event based on the time it occurs
   //Precondition: none
   //Postcondition: returns true this time is greater than the time passed in, false if less then
   bool operator>(const Event &e1) const;

private:
   //Type of event: ("A", "D", "B" or "DB")
   string eventType_;

   //The time the event occured
   double time_;

   //How long the event/call is supposed to last
   double serviceLength_;

   //How long the event/call was in the waitlist
   double extraTime_;

   //How long the call actually lasted (includes extra time)
   double totalServiceTime_;
};