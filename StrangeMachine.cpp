#include <bits/stdc++.h>
using namespace std;
// #include "debugPrints.h"

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
    int N, Q; cin >> N >> Q;
    string t; cin >> t;
    vi nxtB(N);
    int lastB = N;
    for (int i = N - 1; i >= 0; --i) {
        nxtB[i] = lastB;
        if (t[i] == 'B') lastB = i;
    }
    if (lastB == N) {
        rep (Q) {
            int q; cin >> q;
            cout << q << endl;
        }
        return;
    }
    for (int i = N - 1; i >= 0; --i) {
        if (nxtB[i] == N) {
            nxtB[i] = lastB;
        }
    }
    // cout << nxtB << endl;
    rep (Q) {
        int q; cin >> q;
        // cout << "Testing q = " << q << endl;
        int curr = 0;
        int steps = 1;
        if (t[0] == 'B') {
            q /= 2;
        } else {
            q--;
        }
        while (q > 0) {
            // cout << "curr = " << curr << ", q = " << q << endl;
            int dist = 0;
            if (nxtB[curr] == curr) {
                dist = N;
            } else if (nxtB[curr] > curr) {
                dist = nxtB[curr] - curr;
            } else {
                dist = N - curr + nxtB[curr];
            }
            if (q <= dist) {
                steps += q;
                break;
            }
            int step = min(dist, dist); 
            // cout << "step = " << step << endl;
            q -= (step-1);
            q /= 2;
            curr = (curr + step) % N;
            steps += step;
        }
        cout << steps << endl;
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

