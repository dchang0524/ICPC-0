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
    def(int, N, M);
	vector<string> votes(N);
	vector<int> cnt(M);
	FOR (i, 0, N) {
		cin >> votes[i];
		FOR (j, 0, M) {
			if (votes[i][j] == '1') {
				cnt[j]++;
			}
		}
	}
	int maxPts = 0;
	vector<int> pts(N);
	FOR (i, 0, N) {
		FOR (j, 0, M) {
			if (cnt[j] > N/2 && votes[i][j] == '0') {
				// cout << cnt[j] << endl;
				// cout << "i: " << i << ", j: " << j << endl;
				pts[i]++;
			} else if (cnt[j] <= N/2 && votes[i][j] == '1') {
				// cout << cnt[j] << " " << M/2 << " " << votes[i][j] << endl;
				// cout << "i: " << i << ", j: " << j << endl;
				pts[i]++;
			}
		}
		maxPts = max(maxPts, pts[i]);
	}
	// cout << cnt << endl;
	// cout << pts << endl;
	FOR (i, 0, N) {
		if (pts[i] == maxPts) {
			cout << i + 1 << " ";
		}
	}

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    solve();
}

