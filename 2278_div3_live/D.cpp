#include <algorithm>
#include <bits/stdc++.h>
#include <climits>

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using vll = std::vector<ll>;
using dll = std::deque<ll>;
using pll = std::pair<ll, ll>;
using vpll = std::vector<pll>;

// prefix sum
#define PS(v_ps, v_in)                                                         \
  vll v_ps(v_in.size() + 1, 0);                                                \
  for (ll i = 1; i < v_in.size() + 1; i++) {                                   \
    v_ps[i] = v_ps[i - 1] + v_in[i - 1];                                       \
  }

// suffix sum
#define SS(v_ss, v_in)                                                         \
  vll v_ss(v_in.size() + 1, 0);                                                \
  for (ll i = n - 1; i >= 0; i--) {                                            \
    v_ss[i] = v_ss[i + 1] + v_in[i];                                           \
  }

#define PB push_back
#define PF push_front
#define ST(v) std::sort(v.begin(), v.end())

#define II(i, n) for (ll i = 0; i < n; i++)

#define DD(i, n) for (ll i = n - 1; i >= 0; i--)

#define OIT(a)                                                                 \
  {                                                                            \
    for (auto &el : a) {                                                       \
      std::cout << el << " ";                                                  \
    }                                                                          \
    std::cout << std::endl;                                                    \
  }

template <typename... Args> void cout_vars(Args... args) {
  ((std::cout << std::fixed << std::setprecision(10) << args << " "), ...)
      << std::endl;
}
#define O(...) cout_vars(__VA_ARGS__)
#define OHYES std::cout << "YES" << std::endl
#define OHNO std::cout << "NO" << std::endl

#define IS(s)                                                                  \
  string s;                                                                    \
  cin >> s;

#define IV(a, n)                                                               \
  vll a;                                                                       \
  for (ll i = 0; i < n; i++) {                                                 \
    ll ai;                                                                     \
    std::cin >> ai;                                                            \
    a.push_back(ai);                                                           \
  }

#define IVP(ap, n)                                                             \
  vpll ap;                                                                     \
  for (ll i = 0; i < n; i++) {                                                 \
    ll ai, bi;                                                                 \
    std::cin >> ai >> bi;                                                      \
    ap.push_back({ai, bi});                                                    \
  }

template <typename... Args> void read_vars(Args &...args) {
  (std::cin >> ... >> args);
}
#define I(...)                                                                 \
  ll __VA_ARGS__;                                                              \
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

//
//
//
//
//
//
//
//
//
//
// END MACROS
//
//
//
//
//
//
//
//
//
//

void solve(ll T);

int main() {
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  // comment out or set to true when working with interactive problems
  //
  //
  ios_base::sync_with_stdio(false);
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //

  cin.tie(NULL);
  cout.tie(NULL);

  ll T = 1;

  // comment out when working w/o testcases
  cin >> T;

  ll t = T;
  while (t--) {
    solve(T - t);
  }

  return 0;
}

// start:
//   end:

//
//
//
//
//
//
//
//
//
//
// NOTES
//
//
//
//
//
//
//
//
//
//
//
// worst-case naive way:
//  find the mean:
//      and make the array elements converge towards it for minimal ops and cost
//
// clearly:
//  worst possible min_ops=largest_element-smallest_element
//
//
// why do i get the feeling that there's no tradeoffs??
//
// or rather every elements away always have a cost of 1... there no better way
// to do it?
//
// ok let's actually do the average, but what if the mean is non-integer?
//
// say (1+1+3)/3 = 5/3 = 1.66666
//
//      2 2 2 ? (either 1 1 1 are fine)
//
//      1+1+2
//
//      1 1 1
//
//
// what does it mean for an AVERAGE to be non-integer?
//
// it just means at the average-th level, some would have +1 distance while the
// others have -1 distance
//
//
//     (1+1+1+1+15)/5 = 19/5 = 3.6
//
//      3 3 3 3 3 ?
//      4 4 4 4 4 ?
//
//      |-----|
//      4x0=0   14
//      4x2=8   12 = 20
//      4x3=12  11 = 23 (clearly not mean/average)
//
//      least squares???
//      this is discrete...
//
// or....1 1 1 1 1 ?
//
//
//
//
// ternary search?
//
//
//
// 2.6+2.6+2.6+2.6+11.4 = 10.4+11.4 = 21.8
//
// sqrt(21.8) ~= 4
//
// no thats std dev
//
//
//
// OR, just lock the mins/maxes??
//
// binary search till the halfway point???
//
// given levels from min to the max
//      count the numbers of elements exactly at i=min..max
//      or prefix it?
//
//      binary search it for the halves? (almost like a CDF)
//
//      then you'll  get the imaginary elements where we want all the a to be
//      equal at a minimal cost? at a a minimal cost!
//          but min_ops has to be the range of the values regardless (except 1
//          in the middle)
//
//      what if the halves are non-integer?
//          => that's actually fine, the point from floor(halves) to
//          floor(halves)+1 works
//
//          HOWEVER, if it an integer X, we need to be worried
//          we can end the operation at the level below or at the level above
//
//          to make it safe, we just do floor(halves)
//              and check both sides??
//              floor(halves) and floor(halves)+1
//              and floor(halves)-1?
//
//
//              or binary search it until the deltas cross??
//
//
//
//          consider   3       ---x
//                     2       --x|   <-- exactly at 3 then it's good
//                     1       -x||
//                                        if non-integer..
//
//                                        idk say total is
//
// does it even matter??
//
// REMEMBER THE NO TRADEOFFS OBSERVATION???
//
// REGARDLESS HOW WE DO IT, IT IS STILL THE SAME!!!!!
// DECREASE OR INCREASE <== KEY INVARIANCE OF THE NO-TRADEOFFS????
//
// however if we have a
//
//
// .....xxxxxxxxxxxxxx
// ...xx..............
// ..x................
// ...................
// .x.................
// ...................
// ...................
// ...................
// x..................
//
// is the key invariance on the # of duplicate mins/maxs??
//
// DEC...............x
// ...................
// ................xx.
// ......xxxxxxxxxx...
// .....x.............
// ...................
// ....x..............
// ...................
// ...................
// ..xx...............
// .x.................
// x...............INC
//
// i think just binary search on two things
//
// cost of decrement at level i (prefixed from top),
// cost of increment at level i (suffixed from top)
//
// binary search (say from the bottom) until the cost increases (then linearly
// go back until the cost increases WHILE keeping track of min_ops)
//
// OR linear search (b/c max elements of 10^5, the 10^9 range is fine if we keep
// unique elements)
//
//  MIN OPS = (max elements - min elements)
//
// IMPL:
//      ordered freq_map
//      => cost_of_inc, cost_of_dec (prefix/suffix sums)
//      linear search for min_cost
//      O(min_cost, min_ops=max-min)
//
//-------
// for min_cost, the current way is inefficient...
//      there's a more optimal way
//
// instead of
//
// *******
// ******
// *****
// ****
//     ****
//    *****
//   ******
//  *******
//
// do this
//
// *
// **
// ***
// ****
//     ****
//      ***
//       **
//        *
//
// (and the incremenents and decrements are flipped)
//
//~~~~ in this manner (well actually the previous approach also), the total cost
// is
//~~~~ invariant (whatever the level is, the amount of *'s )
//
//
// just minimize over the 2nd approach
//
// (you also have to SORT THE ELEMENTS ALSO!!!!)
//
// !!! checked editorial, similiar approach but more intuitive
//
//!!!! notice, the editorial uses min(i,n-i)
//      ...while after sorting it is monotonic, but we're not searching for the
//      point of flipping from i to n-i (or n-i to i)
//
//      we're trying to find the (MIN) TOTAL COST (an aggregate). but for each
//      levels (i.e., AT a specific value constrained on the elements), to find
//      the aggregate, we can naively do a prefix/suffix accumulation of it and
//      find which configuration is the best (as observed before).
//
//      but by the monotonicity (or really just greedy on the given !! two
//      optimal choices !! as mentioned by the editorial over the levels)
//          we can just do min(i,n-i)
//
//          because the moment we flip, we are guaranteed to not need to flip
//          back (which if not guaranteed, can be complicated) WHILE ALSO the
//          point of flipping is ALSO OPTIMALLY the location where we would want
//          to flip the operation
//              (because when we flip, we also want to flip the direction of the
//              operation: increment <-> decrement)
//
//      remember, this is all supported by the fact where-ever we optimize
//      towards, every element has to go through conseuctive neighboring values
//      until the level is reacheed (i.e., no skipping, no special tradeoffs to
//      consider other than between the two optimal choices)
//
//      it also similiar to that other graph question where we assume the
//      current neighbor is un-optimal but all previous operation (before i) are
//      optimal (flattened)

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n);
  IV(a, n);

  ST(a);

  ll min_cost = 0;
  II(i, n - 1) { min_cost += (a[i + 1] - a[i]) * min(i + 1, n - i - 1); }
  //  min arg 1: increment the prefix (up to i)
  //  min arg 2: decrement the suffix (down to i+1)
  //  where overlapping pairs of (i, i+1) is scanned over the array

  // // automatically ordered (not ordered by insertion)
  // map<ll, ll> ao_freq;
  // II(i, n) { ao_freq[a[i]]++; }
  //
  // vector<pll> ao_freq_v(ao_freq.begin(), ao_freq.end());
  //
  // // for (auto &[val, freq] : ao_freq) {
  // // }
  //
  // ll m = ao_freq_v.size();
  // ll min_cost = LLONG_MAX;
  //
  // vll cost_of_dec(m + 1, 0);
  // vll cost_of_inc(m + 1, 0);
  // ll k = 0;
  //
  // for (ll i = 1; i < m; i++) {
  //   // k += ao_freq_v[i - 1].second;
  //   //
  //   // cost_of_dec[i] =
  //   //     cost_of_dec[i - 1] + (ao_freq_v[i].first - ao_freq_v[i - 1].first)
  //   *
  //   //     k;
  //   k += ao_freq_v[m - i - 1].second;
  //   cost_of_dec[i] = cost_of_dec[i - 1] +
  //                    (ao_freq_v[m - i].first - ao_freq_v[m - i - 1].first) *
  //                    k;
  // }
  //
  // k = 0;
  // for (ll i = 1; i < m; i++) {
  //   // k += ao_freq_v[m - i - 1].second;
  //   // cost_of_inc[i] = cost_of_inc[i - 1] +
  //   //                  (ao_freq_v[m - i].first - ao_freq_v[m - i - 1].first)
  //   *
  //   //                  k;
  //   k += ao_freq_v[i - 1].second;
  //
  //   cost_of_inc[i] =
  //       cost_of_inc[i - 1] + (ao_freq_v[i].first - ao_freq_v[i - 1].first) *
  //       k;
  // }
  //
  // // opt to @ smallest: cost_of_dec[m-1] + cost_of_inc[0]
  // // opt to @ largest: cost_of_dec[0] + cost_of_inc[m-1]
  // // opt to @ 2nd smallest: (cost_of_dec[m-1]-cost_of_dec[1]) +
  // cost_of_inc[1]
  // // ~~~~~~~~~~ ^^^^ flip the order
  // //
  // //
  //
  // II(i, m) { min_cost = min(min_cost, 0LL); }

  // vll cost_of_inc(m + 1, 0);
  // ll k = n;
  // // for (ll i = m - 1; i >= 1; i--) {
  // //   // largey key - smaller key (local height)
  // //   //
  // //   // smaller key -> larger key
  // //   //
  // //   // multiplied by the k needed (so exclude anything from the larger key
  // //   and
  // //   // itself)
  // //
  // //   k -= ao_freq_v[i].second;
  // //   cost_of_inc[i] =
  // //       cost_of_inc[i + 1] + (ao_freq_v[i].first - ao_freq_v[i - 1].first)
  // *
  // //       k;
  // // }
  //
  // for (ll i = 1; i <= m - 1; i++) {
  //   // we're increasing from the bottom to m=i
  //   // which corresponds to the sorted order of the freq (from bottom to top)
  //
  //   // we unlock all the smaller elements that needs to be increased
  //   k -= ao_freq_v[i - 1].second;
  //   cost_of_inc[i] =
  //       cost_of_inc[i - 1] + (ao_freq_v[i].first - ao_freq_v[i - 1].first) *
  //       k;
  // }
  //
  // // because we are excluding the largest and the smallest
  // // cost_of_inc and cost_of_dec from i=1..m-1
  //
  // vll cost_of_dec(m + 1, 0);
  // k = n;
  // // for (ll i = 1; i <= m - 1; i++) {
  // //   // cost to decrement
  // //   //
  // //   // larger key - smaller key (local height)
  // //   // we start from the larer key -> smaller key
  // //
  // //   // but we exclude in the other direction now (hence i-1)
  // //   k -= ao_freq_v[i - 1].second;
  // //   cost_of_dec[i] =
  // //       cost_of_dec[i - 1] + (ao_freq_v[i].first - ao_freq_v[i - 1].first)
  // *
  // //       k;
  // // }
  //
  // for (ll i = m - 1; 1 <= i; i--) {
  //   // we're decreaseing from the top to m=i
  //
  //   // we unlock all the larger elements (from the right) that needs to be
  //   // decreased (which corresponds to i also going down along the sorted
  //   order) k -= ao_freq_v[i].second; cost_of_dec[i] =
  //       cost_of_dec[i + 1] + (ao_freq_v[i].first - ao_freq_v[i - 1].first) *
  //       k;
  // }
  //
  // ll min_cost = LLONG_WIDTH;
  //
  // /*
  //  *
  //  * ..x
  //  * .x.
  //  * x..
  //  */
  //
  // II(i, m) {
  //   // again
  //   //
  //   // if i==0 (smallest or AT min)
  //   //  cost_of_inc[0]==0 + cost_of_dec[0+1]==large
  //   // if i==m-1 (largest or AT max)
  //   //  cost_of_inc[m-1]==large + cost_of_dec[m-1+1]==0
  //   //  if i==1
  //   //
  //
  //   DBGLN(i, cost_of_inc[i], cost_of_dec[i + 1]);
  //   min_cost = min(min_cost, cost_of_inc[i] + cost_of_dec[i + 1]);
  // }

  // II(i, m) {
  //   // for each mth level
  //   // we want all values to be m
  //   //
  //   // for i==1...m-1
  //   //     i==(0...m-2) + 1
  //   // that means we do not need to include the cost of inc and cost of
  //   decrete
  //   // for values AT m
  //   //
  //   // so how?
  //   //
  //   // for example, for i==0 (with key sorted from small to large)
  //   //    we want all values except the min to be decrement'd
  //   // so, cost_of_dec[i+1]
  //   //
  //   // or
  //   // for i==0, we want all the
  //   //
  //   // if i==m-1
  //   // cost_of_inc[]
  //   //
  //   // flipped this i==0 is the top
  //   //
  //   // if i==0: we want
  //   //
  //   // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^^
  //   //
  //   // if i==0: what's the cost to make all values the smallest?
  //   //
  //   // ~~~~~~ ^^^
  //   //
  //   // if i==0: what's the cost to make all values the largest? (except the
  //   max)
  //   //
  //   //      cost_of_inc[1] + cost_of_dec[0]==0
  //   // if i==m-1:  what's the cost to make all values the smallest?
  //   //
  //   //      cost_of_dec[m-1] + cost_of_inc[m]==0
  //   //
  //   // if i==1: what's the cost to make all values the 2nd largest?
  //   //
  //   //      cost_of_inc[2] + cost_of_dec[1]
  //   //
  //   // its just cost_of_inc[i+1]+cost_of_dec[i]
  //
  //   min_cost = min(min_cost, cost_of_inc[i + 1] + cost_of_dec[i]);
  // }

  ll min_ops =
      *max_element(a.begin(), a.end()) - *min_element(a.begin(), a.end());

  O(min_cost, min_ops);
  ;
}
