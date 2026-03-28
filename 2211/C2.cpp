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

// b does not have to be a permutation

// isnt this just to make sure a==b??
// only when the window is smaller than the half of the length
// if k>n/2
//      from n-k+1 to k
//          we just have to check any rearrangemnt is fine within this one (I think?)
//          if we think about a window moving to the left, we never have to touch or think about elements in that
//          middle region (i.e., we don't care about its order)
//      so... we just have to find if the set in a in that region matches with set in b (if there's duplicate, there will be one missing)
//      but we have the -1 wildcard
//          to simplify, we can just let -1 be the corresponding element in a if outside the middle region
//          if it's in the middle region, we can just compute length of sets are same offseted by the # of -1s (but this requires if b is a subset of a)
// if k<=n/2
//      a==b element-wise

// C2...

// consider this
// 3 5 3 5 ........
// 5 3 5 3 ........
// this is a valid re-arrangement given some super long array and small k (k=4 for example)
// so we cant do element wise inequality, we have to do frequency maps to ensure frequency is the same
// we also have the -1 wild card
// but first, if there's an intersecting middle region, does it change?
//      too complicated, lets just raw-iterate i from k to n

// ensure f-map is same
// if there's discrepency and -1 is available, try to allocate all the -1 frequencies to each discrepency
//      this can be done s.t. at the end there's no -1... (i.e., discrepency is exactly the amount of -1, if not => NO)
// then, for each increase in index, ensure the new element in a matches with new element of b (if -1, should be the new element of a then)
//       however, if the outgoing element b is a -1, it should just correspond to decrementing the outgoing element a
//   so technically speaking arrangement doesnt matter for the first k element, but matters after (??), but doesn't matter again in the middle region?
//                                                                                  ^^^ in this region
//      lets say k=7
//          5 1 1 1 9 1 1 ?
//          9 1 1 1 5 1 1 ?
//                              if both ? ? are 5 9, then works, if not then fails (ie, the outgoing element must match with the incoming element to ensure
//                              the frequency matches and its the only way to ensure the frequency matches in an overlapping way)
//              OH SO ITS JUST ENSURING FREQUENCY MATCHES

//          5 1 1 1 9 1 1 ?
//         -1-1-1-1-1-1-1 ?  // to ensure frequency matches, we should try to make 5 leave the same place it was assigned (we are not locked on the next increment)
//                  so there's a new locking notion now (lets just leave C2 as it is)

void solve([[maybe_unused]] ll T)
{
    READ(n, k);
    READ_VLL(a, n);
    READ_VLL(b, n);

    unordered_map<ll, ll> fmap_a;
    unordered_map<ll, ll> fmap_b;

    for (ll i = 0; i < k; i++)
    {
    }

    for (ll i = k - 1; i < n; i++)
    {
    }

    if (k <= n / 2)
    {
        INC(i, n)
        {
            if (b[i] != -1 && a[i] != b[i]) // if b is -1, ignore (optimally, b@i = a@i)
            {
                OUT("NO");
                return;
            }
        }
        OUT("YES");
    }
    else
    {
        for (ll i = 0; i < n - k; i++)
        {
            if (b[i] != -1 && a[i] != b[i]) // if b is -1, ignore (optimally, b@i = a@i)
            {
                OUT("NO");
                return;
            }
        }
        for (ll i = k; i < n; i++)
        {
            if (b[i] != -1 && a[i] != b[i]) // if b is -1, ignore (optimally, b@i = a@i)
            {
                OUT("NO");
                return;
            }
        }

        // once we ensure the outer region is equal...
        // middle region at 0-index: n-k to k-1 (inclusive)

        // 2x nlogn
        // set vs multiset on count (if there's many elements that are the same ==> multiset becomes n^2)
        set<ll> sa(a.begin() + n - k, a.begin() + k); // exclusive
        set<ll> sb(b.begin() + n - k, b.begin() + k);

        // the middle region
        ll b_available = 0;
        for (ll i = n - k; i < k; i++)
        {
            if (b[i] == -1)
            { // element of a is present in b
                b_available++;
            }
        }

        // to much O(logn)s within this O(n) ?
        ll count_missing_a = 0;
        for (ll ai : sa)
        {
            if (sb.count(ai) >= 1)
            { // element of a is present in b
            }
            else
            { // el of a not present in el b
                count_missing_a++;
            }
        }
        if (count_missing_a <= b_available)
        {
            // the number of elements in a not in b can all be satisfied with the -1s present in b
            OUT("YES");
        }
        else
        {
            OUT("NO");
        }
    }
}