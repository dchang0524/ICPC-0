#include <bits/stdc++.h>
using namespace std;

#define mp make_pair
#define pb push_back

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

class DisjointSets {
  private:
    vector<int> parents;
    vector<int> sizes;
    //unordered_set<int> components;


  public:
    DisjointSets(int size, string s) : parents(size), sizes(size, 1) {
        sizes[0] = 0;
        for (int i = 1; i < size; i++) { 
            parents[i] = i; 
            if (s[i - 1] == '1') {
                sizes[i] = 0;
            }
            //components.insert(i);
        }
    }


    /** @return the "representative" node in x's component */
    int find(int x) { return parents[x] == x ? x : (parents[x] = find(parents[x])); }


    /** @return whether the merge changed connectivity */
    bool unite(int x, int y) {
        int x_root = find(x);
        int y_root = find(y);
        if (x_root == y_root) { return false; }


        if (sizes[x_root] < sizes[y_root]) { swap(x_root, y_root); }
        sizes[x_root] += sizes[y_root];
        parents[y_root] = x_root;
        //components.erase(y_root);
        return true;
    }


    /** @return whether x and y are in the same connected component */
    bool connected(int x, int y) { return find(x) == find(y); }

    int getSize(int c) {
        return sizes[find(c)];
    }

    ll pairsCnt(int c) {
        ll curr = getSize(c);
        if (curr == 0 || curr == 1) {
            return 0;
        }
        return curr * (curr-1) / 2;
    }

    void incrementSize(int c) {
        sizes[find(c)]++;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int N, M; cin >> N >> M;
    string s; cin >> s;

    DisjointSets G(N+1, s);
    vector<unordered_set<int>> frontEdges(N+1);
    vector<unordered_set<int>> backEdges(N+1);
    for (int i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        if (a < b) {
            backEdges[a].insert(b);
            frontEdges[b].insert(a);
        } else {
            backEdges[b].insert(a);
            frontEdges[a].insert(b);
        }

        if (s[a-1] == '1' && s[b-1] == '1') {
            G.unite(a, b);
        }
    }

    vector<ll> ans(N + 1);
    for (int i = N; i >= 1; i--) {
        ans[i-1] = ans[i];
        if (s[i-1] == '0') {
            for (int n : backEdges[i]) {
                if (!G.connected(i ,n)) {
                    ans[i-1] -= (G.pairsCnt(i) + G.pairsCnt(n));
                    G.unite(i, n);
                    ans[i-1] += G.pairsCnt(i);
                }
            }
            for (int n : frontEdges[i]) {
                if (s[n-1] == '1') {
                    if (!G.connected(i ,n)) {
                        ans[i-1] -= (G.pairsCnt(i) + G.pairsCnt(n));
                        G.unite(i, n);
                        ans[i-1] += G.pairsCnt(i);
                    }
                }
            }
        } else {
            ans[i-1] -= G.pairsCnt(i);
            G.incrementSize(i);
            ans[i-1] += G.pairsCnt(i);
        }
    }

    for (int i = 0; i < N; i++) {
        cout << ans[i] << endl;
    }
}