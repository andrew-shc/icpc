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

// H.1: we can maximize bonus points by first purchasing for a total of X-M+1 price, and a single order of M
//          (preferably largest) right after resulting in a bonus of M points.
// O.2: prices can be thought of as a segment of length ai on a number line and whenever the segment intersects
//          multiples of X (the X-level), that contributes to the total bonus
//      H.2.1: since ai<=X, we can first put all the large segments to intersect(*) the X-level traded-off by
//              whatever smaller segments can fit between the large segments
// (*): intersect means whenever a segment inclusively includes the multiples of X itself
// H.3: greedy? pick the largest segment and few smallest segments that makes the largest to intersect X-level
//          what if there's no optimal smallest segment (ie the smallest will make the largest's R go slightly over X-level)
//                  (...cutting into the next loyalty level while still intersecting X)
//          ieie => if the segments make a perfect X-level, we can just remove them from the list and apply again to the remaining prices with the same exact condition
//              and this should be the optimal
//          WAIT... wouldnt it be better if the largest segment L be right at the first X and a smaller segment NO
//              REMEMBER, MAXIMIZE THE SUM OF SEGMENT LENGTHS THAT INTERSECTS X
//      can we produce a counter-example? or proof by contradiction?
//      if we pick the larger values that must cause the larger segment A to overlap X => inefficient? ineff. but best?
//          it just shifts the X-level to left, and makes the next largest segment reach the next X-level easier (<=X)
//      proof by intuition for now (read editorial after if it doesnt work)
//      !!! before looking at editorial, try >>>> pattern deduction by exploring select existing test cases <<<<

// O.4: we always hit X-level S/X amount of times => how to arrange the segments to maximize the length of segments
//          that intersect it
//      O.4.1: swapping whatever for the k-first elements does not affect the max # of bonus points after k segments
//              the reverse is true (arbitrary swapping order of the k-last element does not affect max pts for (n-k)-first el)
// O.5: each element can at most hit X-level once
//      O.5.1: there can be at most n X-level intersections
// H.6: just pick S/X largest element??????????
//      H.6.1: given S/X intersection with X-level, can any S/X elements be intersected? => just pick a certain arrangement
//          of intersection that maximizes the score
//          => counter-example: X=10, a=1,10,1 => 1,1,10 (10 intersects) 1,10,1 (10 intersects) 10,1,1 (10 intersects)
//          O.6.1.1: all arrangements prefer larger segments *naturally*? that just vaguely narrows down the method
//      H.6.1.2: can we just pick the largest? whats the problem? is greedily pick the largest can prevent 2nd,3rd largest max?
//      honestly fuck it this is the best ive got + gotta print the arrangements
//      test case looks right!!!
//      how tf do i arrange the output? can definitely be greedy
//  lmao it worked..... not intuitive.....
//  lmao editorial useless af

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//      suppose the group of smallest segment does not make the next largest segment overlap X => what was the point?
//      suppose the max # of bonus points is not achieved by this, how would it get the max # of bonus points by forgoing larger
//          segments with smaller of the larger segments?

void solve([[maybe_unused]] ll T)
{
    READ(n, X);
    READ_VLL(a, n);
    sort(a.begin(), a.end()); // nlogn (ascending)

    ll ind_large = n - 1;
    ll ind_small = 0;

    ll cur_sum = 0;
    vll b;
    while (ind_small <= ind_large)
    {
        ll remaining = X - cur_sum % X;
        if (remaining > a[ind_large])
        {
            b.push_back(a[ind_small]);
            cur_sum += a[ind_small];
            ind_small++;
        }
        else
        {
            b.push_back(a[ind_large]);
            cur_sum += a[ind_large];
            ind_large--;
        }
    }

    ll sum = 0;
    INC(i, n)
    {
        sum += a[i];
    }

    ll max_bonus_pts = 0;
    INC(i, sum / X)
    {
        DBGLN(n, i, sum, X, sum / X, a[n - i - 1]);
        max_bonus_pts += a[n - i - 1];
    }
    OUT(max_bonus_pts);
    OUT_ITER(b);

    // ll i_large = n - 1;
    // ll i_small = 0;

    // ll max_bonus_points = 0;
    // ll total = 0;
    // vll h;
    // while (i_large > i_small - 1)
    // {
    //     ll remaining = X - total % X;
    //     while (remaining > a[i_large])
    //     {
    //         if (i_small == i_large + 1)
    //         {
    //             OUT(max_bonus_points);
    //             OUT_ITER(h);
    //             return;
    //         }
    //         total += a[i_small];
    //         remaining -= a[i_small];
    //         h.push_back(a[i_small]);
    //         i_small++;
    //     }
    //     max_bonus_points += a[i_large];
    //     total += a[i_large];
    //     h.push_back(a[i_large]);
    //     i_large--;
    // }

    // OUT(max_bonus_points);
    // OUT_ITER(h);
}