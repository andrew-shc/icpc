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

// start: 2053
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
// !! GO BY MIN-LENGTH, not by 1st-position fixed (for the k-subarray)
//          (in any position) but still ordered
//
// IF k=m => ALWAYS POSSIBLE (....+1+1+1+...)
// IF k<m => ALWAYS POSSIBLE (....+1+1+1+...+1+(m-k+1))
// IF k>m => BY THE MOD ADDITION RULE
//     not div. + not div. + not div. + complementary = s.t.
//
//
//  k=50 m=7
//
//  2+2+2+... will it ever divide by 7 no~~~C actuall yess
//  2+2+2+2
//  2+2+2+... will it ever divide by 5 yes
//      4+4+4+4
//  2+2+2+... will it ever divide by 3 yes
//  15+15+15+15 will it ever divide by--
//
//
//
//  lcm cycle?
//      20 > 6? lcm=60 and not 120??
//
//      6+6+6+6+6+6+6+6+6+6
//                        |
//                 20 would divide 60
//  maximum of lcm??
//
//  given k>m,
//
//  we need to add by m/2 (that maximizes...)
//  wait wouldnt 1 technically maximize or m-1???
//      as in that's the maximum??
//  k=8 m=7
//
//  6+6+6+6+6+6+6+6
//  1+1+1+1+1+1+1+1
//  3+3+3+3+3+3+3+3
//
//  k=8 m=7
//
//  1 1 1 1 1 1 6 6
//
//  if think of adding as cycling through the MODULO cycle
//      we want to avoid hitting the 0 on the cycle
//
//
// H.1: k>m never works
//
// consider the mod-space of m=4 {0,+1,+/-2,-1}
//
// 1  1  1  1 <- largest
// 2  {+1, -1} 2 {-1. 1}
//
//
//      suppose H.1:
//          proof by induction? (for m++)
//
//              suppose base case k>m=1:
//                  clearly, every number THEMSELVES are divisible by m, then
//                  k=1. however, k>1. contradiction. hence, for m=1, it doesn't
//                  work.
//
//              induction hypothesis:
//                  suppose l is bad. we want to show l+1 is also bad.
//
//                  given say k1>l is bad, we must show k2>l+1 is bad.
//                  assuming k1>l and k2>l+1 themselves are true (not whether
//                      good/bad) => k1>=l+1>l
//                                   k2 >l+1
//
//                  for a k1>l to be bad (i.e., a contradiction exist), then
//                  there must be k1<=l => either each elements are 1 or >1
//
//                  for k2>l+1 to be bad, will there exits the k2<=l+1?
//
//                  if we know sum of combination of {0,1,..,l-1} (mod l) can
//                  only be achieved at a length k that is at most l
//                      can we show with an additional l (mod l+1), the length k
//                      can at most be l+1?
//
//
//                      induction doesnt seem to really help since we can always
//                      just re-arrange the elements in the array (it seems
//                      like) with elements in an increasing mod-space and
//                      there's no observed property invariant to the
//                      arrangements of the array, yet
//
// H.2:
//      (similiar to the soln.)
//
// soln:
// ~~~
//      when m<k, by the time k reaches m, there will be no unique remainder
//      (mod m) left and any elements in the mod-space that appears after will
//      have a duplicate modulo ==> there exists a smaller subarray formed by
//      those two duplicate modulo that will be divisble by m. hence, m<k =>
//      never works. because when that smaller subarray with duplicate modulo
//      exist (i.e., any duplicate modulo)
//      ~~~
//
// we have to consider IN TERMS of sum (notice, when a problem is asking
// something regarding sum, THINK IN SUMS)
//      in this case, the worst case would be a prefix-sum fixed at 1st position
//          at every prefix-sum, we do not want the same modulo since if they
//          have the same modulo => removing both sides of the array that have
//          the duplicate elements results in a sum that is divisble by m (and
//          by removal, we suggest a smaller subarray)
//
//          x<y, l1=l2
//          ps[x] = l1 (mod m)
//          ps[y] = l2 (mod m)
//
//          subarray SUM from x+1 to y = ps[y]-ps[x] === l1-l2 === 0 (mod m)
//          and, per prior observation, 0 (mod m) is the point of bad in the
//          mod-cycle
//
//          (technically it should include one of the element in the raw-space
//          CORRESPONDING to the duplicate prefix-SUM mods)
//
//          and in the best of the worst case scenario, it would be every
//          elements CORRESPONDS to a unique prefix-SUM mods until it is no
//          longer possible (m<k)
//
//
//
//          ~~~removing one side of the array that contains
//          one of the duplicate modulo (subtract that portion) results in a SUM
//          that is divisible by m~~~
//
//
//
//
//
//
//~~~~
//                      clearkly, k*0, k*1, k*2, ..., k(l-1), k(l) are all
//                      divisible by m when k reaches m
//
//                      but, any other config that allows k>m?
//~~~~
//
//
//~~~~~~~~~~~~~
// IF k>m => ALWAYS IMPOSSIBLE
//
//      k=8 m=7 n=??
//      (2+2+2+2+2+2+1+1)
//                   ---
//       ----------- 12
//
// k <= n
//
// ~~~~~~
// IF k>m => ensure every additional element before reaching k is NOT DIVISIBLE
//           by m (n becomes important)
//      k=4,m=3
//      1+1+2+2+1+1???
//
//      1+1+1+1
// ~~~
//

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n, k, m);
  if (m >= k) {
    O("YES");
    vll a;
    II(i, k - 1) { a.PB(1); }
    a.PB(m - k + 1);
    II(i, n - k) { a.PB(1); }
    // 1 1 1 1 m-k+1
    OIT(a);
  } else {
    O("NO");
  }

  ;
}
