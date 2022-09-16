#include "proj0.cpp"
// #include "LLQueue.hpp"
#include <unordered_map>
#include <string>
#include <iostream>
using namespace std;
// NOTE:  these are not intended as exhaustive tests.                                                                                                                                                                                                                                               
// This should get you started testing.                                                                                                                                                                                                                                                             
                                                                                                                                                                                                                                                                                


And some tests for the linked list based queue.                                                                                                                                                                                                                                                  
    VERY IMPORTANT:  if your LLQueue is not templated, or if                                                                                                                                                                                                                                     
         it is not linked-list based, your score for this project                                                                                                                                                                                                                                
         will be zero.  Be sure your LLQueue compiles and runs                                                                                                                                                                                                                                   
         with non-numeric data types.                                                                                                                                                                                                                                                            

TEST(QueueTest, QueueTest1)
{
    LLQueue<int> a;
    a.enqueue(5);
    EXPECT_TRUE( a.front() == 5 );
}

TEST(QueueTest, QueueTest2)
{
    LLQueue<int> a;
    a.enqueue(5);
    a.enqueue(3);
    EXPECT_TRUE( a.front() == 5 );
}


TEST(QueueTest, QueueTest3)
{
    LLQueue<int> a;
    a.enqueue(5);
    a.enqueue(3);
    a.dequeue();
    EXPECT_TRUE( a.front() == 3 );
}

