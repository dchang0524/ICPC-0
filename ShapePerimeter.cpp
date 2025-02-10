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
        int x, y; cin >> x >> y;
        int dx = M;
        int dy = M;
        for (int i = 0; i < N-1; i++) {
            int ddx, ddy; cin >> ddx >> ddy;
            dx += ddx;
            dy += ddy;
        }
        cout << (2*dx + 2*dy) << endl;
    }
}
