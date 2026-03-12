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

// start: 6:23
//   end:

void solve([[maybe_unused]] ll T)
{
    READ(n);
    READ_VLL(a, n);

    dll e;
    dll o;
    for (auto &el : a)
    {
        if (el % 2)
        {
            // odd
            o.push_back(el);
        }
        else
        {
            // even
            e.push_back(el);
        }
    }
    sort(e.begin(), e.end(), [](int aa, int bb)
         { return aa > bb; });
    sort(o.begin(), o.end(), [](int aa, int bb)
         { return aa > bb; });

    if (o.size() == 0)
    { // all evens, answer only 0
        vll k(n, 0);
        OUT_ITER(k);
    }
    else if (e.size() == 0)
    { // all odds, no even
        vll k;
        // always use the largest o
        k.push_back(o.front());
        o.pop_front();

        for (auto &_ : o)
        {
            if (k.back() != 0)
            {
                k.push_back(0);
            }
            else
            {
                k.push_back(k.front());
            }
        }
        OUT_ITER(k);
    }
    else
    { // at least one odd AND one even
        vll k;
        // always use the largest o
        k.push_back(o.front());
        o.pop_front();

        // incrementally add all the evens first
        for (auto &el : e)
        {
            k.push_back(k.back() + el);
        }

        // remaining are all odds.
        // strat:
        //      adding +1 odds yields even => must do +2 odd in the beginning (-1 even at the end)
        //      +1 even back
        //      adding +1 odds yields even .... => -1 even
        //      +1 even back
        //      no more odds left? (end); only one more odd left? (=0; end); >=2 odds? (continue)

        ll ref = k.back();

        for (int i = 0; i < 2 * (o.size() / 2); i++)
        {
            if (k.back() == ref)
            {
                k.push_back(ref - e.back());
            }
            else
            {
                k.push_back(ref);
            }
            // OUT_ITER(k);
        }
        if (o.size() % 2 == 1)
        {
            k.push_back(0);
        }

        OUT_ITER(k);
    }
}