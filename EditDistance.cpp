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
    string s, t; cin >> s >> t;
    int N = s.length(); int M = t.length();
    vector<vector<int>> dp(N+1, vector<int>(M+1));
    for (int i = 1; i <= N; i++) {
        dp[i][0] = i;
    }
    for (int i = 1; i <= M; i++) {
        dp[0][i] = i;
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            int cost = s[i-1] == t[j-1] ? 0 : 1;
            dp[i][j] = min(dp[i-1][j-1] + cost, min(dp[i-1][j], dp[i][j-1]) + 1);
        }
    }
    cout << dp[N][M] << endl;
}
