#include <bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using vll = std::vector<ll>;
using dll = std::deque<ll>;
using pll = std::pair<ll, ll>;
using vpll = std::vector<pll>;

const ll NEG = (long long)-4e18;
const ll MOD = 998244353;

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
#define DBLOCK if (false)
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

// strat
// order ALL of the elements by their difference
//      left m ; right n (leave the middle one unused)
// now iterate over i's corresponding element (where we remove it)
//      if the i lands in the middle => do nothing
//      if the i lands within left m (inclusive) => swap the difference value with the middle
//      if the i lands within right n (inclusive) => " "
// ~~~~~

void solve([[maybe_unused]] ll T)
{
    READ(n, m);
    READ_VLL(a, n + m + 1);
    READ_VLL(b, n + m + 1);

    vll e;
    vll e_inv(n + m + 1, 0);
    vll d;
    INC(i, n + m + 1)
    {
        d.push_back(a[i] - b[i]);
        e.push_back(i);
    }

    sort(e.begin(), e.end(), [&](ll i, ll j)
         { return d[i] < d[j]; });
    sort(d.begin(), d.end());

    INC(i, n + m + 1)
    {
        e_inv[e[i]] = i; // takes the destination index back to the sorted index
    }

    ll team_skill = 0; // excludes the middle
    // pre-compute
    INC(i, n + m + 1)
    {
        if (i < m)
        { // left m
            team_skill += b[e[i]];
        }
        else if (i >= m + 1)
        { // right n
            team_skill += a[e[i]];
        }
    }

    DBG_ITER(e);
    DBG_ITER(e_inv);
    DBG_ITER(d);

    vll o(n + m + 1, 0);
    INC(i, n + m + 1)
    {
        if (e_inv[i] == m)
        {
            // middle is already excluded
            o[i] = team_skill;
        }
        else if (e_inv[i] < m)
        { // i in left m (remove the value @ index and add the value of the middle)
            o[i] = team_skill - (b[i]) + (b[e[m]]);
        }
        else
        { // i in right n
            o[i] = team_skill - (a[i]) + a[e[m]];
        }
    }

    OUT_ITER(o);
}