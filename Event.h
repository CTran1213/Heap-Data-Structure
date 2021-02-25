#pragma once
#include <iostream>
using namespace std;

class Event
{
   friend ostream& operator<<(ostream &outStream, const Event &e);

public:
   Event(string eventType, double time, double serviceTime, double extraTime);
   string getEventType() const;
   double getTime() const;
   double getServiceLength() const;
   double getExtraTime() const;
   double getTotalServiceTime() const;
   bool operator<(const Event &e1) const;
   bool operator>(const Event &e1) const;

private:
   string eventType_;
   double time_;
   double serviceLength_;
   double extraTime_;
   double totalServiceTime_;
};