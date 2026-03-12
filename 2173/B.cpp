#include <bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;
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
    ((std::cout << args << " "), ...) << std::endl;
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

void solve([[maybe_unused]] ll T)
{
    READ(n);
    READ_VLL(a, n);
    READ_VLL(b, n);

    // greedy since each input does not care about the history (only the immediate previous) (ie markovian)
    //      since each input like affects the delta, (independent of the previous)

    // however, there's an option to choose  b twice (ie, double negative k == +k)
    // so greedy at 2-level history?

    // forget about this notion of greedy... dp? forward backward? (decision depends only on history/previous
    // due to more than possibilities of operating k (negating/identity))
    //  forward?

    // k - a - a - a - a - a
    // (-1)^x k - b + b - b + b

    // quadratic from the constraints of n?

    // choose red vs choose blue (both decision are always available)
    // ll dp[n + 1][n + 1];
    // dp[0][0] = 0;
    // INC(i, n + 1)
    // {
    //     INC(j, n + 1)
    //     {
    //         if (i + j - 2 >= n)
    //         {
    //             continue;
    //         }
    //         if (i > 0 && j == 0)
    //         {
    //             // no choose blue
    //             dp[i][j] = dp[i - 1][j] - a[i - 1];
    //         }
    //         else if (i == 0 && j > 0)
    //         {
    //             // no choose red
    //             dp[i][j] = b[j - 1] - dp[i][j - 1];
    //         }
    //         else if (i > 0 || j > 0)
    //         {
    //             dp[i][j] = max(dp[i - 1][j] - a[i + j - 2], b[i + j - 2] - dp[i][j - 1]);
    //         }
    //     }
    // }

    // DBGLN(T);
    // INC(i, n + 1)
    // {
    //     DBG_ITER(dp[i]);
    // }

    // ll k = 0;
    // INC(i, n)
    // {
    //     if (i < n - 1)
    //     {
    //         // k = max(k - a[i] - a[i + 1], b[i] - k - a[i + 1], b[i + 1] - b[i] + k, );

    //         // in 2 steps, it will be the same again
    //         ll aa = k - a[i] - a[i + 1];
    //         ll ab = b[i + 1] - k + a[i];
    //         ll ba = b[i] - k - a[i + 1];
    //         ll bb = b[i + 1] - b[i] + k;
    //         k = max(max(max(aa, ab), ba), bb);

    //         i += 2;

    //         // k = max(max(max(
    //         //                 0,  // a a
    //         //                 0), // a b
    //         //             0),     // b a
    //         //         0);         // b b
    //     }
    //     else
    //     {
    //         // i == n-1
    //         k = max(k - a[i], b[i] - k);
    //     }
    // }

    // per editorial

    // MAJOR OBSERVATION/INSIGHT:
    //  simple idea => negative flips max/min operation
    //  at every point in time (every round/game), we only care about the overall min/max of the history
    //  (no more = no complex 2D DP or i-2/i+2 checking) NO LESS (just looking at the prev. element not enough)
    //  which is used in the next round
    //  each min/max can thought of like the two policies to choose which action/operation
    //     where these two policies at the end of the day just reduce to deciding which operation to select
    //     (no extra operations there) and just to expand a bit on what possible values might exist before

    // another key insight: notice the max/min flips for selecting b when we negate the original k value
    //  this can be thought of as trying to pull the maxk and mink as far apart at each iteration (and implicitly
    //  temporarily stores these operations until used when selected)

    // SUMMARY: min/max are two *ways* of selecting red/blue (the operations). minkg and maxkg merely
    //   IMPLICITLY stores these operations until used (and they select at most one operation) and we only select
    //   maxkg at the end.

    ll minkg = 0;
    ll maxkg = 0;
    INC(i, n)
    {
        ll mink = min(minkg - a[i], b[i] - maxkg); // implicitly stores the ops. that selected the smallest k
        ll maxk = max(maxkg - a[i], b[i] - minkg); // implicitly stores the ops. that selected the largest k

        minkg = mink;
        maxkg = maxk;
    }

    OUT(maxkg);
}