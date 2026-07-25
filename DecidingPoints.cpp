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
} //example: auto grid = ndvec<char>(n + 1, m + 1, '_');

string solve() {
	int N, M; cin >> N >> M;
    bool possible = true;
    if (N < M || (N > 2*M - 2 && N % 2 == 1)) {
        possible = false;
    }
    if (possible) {
        return "YES";
    }
    return "NO";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    FOR1 (t, 1, T) {
        string ans = solve();
        cout << "Case #" << (t) << ": " << ans << endl;
    }
}

