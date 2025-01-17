#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

// Overload the << operator for vector
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
   for (const auto& elem : v) {
       os << elem << " ";
   }
   return os;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) {
        int N, M; ll K; cin >> N >> M >> K;
        vector<vector<ll>> cost(N, vector<ll>(M));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                cin >> cost[i][j];
            }
        }
        vector<ll> dp(M); //dp[i][j] = min cost to reach (i, j)
        vector<vector<ll>> dp1(M, vector<ll>(M)); //dp1[i][j][k] = min cost to reach (i,j) while shifting row i by k
        //dp1[i][j][k] = min(dp1[i][j-1][k] + cost[i][(j+k) % M], dp[i-1][j] + cost[i][(j+k) % M])
        for (int i = 0; i < N; i++) {
            vector<vector<ll>> ndp1(M, vector<ll>(M));
            for (int j = 0; j < M; j++) {
                for (int k = 0; k < M; k++) {
                    if (j > 0) { //you can come from previous column
                        if (i > 0) { //you can come from previous row too
                            ndp1[j][k] = min(ndp1[j-1][k] + cost[i][(j+k) % M], dp[j] + cost[i][(j+k) % M] + K*k);
                        }
                        else { //you can only come from previous column
                            ndp1[j][k] = ndp1[j-1][k] + cost[i][(j+k) % M];
                        }
                    }
                    else { //you can only come from previous row
                        //dp[j] is 0 when i == 0
                        ndp1[j][k] = dp[j] + cost[i][(j+k) % M] + K*k;
                    }
                }
            }
            dp1 = ndp1;
            for (int j = 0; j < M; j++) {
                dp[j] = dp1[j][0];
                for (int k = 1; k < M; k++) {
                    dp[j] = min(dp[j], dp1[j][k]);
                }
            }
        }
        cout << dp[M-1] << endl;
    }
}
