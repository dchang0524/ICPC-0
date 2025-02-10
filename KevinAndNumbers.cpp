#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

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

void printMultiset(multiset<int> k) {
    cout << "{";
    for (int i : k) {
        cout << i << ", ";
    }
    cout << "}";
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) {
        int N, M; cin >> N >> M;
        unordered_map<int, int> A;
        int Asize = N;
        multiset<int> B; //using a hashmap is faster but more implementation
        for (int i = 0; i < N; i++) {
            int a; cin >> a;
            A[a]++;
        }
        for (int i = 0; i < M; i++) {
            int b; cin >> b;
            B.insert(b);
        }

        while (!B.empty() && B.size() <= Asize) {
            auto k = prev(B.end());
            int val = *k;
            if (val == 1 && A[val] == 0) {
                break;
            }
            B.erase(k);


            if (A[val] > 0) {
                A[val]--;
                Asize--;
            } else {
                if (val % 2 == 0) {
                    B.insert(val/2);
                    B.insert(val/2);
                } else {
                    B.insert(val/2+1);
                    B.insert(val/2);
                }
            }
        }

        bool Aempty = true;
        for (const auto &p : A) {
            if (p.second != 0) {
                Aempty = false;
                break;
            }
        }

        if (Aempty && B.empty()) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }

    }
}
