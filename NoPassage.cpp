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
    // ios_base::sync_with_stdio(0);
    // cin.tie(0); cout.tie(0);
    def(int, H, W, K);
    auto vis = vector<vector<vi>>(H+1, vector<vi>(W+1, vi()));
    vector<vector<int>> dp(H+1, vector<int>(W+1, -1));
    deque<pii> q;
    vector<pii> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    rep(K) {
        def(int, x, y);
        q.pb(mp(x, y));
        dp[x][y] = 0;
    }
    while (!q.empty()) {
        // cout << q << endl;
        auto [x, y] = q.front();
        // cout << "Processing: " << x << ", " << y << endl;
        q.pop_front();
        for (auto &d : directions) {
            int nx = x + d.first, ny = y + d.second;
            if (nx >= 1 && nx <= H && ny >= 1 && ny <= W && dp[nx][ny] == -1) {
                vis[nx][ny].pb(dp[x][y]);
                if (vis[nx][ny].size() == 2) {
                    q.pb(mp(nx, ny));
                    dp[nx][ny] = vis[nx][ny][1] + 1;
                }
            }
        }
        // cout << "dp[" << x << "][" << y << "] = " << dp[x][y] << endl;
    }
    // FOR1 (i, 1, W) {
    //     FOR1(j, 1, H) {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    ll ans = 0;
    FOR1(i, 1, H) {
        FOR1(j, 1, W) {
            if (dp[i][j] != -1) {
                ans += dp[i][j];
            }
        }
    }
    cout << ans << endl;
}
