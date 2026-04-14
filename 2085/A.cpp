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

// O.1: s is universal if the first character is smaller than the last character lexicographically
//      O.1.1: we can swap i-th and (n-i)-th character (up to n/2) to ensure it satisfies the universal property
//                   => requires 1 ops
//      O.1.2: if the i-th and (n-i)-th character is same... swapping no longer works but it can still be universal
//                   => requires 1 ops
//  if no single letter is same more than n/2 characters
//  as long there's 1 character different, you can always swap that different character to the first or the last to ensure
//      the smaller character is at the first and larger character is at the end
//      so AT MOST 1 k is needed (0 k possible)
//  honestly burh moment

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// count how many times the i-th character is larger than (n-i)-th character (up to n/2) -- bad ordering -- bads
//  if the number of bads exceeds k, it is

// however, consider afcba
//                     vs.
//                   abcfa (r)
//      the reverse is lexico. smaller (not the original string being lexico. smaller ==> bad)
//      we can swap b,f, but a is still the same.....
//      there must be a better way

void solve([[maybe_unused]] ll T)
{
    READ(n, k);
    READ_S(s);

    string r(s.rbegin(), s.rend());

    bool different = false;
    INC(i, n - 1)
    {
        if (s[i + 1] != s[0])
        {
            different = true;
        }
    }

    if (s < r)
    {
        OUT("YES");
    }
    else
    {
        if (different && k > 0)
        {
            // pick the SINGLE differing character and swap it with either the beginning or the end of the string
            //  to make the string universal
            OUT("YES");
        }
        else
        {
            // all same or k == 0 or both?
            OUT("NO");
        }
    }
}