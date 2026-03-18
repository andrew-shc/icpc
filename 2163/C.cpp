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

// start: 1650
//   end:

// O.1: given any valid path, l must be the min # along the path and r must be the max # along the path
//      O.1.1: this creates like the smallest interval given a path
// O.2: given 2xn & down-right paths only => n unique paths only
//      O.2.1: there can be at most 1-down movement for any path
// O.3: this is sooo DP. because everytime you move location where the down movement happens (across different paths)
//              you can just **RE-USE** the min-interval at the bottom row & the top row

// ~~~~~~~~~~~~~~~~~~~~~~~ (totally wrong, no gaussian sum)
// O.4: given an interval [l,r] => (l)*(n-r+1) + (l-1)*(n-r+1) + (l-2)*(n-r+1) + ... until l-l (# of pairs)
//          => l(l+1)/2*(n-r+1)  # of pairs
//   ~~~~~~ THERE"S SOME OVER-COUNTING (DUPLICATES)
// ^^^ this way requires unnecessarily complicated ways of counting intervals

// per editorial via two-pointers

// EO.1: ~O.4, [l,r] works? so for all r's up to 2n
// EO.2: two-pointer, if [l+1,r] does not work, then increment r and check again
// how do we check if some [a,b] work?
// editorial's way feels so inefficient, esp seeing O(n) solution exists...
//  O(n) solution is definitely doing something with unionizing or intersecting the intervals....
//  to count all possible intervals

// back to my own solution (inspired by the existence of O(n) soln and too lazy to re-learn the editorial)

// counting all possible intervals given the requirements is actually easy
// 1. remove duplicates (duplicates are auto removed by 2.)
// 2. remove outset intervals (any intervals that has an inset)
//      we know the left endpoint is always within older one (by set ordering)
//      we just have to check if the right endpoint is within the largest right end point
// 3. do the usual ways again
// so just #2

// how to do #2 then
// if the set is ordered by .first then by .second => if the r went down again or stagnates,
//      the previous interval is an outset (by existence of inset)
//      => remove the previous one and add the new one

// too complicated

// per 348331154
// BIG IDEA: go from left instead of from right
// MAJOR OBSERVATION: given any l, as long there's an interval with a right endpoint of r, any r,r+1,r+2,...,2*n supports the interval
//      KEY OBSERVATION:  ANY INTERVAL's RIGHT ENDPOINT (ie, MIN R)
//          MAJOR OBSERVATION: for an l without an r, go for the previous min r (as if we're just extending the l of the previous interval)
// and use sentinel value

// implementation
// another suffixmin of r

void solve([[maybe_unused]] ll T)
{
    READ(n);
    READ_VLL(a1, n);
    READ_VLL(a2, n);

    // if (T == 615)
    // {
    //     a1.insert(a1.end(), a2.begin(), a2.end());
    //     for (auto &el : a1)
    //     {
    //         std::cout << el << "#";
    //     }
    //     std::cout << std::endl;
    //     return;
    // }

    pair<ll, ll> dp1[n];
    pair<ll, ll> dp2[n];

    INC(i, n)
    {
        if (i == 0)
        {
            dp1[0].first = a1[i];
            dp1[0].second = a1[i];
        }
        else
        {
            dp1[i].first = min(dp1[i - 1].first, a1[i]);
            dp1[i].second = max(dp1[i - 1].second, a1[i]);
        }
    }

    DEC(i, n - 1)
    {
        if (i == n - 1)
        {
            dp2[i].first = a2[i];
            dp2[i].second = a2[i];
        }
        else
        {
            dp2[i].first = min(dp2[i + 1].first, a2[i]);
            dp2[i].second = max(dp2[i + 1].second, a2[i]);
        }
    }

    // nlogn
    set<pair<ll, ll>> pairs;                         // ordered ascending order by .first then .second
    vll r_min(2 * n + 2, numeric_limits<ll>::max()); // min right per left endpoint

    INC(i, n)
    {
        ll l = min(dp1[i].first, dp2[i].first);
        ll r = max(dp1[i].second, dp2[i].second);
        pairs.insert(make_pair(l, r));
        r_min[l] = min(r_min[l], r);
    }

    ll sum_of_intervals = 0; // for the right most L
    DEC(l, 2 * n)
    {
        if (l == 0)
            continue;
        r_min[l] = min(r_min[l], r_min[l + 1]);

        if (r_min[l] == numeric_limits<ll>::max())
            continue;

        sum_of_intervals += 2 * n - r_min[l] + 1;
    }

    OUT(sum_of_intervals);
    return;

    // ll sum_of_intervals = 0;

    // set<pair<ll, ll>> pairs_improved; // instead of two pointing
    // // ll prev_l = 0;                    // l always at least 1, so the first condition will (should) always be ran
    // // ll prev_prev_l = 0;
    // // ll prev_r = 0;
    // // // ll max_prev_r = 0;
    // // ll prev_pos_delta = 0;
    // pair<ll, ll> prev_prev = make_pair(0, 0);
    // pair<ll, ll> prev = make_pair(0, 0); // previously chosen one
    // bool inset_mode = false;
    // pair<ll, ll> smallest_inset = make_pair(0, 0);

    // DBGLN(T);
    // for (auto &cur : pairs)
    // {
    //     DBGLN(">>", cur.first, cur.second);
    //     if (cur.second <= prev.second)
    //     { // found the inset of the previous
    //         DBGLN("FOUND INSET");
    //         if (!inset_mode)
    //         {
    //             DBGLN(prev.first, prev_prev.first, prev.second);
    //             DBGLN(cur.first, prev_prev.first, cur.second);
    //             sum_of_intervals -= (prev.first - prev_prev.first) * (2 * n - prev.second + 1) + (prev.first == prev.second && (prev.second != 2 * n && prev.first != 1 && prev.first != prev_prev.first - 1) ? -1 : 0);
    //             sum_of_intervals += (cur.first - prev_prev.first) * (2 * n - cur.second + 1) + (cur.first == cur.second && (cur.second != 2 * n && cur.first != 1 && cur.first != prev_prev.first - 1) ? -1 : 0);

    //             smallest_inset = cur; // dont modify the prev (ie, treat inset mode like a inter-mega-branch)
    //             inset_mode = true;
    //             prev = cur; // for calculating the L in regular we still need the most recent inset ones (and by the ordering of set, the largest L)
    //         }
    //         else
    //         {
    //             DBGLN(smallest_inset.first, prev_prev.first, smallest_inset.second);
    //             DBGLN(cur.first, prev_prev.first, cur.second);
    //             sum_of_intervals -= (smallest_inset.first - prev_prev.first) * (2 * n - smallest_inset.second + 1) + (smallest_inset.first == smallest_inset.second && (smallest_inset.second != 2 * n && smallest_inset.first != 1 && smallest_inset.first != prev_prev.first - 1) ? -1 : 0);
    //             sum_of_intervals += (cur.first - prev_prev.first) * (2 * n - cur.second + 1) + (cur.first == cur.second && (cur.second != 2 * n && cur.first != 1 && cur.first != prev_prev.first - 1) ? -1 : 0);

    //             smallest_inset = cur;
    //             prev = cur; // for calculating the L in regular we still need the most recent inset ones (and by the ordering of set, the largest L)
    //         }
    //     }
    //     else if (prev.first < cur.first)
    //     {
    //         // regular interval
    //         DBGLN("REGULAR");
    //         DBGLN(cur.first, prev.first, cur.second);
    //         sum_of_intervals += (cur.first - prev.first) * (2 * n - cur.second + 1) + (cur.first == cur.second && (cur.second != 2 * n && cur.first != 1 && cur.first != prev.first - 1) ? -1 : 0);
    //         prev_prev = prev;
    //         prev = cur;

    //         inset_mode = false;
    //     }

    //     // if (prev_l != l)
    //     // {
    //     // if (r >= prev_r) // ~~~~ no subset interval after ~~~~
    //     // {
    //     // pairs_improved.insert(make_pair(l, r));
    //     // if (r <= prev_r) // l can be higher => making smaller interval
    //     // {                // found smaller interval
    //     //     // remove prev one
    //     //     sum_of_intervals -= prev_pos_delta;
    //     //     // add the newest found inset
    //     //     prev_pos_delta = (l - prev_l) * (2 * n - r + 1);
    //     //     sum_of_intervals += prev_pos_delta;
    //     //     // prev_r = r;
    //     //     // prev_l = l;
    //     // }
    //     // else
    //     // { // add regular interval
    //     //     prev_pos_delta = (l - prev_l) * (2 * n - r + 1);
    //     //     sum_of_intervals += prev_pos_delta;
    //     //     prev_r = r;
    //     //     prev_prev_l = prev_l;
    //     //     prev_l = l;
    //     // }

    //     // sum_of_intervals += (l - prev_l);
    //     // prev_r = r;
    //     // }
    //     // else
    //     // {
    //     //     // we do need subset (when r < prev_r)

    //     //     // sum intervals for all L on prev_r-r
    //     //     // sum intervals for l-prev_l on the rest of after prev_r

    //     //     sum_of_intervals += (l - prev_l) * (prev_r - r);
    //     //     sum_of_intervals += (l - prev_l) * (2 * n - prev_r + 1);
    //     // }
    //     // prev_l = l;
    //     // max_prev_r = max(max_prev_r, r);
    //     // }
    // }

    // for (auto &[l, r] : pairs_improved)
    // {
    //     sum_of_intervals += (l - prev_l) * (2 * n - r + 1);
    //     // if (prev_l != l)
    //     // {
    //     //     sum_of_intervals += (l - prev_l) * (2 * n - r + 1);
    //     //     prev_l = l;
    //     // }
    //     // else
    //     // {
    //     //     // same l? by the order of the ascending order on the .second, prev ones has covered all the possible intervals already
    //     //     // observation: same r, but different l?, different interval that defn. did not get counted (l usually larger)
    //     //     //      which will be counted later on
    //     //     continue;
    //     // }
    //     // // sum_of_intervals += l * (l + 1) / 2 * (2 * n - r + 1);
    // }

    // OUT(sum_of_intervals);
}
