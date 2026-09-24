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

// start: ~1100
//   end:

// rephrase: the earliest time when ALL rooms have their lights on

// O.1: if a pair of rooms are started at an offset of 2k apart exactly (for any integer k) => they're the same
// O.2: if a pair of rooms are started at an offset of  k apart exactly (for any integer k) => -1

/*
strat


starting with the largest element max(a):
    - we have the earliest valid range from max(a) to max(a)+k-1

    // O.3: if the first valid interval the max(a) to max(a)+k are invalid (no point in time when all their lights are turn on)
    //          => all the next intervals are invalid => we just have to check the initial interval max(a) to max(a)+k

from the *next* largest to smallest over aj
    - if @max(a) - j    <=    k-1:    decrease max(a)+k-1 by @max(a)-j
    - if @max(a) - j

*/

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// O.1: it is impossible (-1) whenever any pair of rooms are initiated perfectly at k-times apart

void solve([[maybe_unused]] ll T)
{
    READ(n, k);
    READ_VLL(a, n);

    sort(a.begin(), a.end());

    ll l = a[n - 1];
    ll r = a[n - 1] + k - 1;

    DEC(i, n - 2)
    {
        // a[n-1] is our max
        ll d = (a[n - 1] - a[i]) % (2 * k);

        if (d < k)
        {
            r = min(r, a[n - 1] + k - 1 - d);
        }
        else if (d == k)
        {
            OUT(-1);
            return;
        }
        else
        { // k<d<2*k
            l = max(l, a[n - 1] + (2 * k - d));
        }
    }

    if (l > r)
    {
        OUT(-1);
    }
    else
    {
        OUT(l);
    }
}
