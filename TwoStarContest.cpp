#include <bits/stdc++.h>
using namespace std;
// #include "debugPrints.h"

#define pb push_back
#define mp make_pair
#define sz(x) (int)(x).size()
#define rep(x) for (int neverusedvariable = 0; neverusedvariable < (x); ++neverusedvariable)
#define FOR(i, a, b) for(int i = a; i < (b); ++i)
#define FOR1(i, a, b) for(int i = a; i <= (b); ++i

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
    int N, M, K; cin >> N >> M >> K;
    vector<vector<ll>> p(N, vector<ll>(M));
    vector<pii> S(N);
    FOR (i, 0, N) {
        int s; cin >> s;
        S[i] = mp(s, i);
        FOR (j, 0, M) {
            cin >> p[i][j];
        }
    }
    sort(S.begin(), S.end());

    // cout << S << endl;
    // FOR (i, 0, N) {
    //     cout << p[i] << endl;
    // }


    int prevStar = 0; ll prevScore = -1; ll maxCurrScore = 0;
    bool works = true;
    FOR (i, 0, N) {
        int cS = S[i].first;
        int ci = S[i].second;
        ll cSum = 0;
        FOR (j, 0, M) {
            if (p[ci][j] != - 1)
                cSum += p[ci][j];
        }
        // cout << "cSum for " << ci << " = " << cSum << endl;
        ll toAdd = max(prevScore - cSum, (ll)-1) + 1;
        // cout << "toAdd "<< toAdd << endl;
        for (int j = 0; j < M; j++) {
            if (p[ci][j] != -1) {
                continue;
            }
            ll used = min(toAdd, (ll)K);
            toAdd -= used;
            p[ci][j] = used;
            cSum += used;
        }
        if (toAdd > 0) {
            works = false;
            break;
        }
        if (i + 1 < N && S[i+1].first > cS) {
            prevStar = cS;
            prevScore = max(cSum, maxCurrScore);
            maxCurrScore = 0;
        } else {
            maxCurrScore = max(maxCurrScore, cSum);
        }
    }
    if (!works) {
        cout << "No" << endl;
        return;
    }
    cout << "Yes" << endl;
    FOR (i, 0, N) {
        FOR (j, 0, M) {
            cout << p[i][j] << " ";
        }
        cout << endl;
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

