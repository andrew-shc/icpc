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

// rephrase, each ball i is given a direction {-1,1}^2 (45deg only) and xi,yi (the position)
//           all at the same speed ---->
//           determine how many reaches the pocket (at the four corner @s)

// O.1: all balls forms a path of 45deg aligned rectangle
//      O.1.1: if the rectangle is so thin it becomes a line => it will reach a pocket
//      O.1.2: the path of ball then must intersect with the path of other balls =>
//              question becomes if they're sync'd to collide?
// O.2: n is up to 10^3 (quadratic seems to be allowed)
//      H.2.1: simulation
//      O.2.2: quadratic over balls is allowed but cannot be quadratic over the raw space the tool table itself
// H.3: all path of the balls has the same length (assuming perfact path with no collision)

// lets not focus too much on the entire simulation and focus on the case where the ball will reach the pockets
//      (to help me guide which observation immediately helps)

// O.4: any balls along the points of (x,y) where y==x or y==s-x (diagonal and cross-diagonal)
//          will eventually reach the pocket
//      O.4.1: given all the balls initially on the diagonal and cross diagonal... it can collide
//                  with another ball on  the diagonal/cross-diagonal => same amount of balls on diagonal or cross-diagonal
//                  with another ball off the diagonal/cross-diagonal => the old ball get's bounced out but the new ball get's bounced in
//                                                                          => SAME AMOUNT OF BALLS on the diagonals

// to simplify O.4... we just have to count the balls on the diagonals??
// additionally, the balls have to have their direction follow their respective diagonals
// additionally, there won't be loops along the diagonals/cross-diagonals (balls that wouldve been pocketed but could not)
//                  since outer balls (balls closest to the pockets) will be pocketed and disappear and will be like unraveling the onion until all balls on the diagonals are pocketed

// the strong test case carried a lot of the observation O.4 and after

void solve([[maybe_unused]] ll T)
{
    READ(n, s);

    ll pockets = 0;
    INC(i, n)
    {
        READ(dx, dy, xi, yi);

        if ((yi == xi && dx == dy) || (yi == s - xi && dx == -dy))
        {
            pockets++;
        }
    }

    OUT(pockets);
}