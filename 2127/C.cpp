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

// O.1: v only goes up since Bahamin has the option to not do anything if Ali found something optimal for him
// O.2: if there's a certain i,j where whatever Bahamin does it does not affect v, Ali can always select it
//          O.2.1: only occurs when ai,aj,bi,bj are all equal
// H.3: it is optimal for Ali to pick the same certain i,j for all k rounds?
//      (i.e., it does not benefit Ali to always pick different i,j per round?)
//          => if Ali founds i,j that has 4 elements with the overall smallest range => Bahamin would try to increase cross-array element range for each i,j
//              which does not affect the current overall range but will reduce the option of Ali to find the smallest range
//          => Ali should jsut keep using the same i,j with the smallest range
//      O.3.1: better option, if Ali founds 4 elements that is already optimal for Bahamin => Bahamin has no choice but don't do anything => cannot increase v

// game strat: have Ali pick 4 elements that is already optimal for Bahamin (and keep repeating that choice)
//             if such 4 el doesn't exist, pick a 4-subgroup with smallest range overall => Bahamin will optimally regroup it => stable loop
// O.4: since k>=1, we don't care about the rounds actually

// Q.5: what is optimal for Bahamin? is the smallest range really the best option? (yes to the smallest range)
//          optimal for Bahamin is when either the largest - smallest & 2nd largest - 2nd smallest
//                                              or largest - 2nd smallest & 2nd largest - smallest
//          a<=b<=c<=d => [d-a]+[c-b] = [d-b]+[c-a]
//          (any other way does not optimally yield the best result for Bahamin)
//      codified:
//                              b[i] <= b[i+1] <= a[i+1] <= a[i]
//                              b[i] <= b[i+1] <= a[i+1] <= a[i]

// reduced strat: find the smallest increase (limit to 0) in v after a 4-way maximal re-arrangement

// DP????? (has to be O(n) or O(nlogn))
// X=i, >=j (per i)
// 1 2 3 4 5 6 7 8 9
// X > > > > > > > >
//   X > > > > > > >
//     X > > > > > >
//       X > > > > >
//         X > > > >
//           X > > >  (6,7) or (6,8) or (6,9)
//             X > >           (7,8) or (7,9)
//               X >                    (8,9)

// after looking at the tag:
// global sorting??? on value??? on a then on b? (ascending order on a and descending order on b within?)
//          pick the last element in this special order.... 2nd element should be next element where the b is larger (since we already pick the a to be largest already)
//              if all b element is smaller than the smallest b within the largest a... iterate to the next largest a??? (with potentially much smaller b to accomodate more compatible elements?)

//   per O.5:   largest - smallest & 2nd largest - 2nd smallest =>
//              largest - 2nd smallest & 2nd largest - smallest =>

// if editorial says O(n^2) solution works... then this problem sucks
/// should try O(n^2) solution first.

// writing out O(n^2) solution seems to reveal the DPness??
// but there's no DP tag

// PER EDITORIAL

// order doesn't matter for a,b so we can permute the arrays a,b (index-linked) => sorting???? (but tried it but doesn't seem to reduce the solution from O(n^2))

// per O.5: when the element's range (between @i and @j) intersect, it is already optimal (cannot be changed)
//      but when they don't intersect (i.e., 2 largest subtracted and 2 smallest subtracted) => suboptimal
//          per editorial, this increases by twice the range of the two middle elements (can be seen visually on a number line also)
// so... we want to minimize the increase (if no alternatives)

// BEFORE I WAS TOOO RESTRICTIVE BY FOCUSING ON STRICT SUBSET, BUT ANY OVERLAPPING INTERVALS WORKS
// if we sort again with ascending order on a and ascending order on b,
//                  if we find the current a is larger then or equal to the next b => 0 offset (we dont care if the next b is smaller or larger than the current b)
//                  meanwhile, if the current a is smaller than the next b => 2*(next b - current a)
//                      only works when the next a is strictly greater than the current a
//                      (and hence, implies these two intervals are disjoint and can be made overlapped with the 2x formula above)
//                      find the min of that value
//     generalization: since this works on an adjacency basis... we can just compute the min for each adjacent elements after sorting
//     clarification: are we missing anything if we focus locally like that? we always want to find the overlapping region,
//                          and the only optimal way to find overlapping region is we find intervals that are close to each other
//                          hence this works (over distinct a) (if there are multiple a's as in same a's with different b's => instant 0)

void solve([[maybe_unused]] ll T)
{
    READ(n, k);
    READ_VLL(a, n);
    READ_VLL(b, n);

    vpll intervals(n);
    INC(i, n)
    {
        // if we can freely swap the order of the interval, we should be able to freely swap the order of the endpoints
        // has no impact on the value
        // FOUND MORE INVARIANCES ACROSS INDEX AND ENDPOINTS (notice these invariances when thought of them as intervals)
        intervals[i] = {max(a[i], b[i]), min(a[i], b[i])};
    }

    sort(intervals.begin(), intervals.end()); // sort on pairs by default sorts ascending on first then on second

    ll v = abs(intervals[n - 1].first - intervals[n - 1].second);
    ll v_ofs = LLONG_MAX;
    INC(i, n - 1)
    {
        v += abs(intervals[i].first - intervals[i].second);
        if (intervals[i].first >= intervals[i + 1].second)
        {
            v_ofs = 0;
            // break;
        }
        else
        {
            v_ofs = min(v_ofs, 2 * (intervals[i + 1].second - intervals[i].first));
        }
    }

    OUT(v + v_ofs);

    // ll v = abs(a[n - 1] - b[n - 1]);
    // ll v_ofs = LLONG_MAX;
    // // for any two indices i,j
    // for (ll i = 0; i < n - 1; i++)
    // {
    //     ll vi = abs(a[i] - b[i]);
    //     v += vi;
    //     for (ll j = i + 1; j < n; j++)
    //     {
    //         ll vj = abs(a[j] - b[j]);

    //         ll els[4] = {a[i], b[i], a[j], b[j]};
    //         sort(begin(els), end(els));
    //         // [0] <= [1] <= [2] <= [3]

    //         ll v_optimal = els[3] - els[0] + els[2] - els[1];

    //         v_ofs = min(v_ofs, v_optimal - (vi + vj));
    //     }
    // }

    // OUT(v + v_ofs);

    // ll v = 0;
    // INC(i, n)
    // {
    //     v += abs(a[i] - b[i]);
    // }
    // OUT(v);
}