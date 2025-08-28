#include <bits/stdc++.h>
using namespace std;
// #include "debugPrints.h"

#define pb push_back
#define mp make_pair
#define sz(x) (int)(x).size()
#define rep(i, a, b) for(int i = a; i < (b); ++i)

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef unsigned long long ull;

vi order(vi &A) {
    // cout << "Ordering: " << A << "\n";
    if (sz(A) == 2) {
        return {1, 2};
    }
    vector<pii> v;
    map<int, int> ind; //the index of the element in the simple array
    for (int i = 0; i < sz(A)/2; i++) {
        if (A[2*i] > A[2*i+1]) {
            v.pb({A[2*i+1], A[2*i]});
        }
        else {
            v.pb({A[2*i], A[2*i+1]});
        }
        ind[min(A[2*i], A[2*i+1])] = i;
    }
    // cout << ind << endl;
    vector<int> simple(sz(v));
    int i = 1;
    map<int, pii> val;
    for (auto &p : ind) {
        simple[p.second] = i;
        val[i] = {min(A[2*p.second], A[2*p.second+1]), max(A[2*p.second], A[2*p.second + 1])};
        i++;
    }
    // cout << "Simple: " << simple << "\n";
    vector<int> ansSimple = order(simple);
    vector<pii> ansPairs;
    for (int i = 0; i < sz(simple); i++) {
        ansPairs.pb(val[ansSimple[i]]);
    }
    vector<int> ans;
    for (int i = 0; i < sz(ansPairs); i++) {
        ans.pb(ansPairs[i].first);
        ans.pb(ansPairs[i].second);
    }
    return ans;
}


void solve() {
    int N; cin >> N;
    vi A(pow(2, N));
    for (int i = 0; i < pow(2, N); i++) {
        cin >> A[i];
    }
    // cout << "Initial: " << A << "\n";

    vi ans = order(A);
    for (int i = 0; i < pow(2, N); i++) {
        cout << ans[i] << " ";
    }
    cout << "\n";
}

int main() {
    // ios_base::sync_with_stdio(0);
    // cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) {
        solve();
    }
}

