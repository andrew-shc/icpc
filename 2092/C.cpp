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

// O.1: if we find any pair-wise odd, apply the operation to maximize one of the pair
//      O.1.1: the maximized element will still be odd
//      O.1.2: for a pair-wise to be odd, one has to be even and the other has to be odd
//      O.1.3: if there are 1 odd, the odd can infect every even to sum everything up
//      O.1.4: if there are 2 odd, pick the larger odd to infect every other even to produce a single largest element
//                  (the smaller odd can't be used)
//          HOWEVER, consider the following testcase (THANKS AGAIN TO THE TEST CASE)
//              5 4 3 2  9
//              4 4 3 3  9
//              0 0 3 3 17
//              2 2 1 1 17
//              0 0 1 1 21
// O.2: if there are 2 odds, move the special odd-1 to the smallest even (effectively, from the original smaller odd,
//          to the smallest odd with the original becoming even which could be a larger even)
//          then, have the larger odd infect every other even (including the original odd turned-to mediocre even)
//              then, have the original smallest even turned-to smallest odd into 1s and the even part moved out to be re-integrated into the max el.

// strat:
//      1. keep the largest odd as the max el.
//      2. pair every larger odd to a smaller even (to transfer the odd-1 to a smaller number)
//          => effectively, given a pair of odd and even (excluding the max el.), pick max(odd-1,even) and leave min(odd-1,even)+1 which we reintegrate with min(odd-1,even) leaving 1

// strat (refined)
//      1. answer is largest odd + k (odd-1+even) s.t. odd & even are the odd-even pairs that contains k largest odd and k largest even
//              where k is min(# of odds, # of even)

// O.3: if there is a 0 (or any even) in the tower, every odd can have its odd-1 removed by splitting into 1 (for its original) and the even part at the 0-el
//          which serves as the intermediate cargo to the final max el.
// O.4: an odd outside the picked max el. odd will always have a 1 remaining (since we cannot add two odds, we can merge the 2 extra-1s to form a even to merge into the final odd)

// strat (refined II):
//  1. if an even slot exists, any other odds can transit through this even slot to maximize the element while the extra 1 is left behind
//          since we only want the even part
//  2. if an even slot does not exist, all the odds are locked behind
//  3. if only even present, we cannot add anything.

void solve([[maybe_unused]] ll T)
{
    READ(n);
    READ_VLL(a, n);

    ll k_odds = 0;
    ll odds = 0;
    ll evens = 0;
    bool even_slot = false;
    bool odd_slot = false;
    ll max_odd = 0;
    ll max_even = 0;
    INC(i, n)
    {
        if (a[i] % 2 == 0)
        {
            evens += a[i];
            max_even = max(max_even, a[i]);
            even_slot = true;
        }
        else
        {
            odds += a[i];
            max_odd = max(max_odd, a[i]);
            k_odds++;
            odd_slot = true;
        }
    }

    if (even_slot && odd_slot)
    {
        // we can sum (other odds transited through any one of the even slots)
        //  and optimally staying at one of the odds (no need to leave an extra 1 out)
        OUT(evens + odds - (k_odds - 1));
    }
    else if (!even_slot && odd_slot)
    {
        // max odd
        OUT(max_odd);
    }
    else
    { // even_slot && !odd_slot
        // max even
        OUT(max_even);
    }
}