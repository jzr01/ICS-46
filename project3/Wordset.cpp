#include <iostream>
#include "Wordset.hpp"
#include <string>
using namespace std;


// returns s, as a number in the given base, mod the given modulus
unsigned polynomialHashFunction(const std::string & s, unsigned base, unsigned mod)
{
  unsigned sum = 0;
  for (int i = s.size() - 1; i >= 0; i--)
  {
    unsigned b = s[s.size() - i - 1] - 'a' + 1;

    for (int j = 0 ; j < i; j++)
    {
      b = b * base;
    }

    sum += b;
  }
  return sum % mod;
}



WordSet::WordSet(unsigned initialCapacity, unsigned evictionThreshold)
{
    base1 = new std::string[initialCapacity];
    base2 = new std::string[initialCapacity];
    for (int i = 0 ; i < initialCapacity; i++)
    {
      base1[i] = "";
      base2[i] = "";
    }
    count = 0;
    size = initialCapacity;
}

WordSet::~WordSet()
{
  delete[] base1;
  delete[] base2;
}

void WordSet::insert(const std::string & s)
{
  unsigned times = 0;
  
  std::string s1 = s;
  while (times <= WordSet::DEFAULT_EVICT_THRESHOLD)
  {
    if (contains(s1))
    {
      break;
    }

    unsigned index1 = polynomialHashFunction(s1,WordSet::BASE_H1,size);
    if (base1[index1] == "" )
    {
      base1[index1] = s1;
      count++;
      break;
    }
    else
    {
      std::string s2 = base1[index1];
      base1[index1] = s1;
      unsigned index2 = polynomialHashFunction(s2,WordSet::BASE_H2,size);
      
      if (base2[index2] == "")
      {
        base2[index2] = s2;
        count++;
        break;
      }
      
      else
      {
        s1 = base2[index2];
        base2[index2] = s2;
      }
    }
    times++;
  }

  if ( times > WordSet::DEFAULT_EVICT_THRESHOLD)
  {
    unsigned new_size = 2*size;
    while (!isPrime(new_size))
    {
      new_size++;
    }

    WordSet new_set = WordSet(new_size);
    new_set.insert(s1);
    for (int i = 0; i < size; i++)
    {
      if (base1[i] != "")
      {
        new_set.insert(base1[i]);
      }
    }
    
    for (int i = 0; i < size; i++)
    {
      if (base2[i] != "")
      {
        new_set.insert(base2[i]);
      }
    }
    
    *this = new_set;
  }

}




bool WordSet::isPrime(unsigned s)
{
    if (s <= 1)
        return false;
 
    for (int i = 2; i < s; i++)
        if (s % i == 0)
            return false;
 
    return true;
}

bool WordSet::contains(const std::string & s) const
{
  unsigned ind1 = polynomialHashFunction(s,WordSet::BASE_H1,size);
  unsigned ind2 = polynomialHashFunction(s,WordSet::BASE_H2,size);
  bool b1 = (base1[ind1] == s);
  bool b2 = (base2[ind2] == s); 
  return b1 || b2;
}

// return how many distinct strings are in the set
unsigned WordSet::getCount() const
{
  return count;
}

// return how large the underlying array is.
unsigned WordSet::getCapacity() const
{
	return this->size;
}