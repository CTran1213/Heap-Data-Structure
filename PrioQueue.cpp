//PrioQueue.cpp
//Catherine Tran ID: 2021829, 2/26/21
//Implementation of PrioQueue.h
//This class uses the heap class. This priority queue is implemented as a heap. 
//The pq can enqueue, deqeuue, peek, check if its empty, and display its contents.
#include "PrioQueue.h"

//Constructor
PrioQueue::PrioQueue()
{

}

//Checks to see if the priority queue is empty
//Precondition: none
//Postcondition: returns true if empty, false otherwise
bool PrioQueue::isEmpty() const
{
    if (storage.isEmpty()){
        return true;
    }
    else{
        return false;
    }
}

//Adds an event to the priority queue
//Precondition: none
//Postcondition: priorityqueue gains an element. returns true
bool PrioQueue::enqueue(const Event &newEntry)
{
    storage.add(newEntry);
    return true;
}

//Removes an event from the priority queue
//Preconditon: none
//Postcondition: an element is removed from the pq and returns true
bool PrioQueue::dequeue()
{
    storage.remove();
    return true;
}

//Lets the user see whats at the beginning of the priority queue
//Precondition: None
//PostCondition: returns the element at the beginning of the prioqueue
Event PrioQueue::peek() const
{
    return storage.peek();
}

//Print the elements in the priority queue. This was used during testing
//Precondition: none
//postcondition: prints the events in the priority queue to the console. returns true
bool PrioQueue::Display() const
{
    storage.Display();
    return true;
}