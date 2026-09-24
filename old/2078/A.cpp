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

// rephrase: split into k integer-partitions after each operations
//              average each partition
//           repeat
//  find if there's a sequence of operations (via k) that results a = [x]
//  isnt this just the average of every element?

// H.1 this is just an average of every element
//      consider 10 elements, 2 ways to partition, by 2 or by 5
//          by 5: (avg(s1)+avg(s2))/(# of partitions) = avg(s1 concat s2)
//                  since the sizes of s1 and s2 are always equal, the denominator will always multipled into the number of total elements
//      do i need to casual-prove this?

// post-AC

// to see these kind of problems more quickly, consider more complicated cases like n=12
// ((/2 /2)/2 (/2 /2)/2 (/2 /2)/2)/3
// since we require k to divide the length of the array *currently*, it must be an INTEGER FACTOR of the array,
//      furthermore INT FACTOR of the length of the original arr
// we want the final array length to be 1, so we have to find ALL INTEGER FACTORs of the length of the original/init. arr.
// which always yield the same number... the length of the original arr.

void solve([[maybe_unused]] ll T)
{
    READ(n, x);
    READ_VLL(a, n);

    ll sum = 0;
    INC(i, n)
    {
        sum += a[i];
    }

    if (sum % n == 0)
    {
        if (sum / n == x)
        {
            OUT("YES");
        }
        else
        {
            OUT("NO");
        }
    }
    else
    {
        // always expect x to be an integer
        OUT("NO");
    }
}