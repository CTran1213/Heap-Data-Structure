#include "Event.h"

Event::Event(string eventType, double time, double serviceTime, double extraTime)
{
   eventType_ = eventType;
   time_ = time;
   serviceLength_ = serviceTime;
   extraTime_ = extraTime;

}

string Event::getEventType() const
{
   return eventType_;
}

double Event::getTime() const
{
   return time_;
}

double Event::getServiceLength() const
{
   return serviceLength_;
}

double Event::getExtraTime() const
{
   return extraTime_;
}

double Event::getTotalServiceTime() const
{
   double arrival = time_ - serviceLength_ - extraTime_;
   return (time_ - arrival);
}

bool Event::operator<(const Event &e1) const
{
   if (time_ < e1.getTime())
   {
      return true;
   }
   else
   {
      return false;
   }
}

bool Event::operator>(const Event &e1) const
{
   if (time_ > e1.getTime())
   {
      return true;
   }
   else
   {
      return false;
   }
}

ostream& operator<<(ostream &outStream, const Event &e)
{
   outStream << e.getTime();
   return outStream;
}