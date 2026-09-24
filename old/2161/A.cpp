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

// X and D same across all contests

// always go up (since X,D same, forgoing div2 for div1 does not help)
// div2, max rating = X-1+D
// div1, max rating = R+D
// if R0<X => min is X-1+D
// if R0>=X => R0

// R + (# of div1)*D
// if div2 exists, try to maximize up to X-1+D
// if R0<X
// if #div2 == 1: R0+D
// if #div2 > 1: min([(X-1)-R0]/D X-1)+D (once X-1, then do +D)
//      i.e., (#div2)*[(X-1)-R0]/D

// #div2needed = ceil([(X-1)-R0]/D)+1  to reach X-1+D
// or else = R0+#div2*D
// over all +#div1*D

// output is # OF RATED ROUNDS not max score

// contests are ordered => JUST SIMULATE (DONT BE ELEGANT, ESP IN COMPETITION
// JUST USE KEY OBSERVATION = DONT FORGO Div1 for Div2
// always pick div1 (so focus on counting div2 to maximize )

// wait wait wait we want to maximize number of rated rounds...

void solve([[maybe_unused]] ll T)
{
    READ(R0, X, D, n);
    READ_S(s);

    // ll ndiv2 = 0;
    // ll ndiv1 = 0;
    ll rated_rounds = 0;
    for (auto &c : s)
    {
        if (c == '1')
        {
            // ndiv1++;
            rated_rounds++;
            R0 = max(0ll, R0 - D);
        }
        else if (R0 < X)
        {
            // ndiv2++;
            rated_rounds++;

            R0 = max(0LL, R0 - D);
        }
    }

    OUT(rated_rounds);

    // // DBGLN(R0, X);

    // ll rated_rounds = ndiv1;
    // if (R0 < X) // as long it can be rated (we dont care if X <= R0 < X-1+D because if it needs a div1 to forgo but might as well just do div1 directly)
    // {
    //     if ((X - 1 - R0 + D - 1) / D + 1 >= ndiv2)
    //     {
    //         R0 = X - 1 + D;
    //         rated_rounds += ndiv2;
    //     }
    //     else
    //     {
    //         R0 += ndiv2 * D; // < X-1+D
    //         rated_rounds += (X - 1 - R0 + D - 1) / D + 1;
    //     }
    // }

    // OUT(rated_rounds);
}