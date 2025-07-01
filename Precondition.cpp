#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define sz(x) (int)(x).size()
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define rep1(i, a, b) for(int i = a; i <= (b); ++i)

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef unsigned long long ull;


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    string s, t; cin >> s >> t;
    unordered_set<char> tChar;
    for (int i = 0; i < sz(t); i++) {
        tChar.insert(t[i]);
    }
    bool works = true;
    for (int i = 1; i < sz(s); i++) {
        if (s[i] - 'A' <= 25 && s[i] - 'A' >= 0) {
            if (!tChar.count(s[i-1])) {
                works = false;
                break;
            }
        }
    }
    if (works) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}
