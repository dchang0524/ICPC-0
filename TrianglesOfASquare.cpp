//https://open.kattis.com/contests/nasouth24d1open/problems/trianglesofasquare
//https://open.kattis.com/problems/trianglesofasquare
//To split a n-gon into triangles, we need n-3 diagonals
//A given line splits the square into 2 triangles, a triangle and a quadrilateral, or 2 quadrilaterals
    //depends on how many corners of the square the given line lies on
#include <bits/stdc++.h>
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
//example:
//auto grid = ndvec<char>(n + 1, m + 1, '_');

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    set<pii> corners; //can't use hashmap because pair don't have built in hash function
    corners.insert(mp(0,0));
    corners.insert(mp(0,2024));
    corners.insert(mp(2024,0));
    corners.insert(mp(2024,2024));
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    cout << 2 - (corners.count(mp(x1, y1)) + corners.count(mp(x2, y2)));

}
