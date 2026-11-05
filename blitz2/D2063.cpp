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
// since the height is fixed we know
//
// A = (|a1-a2|*2)/2
//     or
//     (|b1-b2|*2)/2
//
// this is similiar to intervals
//
// we want to maximize overlaps
//
// notice, this is effectively the same as nested (choosing the extremes of two
// points)
//
//
// we know 1<=n,m
//
// if n == 1 && m == 1:
//      O(0)
// else:
//      f(1) => max(max |a1-a2| in a, max |b1-b2| in b)
//
// but we also have the cases where
//  -100 100
//  1 2 3 4
//
//  is it greedy on longest interval?
//
//
//
// !!!!!!!!!!!!!!!
//
// for simplicity sake we can actually separate the score value (by the
// observation that we prefer the longer/outer subarray first) before the
// shorter/inner subarrray FROM the valid operations scheme (notably the
// annoying 2 points taken on one and 1 points taken on the other)
//
// like FUNDAMENTALLY can be separated on a high-level (in that sense)
//
//
// now, consider the function g(k_a,k_b) -> score
//      NOTICE, we make the problems easier by first fixing on some input in
//      this case the # of operations on the 1st row and the 2nd row separately
//
//
//
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
  I(n, m);
  IV(a, n);
  IV(b, m);

  ST(a);
  ST(b);

  vll int_a(n / 2 + 1, 0);
  vll int_b(m / 2 + 1, 0);

  II(ka, n / 2) { int_a[ka + 1] = a[n - ka - 1] - a[ka] + int_a[ka]; }
  II(kb, m / 2) { int_b[kb + 1] = b[m - kb - 1] - b[kb] + int_b[kb]; }

  // f(k) := max_{ka+kb=k} g(ka,kb)
  // BETTER FORMULATION (we have 2 variables and 1 equation => 1 DoF / 1D /
  // line)
  //
  // f(k) := max_{x} g(x,k-x)   s.t. x+k-x = k
  //
  // linearly over k (or rather sum of them)
  //      and for each k (fixed), we vary >>>x<<<
  //
  //
  // 0 <= ka
  // 0 <= kb
  //
  //
  //
  // 2ka+kb <= n
  // 2kb+ka <= m
  // 0 <= ka
  // 0 <= kb
  //
  // ka=x, kb=k-x
  //
  // 2x+k-x <= n => x+k <= n => x <= n-k
  // 2(k-x)+x <= m => 2k-x <= m => -x <= m-2k => 2k-m <= x
  // 0 <= x
  // 0 <= k-x => x <= k
  //
  // max(0,2k-m) <= x <= min(k,n-k)
  //
  // remember, x => g(x,k-x)
  //               ka     kb
  //
  // notice, both ka and kb are strictly decreasing sequence (ALSO by the input
  // assumption of DISTINCT/UNIQUE points)
  //
  // well, if we look at the definition, ka is strictly increasing while kb is
  // strictly decreasing... (because ka++ and kb--)
  //        wtf does this tells us
  //
  // ACTUALLY, the RATE of increment/decrement is actualy decreasing/increasing
  //      => convex
  //
  //    remember, we greedily take shorter and shorter intervals but we still
  //    keep the previously selected intervals (if we're going to pick more)
  //    => always increasing, but the RATE of increasing is decreasing => convex
  //
  //    key observation: while previously one can imagine the rate can go up and
  //    down, but by the greedy observation on which intervals to take, the rate
  //    of additional increment on later intervals will always be smaller =>
  //    convex
  //
  //
  // ka:=x
  //      convex: increasing at a decreasing rate (negative 2nd derivative)
  // kb:=k-x
  //      convex: decreasing at a decreasing rate (negative 2nd derivative)
  //
  //      because summing both the same function with negative 2nd derivative:
  //              => convex
  //
  //      while it won't be like a Normal function where it increases
  //      exponentially before turning around and some weird 2nd derivative
  //      thingy
  //
  //      this function of linear combination of ka,kb is like a consistently
  //      round function where sure it MIGHT be increasing in the beginning but
  //      the rate of change is always decreasing (no sign change in 2nd
  //      derivative)
  //
  //      so not a hard, distinctive peak like a Normal function but a rounded
  //      one
  //
  //      but still a single UNIMODAL function where we're ALSO trying to find
  //      the MAX of the UNIMODAL => ternary search
  //
  //
  //~~~~
  // SO,  ka:=x
  //      convex: increasing at a decreasing rate
  //      kb:=k-x
  //      convex: decreasing at an increasing rate
  //
  //      combine them linearly:
  //              at first, increasing at more of a decreasing rate
  //                            (by the )
  //~~~~
  //
  // ~~~~~~~~~~~
  // suppose ka=k-kb
  //
  // 2k-2kb+kb <= n => k <= (n+kb)/2
  // 2kb+k-kb <= m => k <= m-kb
  //
  // 0 <= k?????
  // ~~~~~~~~~~~
  //
  //
  //

  // int_a[0] => 0 (makes sense, aligns with the 1@ of the prefix)
  auto g = [&](ll ka, ll kb) { return int_a[ka] + int_b[kb]; };

  vll scores;

  ll k = 0;
  // max(0,2k-m) <= x <= min(k,n-k)
  while (max(0LL, 2 * k - m) <= min(k, n - k)) {
    auto f = [&](ll x) { return g(x, k - x); };

    // ternary search on x
    ll L = max(0LL, 2 * k - m);
    ll R = min(k, n - k);
    // ll m1 = L + (R - L) / 3;
    // ll m2 = R - (R - L) / 3;
    ll M;
    while (L != R) {
      ll m1 = L + (R - L) / 3;
      ll m2 = R - (R - L) / 3;

      // if (m1 == m2) {
      //   // can this always be reliably reached?
      //   // suppose 1,2,3
      //   //         L   R
      //   //        m1   m2
      //   //
      //   // stuck here?
      //   //
      //   // regardless, either it becomes
      //   //           L R
      //   //   OR,   L R
      //   //
      //   // and with another iteration
      //   //
      //   //           L
      //   //           R
      //   //  or         R
      //   //             L
      //   //  or     L
      //   //         R
      //   //
      //   //  at this point the max would be the last M before R<L
      //
      //        or better, break on L==R
      //
      //   M = m1;
      //   break;
      // }
      // else {
      //         break;
      //       }

      if (f(m1) < f(m2)) {
        L = m1 + 1;
      } else {
        // f(m1)>=f(m2)

        R = m2 - 1;
      }

      // else {
      //         // f(m1) == f(m2)
      //
      //         L = m1 + 1;
      //         R = m2 - 1;
      //       }
    }

    // reaches here whenever L==R (where the max is at L,R)
    // for (ll x = max(0LL, 2 * k - m); x <= min(k, n - k); x++) {
    // }

    scores.PB(f(L));

    k++;
  }

  // the 0 is always included for completeness but the question is not asking
  // for it
  scores.erase(scores.begin(), scores.begin() + 1);

  O(scores.size()); // up to <=k_max
  if (scores.size() > 0) {
    OIT(scores);
  };
}
