#include <iostream>
#include "Wordset.cpp"
#include "convert.cpp"
#include <string>
#include <fstream>

using namespace std;

// unsigned polynomialHashFunction(const std::string & s, unsigned base, unsigned mod)
// {
//   unsigned sum = 0;
//   for (int i = s.size() - 1; i >= 0; i--)
//   {
//     unsigned b = s[i] - 'a' + 1;

//     for (int j = 0 ; j < i; j++)
//     {
//       b = b * base;
//     }
//     sum += b;
//   }
//   return sum % mod;


int main()
{
  WordSet words(11);
	std::ifstream in("words.txt");
	loadWordsIntoTable(words, in);
  std::vector<std::string> a = convert("eat","sct",words);
  for (int i = 0; i < a.size(); i++)
  {
    cout << a[i] << endl;
  }
}