#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

ll MOD = 998244353;
ll maxN = 2*1e5;
vector<ll> catalan(maxN+1);
void setUpCatalan() {
    vector<ll> inv(maxN+1);
    inv[1] = 1;
    for (int i = 2; i < maxN+1; i++) { 
        inv[i] = MOD - MOD / i * inv[MOD % i] % MOD; 
    }
    catalan[0] = 1;
    catalan[1] = 1;
    for (int i = 2; i < maxN + 1; i++) {
        catalan[i] = ( catalan[i-1] * (2LL*(2*i - 1) % MOD) ) % MOD;
        catalan[i] = ( catalan[i] * inv[i+1] ) % MOD;
    }

}

struct lengthCmp {
    bool operator()(const pii& a, const pii& b) const {
        int diffA = a.second - a.first;
        int diffB = b.second - b.first;
        
        if (diffA != diffB) {
            return diffA < diffB;  // Compare based on difference first
        }
        if (a.first != b.first) {
            return a.first < b.first;
        }
        return a.second < b.second;
    }
};

struct pair_hash {
    std::size_t operator()(const std::pair<int, int>& p) const {
        std::size_t h1 = std::hash<int>{}(p.first);
        std::size_t h2 = std::hash<int>{}(p.second);
        return h1 ^ (h2 << 1); // XOR with bit shifting
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    setUpCatalan();
    while (T--) {
        int M, N; cin >> M >> N;
        set<pii, lengthCmp> segments;
        for (int i = 0; i < N; i++) {
            int a, b; cin >> a >> b;
            segments.insert(mp(a, b));
        }
        for (int i = 1; i <= M; i++) {
            segments.insert(mp(i, i));
        }
        segments.insert(mp(1, M));

        vector<pii> order(segments.size());
        unordered_map<pii, int, pair_hash> id;
        int a = 0;
        for (auto const &seg : segments) {
            order[a] = seg;
            id[seg] = a;
            a++;
        }
        vector<unordered_set<int>> children(segments.size());
        vector<int> parent(segments.size(), -1);
        set<pii> curr;
        for (int i = 0; i < segments.size(); i++) {
            auto it = curr.upper_bound(mp(order[i].first, 0));
            while (it != curr.end() && it->second <= order[i].second) {
                pii cSeg = *it; 
                children[i].insert(id[cSeg]);
                parent[id[cSeg]] = i;
                it = curr.erase(it);
            }
            curr.insert(order[i]);
        }

        vector<ll> dp(segments.size());
        function<ll(int)> dfs = [&](int node) {
            // cout << "processing (" << order[node].first << " " << order[node].second << ")" << endl;
            if (dp[node] > 0) {
                // cout << "already processed, value: " << dp[node] << endl;
                return dp[node];
            }
            if (children[node].size() == 0) {
                dp[node] = 1;
                // cout << "node is leaf" << endl;
                return 1LL;
            }
            ll mult = 1;
            for (int neighbor : children[node]) {
                mult *= dfs(neighbor);
                mult %= MOD;
            }
            mult *= catalan[children[node].size() - 1];
            mult %= MOD;
            // cout << "processed (" << order[node].first << " " << order[node].second << "), value " << mult << endl;
            dp[node] = mult;
            return dp[node];
        };
        cout << dfs(segments.size() - 1) << endl;
    }
}
