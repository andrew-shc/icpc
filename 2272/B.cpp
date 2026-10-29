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
  vpll a;                                                                      \
  for (ll i = 0; i < n; i++) {                                                 \
    ll ai, bi;                                                                 \
    std::cin >> ai >> bi;                                                      \
    a.push_back({ai, bi});                                                     \
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
// P.1: within a jump, if it is valid, we can make the frogs jump back to the
// original position
//      => we only need to check for one step of jump (one tick of simulation)
//
// P.2: each column contains at least one frog (1-2 frogs)
//      => 1-2 frogs
//      => after 1-jump, the same amount of frogs must remain for each column
//      => either 0-in, 0-out
//                1-in, 1-out
//                2-in, 2-out
//
//      fff -> f[ff]o
//      ofo    o[o ]f
//
// P.3: the total cardinality/directions the frogs jump must be 0
//      i.e.,
//              same amount of <- as ->
//              same amoutn of ^  as v
//
// O.1: if there are odd amount of frogs => P.3 never gets satisfied
//          => we need to ensure at least even amount of frogs
//
// H.2: is there a case where even # of frogs still fail?
//      consider islands
//
//      ofooooofooo 2
//      ooooooooooo 0
//      01000001000
//
//      H.2->O.2:
//          xxofoxx
//          xxoooxx
//
//          xxofffoxx
//          xxoooooxx
//
//          because, there are only 2 rows,
//          the only case these become invalid is if there are any islands of
//          {row 1, row 2}xODD#s
//
//          oofofofofofo
//          ofofofofofoo  (these are fine)
//
//      O.2/1: IF there's a column o
//                                 o
//             that column must ALWAYS be o
//                                        o
//             (HARD BOUNDARY, proper definition of an island)
//
//
// IMPL:
//
// per islands (delimited by [o o]T)
//  if even #s in each rows and columns => 0 (???)
//      foooof
//      offffo
//      ->
//      ofoofo
//      foffof
//
//      O.3:
//          even groups/islands are only made of such following blocks
//
//          f*o    o*f
//          o*f or f*o
//
//          ff    **    f
//          ** or ff or f
//
//          which individually always work
//
//          off
//          ffo
//
//          offf
//          fffo
//
//
//          offof
//          foffo
//
//          how to prove this??
//
//  if odd #s exist => 1 (by O.1)

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n);
  IS(row1);
  IS(row2);

  ll ones = 0;
  II(i, n) {
    if (row1[i] == 'o' && row2[i] == 'o') {
      // new island
      if (ones % 2 == 1) {
        O(1);
        return;
      }
      ones = 0;
    } else {
      ones += row1[i] == 'f' ? 1 : 0;
      ones += row2[i] == 'f' ? 1 : 0;
    }
  }

  if (ones % 2 == 1) {
    O(1);
    return;
  }

  O(0);
  ;
}
