#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

vector<int> use(10);

struct data
{
  int v;
  char c;
};

bool verifySolution(string s1, string s2, string s3, data* answer)
{
  int num;
  int nums1 = 0;
  for (int i = 0; i < s1.length() ; i++)
  {
    for (int m = 0; m < sizeof(answer); m++)
    {
      if (answer[m].c == s1[i])
      {
        num = answer[m].v;
        break;
      }
    }
    
    for (int j = s1.length() - 1-i; j > 0; j--)
    {
      num = num * 10;
      
    }
    nums1 += num;
  }

  int nums2 = 0;
  for (int i = 0; i < s2.length() ; i++)
  {
    for (int m = 0; m < sizeof(answer); m++)
    {
      if (answer[m].c == s2[i])
      {
        num = answer[m].v;
        break;
      }
    }
    
    for (int j = s2.length() - 1-i; j > 0; j--)
    {
      num = num * 10;
    }
    nums2 += num;
  }

  int nums3 = 0;
  for (int i = 0; i < s3.length() ; i++)
  {
    for (int m = 0; m < sizeof(answer); m++)
    {
      if (answer[m].c == s3[i])
      {
        num = answer[m].v;
        break;
      }
    }

    for (int j = s3.length() - 1-i; j > 0; j--)
    {
      num = num * 10;
    }
    nums3 += num;
  }

  return (nums1 + nums2 == nums3);

}

bool find_char(string s1, string s2, string s3, int num_char, int n, data * answer)
{
  if (n == num_char - 1)
  {
    for (int i = 0; i < 10 ; i++)
    {
      if (use[i] == 0)
      {
        answer[n].v = i;

        if (verifySolution(s1,s2,s3,answer))
        {
          cout << "The solution is:" << endl;
          for (int i = 0; i < num_char; i++)
          {
            cout << answer[i].c << " is " << answer[i].v << endl;
          }
          return true;
        }
      }
    }
    cout << "un" << endl;
    return false;
  }

  for (int i = 0; i < 10; i++)
  {
    if (use[i] == 0)
    {
      answer[n].v = i;
      use[i] = 1;

      if (find_char(s1,s2,s3,num_char,n+1,answer))
      {
        return true;
      }

      use[i] = 0;
    }
  }
  cout << "un1" << endl;
  return false;
}

bool solve(string s1, string s2, string s3)
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
  return find_char(s1,s2,s3,char_set.size(),0,data1);

};

int main()
{
  string a = "AAA";
  string b = "BBB";
  string c = "AAA";
  data d[2];
  d[0].c = "A";
  d[0].v = 1;
  d[1].c = "B";
  d[1].v = 0;
  cout << verifySolution(a,b,c,d);
  return 0;
};