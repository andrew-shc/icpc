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

// allowing the elements to be placed anywhere once taken from simplifies the questions....
// we are also guaranteed the EXISTENCE of sequence of these operations

// O.1: you can move all the 0s at the top back below the 1s at the bottom at the same pile (reflexive)
//          (right below the 1s that are needed for other piles)
// O.2: all the 1s at the top would be insert into other piles that needs the 1s (we dont care where,
//          since we only care about minimizing ops, our analysis ends here)
// O.3: if some piles needs 0s, first move the 0s out (independent of the later operation of 1s except for moving 0s down)
// O.4: by the assumption of EXISTENCE, we can just check each pile LOCALLY to find extra 0s and extra 1s

// strat: solve by expulsion
//          given each a,b,c,d
//          a-c>0 (more 0s than needed? expel them to piles that are needed--we don't care where it goes, we know it is
//                  guaranteed to be optimally placed s.t. 0-ops to get to the condition)
//          b-d>0 (more 1s than needed? move the remaining 0s (c OR LESS) right below the 1s that are needed and move b-d 1s out )

// can there be a better way where we expel all the 0s to another block and shift it back?
//      unlikely... no thats extra ops because then we would need additional ops to get the 0s back
//      when we already have better more optimal op counts such as the above strat
//   => O.5: no unnecessary moving of the 0s and 1s around (batching doesnt improve)

void solve([[maybe_unused]] ll T)
{
    // codeforce slow

    READ(n);

    ll min_ops = 0;
    INC(i, n)
    {
        READ(a, b, c, d);
        if (a - c > 0)
        { // expel extraneous 0s
            min_ops += a - c;
            a = c;
        }

        if (b - d > 0)
        { // too much 1s
            // shift the 0s down until right below the extraneous 1s
            min_ops += a;
            // expel extraneous 1s
            min_ops += b - d;
            b = d;
        }
    }

    OUT(min_ops);
}