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
// dp?
//
// b/c for each idnex i=2..n IN THAT ORDER
//
// DP-able?
//
// prefix sum?
// prefix sum!
//
// when apply the a-s or a+s operation
//              all the later elements of the prefix sum gets +s or -s
//
//              (reminder: -s is valid if s itself is negative)
//
// by the simple observation of prefix sum, one can see the need to maximize the
// prefix sum or really just the running sum if possible
//
//
// this is DP-able since if we can find an |s| > 0 => it will help with the
// rest?
//      however, noticed we use |s| not s, this means if the later values are
//      all negatives we want it to be more negative
//
//      ==> we want the numbers to be EXTREME (the more extreme the better)
//          since we do not care about negatives (since we can just do a-s)
//
//          HOWEVER, this is also a prefix sum.... where the extremes can CANCEL
//          OUT each other
//
//
//
// H.1: try/test two methods, all +s and all -s then at the end decide to use
// +/-s to maximize? (i.e., is changing +/-s in between sub-optimal)
//      .... considering how s is prefix sum in-statement--literally
//              and how summations tends to cancel out it might be wise to just
//              go all +/- until at the end
//
//              think of it like a undecisive person whether to go left or right
//              and at the EOD the person is still in the middle (not extreme)
//              since we sum up all the deltas
//
//              but another person who either always go left or right will be
//              maximally extreme?
//
//         consider n=3 (n>3 should be clearly visible then)
//
//         1 2 3
//
//         1 2 3
//          +1+4 = 7
//
//         1 2 3
//          -1-2 = 1
//
//         1 2 3
//          -1+2 = 5
//
//         1 2 3
//          +1-4 = -1 (!!!) but that's b/c its at the end
//
//
//         n=4 (then n>=4 should be ez)
//
//         1 2 3 4
//          +1+4.11 = 15 or -7
//
//         1 2 3 4
//          +1-4.3  = 7 or 1
//
//         1 2 3 4
//          -1+2.7  = 11 or -3
//
//         1 2 3 4
//          -1-2-3  = 1 or 7
//
//
//         if we do a[i] = a[i] - sign(a[i-1])*s
//              by opposing the sign of the previous element,
//              we effectively cancel out the most recent element's contribution
//              (guaranteed)
//
//              by keeping the sign of the previous element
//              we effectively incorporate the most recent element's
//              contribution (guaranteed)
//
//              IF the most recent element's contribution is the most extreme
//              THEN this ensures the eventual maximization
//
//              but ARE the most recent element's contribution the most extreme?
//              (remember, we have the previous sum of s to consider)
//
// reverse DP?
//
//  start with a[n]
//      look at sign(a[n-1]),
//          if the previous element is negative, negate the sum
//          if the previous element is positive, add the sum
//      go backwards until
//
//      look at sign(a[2-1])
//          if a[1] is negative, negate a[1]
//          if a[1] is positive, add a[1]
//          if 0, do 0 or whatever doesn't matter (later 0's after non-zeroes
//          will be non-zero by the operations)
//
//
// sounds reasonable look at test cases omg
//
//
//
// 3 -5 1 -4 2
//  +  - +  +
// 3 -2 3 -1 1<
//
// this is just summing the elements
// we have to make the current a[i] the maximum contribution (basically greedy)?
//
// 3 -5 1 -4 2
//  -  - -  -
// 3 -8 6 -10 12
//      -4
//
//
// another simpler observation
//
//
// if the elements are all positive, just do a+s all the way
// if the elements are all negative, just do a-s all the way (until the end)
//
// if some elements are negative but most are positive, just do a+s all the way?
//      some negatives will be re-absorbed?
//      but if some negatives are truely very large negatives just do a-s all
//      the way?
//
//
// because if we do a+s then a-s later the previous s will incorporate all of it
// but then a-s begines to go down and de-incorporate and might as well just do
// a-s from the beginning but -s FLIPs the sign especially when the s>a[i]
// where -s => +s => -s => +s
//
// if(|a[i]| > |s|) {
//    let a[i] decide the RESULTING sign
//    we just want a[i] to be even more extreme for later values beyond what s
//    can achieve (a[i] positive? +s, a[i] negative? -s)
// }
// if(|s| > |a[i]|) {
//    let s decide the RESULTING sign
//    s is positive? +, follow a[i]'s sign actually
//    s is negative? -, negate and follow a[i]'s sign
//    just follow a[i]'s sign??'
// }
//
//
//
//
//
//
// a1 a1+a2 a1+a2+a3 a1+a2+a3+a4
//
//
//
// a1 a2+a1 a3+a2+a1 a4+a3+a2+a1
// a1 a2-a1 a3+a2-a1 a4-a3-a2+a1
// nooo
//
// a1 a2+a1 a3+a2+a1+a1 a4+a3+a2+a1+a1+a2+a1+a1
//                      a4 a3 a2 a1 a1 a2 a1 a1
//                              a1 appears 3 times
//                              a2 appears 2 times
//                              a3 appears 1 times
//                              a4 appears 0 times (in the s)
//
//
// n<=50
// -50<=ai<=50
//
// 100x50 = 5000
//
// quadratic?
//
//
// a4 a3 a2 a1 a1 a2 a1 a1
//    -- -- -- -- -- -- --
//    -- ----- -- -- -- --
//    -- -------- ----- --
//    --------------------
//
//    dp_s[1] = max(a1,-a1)
//    dp_s[2] = max(a2+a1,a2+a1)+dp_s[1]
//
// grewedey all the wayy?

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n);
  IVLL(a, n);
  ll ans = a[0];
  ll running_sum = a[0];
  for (ll i = 1; i < n - 1; i++) {
    ll c1 = (a[i] + running_sum);
    ll c2 = (a[i] - running_sum);
    ll c3 = (a[i]);
    ll s1 = c1 == 0 ? 0 : c1 / abs(c1);
    ll s2 = c2 == 0 ? 0 : c2 / abs(c2);
    ll s3 = c3 == 0 ? 0 : c3 / abs(c3);
    vpll c = {{abs(c1), s1}, {abs(c2), s2}, {abs(c3), s3}};
    ST(c);

    // we still want the actual value BUT we want to find the most extreme value
    ans = max(ans, c[2].first * c[2].second);
    running_sum += c[2].first * c[2].second;
  }
  ans = max(ans, max(a[n - 1] - running_sum, a[n - 1] + running_sum));
  // ll running_sum = 0;
  // ll running_sum_neg = 0;
  // II(i, n) {
  //   ans = max(ans, a[i] + max(abs(running_sum), -abs(running_sum_neg)));
  //   running_sum += a[i] + abs(running_sum);
  //   running_sum_neg = a[i] - abs(running_sum_neg);
  // }
  // ans = max(ans, a[n - 1] + max(abs(running_sum), -abs(running_sum_neg)));
  O(ans);
  ;
}
