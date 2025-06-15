#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define rep1(i, a, b) for(int i = a; i <= (b); ++i)
#define sz(x) ((int)(x).size())

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef unsigned long long ull;

// Overload the << operator for vector
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
   for (const auto& elem : v) {
       os << elem << " ";
   }
   return os;
}

// Overload operator<< for unordered_set
template <typename T>
ostream& operator<<(ostream& os, const unordered_set<T>& s) {
   os << "{";
   bool first = true;
   for (const auto& elem : s) {
       if (!first) os << ", ";
       os << elem; // Requires operator<< for T
       first = false;
   }
   os << "}";
   return os;
}

// Overload operator<< for pair
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) {
   os << "(" << p.first << ", " << p.second << ")";
   return os;
}

// Overload the << operator for deque
template <typename T>
ostream& operator<<(ostream& os, const deque<T>& dq) {
    os << "[";
    for (auto it = dq.begin(); it != dq.end(); ++it) {
        if (it != dq.begin()) {
            os << ", ";
        }
        print_element(os, *it);
    }
    os << "]";
    return os;
}

void solve() {
    int N; cin >> N;
    map<pii, unordered_set<int>> adj;
    map<pii, int> edgeID;
    rep1(i, 1, N) {
        int v, p; cin >> v >> p;
        adj[mp(v, 0)].insert(p);
        adj[mp(p, 1)].insert(v);
        edgeID[mp(v, p)] = i;
    }
    
    bool works = true;
    pii v1 = mp(-1, -1); pii v2 = mp(-1, -1);
    for (const auto &c : adj) {
        if (sz(c.second) % 2 == 1) {
            if (v1 == mp(-1, -1)) {
                v1 = c.first;
            } else if (v2 == mp(-1, -1)) {
                v2 = c.first;
            } else {
                works = false;
            }
        }
    }
    // cout << v1 << " " << v2 << endl;
    if (!works) {
        cout << "NO" << endl;
        return;
    }
    // bool added = false;

    // if (v1.first != -1) {
    //     if (adj[v1].count(v2.first)) {
    //     adj[v1].erase(v2.first);
    //     adj[v2].erase(v1.first);
    //     } else {
    //         adj[v1].insert(v2.first);
    //         adj[v2].insert(v1.first);
    //     }
    // }

    deque<pii> ans;
    deque<pii> q;
    if (v1.first != -1) {
        // cout << "trail" << endl;
        // cout << v1 << " " << v2 << endl;
        q.pb(v1);
    } else {
        // cout << "circuit" << endl;
        // cout << adj.begin()->first << ": " << adj.begin()->second << endl;
        q.pb(adj.begin()->first);
    }
    // cout << "start:" << q[0] << endl;

    function<void(pii)> dfs = [&] (pii c) -> void {
        // cout << "Traversing " << c << endl;
        q.pb(c);
        if (adj[c].size()) {
            int nxt = *adj[c].begin();
            adj[c].erase(nxt);
            adj[mp(nxt, c.second^1)].erase(c.first);
            dfs(mp(nxt, c.second^1));
        }
    };
    // cout << adj[mp(1, 0)] << endl;
    while (sz(q)) {
        pii curr = q.back();
        // cout << "Current: " << curr << endl;
        q.pop_back();
        // cout << adj[curr].size() << endl;
        if (adj[curr].size()) {
            dfs(curr);
        } else {
            ans.push_front(curr);
        }
    }
    // for (auto p : ans) {
    //     cout << p << " ";
    // }
    // cout << endl;
    vector<int> finalAns;
    for (int i = 0; i < sz(ans) - 1; i++) {
        if (ans[i].second == 0) {
            finalAns.pb(edgeID[mp(ans[i].first, ans[i + 1].first)]);
        } else {
            finalAns.pb(edgeID[mp(ans[i + 1].first, ans[i].first)]);
        }
    }
    if (finalAns.size() == N) {
        cout << "YES" << endl;
        cout << finalAns << endl;
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

