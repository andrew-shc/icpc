#include <bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using vll = std::vector<ll>;
using dll = std::deque<ll>;
using pll = std::pair<ll, ll>;
using vpll = std::vector<pll>;

const ll NEG = (long long)-4e18;
const ll MOD = 676767677;

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

// O.0: there's always one partition of a that satisfies... a itself
// REPHRASE: given x,y, we want to find an ORDER of a that minimizes these partitions
//          remember this is truely like partition... subarray is the partition (local)
// O.1: if only x,
//      x=3: 1 1 1   f(a) = 2  {you have 1 three 1's or 3 one 1's}    1x3,3x1
//      x=4: 1 1 1 1  f(a) = 3   1 four 1s, 2 two 1s, 4 one 1s....    1x4,2x2,4x1
//      ..... find any numbers that can divide x (include 1 and x itself)
// O.2: if only y,
//      ..... same thing as O.1
// Q.3: what if it's mixed?
// x+y is even
//  x=3 y=3
//  1 1 1 -1 -1 -1 => 1
//  x=4 y=2
//  1 1 1 1 -1 -1 => 1 & 1 1 1 -1 -1 => 2
//  x=5 y=1
//  1 1 1 1 1  -1 => 1,1,1, 1 1 -1 & 1 1 , 1 1 1 -1
//  1 1 -1 1 1 1 => ....
//      O.3.1:
//          you always want to group the -1s together to minimize partition such as
//          1 -1 1 -1 1 -1 (2) vs 1 1 1 -1 -1 -1 (1)
//          1 -1 1 1 -1 1 (2) vs 1 1 1 1 1 -1 -1 (2 still)
// x+y is odd
//      x=3 y=4
//          +1 +1 +1 -1 -1 -1 -1 (1)
//          +1 +1 -1 -1 -1 -1 -1 (2) vs 1 -1 -1 -1 -1 -1 1 (2)
//

// ~~~~~~~~~~~~~~~~
// O.3: if mixed?
//      1 1 -1 => (either 2 & -1 or 1 & 0)
//      1 -1 -1 => (either -2 & 1 or -1 & 0)
//      1 1 1 -1 => nope
//      1 -1 -1 -1 => nope
//      1 1 -1 -1 => yes (2) => NO PER SUBARRAY
//      ..... even length => odd amount of either (=> both are odd) means impossible?
//      1 1 1 1 1 -1 -1 -1 -1 -1   (NOPE.. COUNTEREXAMPLE, 5 1s and 5 -1s match each other perfectly)

// something is telling me if we separate all the 1s to all the -1s is the optimal
//      BUT UNPROVEN AND UNINTUITIVE

// O.4: x 1s and y -1s is same as x -1s and y 1s (symmetry)
//          since the summation is symmetric on flipping signs of each elements the array (and we are only comparing equality of the sum)
// let x be the larger and y the smaller (x>=y)
// x==y ==> 1 partition valid
// x>y ==> treat it as the case that they are all the same with x-y

void solve([[maybe_unused]] ll T)
{
    READ(x, y);

    vll result;
    INC(i, x)
    {
        result.push_back(1);
    }
    INC(i, y)
    {
        result.push_back(-1);
    }

    if (x == y)
    {
        OUT(1);
        OUT_ITER(result);
    }
    else
    {
        ll n = max(x, y) - min(x, y);

        ll partitions = 1; // 1 is always valid since 1 is divisible to anything
        // we want to find all the valid factors of n
        for (ll f = 2; f <= n; f++)
        {
            if (n % f == 0)
            {
                partitions++;
            }
        }
        OUT(partitions % MOD);
        OUT_ITER(result);
    }
}