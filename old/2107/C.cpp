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

// of course some element is negative or else it will be too easy

// O.1: we just need at least ONE subarray (inclusive) to have a maximum of k
//                             ^^correction, has to be THE MAX
//  O.1.1: pick the current subarray (s.t. its sum is the max) that contains si=0 and
//          and let the forgotten value equal to k - current subarray max to bring the current subarray max to k
//          (and set all other forgotten value to 0)
//  O.1.2: because this is the subarray max, and we added k-current subarray max, every other possible subarray
//      will only add upto the new value (keeping within the limits)
//>>O.1.3: this is impossible when there's a subarray sum >k (s.t., the subarray contains no forgotten values)
//      O.1.3.1: otherwise, if there's a max subarray sum =k, let all forgotten value be 0
//                          if the max subarray sum <k AND there exists at least 1 forgotten value, let the
//                              the forgotten value be k - current subarray max and other forgotten value be 0.

// strat:
//  if any *exclusive* subarray sum >k (s.t., the subarray contains no forgotten values / resets on forgotten values)
//      NO
//      => we can let all forgotten values be up to -10^18 allowing max subarray sum <= k. (input constraints allow this construction)
//      ~~~merged to one of the following cases (since we filled the forgottens with the lowest values possible)
//  if there exists at least 1 forgotten value within any local max subarrays (which it is always in):
//      let other forgotten values be -10^18
//      let the forgotten value be (k - local max), where the local max is the recomputed max subarray after the assignment of the forgotten value
//  if no forgotten value AND max subarray sum !=k:
//      NO, impossible to modify to fit the need of k
//  if no forgotten value AND max subarray sum ==k:
//      YES, as is

// => find a way to compute subarray sum, exclusive subarray sum [done], and optimized recomputing subarray sum?

// how does one find the max subarray sum (mss)?
// 2 pointers??
// if a[i] is +, add, if a[i] is -????
// include current subarray sum (css)
// if a[i] is +, mss = max(a[i])
// if a[i] is 0, ignore
// if a[i] is -, a;

// ~~~~~~~~~~~~~~~~~~~~
//  if the max subarray sum =k
//      let all forgotten value be 0

// given an array a, we need to be able to find the max subarray sum, local max subarray sum of a local forgotten value

// per editorial's solution

// use prefix max and suffix max, but why does that work? and how would it even work??
// WLOG, use prefix sum
// if we have a new element a[i] and sum of previous element dp[i-1]
//      we can do the following... dp[i] = max(dp[i-1]+a[i[,a[i])
//          but... what if we remove the earlier elements of dp[i-1]?? that makes it higher?
//              actually, since we're adding a[i] on both sides, it would prefer the previous sum
//              if it's already positive, if the accumulation is negative, it'll always prefer newer element (reset)
//              BUT, im asking if we remove the earlier elements from dp[i-1] to make the accumulation from
//              negative to positive???
//                  => that only happens when the oldest (left-most; to-be-removed) elements are already negative
//                  => but we only kept those negative elements if prior accumulation is quite high/good
//                  => the moment we remove positive elements of the previous accumulation (bad; decreases accumulation)
//                      and when we start removing negative elements at the left-most end, we remove all left-most elements
//                      as there's no reason to keep them anymore to keep them for the previous previous positive accumulation
//                  => (MAJOR OBSERVATION: elements always starts with positives)
//                        and by that observation, we will always have the accumulation being reduced strictly
//                        and better to restart the whole accumulation
//                     (MAJOR OBSERVATION: the first positive accumulation must be greater than the coming negative accumulation
//                      for it to make sense to keep the negative accumulation unless the newer elements can just do better)

void solve([[maybe_unused]] ll T)
{
    READ(n, k);
    READ_S(s); // n
    READ_VLL(a, n);

    vll prefix(n + 1, 0);
    vll suffix(n + 1, 0);
    ll forgotten_values = 0;
    ll last_forgotten_ind = -1;
    INC(i, n)
    {
        DBGLN(s[i]);
        if (s[i] == '0')
        { // forgotten value
            DBGLN("???", i, a[i]);
            forgotten_values++;
            a[i] = -10e17; // won't underflow and maintain less than -2*10^5*10^6=-2*10^11 (ensuring correctness)
            last_forgotten_ind = i;
            DBGLN("AAA", a[i]);
        }

        DBGLN("----");
    }
    INC(i, n)
    {
        // note: the suffix will access the value AHEAD of the negative assignemnts.
        //      got to do it on a separate linear loop

        // potential underflow can happen here with prefix[i]+a[i]
        prefix[i + 1] = max(prefix[i] + a[i], a[i]); // if the previous accumulation helps, continue; then restart, if it's better than the accumulation
                                                     // (i.e., when the accumulation goes negative)
        suffix[n - 1 - i] = max(suffix[n - i] + a[n - 1 - i], a[n - 1 - i]);
    }

    // if no forgotten values, we just got to check if the max subarray is at k or not
    // if there are, the assignment of forgotten values to the effectively lowest value
    //      will still allow us to detect max subarrays where they're >k within the forgottens boundaries
    //          (since assigning them to the effectively lowest value creates a boundary when computing the max subarray)

    ll max_subarray = 0;
    INC(i, n)
    {
        DBGLN("MAX SUBARRAY", i, prefix[i + 1], suffix[i], a[i]);
        max_subarray = max(max_subarray, prefix[i + 1] + suffix[i] - a[i]);
    }

    if (max_subarray == k)
    {
        OUT("YES");
        OUT_ITER(a);
    }
    else if (max_subarray > k)
    {
        DBGLN("NO--max_subarray > k", max_subarray, k);
        OUT("NO");
    }
    else if (forgotten_values == 0)
    { // if max_subarray < k, but no forgotten_values to alleviate the issue
        DBGLN("NO--forgotten_values==0");
        OUT("NO");
    }
    else
    { // max_subarray < k, but at least one forgotten_values which is obtained from last_forgotten_ind

        // re-computing this value as if a[last_forgotten_ind] was 0
        //  finds the prefix running subarray max before the current index and the suffix after the current index
        //  since the max_subarray < k, while this is not necessarily the MAX subarray sum, but will become THE MAX subarray sum

        // so sometimes doing the above way might yield suboptimal results that includes suboptimal max subarray from an index before or after
        //      when better subarray exists on the index
        // hence, this new way re-computes it with the prefix and suffix at the index while assuming the original value in a is 0 (hence -2*a[i])
        DBGLN(last_forgotten_ind, a[last_forgotten_ind]);
        a[last_forgotten_ind] = k - (prefix[last_forgotten_ind + 1] + suffix[last_forgotten_ind] - 2 * a[last_forgotten_ind]);
        // NOTE: as long we don't re-use the prefix/suffix this is fine
        //      i.e., modifying the underlying a invalidates prefix and suffix at other indices

        OUT("YES");
        OUT_ITER(a);
    }

    // // this doesnt consider internal subarrays that can go above k while overall being less than k
    // bool has_forgotten_value = false;
    // ll excl_sub_sum = 0;
    // INC(i, n)
    // {
    //     if (s[i] == '1')
    //     {
    //         excl_sub_sum += a[i];
    //     }
    //     else
    //     { // forgotten value
    //         if (excl_sub_sum > k)
    //         {
    //             OUT("NO");
    //             return;
    //         }
    //         excl_sub_sum = 0;
    //         has_forgotten_value = true;
    //     }
    // }
    // if (excl_sub_sum > k)
    // {
    //     OUT("NO");
    //     return;
    // }

    // if (!has_forgotten_value)
    // {
    // }
}

/*

1
5 10
10101
10 0 10 0 10

Yes
10 -20 10 -20 10
*/