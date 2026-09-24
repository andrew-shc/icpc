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

// P.1: order doesn't matter on a
// O.1: min always produce the smallest element; gcd produces smallest element or smaller (down to 1)
//          => if there are >=2 equal mins, we can let the one min be the gcd-group and the other min be the part of other min-group
//          => if there are 1 unique min => if we place the min in the gcd, the min-group can never reach a value below gcd
//                                          BUT if we place the min in the min-group, the gcd-group CAN produce a smaller value then the min of the gcd-group
//                  => can gcd(group without the min) == min(group with the min)?
//      O.1.1: assume the single min element is already part of the min-group, the question becomes where do we put the rest of n-1 elements?
//                      if the min is 1, if all remaining n-1 are coprime works
//                                          but if all elements are not coprime of each other (fails, bad example)
//                      if the min is 2, if all remaining n-1 are coprime in the gcd-group
//                          remove elements from the gcd-group into the min-group until the gcd(gcd-group) produces the min
//                              unless its impossible...
// O.2: gcd needs at least one element
// O.3: to have gcd(gcd-group) = the unique min => find all the prime factors of each element
//          if a group of element's prime factors intersects to produce a product that equals to the unique min
// O.4: we can try aj%min==0 (where aj is the n-1 element excluding min)
//      i.e., find all n-1 elements that are divisible by min
//      O.4.1: then, divide these n-1 elements by the min. now, if we find any divisible divided element that are coprime of each other => guaranteed gcd of min
//      O.4.2: by default, the larger the gcd-group the smaller it will be to be co-prime (of the divisibles)
//         O.4.2.1: and if even the largest gcd-group of the divisibles are not mutually co-prime, no numbers are coprime of each others => NO
// O.5: is there an efficient way to compute gcd of all n elements? (let's just try c++ gcd first)

// after AC
//  DONT GET BOGGED DOWN BY THE SEARCH FOR ELEGANCE, gcd of N elements are not slow even when each element can reach up to ^18

void solve([[maybe_unused]] ll T)
{
    READ(n);
    READ_VLL(a, n);

    sort(a.begin(), a.end());
    ll mn = a[0];
    vll gcd_group;
    INC(i, n - 1)
    {
        if (a[i + 1] % mn == 0)
        {
            gcd_group.push_back(a[i + 1] / mn);
        }
    }

    if (gcd_group.size() == 0)
    {
        OUT("NO");
    }
    else if (gcd_group.size() == 1)
    {
        if (gcd_group[0] == 1)
        {
            OUT("YES");
        }
        else
        {
            OUT("NO");
        }
    }
    else
    {
        ll g = accumulate(gcd_group.begin() + 1, gcd_group.end(), gcd_group[0], [](ll ga, ll gb)
                          { return gcd(ga, gb); });

        if (g == 1)
        { // co-prime of each other
            OUT("YES");
        }
        else
        {
            OUT("NO");
        }
    }

    // INC(i, n)
    // {
    //     vll factors;
    //     ll ai = a[i];
    //     for (ull f = 2; f * f <= ai; f++)
    //     {
    //         while (ai % f == 0)
    //         {
    //             ai /= f;
    //             factors.push_back(f);
    //         }
    //     }
    //     if (ai > 1)
    //     {
    //         factors.push_back(ai);
    //     }

    //     DBG(i);
    //     DBG_ITER(factors);
    // }
}