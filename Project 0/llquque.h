#include <iostream>
using namespace std;
#ifndef __ICS46_LL_QUEUE_HPP
#define __ICS46_LL_QUEUE_HPP
#include "runtime_exception.hpp"


class QueueEmptyException : public RuntimeException
{
public:
        QueueEmptyException(const std::string & err) : RuntimeException(err) {}
};

template<typename T>
struct ListNode
    {
      T info;
      ListNode * next;
      ListNode(T newInfo)
      : info( newInfo ), next( nullptr )
      {
      }
    };


template<typename Object>
class LLQueue
{
private:
        ListNode<Object>* head;
        ListNode<Object>* rear;                                                                                                                                                                                                                                                       

public:
        LLQueue();

        // Note:  copy constructors are required.                                                                                                                                                                                                                                                   
        // Be sure to do a "deep copy" -- if I                                                                                                                                                                                                                                                      
        // make a copy and modify one, it should not affect the other.                                                                                                                                                                                                                              
        LLQueue(const LLQueue & st);
        LLQueue & operator=(const LLQueue & st);
        ~LLQueue()
        {
          delete head;
          delete rear;                                                                                                                                                                                                                                       
        }

        size_t size() const noexcept;
        bool isEmpty() const noexcept;

        // We have two front() for the same reason the Stack in lecture week 2 had two top() functions.                                                                                                                                                                                             
        // If you do not know why there are two, your FIRST step needs to be to review your notes from that lecture.                                                                                                                                                                                

        Object & front();
        const Object & front() const;

        void enqueue(const Object & elem);
                                                                                                                                                                                                                                                     
        void dequeue();
};

template<typename Object>
LLQueue<Object>::LLQueue()
{
  head = rear = nullptr;
}                                                                                                                                                                                                                           

template<typename Object>
LLQueue<Object>::LLQueue(const LLQueue & st)
{
  head = st.head;
  rear = st.rear;
}

template<typename Object>
LLQueue<Object> & LLQueue<Object>::operator=(const LLQueue & st)
{
  head = st.head;
  rear = st.rear;
  return *this;
}

template<typename Object>
size_t LLQueue<Object>::size() const noexcept
{
  size_t i = 0;
  ListNode<Object> * temp = head;
  while (temp != nullptr)
  {
    i++;
    temp = temp -> next;
  }
  return i;
}

template<typename Object>
bool LLQueue<Object>::isEmpty() const noexcept
{
  return (head == nullptr);
}                                                                                                                                                                              

template<typename Object>
Object & LLQueue<Object>::front()
{
  if (head != nullptr)
  {
    return head->info;
  }else
  {
    throw QueueEmptyException("The queue is empty.");
  }
}

template<typename Object>
const Object & LLQueue<Object>::front() const
{
  if (head != nullptr)
  {
    return head->info;
  }else
  {
    throw QueueEmptyException("The queue is empty.");
  }
}

template<typename Object>
void LLQueue<Object>::enqueue(const Object & elem)
{
  ListNode<Object> * temp = new ListNode<Object>(elem);
  if (rear == nullptr & head == nullptr)
  {
    head = rear = temp;
  }
  else
  {
    rear->next = temp;
    rear = temp;
  }

}

template<typename Object>                                                                                                                                                                                                                                           
void LLQueue<Object>::dequeue()
{
  if (head == nullptr)
  {
      throw QueueEmptyException("The queue is empty.");
  }else
  {
  ListNode<Object>* temp = head;
  head = head->next;

  if (head == nullptr)
      rear = nullptr;

  delete (temp);
  }
}                                                                                                                                                                                     

#endif