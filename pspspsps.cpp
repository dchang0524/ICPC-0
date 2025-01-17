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
        int numP = 0;
        int numS = 0;
        int N; cin >> N;
        bool works = true;
        string str; cin >> str;
        for (int i = 0; i < N; i++) {
            if (str[i] == 'p') {
                numP++;
            }
            else if (str[i] == 's') {
                if (numP) {
                    works = false;
                }
                numS++;
            }
        }
        
        if (numS > 1 && numP > 1) {
            works = false;
        }
        else if (numS && numP) {
            if (!((str[0] == 's' && numS == 1) || (str[N-1] == 'p' && numP == 1))) {
                works = false;
            }
        }

        if (works) {
            cout << "YES" << endl;
        }
        else {
            cout << "NO" << endl;
        }

    }
    
}
