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
auto ndvec(size_t head, U &&...u) {
    auto inner = ndvec<T>(u...);
    return vector<decltype(inner)>(head, inner);
}

void solve() {
    int N; 
    cin >> N;

    vi P(N);
    FOR(i, 0, N) {
        cin >> P[i];
    }

    vi Q(N);
    FOR(i, 0, N) {
        cin >> Q[i];
    }

    vll factorial(N + 1, 1);
    FOR1(i, 1, N) {
        factorial[i] = factorial[i - 1] * i;
    }

    function<ll(vi)> count = [&](vi A) -> ll {
        ll ans = 0;

        FOR(i, 0, N) {
            // First i digits are the same as A.
            // Count unused values smaller than A[i].
            ll cnt = A[i] - 1;

            FOR(j, 0, i) {
                if (A[j] < A[i]) {
                    cnt--;
                }
            }

            ans += cnt * factorial[N - i - 1];
        }

        return ans;
    };

    cout << max(0LL, count(Q) - count(P) - 1) << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); 
    cout.tie(0);

    int T = 1;
    rep(T) {
        solve();
    }
}