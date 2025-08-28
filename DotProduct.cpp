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

void solve() {
    def(int, N);
    vector<int> A(N);
    FOR(i, 0, N) {
        cin >> A[i];
    }
    vector<int> B(N);
    FOR(i, 0, N) {
        cin >> B[i];
    }
    int ind = -1;
    FOR (i, 1, N) {
        if ((ll)A[0]*B[i] != (ll)A[i]*B[0]) {
            ind = i;
            break;
        }
    }
    // cout << ind << endl;
    if (ind == -1) {
        cout << "No" << endl;
    } else {
        cout << "Yes" << endl;
        int x0 = A[ind] + B[ind];
        int xInd = A[0] + B[0];
        ll val = (ll)(-1) * (ll)A[0] * (ll)x0 + (ll)A[ind] * (ll)xInd;
        if (val > 0) {
            FOR (i, 0, N) {
                if (i == 0) {
                    cout << -x0 << " ";
                } else if (i == ind) {
                    cout << xInd << " ";
                } else {
                    cout << 0 << " ";
                }
            }
            cout << endl;
        } else {
            FOR (i, 0, N) {
                if (i == 0) {
                    cout << x0 << " ";
                } else if (i == ind) {
                    cout << -xInd << " ";
                } else {
                    cout << 0 << " ";
                }
            }
            cout << endl;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    rep (T) {
        solve();
    }
}

