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
typedef vector<ll> vll;
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
    int N; cin >> N;
    vi A(N);
    vi ind(N+1);
    FOR (i, 0, N) {
        cin >> A[i];
        ind[A[i]] = i;
    }
    // cout << A << endl;
    // cout << ind << endl;
    FOR1 (best, 1, N) {
        //find first index where A[i] % 2 == best % 2 and A[i:N-1] contains [best, A[i]]. If A[0] % 2 == best % 2 , i = 0.
        int first = ind[best];
        int curr = ind[best];
        FOR1 (i, best+1, N) {
            curr = min(curr, ind[i]);
            if (i % 2 == best % 2 && ind[i] <= curr) {
               first = min(first, curr); 
            }
        }
        // cout << first << endl;
        //increment values <= [best,A[i]] by 1
        for (int i = A[first]; i > best; i--) {
            ind[i] = ind[i-1];
            A[ind[i-1]]++;
        }
        ind[best] = first;
        A[first] = best;
        // cout << "Processed " << best << endl;
        // cout << A << endl;
        // cout << ind << endl;
    }

    FOR (i, 0, N) {
        cout << A[i] << " ";
    }
    cout << endl;
}

int main() {
    // ios_base::sync_with_stdio(0);
    // cin.tie(0); cout.tie(0);
    int T; cin >> T;
    rep (T) {
        solve();
    }
}

