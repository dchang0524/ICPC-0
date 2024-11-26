//https://codeforces.com/contest/2039/problem/A
//a_1 = 0 mod 1
    //Then a_2 = 1 mod 2, a_3 = 2 mod 3, ..., a_N = N-1 mod N
//Since 1 <= a_1 < a_2 < ... < a_N <= 2*N
    //Let a_i = i-1 + i = 2i-1
    //Then all conditions are satisfied
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
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        for (int i = 1; i <= N; i++) {
            cout << 2*i - 1 << " ";
        }
        cout << endl;
    }
}
