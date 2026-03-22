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

// BLUNDER: if we followed the assumption that the a string is always valid, the checks would be simplified to
//              to checking for increments only for n-m+1 or else 1.
//      ==> CAREFUL READING OF THE PROBLEM IS EQUALLY IMPORTANT IN SPEED SOLVING A&B

void solve([[maybe_unused]] ll T)
{
    READ(n, m);
    // READ_VLL(a, m);

    ll mx = 0;
    ll prev = 0;
    ll prev_mx = 0;
    bool valid = true; // apparently the question assumes the seq of a would always be valid
    bool pinned = false;
    INC(i, m)
    {
        ll ai;
        cin >> ai;
        if (i == 0)
        {
            prev = ai;
            mx = ai;
            continue;
        }

        if (ai == prev + 1)
        {
            // expected increment of 1

            mx = max(ai, mx);
        }
        else if (ai == 1)
        {
            // reset (whenever 1 is not at the initial position)
            pinned = true;

            // record the maxes and ensure the current max is at most an increment of the previous max
            if (prev_mx == 0)
            {
                prev_mx = prev;
            }
            else if (prev_mx + 1 == mx)
            {
                prev_mx = mx;
            }
            else
            {
                // incorrect max (despite strictly increasing by 1 with occasional reset to 1)
                valid = false;
                break;
            }
        }
        else
        {
            valid = false;
            break;
        }

        prev = ai;
    }

    if (valid)
    {
        if (pinned)
        {
            OUT(1);
        }
        else
        {
            OUT(n - mx + 1); // works for 1..mx or even for mx-1..mx
        }
    }
    else
    {
        OUT(0);
    }

    // ll cnt = 0;
    // ll mx = 0;
    // ll prev = 0;
    // ll post = false;
    // ll pre = true;
    // INC(i, m)
    // {
    //     READ(ai);
    //     if (i > 0)
    //     {
    //         if (ai - prev != 1 && ai != 1)
    //         {
    //             // if ai is not 1 and somehow its not incrementing by 1 => invalid (no subarray matched)
    //             OUT(0);
    //             return;
    //         }
    //     }
    //     else
    //     {
    //         // i ==0
    //         pre = ai != 1;
    //     }

    //     if (ai == 1)
    //     {
    //         cnt++;
    //     }

    //     if (mx < ai)
    //     {
    //         mx = ai;
    //         post = false;
    //     }
    //     else
    //     {
    //         post = true;
    //     }
    //     prev = ai;
    // }

    // if (cnt >= 2)
    // {
    //     // 2 or more 1s means at most 1 subarrays
    //     if (mx < n)
    //     {
    //         OUT(1);
    //     }
    //     else if (mx == n && !post)
    //     { // make sure no post at the end
    //         OUT(1);
    //     }
    //     else
    //     {
    //         // post after the final or max > n
    //         OUT(0);
    //     }
    // }
    // else if (cnt == 1 && !pre)
    // {
    //     // 1 ones
    //     OUT(n - mx + 1);
    // }
    // else if (cnt == 1 && pre)
    // { // 1 ones + pre
    //     if (mx <= n)
    //         OUT(1)
    // }
    // else
    // {
    //     // 0 ones
    // }
}