//Let ^ denote xor
//Note xor is commutative and associative, so we can order the xor operations in any way
    //casework for one bit on 2-3 operations, and then apply induction
//x^x = 0, x^0 = x
//We get that xor[l,r] = 0 where if there are a pair of each integers from l to r 
    //if xor[l, r] != 0, it must contain at least one of a,b, or c
    //assume a^b^c != 0
        //Then any nonzero segment contains a,b, or c.
        //We continously check the first and second half of a segment
            //We query only the first half, and we can use xor to calculate the second half
                //xor[l,r] = xor[l, a]^xor[a+1, r]
                //xor[l,r]^xor[a+1,r] = xor[l,a]^xor[a+1, r]^xor[a+1, r] = xor[l,a]^0 = xor[l,a]
            //If one is zero, discard that segment
                //Apply the algorithm on the nonzero component
                    //If it has size 1, the number on the segment is one of a, b, or c
            //If a segment containing a,b,c divided into two nonzero segments
                //apply this algorithm again for both segments
            //If a segment containing two (or one, since we wouldn't know which) of a,b,c divided into two nonzero segments
                //the xor values of the two segments correspond to two of a,b, or c (which means the segment contained two numbers)
    //in the case where a^b^c = 0, WLOG, let a<b<c.
        //Then a<2^k<=b<c for some integer k
            //Check the highest nonzero bits of b and c
            //We can separate [1,N] into [1, 2-1], [2, pow(2,2)-1], ..., [pow(2, k), min(N, pow(2,k+1)-1)]
                //a will be a segment, and b and c will be in a segment that is not the segment a is in
                //We can apply the algorithm for the case where xor[l,r] != 0 on the two segments with nonzero values
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

ll query(ll l, ll r) {
    cout << "xor " << l << " " << r << "\n";
    cout.flush();
    ll q;
    cin >> q;
    if (q == -1)
        exit(0);
    return q;
}

void answer(ll a, ll b, ll c) {
    cout << "ans " << a << " " << b << " " << c << "\n";
    cout.flush();
}

vector<ll> searchAns(ll l, ll r, ll prevVal) { //if range contains 1 or 2 answers
    if (l == r) {
        // ll val = query(l, r);
        vector<ll> ans;
        // if (val != 0) {
        //     ans.pb(val);
        // }
        ans.pb(l);
        return ans;
    }
    ll mid = l + (r-l)/ 2;
    ll val1 = query(l, mid);
    ll val2 = prevVal^val1; //can't be 0, as otherwise val1 == prevVal

    if (val1 == 0) {
        return searchAns(mid+1, r, prevVal);
    }
    if (val2 == 0) {
        return searchAns(l, mid, prevVal);
    }

    vector<ll> ans;
    ans.pb(val1);
    ans.pb(val2);
    return ans;
}

void solve(ll N) {
    ll total = query(1, N);
    //Case: a^b^c = 0
    if (total == 0) {
        //a + b = c
        vector<pll> segments;
        ll left = 1;
        while (left <= N) {
            segments.pb(mp(left, min(2*left-1, N)));
            left = 2*left;
        }
        vector<pll> ansSegments;
        vector<ll> vals;
        for (pll seg : segments) {
            ull val = query(seg.first, seg.second);
            if (val != 0) {
                ansSegments.pb(seg);
                vals.pb(val);
                if (ansSegments.size() == 2) {
                    break; //there can only be two segments with nonzero xor value
                }
            }
        }
        
        //there must be two segments
        ll c = vals[0];
        if (ansSegments[0].first <= c && c <= ansSegments[0].second) {
            vector<ll> ans = searchAns(ansSegments[1].first, ansSegments[1].second, c);
            answer(vals[0], ans[0], ans[1]);
        }
        else {
            vector<ll> ans = searchAns(ansSegments[0].first, ansSegments[0].second, c);
            answer(vals[0], ans[0], ans[1]);
        }
    }
    //Case: a^b^c != 0
    else {
        ll l = 1;
        ll r = N;
        while (l <= r) {
            ll mid = l + (r - l) / 2;
            ll val1= query(l, mid);
            ll val2 = total^val1;
            if (val1 == 0) {
                l = mid+1;
            }
            else if (val2 == 0) {
                r = mid;
            }
            else {
                vector<ll> ans1 = searchAns(l, mid, val1);
                vector<ll> ans2 = searchAns(mid+1, r, val2);
                vector<ll> ans3;
                for (ll i : ans1) {
                    ans3.pb(i);
                }
                for (ll i : ans2) {
                    ans3.pb(i);
                }
                answer(ans3[0], ans3[1], ans3[2]);
                break;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    while (T--) {
        ll N;
        cin >> N;
        solve(N);
    }
}
