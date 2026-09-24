#include <bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef std::vector<ll> vll;
typedef std::deque<ll> dll;

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

// trivial DP?

// O.1: if an array is not good and we can only decrement => we can only decrement on odd indices
// H.2: if the E is >= sum of two if its adjacent O for all E in the array => array good?
//      O.2.1: OEO s.t. E>=O+O for all E => by inequalities, any subset must satisfy => array good
//      H.2.2: array good => E>=O+O?? (find if there's a good array where E<O+O)
//          assuming array is good, then any subarray satisfy conditions included E>=O+O
//          therefore => is also true
// O.3: simplification of H.2: if array is good, E>=O (for both Os adjacent)
//          since if E>=O on both of its side for all E, then any subset satisfy the condition
//      O.3.1: the moment it fails this atomic condition, everything falls apart (tight)
// strat: we just need to ensure all the elements in the odd indices are less than the elements in the even indices

// ~~~~~~ BIG IDEA: (2-)ATOMIC CONDITION GUARANTEES OVERALL CONDITION
// NO BIG IDEA counter example
// 5 5 5 => 5 >= 5+5 fails
// 5 5 5 5 5 => 5+5 >= 5+5+5 fails
// if we guarantee E>=O+O for all adjacent odds (the worse case)
//      stricter inequality than E>=O
// idea: if add another even, it just splits up the shared odd, and the next must be odd but satisfies
//          the new 3-atomic condition (E1>=O1+O2 && E2>=O2+O3 => E1+E2>=O1+O2+O2+O3>=O1+O2+O3)

// 2 5 3 => 5 >= 2+3 (satisfies)
// 2 5 3 3 0 => satisfies

// BIG IDEA: 3-ATOMIC CONDITION GUARANTEES OVERALL CONDITION
//    E1>=O1+O2 && E2>=O2+O3 => E1+E2>=O1+O2+O2+O3>=O1+O2+O3
//      (because we need the atomic condition E>=O+O to be satisfied anyways)

// O.4: per big idea, to satisfy the 3-atomic conditions by minimally decrement the odd indices (O.1)
//          => try to minimize the odd that effects both adjacent evens
//              i.e.,  5 5 5 5 5 => 0 5 5 5 5 => 0 5 0 5 5 (unoptimal)
//                     5 5 5 5 5 => 5 5 0 5 5 (optimal)

// strat: at each even indices, compute how much the both odds summed are over the evens (overruns)
// overruns (@even) = 5 5 5 4 3 2 2 0 0 0 2 2 3 4 5
// strat =>

// O.5: to minimize, always first try to minimize/decrement odd indices NOT at the boundary, but in between everywhere
//          since O2-=? => E1-=? && E2-=? (overlapped decrements) vs separate reduction in overruns
//     Q.5.1: but which in-between overruns should be reduced to 0?
//              5 5. 5 5. 5 5. 5 5. 5
//                   ^         ^
//                        vs.
//              ^         ^         ^
//                        vs.
//                   ^    ^    ^
//     Q.5.2: what does a good array look like?
//          per big idea.... decrementing on overlapping odds is the most optimal it can be (greedily)
//          given E<O>E, reduce O to E o
//              .... am i over complicating???

//                  just first reduce all odds to the smallest adjacent even
//                  if an even still less than both adjacent odds => reduce the smaller odd (always/greedily?)
//

// O.6: if an overrun is higher than nearby overrun, nearby overrun cannot certainly remove the higher overrun
//          => go by order of the overruns (first minimize largest overruns completely then recal. overruns)
//          => requires random access!!

// per editorial and comments, there's no nice analytical formula; use simulation

// given three-element subarray (the E1,O1,O2), we minimize the last odd (O2 in this case)
//          (for some magical reason?? => because it benefits later subarray as always)

// note: this problem got so dull at the end (problem spent way too much time on it)

void solve([[maybe_unused]] ll T)
{
    READ(n);
    READ_VLL(a, n);

    ll min_ops = 0;

    // 1st pass  --> making sure 2-subset satisfied
    for (int i = 0; i < n; i += 2)
    { // @odds
        if (i == 0)
        {
            min_ops += max(0LL, a[i] - a[i + 1]);
            a[i] = min(a[i], a[i + 1]);
        }
        else if (i == n - 1)
        {
            min_ops += max(0LL, a[i] - a[i - 1]);
            a[i] = min(a[i], a[i - 1]);
        }
        else
        {
            min_ops += max(0LL, max(a[i] - a[i + 1], a[i] - a[i - 1]));
            a[i] = min(a[i], min(a[i + 1], a[i - 1]));
        }
    }

    // 2nd pass --> optimally ensuring 3-subset satisfied by always minimizing the later one (benefits later subarray / focuses on inner subarrays)
    for (int i = 0; i < n - 2; i += 2)
    { // @odds

        min_ops += max(0LL, a[i + 2] - (a[i + 1] - a[i]));
        a[i + 2] = min(a[i + 2], a[i + 1] - a[i]);
    }

    OUT(min_ops);
}