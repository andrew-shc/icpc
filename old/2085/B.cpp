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

// problem assumes the input always allows the creation of an array [0]
// ACTUALLY, given any input of n>=4, the creation of [0] is always possible

// O.1: mex(mex(array with 0)) = mex(something definitely not 0) = definitely 0

// strat
// if no zero, compute the mex in its entirety directly
// if one end is non-zero, group the n-1 element subarray (containing the end WITH ZERO) to produce a max of non-zero
//      then the remaining 2 non-zero element will produce a mex of 0
// if both side is zero, group the arrays into two halves => 2 non-zero element => zero

// strat (refined)
// if no zero, compute the mex on the entire array
// if both ends are zero, mex on two halves of the array => mex of zero on the two non-zeroes
// if an end is non-zero, then just find mex of the subarray that contains all 0s => mex of zero on two non-zeros

void solve([[maybe_unused]] ll T)
{
    READ(n);
    READ_VLL(a, n);

    bool l_zero = false;
    bool r_zero = false;
    ll zero1 = -1;
    ll zero2 = -1;
    bool no_zeroes = true;
    INC(i, n)
    {
        if (i == 0)
        {
            l_zero = a[i] == 0;
        }
        if (i == n - 1)
        {
            r_zero = a[i] == 0;
        }
        if (a[i] == 0)
        {
            no_zeroes = false;

            if (zero1 == -1)
            {
                zero1 = i;
            }
            else
            {
                zero2 = i;
            }
        }
    }

    if (no_zeroes)
    {
        OUT(1);
        OUT(1, n);
    }
    else if (l_zero && r_zero)
    {
        OUT(3);

        OUT(1, n / 2 + ((n % 2 == 1) ? 1 : 0)); // first half non-zero => 1 element
        OUT(1 + 1, n / 2 + 1);                  // second half non-zero
        OUT(1, 2);                              // both half non zero to produce a mex of 0
    }
    else if (zero1 != -1 && zero2 != -1)
    {
        OUT(2);

        OUT(zero1 + 1, zero2 + 1);   // first, find the mex of all all groups
        OUT(1, n - (zero2 - zero1)); // find the mex of all non-zero elements to produce 0
    }
    else
    { // zero1 gets filled first before zero2 (this is when there's only 1 zero)
        OUT(2);

        if (zero1 == n - 1)
        {
            OUT(zero1 + 0, zero1 + 1);
        }
        else
        {
            OUT(zero1 + 1, zero1 + 2);
        }
        OUT(1, n - 1);
    }
}