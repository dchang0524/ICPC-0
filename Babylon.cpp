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
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<ll> vll;
typedef vector<vector<ll>> vvl;
typedef unsigned long long ull;

template <typename T> 
vector<T> ndvec(size_t size, T initial_value) {
    return vector<T>(size, initial_value);
}

template <typename T, typename... U> 
auto ndvec(size_t head, U &&...u){
    auto inner = ndvec<T>(u...);
    return vector<decltype(inner)>(head, inner);
}

void solve() {
    int n; cin >> n;

    vector<pair<ll, pii>> blocks(n);

    FOR (i, 0, n) {
        int l, w; cin >> l >> w;
        if (w > l) {
            swap(l, w);
        }
        blocks[i] = {(ll)l * w, {l, w}};
    }
    sort(blocks.begin(), blocks.end());

    ll MOD = 998244353;
    vector<ll> fact(n + 1, 1);
    FOR (i, 1, n + 1) {
        fact[i] = fact[i - 1] * i % MOD;
    }

    ll cnt = 1;
    int currSame = 1;
    FOR (i, 1, n) {
        pii currBlock = blocks[i].second;
        pii prevBlock = blocks[i - 1].second;

        if (currBlock.first < prevBlock.first ||
            currBlock.second < prevBlock.second) {
            cnt = 0;
            break;
        }

        if (currBlock == prevBlock) {
            currSame++;
            continue;
        }
        cnt = cnt * fact[currSame] % MOD;
        currSame = 1;

        //base
        ll prod = (ll)(currBlock.first - prevBlock.first + 1) * (currBlock.second - prevBlock.second + 1) % MOD;
        //rotation
        if (prevBlock.first != prevBlock.second && prevBlock.first <= currBlock.second) {
            prod += (ll)(currBlock.first - prevBlock.second + 1) * (currBlock.second - prevBlock.first + 1) % MOD;
            prod %= MOD;
        }
        cnt = cnt * prod % MOD;
    }

    if (cnt != 0) {
        cnt = cnt * fact[currSame] % MOD;
    }
    if (blocks[n-1].second.first != blocks[n-1].second.second) {
        cnt = (cnt * 2) % MOD;
    }
    cout << cnt << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    rep (T) {
        solve();
    }
}