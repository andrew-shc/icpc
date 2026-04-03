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

// IMPORTANT REPHRASE: SUBSEQUENCE (any characters can be removed; not just at the end)
// MISUNDERSTANDING?: NUMBER OF SUBSEQUENCE IS HOW MANY IT CAN BE UNIQUELY GENERATED TO THE TARGET SUBSEQ
//          FOR ANY UNIQUE DELETION OF CHARACTERS??
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
// there's an easier way.... just do all k 1s in the beginning
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

// ^^^ this is literally part of the solution

// 1010
// 10111111110
// 0
// 1
// 00000
// 10000
// 10100
// 10110  <-- any amount of 1s in between
// 11110
// 11111

void solve([[maybe_unused]] ll T)
{
    READ(n, k);

    string s(n, '0');

    INC(i, k)
    {
        s[i] = '1';
    }

    // if (k == 0)
    // {
    //     // pass
    // }
    // else if (k == 1)
    // {
    //     s[0] = '1';
    // }
    // else if (k == 2)
    // {
    //     // place 2 1's in the beginning (to satisfy the case of n==2)

    //     s[0] = '1';
    //     s[1] = '1';
    // }
    // else if (k < n - 1)
    // {
    //     s[0] = '1';
    //     INC(i, k - 1)
    //     {
    //         s[2 + i] = '1';
    //     }
    // }
    // else if (k < n)
    // {
    //     INC(i, n - 1)
    //     {
    //         s[i] = '1';
    //     }
    // }
    // else if (k == n)
    // {
    //     INC(i, n)
    //     {
    //         s[i] = '1';
    //     }
    // }

    OUT(s);
}