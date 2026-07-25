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
    int n, k, p, m; cin >> n >> k >> p >> m;
    vi costs(n+1);
    int cnt = 0;
    FOR1(i, 1, n) {
        cin >> costs[i];
    }
    if (p > k) {
        //lowest p-k numbers within [1, p-1]
        sort(costs.begin() + 1, costs.begin() + p);
        FOR1 (i, 1, p-k) {
            m -= costs[i];
        }    
    }
    if (m >= costs[p]) {
            m -= costs[p];
            cnt++;
    } else {
        cout << 0 << endl;
        return;
    }
    std::swap(costs[p], costs[n]);
    sort(costs.begin()+1, costs.begin() + (n));
    //lowest n - k numbers
    int totalCost = 0;
    FOR1 (i, 1, n-k) {
        totalCost += costs[i];
    }
    totalCost += costs[n];
    cnt += m / totalCost;
    cout << cnt << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    rep (T) {
        solve();
    }
}

