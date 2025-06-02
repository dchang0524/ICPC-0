#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;


// Overload operator<< for unordered_map
template <typename K, typename V>
ostream& operator<<(ostream& os, const unordered_map<K, V>& umap) {
   os << "{";
   bool first = true;
   for (const auto& kv : umap) {
       if (!first) os << ", ";
       os << "[" << kv.first << ": " << kv.second << "]";
       first = false;
   }
   os << "}";
   return os;
}

void solve() {
    int N; cin >> N;
    vector<int> nums(N);
    int g = 0;
    for (int i = 0; i < N; i++) {
        cin >> nums[i];
        g = gcd(g, nums[i]);
    }
    int sub = 0;
    for (int i = 0; i < N; i++) {
        nums[i] /= g;
        if (nums[i] == 1) {
            sub++;
        }
    }
    vector<int> minSet(5001);
    for (int i = 0; i < N; i++) {
        int c = nums[i];
        minSet[c] = 1;
        for (int k = 5000; k >= 1; k--) {
            if (minSet[k] > 0) {
                int nGCD = __gcd(c, k);
                if (minSet[nGCD] > 0) {
                    minSet[nGCD] = min(minSet[nGCD], minSet[k] + 1);
                } else {
                    minSet[nGCD] = minSet[k] + 1;
                }
            }
        }
    }
    // cout << minSet << endl;
    cout << minSet[1] - 1 + N - (max(1, sub)) << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) {
        solve();
    }
}

