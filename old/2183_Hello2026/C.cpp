#include <bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;
typedef std::vector<ll> vll;
typedef std::deque<ll> dll;

const long long NEG = (long long)-4e18;

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
    ((std::cout << args << " "), ...) << std::endl;
}
#define OUT(...) \
    cout_vars(__VA_ARGS__)

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
    ios_base::sync_with_stdio(false);
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

/*
6
3 1 3
3 3 2
4 2 2
3 2 1
4 3 3
7 7 4

*/

void solve([[maybe_unused]] ll T)
{
    READ(n, m, k);

    // per editorial

    // by proof, a+b+max(a,b)-1 <= m days to fit a,b
    // use two pointers (with math, O(1) is definitely possible)

    // assume we have just the base
    ll a = 0; // left: <= k-1
    ll b = 0; // right <= n-k
    // ll global_m = 0;

    bool flip = true;
    while (a < k - 1 || b < n - k)
    {
        if (flip && a < k - 1)
        {
            a++;
        }
        else if (b < n - k)
        {
            b++;
        }
        flip = !flip;

        ll local_m = a + b + max(a, b) - 1;

        // DBGLN(a, b, k - 1, n - k, local_m, m);

        if (local_m > m)
        {
            // restricted by m
            OUT(a + b + 1 - 1); // +1 for the base, -1 for removing the pre-emptive increment
            return;
        }
        // else
        // {
        //     global_m = local_m;
        // }
    }

    // when m is so much to allow greater a,b
    OUT(a + b + 1); // +1 for the base, (no -1 since the condition is first checked before incrementing at each it)
    return;

    // if (m >= 2 * (n - 1))  << per editorial, there's a better absolute lower bounds
    // { // upper limit of days to maximize maxf
    //     OUT(n);
    //     return;
    // }

    // assuming the strat is
    //  1st. 1/3 of doing nothing
    //  2nd. 1/3 of moving the troops (all at once like batch processing) to the side with the largest
    //  3rd. 1/3 of moving the remaining newly drafted troops to the smaller side

    // works when k is middle (ie, both sides are equal length)
    // what if one side is longer? => pick the larger side (while fitting the 1/3 model) to ensure
    //   when we move the troops to the shorter side we dont have to wait for drafting
    //   (drafting happens at k regardless of troop movement)
    //      whereas doing it on the shorter side incur additional waiting days for the longer side or
    //      expect inefficient troop movement (ie pre-maturely moving troops)
    // if only one side is feasible (ie k=1 or k=n), this strat still works (the most efficient)
    //    - know that moving troops back is inefficient/non-optimal (always keep or move troops away k)
    //    - prematurely moving troops away at home base k is sub-optimal (esp when we can merge)

    /////// ignore
    // if the longest side is smaller than or equal to m/3 (we dont care about the smaller side)
    //      [2*(m+2)]/3
    // if the longest side is greater than m/3
    ///////

    // [2*(m+2)]/3

    ll maxf = 0;

    OUT(maxf);
}