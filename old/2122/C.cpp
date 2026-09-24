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

// to maximize multiple length measurements (e.g., Manhattan distance, intervals, etc.) => try to have as much overlap as possible
// => go from the furthest to closest pairs of points

// sort by x then by y? (ascending order of what?)

// first, find the largest point x1,y1 and the smallest point x2,y2... I.E., find the largest manhattan distance...
//      but what if there are two equally largest pair  have the same manhattan distance?
//      actually... how does one even find the largest manhattan distance???

// consider
/*

..........
....#.....
........#.
....#.....
.#........
.......#..
....#...#.
..#.......
....#.....
..........

what's the largest manhattan distance? so we find the distance on the diagonals?? (ie, produce d=x+y, distance from origin)

im probably over complicating it.... split the points into 2 1D intervals
... problem: the x and y are bounded... tied together


...#.|
.....|
....#|
.#...|
...#.|
-----


~~~~~~~~~~~~~~

wait... |x1-x2|+|y1-y2|

case by case....:

if x1>x2 and y1>y2:
    x1+y1-x2-y2 => d1-d2 (easy ordering)

if x1<x2 and y1<y2:
    x2-x1+y2-y1 = x2+y2-x1-y1 = d2-d1 (easy ordering)

if x1<x2 and y1>y2:
    x2-x1+y1-y2 = -x1+y1 + x2-y2 = e1-e2 (easy ordering)

if x1>x2 and y1<y2:
    x1-x2+y2-y1 =  x1-y1 +-x2+y2 = e2-e1 (easy ordering)???

let us suppose we calculate all the point's distance from origin (x2=0,y2=0)
    >> that's ordering points from their distance to the origin... not between points to points?
    >> given two points pA,pB, we can find the dstiance as follows... pA-pB = (pA-0)-(pB-0)
    >> |x1-x2|+|y1-y2| = |x1-0-0-x2|+|y1-0-0-y2| = |(x1-0)-0-x2|+|y1-0-0-y2|

    NOPE DOESNT WORK [[ABORT]]

if quadrant I:
    d=x1+y1

if quadrant II:
    d=-(x1-y1)

if quadrant III:

*/

// per editorial, if you want to maximize overlapping regions
//      you actually don't need to first find two points with largest manhattan distance and
//          in the order of that find the next two points with the next largest manhattan distance
//      you just need to find half of the points connected to the half of the points which guarantees
//      at the half-way point... you maximize the overlapping regions (i.e., n/2)

void solve([[maybe_unused]] ll T)
{
    READ(n);

    vpll pts;
    INC(i, n)
    {
        READ(x, y);
        pts.push_back({x, y});
    }

    // wait, can't we just sort by X first, then top half and bottom half sort again by Y?
    // => -x,-y ; -x,+y ; +x,-y ; +x,+y
    // so, connect the first to the fourth path and second to the third part

    vll indX(n);
    vll indY(n);
    iota(indX.begin(), indX.end(), 0);
    iota(indY.begin(), indY.end(), 0);

    // // sort by x overall first
    // sort(ind.begin(), ind.end(), [&](ll i, ll j)
    //      { return pts[i].first < pts[j].first; });
    // // sort by y in halves
    // sort(ind.begin(), ind.begin() + n / 2, [&](ll i, ll j)
    //      { return pts[i].second < pts[j].second; });
    // sort(ind.begin() + n / 2, ind.end(), [&](ll i, ll j)
    //      { return pts[i].second < pts[j].second; });

    sort(indX.begin(), indX.end(), [&](ll i, ll j)
         { return pts[i].first < pts[j].first; });
    sort(indY.begin(), indY.end(), [&](ll i, ll j)
         { return pts[i].second < pts[j].second; });

    sort(indX.begin(), indX.begin() + n / 2);
    sort(indX.begin() + n / 2, indX.end());
    sort(indY.begin(), indY.begin() + n / 2);
    sort(indY.begin() + n / 2, indY.end());

    vll aa;
    vll ab;
    vll ba;
    vll bb;

    DBG_ITER(indX);
    DBG_ITER(indY);

    set_intersection(indX.begin(), indX.begin() + n / 2, indY.begin(), indY.begin() + n / 2, back_inserter(aa));
    set_intersection(indX.begin(), indX.begin() + n / 2, indY.begin() + n / 2, indY.end(), back_inserter(ab));
    set_intersection(indX.begin() + n / 2, indX.end(), indY.begin(), indY.begin() + n / 2, back_inserter(ba));
    set_intersection(indX.begin() + n / 2, indX.end(), indY.begin() + n / 2, indY.end(), back_inserter(bb));

    DBG_ITER(aa);
    DBG_ITER(ab);
    DBG_ITER(ba);
    DBG_ITER(bb);

    DBGLN(aa.size(), bb.size(), ab.size(), ba.size());

    for (ll i = 0; i < aa.size(); i++)
    {
        OUT(aa[i] + 1, bb[i] + 1);
    }
    for (ll i = 0; i < ab.size(); i++)
    {
        OUT(ab[i] + 1, ba[i] + 1);
    }

    // vpll results;
    // ll incl_fourth = (n + 3) / 4; // ceil division (be inclusive => includes the center)
    // ll excl_fourth = n / 4;
    // // -,- -> +,+
    // INC(i, excl_fourth)
    // {
    //     results.push_back(make_pair(ind[i], ind[i + n / 2 + incl_fourth]));
    // }
    // // -,+ -> +,-
    // INC(i, excl_fourth)
    // {
    //     results.push_back(make_pair(ind[i + incl_fourth], ind[i + n / 2]));
    // }
    // if (n % 4 == 2)
    // {
    //     // there's a pair of points left apart in x but close in y (just make a pair with it)
    //     results.push_back(make_pair(ind[excl_fourth], ind[n / 2 + excl_fourth]));
    // }

    // for (auto &[x, y] : results)
    // {
    //     OUT(x + 1, y + 1);
    // }

    // for ()

    //     sort(ptsX.begin(), ptsX.end());

    // sort(ptsY.begin(), ptsY.end(), [](const pll &a, const pll &b)
    //      { return a.second < b.second; });

    // vpll result;
    // // -,- -> +,+
    // INC(i, n / 2)
    // {
    //     result.push_back(make_pair);
    // }

    // // -,+ -> +,-
}