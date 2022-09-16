#include "convert.hpp"
#include "Wordset.hpp"
#include <iostream>
#include <set>
#include <sstream>
#include <map>
#include <stack>
#include <queue>
#include <vector>

// You should not need to change this function.
void loadWordsIntoTable(WordSet & words, std::istream & in)
{
	std::string line, word;
	std::stringstream ss;

	while(	getline(in, line) )
	{
		ss.clear();
		ss << line;
		while( ss >> word )
		{
			words.insert( word );
		}
	}
}


bool BFS(std::string s1, std::string s2, std::map<std::string,std::set<std::string>> graph,	std::map<std::string,std::string> &pred,
	std::map<std::string,int> &dist)
{
	std::queue<std::string> Q;
	std::set<std::string> visited;

	for (auto x:graph)
	{
		pair<std::string,int> p1 = pair<std::string,int>(x.first,50000);
		pair<std::string,std::string> p2 = pair<std::string,std::string>(x.first,"");
		dist.insert(p1);
		pred.insert(p2);
	}

	visited.insert(s1);
	Q.push(s1);
	dist[s1] = 0;
	while (! Q.empty())
	{
		std::string v = Q.front();
		Q.pop();
		for (auto s:graph[v])
		{
			if (visited.find(s) == visited.end())
			{
				visited.insert(s);
				dist[s]++;
				pred[s] = v;
				Q.push(s);
				if (s == s2)
				{
					return true;
				}
			}
		}
	}
	return false;
}

std::vector<std::string> SD(std::map<std::string,std::set<std::string>> garph, std::string s1, std::string s2)
{
	std::map<std::string,std::string> pred;
	std::map<std::string,int> dist;
	if (! BFS(s1,s2,garph,pred,dist))
	{
		std::vector<std::string> a;
		return a;
	}

	std::vector<std::string> answer;
	std::vector<std::string> path;
	std::string c = s2;
	path.push_back(c);
	while (pred[c] != "")
	{
		path.push_back(pred[c]);
		c = pred[c];
	}

	for (int i = path.size()-1; i >= 0; i--)
	{
		answer.push_back(path[i]);
	}
	return answer;


}


// You probably want to change this function.
std::vector< std::string > convert(const std::string & s1, const std::string & s2, const WordSet & words)
{
	std::vector< std::string > solution;
	std::map<std::string,std::set<std::string>> graph;
	if (! (words.contains(s1) && words.contains(s2)))
	{
		return solution;
	}	

	if (s1.size() != s2.size())
	{
		return solution;
	}

	std::vector<std::string> temp;
	for (int i = 0; i < words.size; i++)
	{
		if (words.base1[i].size() == s1.size())
		{
			temp.push_back(words.base1[i]);
		}

		if (words.base2[i].size() == s1.size())
		{
			temp.push_back(words.base2[i]);
		}
	}
	for (int i = 0; i < temp.size(); i++)
	{
		std::set<std::string> my_set;
		std::string key = temp[i];
		for (int j = 0 ; j < temp.size(); j++)
		{
			std::string value = temp[j];
			if (key != value)
			{
				unsigned count = 0;
				for (int m = 0 ; m < key.size() ; m++)
				{
					if (key[m] != value[m] )
					{
						count++;
					}
				}
				if (count == 1)
				{
					
					my_set.insert(value);
				}
			}
		}
		graph.insert(std::pair<std::string,std::set<std::string>>(key,my_set));
	}

				
	 
	return SD(graph,s1,s2);

}
