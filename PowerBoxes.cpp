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

int query(int x) {
    cout << "throw " << x << endl;
    cout.flush();
    int ret; cin >> ret;
    return ret;
}

void qSwap(int x) {
    cout << "swap " << x << endl;
    cout.flush();
}

void solve() {
    int N; cin >> N;
    vector<int> f(N+1, -1); //could also just extend to big size and set f[>N] = 0 
    vector<int> p(N+1, -1);
    vector<int> swapsMade;
    //init
    f[N] = 1;
    int q = query(N-1);
    p[N] = q == 1 ? 2 : 1;
    qSwap(N-1); swapsMade.pb(N-1);
    f[N-1] = query(N-1);
    p[N-1] = f[N-1] == 1 ? 2 : 1;

    int last = N-2;
    while (last > 0) {
        if (last == 1) {
            if (f[2] != f[3]) {
                f[1] = query(1);
                p[1] = f[1] == f[2] + 1 ? 1 : 2;
            } else { //f[3] != f[4]
                qSwap(1);
                swapsMade.pb(1);
                f[1] = f[2];
                p[1] = p[2];
                f[2] = query(2);
                p[2] = f[2] == f[3]+1 ? 1 : 2;
            }
        } else {
            if (f[last+1] != f[last+2]) {
                f[last] = query(last);
                p[last] = f[last] == f[last+1] + 1 ? 1 : 2;
            } else {
                f[last-1] = query(last-1);
                f[last] = f[last+1] + 1;
                p[last-1] = f[last-1] == f[last] + 1 ? 1 : 2;
                qSwap(last-1); swapsMade.pb(last-1);
                p[last] = p[last-1];
                f[last-1] = query(last-1);
                p[last-1] = f[last-1] == f[last] + 1 ? 1 : 2;
                last--;
            }
        }
        last--;
    }
    for (int i = sz(swapsMade)-1; i >= 0; i--) {
        int ind = swapsMade[i];
        swap(p[ind], p[ind+1]);
    }
    cout << "! ";
    FOR (i, 1, N+1) {
        cout << p[i] << " ";
    }
    cout << endl;
}

int main() {
    // ios_base::sync_with_stdio(0);
    // cin.tie(0); cout.tie(0);
    int T; cin >> T;
    rep (T) {
        solve();
    }
}

