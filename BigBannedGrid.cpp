#include <bits/stdc++.h>
using namespace std;
// #include "debugPrints.h"

#define pb push_back
#define mp make_pair
#define sz(x) (int)(x).size()
#define rep(x) while(x--)
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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
	int H, W, K; cin >> H >> W >> K;
	set<pii> blocked;
	rep(K) {
		int r, c; cin >> r >> c;
		blocked.insert({r, c});
	}
	deque<pii> q;
	set<pii> visited;
	vector<pii> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1}};
	auto isValid = [&](int r, int c) {
		return r >= 1 && r <= H && c >= 1 && c <= W && visited.find({r, c}) == visited.end();
	};
	auto bfs = [&] {
		while (!q.empty()) {
			pii curr = q.front();
			// cout << "Visiting: " << curr.first << ", " << curr.second << endl;
			q.pop_front();
			for (auto dir : directions) {
				int nr = curr.first + dir.first;
				int nc = curr.second + dir.second;
				if (isValid(nr, nc) && blocked.count({nr, nc})) {
					visited.insert({nr, nc});
					q.pb({nr, nc});
				}
			}
		}
	};

	bool canReach = true;

	for (auto &p : blocked) {
		int r = p.first, c = p.second;
		if (r == H) {
			q.pb({r, c});
			visited.insert({r, c});
		}
	}
	bfs();
	for (int i = 1; i <= H; i++) {
		if (visited.count({i, W})) {
			canReach = false;
			break;
		}
	}
	for (int i = 1; i <= W; i++) {
		if (visited.count({1, i})) {
			canReach = false;
			break;
		}
	}
	// cout << visited << endl;
	q.clear();
	visited.clear();

	for (auto &p : blocked) {
		int r = p.first, c = p.second;
		if (c == 1) {
			q.pb({r, c});
			visited.insert({r, c});
		}
	}
	bfs();
	for (int i = 1; i <= H; i++) {
		if (visited.count({i, W})) {
			canReach = false;
			break;
		}
	}
	for (int i = 1; i <= W; i++) {
		if (visited.count({1, i})) {
			canReach = false;
			break;
		}
	}

	if (canReach) {
		cout << "Yes" << endl;
	} else {
		cout << "No" << endl;
	}
}
