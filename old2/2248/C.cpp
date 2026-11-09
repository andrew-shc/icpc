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
    v_ps[i] = v_ps[i - 1] + v_in[i];                                           \
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

// start: 1726
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
// O.1: since the integers in a[] are merely indices and the score is by
//      quadratic over the length, => pick the longest to shortest length
//      obviously
// P.1: (r-l+1)^2 is quadratic over the intervals [l,r] (inclusive)
//
//
// suppose a[] is split in 1st-half and 2nd-half
//
//  1st-half
//      if all n appears in there => 2n is the best length
//      if all duplicates => n is the best length (depends on the 2nd half)
//
//
//  well ok
//
//  1*f(2n) is the best
//  n*f(2) is the worst
//
// O.2: the first index can only be consumed by intervals that includes it
//      but the second index and so forth (excepth the nth) can be consumed by
//      multiple intervals (well just the first)
//
//      so for each increasing index i=1..n, there are i-1 indices below that
//      can consume the i-th index
//
//  or, we can construct the intervals [l_i,r_i] for i=1..n
//      and sort by the length r-l+1
//
//  while loop until no more intervals:
//      pick the longest length [l_k,r_k]
//      consume it
//      1. any intervals that surrounds k-th interval, just shorten its length
//          (has to strictly/exclusively surround it, no sharing indices)
//      2. any intervals that partially intersects k-th interval, just shorten
//      it to 1 => tradeoffs to consider?? (e.g., 5*f(5) is better than
//      1*f(10)??)
//
//
//      non-greedy (trade-offs to consider)
//
// if the answer wants the score (that depends on the selected intervals)
//      => might be wise to work in the interval-space (how would it look like?)
//
// there's tradeoff to consider, might want to work the answer space on the raw
// score value instead of the length (as previously thought)
//
// dp?
// dp on index?
//
// tradeoffs happens on whether some intervals gets cut-off by some other
// intervals
//
// dp on index? with value being the score?
// index-dp on index?
//
//         1  1  2  3  3  2
// dp[i]   2  2  16 4  4 16
// dp[i]   2  1  6  5  4  3
//
// dp[i-1] = max(mapping[i]-i+dp[mapping[i]], 1+dp[i+1])
//                  ^
//              take the interval sum of the next indices +
//              rest of the sum from dp[interval_mapping[i]] (from the rest on
//                      the right)
//
//                                        ^
//                                   or don't take the interval and treat it
//                                   as an interval that has its other indices
//                                   got consumed (is that true?)
//                                      it's gonna have to be 1 (if partially
//                                      consumed) or whatever its insides got
//                                      shortened to
//
//                                   and take the next-next indice's max score
//
//
// per editorial:
//
//      key insight:
//          (A-B)^2+B^2 <= A^2
//
//      also you can't do things like 2*f(5) where the 5-lengthed interval
//      overlaps (one will partially consume the other) so it's better to
//      exhaustively look for all options (or really two options at the current
//      index i to either take it's interval block or assume it's a singleton)
//      and recurse through it (but of course we can use DP to do it with some
//      basic greedy idea that we just need the max at the current prefix will
//      benefit the later results)
//
//      editorial + chatgpt:
//
//          (regardless, yes we always want the largest interval)
//              yes, there were some incorrect counter-examples that assumed the
//              ability
//                  to sum all the overlapping intervals (but they will just
//                  partially consume each other in our case) => hence, we go
//                  back to the largest/longest interval
//              with this insight,
//                  there's a missed connection of largest interval / maximizing
//                  score to simplifying the problem with overlapping/containing
//                  intervals
//              PER (A-B)^2+B^2 <= A^2 (obviously as initially observed by the
//                  rules of quadratic in a loosely-connected observation)
//                  => we always want the longest subarray that also includes
//                  taking over any smaller subarray FULLY/EXCLUSIVELY/STRICTLY
//                  contained within the longest/longer outer subarray
//
//       ok we have
//
//          dp[i] = max(dp[i-1]+1,              << take the prev. score + 1
//                                                  (score from the ASSUMED
//                                                  singleton)
//                      dp[l-1]+(i-l+1)^2)
//
//                           ^^ take the first occurence of a_i (=l) and compare
//                           against whatever we used for the dp[i-1]+assumed
//                           singleton
//
//                      NOTICE, regardless if this ai value is first or second
//                      occurence it will always be fixed to go back to the
//                      first location (which would either be AT i as an assumed
//                      singleton or WAY before i, NEVER AFTER i)
//                          assumed singleton which fits perfectly to the
//                          problem statement
//
//
//

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n);
  IVLL(a, 2 * n);

  unordered_map<ll, ll> ind;
  II(i, 2 * n) {
    if (ind.contains(a[i])) {
      // pass
    } else {
      ind[a[i]] = i;
    }
  }

  vll dp(2 * n + 1, 0);

  // II(i, 2 * n)

  for (ll i = 1; i < 2 * n + 1; i++) {
    ll l = ind[a[i - 1]] + 1;
    dp[i] = max(dp[i - 1] + 1, dp[l - 1] + (i - l + 1) * (i - l + 1));
  }

  O(dp[2 * n]);
  ;
}
