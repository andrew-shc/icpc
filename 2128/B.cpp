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

void solve([[maybe_unused]] ll T)
{
    READ(n);
    READ_VLL(p, n);

    // clearly if the array is already good (not bad), we can just do L all the way
    // consider 1 2 3 4 5 6 7
    // you gotta do the accordion LRLR or RLRL (ie, you can just wait for the fifth element to alternate) (non-local)
    // consider 3 4 5 6 1 7 2
    // we can use the old way of selecting a different end upon the 5th element reaching bad condition (local)

    // can we always start on left side (ie is there a condition where we must do right side?)
    //  1 2 4 7 6 5 3
    //  because if you pick either side, since this is a permutation, the next available number at each endpoints are not equal
    //          => one has to be strictly greater than the other (and the flip side is the same) => YES (ie we can also always start on the right side => just for simplification)

    // denote @Re and @Le as the current endpoints @R and @L (after the operations)
    // by that logic, if we start with @Le, we just pick the max(@Le, @Re) and pick the other endpoint after to guarantee alternating comparison order

    // in other words, swap the picking of max(@Le, @Re) and min(@Le, @Re) for every 2 and take the remaining
    // we dont even always need to take L as the first

    // just take the max THEN the min (first 2) => take the min THEN take the max (next 2)
    //   ,>,?,<,?,>,?,<,?   <=== as long its not consecutively <,> over 5 elements its fine
    //              <,<,<,<,<, (worst with 3 remaining elements all having the same comparison)
    //                 ,?,>,?

    string ops;
    for (ll i = 0; i < n / 2 - 1; i += 2)
    { // => up to 3 remaining elements in the center
        // pick max first
        if (p[i] == max(p[i], p[n - i - 1]))
        { // p0 is the max
            ops += "LR";
        }
        else
        { // the other side is the max
            ops += "RL";
        }

        // alternate to picking min
        if (p[i + 1] == min(p[i + 1], p[n - (i + 1) - 1]))
        { // p0 is the min
            ops += "LR";
        }
        else
        { // the other side is the min
            ops += "RL";
        }
    }

    ll remaining = n % 4;
    if (remaining == 3)
    {
        // pick max first
        if (p[2 * (n / 4)] == max(p[2 * (n / 4)], p[n - (2 * (n / 4)) - 1]))
        { // p0 is the max
            ops += "LR";
        }
        else
        { // the other side is the max
            ops += "RL";
        }

        // last element, L==R
        ops += "R";
    }
    else if (remaining == 2)
    {
        // pick max first
        if (p[2 * (n / 4)] == max(p[2 * (n / 4)], p[n - (2 * (n / 4)) - 1]))
        { // p0 is the max
            ops += "LR";
        }
        else
        { // the other side is the max
            ops += "RL";
        }
    }
    else if (remaining == 1)
    { // last element, L==R
        ops += "R";
    }

    // ll L = 0;
    // ll R = n - 1;
    // for (auto c : ops)
    // {
    //     if (c == 'L')
    //     {
    //         DBG(p[L]);
    //         L++;
    //     }
    //     else
    //     {
    //         DBG(p[R]);
    //         R--;
    //     }
    //     DBG(" ");
    // }
    // DBGLN("");

    OUT(ops);
}