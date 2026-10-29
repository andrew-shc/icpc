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
// a1 < ... < an
//
// STRICTLY LT/GT
//
//
// ==> basically,
//      pick any 1s as the first and pick any 3s (that comes after) as the last
//      and pick any combination of 2 (n*2^(n-1) combination of all n 2s within
//      where at least one of the 2 needs to be present)
//
//
// 1 -> 3 (no)
// 1 --> 2 --> 3 (yes)
//
// find the earliest 1 and latest 3
//  count all the 1s that comes before 3
//  count all the 3s that comes after 1s
//
//  (basically they are equivalent because if a 1s has a 3 that comes after,
//  then the 3 must be counted since there is a 1 that comes before like
//  biconditoinally)
//
//  i.e., the counts of 1/3s are bounded (exclusively) within by the most
//  extreme positions of 1/3s
//
//
// IMPL:
//  II:
//      found 1? => count all 3s after
//  DD:
//      found 3? ==> count all 1s after (chronologically)
//  # of 1's x # of 3's
//
//  however, not all 1's can include all possible 3's (e.g., latest 1's canNOT
//  include the earliest 3's if the earliest 3 came before the latest 1)
//
//
// IMPL V2:
//  PREFIX SUM #1s (PS_1)
//  PREFIX SUM #2s (PS_2)
//  PREFIX SUM #3s (PS_3)
//
//  // num of 2s
//  k = PS_2[n]-PS_2[i]
//  cnt += PS_1[i] * (PS_3[n]-PS_3[i]) * (k * binpow(2, k-1))
//         ^^
//        (should be rather 1 and summed over every a[i]==1)
//
//                                              ^
//                                         k also depends on where the 3s are
//
//                                         this work if all 3s are after all
//                                         possible 2s
//
//                                         but some 2s are bound to be beyond
//                                         some of the 3s
//
//  given ps1 & ps3
//
//  for each a[i] == 2
//      prod2[i] = compute their product of number of 1's before and 3's after?
//      ==> this assumes single 2
//
//      sum of all prod2[i]>0 ==> all the possible configs for 1 2 3 (only a
//                                                                  single 2)
//      what about mixing them?
//      1 2 3 and 1 2 3?
//          only works for cases where their and our 1s/3s matches
//
//          this is too complex....
//
// 1 2 2 3
//   a2 a3
//   a2
//      a3
//
// k*binpow(2,k-1) - 1
//                   ^
//           the only times when all cases are the same is when all the
//           2-elements are selected to be present
//
// 1 2 2 2 3
//
//  a2: 2x2 = 4
//  a3:     = 4
//  a4:     = 4
//
//  it's not 2^k-1
//  but k!
//  since we care about the ORDER and we only want one specific KIND OF ORDER?
//      => we do not care about the order
//  a2 a3 a4
//
//  3 x (2x2) = 12?
//  2 x 2 x 2 = 8?
//
//  2^k-1????
//
//  the only unallowed cases is the empty case, otherwise treat them as various
//  combination or presences of 2s from different element with each element
//  decided to be taken or not
//      2^k models that well
//
//  binpow(x): check the bits of x
//      O(nlog2(n))
//
//
// === STUCK: 2 amount varies between various position of selected 3 on a given
// fixed 1 ===
//
//
//  ps2 delimited/index by 3s??
//  but that doesn't really help...
//
//
//  we can march along the fixed ~~ps1~~ a[i] ==1
//      suppose we did a prefix PRODUCT of all combinations of 2s
//
//      for every next 1-element (a[i]==1)
//          we get the REDUCED computed prefix product at that point
//      no it depends on the 1/3-element each with different amount of 2s
//
//
// !!! (editorial)
// !!! new concept: transitional DPs (with 4 states almost like automatons)
//
//      dp[1] = dp[1] +1 (if a[i] == 1)
//
//          // currently just merely tracks all the opening 1s (raw-space)
//
//      dp[2] = 2*dp[2] + dp[1] (if a[i] == 2)
//
//          // counts additional binary possibilities
//          // of including another 2 for existing 2 subarrays OROROR
//          // the additional possibilities of having the current 2 as the FIRST
//          // number 2 for all existing opening 1s
//          //      NOTICE: fixing opening 1s, we do not care where and what to
//          //          account
//          //          for the various ending position of the closing 3s
//          //  also notice how when expanding dp[2] relation shows the actual
//          structure
//          // it basically collapsing all the shared paths into a single sum as
//          a count
//          // and each a[i] == 3 just takes a snapshot of all these
//          possibilities and linearly sums them
//
//          // dp[2] =
//          2*(2*(2*(2*(0+dp_old4[1])+dp_old3[1])+dp_old2[1])+dp_old1[1])+dp[1]
//          // (or a snapshot at the latest dp[3] where an a[i] == 3 occured)
//          // NOTICE: how earlier open 1s is exposed to more x2 factor to show
//          earlier they are the more possibilities they can have
//          //      (in which we can linearly expand this also)
//
//          // (possibilities-space)
//
//      dp[3] = dp[3] + dp[2] (if a[i] == 3)
//
//          // all the possibilities of dp[2] summed and closed with
//          // the closing 3 (think of like capturing all the possibilities)
//
//
//
//      NOTICE: in cases of 1 3 1 3 it is handled with the later 3 having access
//      to both 1s
//      NOTICE: cases like "overlapping" 1  1  3  3
//                                       \--|--/  |
//                                          \-----/
//
//              technically just folds to iself and even with the 1 3 1 3
//              examples above we could've just used dp1[index of 3]
//
//                  oh yes, we're fixing to the closing 3s but we have to
//                  consider the varying starting point of 2s (especially with
//                  their possibilities)
//
//                      this is where the dp[2] = 2*dp[2] + dp[1] becomes VERY
//                      useful
//
//                      it COLLAPSES ALL the simulatenous possibilities as a
//                      numerical COUNT (as previously observed but unrealized)
//                      which does not need expensive tracking of any sort
//
//                      where dp[2] is well-known to track all the possibilities
//                      of 2's started from the 1s

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n);
  IVLL(a, n);

  // ll cnt = 0;
  vll dp(4, 0);

  II(i, n) {
    if (a[i] == 1) {
      dp[1]++;
    } else if (a[i] == 2) {
      dp[2] = ((2 * dp[2]) % MOD + dp[1]) % MOD;
    } else {
      dp[3] = (dp[3] + dp[2]) % MOD;
    }
  }

  // O(cnt);
  O(dp[3]);

  // vll ps1(n + 1, 0);
  // vll ps2(n + 1, 0);
  // vll ps3(n + 1, 0);
  //
  // II(i, n) { ps1[i + 1] = ps1[i] + (a[i] == 1 ? 1 : 0); }
  // II(i, n) { ps2[i + 1] = ps2[i] + (a[i] == 2 ? 1 : 0); }
  // II(i, n) { ps3[i + 1] = ps3[i] + (a[i] == 3 ? 1 : 0); }
  //
  // DBG_ITER(ps1);
  // DBG_ITER(ps2);
  // DBG_ITER(ps3);
  //
  // ll cnt = 0;
  //
  // II(i, n) {
  //   ll k = ps2[n] - ps2[i + 1];
  //   if (k > 0 && a[i] == 1) {
  //     ll bp = 1; // k
  //     // k--; // binpow to be k-1
  //     ll exp = 2;
  //     while (k != 0) {
  //       // DBGLN("AAAAA");
  //       if ((k & 1) == 1) {
  //         // if the current last bit is 1, power by 2
  //         bp = (bp * exp) % MOD;
  //       }
  //       exp <<= 1;
  //       k >>= 1;
  //     }
  //
  //     bp--; // don't count the empty case
  //
  //     /*       cnt += ((ps1[i + 1] * (ps3[n] - ps3[i + 1]) % MOD) * bp) %
  //     MOD;
  //      */
  //     cnt += (((ps3[n] - ps3[i + 1]) % MOD) * bp) % MOD;
  //   }
  // }
  //
  // O(cnt);
  ;
}
