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

    private:
    string eventType_;
    int time_;
    int serviceLength_;
    int totalServiceTime_;

};