#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int N;
vector<int> sol;

// Overload the << operator for vector
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
   for (const auto& elem : v) {
       os << elem << " ";
   }
   return os;
}

int prev(int a) {
    if (a - 1 == -1) {
        return N - 1;
    }
    return a - 1;
}

int next(int a) {
    if (a + 1 == N) {
        return 0;
    }
    return a + 1;
}

void fill(int a, int b) {
    sol[a] = 0;
    sol[b] = 0;
    int curr = next(a);
    while (curr != b) {
        if (curr == prev(b)) {
            if (sol[prev(curr)] == 1) {
                sol[curr] = 2;
            }
            else {
                sol[curr] = 1;
            }
        }
        else {
            if (sol[prev(curr)] == 0) {
                sol[curr] = 1;
            }
            else {
                sol[curr] = 0;
            }
        }
        curr = next(curr);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) {
        cin >> N;
        vector<int> temp(N);
        sol = temp;
        int a, b; cin >> a >> b; a--; b--;
        if (N == 3) {
            for (int i = 0; i < N; i++) {
                sol[i] = i;
            }
        }
        else if (b == prev(a) || b == next(a)) {
            sol[a] = 1;
            fill(next(a), prev(a));
        }
        else if (N == 4) {
            sol[a] = 1;
            sol[b] = 2;
        }
        else if (next(next(a)) == b) {
            sol[a] = 1;
            sol[next(a)] = 2;
            fill(b, prev(a));
        }
        else if (prev(prev(a)) == b) {
            sol[a] = 1;
            sol[prev(a)] = 2;
            fill(next(a), b);
        }
        else {
            sol[a] = 1;
            fill(next(a), b);
            fill(b, prev(a));
        }
        cout << sol << endl;
        //cout << a << " " << b << endl;
    }
}
