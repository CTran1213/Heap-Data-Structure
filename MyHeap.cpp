#include "MyHeap.h"

MyHeap::MyHeap()
{

}

bool MyHeap::add(const Event& newData)
{
   int newDataIndex;
   bool inPlace;
   int parentIndex;

   event_.push_back(newData);

   newDataIndex = event_.size() - 1;
   inPlace = false;
   while ((newDataIndex >= 0) and !inPlace)
   {
      parentIndex = (newDataIndex - 1)/2;
      if (event_[newDataIndex] > event_[parentIndex])
      {
         inPlace = true;
      }
      else
      {
         Event temp = event_[parentIndex];
         event_[parentIndex] = event_[newDataIndex];
         event_[newDataIndex] = temp;
         newDataIndex = parentIndex;
      }
   }
   return true;
}

bool MyHeap::remove()
{
   event_[0] = event_[event_.size() - 1];
   event_.pop_back();
   heapRebuild(0);
   return true;
}

Event MyHeap::peek() const
{
   return event_[0];
}

bool MyHeap::isLeaf(int nodeIndex) const
{
   if (getLeftChildIndex(nodeIndex) == -1 && getRightChildIndex(nodeIndex) == -1)
   {
      return true;
   }
   else
   {
      return false;
   }
}

void MyHeap::heapRebuild(int subTreeRootIndex)
{
   int leftChildIndex;
   int rightChildIndex;
   if (!(isLeaf(subTreeRootIndex)))
   {
      leftChildIndex = 2* subTreeRootIndex + 1;
      if (getRightChildIndex(subTreeRootIndex) != -1)
      {
         rightChildIndex = leftChildIndex + 1;
         if (event_[rightChildIndex] < event_[leftChildIndex])
         {
            leftChildIndex = rightChildIndex;
         }
      }

      if (event_[subTreeRootIndex] > event_[leftChildIndex])
      {
         Event temp = event_[subTreeRootIndex];
         event_[subTreeRootIndex] = event_[leftChildIndex];
         event_[leftChildIndex] = temp;
         heapRebuild(leftChildIndex);
      }
   }
}

int MyHeap::getLeftChildIndex(const int nodeIndex)const
{
   if ((2*nodeIndex + 1) < event_.size())
   {
      return -1;
   }
   else
   {
      return 2*nodeIndex + 1;
   }
}

int MyHeap::getRightChildIndex(const int nodeIndex)const
{
   if ((2*nodeIndex + 2) < event_.size())
   {
      return -1;
   }
   else
   {
      return 2*nodeIndex + 2;
   }
}

int MyHeap::getParentIndex(const int nodeIndex)const
{
   if ((nodeIndex - 1)/2 > -1)
   {
      return -1;
   }
   else
   {
      return (nodeIndex - 1)/2;
   }
}