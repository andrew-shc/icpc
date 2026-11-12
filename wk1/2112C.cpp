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
// P.1: WIN only when sum of red elements are STRICTLY GREATER than blue
//      elements
// P.2: Optimally,
//          x+y+z > any single elements excluding {x,y,z}
//          a+b > c for any (a,b)-pairs in {x,y,z} and c-element for the
//                  excluded
//
//          => number of ways to select {x,y,z} from a[] s.t.
//             x+y+z-c > x
//
//             for any elements x in a[] with a correction factor c from x IF x
//             is selected from within {x,y,z}
//
//          => going back (for impl. sake),
//             ensure x+y+z > c for any elements c in a[] excluding {x,y,z}
//             AND    x+y > z
//                    x+z > y
//                    y+z > x
//
//
// assume we sort them (it is sorted per input description / not part of the
// main description)
//
//      by the x+y+z > c,
//          we are bounded by ensuring the sun > max(a)
//          IF x,y,z excludes max(a)
//              (consider cases of multiple maxes)
//
//      we also have to ensure x+y+z > 2*max{x,y,z}
//          (for all cases)
//
//      ==> x+y+z > max(max(a),2*max(x,y,z))
//          (still cubic or worse)
//
//      max(max(a),2*max(x,y,z)) < x+y+z
//
//      suppose x<=y<=z,
//
//~~      x+y+z > max()
//
//
// DP on individual possible sums of x,y,z????
//
//
// RECALL, find the arrangements of {x,y,z} s.t.  REGARDLESS of all possible
// Bob's actions {x,y,z} satisfies the above constraints and count how many such
// arrangements satisfies
//    x+y+z > max(max(a), 2*max(x,y,z))
//
//    suppose x<=y<=z,
//      x+y+z > max(max(a),2*z)
//      ==>
//          x+y+z > max(a)   AND
//          x+y+z > 2*z => x+y>z
//
//      hence,
//          x+y+z > max(a)
//          x+y   > z
//
//      =>
//~~          x+y+x+y+z   > z + max(a)
//  ~~        2x+2y > max(a)    ????
//    ~~      2(x+y) > max(a)
//
//                  why can we remove z? does it even make sense? logical
//                  fallicy?
//
//                  counter-examples?
//
//                  1 2 3 (clearly invalid but valid according to the most
//                  recent statement)
//
//                  we can't do that because obviously logically it makes sense
//                  to bound to a max(max(a),2*z) which is clearly not linear
//                  (like a ReLU clamp w.r.t. each of the parameter) hence it
//                  does NOT makes sense to ADD these linear eqs together
//
// prefix count on x+y???
//
// if we sum, we should think in sum...
//
// quadratic??
//
//!!!!      +50: editorial has the solution saying O(n^2*logn) or just O(n^2)
//!!!       quadratic fine with cases <1x10^4 (e.g., 5000) given 2.5s
//!!        (per editorial, windowing also works here for a fast O(n^2))
//
// a better formula would be
//  x+y+z > max(max(a),2*z)
//      => x+y > max(max(a)-z, z)   (for all x,y; vary over z)
//
//      we can pre-compute x+y
//      where
//          pc[x+y]=(pair_counts, lower_bound_z)
//
// pc[x+y] will take quadratic construction and quadratic access
//
// no point in pre-computing => just iterate for each x,y
//
//  since we want to maximize the valid, this is where the logn portion comes
//  with binary search on z?
//      since a is sorted, if i++ => x+y>z => z+y>z++ (monotonic)
//                          BUT -z is the reverse direction (the other bound??)
//
//      2 bounds???
//
//      ~~~does editorial have easier way?
//
//
//
//
//!!! per editorial, we can find a much faster (and simpler way) by iterating
//! over y,z and binary searching on the x
//
// same observation with x+y+z > max(max(a),2*z)
//
//      (without using the translation invariance of max)
//
//      but we just do
//          x > max(max(a),2*z) -y-z
//
//      without trying to intuitively understanding it,
//      logically, we just find the smallest x where this statement is valid
//          (=> the next larger x will hence must work and we can just find the
//          difference in index-range)
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
  IV(a, n);

  // ST(a);

  ll ways = 0;
  for (ll i = 1; i < n - 1; i++) {
    for (ll j = i + 1; j < n; j++) {
      ll y = a[i];
      ll z = a[j];

      ll L = 0;
      ll R = i - 1;
      ll x_LB = -1;
      while (L <= R) {
        ll M = L + (R - L) / 2;
        ll x = a[M];

        if (x > max(a[n - 1], 2 * z) - y - z) {
          // good ==> find the lower bound of the @i=x

          x_LB = M;
          R = M - 1;
        } else {
          // bad

          L = M + 1;
        }
      }

      if (x_LB != -1) {
        ways += i - x_LB;
      }
    }
  }

  // for (ll i = 0; i < n - 2; i++) {
  //   for (ll j = i + 1; j < n - 1; j++) {
  //     ll x = a[i];
  //     ll y = a[j];
  //
  //     // x+y>z (R-BOUND)
  //     // max(a)-z < x+y (L-BOUND)
  //     //
  //     // sometimes it becomes R-BOUND to L-BOUND ???
  //     //
  //     //
  //     // why would z_RB < z_LB????
  //
  //     ll L = j + 1;
  //     ll R = n - 1;
  //     ll z_RB = -1;
  //     ll z_LB = -1;
  //
  //     while (L <= R) {
  //       ll M = L + (R - L) / 2;
  //       ll z = a[M];
  //       if (x + y > z) {
  //         // good
  //         z_RB = M;
  //
  //         L = M + 1;
  //       } else {
  //         // bad
  //
  //         R = M - 1;
  //       }
  //     }
  //
  //     L = j + 1;
  //     R = n - 1;
  //     while (L <= R) {
  //       ll M = L + (R - L) / 2;
  //       ll z = a[M];
  //       if (a[n - 1] - z < x + y) {
  //         // good
  //
  //         z_LB = M;
  //         R = M - 1;
  //       } else {
  //         // bad
  //
  //         L = M + 1;
  //       }
  //     }
  //
  //     // note -1s can exist (esp if 1 element left)
  //
  //     DBGLN(x, y, z_LB, z_RB);
  //     // if (L != -1 && R != -1) {
  //     if (z_RB != -1 && z_LB != -1) {
  //       // ways += R - L + 1;
  //       ways += z_RB - z_LB + 1;
  //     }
  //   }
  // }

  O(ways);

  ;
}
