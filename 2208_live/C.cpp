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

// at what point *c > *(1-p/100)?
// 100(1-c)=p
// c == (1-p/100) does nothings

// c > 1-p/100 => 1-c > p/100 => 100(1-c) > p

// ~~~~~ WE ARE NOT DIVIDING (1-p/100)

// S vs Sc(1-p/100)
// c(1-p/100) > 1
// c-cp/100 > 1
// c > 1+cp/100
// 100c > 100+cp

// ~~~~~~~~~~~~~~~~~~ ^^^^ misunderstood

// MAJOR OBSERVATION (O.3): adding a term c (ie, completing a task) affects all the fractions AFTER
//     and ONLY AFTER the current task (via the current p) => BACKWARDS DP???
//      O.3.1: doesn't this imply we always pick the last term? YES!! b/c it doesn't affect later terms (b/c it
//              doesn't have a later term to affect via p)

void solve([[maybe_unused]] ll T)
{
    READ(n);
    vll c;
    vll p;
    INC(i, n)
    {
        ll ci, pi;
        cin >> ci >> pi;
        c.push_back(ci);
        p.push_back(pi);
    }

    ld bdp[n];

    bdp[n - 1] = c[n - 1];
    DEC(i, n - 2)
    {
        bdp[i] = max(bdp[i + 1], (ld)c[i] + (1.L - ((ld)p[i]) / 100.L) * bdp[i + 1]);
    }

    // double s = 1.;
    // INC(i, n)
    // {
    //     // if (100 * (1 - c[i]) > p[i])
    //     // {
    //     //     s *= c[i]
    //     // }
    //     if ((100 * c[i]) > (100 + c[i] * p[i]))
    //     {
    //         s *= (1. - (double)p[i] / 100.);
    //     }
    // }

    OUT(bdp[0]);
}