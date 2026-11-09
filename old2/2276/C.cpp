#include <bits/stdc++.h>
#include <climits>
#include <unordered_map>

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

#define IVLL(a, n)                                                             \
  vll a;                                                                       \
  for (ll i = 0; i < n; i++) {                                                 \
    ll ai;                                                                     \
    std::cin >> ai;                                                            \
    a.push_back(ai);                                                           \
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
// we only want subarrays greater than length k
//
//
// 1 1 1 1 1 1 1 1 1
// 1 1 1 1 1 1
//   1 1 1 1 1 1
//     1 1 1 1 1 1
//       1 1 1 1 1 1
// 1 1 1 1 1 1 1 1 1
//
// k=2
//
// v v v v v
// 2 1 3 1 4        mod 2 (nope doesnt work if multiple +1's = back to 0 but no)
// 2 1 3     = 6    +0
//   1 3 1   = 5    +1
//     3 1 4 = 8
// 2 1 3 1   = 7
//   1 3 1 4 = 5
// 2 1 3 1 4 = 11
//
// 0 1 1 1 0
// 0 1 1
//     1 1 0
//
//
// k = something large
// 0 1 1 3 1 9 4 2 0 0 0 0 0 0 0
//
//
// we got to count all the possibilities... DP? (memoized exhaustive search/sum)
//
//
// do[k] = 0
// dp[k+1] = prefix_sum[k+1] divides k?
// dp[k+2] = prefix_sum[k+2]-prefix_sum[1] divides k?
//           prefix_sum[k+2] divides k?  (triangular loop again)
// dp[k+3] = ps[k+3] - ps[2]
//           ps[k+3] - ps[1]
//           ps[k+3] - ps[]
//
//
//
//  suppose k=1... how can one calcualte ths sums of subarrays
//  sub-quadratically?
//
//  every subarray will be divisible by k=1
//  which will be gaussian sum if it were not that the conditions can change
//
//
// has to be DP some invariance index-by-index?
// prefix sum by prefix sum?
//
// ps[n]+ps[k] divides k?
//   ps[k]-ps[0] |k?
// ps[k+1]-ps[1]
// ps[k+2]-ps[2]
// ps[k+2]-ps[1]
//
//
// find all the subarray sum
//  in an increasingly smaller window (towards the right/end) we add the next
//  elements?
//  if any are divisible by 7 => +1
//  continue  // but this is quadratic
//
//
// find the smallest LOCAL groups that divides k?
//      how?
//      when the mod repeats back to the initial? nonono
//      it's when the mod resets but that's hard to find
// if that LOCAL group has a length <k ==>
//      don't count it but keep it as a reference
//
// if there are adjacent LOCAL k-divisible groups
//      => join them
//
// if the LOCAL k-divisible groups are separated by non k-divisible groups:
//      => never be able to join them
//
// but the LOCAL group can be shared such as (but not joined together)
//    k=7  1 6 1
//         ---
//           ---
//
//
// heuristics????
// if k>n/2 nononooo
//
// suffix represents delta...
// if prefix is divisible by k, suffix must have a divisible by k to extend the
// subarray
//
// sets on modulos???????
//
// SETS ON MODULOES
//
// MODULOS MAPPING???
//
// but k can be n
//
// or by the nature of k,n
//      => if k=1, then at most 1 mapping (but n indices)
//      => if k=n, then there's like 1 mapping (1 unique modulo)
//                  (1 indices)
//      => if k=n/2, then there's like at most n/2 mapping with each indices
//              having a sum of n-k
// EXISTING MODULOS MAPPING?
//
// find all subarrays i to k+i for i=1..n-k
//
// map it to each subarrays correspoding modulo sum
//      as a modulo freq. map
//
// not frequencies, but indices
//
//
// map = {
//   +0: [1]
//   +1: [3,5]
//   +2: [2]
// }
// suffix_sum_moduloed =  5 9 2 4 5 6 1 (mod k)
//              say       1 2 0 9 2 3 5
//      do the same?
// suffix_map_modulo
//      key: modulos, value: indices
//
//    now go through each map's key, then for every complementary moduloes,
//          find a pair of indices that sums to n
//          which is still quadratic and a bit complicated
//
// maybe the converse mapping??
//      starting subarray indices and vectors of modulos for that prefix sum?
// suffix_sum_moduloed (from right to left)
//
// map of a map?
// different starting subarray indices mapped to
//      modulos mapped to # of (ending) indices (with more of them as the
//      starting index is smaller)
//~~~~
//
// different ending subarray indices mapped to
//      moduloes mapped to # of (starting) indices
//              (w/ more of them as the starting index gets smaller at the inner
//              map)
//
//              isnt CONSTRUCTING this inner mapping a quadratic complexity???
//
//
// then, the suffix_sum_moduloed can go from right to left <--
//      first, restrict to the ending index (by querying the map)
//      then, get the value of the suffix_sum_moduloed to get its mod-value
//          and then query the COMPLEMENTARY mod in the inner map to query
//          number of elements that complements with the mod (paired together)
//          with the number of starting indices
//
//          key insight: pairings
//          space: bounded by the modulo actually (because we're just counting
//          the number of elements in the inner map)
//
// IMPL:
//      compute suffix_mod_sum
//      compute prefix_sum
//
//
//
//  of course its the special property
//      Pl === Pr (mod k)
//
//      since we ONLY CHECK FOR EQUALITIES (i.e., comparisons/tests),
//      we can compress these tests as a frequency map!!
//
//  so actually previous worry that if we do mod-cycle we fear it will go pass
//  the 0,
//      checkign for equal mods (not for whether both are ZEROES) would be good
//      enough
//
//
//~~      obtain the
//~~      modulo
//
//
// k = 7
// 9 1 7 3 2 6 4 5 9 2 4 5 6 1               ...... triangle
// 9 1 7 3 2 6 4               = 32      +5     +9
//   1 7 3 2 6 4*5             = 28  |7  +9     +2
//     7 3 2 6 4 5 9   *       = 36      +2     +4 |7
//       3 2 6 4 5 9 2 *       = 31      +4 |7  +5
//         2 6 4 5 9 2 4       = 32      +5     +6
//           6 4 5 9 2 4*5   * = 35  |7  +6     +1 |7
//             4 5 9 2 4 5 6   = 37      +1
//               5 9 2 4 5 6 1 = 34
// 9 1 7 3 2 6 4 5
//   1 7 3 2 6 4 5 9
//     7 3 2 6 4 5 9 2
//       3 2 6 4 5 9 2 4
//         2 6 4 5 9 2 4 5
//           6 4 5 9 2 4 5 6
//             4 5 9 2 4 5 6 1
// 9 1 7 3 2 6 4 5 9
//   1 7 3 2 6 4 5 9 2
//     7 3 2 6 4 5 9 2 4
//       3 2 6 4 5 9 2 4 5
//         2 6 4 5 9 2 4 5 6
//           6 4 5 9 2 4 5 6 1
// 9 1 7 3 2 6 4 5 9 2
//   1 7 3 2 6 4 5 9 2 4
//     7 3 2 6 4 5 9 2 4 5
//       3 2 6 4 5 9 2 4 5 6
//         2 6 4 5 9 2 4 5 6 1
// 9 1 7 3 2 6 4 5 9 2 4
//   1 7 3 2 6 4 5 9 2 4 5
//     7 3 2 6 4 5 9 2 4 5 6
//       3 2 6 4 5 9 2 4 5 6 1
// 9 1 7 3 2 6 4 5 9 2 4 5
//   1 7 3 2 6 4 5 9 2 4 5 6
//     7 3 2 6 4 5 9 2 4 5 6 1
// 9 1 7 3 2 6 4 5 9 2 4 5 6
//   1 7 3 2 6 4 5 9 2 4 5 6 1
// 9 1 7 3 2 6 4 5 9 2 4 5 6 1

//
//
// two-pointers???
//
// move the R-point right when not divisible by k
// move the L-point right when divisible by k??
//
// quadratic??
// nlogn??n onononono
//
// prefix_sum
// and prefix sum again?
//
// prefix_sum
// 2nd-order prefix_sum (from k+1...i...n * (n-i+1))

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n, k);
  IVLL(a, n);

  unordered_map<ll, ll> running_prefix_mods; // values auto-init to 0

  ll cnt = 0;

  PS(ps, a);
  // vll prefix_sum(n + 1, 0);
  // II(i, n) { prefix_sum[i + 1] = prefix_sum[i] + a[i]; }
  // II(i, k) { running_prefix_mods[a[i] % k]++; }
  for (ll i = k; i < n; i++) {
    running_prefix_mods.try_emplace(ps[i + 1] % k, 0);
    running_prefix_mods[ps[i - k] % k]++;
    cnt += running_prefix_mods[ps[i + 1] % k];

    // needs to include k+1th, hence
    // ps[i+1]->i+2 and <n becomes <n-1
    // but recall we also need to include 1 to k-th subarray
    // or i+1 to i+k inclusive
    //
  }

  // II(i, n) {
  //   running_prefix_mods.try_emplace(a[i] % k, 0);
  //   cnt += running_prefix_mods[a[i] % k];
  //   running_prefix_mods[a[i] % k]++; // basically gaussian sum
  //                                    // but this needs to be delayed by k (so
  //                                    // not gaussian sum)
  //                                    //
  // }
  O(cnt);
  // example:
  // look for %=4
  // 0 1 2 7 5 4 8 1 4 3 4 0 9
  //           ^     ^   ^          we can do
  //           .     .           +1
  //           .         .       +2
  //                 .   .
  // but be careful with the k-constraint
  // but we have to check whenever the
  //  %L == %{R+1}  (MOD k)
  //  or 0  & k+1 (minimum)
  //
  //  PREFIX_L == PREFIX_R

  // DBLOCK {
  //   vll a = {9, 1, 7, 3, 2, 6, 4, 5, 9, 2, 4, 5, 6, 1};
  // }

  ;
}
