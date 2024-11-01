#include <bits/stdc++.h>


using namespace std;
typedef long long ll;

int query(int a, int b) {
    cout << "? " << a << " " << b << "\n";
    cout.flush();
    int r;
    cin >> r;
    return r;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T;
    cin >> T;
    for (int t = 0; t < T; t++) {
        int N;
        cin >> N;
        vector<int> parent(N, -1);
        parent[0] = 0;
        parent[1] = 0;
        deque<int> level;
        deque<int> newLevel;
        int curr = 0;      
        for (int i  = 2; i <= N; i++) {
            int r = query (1, i);
            if (r == 0) {
                parent[i] = 1;
                newLevel.push_back(i);
                curr = i;
                break;
            }
            else {
                level.push_back(i);
                parent[i] = 0;
            } 
        }
        
        curr++;
        while (curr <= N-1) {
            if (level.size() == 0) {
                level = newLevel;
                newLevel.clear();
            }
            while (level.size() > 0) {
                int c = level.front();
                level.pop_front();
                int r = query(c, curr);
                if (r == 0) {
                    parent[curr] = c;
                    newLevel.push_back(curr);
                    curr++;
                    break;
                }
            }
        }
        
        cout << "! ";
        for (int i = 1; i < N; i++) {
            cout << parent[i] << " ";
        }
        cout.flush();

    }
}
