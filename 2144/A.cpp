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

// modular arithmetic (mod summation): sum of mod = mod of sum
// brute force? brute force => 3 loops => no brute force

// O.1: if all 3 numbers are different or the same => we don't want 2 numbers to be the same
//          => exhaustively find if any three subarray sums to the same???? (errrrr n^3???)

// probably brute force

// n^3 or n^2????
// should be n^2 bruh
// iterate l and iterate r via prefix sum

// per editorial

// MAJOR OBSERVATION: (s1+s2+s3)%3 == 0 WHENEVER s1,s2,s3 are ALL same or three-way unique!!!
//              (know number theory next time or practice more on # theory :vomit:)
// => get gid on number theory

void solve([[maybe_unused]] ll T)
{
    READ(n);
    READ_VLL(a, n);

    // ll l = 0;
    // ll r = 0;

    // vll f(n, 0);
    // INC(i, n)
    // {
    //     f[i] = a[i] % 3;
    // }
    // DBG_ITER(f);

    vll ps(n, 0); // suffix sum not prefix sum
    DEC(i, n - 1)
    {
        if (i == n - 1)
        {
            ps[n - 1] = a[n - 1];
        }
        else
        {
            ps[i] = a[i] + ps[i + 1];
        }
    }

    for (ll l = 1; l < n - 1; l++)
    {
        for (ll r = l + 1; r < n; r++)
        {
            ll s1 = ps[0] - ps[l];
            ll s2 = ps[l] - ps[r];
            ll s3 = ps[r];

            if (
                (s1 % 3 == s2 % 3 && s2 % 3 == s3 % 3) ||                  // same remainder
                (s1 % 3 != s2 % 3 && s2 % 3 != s3 % 3 && s1 % 3 != s3 % 3) // all different / unique
            )
            {
                DBGLN(s1, s2, s3);
                OUT(l, r);
                return;
            }
        }
    }

    // ll s1 = 0;
    // for (int i = 0; i < n - 2; i++)
    // {
    //     s1 += a[i];

    //     for (int j = i + 1; j < n - 1; j++)
    //     {
    //         ll s2 = ps[i + 1] - ps[j];
    //         ll s3 = ps[j];
    //         for (int k = j + 1; k < n; k++)
    //         {
    //             s3 -= a[k - 1];
    //             s2 += a[k - 1];

    //             DBGLN(i, j, k, s1, s2, s3);
    //         }
    //     }
    // }

    OUT(0, 0);
}
