#include <bits/stdc++.h>
using namespace std;
// #include "debugPrints.h"

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

void solve() {
    def(int, N);
	vector<unordered_set<int>> adj(N+1);
	rep(N-1) {
		def(int, v1, v2);
		adj[v1].insert(v2);
		adj[v2].insert(v1);
	}
	// cout << "input read" << endl;
	vi dist(N+1);
	vi parent(N+1, -1);
	function<void(int, int)> dfs = [&] (int v, int p) {
		for (int u : adj[v]) {
			if (u == p) continue;
			dist[u] = dist[v] + 1;
			parent[u] = v;
			dfs(u, v);
		}
	};
	dfs(1, -1);
	int v1 = 0;
	int maxDist = 0;
	FOR1 (i, 1, N) {
		if (dist[i] > maxDist) {
			maxDist = dist[i];
			v1 = i;
		}
	}
	dist = vi(N+1);
	parent = vi(N+1, -1);
	dfs(v1, -1);
	int v2 = 0;
	maxDist = 0;
	FOR1 (i, 1, N) {
		if (dist[i] > maxDist) {
			maxDist = dist[i];
			v2 = i;
		}
	}
	//diameter is from v1 to v2
	unordered_set<int> path;
	for (int v = v2; v != -1; v = parent[v]) {
		path.insert(v);
	}
	for (int i : path) {
		if (sz(adj[i]) > 2) {
			for (int nei : adj[i]) {
				if (path.count(nei) == 0) {
					cout << parent[i] << " " << i << " " << nei << endl;
					return;
				}
			}
		}
	}
	cout << -1 << endl;
}

int main() {
    int T; cin >> T;
	while (T--) {
		solve();
	}
}

