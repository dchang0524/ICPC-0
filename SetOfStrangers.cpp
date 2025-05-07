#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) {
        int N, M; cin >> N >> M;
        vector<vector<int>> color(N, vector<int>(M));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                cin >> color[i][j];
            }
        }

        unordered_map<int, int> check; //0 = all connected, 1 = needs 2 groups
        vector<int> dx = {1, -1, 0, 0};
        vector<int> dy = {0, 0, 1, -1};
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                for (int k = 0; k < 4; k++) {
                    int X = i + dx[k];
                    int Y = j + dy[k];
                    // cout << X << " " << Y << endl;
                    if (X >= 0 && X < N && Y >= 0 && Y < M) {
                        // cout << "checking current coord" << endl;
                        if (color[X][Y] == color[i][j]) {
                            check[color[i][j]] = 1; 
                        }
                    }
                }
                int dum = check[color[i][j]];
            }
        }

        int ans = 0;
        int cnt2 = 0;
        for (const auto &c : check) {
            if (c.second == 0) {
                ans++;
            } else {
                ans += 2;
                cnt2++;
            }
        }
        ans--;
        if (cnt2 > 0) {
            ans--;
        }
        cout << ans << endl;
    }
}
