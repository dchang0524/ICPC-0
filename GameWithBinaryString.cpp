#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

template <class T> class SumSegmentTree { //0-indexed
    private:
      const T DEFAULT = 0;
      vector<T> segtree;
      int len;
  
    public:
      SumSegmentTree(int len) : len(len), segtree(len * 2, DEFAULT) {}
  
      void set(int ind, T val) {
          ind += len;
          segtree[ind] = val;
          for (; ind > 1; ind /= 2) {
              segtree[ind / 2] = segtree[ind] + segtree[ind ^ 1];
          }
      }
  
      T range_sum(int start, int end) { //[start, end)
          T sum = DEFAULT;
          for (start += len, end += len; start < end; start /= 2, end /= 2) {
              if (start % 2 == 1) { sum += segtree[start++]; }
              if (end % 2 == 1) { sum += segtree[--end]; }
          }
          return sum;
      }

      void increment(int ind, int val) {
        set(ind, range_sum(ind, ind + 1) + val);
      }
  };

void solve() {
    int N; cin >> N;
    string s; cin >> s;
    if (N == 1) {
        cout << 0 << endl;
        return;
    }
    vector<int> q(N+1);
    for (int i = 0; i < N; i++) {
        q[i+1] = q[i] + (s[i] == '1' ? 1 : 0);
    }
    for (int i = 0; i <= N; i++) {
        q[i] = i - 4*q[i] + 3*N + 2;
    }
    ll ans = 0;
    SumSegmentTree<int> segTree(4*N + 1 + 2 + 2);
    for (int i = 0; i <= N; i++) {
        ans += segTree.range_sum(0, q[i] - 1) + segTree.range_sum(q[i]+1, q[i]+2);
        segTree.increment(q[i], 1);
    }
    cout << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    solve();
}

