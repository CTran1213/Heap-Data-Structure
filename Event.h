#pragma once
#include <iostream>
using namespace std;

class Event
{
public:
   Event(string eventType, int time, int serviceTime, int extraTime);
   string getEventType() const;
   int getTime() const;
   int getServiceLength() const;
   int getTotalServiceTime() const;
   bool operator<(const Event &e1) const;
   bool operator>(const Event &e1) const;

private:
   string eventType_;
   int time_;
   int serviceLength_;
   int extraTime_;
   int totalServiceTime_;
};