#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}

ll lcm(ll a, ll b) {
    return a/gcd(a, b)*b;
}

ll inv(ll a, ll b) {
    if (a == 0) {
        return 0;
    }
    if (a == 1) return 1ll;
    return b - inv(b % a, a) * b / a;
}

void solve(int T, int TT) {
    ll N, x, y, v_x, v_y; cin >> N >> x >> y >> v_x >> v_y;
    // cout << "N: " << N << " x: " << x << " y: " << y << endl;
    // cout << "v_x: " << v_x << " v_y: " << v_y << endl;
    ll g = gcd(v_x, v_y); v_x = v_x/g; v_y = v_y/g;
    // cout << "v'_x: " << v_x << " v'_y: " << v_y << endl;
    g = gcd(v_x, N);
    if ((N - x) % g != 0) {
        cout << -1 << endl;
        return;
    }
    ll m_1 = N/g;
    ll t_1 = (N - x)/g * inv(v_x/g, m_1) % m_1;
    // cout << t_1 << " mod " << m_1 << endl;
    g = gcd(v_y, N);
    if ((N - y) % g != 0) {
        cout << -1 << endl;
        return;
    }
    ll m_2 = N/g;
    ll t_2 = (N - y)/g * inv(v_y/g, m_2) % m_2;
    // cout << t_2 << " mod " << m_2 << endl;

    //t mod lcm(m_1, m_2) = t_1 mod m_1, t_2 mod m_2
    //t_1 + (m_1)*(x_1) = t_2 + (m_2)(x_2)
        //t_2 - t_1 = (m_1)*(x_1) + (m_2)(-x_2)
        //1 = (m_1)/g *(b_1) + (m_2)/g *(b_2)
            //(b_1) = inv(m_1/g, m_2/g)
    //x_1 = (b_1)*(t_2 - t_1)/g
    //t = t_1 + (m_1)(x_1) mod m_1 * m_2
    g = gcd(m_1, m_2);
    if ((t_2 - t_1) % g != 0) {
        cout << -1 << endl;
        return;
    }
    ll b_1 = inv(m_1/g, m_2/g);
    // cout << "b_1: " << b_1 << endl;
    ll x_1 = b_1 * (t_2 - t_1)/g;
    // cout << "x_1: " << x_1 << endl;
    ll m_f = lcm(m_1, m_2);
    ll t = ((t_1 + m_1 * x_1) % m_f + m_f) % m_f;
    // cout << t << " mod " << lcm(m_1, m_2) << endl;

    ll t_x = (t*v_x + x)/N;
    ll t_y = (t*v_y + y)/N;
    ll ans = (t_x - 1) + (t_y - 1) + (t_x + t_y)/2 + abs(t_x - t_y)/2;
    cout << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    int t = 1;
    while (t <= T) {
        solve(t, T);
        t++;
    }
}

