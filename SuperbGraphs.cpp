#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define sz(x) (int)(x).size()
#define rep(i, a, b) for(int i = a; i < (b); ++i)

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef unsigned long long ull;

void solve() {
    int N, K; cin >> N >> K;
    vector<unordered_set<int>> zero(N + 1); //For each (i, j) where j is in zero[i], at least one of i or j is 0
    vector<unordered_set<int>> one(N + 1); //For each (i, j) where j is in one[i], at least one of i or j is 1
    for (int i = 0; i < K; ++i) {
        // cout << "Processing graph " << i + 1 << endl;
        int M; cin >> M;
        vector<vector<int>> adj(N+1);
        for (int j = 0; j < M; ++j) {
            int x, y; cin >> x >> y;
            adj[x].pb(y);
            adj[y].pb(x);
        }
        for (auto &v : adj) {
            sort(v.begin(), v.end());
        }

        for (int i = 1; i <= N; ++i) {
            for (int j = i + 1; j <= N; ++j) {
                bool same = true;
                bool areNeighbors = false;
                int ptr1 = 0, ptr2 = 0;
                while (ptr1 < adj[i].size() && ptr2 < adj[j].size()) {
                    if (adj[i][ptr1] == j) {
                        areNeighbors = true;
                        ptr1++;
                    } else if (adj[j][ptr2] == i) {
                        areNeighbors = true;
                        ptr2++;
                    } else if (adj[i][ptr1] != adj[j][ptr2]) {
                        same = false;
                        break;
                    } else {
                        ptr1++;
                        ptr2++;
                    }
                }
                if (ptr1 < adj[i].size() && (ptr1 != adj[i].size()-1 || adj[i][ptr1] != j) ) {
                    same = false;
                } else if (ptr2 < adj[j].size() && (ptr2 != adj[j].size()-1 || adj[j][ptr2] != i)) {
                    same = false;
                }
                if (same) {
                    if (areNeighbors) {
                        one[i].insert(j);
                        one[j].insert(i);
                    } else {
                        zero[i].insert(j);
                        zero[j].insert(i);
                    }
                }
            }
        }
    }
    

    vector<int> color(N + 1, -1);
    function<bool(int, int)> bfs = [&](int node, int c) {
        queue<int> q;
        vector<int> reset; //visited nodes to reset color after BFS, if coloring fails
        bool conflict = false;
        q.push(node);
        color[node] = c;
        reset.push_back(node);
        while (!q.empty() && !conflict) {
            int curr = q.front();
            q.pop();
            if (color[curr] == 0) {
                for (int neighbor : one[curr]) {
                    if (color[neighbor] == -1) {
                        color[neighbor] = 1;
                        reset.pb(neighbor);
                        q.push(neighbor);
                    } else if (color[neighbor] == 0) {
                        conflict = true;
                        break;
                    }
                }
            } else {
                for (int neighbor : zero[curr]) {
                    if (color[neighbor] == -1) {
                        color[neighbor] = 0;
                        reset.pb(neighbor);
                        q.push(neighbor);
                    } else if (color[neighbor] == 1) {
                        conflict = true;
                        break;
                    }
                }
            }
        }


        if (conflict) {
            for (int node : reset) {
                color[node] = -1; // Reset colors if conflict occurs
            }
        }
        return !conflict;
    };

    bool possible = true;
    for (int i = 1; i <= N && possible; ++i) {
        if (color[i] == -1) { 
            bool works = bfs(i, 0); 
            if (!works) {
                works = bfs(i, 1); 
            }
            possible &= works;
        }
    }
    if (possible) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) {
        solve();
    }
}

