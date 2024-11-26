//https://codeforces.com/contest/2039/problem/B
//If there's any two consective equal characters in the string, the substring containing those two letters have an even number of nonempty substrings
//If there's any three consecutive characters that are all distinct in the string, the substring containing those three letters have an even number of nonempty substrings
//If there aren't two consecutive equal characters or three consecutive characters all distinct, the string must alternate between two distinct characters
    //It is clear no such strings have an even number of nonempty substrings
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        string s;
        cin >> s;
        int containsSameAdj = -1;
        int allDiff = -1;
        for (int i = 0; i+1 < s.size(); i++) {
            if (s[i] == s[i+1]) {
                containsSameAdj = i;
            }
        }
        if (containsSameAdj != -1) {
            cout << s.substr(containsSameAdj, 2) << endl;
            continue;
        }
        for (int i = 0; i+2 < s.size(); i++) {
            if (s[i] != s[i+1] && s[i] != s[i+2] && s[i+1] != s[i+2]) {
                allDiff = i;
            }
        }
        if (allDiff != -1) {
            cout << s.substr(allDiff, 3) << endl;
            continue;
        }
        cout << -1 << endl;
    }
}
