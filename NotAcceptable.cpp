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
    int A, B, C, D; cin >> A >> B >> C >> D;
    if (C < A) {
        cout << "Yes" << endl;
    } else if (C == A) {
        if (D < B) {
            cout << "Yes" << endl;
        }
         else {
            cout << "No" << endl;
         }
    } else {
        cout << "No" << endl;
    }
}
