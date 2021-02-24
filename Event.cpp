#include "Event.h"

Event::Event(string eventType, int time, int serviceTime, int extraTime)
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

int Event::getTime() const
{
   return time_;
}

int Event::getServiceLength() const
{
   return serviceLength_;
}

int Event::getExtraTime() const
{
   return extraTime_;
}

int Event::getTotalServiceTime() const
{
   int arrival = time_ - serviceLength_ - extraTime_;
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