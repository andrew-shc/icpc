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
//  DP?????
//
//  dp[1] = a[1] + if a[1] < 0:
//                      dp[0]
//                 else: // a[1] > 0
//                      do[2]
//
//
//  dp[i] = abs(a[i]) + if a[i]<0:
//                          dp[i-1]
//                      else:
//                          dp[i+1]
//  O(n^2) because -1 and +1 unless
//
//
//  dp[i+1] = abs(a[i+1]) + if a[i+1]<0:
//                              dp[i]
//                          else:
//                              dp[i+2]
//  even then it requires both sides to be fully computed by then <==> layer by
//  layer simulation basically
//
//  -10 -3 -17   1  19  20
//
//   10  3  17   1  19  20
//          +3 +19
//     +10 +10 +20 +20
//
//
//  abstract the groups into conseuctive +'s and -'s
//
//  do two linear runs (one start with + at the left-most
//                  and one start with - at the right-most)
//         and at each iteration, we get to keep one opposing group's sum at the
//         end
//
// === PRELIM'D SOLVED ===
//
//
// WA2:
//
//          you could still incorporate many (+) but it will have to be
//          left-side of the last selected element from (-)
//
//          ps on both (-) group and (+) group??
//
//          because more generally, we can do all negatives on the right and all
//          positives on the left, technically both works in either
//          chronological order
//
//          or all positives and all negatives, but never let them cross/change
//          more than once (i.e., twice or more)
//
//          ==> prefix sum on both (-) and (+) group
//          ~~~and simply test 2 combination at each pair of groups:
//          and find the max of the follow 3 value:
//              1. all (+) group
//              2. all (-) group
//              3. (+) left, (-) right for each crossings floor(groups / 2)
//

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n);
  IVLL(a, n); // no zero

  if (n == 1) {
    O(abs(a[0]));
    return;
  }

  // ASSUME: first group is (-), and every other group is (+)
  vll groups;
  if (a[0] > 0) { // ensure first group is (-)
    groups.PB(0);
  }
  groups.PB(0);
  II(i, n - 1) {
    if ((a[i] > 0) == (a[i + 1] > 0)) {
      groups.back() += a[i];
    } else {
      groups.back() += a[i];
      // groups.PB(a[i + 1]);
      groups.PB(0);
    }
  }
  groups.back() += a[n - 1];
  // if (((a[n - 2] > 0) == (a[n - 1] > 0))) {
  //   groups.back() += a[n - 1];
  // }
  if (a[n - 1] < 0) { // ensure last group is (+)
    groups.PB(0);
  }

  DBG_ITER(groups);

  ll max_coins = 0;

  vll ps_pos(groups.size() / 2 + 1, 0);
  vll ps_neg(groups.size() / 2 + 1, 0);

  for (ll i = 1; i < groups.size(); i += 2) {
    ps_pos[i / 2 + 1] = ps_pos[i / 2] + abs(groups[i]);
  }
  for (ll i = 0; i < groups.size(); i += 2) {
    ps_neg[i / 2 + 1] = ps_neg[i / 2] + abs(groups[i]);
  }

  max_coins = max(ps_neg.back(), ps_pos.back());

  II(i, groups.size() / 2 + 1) {
    max_coins = max(max_coins, ps_pos[i] + (ps_neg.back() - ps_neg[i]));
  }

  // ll running_pos = 0;
  // ll running_neg = 0;
  // II(i, groups.size() / 2) {
  //   running_pos += abs(groups[i * 2 + 1]);
  //   max_coins = max(max_coins, running_pos + ((i * 2 + 1 < groups.size() - 1)
  //                                                 ? abs(groups[i * 2 + 2])
  //                                                 : 0));
  // }
  // II(i, groups.size() / 2) {
  //   running_neg += abs(groups[groups.size() - 2 - i * 2]);
  //   max_coins = max(max_coins,
  //                   running_neg + ((groups.size() - 2 - i * 2 > 0)
  //                                      ? abs(groups[groups.size() - 3 - i *
  //                                      2]) : 0));
  // }

  O(max_coins);
  ;
}
