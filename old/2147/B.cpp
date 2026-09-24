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

// the question becomes how to arrange them?
// REMEMBER the distance can be multiples of the element itself away (not exactly the element's value itself)

// H.1: strat 1 where we add the largest to smallest odd on the left (doesnt work, there's a forced intersection)
//          n=10
//          .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .
//          9  7  5  3  1  3  5  7  9  1  10 8  6  4  2  2  4  6  8  10     (inclusive distance / counts) ~~~~~`
//          9                          10 8  6  4  2  1  2  4  6  8  10     (exclusive distance / true distance) [EITHER WAY DOESNT WORK]
//                                    9^

// O.1: the largest number n can only be placed one multiples of each other
// O.2: to pack the larger numbers tightly as possible, we should let them overlap as much as possible first

//          .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .
//          10    9     8  5  7     6     10 9  8  7  6  5 x4  3  2  1   xxxxx

// try the following strat:
// H.1:
//      evens on n+1 left side
//      largest odd in the middle with the corresponding largest odd on the odd side
//      odd side wrap with 2nd largest to smallest
//      make the one empty space right and the final be 1

// per editorial (after AC)

// after adding n @i & @n+1, we can place two numbers at 2 multiples across the center 2nd n position (as the pivot)
//          this is close to O.1 where we observe every other number except n can be placed at >=3 valid locations

void solve([[maybe_unused]] ll T)
{
    READ(n);

    if (n == 1)
    {
        OUT(1, 1);
        return;
    }
    else if (n == 2)
    {
        OUT(2, 1, 2, 1);
        return;
    }
    else if (n == 3)
    {
        OUT(2, 3, 2, 1, 3, 1);
        return;
    }

    vll a(2 * n, 0);
    ll largest_odd = n % 2 == 1 ? n : n - 1;
    for (ll i = 1; i <= n; i++)
    {
        if (i % 2 == 0)
        {
            a[n / 2 - i / 2] = i;
            a[n / 2 + i / 2] = i;
        }
        else
        {
            if (i == 1)
            {
                a[n / 2 + largest_odd + 1] = 1; // gaurantees to be at most 3n/2+1
                if (n % 2 == 1)
                {
                    a[n] = 1; // when n is odd, the even doesnt increase giving us a space right after
                }
                else
                {
                    a[2 * n - 1] = 1;
                }
            }
            else if (i == largest_odd)
            {
                a[n / 2] = largest_odd;
                a[n / 2 + largest_odd] = largest_odd;
            }
            else
            { // regular odds
                a[n / 2 + largest_odd - i / 2] = i;
                a[n / 2 + largest_odd + i / 2 + 1] = i;
            }
        }
    }

    OUT_ITER(a);
}