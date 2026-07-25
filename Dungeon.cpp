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
} ////example: auto grid = ndvec<char>(n + 1, m + 1, '_');

int last_true(int lo, int hi, function<bool(int)> f) {
    // if none of the values in the range work, return lo - 1
    lo--;
    while (lo < hi) {
        // find the middle of the current range (rounding up)
        int mid = lo + (hi - lo + 1) / 2;
        if (f(mid)) {
            // if mid works, then all numbers smaller than mid also work
            lo = mid;
        } else {
            // if mid does not work, greater values would not work either
            hi = mid - 1;
        }
    }
    return lo;
}

void solve() {
    int N, M; cin >> N >> M;
    vi swords(N);
    FOR (i, 0, N) {
        cin >> swords[i];
    }
    vector<pii> monsters(M);
    FOR (i, 0, M) {
        cin >> monsters[i].first;
    }
    FOR (i, 0, M) {
        cin >> monsters[i].second;
    }
    vector<pii> free;
    vector<int> actual;
    FOR (i, 0, M) {
        if (monsters[i].second == 0) {
            actual.pb(monsters[i].first);
        } else {
            free.pb(monsters[i]);
        }
    }
    sort(free.begin(), free.end());
    sort(swords.begin(), swords.end());
    sort(actual.begin(), actual.end());

    int ans = 0;
    int maxSword = swords[N-1];
    FOR (i, 0, sz(free)) {
        if (free[i].first <= maxSword) {
            maxSword = max(maxSword, free[i].second);
            ans++;
        }
    }
    
    // cout << ans << endl;
    // cout << swords << endl;
    // cout << free << endl;
    // cout << actual << endl;
    function<bool(int)> check = [&](int k) -> bool {
        // cout << "Checking " << k << endl;
        if (k > sz(actual) || k > N) {
            return false;
        }
        multiset<int> currSwords;
        FOR (i, N-k, N) {
            currSwords.insert(swords[i]);
        }
        // cout << currSwords << endl;
        int pm = 0; //ptr for actual monsters to kill
        int pf = 0;
        multiset<int> increments; //increments for free monsters you can currently kill
        while (!currSwords.empty() && pm < k) {
            // cout << "pm: " << pm << endl;
            // while (pf < sz(free) && free[pf].first <= *currSwords.begin()) {
            //     increments.insert(free[pf].second);
            //     pf++;
            // }

            if (*currSwords.begin() >= actual[pm]) {
                currSwords.erase(currSwords.begin());
                pm++;                
                continue;
            }
            
            while (*currSwords.begin() < actual[pm]) {
                while (pf < sz(free) && free[pf].first <= *currSwords.begin()) {
                    increments.insert(free[pf].second);
                    pf++;
                }
                if (increments.empty()) {
                    break;
                }
                int nxt = max(*currSwords.begin(), *increments.begin());
                currSwords.erase(currSwords.begin());
                increments.erase(increments.begin());
                currSwords.insert(nxt);
            }
            if (*currSwords.begin() < actual[pm]) {
                return false;
            }
            pm++;
            currSwords.erase(currSwords.begin());
            // cout << currSwords << endl;
        }
        if (pm != k) {
            return false;
        }
        return true;
    };
    cout << ans + last_true(0, N, check) << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    rep (T) {
        solve();
    }
}

