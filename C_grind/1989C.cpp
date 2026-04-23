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

void solve([[maybe_unused]] ll T)
{
    READ(n);
    READ_VLL(a, n);
    READ_VLL(b, n);

    ll first = 0;
    ll second = 0;
    ll all_neg = 0; // these are up to global decision
    ll all_pos = 0;
    INC(i, n)
    {
        if (a[i] == 1 && b[i] == 1)
        {
            all_pos++;
        }
        else if (a[i] == -1 && b[i] == -1)
        {
            all_neg++;
        }
        // at least 0,1 is present in at least either a or b after this point
        else if (a[i] >= b[i])
        {
            first += a[i];
        }
        else
        { // a[i] < b[i]
            second += b[i];
        }
    }

    DBGLN(first, second, all_neg, all_pos);

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // key observation: we do not always want to put negatives in one of them and positives in the other => optimally, cancel the negatives with positives out
    //      at each review => just subtract them
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // updated observation helped from a test case: yea putting negatives on the mn and positive on the mx does not help
    //      but swapping it helps (ie, negatives on the mx and positive on the mn) to reduce the prominence by 2
    //          since this splits the cancellation and allows raw increase on the min (since min is only thing we care)

    ll prominence = abs(first - second);

    // first do the strat first

    ll &mx1 = (first < second) ? second : first;
    ll &mn1 = (first < second) ? first : second;

    ll reduction = min(min(all_neg, all_pos), prominence / 2); // how much prominence can be reduced in 2s by pairing all_neg,all_pos to mx,mn respectively
    all_neg -= reduction;
    all_pos -= reduction;
    mx1 -= reduction;
    mn1 += reduction;
    prominence -= reduction * 2;

    ll all_net = all_pos - all_neg;

    if (all_net < 0)
    {
        ll &mx = (first < second) ? second : first;
        mx -= min(prominence, -all_net);
        all_net += min(prominence, -all_net);
        // ~~~~~~~~~~~~~~~ if odd amount still remains, the odd does not change the answer
        // ok thought today is the day you can skip some but no, when we go negative it matters

        // forgot this is all_negatives, so we subtract
        first -= (-all_net) / 2;
        second -= (-all_net) / 2;
        if ((-all_net) % 2 == 1)
            first--; // pick either
    }
    else if (all_net > 0)
    {
        ll &mn = (first < second) ? first : second;
        mn += min(prominence, all_net);
        all_net -= min(prominence, all_net);

        first += all_net / 2;
        second += all_net / 2;
        // ~~~~~~~~~~~~~~~~~~~~~ this does not matter for odd amounts remaining
        // ~~~~~~~~~ still matters if first and second was odd (we did not guarantee ~~~~~)
    }

    OUT(min(first, second));
}

/*
HELPED BY TEST CASE 4
problem: if there exists some prominence and there exists all_negs and all_pos => DO NOT CANCEL THEM OUT IMMEDIATELY
            => instead put all_negs on the max so we can put all_pos on the min
            => we should cancel them ONLY WHEN THERE NO LONGER EXISTS A PROMINENCE / DIFFERENCE

                - the effect of doing this reduces the prominence by 2

strat:
1. do the all_neg on mx and all_pos on mn (reduces prominence by 2, if 1 left over == same effect so we just leave it to step #2)
2. cancel the remaining negs out with the pos
3. if neg still present => do it, if pos still present => do it

*/
