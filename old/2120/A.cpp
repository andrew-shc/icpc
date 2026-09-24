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
// comment: ugliest bruteforce ever to date

// rotating rectangle is not allowed, even 90deg rotation

// 2 kinds of arrangements for 3 rectangles: parallel or t-shaped
// parallel lines requires 3 side SUMMED to x and 3 side EQUAL to x
// t-shaped requires 2 side SUMMED TO x and 2 of the 3 side EQUAL to x ~~~~~~~~

// since lengths are ordered from largest to smallest => just check (for t-shaped arrangement)
//      if the largest side (of the 1st) sums up 2 smallest of the same side (2nd & 3rd)
//              and check if the smaller side (of the 1st) sums to the same number with
//              the smaller side (either 2nd & 3rd) ensuring the 2nd and 3rd has the same length on the smaller side

void solve([[maybe_unused]] ll T)
{
    READ(l1, b1, l2, b2, l3, b3);
    // parallel

    bool works = false;

    works |= l1 + l2 + l3 == b1 && b1 == b2 && b2 == b3;
    works |= b1 + b2 + b3 == l1 && l1 == l2 && l2 == l3;
    // ordered from largest to smallest (the sides)
    works |= l1 == l2 + l3 && l1 == b1 + b2 && b2 == b3;
    works |= b1 == b2 + b3 && b1 == l1 + l2 && l2 == l3;

    if (works)
    {
        OUT("YES");
    }
    else
    {
        OUT("NO");
    }
}