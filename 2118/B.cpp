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

// note the difference between subarray and subsequence

// you are only given the reverse operator

// O.1: each row is a permutation from 1 to n => with some swapping (i.e., cycling along the row)
//          we can make each column a permutation of n (regardless of the order of the permutation w.r.t. other columns)
// O.2: for each column to be some permutation, each row has to be in unique order
// O.3: an easy way to ensure unique order is if we rotate the elements and there's a way to do it for each row at most twice
//          with only reverse operations
//          => reverse i to n; then reverse 1 to i (creates the break between @i-1 and @i)
//              where 1 to i (=>) and i to n (=>)  becomes i to 1 (<=) and n to i (<=)
//              so like reversed rotation

// output strat:
// k==2(n-1)
// i=2 2 n
// i=2 1 1
// i=3 3 n
// i=3 1 2
// i i n
// i 1 i-1

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//          => reverse elements for i to n; then, reverse element from 1 to n (nope)

// 1 2 3 4 5 6 7 8 9

// 9 8 7 6 5 4 3 2 1  (i guess i forgot this was meant to be for the first row and starting from 2nd row since 5 is in the same place)
//                      we need the first row to be reversed also to ensure the same largest number at the end doesnt reappear in the last rotation of the reversed

// 1 9 8 7 6 5 4 3 2
// 2 3 4 5 6 7 8 9 1

// 1 2 9 8 7 6 5 4 3
// 2 1 9 8 7 6 5 4 3

// 8 7 6 5 4 3 2 1 9

// ~~~~~~~~~~~~~~~~~
// 9 8 7 6 5 4 3 2 1
// 9 8 7 6 4 5 3 2 1

// 1 9 8 7 6 5 4 3 2
// 2 3 4 5 6 7 8 9 1

// ~~~~~~~~~~~~~~~~~~
// O.3: reverse on odd length swaps elements over the center except the center

void solve([[maybe_unused]] ll T)
{
    READ(n); // square matrix
    OUT(2 * (n - 1) + 1);

    // DBGLN(2 * (n - 1));

    OUT(1, 1, n);

    for (ll i = 2; i <= n; i++)
    {
        OUT(i, i, n);
        OUT(i, 1, i - 1);
    }
}

/*

1 2 3
1 2 3
1 2 3

1 2 3
1 3 2
2 1 3

3 2 1
1 3 2
2 1 3

*/