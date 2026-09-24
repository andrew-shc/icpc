#include <bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
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

// O.1: order matters in the permutation p
// O.2: no operations can set the first and the last character in s to be 1 (if x requires at these location => automatic rejection)
// O.2.1: no operations can set sk1 and sk2 to 1 (ie, when xi==1 additionally matches to the position of largest & smallest pi)

// MAJOR OBSERVATION, just like you can brute force all the combination of a permutation of *last two/three* digit
// (from one of the problem A i forgot which specific one) to check whether it satisfies a condition,
// this problem exploits the idea of 5 max operations and the max's and min's of the permutation to prove
// that with these 5 operations, you can always achieve si=1 (except the cases as noted above)

// => learn how to prove greedy?

void solve([[maybe_unused]] ll T)
{
    READ(n);
    READ_VLL(p, n);
    READ_S(x);

    ll pos_max = distance(p.begin(), max_element(p.begin(), p.end()));
    ll pos_min = distance(p.begin(), min_element(p.begin(), p.end()));

    if (x[0] == '1' || x[n - 1] == '1' || x[pos_max] == '1' || x[pos_min] == '1')
    {
        OUT(-1);
        return;
    }

    if (pos_max < pos_min)
    {
        swap(pos_max, pos_min);
    }

    OUT(5);
    OUT(1, pos_max + 1);
    OUT(1, pos_min + 1);
    OUT(pos_max + 1, n);
    OUT(pos_min + 1, n);
    OUT(pos_min + 1, pos_max + 1);
}