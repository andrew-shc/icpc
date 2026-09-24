#include <bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using vll = std::vector<ll>;
using dll = std::deque<ll>;
using pll = std::pair<ll, ll>;
using vpll = std::vector<pll>;

const ll NEG = (long long)-4e18;
const ll MOD = 1E9 + 7;

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

// O.1: each move must take an available unique r,c away (at least one, up to two)
//      O.1.1:

// per editorial

// combinatorically, missed a key observation: we do care about the orderings *within* each pair (since black/white ordering gives different config)
//                      BUT we do not care about the ordering of pairs themselves (i.e., 1st pair 2nd pair is same as 2nd pair 1st pair)
//                          hence, to remove the various ordering of the pairs (an abstraction of the individual underlying elements), we do (m-c)/2! (not (m-c)*2! or any other shenanigans)

// editorial presents another solution: DP
// ~~~~~  given dp[i] = # of configs given first i available rows/cols are taken (actually conceptually this means always 1 config)
// given dp[i] = # of configs given i remaining rows/cols (since the answer wants the total # of possible final config => think of it like DP on answer)
//                          ixi matrix remaining
//   dp[0] = 1
//   dp[1] = 1
// inductive step:
//      dp[i] = ????
//              given each additional ith row/cols, how much additional configs can we do?
//                  we can let the ith be another (r,r) (the default config that we can always do; *= 1 (do nothing))
//                  given the correction, we can have the ith pair with another row/col (WE DO NOT CARE WHICH ONE EXACTLY <= THATS THE INVARIANCE)
//                      what does this entail? we TAKE an additional previous element, not just adding a new element so i-2
//                          creating 2 free elements (1 new + 1 previous)
//                          since the new one is fixed at the ith since we're interested in the COMBINATIONS of UNIQUE PAIRING with the previous
//                              there are i-1 possibilities
//                          remember, this is assuming either first black second white or first white second black (but both options are available)
//                              add 2x factor for the ith (for the remaining i-1 elements, the color selection must be the opposite of the previous one)
//                                  ANOTHER KEY INVARIANCE: either black or white as the initial choice works
//                      = 2*(i-1)*dp[i-2]
//                          this is the solution... but can we confirm there is no overlapping issue like in the combinatoric case?
//                              well, first of all the ith is always a unique new choice, so the question is rather does it cover all options/combinations (ie completeness)?
//                                  well, given the ith, we can choose ALL the available option from 1st to the i-1th
//                                  if we're talking about future elements like i+1th, then i+1th will include the option to choose the current
//                                      so this is handled already (but the combinatoric case sort of includes the future term hence the issue arises there but not in DP which is strictly looks backwards)
//              overall, there are dp[i-1] configs if pick the (r,r) (or (c,c)) option preventing the computer to pick one
//                  AND with the an additional possibilities of pairing a previous element (WHICHEVER IT MAYBE, WE DONT CARE ABOUT THE SPECIFICS => invariance)
//             ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                  or, have the ith be paired with (i-1)th?
//                      does this guarantee completeness? what if we want to pair with the 1st???
//                          PER EDITORIAL, REMEMBER WHAT DP[i] REPRESENTS
//                              IT DOES NOT REPRESENT THE EXACT ROWS OR COLS, IT ONLY REPRESENTS THE NUMBER OF ROWS OR COLS (REMAINING)
//             ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                  we can have the ith be paired with one of the previous i-1 (call that k) (but that implies we forget everything about k+1 to i-1 (BAD))
//                      if the ith is even (1-index), (BAD)

void solve([[maybe_unused]] ll T)
{
    READ(n, k);
    // vpll moves;
    INC(i, k)
    {
        READ(r, c);
        // n--;
        // make sure to include the implied moves
        if (r == c)
        {
            n--;
        }
        else
        {
            n -= 2;
        }
        // moves.push_back({r, c});
    }

    vll dp(n + 1, 1);
    INC(i, n + 1)
    {
        if (i >= 2)
        {
            dp[i] = (dp[i - 1] % MOD + 2 * (i - 1) * (dp[i - 2] % MOD)) % MOD;
        }
    }
    // 1 1 1+2*(2-1)*1=3 3+2*(3-1)*1=7

    DBG_ITER(dp);

    // where n (0-index) represents the remaining open rows/cols and DP is in the order of as we increase the open rows/cols, how many configs can we have

    OUT(dp[n]);

    // ll configs = 1;

    // OUT(configs % MOD);
}