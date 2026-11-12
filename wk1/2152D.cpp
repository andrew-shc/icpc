#include <bits/stdc++.h>
#include <climits>
#include <cmath>

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
// P.1: it is optimal for Rekkles to first +1 on any elements that are odd (1
//      ops -> possibly 1 additional ops for Poby)
//          if even, it will take 2 ops -> possibly 1 additional ops for Poby
//
// P.2: num. of ops for Poby is floor(log2(b[i]))
//
//      9 9->4->2->1 => 3
//      8 8->4->2->1 => 3
//      7 7->3->1 => 2
//      6 6->3->1 => 2
//      5 5->2->1 => 2
//      4 4->2->1 => 2
//      3 3->1 => 1
//      2 2->1 => 1
//      1 1 => 0
//
//      P.2/1:  Rekkle needs d[i]=pow2(floor(log2(b[i]))+1)-b[i] ops
//              to make Poby use ONE MORE operation to reduce it to 1
//
//      P.2/2: if p[i]>=j for j=permutation(1..n) and i=1..n
//             (i.e., there exists an increasing amount of operation Rekkles
//             need to do to increase Poby's operation. but its a permutation
//             that allows Poby to take on increasing number of operations s.t.
//             Rekkles can never really impact the /2 division from Poby)
//
//             however, if at any point the /2-Poby's op lends itself
//             immediately before the log2 levels, then Rekkles just bump the
//             number once to increase the operation (at most 1) on Poby (bad)
//
// graph reduction????
//
//
// O.1: for each elements, Rekkles can only increase the score AT MOST once
// under very special condition (at most once??? == yes at most once)
//      for example say 7->3->1
//
//      however Poby moves, it will either result the value in 7 or 3 =>
//          all 1 away from the log2s => Rekkles can force-increase # of moves
//          by 1 (force-increase score by 1)
//
//          however, upone Rekkles' move
//              it resets all paths to the first number of each
//              log-level (and are even number => requires at least two
//              operation minimum to increase moves instead of one)
//
//      ==> optimally, Poby moves floor(log2(b[i])) for every i
//  O.1/1: worst-case, Rekkles can AT MOST increase 1 forcing
//                     Poby to move AT MOST floor(log2(b[i]))+1
//
//              but only guarantees to work on single element
//
//              if we extend this to multiple elements, it might not work
//
// O.2: can be better thought of as buffers of remaining ops until the next ops
//      will increase it to the next log-level (force-increase 1 ops for Poby)
//          => forces Poby to operate and reset the buffer to the next (lesser)
//          log-level (before it reaches to 1 => meaning Rekkles woudl be able
//          to force-in op in one go)
//
//=== so much to think about
//
//!! think locally, greedily, for each round, how Poby operates and Rekkles
//! respond (not globally)
//
//! editorial simplifies a lot of the prior observation made here
//!  type a: perfect integer powers of 2, un-ruin-able
//          again, if we think in games,
//              if Rekkles pick type a, Poby picks a
//              by the assumption of type a, it will always take at least 2 ops
//              for Reckkles to force-inc the score and Poby will know it
//              in-time
//!  type b: 2^x+1, lower halves
//          this can be thought of as the problem in the beginning
//          and Rekkles greedily takes them
//          (if Rekkles tries any other it is either type a or type b which can
//          be thought of as the initial case of type c)
//!  type c: similiar to O.1/1,
//          the at most increment of 1 is whenever it is not type a/b
//          (since at SOME POINT the division operated on Poby will be one off
//          from the next power allowing Rekkles to take advantage of it and
//          force increase)
//              this one-off thing can be thought of as any type-a has prime
//              factors of 2 only but type-c have prime factors other than 2
//              which when Poby can only divide by 2 can result the remaining
//              value to be 3,5,7,11,13,17 etc
//                  which when we always apply with floor((x+1)/2)
//                      always results in some >2 PFs => +1 ops
//                          if x is even: its just x'=x/2
//                              => reduces prime factors of 2
//                          if x is odd: its x'=x/2+1
//                              => MAINTAINS the LACK of prime factors of 2
//                                  until the next integer power of 2 hits
//                                  (gaurantee-ing a force-inc in ops)
//
//                          and if x is perfect integer power of 2 then it will
//                          always stay in the 1st case. but if not, at SOME
//                          point it will get STUCK on the 2nd case where x is
//                          odd (because there's some non-2 prime factors
//                          present)
//
//
//                              ~~~~
//                              => always ends in some prime factor
//                              => always odd
//                              ~~~~
//
// and to start the game...
//      (remember, type b/c stays stuck as type b/c)
//      (and, remember, type a (optimally) stays type a)
//
//      b/c (optimally) type a stays in its own track and type b/c stays in
//      their own track, whatever poby does can't really reduce the operation or
//      prevent additional operation
//
//      edge case: Poby optimally takes any elements of 3
//          but that can be generalized into the floor(|B|/2) case where an odd
//          amount of type b means the lower half will be force-increased
//
//
//  so,
//
//!!! score = sum floor(log2(a[i])) + floor(|B|/2) + |C|
//
// clearly, prefix sum along these three tracks should suffice
//
// notice, we can't merely aggregate these per-element since the floor-div
// operation can have different behavior on [l,r] that can't be capture on a
// per-element basis

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n, q);
  IV(a, n);
  IVP(queries, q);

  vll ps_type_a(n + 1, 0);
  vll ps_type_b(n + 1, 0);
  vll ps_type_c(n + 1, 0);

  II(i, n) {
    ll offset = a[i] - pow(2, (ll)log2(a[i]));

    ps_type_a[i + 1] = ps_type_a[i] + (ll)log2(a[i]);
    ps_type_b[i + 1] = ps_type_b[i] + ((offset == 1) ? 1 : 0);
    ps_type_c[i + 1] = ps_type_c[i] + ((offset > 1) ? 1 : 0);
  }

  vll outputs(q, 0);

  II(i, q) {
    ll l = queries[i].first;
    ll r = queries[i].second;

    // 1@ -> 1@
    outputs[i] = (ps_type_a[r] - ps_type_a[l - 1]) +
                 (ps_type_b[r] - ps_type_b[l - 1]) / 2 +
                 (ps_type_c[r] - ps_type_c[l - 1]);
  }

  II(i, q) {
    O(outputs[i]);
  }

  ;
}
