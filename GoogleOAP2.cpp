#include <iostream>
#include <vector>
using namespace std;
int solution(vector<int> &chapters, vector<int> &evenings) {
  cerr << "Tip: Use cerr to write debug messages on the output tab.";
  int c = 0;
  int e = 0;
  int ans = 0;
  bool done = false;
  for (int e = 0; e < evenings.size(); e++) {
    int budget = evenings[e];
    while (budget > 0 && c < chapters.size()) {
        if (budget >= chapters[c]) {
            budget -= chapters[c];
            c++;
        } else {
            break;
        }
    }
    ans++;
    if (c >= chapters.size()) {
        done = true;
        break;
    }
  }
  if (!done) {
    ans = -1;
  }
  return ans;
}