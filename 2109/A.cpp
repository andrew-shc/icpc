#include <bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using vll = std::vector<ll>;
using dll = std::deque<ll>;
using pll = std::pair<ll, ll>;
using vpll = std::vector<pll>;

const ll NEG = (long long)-4e18;
const ll MOD = 998244353;

#define INC(i, n) \
    for (ll i = 0; i < n; i++)

#define DEC(i, n) \
    for (ll i = n; i >= 0; i--)

#define OUT_ITER(a)                 \
    {                               \
        for (auto &el : a)          \
        {                           \
            std::cout << el << " "; \
        }                           \
        std::cout << std::endl;     \
    }

template <typename... Args>
void cout_vars(Args... args)
{
    ((std::cout << std::fixed << std::setprecision(10) << args << " "), ...) << std::endl;
}
#define OUT(...) \
    cout_vars(__VA_ARGS__)

#define READ_S(s) \
    string s;     \
    cin >> s;

#define READ_VLL(a, n)         \
    vll a;                     \
    for (ll i = 0; i < n; i++) \
    {                          \
        ll ai;                 \
        std::cin >> ai;        \
        a.push_back(ai);       \
    }

template <typename... Args>
void read_vars(Args &...args)
{
    (std::cin >> ... >> args);
}
#define READ(...)   \
    ll __VA_ARGS__; \
    read_vars(__VA_ARGS__)

#ifdef DEBUG
#include "debug.h"
#else
#define DBGLN(...)
#define DBG(...)
#define DBG_ITER(arr)
#define DBG_MAP(map_var)
#define DBLOCK if (false)
#endif

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// END MACROS ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

void solve(ll T);

int main()
{
    /////////////////////////////////////////////////////////////////////
    //// comment out the sync when working with interactive problems ////
    /////////////////////////////////////////////////////////////////////
    ios_base::sync_with_stdio(false);
    /////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////

    cin.tie(NULL);
    cout.tie(NULL);

    ll T = 1;

    cin >> T;

    ll t = T;
    while (t--)
    {
        solve(T - t);
    }

    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// START ACTUAL CODE ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

// start:
//   end:

// rephrase: every overlapping pairs produces one win that gets reassigned to one of the pair
// O.1: each player can win at most 2 and at minimum 0
//      O.1.1: a center player winning 2 => adjacent player can win a most 1 (1 1 1 is valid)
// O.2: there can be at most n-1 1s, or
//      O.2.1: 0 1 1 1 1 1 1 1 1 is valid
//             1 1 1 1 1 1 1 1 0 is valid
//      O.2.2: 1 0 0 0 1 is invalid
//              per O.3, 1 0 0 1 is also invalid
// O.3 (O.2.2): any overlapping pair of number must have a 1 (there must be a win between each duel)
//      O.3.1: REGARDLESS whether a player wins 2 (which means an extra 0 is present which is fine)
//                  1 1 1 1 0 1 0 1 1 1 1 ...

// 0 0 0 0 0 0 0 0 0

void solve([[maybe_unused]] ll T)
{
    READ(n);
    READ_VLL(a, n);

    ll ones = a[n - 1] == 1 ? 1 : 0;
    INC(i, n - 1)
    {
        if (a[i] == 0 && a[i + 1] == 0)
        {
            OUT("YES");
            return;
        }
        if (a[i] == 1)
        {
            ones++;
        }
    }

    if (ones >= n)
    {
        OUT("YES");
    }
    else
    {
        OUT("NO");
    }
}