#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        map<int, int> lengths;
        for (int i = 0; i < N; i++) {
            int a; cin >> a;
            lengths[a]++;
        }

        bool works = false;
        int g2 = -1;
        for (const auto &p : lengths) {
            if (p.second >= 2) {
                if (g2 != -1 && !works) {
                    works = true;
                    cout << g2 << " " << g2 << " " << p.first << " " << p.first << endl;
                    break;
                }
                g2 = p.first;
            }
            if (p.second >= 3) {
                if (p.second >= 4 && !works) {
                    works = true;
                    cout << p.first << " " << p.first << " " << p.first << " " << p.first << endl;
                    break;
                } else {
                    auto it = lengths.begin();
                    g2 = p.first;
                    while ((*it).first == g2 || 3*g2 <= (*it).first) {
                        it++;
                        if (it == lengths.end()) {
                            break;
                        }
                    }
                    if (it != lengths.end() && !works) {
                        works = true;
                        cout << (*it).first << " " << g2 << " " << g2 << " " << g2 << endl;
                        break;
                    }
                }
            }
        }
        lengths.erase(g2);
        auto it = lengths.begin();
        while ((next(it)) != lengths.end() && !works) {
            auto p1 = *it;
            auto p2 = *next(it);
            if (p1.first + 2*g2 > p2.first) {
                works = true;
                cout << g2 << " " << g2 << " " << p1.first << " " << p2.first << endl;
                break;
            }
            it++;
        }

        if (!works) {
            cout << -1 << endl;
        }
    }
}
