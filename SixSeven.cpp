#include <bits/stdc++.h>
using namespace std;
//#include "debugPrints.h"

#define pb push_back
#define mp make_pair
#define sz(x) (int)(x).size()
#define rep(x) for (int neverusedvariable = 0; neverusedvariable < (x); ++neverusedvariable)
#define FOR(i, a, b) for(int i = a; i < (b); ++i)
#define FOR1(i, a, b) for(int i = a; i <= (b); ++i)
#define all(x) (x).begin(), (x).end()

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<ll> vll;
typedef vector<vector<ll>> vvl;
typedef unsigned long long ull;
template <typename T> 
vector<T> ndvec(size_t size, T initial_value) {
    return vector<T>(size, initial_value);
}
template <typename T, typename... U> 
auto ndvec(size_t head, U &&...u){
    auto inner = ndvec<T>(u...);
    return vector<decltype(inner)>(head, inner);
} //example: auto grid = ndvec<char>(n + 1, m + 1, '_');

void solve() {
    string num; cin >> num;
    if (num.size() > 9) {
        cout << -1 << endl;
        return;
    }
    int start = num[0] - '0';
    if (start + num.size() - 1 <= 9) {
        string s = "";
        for (int i = 0; i < num.size(); i++) {
            s += (char)(num[0] + i);
        }
        if (stoi(s) >= stoi(num)) {
            cout << s << endl;
            return;
        }
        
        if (start + num.size() <= 9) {
            s = "";
            for (int i = 1; i <= num.size(); i++) {
                s += (char)(num[0] + i);
            }
            cout << s << endl;
            return;
        }
    }
    start = 1;
    string s = "";
    for (int i = 0; i <= num.size(); i++) {
        s += (char)('0' + start + i);
    }
    if (stoi(s) >= stoi(num)) {
        cout << s << endl;
        return;
    }
    cout << -1 << endl;
    return;
}
    

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    rep (T) {
        solve();
    }
}

