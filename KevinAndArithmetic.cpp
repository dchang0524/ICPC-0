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
        int numOdd = 0;
        int numEven = 0;
        for (int i = 0; i < N; i++) {
            int a; cin >> a;
            if (a % 2 == 0) {
                numEven++;
            } else {
                numOdd++;
            }
        }

        if (numEven) {
            cout << (1 + numOdd) << endl;
        } else {
            cout << max(numOdd - 1, 0) << endl;
        }
    }
}
