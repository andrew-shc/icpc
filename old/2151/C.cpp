#include <bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
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

// REPHRASE:
//      - every moments (the seconds it detected activity) are unique
//      - given k, determine max possible TOTAL stay time (for all visitors' stay time summed)

// O.1: the more overlaps, the more optimal it is => find a config where we overlap the visitors
//      as much as possible
//          => this is just > > > < < < like a pancake (the strat)
// Q.1: how to make the strat O(n)?
//      1. find the sum of k=1
//      2. for k=2, we sum the diff of last and the first
//              a b c d e f g h
//                b c d e f g
//              b-a+d-c+f-e+h-g --> c-b+e-d+g-f => -b,+g
//              all odd elements gets added and all even elements gets subtracted (<-- odd/even flipped for this statement)
//              for each increment of k, subtract the last and add the first and negate odd sums and even sums

void solve([[maybe_unused]] ll T)
{
    READ(n);
    READ_VLL(a, 2 * n);

    ll evens = 0;
    ll odds = 0;

    for (int i = 0; i < 2 * n; i += 2)
    {
        odds += a[i]; // under 1-index
    }
    for (int i = 1; i < 2 * n; i += 2)
    {
        evens += a[i]; // under 1-index
    }

    vll r;
    ll s = 0;
    INC(k, n)
    {
        // evens - odds
        // evens -= - a[n-k-1], odds -= a[k];  odds - evens

        if (k % 2 == 0)
        {
            r.push_back(evens - odds + s);
            evens -= a[2 * n - k - 1];
            odds -= a[k];
        }
        else
        {
            r.push_back(odds - evens + s);
            evens -= a[k];
            odds -= a[2 * n - k - 1];
        }
        s += a[2 * n - k - 1] - a[k];
    }
    OUT_ITER(r);
}