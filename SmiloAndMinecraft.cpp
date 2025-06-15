#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define sz(x) (int)(x).size()
#define rep(i, a, b) for(int i = a; i < (b); ++i)

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef unsigned long long ull;

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
    // cout << "N: " << N << ", M: " << M << ", K: " << K << endl;
    vector<string> grid(N);
    int total = 0;
    for (int i = 0; i < N; i++) {
        cin >> grid[i];
        // cout << grid[i] << endl;
        for (int j = 0; j < M; j++) {
            if (grid[i][j] == 'g') {
                total++;
            }
        }
    }
    //find the 2K x 2K square with least g's using 2D prefix sum, allowing square to go out of bounds, as long as center is within bounds
    vector<vector<int>> prefix(N + 1, vector<int>(M + 1, 0));
    prefix[0][0] =  (grid[0][0] == 'g');
    for (int i = 1; i < N; i++) {
        prefix[i][0] = prefix[i - 1][0] + (grid[i][0] == 'g');
    }
    for (int j = 1; j < M; j++) {
        prefix[0][j] = prefix[0][j - 1] + (grid[0][j] == 'g');
    }
    for (int i = 1; i < N; i++) {
        for (int j = 1; j < M; j++) {
            prefix[i][j] = prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1] + (grid[i ][j] == 'g');
        }
    }

    // for (int i = 0; i < N; i++) {
    //     for (int j = 0; j < M; j++) {
    //         cout << prefix[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    int min_g = total;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (grid[i][j] != '.') {
                continue;
            }
            int curr = prefix[min(i+K-1, N-1)][min(j+K-1, M-1)];
            if (i - K >= 0) {
                curr -= prefix[i-K][min(j+K-1, M-1)];
            }
            if (j - K >= 0) {
                curr -= prefix[min(i+K-1, N-1)][j-K];
            }
            if (i - K >= 0 && j - K >= 0) {
                curr += prefix[i-K][j-K];
            }
            // cout << "Current square at (" << i << ", " << j << ") has " << curr << " g's." << endl;
            min_g = min(min_g, curr);
        }
    }
    cout << total - min_g << endl;    
    
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) {
        solve();
    }
}

