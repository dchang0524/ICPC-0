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
    int N; cin >> N;
    vector<ll> A(N+1);
    FOR (i, 1, N+1) {
        cin >> A[i];
    }
    //A_{2i} >= A_{2i - 1} + A_{2i + 1} for all valid i
    if (N % 2 == 0) {
        A.pb(0LL);
        N++;
    }
    // cout << A << endl;
    ll totalOps = 0;
    //guranteed ops
    for (int i = 2; i < N; i += 2) {
        if (A[i] < A[i-1]) {
            ll diff = A[i-1] - A[i];
            A[i-1] = A[i];
            totalOps += diff;
        }
        if (A[i] < A[i+1]) {
            ll diff = A[i+1] - A[i];
            A[i+1] = A[i];
            totalOps += diff;
        }
    }
    //remaining ops
    for (int i = 2; i < N; i += 2) {
        if (A[i] < A[i-1] + A[i+1]) {
            ll diff = A[i-1] + A[i+1] - A[i];
            ll ops = min(diff, A[i+1]);
            A[i+1] -= ops;
            totalOps += ops;
            if (A[i] < A[i-1] + A[i+1]) {
                ll diff = A[i-1] + A[i+1] - A[i];
                ll ops = min(diff, A[i-1]);
                A[i-1] -= ops;
                totalOps += ops;
            }
        }
    }
    cout << totalOps << "\n";
}

int main() {
    // ios_base::sync_with_stdio(0);
    // cin.tie(0); cout.tie(0);
    int T; cin >> T;
    rep (T) {
        solve();
    }
}

