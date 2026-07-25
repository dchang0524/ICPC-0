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
    int n, m; cin >> n >> m;
    vi cnt(n+1);
    vector<vi> changes(m+1);
    vector<pii> color(n+1);
    FOR1 (i, 1, n) {
        int a, d, b; cin >> a >> d >> b;
        color[i] = mp(a, b);
        cnt[a]++;
        changes[d].pb(i);
    }
    int num = 0;
    FOR1 (i, 1, n) {
        if (cnt[i] > 0) {
            num++;
        }
    }
    FOR1 (i, 1, m) {
        while (!changes[i].empty()) {
            int curr = changes[i][sz(changes[i]) - 1];
            changes[i].pop_back();
            int a = color[curr].first;
            int b = color[curr].second;
            if (a == b) {
                continue;
            }
            cnt[a]--;
            cnt[b]++;
            if (cnt[a] == 0) {
                num--;
            }
            if (cnt[b] == 1) {
                num++;
            }
        }
        cout << num << endl;
    }



}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T = 1;
    rep (T) {
        solve();
    }
}

