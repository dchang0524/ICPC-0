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

int query(int a, int b) {
    cout << "? " << a << " " << b << endl;
    cout.flush();
    int q; cin >> q;
    return q;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        unordered_set<int> noOut;
        for (int i = 1; i <= N; i++) {
            noOut.insert(i);
        }
        map<int, set<int>> id;
        for (int i = 0; i < N; i++) {
            int a; cin >> a;
            noOut.erase(a);
            id[a].insert(i+1);
        }
        if (!noOut.empty()) {
            int a = *noOut.begin();
            int b = a == N ? N-1 : N;
            int q = query(a, b);
            if (q == 0) {
                cout << "! A" << endl;
            } else {
                cout << "! B" << endl;
            }
        } else {
            int a = *id[1].begin();
            int b = *id[N].begin();
            int q = query(a, b);
            if (q < N-1) {
                cout << "! A" << endl;
                cout.flush();
            } else {
                int q2 = query(b, a);
                if (q != q2) {
                    cout << "! A" << endl;
                    cout.flush();
                } else {
                    cout << "! B" << endl;
                    cout.flush();
                }
            }
        }
    }
}
