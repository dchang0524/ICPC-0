//https://open.kattis.com/contests/nasouth24d1open/problems/islandmemories
//https://open.kattis.com/problems/islandmemories
//Consider a componenet as a set of nodes(islands) who form a tree
    //We can split a component into two components, and adding an edge between two components
//We view the problem as a graph
    //each node is a component
    //an edge between two components means that 
        //there exists exactly 1 edge in the graph of islands between 
            //a node in the set of vectors in the first component and 
            //a node in the set of vectors in the second component
    //Initially, we have 1 component with all the islands
    //Every time an edge in the island graph is lifted, 
        //one component will be split into two components with an edge between them 
        //the components connected to the component before the split will be distributed between the two splitted components
//For each memory of the islanders
    //A set of islands will be given, and they must all belong to some component
    //If this is a consistent memory the following must hold:
        //There is a maximum of one component where only some (not all, not 0) of its islands are included in the set
            //Because maximum of one component can be split into two components when an edge is lifted
                //0 components are split when the edge lifted in the island graph is represented in the component graph
        //Out of the components represented by the islands in the memory
            //It must be possible visit each component represented without visiting an unrepresented component
                //Otherwise, when the edge is lifted, the components represented wouldn't be fully connected
                //You must make the same check for unrepresented components
    //Thus each memory can be processed by a check of hashmap and BFS with hashset, so overall time complexity is O(M*N)
        //M = number of memories
        //N = number of islands
            //Note number of edges is less than N because the graph of components can't have more than N components and the graph is a tree
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

// Overload operator<< for pair
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) {
   os << "(" << p.first << ", " << p.second << ")";
   return os;
}


// Overload operator<< for set
template <typename T>
ostream& operator<<(ostream& os, const set<T>& s) {
   os << "{";
   bool first = true;
   for (const auto& elem : s) {
       if (!first) os << ", ";
       os << elem; // Requires operator<< for T
       first = false;
   }
   os << "}";
   return os;
}


// Overload operator<< for unordered_set
template <typename T>
ostream& operator<<(ostream& os, const unordered_set<T>& s) {
   os << "{";
   bool first = true;
   for (const auto& elem : s) {
       if (!first) os << ", ";
       os << elem; // Requires operator<< for T
       first = false;
   }
   os << "}";
   return os;
}


// Overload operator<< for map
template <typename K, typename V>
ostream& operator<<(ostream& os, const map<K, V>& umap) {
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


// Overload the << operator for vector
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
   for (const auto& elem : v) {
       os << elem << " ";
   }
   return os;
}

// Overload the << operator for deque
template <typename T>
ostream& operator<<(ostream& os, const deque<T>& dq) {
    os << "[";
    for (auto it = dq.begin(); it != dq.end(); ++it) {
        if (it != dq.begin()) {
            os << ", ";
        }
        print_element(os, *it);
    }
    os << "]";
    return os;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int N, M;
    cin >> N >> M;
    int numComponents = 1;
    vector<int> compNum(N+1, 1);
    compNum[0] = 0;
    unordered_map<int, unordered_set<int>> compEdges;

    bool consistent = true;
    for (int i = 0; i < M; i++) {
        if (!consistent) {
            break;
        }
        int k;
        cin >> k;
        unordered_set<int> curr;
        for (int j = 0; j < k; j++) {
            int a;
            cin >> a;
            curr.insert(a);
        }
        unordered_set<int> currComps; //components represented
        unordered_set<int> notComps; //components not represented
        int split = 0;
        for (int j = 1; j <= N; j++) {
            if (curr.count(j)) {
                currComps.insert(compNum[j]);
                if (notComps.count(compNum[j])) {
                    if (split == 0 || split == compNum[j]) {
                        split = compNum[j];
                    }
                    else {
                        consistent = false;
                        break;
                    }
                }
            }
            else {
                notComps.insert(compNum[j]);
                if (currComps.count(compNum[j])) {
                    if (split == 0 || split == compNum[j]) {
                        split = compNum[j];
                    }
                    else {
                        consistent = false;
                        break;
                    }
                }
            }
        }
        // if (i == M-1) {
        //     cout << "Consistent: " << consistent << endl;
        //     cout << "processing last query" << endl;
        //     cout << "numComponents: " << numComponents << endl;
        //     cout << "components: " << compNum << endl;
        //     cout << "Component edges: " << compEdges << endl;
        //     cout << "Curr: " << curr << endl;
        //     cout << "CurrComps: " << currComps << endl;
        //     cout << "NotComps: " << notComps << endl;
        //     cout << "Split: " << split << endl;
        // }

        //split component, if needed
        if (split > 0) {
            numComponents++;
            for (int j = 1; j <= N; j++) {
                if (compNum[j] == split && curr.count(j)) {
                    compNum[j] = numComponents;
                }
            }

            for (int c : currComps) {
                if (compEdges[split].count(c)) {
                    compEdges[split].erase(c);
                    compEdges[c].erase(split);

                    compEdges[numComponents].insert(c);
                    compEdges[c].insert(numComponents);
                }
            }
        }

        //check if traversal is possible
        if (split != 0) {
            currComps.insert(numComponents);
            currComps.erase(split);

            notComps.insert(split);
        }
        if (!currComps.empty()) {
            deque<int> bfs;
            unordered_set<int> visited;
            bfs.pb(*(currComps.begin()));
            visited.insert(*(currComps.begin()));
            while (!bfs.empty() && visited.size() < currComps.size()) {
                int c = bfs.front();
                bfs.pop_front();
                for (int neighbor : compEdges[c]) {
                    if (!visited.count(neighbor) && currComps.count(neighbor)) {
                        visited.insert(neighbor);
                        bfs.pb(neighbor);
                    }
                }
            }

            if (visited.size() != currComps.size()) {
                consistent = false;
                break;
            }
        }

        if (!notComps.empty()) {
            deque<int> bfs;
            unordered_set<int> visited;
            bfs.pb(*(notComps.begin()));
            visited.insert(*(notComps.begin()));
            while (!bfs.empty() && visited.size() < notComps.size()) {
                int c = bfs.front();
                bfs.pop_front();
                for (int neighbor : compEdges[c]) {
                    if (!visited.count(neighbor) && notComps.count(neighbor)) {
                        visited.insert(neighbor);
                        bfs.pb(neighbor);
                    }
                }
            }

            if (visited.size() != notComps.size()) {
                consistent = false;
                break;
            }
        }

        //add edge between splitted components if they were splitted
        if (split != 0) {
            compEdges[split].insert(numComponents);
            compEdges[numComponents].insert(split);
        }
    }

    // cout << numComponents << endl;
    // cout << endl;
    // cout << compNum << endl;
    // cout << endl;
    // cout << compEdges << endl;
    // cout << endl;

    //answer
    if (consistent) {
        cout << 1 << endl;
    }
    else {
        cout << 0 << endl;
    }

}
