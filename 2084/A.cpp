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

// for odd (always work assuming n>=2)
// 1 2 3 4 5 6 7 8 9 <- i
// 9 1 2 3 4 5 6 7 8 <- p

// for even
// 1 2 3 4 5 6 7 8
// 1 8 2 3 4 5 6 7 (doesnt work since 8%2==0, we forgot it would be included in there...)

// H.3 only when x%3==2 (when n is even)
// 1 2 3 ......
// 1 x 2 .....

// consider x==6
// 1 2 3 4 5 6
// 6 1 2 3 4 5 (nope doesnt work)
// 1 6 2 3 4 5 (nope doesnt work)
// 1 3 2 6 4 5 (by O.1, @4, it does not have 4-1, and now doesn't work)

// 1 2 3 4 5  6
//   1 2 3 4  5
//   3 5 7 9 11
//     2 4 3  5
//         4  5

// O.1: at the last index, max(pn-1,pn) mod n = n-1
//          but by the permutation restriction, pn-1 or pn must be n-1 (cannot be more than n)
//          => by the domino effect, every index i must contain a pi that is 1 less
// O.2: the optimal choice is pn-1<pn, if pn-1>pn, then it must be pn-2<pn-1 (since you cannot move element more than twice)
//          then, you have the problem of pi @ i where pi=i => pi%i=0

void solve([[maybe_unused]] ll T)
{
    READ(n);
    if (n % 2 == 1)
    {
        vll o;
        o.push_back(n);
        INC(i, n - 1)
        {
            o.push_back(i + 1);
        }
        OUT_ITER(o);
    }
    else
    {
        OUT(-1);
    }
    // else if (n % 3 == 2)
    // {
    //     vll o;
    //     o.push_back(1);
    //     INC(i, n - 1)
    //     {
    //         o.push_back(i + 1);
    //     }
    //     OUT_ITER(o);
    // }
}