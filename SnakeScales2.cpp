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

int first_true(int lo, int hi, function<bool(int)> f) {
		//return hi + 1 if none of the values work
    hi++;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (f(mid)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    return lo;
}

int solve() {
    int N; cin >> N;
    vi h(N);
    FOR (i, 0, N) {
        cin >> h[i];
    }
    function<bool(int)> check = [&](int x) -> bool {
        vi vis(N);
        deque<int> bfs;
        FOR (i, 0, N) {
            if (h[i] <= x) {
                bfs.pb(i);
                vis[i] = 1;
            }
        }
        while (!bfs.empty()) {
            int i = bfs.front();
            bfs.pop_front();
            if (i + 1 < N && !vis[i+1] && abs(h[i+1] - h[i]) <= x) {
                vis[i+1] = 1;
                bfs.pb(i+1);
            }
            if (i-1 >= 0 &&  !vis[i-1] && abs(h[i-1] - h[i]) <= x) {
                vis[i-1] = 1;
                bfs.pb(i-1);
            }
        }
        FOR(i, 0, N) {
            if (!vis[i]) {
                return false;
            }
        }
        return true;
    };
    return first_true(0, 1e9, check);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    FOR1 (t, 1, T) {
        int ans = solve();
        cout << "Case #" << (t) << ": " << ans << endl;
    }
}

