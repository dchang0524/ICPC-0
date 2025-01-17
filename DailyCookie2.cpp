//https://atcoder.jp/contests/abc382/tasks/abc382_b
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
    int N, D;
    string S;
    cin >> N >> D >> S;
    vector<int> cookies(N);
    for (int i = 0; i < N; i++) {
        if (S[i] == '@') {
            cookies[i] = 1;
        }
    }
    for (int i = N-1; i >= 0; i--) {
        if (D && cookies[i]) {
            cookies[i] = 0;
            D--;
        }
    }
    for (int i = 0; i < N; i++) {
        if (cookies[i]) {
            cout << "@";
        }
        else {
            cout << ".";
        }
    }
    cout << endl;
}
