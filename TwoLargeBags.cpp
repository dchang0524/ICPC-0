#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        //could replace first and last with hashmaps
        map<int, int> first;
        map<int, int> last;
        set<int> queue;
        for (int i = 0; i < N; i++) {
            int a; cin >> a;
            if (last[a] == 0) {
                last[a]++;
            } else {
                first[a]++;
            }
            queue.insert(a);
        }
        
        auto it = queue.begin();
        bool possible = true;
        while (!queue.empty()) {
            int curr = *it;
            if (last[curr] == 1 && first[curr] == 1) {
                if (queue.size() != 1) {
                    it = queue.erase(it);
                } else {
                    queue.erase(curr);
                }
                continue;
            }
            if (last[curr] == 1 && first[curr] == 0) {
                possible = false;
                break;
            }
            if (last[curr] == 1) {
                first[curr+1] += first[curr] - 1;
                first[curr] = 1;
                queue.insert(curr+1);
                if (queue.size() != 1) {
                    it = queue.erase(it);
                } else {
                    queue.erase(curr);
                }
            }
            if (last[curr] == 0) {
                if (first[curr] == 0) {
                    if (queue.size() != 1) {
                        it = queue.erase(it);
                    } else {
                        queue.erase(curr);
                    }
                    continue;
                }
                if (first[curr] == 1) {
                    possible = false;
                    break;
                }
                last[curr]++;
                first[curr]--;
                first[curr+1] += first[curr] - 1;
                first[curr] = 1;
                queue.insert(curr+1);
                if (queue.size() != 1) {
                    it = queue.erase(it);
                } else {
                    queue.erase(curr);
                }
                    
            }
        }
        if (possible) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
}
