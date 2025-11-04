#include <bits/stdc++.h>
using namespace std;
//#include "debugPrints.h"

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
    int N, K; cin >> N >> K;
    vi cnt(N + 1);
    FOR (i, 0, N) {
        int a; cin >> a;
        cnt.at(a)++;
    }
    if (N == 1) {
        cout << 1 << endl;
        return;
    }
    vi prefCnt(N+1);
    FOR1 (i, 1, N) {
        prefCnt[i] = prefCnt[i-1] + cnt[i];
    }
    for (int i = N; i >= 1; i--) {
        if (i == 1) {
            cout << 1 << endl;
            return;
        }
        int bad = prefCnt[min(4*i - 1, N)] - cnt[i] - cnt[2*i <= N ? 2*i : 0] - cnt[3*i <= N ? 3*i : 0];
        // cout << "i = " << i << ", bad = " << bad << endl;
        if (bad <= K) {
            cout << i << endl;
            return;
        }
    }

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    rep (T) {
        solve();
    }
}

