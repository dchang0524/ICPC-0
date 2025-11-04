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
    int N; cin >> N;
    vector<ll> A(N);
    FOR (i, 0, N) {
        cin >> A[i];
    }
    reverse(A.begin(), A.end());
    // cout << A << endl;
    //for each i, find the 3+ j with minimum a[j] for j > i
    vector<vector<pll>> smallest(N, vector<pll>(3,{2*1e9, -1}));
    smallest[N-2][0] = {A[N-1], N-1};
    for (int i = N-3; i >= 0; i--) {
        smallest[i] = smallest[i+1];
        for (int d = 0; d < 3; d++) {
            if (A[i+1] <= smallest[i+1][d].first) {
                smallest[i].insert(smallest[i].begin() + d, {A[i+1], i+1});
                smallest[i].pop_back();
                break;
            }
        }
    }
    //for each i, find the 3+ j with maximum a[j] for j < i
    vector<vector<pll>> biggest(N, vector<pll>(3, {-2*1e9, 1}));
    biggest[1][0] = {A[0], 0};
    FOR (i, 2, N) {
        biggest[i] = biggest[i-1];
        for (int d = 0; d < 3; d++) {
            if (A[i-1] >= biggest[i-1][d].first) {
                biggest[i].insert(biggest[i].begin() + d, {A[i-1], i-1});
                biggest[i].pop_back();
                break;
            }
        }
    } 

    // cout << "smallest" << endl;
    // FOR (i, 0, N) {
    //     cout << smallest[i] << endl;
    // }
    // cout << "biggest" << endl;
    // FOR (i, 0, N) {
    //     cout << biggest[i] << endl;
    // }

    // Hao must remove element that has the 2nd best pair with itself = best and the highest 3rd best pair
    int best = -1e9;
    unordered_set<int> cand;
    FOR (i, 0, N) {
        int p1 = 0, p2 = 0;
        int c1 = -1;
        if (((ll)A[i] - smallest[i][p1].first > (ll)biggest[i][p2].first - A[i])) {
            c1 = smallest[i][p1].second;
            p1++;
        } else {
            c1 = biggest[i][p2].second;
            p2++;
        }
        int c2 = (A[i] - smallest[i][p1].first > biggest[i][p2].first - A[i]) ? smallest[i][p1].second : biggest[i][p2].second;
        int curr =  max(A[i] - smallest[i][p1].first, biggest[i][p2].first - A[i]);
        // cout << "2nd best for " << i << " : " << curr << endl;

        if (curr > best) {
            best = curr;
            cand.clear();
            cand.insert(i);
            cand.insert(c1);
            cand.insert(c2);
        } else if (curr == best) {
            if (!cand.count(i)) {
                cand.erase(i);
            }
            if (!cand.count(c1)) {
                cand.erase(c1);
            }
            if (!cand.count(c2)) {
                cand.erase(c2);
            }
        }
    }
    // cout << rmInd << endl;
    //simulate if Alex goes first, with rmInd removed
    ll score = 1e9;
    assert(cand.size() <= 3);
    if (cand.size() == 0) {
        cout << best << endl;
        return;
    }
    for (int rmInd : cand) {
        ll maxScore = -1e9;
        FOR (i, 0, N) {
            int p1 = 0, p2 = 0;
            if (rmInd == i) {
                continue;
            }
            if (rmInd > i && smallest[i][p1].second == rmInd) {
                p1++;
            } else if (rmInd < i && biggest[i][p2].second == rmInd) {
                p2++;
            }

            if (A[i] - smallest[i][p1].first > biggest[i][p2].first - A[i]) {
                p1++;
            } else {
                p2++;
            }
            if (rmInd > i && smallest[i][p1].second == rmInd) {
                p1++;
            } else if (rmInd < i && biggest[i][p2].second == rmInd) {
                p2++;
            }
            maxScore = max(maxScore, max(A[i] - smallest[i][p1].first, biggest[i][p2].first - A[i]));
        }
        score = min(score, maxScore);
    }
    cout << score << endl;
    
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    rep (T) {
        solve();
    }
}

