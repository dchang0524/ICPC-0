#include <bits/stdc++.h>
//https://open.kattis.com/contests/nasouth24d1open/problems/welcomesign
//A simple implementation problem
using namespace std;

#define pb push_back
#define mp make_pair

typedef long long ll;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

template <typename T> vector<T> ndvec(size_t size, T initial_value) {
    return vector<T>(size, initial_value);
}
template <typename T, typename... U> auto ndvec(size_t head, U &&...u) {
    auto inner = ndvec<T>(u...);
    return vector<decltype(inner)>(head, inner);
}

template <typename T>
void printVector(vector<T> v) {
   for (int i = 0; i<v.size(); i++) {
       cout << v[i] << " ";
   }
   cout << "\n";
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int r, c;
    cin >> r >> c;
    cout << r << " " << c << endl;
    int numOdd = 0;
    for (int i = 0; i < r; i++) {
        string word;
        cin >> word;
        //cout << word << endl;
        //cout << c << " " << word.size() << endl;
        int remaining = c - word.size();
        // cout << remaining << endl;
        if (remaining % 2 == 0) {
            remaining /= 2;
            // cout << remaining << endl;
            string x = "";
            for (int k = 0; k < remaining; k++) {
                x += ".";
            }
            string ans = x + word + x;
            cout << ans << endl;
        }
        else {
            remaining /= 2;
            int left = remaining + (numOdd % 2);
            int right = remaining + (1 - numOdd%2);
            numOdd++;
            string x = "";
            for (int k = 0; k < left; k++) {
                x += ".";
            }
            string y = "";
            for (int k = 0; k < right; k++) {
                y += ".";
            }
            string ans = x + word + y;
            cout << ans << endl;
        }
    }
}
