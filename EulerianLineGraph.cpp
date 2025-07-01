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


void solve(int t) {
    int N, M, K; cin >> N >> M >> K;
    // if (t == 75) {
    //     cout << N << "|" << M << "|" << K << endl;
    // }
    vector<vi> adj(N + 1);
    vi deg(N + 1, 0);
    rep(i, 0, M) {
        int u, v; cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
        deg[u]++;
        deg[v]++;
    }
    int odd1 = -1, odd2 = -1;
    rep(i, 1, N + 1) {
        if (deg[i] % 2 == 1) {
            if (odd1 == -1) {
                odd1 = i;
            } else {
                odd2 = i;
            }
        }
    }
    if (odd1 == -1 && odd2 == -1) {
        cout << "YES\n";
        return;
    }
    int oddEdges = 0;
    rep (i, 1, N + 1) {
        for (int v : adj[i]) {
            if (deg[i] % 2 != deg[v] % 2) {
                oddEdges++;
            }
        }
    }
    oddEdges /= 2;
    if (oddEdges == M) {
        if (K == 1) {
            cout << "NO" << endl;
            return;
        } else {
            cout << "YES" << endl;
            return;
        }
    }

    //L(G) and L^2(G)
    bool first = false;
    bool second = false;
    if (deg[odd1] + deg[odd2] == 2 || deg[odd1] + deg[odd2] == 4 && (adj[odd1][0] == odd2 || adj[odd2][0] == odd1)) {
        first = true;
    }
    ll cnt = 0;
    rep(i, 1, N + 1) {
        ll nOdd = 0;
        ll nEven = 0;
        for (int v : adj[i]) {
            if (deg[v] % 2 == 1) {
                nOdd++;
            } else {
                nEven++;
            }
        }
        cnt += nOdd * nEven;
    }
    if (cnt == 2) {
        second = true;
    }

    if (!(first && second)) {
        if (first && K == 1) {
            cout << "YES" << endl;
            return;
        } else if (second && K == 2) {
            cout << "YES" << endl;
            return;
        } else {
            cout << "NO" << endl;
            return;
        }
    }

    //G, L(G), L^2(G) have Euler Tour
    int dist1 = 0;
    int prev = 0;
    int curr = odd1;
    while (adj[curr].size() <= 2) {
        for (int i : adj[curr]) {
            if (i != prev) {
                prev = curr;
                curr = i;
                dist1++;
                break;
            }
        }
    }
    int dist2 = 0;
    prev = 0;
    curr = odd2;
    while (adj[curr].size() <= 2) {
        for (int i : adj[curr]) {
            if (i != prev) {
                prev = curr;
                curr = i;
                dist2++;
                break;
            }
        }
    }
    if (K <= min(dist1, dist2)) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }


}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        solve(T);
    }
}

