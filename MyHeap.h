//MyHeap.h
//Catherine Tran ID: 2021829, 2/26/21
//This class is my own implementation of a heap. I referenced the textbook when creating this class.
//This is a min heap where the "root" is the smallest element, and every child is larger than the parent
//A user can add, remove, peek, check if the heap is empty, and out the contents of the heap to the console
#pragma once
#include <iostream>
#include <vector>
#include "Event.h"
using namespace std;

class MyHeap
{
public:
   //Constructor
   MyHeap();
   
   //This function adds the Event to the end of the vector. The Event trickles up 
   //vector by being compared to its parent ((positionOfEventInVector - 1)/2). 
   //If the Event is < the parent, then the 2 events switch. This continues until 
   //the event is greater than its parent
   //Precondition: None
   //Postcondition: An event is added to the vector and the vector grows in size. returns true
      bool add(const Event& newData);

   //This function removes the first element of the minheap by swapping the front and 
   //back of the vector, then removing the event at the back of the vector. Calls the 
   //heaprebuild function to move the event back to its correct position
   //Precondition: none
   //Postcondition: returns false if the heap is empty, true otherwise. The heap loses one element
   //Functions used: heapBuild() since the first element of the heap isn't the least event, 
   //the event needs to be trickled down until it is in the right position
   bool remove();

   //This function lets the user know if the heap is empty or not
   //precondition:none
   //postcondition: returns true if empty, false otherwise
   bool isEmpty() const;

   //This function returns the element at the beginning of the heap
   //precondition: none
   //postcondition: returns the event at the beginning of the heap
   Event peek() const;

   //This function prints out all the events in the heap. This was used for testing
   //precondition: none
   //postcondition: outputs the contents of the heap to the console
   bool Display() const;

private:
   //Holds the Event objects in the heap
   vector<Event> event_;

   //This function makes the heap a minheap again. It trickles down the 
   //first element of the heap since it was out of place and puts it in 
   //the correct position where the parent of the event is < it and the children are > it.
   //Precondition: none
   //Postcondition: The heap is fixed and is a minheap again
   void heapRebuild(int subTreeRootIndex); 

   //This function returns if the Event is a leaf or not
   //precondition: none
   //postcondition: returns true if leaf, false otherwise
   bool isLeaf(int nodeIndex) const;

   //This function returns the left child of the given index
   //precondition: none
   //postcondition: returns the position of the left child if it exists, -1 otherwise
   int getLeftChildIndex(const int nodeIndex)const;

   //This function returns the right child of the given index
   //precondition: none
   //postcondition: returns the position of the right child if it exists, -1 otherwise
   int getRightChildIndex(const int nodeIndex)const;

   //This function returns the parent of the given index
   //precondition: none
   //postcondition: returns the position of the parent if it exists, -1 otherwise
   int getParentIndex(const int nodeIndex)const;
  
   
};