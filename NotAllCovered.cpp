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
    int N, M; cin >> N >> M;
    vector<int> dx(N+2);
    for (int i = 0; i < M; i++) {
        int L, R; cin >> L >> R;
        dx[L]++;
        dx[R+1]--;
    }
    vector<int> pref(N+2);
    for (int i = 1; i < dx.size(); i++) {
        pref[i] = pref[i-1] + dx[i];
    }
    int ans = M;
    for (int i = 1; i <= N; i++) {
        ans = min(pref[i], ans);
    }
    cout << ans << endl;
}
