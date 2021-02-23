#pragma once
#include <iostream>
#include "Event.h"
#include <vector>
#include "MyHeap.h"
using namespace std;

class PrioQueue
{
public:
   PrioQueue();
   bool isEmpty();
   bool enqueue(const Event& newEntry);
   bool dequeue();
   Event peek() const;
   bool Display() const;

private:
   MyHeap storage;
};