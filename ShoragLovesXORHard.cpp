//https://codeforces.com/contest/2039/problem/C2
//Let ^ denote xor, and pow(a,b) denote a to the power of b
//Let mult_i denote a multiple of i, and div_i denote a divisor of i
//Let k be the smallest integer such that pow(2,k) > x
//x is fixed, and y is in the range 1 <= y <= M
//x^y = mult_x or x^y = mult_y
//From the easy version of the problem, we have if x^y = mult_y, y <= x
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
    //Thus, we can find all such numbers in O(x). Later, we show if x^y = mult_x, y >= pow(2,k), so there will be no overcount as y <= x if x^y = mult_x.
//Consider the case where x^y = mult_x
    //if y < pow(2,k), we can find all y where x^y = mult_x in O(x) time
        //but also we don't have simulate this case, because it is impossible.
            //First, from the lemma that if x^y = mult_y then y <= x, we have x <= y if x^y = mult_x
            //If x <= y < pow(2,k), x^y < x if you compare the highest bits, so x^y can't be a multiple of x 
    //if y >= pow(2,k), let y = a*pow(2,k) + b where 1 <= a <= floor(M/pow(2,k)) and 0 <= b < pow(2,k)
        //Note the range for a changes for each b, as pow(2,k)*a + b <= M
        //Then b^x + a*pow(2,k) = 0 mod x
            //a = -(b^x) / pow(2,k) mod x
                //we also have to account for the case where pow(2,k) isn't relatively coprime to x
            //We have to find the number of a's that satisfy the above modulos and the range for a
                //This can be done in O(log M) for each b
    //The official solution uses the fact that x^y <= x+y and if x<=y, x^y >= y-x to bound x^y and makes x^y a multiple of x
        //this is much more easy to implement and also faster
#include <bits/stdc++.h>
using namespace std;
 
#define pb push_back
#define mp make_pair
 
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

ll gcd(ll a, ll b) {
   return b == 0 ? a : gcd(b, a % b);
}

ll extended_gcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll g = extended_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

ll mod_inverse(ll a, ll m) {
    ll x, y;
    ll g = extended_gcd(a, m, x, y);
    if (g != 1) return -1; // Inverse doesn't exist
    x = (x % m + m) % m;
    return x;
}


ll solve(ll x, ll M) {
    ll ans = 0;
    //x^y = mult_y -> y <= x
    for (int i = 1; i <= x; i++) {
        if (i > M) {
            break;
        }
        ll mult = i^x;
        if (mult % i == 0) {
            ans++;
            //cout << "y: " << i << endl;
        }
    }
 
    //x^y = mult_x
 
    //pow(2,k-1) <= x < pow(2,k)
    int k = 1;
    ll maxB = 1;
    while (maxB*2 <= x) {
        maxB *= 2;
        k++;
    }
    maxB = maxB*2 - 1;
    ll pow2k = 1LL << k;
    ll g = gcd(pow2k, x);
    ll mod = x / g;
    ll mPow = (pow2k / g) % mod;
    // cout << mPow << endl;
    if (mod != 1) {
        mPow = mod_inverse(mPow, mod);
    }
    // cout << "mod: "<< mod << " mPow: " << mPow << endl;
    for (int i = 0; i <= maxB; i++) {
        // cout << "ans: "<< ans << endl;
        // cout << "i: " << i << endl;

        // cout << "i^x: " << (i^x) << endl;
        ll maxA = (M-i)/(maxB+1);
        // cout << "maxA: " << maxA << endl;
        if (maxA <= 0) {
            continue;
        }
        ll s = (i^x);
        if (s % g  != 0) {
            continue;
        } 
        s /= g;
        s %= mod;
        // cout << "s: " << s << endl;
        if (mPow == 0) {
            if (s == 0) {
                ans += maxA;
            }
            continue;
        }
        ll targetMod = (((-s + mod) % mod) * mPow) % mod;
        if (targetMod == 0) {
            targetMod += mod;
        }
        ll numRanges = maxA/mod;
        if (targetMod <= maxA % mod) {
            numRanges += 1;
        }
        ans += numRanges;
    }
    return ans;
}
 
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        ll x, M;
        cin >> x >> M;
        cout << solve(x, M) << endl;
    }
}