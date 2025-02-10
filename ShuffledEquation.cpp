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
    int a, b, c; cin >> a >> b >> c;
    if (a*b == c || a*c == b || b*c == a) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}
