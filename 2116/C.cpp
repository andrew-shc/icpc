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

// rephrase: find the minimum operations to replace all ai's to equal the same via ai=gcd(ai,aj)
//                  given a different element

// O.1: gcd(ai,aj) <= ai (a minimizing operation)
// O.2: since we want ai to be all equal of each other
//          => the number has to be a common denominator (not necessarily Gcd?) of all elements
//              since the output of gcd has to be a common denominator between some two elements
//                  (that eventually reaches to all elements)
// O.3: since gcd always find the greatest common denominator of any two elements,
//          if all elements must be the same, it must also be the gcd of all elements
// O.4: if all elements are the same, they themselves are the gcd and no operation is needed (min ops =0)

// oops accidentally saw the ratings and tags

// consider 24 24 24 42 24 24 24 24
//           6  6  6 42  6  6  6  6
//                    6              n ops? (suppose to be a counterexample)

// consider 24 24 24 42 24  8 24 24
//           6  6  6 42  6  2  6  6 (n-1 ops starting with 42 but what if start with the smallest # the 8?)
//                          2

// consider 24 24 24 42 24  8 24 24
//           8  8  8  2  8  8  8  8 (doesnt work with the smallest also)

// O.5: ORDER w.r.t. index DOESNT MATTER => we can always sort w/ nlogn

// strat?
//      find the quickest way to find global gcd (gcd*) (the smallest gcd since it is a minimizing op)
//      then compute the globally smallest gcd with every other factors
// O.6: min ops = if gcd* present: n - # of ai==gcd*
//                otherwise:       n + the path length to find gcd* (except the final length that computes gcd*)
// O.7: gcd is bounded by the *commonalities* of the factors... and to reach gcd* we have to find an integer that closest
//          to the lowest common denominator.....
//          which means we can first find the number with the smallest number of prime factors (guarantee smallest gcd / a way to find gcd*)
//              BUT, if there are multiple numbers with the same amount of prime factors... find the gcd of that
//                   .... find two elements that produce the minimal gcd
//                  this doesnt improve bc what if we are given an array of numbers each element having the same AMOUNT of factors...
//                  ...
//      O.7.1: this becomes problematic if there many pairs of elements having unique prime factors just between them to be removed.
// O.8: a list of element has x-layer of gcd where each pairs of element has at least x groups of local gcd (including gcd*)
// O.9: an element that requires the least ops/path to reach to gcd*
//          is an element where it takes the least amount of elements to gcd it to gcd*
//      O.9.1: n-1+n-1 is the max of # the min ops possible (n-1 to reach gcd* and n-1 more to use the founded gcd* to convert all other to gcd*)
//      O.9.2: this is a question of maximum spanning with minimum number of groups on x's (element aligned) (a p.f. missing w.r.t. a p.f. common in 2 or more element)
//                      (a p.f. that is unique to itself will always be removed by the minimizing operation of gcd)
//          O.9.2.1: a set of groups where union of it = all x and the amount of groups are minimum
//                      how?

// per editorial HINTS => DP????

// if we do dp on gcd, we will eventually find the gcd* at the end dp[i] = gcd(dp[i-1], a[i])
// if dp[i]<a[i]: the ops is needed to reach the lower gcd
//                       (for a[i], but what about previous a[i] that was at local gcd already?)
//                       so actually, if a gcd is lowered (and since we're only going one by one to the right)
//                          the dp on answer (the min ops) would be i (since every element before it needs to be reduced to the new low gcd)
//                              including the incoming a[i]
// if dp[i]==a[i]: dp[i]=prev; ops not needed since the element is already at the lowest left-gcd
// consider 12 20 30 again
//          12,20>gcd(12,20)=4
//          30>gcd(4,30)=2
//          isnt that a total of 3 but it should be 4....
//              on the 3rd element, since it decreased it goes from 2 to 4 ops because
//              1 ops to reduce the current element to the new low gcd
//              another +1 ops if this new gcd is unreachable directly if the gcd was computed just on the recent pair????
//                  but the latest element can compute gcd* with another way earlier element, this would just be +0 ops
// first compute gcd*
// in the dp, if we find the new gcd to be lower but not gcd*, +2 ops (1 for decreasing the current element, 1 for finding a local left-gcd)
//               since if it reaches gcd* then no more additional decrement and from the intermediate gcd we can reach gcd*
//                                                                          how do we know it must be from intermediate gcd and not pair-wise gcd directly?

// per editorial's solution

// same thing as observed before, if the gcd* is not present in a, we got to find an element
// that takes the least amount of ops to reach gcd*

// we can do this by using (backwards?) dp in a weird and interesting way....
//  f[i] = MAX   for all i from 0 to max(a)
//  f[a[i]] = 0 (to make it explicit)
//  f[gcd(x,a[i])] = min(f[gcd[x, a[i]]], f[x] + 1)  (the min ops to get here from x or a[i] or from elsewhere but f[a[i]]=0 already)
//  but we can optimize to O(max(a)^2) with preprocessing h

// not submitting ==>
// not only can we bruteforce over the bits (i.e., for each integer find a range within 200 elements to find an element that satisfies a condition) [from one of the few problem As where I had look at the solution]
// but also do search or dp over the values of the elements or values themselves
// => be comfortable on doing operations over all possible values within the range of the values (e.g., ai < 5000, get ready to iterate over every *possible* element)

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//              but if the gcd(20,30)=10>gcd(4,30)=2, that means the new element would've not reache

// ~~~~~~ too complicated
// O.9: .........
//          finding the path length to gcd* equates to number of length-spanning cycle + unaligned length-spanning unique gcds
//              (except the largest aligned groups of them since we can just bypass at least one group of them)
//          length-spanning uniques are a layer where there's 2 or more local gcds that are connected
//              s.t. the gcd of any two elements has a p.f. of this group of length-spanning uniques except at a hole
//                  wait.... it's not just a single, there can be multiple holes among the gcd barriers
//                      and we got to find the one with the thinnest gcd barriers to reach to gcd*
//                          (doesn't has to be length spanning, and length-spanning cycle is just length-spanning with no holes)
//   we can represent the barriers at each element as one length

// ~~~~~~~ whats happens if every pair has 2 layers of gcd (i.e., a group of factor part of gcd*, another group of factor part of another local gcd)
// O.8: computing gcd* (gcd of all elements), if gcd* not present, that means there exists a pair of integer

// ~~~~~~~~~~~~~~ lol no, if any two pair's gcd is higher than the global gcd => more than n ops
// O.6: if we find two elements s.t. gcd(a*,aj) is the smallest gcd of any pairwise gcd
//          we can let a* be the result of the smallest gcd and any elements gcd'd on a* will be a*
//          => so n ops maximum (if we can find the smallest gcd => smallest intersection of factors)

void solve([[maybe_unused]] ll T)
{
    READ(n);
    READ_VLL(a, n);
}