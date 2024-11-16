//https://codeforces.com/contest/2029/problem/D
#include <bits/stdc++.h>


using namespace std;
typedef long long ll;

void printMap(unordered_map<int, unordered_set<int>> myMap) {
    cout << "print" << endl;
    for (const auto& pair : myMap) {
        cout << "key: " << pair.first << endl;
        for (int i : pair.second) {
            cout << i << " ";
        }
        cout << endl;
    }
}
void printMap(map<int, unordered_set<int>> myMap) {
    cout << "print" << endl;
    for (const auto& pair : myMap) {
        cout << "key: " << pair.first << endl;
        for (int i : pair.second) {
            cout << i << " ";
        }
        cout << endl;
    }
}


void deleteEdge(int nodeA, int nodeB, unordered_map<int, unordered_set<int>>& edges, map<int, unordered_set<int>>& sizes) {
    // Remove the edge from both nodes
    edges[nodeA].erase(nodeB);
    edges[nodeB].erase(nodeA);

    // Update sizes for nodeA
    int oldDegreeA = edges[nodeA].size() + 1; // Degree before deletion
    int newDegreeA = edges[nodeA].size();     // Degree after deletion

    sizes[oldDegreeA].erase(nodeA);
    if (sizes[oldDegreeA].empty()) {
        sizes.erase(oldDegreeA); // Remove empty degree set
    }
    sizes[newDegreeA].insert(nodeA);

    // Update sizes for nodeB
    int oldDegreeB = edges[nodeB].size() + 1;
    int newDegreeB = edges[nodeB].size();

    sizes[oldDegreeB].erase(nodeB);
    if (sizes[oldDegreeB].empty()) {
        sizes.erase(oldDegreeB);
    }
    sizes[newDegreeB].insert(nodeB);
}

void insertEdge(int nodeA, int nodeB, unordered_map<int, unordered_set<int>>& edges, map<int, unordered_set<int>>& sizes) {
    // Add the edge to both nodes
    edges[nodeA].insert(nodeB);
    edges[nodeB].insert(nodeA);

    // Update sizes for nodeA
    int oldDegreeA = edges[nodeA].size() - 1;
    int newDegreeA = edges[nodeA].size();

    sizes[oldDegreeA].erase(nodeA);
    if (sizes[oldDegreeA].empty()) {
        sizes.erase(oldDegreeA);
    }
    sizes[newDegreeA].insert(nodeA);

    // Update sizes for nodeB
    int oldDegreeB = edges[nodeB].size() - 1;
    int newDegreeB = edges[nodeB].size();

    sizes[oldDegreeB].erase(nodeB);
    if (sizes[oldDegreeB].empty()) {
        sizes.erase(oldDegreeB);
    }
    sizes[newDegreeB].insert(nodeB);
}

class DisjointSets {
 private:
   vector<int> parents;
   vector<int> sizes;
   int numC;

 public:
   DisjointSets(int size) : parents(size), sizes(size, 1) {
       numC = size;
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
       numC--;
       return true;
   }
   
   int numComponents() {
    return numC;
   }

   /** @return whether x and y are in the same connected component */
   bool connected(int x, int y) { return find(x) == find(y); }
};


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        int N, M;
        cin >> N >> M;
        //Consider forest of k trees
            //You can merge 2 trees into 1 tree if at least one of the trees have at least 1 edge
        //Consider the following algorithm:
            //Find a node 'a' that has at least 2 distinct neighbors, 'b' and 'c' and apply operation (a,b,c)
                //Repeat until no such node exists
            //Since the total number of edges decrease 1 or 3 after each operation, this process must terminate
                //it will terminate in at most M steps
        //After this algorithm terminates, every node will have 0 or 1 neighbors
            //This means we have a forest consisting of trees of size 2 or 1
                //If we have no trees of size 2, the total number of edges are 0, so the graph is already cool
                //Otherwise, we can merge all of these trees, where every merge costs 1 operation
                    //There are less than N trees, so we use less than N operations
                    //Select one tree with size >= 2 (1+ edge), say there exists an edge between node 'a' and 'b'
                        //Select one node, 'c', not connected to the tree
                        //Perform (a, b, c)
        //The total cost of reducing the graph to trees and merging the trees uses less than N + M operations
        unordered_map<int, unordered_set<int>> edges;
        for (int i = 0; i < M; i++) {
            int a, b;
            cin >> a >> b;
            a--;
            b--;
            edges[a].insert(b);
            edges[b].insert(a);
        }

        //cout << "Check point 1" << endl;
        
        map<int, unordered_set<int>> sizes;
        for (const auto& pair : edges) {
            int node = pair.first;
            int degree = pair.second.size(); 
            sizes[degree].insert(node);
        }

        // cout << edges.size() << endl;
        // cout << sizes.size() << endl;
        // printMap(edges);
        // printMap(sizes);

        //cout << "Check point 2" << endl;
        vector<vector<int>> operations;
        while (!sizes.empty()) {
            auto maxDegreeIt = prev(sizes.end());
            int maxDegree = maxDegreeIt->first;
            if (maxDegree <= 1) {
                break;
            }
            int node = *(maxDegreeIt->second.begin());
            auto it = edges[node].begin();
            int neighborA = *it++;
            int neighborB = *it;
            deleteEdge(node, neighborA, edges, sizes);
            deleteEdge(node, neighborB, edges, sizes);
            if (edges[neighborA].count(neighborB)) {
                deleteEdge(neighborA, neighborB, edges, sizes);
            } else {
                insertEdge(neighborA, neighborB, edges, sizes);
            }
            vector<int> currOperation;
            currOperation.push_back(node+1);
            currOperation.push_back(neighborA+1);
            currOperation.push_back(neighborB+1);
            operations.push_back(currOperation);
        }
        
        //cout << "Check point 3" << endl;

        // printMap(edges);
        // printMap(sizes);
        if (sizes.size()) {
            auto maxDegreeIt = prev(sizes.end());
            int maxDegree = maxDegreeIt->first;
            if (maxDegree == 1) { //needs merging
                DisjointSets dsu(N);
                for (const auto& pair : edges) {
                    for (int i : pair.second) {
                        dsu.unite(pair.first, i);
                    }
                }
                int node = *(maxDegreeIt->second.begin());
                for (int i = 0; i < N; i++) {
                    if (!dsu.connected(node, i)) {
                        auto it = edges[node].begin();
                        int neighborA = *it;
                        dsu.unite(node, i);
                        insertEdge(node, i, edges, sizes);
                        insertEdge(neighborA, i, edges, sizes);
                        deleteEdge(node, neighborA, edges, sizes);

                        vector<int> currOperation;
                        currOperation.push_back(node+1);
                        currOperation.push_back(neighborA+1);
                        currOperation.push_back(i+1);
                        operations.push_back(currOperation);
                    }
                }
            }
        }

        cout << operations.size() << endl;
        for (int i = 0; i < operations.size(); i++) {
            for (int j = 0; j < operations[i].size(); j++) {
                cout << operations[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}       
