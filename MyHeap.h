#pragma once
#include <iostream>
#include <vector>
#include "Event.h"
using namespace std;

class MyHeap
{
public:
   MyHeap();
   
   bool add(const Event& newData);
   bool remove();
   Event peek() const;
   bool Display() const;

private:
   vector<Event> event_;
   int getLeftChildIndex(const int nodeIndex)const;
   int getRightChildIndex(const int nodeIndex)const;
   int getParentIndex(const int nodeIndex)const;
   bool isLeaf(int nodeIndex) const;
   void heapRebuild(int subTreeRootIndex);
};