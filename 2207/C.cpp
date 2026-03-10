#include <bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;
typedef std::vector<ll> vll;
typedef std::deque<ll> dll;

const long long NEG = (long long)-4e18;

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

// O(n log on) soln. via D&Q is possible but will be trying the editorial's quadratic soln.

// // drain1 vs drain2
// pair<ll, ll> recurse(vll a, ll h)
// {
//     // we self-compute the exclusive region of the current max

//     auto maxv = *max_element(a.begin(), a.end());

//     vll maxes;
//     for (int i = 0; i < a.size(); i++)
//     {
//         if (a[i] == maxv)
//         {
//             maxes.push_back(i);
//         }
//     }

//     bool first = true;
//     for (int i = 0; i < maxes.size(); i++)
//     {
//         if (first)
//         {
//             first = false;

//             // do left side of the max

//             vll c(a.begin(), a.begin() + maxes[i]);
//             pair<ll, ll> p = recurse(c, maxv);
//         }

//         // do right side of the max
//         vll c(a.begin() + maxes[i] + 1, a.begin() + maxes[i + 1]);
//         pair<ll, ll> p = recurse(c, maxv);
//     }
// }

void solve([[maybe_unused]] ll T)
{
    READ(n, h);
    READ_VLL(a, n);

    // max amount of water drained possible given a drain placed at the lowest possible location at each col.
    vll cnt(n, 0);
    for (int i = 0; i < n; i++)
    {
        ll cur = a[i];

        // find max fill from center to right
        for (int j = i; j < n; j++)
        {
            cur = max(cur, a[j]);
            cnt[i] += h - cur;
        }

        cur = a[i];

        // find max fill to left (excluding center)
        for (int j = i - 1; j >= 0; j--)
        {
            cur = max(cur, a[j]);
            cnt[i] += h - cur;
        }
    }

    DBG_ITER(cnt);

    // key insights: we can utilize the same cnt (that corresponds to max elevation between col. i,j)
    //    to find the overlapping regions of cnt_i and cnt_j. (smells like DP)

    ll maxfill = 0;
    for (int i = 0; i < n; i++)
    {
        ll k = i;
        // note, =i instead =i+1 since we allow single drains
        for (int j = i; j < n; j++)
        {
            k = a[k] > a[j] ? k : j;
            // just like computing union, make sure to remove the intersection/overlapping region
            maxfill = max(maxfill, cnt[i] + cnt[j] - cnt[k]);
        }
    }

    cout << maxfill << endl;
}