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
        int N, K; cin >> N >> K;
        string S; cin >> S;
        vector<int> penalty(N);
        for (int i = 0; i < N; i++) {
            cin >> penalty[i];
        }
        function<bool(int)> check = [&] (int maxPenalty) -> bool {
            vector<int> arr(N);
            vector<int> visited(N);
            for (int i = 0; i < N; i++) {
                if (penalty[i] <= maxPenalty) {
                    arr[i] = 0;
                } else {
                    if (S[i] == 'R') {
                        arr[i] = 2;
                    } else {
                        arr[i] = 1;
                    }
                }
            }
            int numComponents = 0;
            function<void(int, int)> dfs = [&] (int node, int c) -> void {
                if (visited[node]) {
                    return;
                }
                visited[node] = c;
                if (node+1 < N && arr[node+1] < 2) {
                    dfs(node+1, c);
                }
                if (node-1 >= 0 && arr[node-1] < 2) {
                    dfs(node-1, c);
                }
            };
            for (int i = 0; i < N; i++) {
                if (arr[i] == 1 && !visited[i]) {
                    numComponents++;
                    dfs(i, numComponents);
                }
            }
            if (numComponents <= K)
                return true;
            return false;
        };

        int lo = 0;
        int hi = 1000000000;
        hi++;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (check(mid)) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        cout << lo << endl;
    }
}
