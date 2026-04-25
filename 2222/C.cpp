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

// if the partitioned subarray must be odd-lengthed (with overall being odd-lengthed)
//      => there must be odd amount of partitions (since even amounts of partitions means one has to be an even-lengthed)
//              since O=O or O+O+O but O+E or O+O+O+E (since the evenness must flip given the constraint of each parts must be odd-lengthed)
// ODD AMOUNT OF SUBARRAYS (PARTITIONS)

// wtf is the question even asking about
// I CANT FUCKING PARSE WHAT THE QUESTION IS ASKIGN
// hypothesis was correct, it was talking about maximizing the amount of partitioning (fucking confusing)
// sequence k is a sequence of starting index of each partition where the last one is a sentinel last index to indicate it should complete/span the entire array

// how do we maximize the number of subarrays where all the medians are the same (finally i can start thinking about the ques)

// partition being odd means we can always find the center exactly

// p can be at most n

// can we do a binary search on answer?
// => does it simplify the problem if let's say we are assuming the amount of partition and say if it works or not
// IS IT MONOTONIC THOUGH
//      if a number of parts p works, then p-1 must work (since that means that element occurs more than half of the times and any ways of merging them is always occur more than half???)
//      but we're not talking about whether it occurs more than half, but median...
//      if you are given parts p and every median of that is p, when you reduce a partition through merges, is it always valid??
//      remember, the partition must be in ODD amount so to merge we have to merge twice each times
//      i mean if we merge twice to the same or different subarrays, we always add at least one occurence of the median and the equal parts of below and above the median gets added MAINTAINING THE MEDIAN
//      (ie, if a config of partition works, then a config of partition works for smaller amount of partition but larger-lengthed partition)
//      but the other way might not work and we have to find that threshold
// => if p works, p-1 must work. if p not works, p+1 must not work

// but given an amount of partitions (p), can we find if it works in O(n)?

// can we decide what the median should be initially?
// assume p=1, given the median m1 for p=1, thats the only valid median?
//      if it occurs only once, its not like the upper and lower parts, even when maximized, will have a monopoly of medians for p>1
//  i dont feel comfortable about this....
//  lets say p=2, even when we maximize the up and low parts with a different center median (so up=low in terms of amount)
//      the median cant be the up or low, since a different middle exists
//      the median will exist when a middle does not since that means one of the up or low is the larger (and is the median for p=1 case)
//  just hand-wavy accept that the median for p=1 must be the median up to p=n

// SO, GIVEN TWO IMPORTANT OBSERVATION (HAND WAVY):
//  1. monotonicity on the validity of p (given the cond of the problem)
//  2. the median of p=1 must be the median for p=3..n (remember, p (the amount of partitions) must be odd also)

// can we find the partitions???? assume median and p???
// given p=1, can we find if p += 2 works then? find each subarrays and split (first time); do it again (second time)
//      can we greedily split or does it not matter?
//      if there are multiple ways to split subarray twice, is there a better option?
//          when you split an array, an even partition must exist, then you must split that even partition also
//          so when you think you find a split is valid, make sure it is also valid for even side of the split
//              => A SPLIT MUST SPLIT A PARTITION THREE-WAYS (YOU CANT SPLIT TWO SEP. SUBARRAY TWO-WAYS)
//      ~~~~~~~~~~~~~~~~~~~~~~ yes i'm pretty sure, if you split 1 1 3 (you can't do it from 2 3)

// hypothesized strat: as you iterate over k, if the first k element fits the median (on odd-length) => immediately split?
///         and try doing it again on the latter split (the even part)?
// per the monotonic logic, if we split the first and split the second the moment it reaches the median, that would be optimal (i think?)

// fuck this im just going to implement it (so much hand wavy observations)

// O(nlogn * logn)

// if we can just greedily split..... then whats the point of binary searching it????
// fuck it.... it really is just greedily split????
// if we greedily split (twice), we leave more spaces in the future
// but that might be bad
// consider
//   1 1 1 2 3 (p at most 1)  (but already p at most 1, is there a case where if you leave a large partition in the beginning? not be greedy?)

// but again, by monotonicity (hand-wavily), if we merge three adjacent subarrays together, we get a new valid subarray

// honestly fuck it and try it

// per discord, O(n^2) is valid (YEA DUH THE n IS ACTUALLY CONSTRAINED TO 5000)

// the idea is at each @i, we iterate j backwards from i to 0, if i to j is a valid subgroup, we can count that as one and sum
//      the remaining groups that excludes j to i and check if that maximizes the amount of group compared to the current dp[i]

void solve([[maybe_unused]] ll T)
{
    READ(n); // n is odd
    READ_VLL(a, n);

    vll b = a;
    sort(b.begin(), b.end());
    ll median = b[n / 2]; // the median that will be the case forever

    DBGLN(median);

    vll dp(n, -1);

    for (int i = 0; i < n; i++)
    {
        int xm = 0; // all medians are +
        int nm = 0; // all medians are -

        DBG_ITER(dp);
        for (int j = i; j >= 0; j--)
        {
            if (a[j] < median)
            {
                nm--;
                xm--;
            }
            if (a[j] > median)
            {
                xm++;
                nm++;
            }
            if (a[j] == median)
            {
                xm++;
                nm--;
            }
            if (((i - j) % 2))
            {
                continue;
            }

            // given EVERY POSSIBLE SUBARRAY from j to i, if it satisfies the median (given odd-length)
            //      +1 subarray compared to the amount of max possible subarray if j to i was removed
            if (xm >= 1 && nm <= -1)
            {
                if (j > 0 && dp[j - 1] != -1)
                    dp[i] = max(dp[i], dp[j - 1] + 1);
                else if (!j)
                    dp[i] = max(dp[i], 1LL);
            }
        }
    }
    DBG_ITER(dp);
    OUT(max(dp[n - 1], 1LL));

    // ll p = 0;
    // ll below = 0;
    // ll at = 0;
    // ll above = 0;
    // INC(i, n)
    // {
    //     if (a[i] == median)
    //     {
    //         at++;
    //     }
    //     else if (a[i] < median)
    //     {
    //         below++;
    //     }
    //     else
    //     { // a[i] > median
    //         above++;
    //     }

    //     // is there a case where the p would be even?

    //     // 1 1 1 1 1
    //     // 1 2 2 2 2 (consider this sorted)

    //     // 2 2 1 2 2 (we can only do this 2, 2, 1 2 2)
    //     // 2 2 1 2 2 (we can only do this 2, 2, 1 2 2)

    //     if ((at + below + above) % 2 == 1 && below < at + above && above < at + below)
    //     { // valid subarray

    //         // DBGLN(i, at, below, above, "YEA");
    //         p++;

    //         below = 0;
    //         at = 0;
    //         above = 0;
    //     }
    //     else
    //     {

    //         // DBGLN(i, at, below, above, "NO");
    //     }
    // }

    // OUT(p);

    // ll low = 1;
    // ll high = n;
    // ll mid;
    // while (low <= high)
    // {
    //     mid = (low + high) / 2; // our candidate p value
    // }
}