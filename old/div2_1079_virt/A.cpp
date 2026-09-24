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

void solve(ll T);

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

void solve(ll T)
{
    ll x;
    cin >> x;

    // we can do some ***HEURISTICS/BRUTE-FORCE*** => digits can at most by 9x9 (0 <= d(y) <= 81)
    // since we know (with some examples) that y is always greater than x (makes sense)
    //    we can just let y be x to x+81 which covers all the possible range y can be s.t. y-d(y)=x

    for (ll y = x; y <= x + 81; y++)
    {
        ll y1 = y;
        ll digits = 0;
        while (y1 != 0)
        {
            digits += y1 % 10;
            y1 /= 10;
        }

        if (y - digits == x)
        {
            // we know that if x satisfies any one of the y, it also satisfies 9 adjacent friendlies
            //   totaling 10 friendly numbers
            cout << 10 << endl;
            return;
        }
    }

    cout << 0 << endl;

    // divisibility by 9 does not always work esp when y cross carry boundaries (e.g., 999->1000)

    // if (x % 9 != 0)
    // {
    //     cout << 0 << endl;
    // }
    // else
    // {
    //     cout << 10 << endl;
    // }
}