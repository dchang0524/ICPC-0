#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

// Overload the << operator for vector
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
   for (const auto& elem : v) {
       os << elem << " ";
   }
   return os;
}

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

template <class T> class SumSegmentTree { //0-indexed
    private:
      const T DEFAULT = 0;
      int len;
  
    public:
      vector<T> segtree;
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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N; cin >> N;
    vector<pii> edgeQ;
    vector<unordered_set<int>> edges(N+1);
    for (int i = 0; i < N-1; i++) {
        int a, b; cin >> a >> b;
        edgeQ.pb(mp(a, b));
        edges[a].insert(b);
        edges[b].insert(a);
    }
    vector<int> a;
    vector<int> sizes(N+1);
    a.pb(0);
    function<void(int, int)> dfs = [&](int node, int parent) {
        a.pb(node);
        for (int adj : edges[node]) {
            //don't need visited for tree
            if (adj != parent) {
                dfs(adj, node);
                sizes[node] += sizes[adj];
            }
        }
        sizes[node]++;
        // cout << "node: " << node << endl;
        // cout << sizes << endl;
    };
    dfs(1, -1);
    unordered_map<int, int> index; //index[i] gives the index of i in the segtree
    for (int i = 1; i <= N; i++) {
        index[a[i]] = i;
    }
    // cout << a << endl;
    // cout << sizes << endl;
    // cout << index << endl;

    SumSegmentTree<int> segTree(N+1);
    for (int i = 1; i <= N; i++) {
        segTree.increment(i, 1);
    }
    
    int Q; cin >> Q;
    for (int i = 0; i < Q; i++) {
        // cout << "i: " << i << endl;
        int type; cin >> type;
        if (type == 1) {
            int a, b; cin >> a >> b;
            segTree.increment(index[a], b);
        } else {
            int e; cin >> e; e--;
            int a = edgeQ[e].first; int b = edgeQ[e].second;
            // cout << "Delete edge " << a << " " << b << endl;
            int total = segTree.range_sum(1, N + 1);
            int sub = 0;
            if (index[a] < index[b]) {
                sub = segTree.range_sum(index[b], index[b] + sizes[b]);
            } else {
                sub = segTree.range_sum(index[a], index[a] + sizes[a]);
            }
            int sub1 = total - sub;
            cout << abs(sub1 - sub) << endl;
        }
        // for (int i = 0; i <= N; i++) {
        //     cout << segTree.range_sum(i, i+1) << " ";
        // }
        // cout << endl;
    }
}
