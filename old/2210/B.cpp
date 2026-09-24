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

// rephrase, you only go forward in each chair one by one (no skipping chairs)
//          => if a chair is marked, all the remaining chair is inaccessible (game immediately ends)
// you want to find the largest group of *conseuctive* elements that references later elements before it refers back to itself
// since this is a permutation, this means a group of elements that does not contain its own index

// but we can always ignore indices that refer back to itself
// but we cant if the indices is refered by a previous index
// so each time you make the group larger, there's more excluded index included from the earlier group

// two pointers?

// marking future (there's a limit) => at most n-1
// marking past/current (that's fine)

// this suggests we are limited by the largest marking future? (but we can choose not to mark the largest future)

// for every marking future, there's at least ONE that marks backward (which we can always take the better option of backward)
//      there's always an element that marks backward at the end of future markers (so even if we take the future, by default taking backwards helps and simplifies the solution)

void solve([[maybe_unused]] ll T)
{
    READ(n);
    READ_VLL(p, n);

    ll cnt = 0;
    INC(i, n)
    {
        if (p[i] <= i + 1)
        {
            cnt++;
        }
    }
    OUT(cnt);

    // ll max_cnt = 0;
    // ll cur_cnt = 0;
    // // 0-indexed
    // ll starting_ind = 0; // no ending index thats just the current one always

    // INC(i, n)
    // {
    //     if (starting_ind <= p[i] <= i)
    //     {
    //         start
    //     }
    // }
}