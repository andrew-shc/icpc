#include <bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;
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
    ((std::cout << args << " "), ...) << std::endl;
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

// O.1: if you merge with the highest value, the max will always be the highest value times n-1.
//          => hence, merge lower values, but how so?
//      O.1.1: the lowest value will always be masked by higher values by max
//          => maybe try merging two lowest adjacent values?

// 2x10^5 = quadratic?
// lets just brute force and see what the editorial has to say

// per editorial, yes we do try merging the ~~two lowest adjacent values~~; no, merge the smallest el.
//      with the smallest *neighbor*

// KEY OBSERVATION: we only need ONE GLOBAL MAX to consider where it will represent the cut for our cycle
//      the remaining elements
// KEY OBSERVATION: if we follow the greedy approach (smallest value and maximizing over the next smallest neighbor)
//      => produce a chain of maxes at *each* *adjacent* pairs *locally*, this is just like summing the maxes for
//      each adjacent pairs... hence sums of adjacent maxes except the double counting of the global max
//      which we just wrap around to avoid incurring the extra cost

void solve([[maybe_unused]] ll T)
{
    READ(n);
    READ_VLL(a, n);

    ll min_total_cost = max(a[n - 1], a[0]) - *max_element(a.begin(), a.end());

    // per editorial
    INC(i, n - 1)
    {
        min_total_cost += max(a[i], a[i + 1]);
    }

    // while (a.size() > 1)
    // {
    //     ll cur_min_total_cost = max(a[a.size() - 1], a[0]);
    //     ll ind1 = a.size() - 1;
    //     ll ind2 = 0;
    //     INC(i, a.size() - 1)
    //     {
    //         if (max(a[i], a[i + 1]) < cur_min_total_cost)
    //         {
    //             ind1 = i;
    //             ind2 = i + 1;
    //             cur_min_total_cost = max(a[i], a[i + 1]);
    //         }
    //     }
    //     a[ind1] = cur_min_total_cost;
    //     a.erase(a.begin() + ind2);

    //     min_total_cost += cur_min_total_cost;
    // }

    OUT(min_total_cost);
}