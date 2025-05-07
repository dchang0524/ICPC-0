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
        int N, X; cin >> N >> X;
        ll K; cin >> K;
        string s; cin >> s;
        vector<int> pref(N);
        for (int i = 0; i < N; i++) {
            if (s[i] == 'L') {
                pref[i] = -1;
            } else {
                pref[i] = 1;
            }
        }
        ll ind0 = K+1;
        ll indX = K+1;
        for (int i = 1; i < N; i++) {
            pref[i] += pref[i-1];
        }
        for (int i = 0; i < N; i++) {
            if (pref[i] == 0 && ind0 == K+1) {
                ind0 = i;
            }
            if (pref[i] == -X && indX == K+1) {
                indX = i;
            }
        }

        ll ans = 0;
        if (indX + 1 <= K) {
            ans++;
            K -= indX + 1;
            ans += K/(ind0+1);
        }
        cout << ans << endl;
        
    }
}
