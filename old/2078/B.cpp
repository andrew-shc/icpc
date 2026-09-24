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

// O.1: you can create a loop at the last 2 elements guaranteeing the users to minimize the distance to the exit (either 1 or 2)
// O.2: if k is odd, user at the exit will have a min dist of 1 to the exit (if they're in a 2-loop)
//      Q.2.1: can we design a 3-loop?
//              => problem, that means 2 users must will have to be further away from the exit => inoptimal => 2-loop is optimal
// O.3: by a very IMPORTANT FACT OF O.2, we will let all users at n-2 and earlier to directly teleport to @n-1 or @n of the 2-loop
//          depending if k is odd or not
//              this ensures every users reaches @n (the exit)
// O.4: there will always be a user not able to reach the exit (the total minimum will always be 1)
//          since starting with n=2, we have a 2-loop => min of always 1
//                              n=3, we can do 3-loop or 1 el direct jump to 2-loop + the 2-loop itself => min of always 1

// strat: (PER O.2 & O.2.1)
//  assuming we assign a 2-loop at the end
//  if k is odd
//      point to the exit
//  if k is even
//      point to the @-1

void solve([[maybe_unused]] ll T)
{
    READ(n, k);
    vll a(n, 0);
    INC(i, n - 2)
    {
        a[i] = n - ((k % 2 == 1) ? 0 : 1);
    }
    a[n - 2] = n;
    a[n - 1] = n - 1;

    OUT_ITER(a);
}