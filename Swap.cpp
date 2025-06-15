#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

template <typename T> 
vector<T> ndvec(size_t size, T initial_value) {
    return vector<T>(size, initial_value);
}
template <typename T, typename... U> 
auto ndvec(size_t head, U &&...u){
    auto inner = ndvec<T>(u...);
    return vector<decltype(inner)>(head, inner);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    string s; cin >> s;
    int K; cin >> K;
    K = min(K, (int)(s.length() * s.length()+1)/2);

    map<char, int> id = {mp('K', 0), mp('E', 1), mp('Y', 2)};
    auto pref = ndvec<int>(s.length()+1, 3, 0);
    for (int i = 1; i <= (int)s.length(); i++) {
        for (int j = 0; j < 3; j++) {
            pref[i][j] = pref[i-1][j] + (id[s[i-1]] == j ? 1 : 0);
        }
    }

    vector<int> totals(3);
    int total_K = pref[s.length()][0];
    int total_E = pref[s.length()][1];
    int total_Y = pref[s.length()][2];
    totals[0] = total_K;
    totals[1] = total_E;
    totals[2] = total_Y;
    pref.pb(totals);

    auto cost = ndvec<int>(total_K+1, total_E+1, total_Y+1, 3, 0);
    for (int i = 0; i <= total_K; i++) {
        for (int j = 0; j <= total_E; j++) {
            for (int k = 0; k <= total_Y; k++) {
                vector<int> lastInd(3);
                for (int a = s.length(); a >= 0; a--) {
                    if (pref[a][0] == i) {
                        lastInd[0] = a;
                    }  
                    if (pref[a][1] == j) {
                        lastInd[1] = a;
                    }
                    if (pref[a][2] == k) {
                        lastInd[2] = a;
                    }
                }
                for (int l = 0; l < 3; l++) {
                    if (lastInd[l] == 0) {
                        cost[i][j][k][l] = -1; // impossible case
                        continue;
                    }
                    int c = lastInd[l];
                    //how many characters that are not l should be before c
                        //WLOG, l != 0. WLOG, consier how many 0's before c
                            //i 0's in the new string
                            //#0's that should exist before c = min(i, pref[c][0])
                            //#0's that were removed before c = max(0, pref[c][0] - min(i, pref[c][0]))
                    
                    vector<int> coord = {i, j, k};
                    int indCurr = lastInd[l] + max(0, pref[c][l] - min(coord[l], pref[c][l]))
                        - max(0, pref[c][0] - min(i, pref[c][0]))
                        - max(0, pref[c][1] - min(j, pref[c][1]))
                        - max(0, pref[c][2] - min(k, pref[c][2]));                    
                    cost[i][j][k][l] = i+j+k - indCurr;
                }
            }
        }
    }
    auto dp = ndvec<ll>(total_K+1, total_E+1, total_Y+1, K+1, (ll)0);
    for (int i = 0; i <= K; i++) {
        dp[0][0][0][i] = 1;
    }

    for (int i = 0; i <= total_K; i++) {
        for (int j = 0; j <= total_E; j++) {
            for (int k = 0; k <= total_Y; k++) {
                for (int x = 0; x <= K; x++) {
                    for (int l = 0; l < 3; l++) {
                        int ni = i - (l == 0);
                        int nj = j - (l == 1);
                        int nk = k - (l == 2);
                        if (ni < 0 || nj < 0 || nk < 0) continue; // out of bounds
                        int c = cost[i][j][k][l];
                        if (c != -1 && x >= c) {
                            dp[i][j][k][x] += dp[ni][nj][nk][x - c];
                        }
                    }
                }
            }
        }
    }
    cout << dp[total_K][total_E][total_Y][K] << endl;    
}
