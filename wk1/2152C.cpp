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
// P.1: output -1 whenever the number of 1s or 0s are NOT divisible by 3
//          can be done in O(q) by prefix-count
// P.2: if optimally packed in 111000111 etc...
//          => sum of groups of 3-zeros and 3-ones
//
//      P.2/1: for every swapped pairs we increase the cost by +2*distance
//              (something along the lines of that)
//              (probably not since we're doing min of the two distances)
// P.3: greedy over the index selection
//      clearly, if we pick a 1 s.t. there's a 1 in-between that was
//      INTENTIONALLY not picked => we can reduce the cost by picking the 1
//      in-between. furthermore, since the cost will for the opposing group (in
//      this case, a 0) will at most reduce by 1 in both cases => therefore, it
//      is greedy to pick the nearest indices. (even if we re-index
//      them)
//          => this comes down to what order to apply the operation?
//
//          P.3/1: the order of operation is also greedy
//              if we have a case of 110101011.
//                  clearly, picking 1 would reduce the cost of 0 later on
//              but a 0 with some gaps will have a higher cost when operated
//              while NOT GAURANTEEING a reduction of cost on the other (or
//              always 1 => invariant, considering there's only 1 or 0)
//
//              but to be more conservative in our understanding, we should just
//              pick the smallest cost first (and the most intuitive also)
//
//              maybe one should consider the invariance?
//              well clearly in this case we just show that it is not invariant
//              to the order of op and we would still want to pick 1 first
//              because of the existence of adj-dup 1s
//
//
//              actually, the invariance does exist. it's the matter if 1-cost
//              operation exists initially.
//
//              since after 1 operation, a dup-adj 1s/0s must exist.
//                  and each operation MUST add dup-adj 1s/0s by the greediness
//                  of index-picking of the operation
//
//                  => sum of groups + whether there exists a 1-cost op in the
//                  beginning???
//
//                      recall, the cost of the operation operates on the
//                      MINIMUM distance between two indices => if we're able to
//                      make any opposing group's one of their distance merge
//                      (become dup-adj) => min-cost becomes 1 for it => sum of
//                      groups (for the rest of the ops)
//
//                      in fact, we can always show an example by greedily
//                      taking operations from left to right (b/c invariance of
//                      order ???)
//
//                      remmeber, this is only possible b/c they're binary
//                      states
//
//                      however, this would be O(nq) naively
//                      even if we check that all of the groups are perfectly
//                      collated (1 0 1 0 1 0 1 ...)
//
//                      in fact, by the word "prefectly" should show that we
//                      could just look for these patterns specifically
//
//
//
// also consider the following case..
//      0 0 1 0 0 1 0 1 0 1 0 1 0 1 ....
//
//      0 0 1 0 0 1 1 0 0
//
//      0 0 1 0 0 1 0 1 0
//
//      no doesnt matter, the min-dist is really strong ensuring most cost are 1
//      (and at most 2)
//
//      0 0 1 0 0 1 0 0 1
//
//      a better way to say is
//          1 0 0 1    will still have min cost of 1
//                     since then we can take any other 0s out
//                     for a min-cost of 1 that allows the 2 1s
//                     to become 1 1 for a min-cost of 1 again (and repeat and
//                     vice versa 1<->0)
//
//          1 0 0 0 1  unfortunately/fortunately, if we increase to 3-dup-adj it
//                     is clear
//
//          1 0 1      if for all array requires only ONE min-cost of 2 in the
//                     beginning
//
// ~~~ but sum of q is constant??
//
// prefix sums of booleans?
//      if a[i]!=a[i+1] => b[i+1] = b[i]+1 # change
//      if a[i]==a[i+1] => b[i+1] = b[i]   # no change
//
//  if r-l+1 == b[l]-b[r-1]:
//      min_cost += 1
//

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

  // 1@
  vll p0(n + 1, 0);
  vll p1(n + 1, 0);
  vll b(n + 1, 0);
  b[1] = 1;
  // 1 0 1 0 1 0 (!= only compares in-between => 5 when it should be 6)
  // @1
  //   @2
  //     @3 ..
  II(i, n - 1) {
    if (a[i] != a[i + 1]) {
      b[i + 2] = b[i + 1] + 1;
    } else {
      b[i + 2] = b[i + 1];
    }
  }

  II(i, n) {
    if (a[i] == 0) {
      p0[i + 1] = p0[i] + 1;
      p1[i + 1] = p1[i];
    } else {
      p0[i + 1] = p0[i];
      p1[i + 1] = p1[i] + 1;
    }
  }

  vll min_costs(q, 0);

  II(i, q) {
    auto [l, r] = queries[i];
    l--;
    r--;

    if ((p0[r + 1] - p0[l]) % 3 == 0 && ((p1[r + 1] - p1[l]) % 3 == 0)) {
      min_costs[i] = (p0[r + 1] - p0[l]) / 3 + (p1[r + 1] - p1[l]) / 3;
      // sometimes, b[l-1]==b[l] when all elements between l..r are different
      // that can compute the unintended results
      //
      // hence, we do b[r+1] - b[l+1] == r-l
      // if (r - l + 1 == b[r + 1] - b[l]) {
      if (r - l == b[r + 1] - b[l + 1]) {
        min_costs[i]++;
      }
    } else {
      min_costs[i] = -1;
    };
  }

  II(i, q) { O(min_costs[i]); };
}
