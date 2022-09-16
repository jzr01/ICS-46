
#ifndef ___SKIP_LIST_HPP
#define ___SKIP_LIST_HPP

#include <cmath> // for log2
#include <string>
#include <vector>
#include "runtimeexcept.hpp"

template<typename T1, typename T2>
class Node {
    public:
        T1 key;
        T2 data;
        Node* right;
        Node* up;

        Node(T1 key1, T2 info, Node * right1, Node* up1)
        {
            key = key1;
            data = info;
            right = right1;
            up = up1;
        }
};

// if we are inserting unsigned integer x into a skip list,
// and have made i previous coin flips on this particular insertion
// this will return the result of a coin flip.
// A return of true indiates heads and false means tails.
bool flipCoin(unsigned x, unsigned i)
{
	char c;
	unsigned first8Bits = (x & 0xFF000000) / 0x01000000 ; 
	unsigned next8Bits =  (x & 0x00FF0000) / 0x00010000;
	unsigned andThen =	 (x & 0x0000FF00) / 0x00000100;
	unsigned lastBits =   (x & 0x000000FF);
	c = first8Bits ^ next8Bits ^ andThen ^ lastBits;
	i = i % 8;
	return ( c & (1 << i) ) != 0;
}

// if we are inserting a std::string into the skip list, we use this instead.
bool flipCoin(std::string s, unsigned i)
{
	char c = s[0];
	for(unsigned j = 1; j < s.length(); j++)
	{
		c = c ^ s[j];
	}
	return ( c & (1 << i) ) != 0;	
}



template<typename Key, typename Value>
class SkipList
{

private:
	Node<Key, Value>* head;
    Node<Key, Value>* tail;

public:


	SkipList()
    {
        head = nullptr;
        tail = nullptr;
    }

	// You DO NOT need to implement a copy constructor or an assignment operator.

	~SkipList()
    {
        Node<Key, Value>* temp = head;
        while (temp != nullptr)
        {
            Node<Key,Value>* next = temp->right;
            delete temp;
            temp = next;
        }
    }

	// how many distinct keys are in the skip list?
	size_t size() const noexcept
    {
        unsigned i = 0;
        Node<Key, Value>* temp = head;
        while (temp != nullptr)
        {
            i++;
            temp = temp->right;
        }
        return i;
    }

	bool isEmpty() const noexcept
    {
        return (head == nullptr);
    }

	// how many layers are in the skip list?
	unsigned numLayers() const noexcept
    {
        unsigned i = 2;
        Node<Key, Value>* temp = head;
        while (temp != nullptr)
        {
            unsigned n;
            Node<Value, Value>* temp1 = temp->up;
            while(temp1 != nullptr)
            {
                n = height(temp->data) + 1;
            }
            if (n > i)
            {
                i = n;
            }
            temp = temp -> right;
        }
        return i;
    }

	// what is the height of this key?  Throw an exception if this key is not in the Skip List. 
	unsigned height(const Key & k) const
    {
        Node<Key, Value>* temp = head;
        while (temp != nullptr) 
        {
            if (temp->key == k)
            {
                unsigned i = 1;
                Node<Value, Value>* temp1 = temp->up;
                while (temp1 != nullptr)
                {
                    i++;
                    temp1 = temp1 -> up;
                }
                return i;
            }
            temp = temp -> right;
        } 
        throw RuntimeException("Key not found");
    }


	// if this key is in the SkipList, nextKey and previousKey return the
	// immediate successor / predecessor key.
	// If k is not in the list, these throw an exception.
	// nextKey also throws if k is the largest and previousKey throws if it is the smallest.
	Key nextKey(const Key & k) const
    {
        if (isLargestKey(k))
        {
            throw RuntimeException("No next key");
        }
        Node<Key, Value>* temp = head;
        while (temp != nullptr) 
        {
            if (temp->data == k)
            {
                return temp->right->data;
            }
            temp = temp -> right;
        }
        throw RuntimeException("No next key");
    }

	Key previousKey(const Key & k) const
    {
        if (isSmallestKey(k))
        {
            throw RuntimeException("No previous key");
        }
        Node<Key, Value>* temp = head;
        while (temp != nullptr && temp->right != nullptr)
        {
            if (temp->right->data == k)
            {
                return temp->data;
            }
            temp = temp -> right;
        }
        throw RuntimeException("No previous key");
    }


	// These return the value associated with the given key.
	Value & find(const Key & k)
    {
         Node<Key, Value>* temp = head;
         while (temp != nullptr)
         {
             if (temp->key == k)
             {
                 return temp->data;
             }
             temp = temp -> right;
         }
         throw RuntimeException("Key not found");
    }

	const Value & find(Key k) const
    {
         Node<Key, Value>* temp = head;
         while (temp != nullptr)
         {
             if (temp->data == k)
             {
                 return temp->up->data;
             }
             temp = temp -> right;
         }
         throw RuntimeException("Key not found");
    }

	// return true if this key/value pair is successfully inserted, false otherwise.
	// If the key already exists, do not insert one -- return false.
	bool insert(const Key & k, const Value & v)
    {
        bool not_in = true;
        Node<Key, Value>* temp = head;
        while (temp != nullptr)
        {
            if (temp->key == k)
            {
                not_in = false;
            }
            temp = temp -> right;
        } 
        if (not_in)
        {
            
            Node<Key, Value>* temp = head;
            Node<Key, Value>* temp_v = new Node<Key,Value>(k,v,nullptr,nullptr);
            Node<Key, Value>* node2 = temp_v;
            unsigned i = 0;
            unsigned height;
            if (size() <= 16)
            {
                height = 12;
            }else
            {
                height = 3*ceil(log2(size()+1));
            }
            while (flipCoin(k,i) && i <= height)
            {
                node2->up = new Node<Key, Value>(k,v,nullptr,nullptr);
                i++;
                node2 = node2->up;
            }
            if (temp == nullptr)
            {
                head = temp_v;
            }
            else
            {
                while(temp->right != nullptr)
                {

                    temp = temp -> right;
                }
                temp->right = temp_v;
            }
            return true;
        }
        return false;
    }


	std::vector<Key> allKeysInOrder() const
	{
		// you are allowed to use a std::vector in this function.
		std::vector<Key> r;
        Node<Key, Value>* temp = head;
        while (temp != nullptr)
        {
            if (r.size() == 0)
            {    
                r.push_back(temp->key);
            }else if (r.size() == 1)
            {
                if (temp->data >= r[0])
                {
                    r.push_back(temp->key);
                }else
                {
                    r.insert(r.begin(),temp->key);
                }
            }else
            {
                if (temp->data <= r[0])
                {
                    r.insert(r.begin(),temp->key);
                }
                else if (temp->key >= r[r.size()-1])
                {
                    r.push_back(temp->key);
                }
                else
                {
                    for (int i = 0; i < r.size()-1;i++)
                    {
                        if (temp->key >= r[i] && temp->key <= r[i+1])
                        {
                            r.insert(r.begin()+i,temp->key);
                        
                        }
                    }
                }
            }
            temp = temp -> right;
        }
        
		return r;
	}


	// True or false:  is this the smallest key in the SkipList?
	bool isSmallestKey(const Key & k) const
    {

        return (allKeysInOrder()[0] == k);
    }

	bool isLargestKey(const Key & k) const
	{
        return (allKeysInOrder()[size()-1] == k);
    }

	
};

#endif

