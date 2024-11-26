//https://codeforces.com/contest/2039/problem/C1
//Let ^ denote xor, and pow(a,b) denote a to the power of b
//We have x^y = div_x or x^y = div_y where div_i denotes a divisor of i
    //x is fixed, but 1 <= y <= M
//If x^y = div_x
    //y = x^div_x
    //Iterate through every div_x in O(sqrt(x)) time
//If x^y = div_y
    //x^div_y = y
    //If div_y <= x
        //Iterate for div_y = 1 to div_y <= x
    //If div_y > x
        //Let x = c_{k-1} * pow(2, k-1) + c_2 * pow((2, k-1) + ... + c_0 * pow(2, 0)
        //Let div_y = a*pow(2,k) + b where b < pow(2,k) and a >= 1
        //x^div_y = y, div_y | y and div_y <= y
            //y = a*pow(2, k) + b^x
            //div_y = a*pow(2,k) + b
            //Thus 2*div_y > y, so we must have div_y = y
            //a*pow(2,k) + b^x = a*pow(2,k) + b
                //b^x = b, so x= 0. However, we are given x != 0. Thus, we know div_y can't be greater than x
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

ll solve(ll x, ll M) {
    unordered_set<ll> Ys;
    //if x^y = div_x
    //can simulate in O(sqrt(x)), but not necessary
    for (ll i = 1; i <= x; i++) {
        if (x % i != 0) {
            continue;
        }
        ll y = x^i;
        if (y <= M)
            Ys.insert(y);
    }
    //if d_y <= x
    for (ll i = 1; i <= x; i++) {
        ll y = x^i;
        if (y <= M && y % i == 0) {
            Ys.insert(y);
        }
    }
    Ys.erase(0);
    return Ys.size();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        ll X, M;
        cin >> X >> M;
        cout << solve(X, M) << endl;
    }
}
