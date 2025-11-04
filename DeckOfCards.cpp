#include <bits/stdc++.h>
using namespace std;
//#include "debugPrints.h"

#define pb push_back
#define mp make_pair
#define sz(x) (int)(x).size()
#define rep(x) for (int neverusedvariable = 0; neverusedvariable < (x); ++neverusedvariable)
#define FOR(i, a, b) for(int i = a; i < (b); ++i)
#define FOR1(i, a, b) for(int i = a; i <= (b); ++i)

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef unsigned long long ull;
template <typename T> 
vector<T> ndvec(size_t size, T initial_value) {
    return vector<T>(size, initial_value);
}
template <typename T, typename... U> 
auto ndvec(size_t head, U &&...u){
    auto inner = ndvec<T>(u...);
    return vector<decltype(inner)>(head, inner);
} ////example: auto grid = ndvec<char>(n + 1, m + 1, '_');

void solve() {
    int N, K; cin >> N >> K; 
    int minFront = 0; int q = 0;
    int minBack = N+1;
    string s; cin >> s;
    FOR (i, 0, K) {
        char t = s[i];
        if (t == '0') {
            minFront++;
        } else if (t == '1') {
            minBack--;
        } else {
            q++;
        }
    }
    // cout << minFront << " " << maxFront << endl;
    // cout << minBack << " " << minBack << endl;
    FOR1 (i, 1, N) {
        if (i <= minFront || i >= minBack || (q > (i-1 - minFront) + minBack - (i+1))) {
            cout << '-';
        } else if (i <= minFront + q || i >= minBack - q){
            cout << '?';
        } else {
            cout << '+';
        }
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    rep (T) {
        solve();
    }
}

