#include "llquque.h"
#include <string>
#include <iostream>
using namespace std;

int main()
{
    LLQueue<int> a;
    try
    {
        a.front();
    }
    catch (QueueEmptyException)
    {
        cout << "empty" << endl;
    }
    a.enqueue(5);
    cout << a.front() << endl;
    a.enqueue(3);
    cout << a.front() << endl;
    a.dequeue();
    cout << a.front() << endl;
    cout << a.size() << endl;

    LLQueue<int> b(a);
    cout << b.front() << endl;

    LLQueue<string> c;
    try
    {
        c.dequeue();
    }
    catch (QueueEmptyException)
    {
        cout << "empty" << endl;
    }
    cout << c.isEmpty() << endl;
    c.enqueue("abc");
    c.enqueue("123");
    c.enqueue("edf");
    cout << c.front() << endl;

    LLQueue<string> d;
    d = c;
    cout << d.front() << endl;
};
