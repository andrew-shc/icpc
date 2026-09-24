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

// MAJOR MAJOR MAJOR MAJOR OBSERVATION: c++ has lcm(a,b)

// MAJOR OBSERVATION: everytime all three visits the same time (i.e., overlaps), it is on one AND ONLY one
//          of the multiples of LCM!!
//          (since each a,b,c has to be a divisible factor at that overlap)

// MAJOR OBSERVATION: LCM(LCM(a,b),c) find the LCM of all 3 (and applies to 4,5,...)
//          since LCM finds the max exponent of each factor, LCM of all 3 input is like finding the max factor
//          for each two inputs

void solve([[maybe_unused]] ll T)
{
    READ(a, b, c, m);

    // computing lcm is O(log(min(a,b)))

    ll abc = lcm(lcm(a, b), c); // 3 visited
    ll ab = lcm(a, b);          // 2 visited
    ll bc = lcm(b, c);
    ll ac = lcm(a, c);
    // and by theoretical extension, a,b,c are LCM themselves

    // observation: everything repeats after reaching past the largest lcm (the lcm of all three)
    // abc / a - 1 - (abc / ab - 1) - ..., a overlaps happens within abc (exclusively)
    // abc / ab - 1, ab overlaps happens within abc (exclusively)

    // find liters of waters each collected per largest lcm cycle
    // actually, we can just replace abc (the lcm itself) with m directly to find the overall count directly and easily
    // ^^ MAJOR OBSERVATION
    ll ca = m / a;
    ll cb = m / b;
    ll cc = m / c;
    ll cab = m / ab;
    ll cbc = m / bc;
    ll cca = m / ac; // STUPID BUG BC OF STUPID NAMING SCHEME (before ca, now ac)
    ll cabc = m / abc;

    DBGLN(ca, cb, cc, cab, cbc, cca, cabc);

    ll only_abc = cabc;
    ll only_ab = cab - only_abc;
    ll only_bc = cbc - only_abc;
    ll only_ac = cca - only_abc;
    ll only_a = ca - only_ab - only_ac - only_abc;
    ll only_b = cb - only_ab - only_bc - only_abc;
    ll only_c = cc - only_ac - only_bc - only_abc;

    // MAJOR OBSERVATION: im a fucking dumbass. the variable literally says "only".
    //      when only finding a, yes exclude the 2-ways AND the 3-ways
    //      when adding up the two-ways, we ONLY add up two ways, no need to subtract/add the three-ways (it's already handled for goodness sake)

    DBGLN(only_abc, only_ab, only_bc, only_ac, only_a, only_b, only_c);
    DBGLN(only_ab + only_ac + only_abc, only_ab + only_bc + only_abc, only_ac + only_bc + only_abc);

    ll alice = 2 * only_abc + 3 * (only_ab + only_ac) + 6 * only_a;
    ll bob = 2 * only_abc + 3 * (only_ab + only_bc) + 6 * only_b;
    ll carol = 2 * only_abc + 3 * (only_ac + only_bc) + 6 * only_c;

    OUT(alice, bob, carol);
}
