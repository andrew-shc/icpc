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

// rephrase: boolean masking on the strip with matching color resulting in 0 penalty and
//              opposite matching color resulting in ai penalty

// smells like dp, or knapsack dp. BUT, there's a monotonicity-ness with
//      how we can only color cells blue (so only more blues after)

// comprehension problem (bruh; thankfully caught this error early)
//      MAXIMUM PENALTY refers to single-point of maximum penalty from incorrect painting for any given single cell
//          => the answer is NOT expecting a SUM OF PENALTY
//          => so even less likely to be a dp?
//  RECALL, WE ONLY CARE ABOUT *MAX* PENALTY

// O.1: if # of consecutive groups of Bs <= k:     => 0 penalty
//      O.1.1: think in terms of groups of reds and blues
//          (since if we can color a blue, might as well color the entire blue)
//          (  and if we need to color another blue within an operation, we have to skip through an entire groups of red)
//      O.1.2: we can always ignore red groups on the left or right end
// O.2: think in terms of blue groups and red groups each with a corresponding max penalty
// O.3: if many reds have high penalty and blues have low penalty, it is better to avoid extending limited blue groups
//          (limited by k) into larger groups over red groups with high penalty
//      O.3.1: since the operation is literally coloring in blue, there's no point to reserve some operations to allow red to "connect"??
//                  (trying to break a bad intuition forming)
//          O.3.1.1: always greedily use up all the k operations to at least paint as much necessary cells to blue as possible
//      O.3.2: per the greediness, one should be careful on where the red groups with high penalties are
// O.4: RECALL, this is by max penalty
//          if there's a single max penalty, we always apply (B) or ignore (R)
//          if there's multiple max penalty, always try to satisfy them
//              (if the maxes occur on the colors with this pattern for k=2, BRBRBRB, then the min must be the max)
//              as in if there are >k groups of blues => the max is the max then
//              if <=k groups of blues => the max is below the current specified max then
//              we have k1 remaining degrees of freedom to specify where the operation should go on the blues
//          if there's a single next max penalty, if its in un-operated R or operated B, leave it be
//                                                if its in operated R or un-operated B,
//                                                    operated R => can we split the B? (uses k1 remaining DoF)
//                                                 un-operated B => can we add a B? (uses k1 remaining DoF)
//                                         if we do not have enough k's (specifically k1==0),
//                                              whatever we do, given the groups constrained on the max max
//                                              the next max max (here) must be included
//
// # denotes forced operation; - denotes forced NO operation
//
//                  15941950959714893
//                  BRBRBRBRBRBRBRBRB
//                    #  -  # #    -     (requires k=2 for penalty <9)
//                  #####-#########-
// go down a level
//                                #      (its in an operated B => leave it be)
//                  #####-#########-
// --
//                             -         (7 is on an operated R => can we split the B?)
//                  #####-#####-###-       to split the B, do we have enough k groups? if not, return the current ma
// --
//                   -    #  -           (5 has 2 operated R and 1 operated B)
//                                         2 operated R, even within the same blue, still requires 2 additional groups
//                  #-###-###-#-###-
//
//                    ..... there has to be a simpler way?

// editorial & rating check
// its a 1500!

// strat:
// let x = max(a)/2
// given x, we replace the array with ? for ai<=x (we dont care)
//      if ai is blue and a{i-1} was (? or R) => 1 op required                 O(n)!!!!!!

// THE FUCKING PROBLEM REFERS "FIRST TYPE" AS AT OR BELOW THE PENALTY, NOT THE RED COLORING
// THIS IS THE MOST CONFUSING QUESTION AND EDITORIAL EVER

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// if ai>x, ensure the element is colored correctly (to ensure the penalty is at x or below)
//      => if ai is red or a{i-1}>x, we dont care
//      => if ai is blue and a{i-1}<=x, that's 1 operation required
//              however, if the previous was blue also and the current ai is blue, we dont need that operation...
//                       NO, its if the previous op was red yet above the penalty won't get counted

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// O.2: starting with a single group of blue
//          if we add another group of blue (separated by a group of red which we also have to include)
//              if the # of blue groups <= k: 0 penalty
//              if the # of blue groups  > k: tradeoffs, sacrifices
//                  given current k+1 blue groups and k red groups
//                      since we only care about MAX PENALTY and in terms of GROUPS:
//                          attach the max penalty to each group

// ~~~~~~~~~~~~~~~~~~~~~~~~~
// O.2: let's say given a sub-painting of 1..i, if there's suddenly a new group of Bs (making it >k)
//          - we want to find the config that minimizes the max-penalty
//          - optimally, there will be a group that
// O.3 (redo O.2): let's say we start with a single group of blue
//      everytime we add

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//          - should we include this new group of B? at a cost of group of red before it?
//          - or, we should not include this group of B to be penalized?

// ~~~~~~
//  H.2: consider dp[i] where dp[i] refers to the maximum penalty possible given a sub-painting of 1..i
//

void solve([[maybe_unused]] ll T)
{
    READ(n, k);
    READ_S(s);
    READ_VLL(a, n);

    ll high = *max_element(a.begin(), a.end());
    ll low = 0; // *min_element(a.begin(), a.end());
    ll res;
    while (low <= high)
    {
        ll x = (high + low) / 2;
        // if the x is the very last leaf branch, the x is bad and technically we want the last good state
        // this is an edge case in binary search that should be handled correctly next time

        char prev = 'R'; // if we do index, we have to care about setting an initial index, but with this
                         // abstraction, we dont have to think about all the edge cases
        ll ops = 0;
        INC(i, n)
        {
            if (a[i] > x)
            {
                if (s[i] == 'B' && prev == 'R')
                { // if the current is blue and the previous was red (given the requirement of correct coloring (since a[i]>x),
                    // we need 1op)
                    ops++;
                }
                prev = s[i];
            }

            // if (i == 0)
            // {
            //     continue;
            // }

            // if (s[i] == 'B' && s[i] > x && s[i - 1] == 'R')
            // { // requires 1 ops to color in a new group of blues if the current is blue
            //     //  (and above the penalty => requires correct coloring)
            //     //  and previously was red (regardless whether it was above the penalty or not)
            //     // this suggests we always avoid coloring red??????
            //     ops--;
            // }
            // else
            // {
            // }
        }

        if (ops <= k)
        { // k supports the number of current operations => minimize / go down (more penalities will be filtered / increasing operations)
            high = x - 1;
            res = x;
        }
        else
        { // k not enough to support the current number of operations => go up (less penalities will be filtered / increasing operations)
            low = x + 1;
        }
    }

    OUT(res);
}