//Event.cpp
//Catherine Tran ID: 2021829, 2/26/21
//Implementation of Event.h
//The purpose of the class is to create an Event object. The event object are 
//calls in the simulation. The object stores the event type 
//("A", "D", "B" or "DB"), the time of the event, how long the event lasted, and how long 
//the event was in the waitlist. Each data memeber in this class is accessible through 
//getters, but cannot be changed
#include "Event.h"

//Constructor. Sets the eventType, time of the event, service time 
//of the event, and how long the event was in the waitlist
Event::Event(string eventType, double time, double serviceTime, double extraTime)
{
   eventType_ = eventType;
   time_ = time;
   serviceLength_ = serviceTime;
   extraTime_ = extraTime;

}

//This function returns the type of event ("A", "D", "B" or "DB")
//Precondition: none
//Postcondition: Returns the event type
string Event::getEventType() const
{
   return eventType_;
}

//This function returns the time of the event
//Preconiditon: none
//Postcondition: returns the time
double Event::getTime() const
{
   return time_;
}

//This function returns how long the call is supposed to last
//Precondition: none
//postcondition: returns the service length
double Event::getServiceLength() const
{
   return serviceLength_;
}

//This function returns how long the call was in the waitlist
//Precondition: none
//postcondition: returns the extra time
double Event::getExtraTime() const
{
   return extraTime_;
}

//This function returns the overall total service time of the event/call
//Precondition: none
//Postcondition: returns the total service time
double Event::getTotalServiceTime() const
{
   //Time of arrival
   double arrival = time_ - serviceLength_ - extraTime_;
   return (time_ - arrival);
}

//This function compares an event based on the time it occurs
//Precondition: none
//Postcondition: returns true this time is less than the time passed in, false if greater then
bool Event::operator<(const Event &e1) const
{
   if (time_ < e1.getTime()){
      return true;
   }
   else{
      return false;
   }
}

//This function compares an event based on the time it occurs
//Precondition: none
//Postcondition: returns true this time is greater than the time passed in, false if less then
bool Event::operator>(const Event &e1) const
{
   if (time_ > e1.getTime()){
      return true;
   }
   else{
      return false;
   }
}

//This function outputs to the console the time of the event. 
//This was used during testing, and can be used in the future if I want to improve the program in any way.
//Precondition: none
//Postcondition: outputs the time of the event
ostream& operator<<(ostream &outStream, const Event &e)
{
   outStream << e.getTime();
   return outStream;
}