#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

int solution(vector<int> A)
{
  // Your solution goes here.
  map<int, int> rows;
  for (int h : A) {
    auto ptr = rows.upper_bound(h);
    if (ptr == rows.end()) {
        rows[h]++;
    } else {
        int k = ptr->first;
        int v = ptr->second;
        rows[k]--;
        if (rows[k] == 0) {
            rows.erase(k);
        }
        rows[h]++;
    }
  }
  int total = 0;
  for (auto p : rows) {
    total += p.second;
  }
  return total; 
}

vector<int> toIntVector(string str)
{
  std::vector<int> out;
  std::string i;
  std::istringstream tokenStream(str);
  while (std::getline(tokenStream, i, ','))
  {
    out.push_back(atoi(i.c_str()));
  }
  return out;
}

int main()
{
  // Read in from stdin, solve the problem, and write answer to stdout.
  string AS;
  cin >> AS;
  vector<int> A = toIntVector(AS);
  cout << solution(A);
}