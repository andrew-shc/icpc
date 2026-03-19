#include <bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
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

// O.1: order matters in the elements of a
// O.2: <,> are relative operations, to minimize op.2 to reduce certain elements, we can increase their adjacent elements
//      O.2.1: we can freely run op1 for every even indices (prefix max, so it only improves)
// H.3: is the strat of running op1 for every even indices and executing op2 for odd indices optimal?
//      by intuition yes

void solve([[maybe_unused]] ll T)
{
    READ(n);
    READ_VLL(a, n);

    // greedy op1 on even indices (1-index) => odd indices
    // but remember prefix max on every elements

    ll prefix_max = a[0];
    INC(i, n)
    {
        prefix_max = max(prefix_max, a[i]);
        if (i % 2 == 1)
        {
            a[i] = prefix_max;
        }
    }

    ll min_op_2 = 0;
    for (int i = 0; i < n; i += 2)
    {         // every odd indices (under 1-index)
        ll m; // the condition to satisfy
        if (i == 0)
        {
            m = a[i + 1] - 1;
        }
        else if (i == n - 1)
        {
            m = a[i - 1] - 1;
        }
        else
        {
            // i in between
            m = min(a[i - 1], a[i + 1]) - 1;
        }

        DBGLN(a[i], m);
        min_op_2 += max(0ll, a[i] - m);
    }

    OUT(min_op_2);
}
