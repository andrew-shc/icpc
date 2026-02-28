#include <bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

const long long NEG = (long long)-4e18;

#define DBG(...)                                     \
    do                                               \
    {                                                \
        std::cout << "[" << #__VA_ARGS__ << "] = ["; \
        _dbg_print(__VA_ARGS__);                     \
        std::cout << "]" << std::endl;               \
    } while (0)

template <typename T>
void _dbg_print(T &&t) { std::cout << t; }

template <typename T, typename... Args>
void _dbg_print(T &&t, Args &&...args)
{
    std::cout << t << ", ";
    _dbg_print(args...);
}
#define DBG_ITER(arr)           \
    do                          \
    {                           \
        cout << #arr << " = ["; \
        bool _dbg_first = true; \
        for (auto &x : arr)     \
        {                       \
            if (!_dbg_first)    \
                cout << ", ";   \
            cout << x;          \
            _dbg_first = false; \
        }                       \
        cout << "]" << endl;    \
    } while (0)

using namespace std;

ll power(ll base, ll exp)
{
    ll result = 1;
    for (ll i = 0; i < exp; i++)
    {
        result *= base;
    }
    return result;
}

void solve(ll T)
{
    ll n;
    cin >> n;

    if (n == 1)
    {
        cout << 1 << endl;
        return;
    }

    // unordered_set<ll> factors;
    ll hk = 1;

    bool new_factor = true;
    ll k = 2;
    for (ll k = 2; k * k <= n; k++)
    {
        if (n % k == 0)
        {
            hk *= k;
            while (n % k == 0)
                n /= k;
        }
    }

    if (n > 1) // n itself was prime also
    {
        hk *= n;
    }

    cout << hk << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    ll T = 1;

    cin >> T;

    while (T--)
    {
        solve(T);
    }

    return 0;
}
