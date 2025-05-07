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
        string s; cin >> s;
        int N = s.length();
        vector<vector<int>> cnt(N+1, vector<int>(26));
        for (int i = 1; i <= N; i++) {
            for (int j = 0; j < 26; j++) {
                cnt[i][j] = cnt[i-1][j];
            }
            cnt[i][s[i-1] - 'a']++;
        }

        int startL = 1;
        int startR = N;
        while (startL < startR) {
            if (s[startL-1] == s[startR-1]) {
                startL++;
                startR--;
            } else {
                break;
            }
        }
        int endL = N/2;
        int endR = N/2+1;
        while (startL < endL) {
            if (s[endL-1] == s[endR-1]) {
                endL--;
                endR++;
            } else {
                break;
            }
        }

        if (startL > startR) {
            cout << 0 << endl;
            continue;
        }

        bool works = true;
        for (int i = 0; i < 26; i++) {
            if (cnt[endL][i] - cnt[startL-1][i] != cnt[startR][i] - cnt[endR-1][i]) {
                works = false;
            }
        }
        if (works) {
            cout << (endL - startL) + 1 << endl;
            continue;
        }

        int ans = N;
        //can replace this prefix/suffix search with binary search, instead of iterating through all indexes
        //segment on left
        int s1 = startL;
        int s2 = endL;
        while (s2 <= startR) {
            works = true;
            for (int i = 0; i < 26; i++) {
                if (cnt[s2][i] - cnt[s1-1][i] < cnt[startR][i] - cnt[s2][i]) {
                    works = false;
                    break;
                }
            }
            if (works) {
                ans = min(ans, s2 - s1 + 1);
                break;
            }
            s2++;
        }
        //segment on right
        s1 = startR;
        s2 = endR;
        while (s2 >= startL) {
            works = true;
            for (int i = 0; i < 26; i++) {
                if (cnt[s1][i] - cnt[s2-1][i] < cnt[s2-1][i] - cnt[startL-1][i]) {
                    works = false;
                    break;
                }
            }
            if (works) {
                ans = min(ans, s1 - s2 + 1);
                break;
            }
            s2--;
        }
        cout << ans << endl;
    }
}
