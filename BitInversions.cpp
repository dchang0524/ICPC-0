#include <bits/stdc++.h>
using namespace std;
//#include "debugPrints.h"

#define pb push_back
#define mp make_pair
#define sz(x) (int)(x).size()
#define rep(x) for (int i = 0; i < (x); ++i)
#define FOR(i, a, b) for(int i = a; i < (b); ++i)
#define FOR1(i, a, b) for(int i = a; i <= (b); ++i)

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef unsigned long long ull;
template <typename T> 
vector<T> ndvec(size_t size, T initial_value) {
    return vector<T>(size, initial_value);
}
template <typename T, typename... U> 
auto ndvec(size_t head, U &&...u){
    auto inner = ndvec<T>(u...);
    return vector<decltype(inner)>(head, inner);
} ////example: auto grid = ndvec<char>(n + 1, m + 1, '_');

struct node {
    int pref;
    int suff;
    int seg;
    int len;
};
node operator+(const node &a, const node &b) {
	return {a.pref == a.len ? a.len + b.pref : a.pref, b.suff == b.len ? b.len + a.suff : b.suff,
	        max(max(a.seg, b.seg), a.suff + b.pref), a.len + b.len};
};

template <class T> class SegmentTree {
  private:
	  const T DEFAULT = {0, 0, 0, 0}; //!!!! Make sure it matches your usage

  	int len;
  	vector<T> segtree;

  T combine(const T &a, const T &b) { 
      return a+b; 
  }

	void build(const vector<T> &arr, int at, int at_left, int at_right) {
	  	if (at_left == at_right) {
		    segtree[at] = arr[at_left];
			return;
		}
		int mid = (at_left + at_right) / 2;
	    build(arr, 2 * at, at_left, mid);
	    build(arr, 2 * at + 1, mid + 1, at_right);
	    segtree[at] = combine(segtree[2 * at], segtree[2 * at + 1]);
	}

	void set(int ind, T val, int at, int at_left, int at_right) {
		if (at_left == at_right) {
			segtree[at] = val;
			return;
		}
		int mid = (at_left + at_right) / 2;
		if (ind <= mid) {
			set(ind, val, 2 * at, at_left, mid);
		} else {
			set(ind, val, 2 * at + 1, mid + 1, at_right);
		}
		segtree[at] = combine(segtree[2 * at], segtree[2 * at + 1]);
	}

	T range(int start, int end, int at, int at_left, int at_right) {
		if (at_right < start || end < at_left) { return DEFAULT; }
		if (start <= at_left && at_right <= end) { return segtree[at]; }
		int mid = (at_left + at_right) / 2;
		T left_res = range(start, end, 2 * at, at_left, mid);
		T right_res = range(start, end, 2 * at + 1, mid + 1, at_right);
		return combine(left_res, right_res);
	}

	int walk(int at, int at_left, int at_right, int max_val, int pref_res) {
		if (at_left == at_right) { return at_left; }
		int mid = (at_left + at_right) / 2;
		int sum_left = combine(pref_res, segtree[2 * at]);
		if (sum_left >= max_val) {
			return walk(2 * at, at_left, mid, max_val, pref_res);
		}
		return walk(2 * at + 1, mid + 1, at_right, max_val, sum_left);
	}

  public:
    //0-indexed, range() is inclusive on both ends
	SegmentTree(int len) : len(len) { segtree = vector<T>(len * 4, DEFAULT); };

	SegmentTree(const vector<T> &arr) : len(arr.size()) {
		segtree = vector<T>(len * 4, DEFAULT);
		build(arr, 1, 0, len - 1);
	}

	void set(int ind, T val) { set(ind, val, 1, 0, len - 1); }

	T range(int start, int end) { return range(start, end, 1, 0, len - 1); }

    void increment(int ind, T val) { set(ind, range(ind, ind) + val);}

	/** @return first i such that range(0, i) >= val */
	int walk(int val) { 
        if (segtree[1] < val)
            return -1;
        return walk(1, 0, len - 1, val, 0); 
    }
};

void solve() {
    string s; cin >> s;
    int N = sz(s);
    int M; cin >> M;
    SegmentTree<node> zeros(N);
    SegmentTree<node> ones(N);
    
    node val0 = {0, 0, 0, 1};
    node val1 = {1, 1, 1, 1};
    FOR (i, 0, N) {
        if (s[i] == '0') {
            zeros.set(i, val1);
            ones.set(i, val0);
        } else {
            zeros.set(i, val0);
            ones.set(i, val1);
        }
    }

    rep(M) {
        int q; cin >> q; q--;
        s[q] = s[q]^1;
        if (s[q] == '0') {
            zeros.set(q, val1);
            ones.set(q, val0);
        } else {
            zeros.set(q, val0);
            ones.set(q, val1);
        }
        cout << max(zeros.range(0, N-1).seg, ones.range(0, N-1).seg) << " ";
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    solve();
}

