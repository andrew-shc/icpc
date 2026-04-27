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

// must be O(n) or O(nlogn)

// O.1: find all the steepest element, starting from the steepest start sweeping (replacing the neighbors value)
//          to maximize the reduction of the sum (it's fine if it starts to sweeping as the elements gets larger)
//      O.2.1: if the sweeping began to sweep elements that are smaller, check if the reduction is still optimal compared to all steepest area
//      O.2.2: however, if the 2nd steepest place is right before the steepest place, when does it makes sense to start sweeping from the 2nd steepest place?
//          it is complicated since sometimes its worth more to lose a sweep on the steepest and to sweep the up-front cost of the 2nd steepest and simultaneously sweep both the combined 1st and 2nd steepeset for one less sweep
//          dp???

// key idea, you can replace a value to a smaller value to increase the difference between some neighbors so that by the time
//          we sweep it its like a *combined effect* (which has an intrinsic tradeoff: better to sweep the steepest or sweep the neighbor-steepest to potentially sweep more *simultaneously/combined* in the later operations)

// per editorial... small value of k strongly suggests the solution is a DP (???????) and it is
// so its a DP...... (only looked at the first two sentences)

void solve([[maybe_unused]] ll T)
{
    READ(n, k);
    READ_VLL(a, n);

    ll dp[n + 1][k + 1] = {0};

    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= k; j++)
            dp[i][j] = 1e18;
    dp[0][0] = 0;

    // INC(i, n)
    // {
    //     if (i == 0)
    //     {
    //         dp[i][0] = a[i];
    //     }
    //     else
    //     {
    //         dp[i][0] = a[i] + dp[i - 1][0];
    //     }
    // }

    INC(i, n)
    {
        INC(j, k + 1)
        {
            ll mn = LLONG_MAX; // min over i to i+d
            INC(d, k + 1)
            { // number of ops to use
                if (i + d >= n || j + d > k)
                { // we want to keep when j+d==k
                    break;
                }

                mn = min(mn, a[i + d]);

                // d+1 for the one extra element that is the min and we dont need to use the op
                dp[i + d + 1][j + d] = min(dp[i + d + 1][j + d], dp[i][j] + (d + 1) * mn);
            }
        }
    }

    // min possible sum at most k ops
    ll ans = dp[n][0];
    // OUT("...../", ans);
    INC(j, k + 1)
    {
        DBGLN(".....", ans);
        ans = min(ans, dp[n][j]);
    }
    // ll ans = *min_element(dp[0], dp[n - 1]);
    // OUT_ITER(dp[0]);

    OUT(ans);
}