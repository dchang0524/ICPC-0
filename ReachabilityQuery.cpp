#include <bits/stdc++.h>
using namespace std;
//#include "debugPrints.h"

#define pb push_back
#define mp make_pair
#define sz(x) (int)(x).size()
#define rep(x) for (int i = 0; i < (x); ++i)
#define FOR(i, a, b) for(int i = a; i < (b); ++i)
#define FOR1(i, a, b) for(int i = a; i <= (b); ++i)
inline namespace IO {
#define SFINAE(x, ...)                                                         \
	template <class, class = void> struct x : std::false_type {};              \
	template <class T> struct x<T, std::void_t<__VA_ARGS__>> : std::true_type {}
 
SFINAE(DefaultI, decltype(std::cin >> std::declval<T &>()));
SFINAE(DefaultO, decltype(std::cout << std::declval<T &>()));
SFINAE(IsTuple, typename std::tuple_size<T>::type);
SFINAE(Iterable, decltype(std::begin(std::declval<T>())));
 
template <auto &is> struct Reader {
	template <class T> void Impl(T &t) {
		if constexpr (DefaultI<T>::value) is >> t;
		else if constexpr (Iterable<T>::value) {
			for (auto &x : t) Impl(x);
		} else if constexpr (IsTuple<T>::value) {
			std::apply([this](auto &...args) { (Impl(args), ...); }, t);
		} else static_assert(IsTuple<T>::value, "No matching type for read");
	}
	template <class... Ts> void read(Ts &...ts) { ((Impl(ts)), ...); }
};
 
template <class... Ts> void re(Ts &...ts) { Reader<cin>{}.read(ts...); }
#define def(t, args...)                                                        \
	t args;                                                                    \
	re(args);
};

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef unsigned long long ull;
template <typename T> 
vector<T> ndvec(size_t size, T initial_value) {
    return vector<T>(size, initial_value);
}
template <typename T, typename... U> 
auto ndvec(size_t head, U &&...u){
    auto inner = ndvec<T>(u...);
    return vector<decltype(inner)>(head, inner);
} ////example: auto grid = ndvec<char>(n + 1, m + 1, '_');

class DisjointSets {
  public:
    vector<int> parents;
    vector<int> sizes;
	vector<int> numBlack;

    DisjointSets(int size) : parents(size), sizes(size, 1), numBlack(size, 0) {
        for (int i = 0; i < size; i++) { parents[i] = i; }
    }


    /** @return the "representative" node in x's component */
    int find(int x) { return parents[x] == x ? x : (parents[x] = find(parents[x])); }


    /** @return whether the merge changed connectivity */
    bool unite(int x, int y) {
        int x_root = find(x);
        int y_root = find(y);
        if (x_root == y_root) { return false; }


        if (sizes[x_root] < sizes[y_root]) { swap(x_root, y_root); }
        sizes[x_root] += sizes[y_root];
		numBlack[x_root] += numBlack[y_root];
        parents[y_root] = x_root;
        return true;
    }


    /** @return whether x and y are in the same connected component */
    bool connected(int x, int y) { return find(x) == find(y); }
};


void solve() {
    def(int, N, Q);
	DisjointSets dsu(N+1);
	vector<int> color(N+1, 0); //0 white, 1 black
	FOR (i, 0, Q) {
		int type; cin >> type;
		if (type == 1) {
			def(int, u, v);
			dsu.unite(u, v);
		} else if (type == 2) {
			int u; cin >> u;
			if (color[u] == 0) {
				color[u] = 1;
				dsu.numBlack[dsu.find(u)]++;
			} else {
				color[u] = 0;
				dsu.numBlack[dsu.find(u)]--;
			}
		} else {
			int u; cin >> u;
			if (dsu.numBlack[dsu.find(u)] > 0) {
				cout << "Yes\n";
			} else {
				cout << "No\n";
			}
		}
	}


}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    solve();
}

