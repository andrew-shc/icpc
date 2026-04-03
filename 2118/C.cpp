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

// O.1: each operation can  AT MOST increase beauty by 1 but decrease beauty by a lot
//      O.1.1: therefore, it's never worth it to forgo a beauty in search of more beauty unless
//              no ops that can immediately gain beauties anymore (greedy on operation (hence, on # of ops == answer))
// O.2: if you are given a super large k, you might as well increase every element to be the most beautiful
//      O.2.1: every time you increase, the larger the number the more beautiful it can be before reset
// O.3:
//      1 2 3 4 5 6 7 8 9
//      1 1 2 1 2 2 3 1 2
//      2^x = beauty of 1
//      1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16
//      1  1  2  1  2  2  3  1  2  2  3  2  3  3  4  1
//     @1 @2 @1 @4 @1 @2 @1 @8                       @
// O.4: by O.1.1, for each element we should first find the number operations to gain an additional k
//      pick the element that requires the least ops, recalculate its required ops. (for the next increase in beauty) and insert it back.
// O.5: multimap has a way to insert elements back in order based off its calculated ops till next beauty
//      O.5.1: multimap based implementation of key being the # of ops till next with value being the current value of that element?
// O(nlogn + klogn) or O((n+k)logn) and O(2n) memory

// impl
// Q.6 how to compute the current beauty given x?
//      to count the # of 1s we can use c++20's popcount
// Q.7 how to compute the k ops remaining till next increase in beauty?
//      subtract the number by 2^floor(log2(x))?
//      i dont think it has to be that elegant???
//      => if treat the bit as an array starting from right, if there's a 0 terminate, if there's a 1, x2 factor and go the next element (<-- direction)
//

void solve([[maybe_unused]] ll T)
{
    READ(n, k);
    READ_VLL(a, n);

    ll max_beauty = 0;
    multimap<ll, ll> b; // ascending order: [k=# of ops remaining, v=ai]
    for (ll el : a)
    {
        max_beauty += popcount((ull)el);

        ll remaining = 1;
        for (ll i = 0; i < 64; i++)
        {
            if (((el >> i) & 1) == 1)
            { // ith bit, it is 1. must continue to find the 0
                remaining *= 2;
            }
            else
            { // ith bit is 0
                break;
            }
        }
        b.insert({remaining, el});
    }

    while (true)
    {
        // pick the element with the smallest ops remaining till next beauty
        auto [r, v] = *b.begin();

        if (k >= r)
        { // if the remaining k ops still supports the smallest ops remaining
            max_beauty++;

            k -= r;
            v += r; // remember, ops represents an increment in the value itself
            b.erase(b.begin());

            ll remaining = 1;
            for (ll i = 0; i < 64; i++)
            {
                if (((v >> i) & 1) == 1)
                { // ith bit, it is 1. must continue to find the 0
                    remaining *= 2;
                }
                else
                { // ith bit is 0
                    break;
                }
            }
            b.insert({remaining, v});
        }
        else
        {
            break;
        }
    }

    OUT(max_beauty);
}