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
void cout_vars(Args &...args)
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

// 2
// 3
// 6

void solve([[maybe_unused]] ll T)
{
    // observations:
    // O.1: pi = i ^ pj <==> pj = i ^ pi     // (pj == ji)
    // O.2: (per editorial) for i=n-1, j must be n (pn)
    // O.3: (per editorial) pj=pn=1 (reducing the possibilities => requires engineering the permutation)
    //  (which the question asks for implicitly actually)

    // O.4: (per O.3 & O.1) at index 2k, 2k^1=2k+1=p_{2k}; at index 2k+1, (2k+1)^1=2k=p_{2k+1}

    // in summary, we only care about pn=1 and simplify condition to only j=n

    READ(n);
    vll p(n, 0);
    p[n - 1] = 1; // per question, we dont care about pn (and 1 is the only value
    //               that would not be generated from this scheme)
    // same reason as above and p[0] would've been 0 if we just followed the formula above
    if (n % 2)
    {                 // odd
        p[0] = n - 1; // the previous even would've generated n (remember, keep values unique)
    }
    else
    {             // even
        p[0] = n; // the previous odd would've generated n-2 (and the even before that generates n-1)
    }
    for (int i = 2; i <= n - 1; i++)
    {
        if (i % 2 == 0)
        {
            p[i - 1] = i + 1;
        }
        else
        {
            p[i - 1] = i - 1;
        }
    }

    OUT_ITER(p);

    // READ(n);

    // vll p(n, 0);
    // for (int i = 0; i < n; i++)
    // {
    //     // p[i] = (i + 2) % n + 1;
    //     p[i] = i + 1;
    // }
    // // if (T == 1)
    // // {
    // //     p[0] = 1;
    // //     p[1] = 2;
    // //     p[2] = 3;
    // //     p[3] = 4;
    // // }
    // // if (T == 2)
    // // {
    // //     p[0] = 2;
    // //     p[1] = 1;
    // //     p[2] = 3;
    // //     p[3] = 4;
    // // }
    // // if (T == 3)
    // // {
    // //     p[0] = 2;
    // //     p[1] = 3;
    // //     p[2] = 1;
    // //     p[3] = 4;
    // // }
    // // if (T == 4)
    // // {
    // //     p[0] = 2;
    // //     p[1] = 3;
    // //     p[2] = 4;
    // //     p[3] = 1;
    // // }

    // DBG_ITER(p);

    // vector<vll> j;
    // for (int pi = 2; pi <= n - 1; pi++)
    // {
    //     vll jpi; // valid indices to place where ji >= i given current pi
    //     for (int i = 1; i <= n; i++)
    //     {
    //         ll ji = i ^ pi;
    //         // DBGLN(i, pi, ji);
    //         if (ji >= i)
    //         {
    //             // DBGLN("!");
    //             jpi.push_back(i);
    //         }
    //     }

    //     j.push_back(jpi);
    // }

    // for (int pi = 2; pi <= n - 1; pi++)
    // {
    //     DBG(pi, "= ");
    //     DBG_ITER(j[pi - 2]);
    // }
}