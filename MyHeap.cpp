//MyHeap.cpp
//Catherine Tran ID: 2021829, 2/26/21
//Implementation of MyHeap.h
//This class is my own implementation of a heap. I referenced the textbook when creating this class.
//This is a min heap where the "root" is the smallest element, and every child is larger than the parent
//A user can add, remove, peek, check if the heap is empty, and out the contents of the heap to the console
#include "MyHeap.h"

//Constructor
MyHeap::MyHeap()
{

}

//This function adds the Event to the end of the vector. The Event trickles up 
//vector by being compared to its parent ((positionOfEventInVector - 1)/2). 
//If the Event is < the parent, then the 2 events switch. This continues until 
//the event is greater than its parent
//Precondition: None
//Postcondition: An event is added to the vector and the vector grows in size. returns true
bool MyHeap::add(const Event& newData)
{
   //BEGINNING OF VARIABLES

   int newDataIndex; //Index of the Event being added
   bool inPlace; //Boolean to see if the event is in the right position
   int parentIndex; //Index of the parent of the event added in

   //END OF VARIABLES

   //Adds event to the vector then finds the position of the event in the vector
   event_.push_back(newData);
   newDataIndex = event_.size() - 1;

   //Event is in the right position
   if (newDataIndex == 0){
      return true;
   }

   inPlace = false;
   //Trickles up the event to its right spot
   while ((newDataIndex > 0) && !inPlace){
      //Invariant: The event isnt in the right place. The heap is not a minheap
      parentIndex = (newDataIndex - 1)/2;
      if (event_[newDataIndex] > event_[parentIndex]){
         inPlace = true;
      }
      else{ //Swaps the parent and child when the child is < parent
         Event temp = event_[parentIndex];
         event_[parentIndex] = event_[newDataIndex];
         event_[newDataIndex] = temp;
         newDataIndex = parentIndex; 
      }
   }
   return true;
}

//This function removes the first element of the minheap by swapping the front and 
//back of the vector, then removing the event at the back of the vector. Calls the 
//heaprebuild function to move the event back to its correct position
//Precondition: none
//Postcondition: returns false if the heap is empty, true otherwise. The heap loses one element
//Functions used: heapBuild() since the first element of the heap isn't the least event, 
//the event needs to be trickled down until it is in the right position
bool MyHeap::remove()
{
   if (event_.empty()){
      return false;
   }

   //The last element of the heap is now the first element. 
   //This will be trickled down until it is in the right position
   //Last element is removed
   event_[0] = event_[event_.size() - 1];
   event_.pop_back();

   if (!event_.empty()){
      heapRebuild(0);
   }
   
   return true;
}

//This function lets the user know if the heap is empty or not
//precondition:none
//postcondition: returns true if empty, false otherwise
bool MyHeap::isEmpty() const
{
   if (event_.empty()){
      return true;
   }
   else{
      return false;
   }
}

//This function returns the element at the beginning of the heap
//precondition: none
//postcondition: returns the event at the beginning of the heap
Event MyHeap::peek() const
{
   if (event_.empty()){
      Event e = Event("", 0, 0, 0);
      return e;
   }
   else{
      return event_[0];
   }
}

//This function makes the heap a minheap again. It trickles down the 
//first element of the heap since it was out of place and puts it in 
//the correct position where the parent of the event is < it and the children are > it.
//Precondition: none
//Postcondition: The heap is fixed and is a minheap again
void MyHeap::heapRebuild(int subTreeRootIndex)
{
   int leftChildIndex; //index of the left child of the given index
   int rightChildIndex; //index of the right child of the given index
   if (!(isLeaf(subTreeRootIndex))) //when the given index isnt a leaf
   {
      leftChildIndex = 2* subTreeRootIndex + 1;

      //Swaps the right and left child if the right child is less than the left child.
      if (getRightChildIndex(subTreeRootIndex) != -1){
         rightChildIndex = leftChildIndex + 1;
         if (event_[rightChildIndex] < event_[leftChildIndex]){
            leftChildIndex = rightChildIndex;
         }
      }

      //When the given Event is greater than its child, that means this isnt a min heap. 
      //The 2 events are switched and heapRebuild is called again
      if (event_[subTreeRootIndex] > event_[leftChildIndex]){
         //Swaps the parent and left child. Event we're looking at is now the left child index
         Event temp = event_[subTreeRootIndex];
         event_[subTreeRootIndex] = event_[leftChildIndex];
         event_[leftChildIndex] = temp;
         heapRebuild(leftChildIndex);
      }
   }
}

//This function returns if the Event is a leaf or not
//precondition: none
//postcondition: returns true if leaf, false otherwise
bool MyHeap::isLeaf(int nodeIndex) const
{
   if (getLeftChildIndex(nodeIndex) == -1 && getRightChildIndex(nodeIndex) == -1){
      return true;
   }
   else{
      return false;
   }
}

//This function returns the left child of the given index
//precondition: none
//postcondition: returns the position of the left child if it exists, -1 otherwise
int MyHeap::getLeftChildIndex(const int nodeIndex)const
{
   if ((2*nodeIndex + 1) < event_.size()){
      return 2*nodeIndex + 1;
   }
   else{
      return -1;
   }
}

//This function returns the right child of the given index
//precondition: none
//postcondition: returns the position of the right child if it exists, -1 otherwise
int MyHeap::getRightChildIndex(const int nodeIndex)const
{
   if ((2*nodeIndex + 2) < event_.size()){
      return 2*nodeIndex + 2;
   }
   else{
      return -1;
   }
}

//This function returns the parent of the given index
//precondition: none
//postcondition: returns the position of the parent if it exists, -1 otherwise
int MyHeap::getParentIndex(const int nodeIndex)const
{
   if ((nodeIndex - 1)/2 > -1){
      return (nodeIndex - 1)/2;
   }
   else{
      return -1;
   }
}

//This function prints out all the events in the heap. This was used for testing
//precondition: none
//postcondition: outputs the contents of the heap to the console
bool MyHeap::Display() const
{
   for (int i = 0; i < event_.size(); i++){
      cout<< event_[i] << " " << endl;
   }
   return true;
}