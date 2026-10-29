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
// 2 2
// <->
//  2
//
// 3 3 3
// <--->
//   3
//
// 3 3
// <->
//
// if any ai >= n?
//  => NO
//
//
// 4 4 4?
// 3 3 3
// 4 3 3
// 3 2 2
// 3 4 2
// 2 3 1
// 2 3 4
// 1 2 3 <-- needs to skip the middle to reach the left-most on
//
//
//
//
//
//
//
// it's like an L-shape
//
//               |
//               |
//               |
//               |
// |             |
// |             |
// |             |
// ---------------
//
//  so it needs to cover something like twice the distance (i.e., roundtrip
//  distance)
//
//  roundtrip distance!
//      the distance to reach to a certain clock to reset and to come back
//
//  if clock's ai < roundtrip distance (to all other elements):
//      not possible to reset all clock
//  if clock's ai >= roundtrip distance (to all other elements):
//      // is the always true?
//      if every ai is long enough to have its roundtrip distance cover all
//      other position from the current clock's position, then this process can
//      continue forever
//
// double check later
//
//
// double checking:
// the idea is that every clock needs to be reachable to all
//      other clock
//
// and that the comparison between clocks time and roundtrip disance is
// invariant to any decision of resetting clocks in between the two clocks
// location
//
//
// IMPL:
//  for each a[i]:
//      ensure a[i]>(n-1)*2
//
//      4 4 4
//      3 3 3 --
//      3 4 3
//      2 3 2 --
//      2 3 4
//      1 2 3 --
//      1 4 3
//      0 3 2 --
//
//      more rigoursly
//
//      left-most element obvisouly need >(n-1)*2
//      middle element just needs >max(1@i-1, n-1@i)*2
//          if we assume we need to zigzag back and forth
//          or rather we must enable the ability to zigzag
//              (and zigzag is the fastest most optimal path to travel)
//          so technically 5 3 5 is fine
//                         4 2 4 --
//                         4 3 4
//                         3 2 3 --
//                         3 2 5
//                         2 1 4 --
//                         2 3 4
//                         1 2 3 --
//                         5 2 3
//                         5 1 2 --
//                         5 3 1
//                         4 2 5
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
  IVLL(a, n);

  // bool impossible = true;
  bool possible = true;
  II(i, n) {
    DBGLN(i, a[i], i, n - (i + 1), max(i, n - (i + 1)) * 2,
          a[i] > max(i, n - (i + 1)) * 2);
    if (a[i] > max(i, n - (i + 1)) * 2) {
      // impossible as it is
      DBGLN("IMPOSSIBLE!");
      // possible = false;
      // break;
    } else {
      // fine
      DBGLN("POSSIBLE");
      // impossible = false;
      possible = false;
      break;
    }
  }

  // if (impossible) {
  if (!possible) {
    OHNO;
  } else {
    OHYES;
  }

  ;
}
