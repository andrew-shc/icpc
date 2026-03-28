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

// O.1: highest MEX is 3
//      O.1.1: MEX can only be 0,1,2,3
//          O.1.1.1: if MEX is 0 => 0 is not present => max-min=mex=0 => max=min => all 3 elements must be same (except 0)
//          O.1.1.2: if MEX is 1 => 1 is not present => max-min=mex=1 => max=1+min => all 3 elements must have a range of 1 [IMPOSSIBLE] (~~~~~except 0,1; i.e., >=2)
//                                                                                          ~~~~~~since range is 1, we have to go 2 or higher
//                                                                                          to have 0, you must include 1 => don't include 1, you can't have 0 => MEX must be 0
//          O.1.1.3: if MEX is 2 => 2 is not present => max-min=mex=2 => all 3 elements must be within a range of 2 (except 2; must include 0,1)
//                                                                                          however, including 0 requires 2 => impossible
//          O.1.1.4: if MEX is 3 => 3 is not present => all 3 elements be within a range of 3 (must include 0,1,2; except 3)
//                                                                                          impossible
//                  => all elements must be same (except 0)  [FINAL OBSERVATIOn]
//      O.1.2: the range of 3-subarray can only be at those 4 MEX values
// H.2: the test case suspiciously suggests all elements in the array must be the same
//          counter example:

// RE-SUMMARIZE (to condense this long observation for future problems)
// THE IDEA: a subarray of 3 can only have MEX up to 3, and the max-min difference must always include 0 for MEX>=1 so the difference must equal to MEX => impossible

void solve([[maybe_unused]] ll T)
{
    READ(n);
    READ_VLL(a, n);
    ll checker = -1;
    INC(i, n)
    {
        DBGLN(i, checker, a[i]);
        if (a[i] == 0)
        {
            OUT("NO");
            return;
        }

        if (checker == -1)
        {
            checker = a[i];
        }
        else if ((a[i] != checker && a[i] != -1))
        {
            OUT("NO");
            return;
        }
    }
    OUT("YES");
}