#include <iostream>
#include <unordered_map>
using namespace std;

bool verifySolution(std::string s1, std::string s2, std::string s3, const unordered_map<char, unsigned> & mapping)
{
  int nums1 = 0;
  for (int i = 0; i < s1.length() ; i++)
  {
    int num = mapping.at(s1[i]);
    for (int j = s1.length() - 1-i; j > 0; j--)
    {
      num = num * 10;
      
    }
    nums1 += num;
  }

  int nums2 = 0;
  for (int i = 0; i < s2.length() ; i++)
  {
    int num = mapping.at(s2[i]);
    for (int j = s2.length() - 1-i; j > 0; j--)
    {
      num = num * 10;
    }
    nums2 += num;
  }

  int nums3 = 0;
  for (int i = 0; i < s3.length() ; i++)
  {
    int num = mapping.at(s3[i]);
    for (int j = s3.length() - 1-i; j > 0; j--)
    {
      num = num * 10;
    }
    nums3 += num;
  }

  return (nums1 + nums2 == nums3);

};

int main()
{
  return 0;
}