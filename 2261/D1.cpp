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
// guarantee that no TWO DETECTOR's EXACT RANGE IS THE SAME
// BUT THATS AN INPUT RESTRICTION
// NOT OUTPUT OR PROBLEM RESTRICTION
//
// so what we can do is:
//
//
// 1
//
// 1 2
// x
//
// 1 2 3
// x x
// y
//
//
// 1 2 3 4
// x x x
// y y
// z
//
// 1 2 3 4 5
// x x x x
// y y y
// z z
// w
// or
// x x x y y
// z z   w
// a
// nooo
//
//
// IMPL:
//   1 to n
//
//   2 3
//     3 5
//       5 7
//         7 9
//           9
//
//   2 3
//     3
//
//   if(i<=1): none
//   if(i<=2): (1,1)
//   else: // n>=3
//      (2,3)
//      (i,i+2)
//      (n-2,n)
//      (n,n)
//
//      or just
//      (n-1,n) (if there's only 2 left)
//
//      if n%3 == 0:
//          a
//
//
//
//             ---
//         -----
//     -----
//   ---
// 1 2 3 4 5 6 7 8 9  (<8 possible?)
//   ---
//     -----
//         -----
//             -----
//                 - 5?   12345 detectors
//                        .....
//                        !....
//                        !!...
//                        .!...
//                        .!!..
//                        ..!..
//                        ..!!.
//                        ...!.
//                        ...!!
//                        ....!
//
//                        but we just can't do the binary b/c of the consecutive
//                        requirement (inefficient)
//
//                        !....
//                        !...!
//                        !..!.
//                        !..!!
//
//
//   ---
//     ---
//       ---
//         ---
//           ---
//             ---
//               --- 7?
//
//
// -------   -------  (only works w/o the consecutive requirement)
// ---       ---
// -   -     -   -
//
//
// ------- -------
//   ----- -----
//     --- ---
//       - -
//     (in-efficienct)
//
// ---------------
// -------------
// -----------
// ---------
// -------
// -----
// ---
// -
//
//
// ---------------
//
// 1 2 3 4
//   ---
//     --- !!!!
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
  I(n, m); // m always 0
  II(i, m) { I(l, r); }
  vpll add_detc;

  // II(i, n - 1) {
  //   add_detc.PB({i + 1, i + 1}); // ?????
  // }

  if (n == 1) {
    // none
  } else if (n == 2) {
    add_detc.PB({1, 1});
  } else {
    for (ll i = 1; i <= n; i += 2) {
      // if i+1 == n
      if (i == n) {
        add_detc.PB({n, n});
        break;
      }
      add_detc.PB({i == 1 ? 2 : i, i + 1 == n ? i + 1 : i + 2});
    }
  }

  O(add_detc.size());
  II(i, add_detc.size()) { O(add_detc[i].first, add_detc[i].second); };

  // isnt this just ceil(n/2)??
  // or floor(n/2)?
  //
  // 1
  //
  // 1 2
  // x
  // 1 2 3
  // x y
  //
  // ????????
}
