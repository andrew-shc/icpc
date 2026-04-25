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

// rephrase: for each m operations, pick an odd-lengthed interval to reverse, and mark index xi
//              then, find the min sum of all elements UNmarked
//              (i.e., try to mark the largest elements first to remove it)

// y can be 0 for NO-OP

// lets say you want to mark an index @j
//  so, we can always (try to) bring the next unmarked max to @j by finding the middle index u and setting y to appropriate length
//      to move the @max to @j
//  however, if the max has even amount of elements in between, it is impossible?

// because the interval is always odd-lengthed, the elements can only be swapped with odd amount of  elements in between
//  => elements on the even index stays on even index
//  => elements on the odd index stays on odd index

// combine this with you can swap any elements (given the constraints)
// we can find the min sum by removing largest elements in the even indices and odd indices

// remaining question: if an index is marked, can we always guarantee to mark a new unmarked next max element?
// because we are given any u,y, we can ARBITRARILY SELECT ANY ELEMENTS TO MARK
//      (SELECT the next nmarked next max and replace it with the current index)

// HOWEVER, IF THERE"S TOO MUCH ODD INDICES, THERE WILL ALWAYS BE EVEN INDICES INCLUDED

// strat:
/*
collect all the odd indices
collect all the even indices

 THERE ARE NEGATIVES KEEP THE NEGATIVES

 we also need an element mark on the evens and the odds (so we can pass the marked around for no-op)

*/

void solve([[maybe_unused]] ll T)
{
    READ(n, m);
    READ_VLL(a, n);
    READ_VLL(x, m);

    if (n == 1)
    { // since m>=1, it will always be marked so the min sum is 0
        OUT(0);
        return;
    }

    vll evens;
    vll odds;
    ll even_negs = 0; // we have to keep all negatives (hence, we need to maintain a min-length for elements to keep on the left)
    ll odd_negs = 0;
    INC(i, n)
    {
        if (i % 2 == 0)
        { // odd under 1-index
            odds.push_back(a[i]);
            if (a[i] < 0)
            {
                odd_negs++;
            }
        }
        else
        {
            evens.push_back(a[i]);
            if (a[i] < 0)
            {
                even_negs++;
            }
        }
    }

    // smallest to largest (ascending) and keep the smallest => min sum
    sort(evens.begin(), evens.end());
    sort(odds.begin(), odds.end());

    ll es = 0;
    ll os = 0;

    INC(i, m)
    {
        if (x[i] % 2 == 1)
        { // odd under 1-index (its already in 1-index)
            os++;
        }
        else
        {
            es++;
        }
    }

    ll min_sum = 0;

    if (even_negs == evens.size() && es > 0)
    { // if all are negatives (one op must exist m>1 so ops always exist), then pick the largest to remove
        min_sum -= evens.back();
    }
    if (odd_negs == odds.size() && os > 0)
    { // since evens and odds are entirely separate, if THERE EXISTS AND ODD INDICES OF COURSE
        min_sum -= odds.back();
    }

    INC(i, max(even_negs, (ll)(evens.size()) - es))
    {
        min_sum += evens[i];
    }
    INC(i, max(odd_negs, (ll)(odds.size()) - os))
    {
        min_sum += odds[i];
    }

    OUT(min_sum);
}