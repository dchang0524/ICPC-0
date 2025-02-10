#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

class DisjointSets {
  private:
    vector<int> parents;
    vector<int> sizes;


  public:
    DisjointSets(int size) : parents(size), sizes(size, 1) {
        for (int i = 0; i < size; i++) { parents[i] = i; }
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
        return true;
    }


    /** @return whether x and y are in the same connected component */
    bool connected(int x, int y) { return find(x) == find(y); }
};

int main() {
    // ios_base::sync_with_stdio(0);
    // cin.tie(0); cout.tie(0);
    int N, M; cin >> N >> M;
    vector<pii> extraEdges;
    vector<int> edgeID;
    DisjointSets dsu(N);
    for (int i = 0; i < M; i++) {
        int a, b; cin >> a >> b; a--; b--;
        if (dsu.connected(a, b)) {
            extraEdges.pb(mp(a, b));
            edgeID.pb(i+1);
        } else {
            dsu.unite(a, b);
        }
    }
    unordered_set<int> components;
    for (int i = 0; i < N; i++) {
        components.insert(dsu.find(i));
    }

    cout << (components.size() - 1) << endl;
    for (int i = 0; i < extraEdges.size(); i++) {
        auto edge = extraEdges[i];
        if (components.size() == 1) {
            break;
        }
        int cmpA = dsu.find(edge.first);
        auto it = components.begin();
        if (*it == cmpA) {
            it++;
        }
        int nodeB = *it;
        cout << edgeID[i] << " " << (edge.first + 1) << " " << (nodeB + 1) << endl;
        dsu.unite(edge.first, nodeB);
        components.erase(cmpA);
        components.erase(nodeB);
        components.insert(dsu.find(cmpA));
    }
}
