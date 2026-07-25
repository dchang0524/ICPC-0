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
typedef vector<int> vi;
typedef vector<vector<int>> vvi;

void solve() {
    int n; cin >> n;

    const int D = 10; // 3^10 = 59049 > 5e4

    vector<vi> digit(n, vi(D));
    FOR (i, 0, n) {
        int x = i;
        for (int k = 0; k < D; k++) {
            digit[i][k] = x % 3;
            x /= 3;
        }
    }

    vi pow3(D, 1);
    FOR (k, 1, D) pow3[k] = pow3[k - 1] * 3;

    vector<vi> queries;
    int id[D][3];

    // 30 ternary queries.
    // For each digit k, query cyclic orders:
    // G0 G1 G2, G1 G2 G0, G2 G0 G1.
    FOR (k, 0, D) {
        vi g[3];

        FOR1 (v, 1, n) {
            g[digit[v - 1][k]].pb(v);
        }

        FOR (shift, 0, 3) {
            id[k][shift] = sz(queries);

            vi p;
            p.reserve(n);

            FOR (t, 0, 3) {
                int group_id = (shift + t) % 3;
                for (int v : g[group_id]) p.pb(v);
            }

            queries.pb(p);
        }
    }

    // Extra reverse query.
    int rev_id = sz(queries);
    vi rev(n);
    FOR1 (v, 1, n) rev[v - 1] = v;
    reverse(all(rev));
    queries.pb(rev);

    int K = sz(queries); // 31

    cout << K << '\n';
    for (auto &p : queries) {
        FOR (i, 0, n) {
            if (i) cout << ' ';
            cout << p[i];
        }
        cout << '\n';
    }
    cout.flush();

    // add[query][v] = number of neighbors of v appearing before v in that query.
    vector<vi> add(K, vi(n + 1));

    FOR (qi, 0, K) {
        int prev = 0;

        FOR (pos, 0, n) {
            int x;
            cin >> x;

            if (x == -1) exit(0);

            int v = queries[qi][pos];
            add[qi][v] = x - prev;
            prev = x;
        }
    }

    //query [1, ..., n] and [n, ..., 1] to find degree of each vertex. 
    // Important: id[9][0] is exactly [1, 2, ..., n].
    int normal_id = id[D - 1][0];

    vi deg(n + 1);
    FOR1 (v, 1, n) {
        deg[v] = add[normal_id][v] + add[rev_id][v];
    }

    //Push all leaves onto a queue
    queue<int> q;
    FOR1 (v, 1, n) {
        if (deg[v] == 1) q.push(v);
    }

    //For each digit k, find inter-degree between groups whose vertex number is 0, 1, or 2 in that digit
    vector<array<array<int, 3>, D>> cnt(n + 1);

    FOR1 (v, 1, n) {
        FOR (k, 0, D) {
            FOR (t, 0, 3) {
                cnt[v][k][t] = 0;
            }
        }
    }

    FOR (k, 0, D) {
        FOR1 (v, 1, n) {
            int x = digit[v - 1][k];

            int prv = (x + 2) % 3;
            int nxt = (x + 1) % 3;

            // Let A_s be add[id[k][s]][v].
            //
            // shift = x:
            //   G_x comes first, so A_x only sees same-group previous vertices.
            //
            // shift = prv:
            //   G_prv comes before G_x, so A_prv - A_x gives neighbors in G_prv.
            //
            // shift = nxt:
            //   G_nxt and G_prv come before G_x, so A_nxt - A_prv gives neighbors in G_nxt.

            cnt[v][k][prv] = add[id[k][prv]][v] - add[id[k][x]][v];
            cnt[v][k][nxt] = add[id[k][nxt]][v] - add[id[k][prv]][v];

            // Same digit group is filled using total degree.
            cnt[v][k][x] = deg[v] - cnt[v][k][prv] - cnt[v][k][nxt];
        }
    }

    vector<pii> ans;
    ans.reserve(n - 1);

    vector<char> removed(n + 1, false);

    //While the queue is not empty, pop the leaf. 
    while (!q.empty()) {
        int v = q.front();
        q.pop();

        if (removed[v] || deg[v] != 1) continue;

        //It's neighbor's vertex number can be found by checking the value of each digit to which the leaf has a connection in that digit group
        int label = 0;

        FOR (k, 0, D) {
            int d = -1;

            FOR (t, 0, 3) {
                if (cnt[v][k][t] == 1) {
                    d = t;
                    break;
                }
            }

            label += d * pow3[k];
        }

        int u = label + 1;

        ans.pb({v, u});

        removed[v] = true;
        deg[v] = 0;

        //Then, decrement the neighbor's degree, and it's degree in the digit groups. If the neighbor has degree 1, add it to queue
        FOR (k, 0, D) {
            int dv = digit[v - 1][k];
            cnt[u][k][dv]--;
        }

        deg[u]--;

        if (deg[u] == 1) {
            q.push(u);
        }
    }

    for (auto [u, v] : ans) {
        cout << u << ' ' << v << '\n';
    }
    cout.flush();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int T; cin >> T;
    rep (T) {
        solve();
    }
}