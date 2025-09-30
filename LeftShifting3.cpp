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

int check(string s) {
    string t = "nanjing";
    int match = 0;
    FOR (i, 0, sz(s)) {
        bool works = true;
        FOR (j, 0, sz(t)) {
            if (i + j > sz(s) || s[i+j] != t[j]) {
                works = false;
                break;
            }
        }
        if (works) {
            match++;
        }
    }
    return match;
}

void solve() {
    int N, K; cin >> N >> K;
    string s; cin >> s;
    int ans = 0;
    FOR1 (i, 0, min(min(sz(s) -1, K), 6)) {
        string t = s;
        rotate(t.begin(), t.begin() + i, t.end());
        ans = max(ans, check(t));
    }
    cout << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    rep (T) {
        solve();
    }
}

