#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

// Overload operator<< for pair
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) {
   os << "(" << p.first << ", " << p.second << ")";
   return os;
}

// Overload the << operator for vector
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
   for (const auto& elem : v) {
       os << elem << " ";
   }
   return os;
}

void solve() {
    int N, M, K; cin >> N >> M >> K;
    vector<int> a(N);
    vector<int> b(M);
    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < M; i++) {
        cin >> b[i];
    }
    vector<vector<int>> ops(M+1);
    for (int mask = 0; mask < (1 << (M)); mask++) {
        int curr =  (1 <<  30) - 1;
        int cnt = 0;
        for (int j = 0; j < M; j++) {
            if ((1 << j) & mask) {
                curr &= b[j];
                cnt++;
            }
        }
        ops[cnt].pb(curr);
    }
    vector<vector<int>> profit(N, vector<int>(M+1));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= M; j++) {
            profit[i][j] = a[i];
        }
        for (int j = 0; j <= M; j++) {
            for (int curr : ops[j]) {
                int op = a[i] & curr;
                // cout << "mask: " << mask << " cnt: " << cnt << " op: " << op << endl;
                profit[i][j] = min(profit[i][j], op);
            }
        }
        for (int j = M; j > 0; j--) {
            profit[i][j] = profit[i][j-1] - profit[i][j];
        }
        profit[i][0] = 0;
    }
    // for (int i = 0; i < N; i++) {
    //     cout << profit[i] << endl;
    // }

    ll ans = 0;
    for (int i =  0; i < N; i++) {
        ans += a[i];
    }

    vector<int> currMoves(N, 1);
    set<pii> moves;
    for (int i = 0; i < N; i++) {
        moves.insert(mp(-profit[i][1], i));
    }
    int cnt = 0;
    while (moves.size() && cnt < K) {
        pii best = *(moves.begin());
        moves.erase(moves.begin());
        cnt++;
        ans += best.first;
        currMoves[best.second]++;
        if (currMoves[best.second] <= M && profit[best.second][currMoves[best.second]] > 0) {
            moves.insert(mp(-profit[best.second][currMoves[best.second]], best.second));
        }
    }
    cout << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) {
        solve();
    }
}

