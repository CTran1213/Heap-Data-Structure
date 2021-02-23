#include "PrioQueue.h"

PrioQueue::PrioQueue()
{

}

bool PrioQueue::isEmpty()
{
    return true;
}

bool PrioQueue::enqueue(const Event &newEntry)
{
    storage.add(newEntry);
    return true;
}

bool PrioQueue::dequeue()
{
    storage.remove();
    return true;
}

Event PrioQueue::peek() const
{
    return storage.peek();
}

bool PrioQueue::Display() const
{
    storage.Display();
    return true;
}