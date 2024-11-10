#include <bits/stdc++.h>


using namespace std;
typedef long long ll;

//https://codeforces.com/contest/2029/problem/A
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        ll l, r, k;
        cin >> l >> r >> k;
        //each operation is removing x if {x, a_1 * x, ..., a_n * x} exists in S, where 1<a_1<a_2<...<a_n and n>=k-1
        //thus, the biggest x possible is floor(l/k), as if x > floor(l/k), kx > l, so we can't remove a set of size at least k
        //this means that the set of possible x are {l, l+1, ..., floor(l/k)}
        //we remove this set in order, and we obtain floor(l/k)-r+1 operations
        ll maxX = r/k;
        ll ans = max(0LL, maxX - l + 1);
        cout << ans << "\n";
    }
}
