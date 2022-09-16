#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

struct data
{
	char c;
	int v;
};

bool used[10] = {false,false,false,false,false,false,false,false,false,false};

bool verifysolution(data* answer, int count, string s1,string s2, string s3)
{
	int num1 = 0;
  int num2 = 0;
  int num3 = 0;
  int co = 1;
  int i,j;

	for (i = s1.length()-1; i >= 0; i--)
	{
		for (j = 0; j < count; j++)
		{
			if (answer[j].c == s1[i])
				{
					break;
				}
		}
		num1 += co * answer[j].v;
		co *= 10;
	}
	co = 1;

	for (i = s2.length()-1; i >= 0; i--)
	{
		for (j = 0; j < count; j++)
		{
			if (answer[j].c == s2[i])
				{
					break;
				}
		}
		num2 += co *answer[j].v;
		co *= 10;
	}
	co = 1;

	for (i = s3.length()-1; i >= 0; i--)
	{
		for (j = 0; j < count; j++)
		{
			if (answer[j].c == s3[i])
				{
					break;
				}
		}

		num3 += co * answer[j].v;
		co *= 10;
	}
	co = 1;
	if (num1 + num2 == num3)
		cout << num1 << " "<< num2 << " " << num3 << endl;
  return (num1 + num2 == num3);
}

bool find_answer(int count, data* answer, int n,string s1, string s2, string s3,unordered_map<char,unsigned> & mapping)
{
	if (n == count - 1)
	{
		for (int i = 0; i < 10; i++)
		{
			if (!used[i])
			{
				answer[n].v = i;
				if (verifysolution(answer,count, s1, s2, s3))
				{
					for (int j = 0; j < count; j++)
					{
						mapping.insert(std::pair<char,unsigned>(answer[j].c,answer[j].v));
					}
					return true;
				}
			}
		}
		return false;
	}

	for (int i = 0; i < 10; i++)
	{
		if (!used[i])
		{
			used[i] = true;
			answer[n].v = i;
			if (find_answer(count, answer, n + 1, s1, s2, s3,mapping))
			{
				return true;
			}
			used[i] = false;
		}
	}
	return false;
}

bool puzzleSolver(string s1, string s2,string s3,unordered_map<char,unsigned> & map)
{
  unordered_set<char> char_set;
  for (int i = 0; i < s1.length() ; i++)
  {
    char_set.insert(s1[i]);
  }

  for (int i = 0; i < s2.length() ; i++)
  {
    char_set.insert(s2[i]);
  }

  for (int i = 0; i < s3.length() ; i++)
  {
    char_set.insert(s3[i]);
  }

  if (char_set.size() > 10)
  {
    return false;
  }
  data data1[char_set.size()];
  vector<char> a(char_set.begin(),char_set.end());
  for (int i = 0; i< char_set.size(); i++)
  {
    data1[i].c = a[i];
  }

	if (find_answer(char_set.size(), data1, 0, s1, s2, s3, map))
	{
		for (auto pair:map)
		{
				std::cout << "{" << pair.first << ": " << pair.second << "}\n";
		}
		return true;
	}

	return false;
}


int main()
{
	unordered_map<char,unsigned> puzzle;
  puzzleSolver("KUCI", "ALEX", "MIKE", puzzle);
	return 0;
}
