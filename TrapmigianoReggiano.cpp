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
    int T; cin >> T;
    while (T--) {
        int N, st, en; cin >> N >> st >> en;
        st--; en--;
        vector<vector<int>> edges(N);
        for (int i = 0; i < N-1; i++) {
            int a, b; cin >> a >> b; a--; b--;
            edges[a].pb(b);
            edges[b].pb(a);
        }
        vector<int> visited(N);
        vector<int> order;
        function<void(int)> dfs = [&](int node) {
            visited[node] = 1;
            order.pb(node);
            for (int i : edges[node]) {
                if (visited[i] == 0) {
                    dfs(i);
                }
            }
        };
        dfs(en);
        for (int i = N-1; i >= 0; i--) {
            cout << (order[i] + 1) << " ";
        }
        cout << endl;
    }
}
