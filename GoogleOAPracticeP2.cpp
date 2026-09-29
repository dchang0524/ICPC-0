#include <iostream>
#include <regex>
#include <string>
#include <vector>

using namespace std;

int solution(vector<int> A)
{
  vector<int> possible(100001);
  possible[0] = 1; 
  int sum = 0;
  for (int w : A) {
    for (int i = possible.size() - 1; i >= w; i--) {
        possible[i] |= possible[i - w];
    }
    sum += w;
  }
  int best = possible.size();
  for (int i = 0; i < possible.size(); i++) {
    if (possible[i]) {
        best = min(best, abs(sum - 2 * i));
    }
  }
  return best; 
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
  cout << solution(toIntVector(AS));
}