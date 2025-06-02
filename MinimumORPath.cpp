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

    int N, M; cin >> N >> M;
    vector<vector<int>> edges(M, vector<int>(3));
    for (int i = 0; i < M; i++) {
        int a, b, w; cin >> a >> b >> w;
        edges[i][0] = a;
        edges[i][1] = b;
        edges[i][2] = w;
    }

    auto check = [&] (int W) { //possible to traverse with edge weight <= W?
        vector<unordered_set<int>> adj(N+1);
        for (int i = 0; i < M; i++) {
            if ((edges[i][2]) <= W) {
                adj[edges[i][0]].insert(edges[i][1]);
                adj[edges[i][1]].insert(edges[i][0]);
            }
        }

        deque<int> bfs;
        bfs.pb(1);
        vector<bool> visited(N+1);
        visited[1] = true;
        while (!bfs.empty()) {
            int curr = bfs.front();
            bfs.pop_front();
            for (int a : adj[curr]) {
                if (!visited[a]) {
                    bfs.pb(a);
                    visited[a] = true;
                }
            }
        }
        if (visited[N]) {
            return true;
        }
        return false;
    };

    int ans = 0;
    for (int d = 29; d >= 0; d--) {
        bool need = !(check((1 << d) - 1));
        if (need) {
            ans |= (1 << d);
            for (int i = 0; i < M; i++) {
                edges[i][2] &= ~(1 << d);
            }
        }
    }
    cout << ans << endl;
}
