//PrioQueue.h
//Catherine Tran ID: 2021829, 2/26/21
//This class uses the heap class. This priority queue is implemented as a heap. 
//The pq can enqueue, deqeuue, peek, check if its empty, and display its contents.
#pragma once
#include <iostream>
#include "Event.h"
#include <vector>
#include "MyHeap.h"
using namespace std;

class PrioQueue
{
public:
   //Constructor
   PrioQueue();

   //Checks to see if the priority queue is empty
   //Precondition: none
   //Postcondition: returns true if empty, false otherwise
   bool isEmpty() const;

   //Adds an event to the priority queue
   //Precondition: none
   //Postcondition: priorityqueue gains an element. returns true
   bool enqueue(const Event& newEntry);

   //Removes an event from the priority queue
   //Preconditon: none
   //Postcondition: an element is removed from the pq and returns true
   bool dequeue();

   //Lets the user see whats at the beginning of the priority queue
   //Precondition: None
   //PostCondition: returns the element at the beginning of the prioqueue
   Event peek() const;

   //Print the elements in the priority queue. This was used during testing
   //Precondition: none
   //postcondition: prints the events in the priority queue to the console. returns true
   bool Display() const;

private:
   //This is the heap. It stores the events in the priority queue. 
   //Most of the methods in the priority queue use the heap methods to manipulate the data member
   MyHeap storage;
};