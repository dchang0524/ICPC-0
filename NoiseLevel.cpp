#include <bits/stdc++.h>
using namespace std;
// #include "debugPrints.h"

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
    int N, M, q, p; cin >> N >> M >> q >> p;
    vector<string> grid(N);
    FOR (i, 0, N) {
        cin >> grid[i];
    }
    vector<vector<ll>> sound(N, vector<ll>(M));
    vi dx = {1, -1, 0, 0};
    vi dy = {0, 0, 1, -1};
    function<void(int, int, int)> fill = [&](int i, int j, int v) -> void {
        auto dist = ndvec<int>(N, M, -1);
        deque<tuple<int, int, int>> bfs;
        dist[i][j] = 0;
        bfs.pb({i, j, v});
        while (!bfs.empty()) {
            int x = get<0>(bfs.front());
            int y = get<1>(bfs.front());
            int val = get<2>(bfs.front());
            bfs.pop_front();
            sound[x][y] += val;
            if (val/2 <= 0) {
                continue;
            }
            for (int d = 0; d < 4; d++) {
                int xP = x + dx[d];
                int yP = y + dy[d];
                if (xP < 0 || xP >= N || yP < 0 || yP >= M) {
                    continue;
                }
                if (dist[xP][yP] == -1 && grid[xP][yP] != '*') {
                    dist[xP][yP] = dist[x][y] + 1;
                    bfs.pb({xP, yP, val/2});
                }
            }
        }
        // FOR (i, 0, N) {
        //     cout << dist[i] << endl;
        // }
    };

    FOR (i, 0, N) {
        FOR (j, 0, M) {
            if (grid[i][j] >= 'A' && grid[i][j] <= 'Z') {
                // cout << "i: " << i << " j: " << j << " v: " << (grid[i][j] - 'A' + 1)*q << endl;
                fill(i, j, (grid[i][j] - 'A' + 1)*q);
            }
        }
    }

    int ans = 0;
    FOR (i, 0, N) {
        FOR (j, 0, M) {
            if (sound[i][j] > p) {
                ans++;
            }
        }
    }
    cout << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T = 1; //cin >> T;
    rep (T) {
        solve();
    }
}

