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
        int N; cin >> N;
        int total = 0;
        int days = 0;
        for (int i = 0; i < N; i++) {
            int curr; cin >> curr;
            total += curr;
            for (int j = 1; j * j <= total; j++) {
                if (j * j == total && j % 2 == 1) {
                    days++;
                    break;
                }
            }
        }
        cout << days << endl;
    }
}
