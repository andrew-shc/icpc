#include <bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef std::vector<ll> vll;
typedef std::deque<ll> dll;

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

// O.1: not 1st-order greedy (pick locally optimal choices based off currently accrued pancakes)
// O.2: at some point you want to sum the pancakes from all oven to find the max
// O.3: you want to maximize the background rate which can be realized at the end instead of choosing the 1st-order greedy
//      O.3.1: if they will all be increased by their amount, it's better to obtain the smallest one while simultaneously
//              have the largest increment increase (to be realized later) instead of taking the max at the current
//              second while the smallest one gets incremented (with occasional resets)
//                  because if you take the largest, you miss the opportunity to gain more by getting the ADDITIONAL
//                  smallest bits since you can always get the *large bits aggregated at the end*
//                      but when should you take the aggregated the large bits? for n==m? n>m? n<m?
//          since you always want the over with the larger rate to accrue the longest in the background before realization...
//              1 second  left => realize the largest                       m*a1
//              2 seconds left => realize the 2nd largest               (m-1)*a2
//              n seconds left => realize the nth largest (smallest)    (m-2)*an
//             >n seconds left => realize the nth largest (smallest)    (m-3)*an
// ^^ this important insight is only realized after a test case

// I need to check editorial for a more grounded intuition and proof....

// per editorial
// KEY INSIGHT: the amount of cakes from one particular oven depends only on the last time we pick it up
//              (ie picking it up earlier does not affect picking it up later, so we might as well just
//              pick it up later once only and conserve the extraneious picking up to really just anything actually)
//                  actually yea we just have to notice we only care about when the last pick up for
//                  any oven is (earlier pick up is independent and we dont care)

void solve([[maybe_unused]] ll T)
{
    READ(n, m);
    READ_VLL(a, n);

    sort(a.begin(), a.end()); // non-descending order

    ll cakes = 0;
    DEC(i, n - 1)
    {
        if ((m - (n - 1 - i)) <= 0)
        {
            break;
        }
        DBGLN(a[i], m - (n - 1 - i));
        cakes += a[i] * (m - (n - 1 - i));
    }

    DBGLN(cakes);

    // it's already included technically for the last element
    // since realizing at the end is the same as getting it everytime greedily

    // if (m > n)
    // {
    //     cakes += a[0] * (m - n); // recall the smallest wouldve been included at least once in previous loop
    // }

    OUT(cakes);
}