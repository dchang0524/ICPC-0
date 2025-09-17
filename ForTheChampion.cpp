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

ll query(string dir, ll dist) {
	cout << "? " << dir << " " << dist << endl;
	cout.flush();
	ll q; cin >> q;
	// cout << "Result " << q << endl;
	return q;
}

void solve() {
    def(int, N);
	ll maxX = 1e9;
	ll maxY = 1e9;
	vector<pll> anchors(N);
	FOR(i, 0, N) {
		def(ll, x, y);
		anchors[i] = {x, y};
	}

	//move to top left
	query("U", maxY);
	query("U", maxY);
	query("L", maxX);
	ll d1 = query("L", maxY);
	//find the closest point
	pll pivot = anchors[0];
	set<pll> dists; dists.insert({0, 0});
	FOR(i, 1, N) {
		ll d = 0;
		d += pivot.second - anchors[i].second;
		d += anchors[i].first - pivot.first;
		dists.insert({d, (ll)i});
	}
	ll c1 = dists.begin()->second;
	
	query("D", maxY);
	query("D", maxY);
	query("D", maxY);
	ll d2 = query("D", maxY);
	pivot = anchors[0];
	dists.clear(); dists.insert({0, 0});
	FOR(i, 1, N) {
		ll d = 0;
		d += anchors[i].second - pivot.second;
		d += anchors[i].first - pivot.first;
		dists.insert({d, (ll)i});
	}
	ll c2 = dists.begin()->second;
	// cout << c1 << " " << c2 << endl;
	ll x1 = anchors[c1].first;
	ll x2 = anchors[c2].first;
	ll y1 = anchors[c1].second;
	ll y2 = anchors[c2].second;
	ll x = (x1 + x2 + 8*maxX +y2 - y1 -d1 -d2)/2;
	ll y = (d1 - d2 +y1 + y2 -x1+ x2)/2;
	cout << "! " << x << " " << y << endl;
	cout.flush();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    rep (T) {
        solve();
    }
}

