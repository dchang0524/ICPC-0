//https://codeforces.com/problemset/problem/2050/G
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

vector<vector<int>> neighbors;
vector<vector<int>> child;
vector<int> dp;

int N;


void tdfs(int a, int p) {
    for (int c : neighbors[a]) {
        if (c != p) {
            child[a].pb(c);
            tdfs(c, a);
        }
    }
}

void tdfs(int a) {
    vector<vector<int>> temp(N+1);
    child = temp;
    tdfs(a, -1);
}

void tdp(int a) {
    
    for (int c : child[a]) {
        tdp(c);
    }
    int max1 = 0;
    for (int c : child[a]) {
        max1 = max(dp[c]-1, max1);
    }
    dp[a] = max1 + child[a].size();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) {
        cin >> N;
        vector<vector<int>> temp(N+1);
        neighbors = temp;
        for (int i = 0; i < N - 1; i++) {
            int a, b; cin >> a >> b;
            neighbors[a].pb(b);
            neighbors[b].pb(a);
        }
        tdfs(1);
        vector<int> temp1(N+1);
        dp = temp1;
        tdp(1);
        int ans = 1;
        for (int i = 1; i < N+1; i++) {
            int max1 = 0;
            int max2 = 0;
            for (int c : child[i]) {
                if (dp[c]-1 > max1) {
                    max2 = max1;
                    max1 = dp[c]-1;
                }
                else if (dp[c]-1 > max2) {
                    max2 = dp[c]-1;
                }
            }
            int curr = max1 + max2 + (int)child[i].size() + (i == 1 ? 0 : 1);
            ans = max(ans, curr);
        }
        cout << ans << endl;
    }
}
