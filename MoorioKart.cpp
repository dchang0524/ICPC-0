#include <bits/stdc++.h>


using namespace std;
typedef long long ll;

const ll MOD = 1e9 + 7;
const ll TWO_MOD_INV = 500000004;


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

ll mult(ll x, ll y, ll m) {
    //computes x*y mod m
    return (x*y)%m;
}
ll add(ll x, ll y, ll m) {
    //computes x+y mod m
    return (x+y)%m;
}
ll sub(ll x, ll y, ll m) {
    //computes x-y mod m
    return (x-y+m)%m;
}
ll div(ll x, ll y, ll m) {
    //computes x/y mod m
    return mult(x, inv(y, m), m);
}
ll exp(ll x, ll n, ll m) {
   //computes x^n mod m
   assert(n >= 0);
   x %= m;  // note: m * m must be less than 2^63 to avoid ll overflow
   ll res = 1;
   while (n > 0) {
       if (n % 2 == 1) { res = res * x % m; }
       x = x * x % m;
       n /= 2;
   }
   return res;
}

ll inv(ll x, ll m) {
   //finds x^-1 mod m
   //requires m to be prime and x to be relatively coprime to m
   return exp(x, m-2, m);
}

int main() {
    
    //divide the graph into connected components
    //since each component is a tree, define dist[a][b] as the unique distance from a to b
    //let K be the number of components, and c_1, c_2, ..., c_k the number of nodes in each component
    //We choose a pair from each component, and there are (K-1)!*2^{K-1} ways to add roads between these pairs
    //Thus, in the total sum of paths, each pair p in connected component i is counted
        // (K-1)!*2^{K-1} * (c_i - 1) * mult_{1<=j<=K && j != i}({c_i}choose{2})
    //Also, there are K roads of length X for each configuration, so we add
        //K*X*(K-1)!*2^{K-1} * mult_{1<=j<=K}({c_i}choose{2})
    //Then, to count the number of paths with length >= Y, we subtract the sum of paths with length < Y
        //we do this by using knapsack DP
            //also, ignore "coins" where dist[a][b]>=Y-2*K*X
                //this limits time complexity from O(N^2Y) to O(N*Y^{3/2})
    

    freopen("mooriokart.in", "r", stdin);
    int N, M, X, Y;
    cin >> N >> M >> X >> Y;
    vector<vector<pair<int, int>>> edges(N);
    for (int i = 0; i<M; i++) {
        int a, b, d;
        cin >> a >> b >> d;
        a--;
        b--;
        edges[a].push_back(make_pair(b, d));
        edges[b].push_back(make_pair(a, d));
    }
    //find connected components
    //while a DFS/BFS is more efficient, I will just use DSU since I'm lazy and there is not a big difference in time complexity
    DisjointSets dsu(N);
    for (int i = 0; i<N; i++) {
        for (int j = 0; j<edges[i].size(); i++) {
            dsu.unite(i, edges[i][j].first);
        }
    }
    int numComponents = 0;
    vector<int> components(N, -1);
    for (int i = 0; i<N; i++) {
        if (components[i] != -1) {
            numComponents++;
            components[i] = numComponents;
            for (int  j = i+1; j<N; j++) {
                if (dsu.connected(i, j)) {
                    components[j] = numComponents;
                }
            }
        }
    }
    vector<vector<int>> forest(numComponents, vector<int>(0));
    for (int i = 0; i<N; i++) {
        forest[components[i]-1].push_back(i);
    }

    //find distances
    //although edges are weighted, since the graph is a tree we can just apply DFS/BFS as paths are unique
    //I will use BFS cause I don't want to call another function
    vector<vector<int>> dist(N, vector<int>(N));
    for (int i = 0; i<N; i++) {
        vector<int> distFrom_i(N, -1);
        distFrom_i[i] = 0; 
        deque<int> bfs;
        bfs.push_back(i);
        while (!bfs.empty()) {
            int node = bfs.front();
            bfs.pop_front();
            for (int k = 0; k<edges[i].size(); k++) {
                if (bfs[edges[i][k].first] == -1) {
                    distFrom_i[edges[i][k].first] = distFrom_i[i] + edges[i][k].second;
                    bfs.push_back(edges[i][k].first);
                }
            }
        }
        for (int j = 0; j<N; j++) {
            dist[i][j] = distFrom_i[j];
        }
    }
    
    //precompute binomial coefficients
    vector<ll> choose(numComponents);
    for (int  i = 0; i < numComponents; i++) {
        choose[i] = mult(forest[i].size(), forest[i].size()-1, MOD);
        choose[i] = div(choose[i], 2, MOD);
    }
    ll totalMult = 1;
    for (int i  = 0; i < numComponents; i++) {
        totalMult = mult(totalMult, choose[i], MOD);
    }
    
    //knapsack DP
}
