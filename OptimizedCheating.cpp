//https://open.kattis.com/contests/nasouth24d1open/problems/optimizedcheating
//https://open.kattis.com/problems/optimizedcheating
//Let S = {}
//For each number in the memory, add it to S if the memory isn't the memory for the currency
//We perform a BFS, where a number is connected to the numbers that can be obtained by performing any of the M operations
    //Instead of keeping a visted array, we keep a visited set of numbers
    //The first time a number is visited is the lowest distance from the initial value
    //We never have to visit more than N values, as if we visit N+1 distinct values we are guranteed that one value is not in the set S
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

template <typename T>
ostream& operator<<(ostream& os, const deque<T>& d) {
    for (const auto& elem : d) {
        os << elem << " ";
    }
    return os;
}

int applyOperation (char o, int v, int c) {
    int next = c;
    if (o == '+') {
        next += v;
        if (next > (int)1e9) {
            return 1e9 + 1;
        }
    }
    else if (o == '-') {
        next -= v;
    }
    else if (o == '*') {
        ll a = next;
        ll b = v;
        if (a*b > (ll)1e9) {
            return (int)1e9 + 1;
        }
        next *= v;
    }
    else if (o == '/') {
        next /= v;
    }
    return next;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int N, M, K;
    cin >> N >> M >> K;
    K--;
    int x = 0;
    unordered_set<int> memory;
    for (int i = 0; i < N; i++) {
        int temp;
        cin >> temp;
        if (i != K)
            memory.insert(temp);
        else
            x = temp;
    }

    vector<char> op(M);
    vector<int> opVal(M);
    for (int i = 0; i < M; i++) {
        char a;
        int b;
        cin >> a >> b;
        op[i] = a;
        opVal[i] = b;
    }


    unordered_set<int> visited; //we could just use dist to keep track of visited, but that's extra work
    unordered_map<int, int> dist; 
    unordered_map<int, int> opUsed; //[i, operation #] last operation used to get to i
    unordered_map<int, int> prev; //[i, last # visited before i]. we could also just reverse opUsed[i] on i, but that's more work
    deque<int> bfs;
    bfs.pb(x);
    bool foundAns = false;
    int ans = -1;
    int lastNode = -1;
    if (!memory.count(x)) {
        foundAns = true;
        ans = 0;
        lastNode = x;
    }
    visited.insert(x);
    dist[x] = 0;
    opUsed[x] = -1;
    prev[x] = -1;

    while (!foundAns && !bfs.empty()) {    
        int curr = bfs.front();
        bfs.pop_front();

        for (int i = 0; i < M; i++) {
            int next = applyOperation(op[i], opVal[i], curr);
            if (next < 0) {
                continue;
            }

            if (!visited.count(next)) {
                visited.insert(next);
                bfs.pb(next);
                dist[next] = dist[curr] + 1;
                prev[next] = curr;
                opUsed[next] = i;
                if (memory.count(next)) {
                    bfs.pb(next);
                }
                else {
                    foundAns = true;
                    ans = dist[next];
                    lastNode = next;
                    break;
                }
            }
        }
    }
    cout << ans << endl;
    int currNode = lastNode;
    vector<int> steps;
    while (foundAns && currNode != x) {
        steps.pb(opUsed[currNode]);
        currNode = prev[currNode];
    }
    for (int i = steps.size()-1; i >= 0; i--) {
        int c = steps[i] + 1;
        cout << c << endl;
    }
}
