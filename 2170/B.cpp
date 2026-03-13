#include <bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;
typedef std::vector<ll> vll;
typedef std::deque<ll> dll;

const long long NEG = (long long)-4e18;

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
    ((std::cout << args << " "), ...) << std::endl;
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
    ios_base::sync_with_stdio(false);
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

// bit slower due to micro sleeps again

// O.1: we do not care about the ordering of each elements in {a} (allows maps, frequency maps, multisets)
//         (though we still care about duplicates/freq.)

// O.2: max r-l+1 is # of elements that are not 0

// O.3: there's always a way to reach {a} to {b} (i.e., min. amount of action s.t. there's no such thing as not enough actions)

// O.4: the max({b}) is the min amount of action needed.
//      O.4.1: if max({b}) < n, (ie extra action that needs to be spent)
//          >> check all the unique distinct elements >1
//              if # of unique distinct elements > n-max({b}) => partitioning up the widest floor (@=1)

//      O.4.2: n-max({b}) - uniq. distinct elements (apart from the col with max({b}) via -max({b})+1)
//          >> be the number of remaining actions

// ~~~~~~~~~~~~
// O.5:
//      1 action left: remove the left/right-most one (r-l+1  -1)
//      2 action left: remove the left/right-most one (r-l+1  -2)
//      3 action left: remove the left/right-most one (r-l+1  -3)
//      optimally pick the smallest portion to leave the largest portion
// ~~~~~~~~~~~~

// wrong previous is correct
// O.6: recall we're trying to find the largest partition
//      1 action left: 1/2 (half)
//      2 action left: 2/3 (thirds)
//      3 action left: 3/4

void solve([[maybe_unused]] ll T)
{
    READ(n);
    READ_VLL(b, n);

    ll max_el = 0;
    ll nonzeros = 0;
    ll actions_left = n;
    for (auto &el : b)
    {
        max_el = max(max_el, el);
        if (el > 0)
        {
            actions_left -= el - 1; // -1 for greatest match at the end
            nonzeros++;
        }
    }

    if (actions_left <= 0)
    { // no more actions before reaching the final step
        OUT(nonzeros);
    }
    else
    {
        // still actions left for the last bottom layer
        OUT((nonzeros - actions_left) + 1);
    }
}