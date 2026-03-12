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

void solve([[maybe_unused]] ll T)
{
    READ(n);
    string s;
    cin >> s;

    // // brute force since n constraint supports quadratic

    // for (int d = 0; d < n; d++)
    // {
    //     for (int i = 0; i < n; i++)
    //     {
    //         if (s[(i + d) % n] == '1' || s[(i - d) % n] == '1')
    //         {
    //             s[i] == '0';
    //         }
    //     }
    // }

    bool beginning = true;
    vll b;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == '0' && beginning)
        {
        }
    }

    ll ini0s = 0;
    ll ini0s_ofs = 0;

    ll max0s = 0;
    ll cur0s = 0;
    for (int i = 0; i < n; i++)
    {
        if ((i == 0 || ini0s > 0) && s[i] == '0')
        {
            ini0s++;
            continue;
        }
        else if ((ini0s > 0) && s[i] == '1')
        {
            ini0s_ofs = ini0s;
            ini0s = 0;
            continue;
        }

        if (s[i] == '0')
        {
            cur0s++;
        }
        else
        {
            max0s = max(max0s, cur0s);
            cur0s = 0;
        }
    }
    max0s = max(max0s, cur0s + ini0s_ofs);

    DBGLN(ini0s_ofs);
    DBGLN(max0s);

    //// MAJOR MISUNDERSTANDING: THE BINARY FLIP OPERATION IMMEDIATELY FLIPS AFTER AND
    ////// THE BIT FLIPS ACCUMULATES
    OUT(max0s);

    // if (max0s > 1)
    // {
    // OUT((max0s * (max0s + 1)) / 2);
    // }
    // else
    // {
    //     OUT(max0s);
    // }

    // if (max0s > 0)
    // {
    // OUT(max0s * (max0s - 1) / 2);
    // }
    // else
    // { // min cost of 1 (we always need to rotate)
    //     OUT(1);
    // }
}