#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

// Overload operator<< for set
template <typename T>
ostream& operator<<(ostream& os, const set<T>& s) {
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

// Overload the << operator for vector
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
   for (const auto& elem : v) {
       os << elem << " ";
   }
   return os;
}

int main() {
    // ios_base::sync_with_stdio(0);
    // cin.tie(0); cout.tie(0);
    int N; cin >> N;
    vector<int> charge(N+1);
    vector<set<pii>> adjList(N+1, set<pii>());
    for (int i = 1; i <= N; i++) {
        cin >> charge[i];
    }
    // cout << charge << endl;
    for (int i = 0; i < N-1; i++) {
        int u, v, w; cin >> u >> v >> w;
        adjList[u].insert(mp(v, w));
        adjList[v].insert(mp(u, w));
    }
    // for (int i = 0; i < N+1; i++) {
    //     for (auto j : adjList[i]) {
    //         cout << j << " ";
    //     }
    //     cout << endl;
    // }
    //dfs lambda function
    vector<int> order;
    function<void(int, int)> dfs = [&](int u, int parent) {
        order.pb(u);
        for (const auto& p : adjList[u]) {
            int v = p.first;
            if (v == parent) continue; // Skip the parent node
            dfs(v, u);
        }
    };
    dfs(1, 0);
    // cout << order << endl;
    ll cost = 0;
    for (int i = N-1; i > 0; i--) {
        // cout << "removing " << order[i] << endl;
        int node = adjList[order[i]].begin()->first;
        ll w = adjList[order[i]].begin()->second;
        cost += abs(charge[order[i]]) * w;
        charge[node] += charge[order[i]];
        adjList[node].erase(mp(order[i], w));
    }
    cout << cost << endl;
}
