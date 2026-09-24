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

// key idea, we want to maximize each subarray to satisfy a lower-bound => just maximally split the cake into 3 parts for 3 people
//      (despite the problem not saying all 3 subarrays needs to span the entire cake)
// => 3 parts has 2 points of partition => n^2 for bruteforce to try all option => nlogn B.S. on answer
//   => lognlogn double B.S. on answer???
// BUT BUT BUT BUT, its unordered (can be alice bob charlie, or other 3! permutation of them)
// soooo 6lognlogn + n???
// since we're only checking for existence and that we know that increasing a subarray's size increases its sum monotonically...
//      if all 6 permutation fails... then that means the current config of subarray does not work so we can decide *in a unified way*
//          if the moment ANY ONE of them passes, return it
// we will denote the two points of partitioning as L*** and R***
// in fact, this is a simplified binary search. since we're looking for existence, not for anything optimal (like barely on the edge)
//      so the moment it satisfies, we're done

// ok here's the thing
// if any left is not passing the condition => the rest aint (for all 6 permutation)
// if any left is now passing the condition but any remaining TWO aint => the rest aint (for all 6 permutation)
// if any left is now passing the condition but any remaining ONE aint => binary search until both aint (bad) or both yea (good)
// for hte last one, we just do linear (too many edge cases to think about???)

void solve([[maybe_unused]] ll T)
{
    READ(n);
    READ_VLL(a, n);
    READ_VLL(b, n);
    READ_VLL(c, n);

    vll a_pre(n + 1, 0);
    vll b_pre(n + 1, 0);
    vll c_pre(n + 1, 0);
    // vll a_suf(n + 1, 0);
    // vll b_suf(n + 1, 0);
    // vll c_suf(n + 1, 0);
    INC(i, n)
    {
        a_pre[i + 1] = a_pre[i] + a[i];
        b_pre[i + 1] = b_pre[i] + b[i];
        c_pre[i + 1] = c_pre[i] + c[i];
    }
    // DEC(i, n)
    // {
    //     a_suf[i] = a_suf[i + 1] + a[i];
    //     b_suf[i] = b_suf[i + 1] + b[i];
    //     c_suf[i] = c_suf[i + 1] + c[i];
    // }

    ll tot = a_pre.back();
    ll cond = (tot + 2) / 3;
    auto satisfied = [cond](const vll &v_pre, ll L, ll R) -> bool
    {
        return v_pre[R + 1] - v_pre[L] >= cond;
    };

    ll Ll = 0;
    ll Lr = n - 2;
    ll Lm;
    while (Ll <= Lr)
    {
        Lm = (Lr - Ll) / 2;

        // if (satisfied(a, 0, Lm) || satisfied(b, 0, Lm) || satisfied(c, 0, Lm))
        // {
        //     // further condition checking

        ll Rl = Lm + 1;
        ll Rr = n - 1;
        ll Rm;
        while (Rl <= Rr)
        {
            Rm = (Rr - Rl) / 2;

            if ((satisfied(a, 0, Lm) && (satisfied(b, Lm + 1, Rm) || satisfied(b, Lm + 1, Rm) || satisfied(c, Lm + 1, Rm) || satisfied(c, Lm + 1, Rm))) ||
                (satisfied(b, 0, Lm) && (satisfied(a, Lm + 1, Rm) || satisfied(a, Lm + 1, Rm) || satisfied(c, Lm + 1, Rm) || satisfied(c, Lm + 1, Rm))) ||
                (satisfied(c, 0, Lm) && (satisfied(b, Lm + 1, Rm) || satisfied(b, Lm + 1, Rm) || satisfied(a, Lm + 1, Rm) || satisfied(a, Lm + 1, Rm))))
            { // given a,b,c is satisfied, there must be at least one of the remaining partition is satisfied to check
              // but what if
            }
        }
        // }
    }
}

// this is so fucking boring / annoying to implement