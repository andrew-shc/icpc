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
// initially, if a scarecrow at y is within (x-k, x]
//      the crow moves to y+k
//
// best-case scenario, a cascade of teleportation
// where the current and every following scarecrow at y is within EACH
// subsequent (x-k,x] resulting in an instant telporation to after l
//
//  if no scarecrow is inside (x-k,x],
//      find the nearest scarecrow on either side of (x-k,x] (with preference on
//      the right-side)
//
// x.5 happens when two scarecrows moves in opposing direction s.t. the halfway
// point where the crow teleports will sometime be at x.5
//
// optimal placement of scarecrows
//  0, k, 2k, 3k, ..., l
//
//
//
// think those moving island jumper game thingy
//      (except you cant jump over gaps)
//
//
// note: convert everything in 2x space (makes all numbers even)
//
//
//
// ~~~ O.1: overlapping (x-k,x]
//
// crow POV: (x-k,x]
// scarecrow POV: for y-th scarecrow's position y
//      has a forward teleportation zone of [y,y+k)
//
//
// O.1: overlapping [y,y+k) is sub-optimal
//      optimal dense config is 0,k,2k,3k (up to x-offset/translation)
//
//
//~~~~~~~~~~~~~
// O.2: if [y,y+k) are all sparsely (not overlapping) between x<->l
//      => MIN TIME = smallest y <-> x + later gaps
// O.3: if [y,y+k) are all sparsely (not overlapping) between 0<->x-k before l
//      => MIN TIME = largest y+k <-> l
//~~~~~~~~~~~~~ REMEMBER, ALWAYS x=0 AT THE BEGINNING
//
//
//
// ~~O.2: if [y,y+k) are not overlapping between 0<->
//   ~~   => MIN TIME = smallest y + later gaps between forward teleportion jump
//     ~~                            zones
//       ~                          (cannot be reduced / invariant by the
//        ~                         observation of non-overlap)
//         ~                        HOWEVER, we can reduce the time needed when
//          ~                       the next teleportation jump zone goes
//          ~towards
//           ~                      it
//
// O.2: if x is at the ends of the first scarecrow and before the next scarecrow
// that is (optimally) coming towards it, we halve the distance to get the time
// (hence, X.5 halves appear)
//      but doesn't this suggest quarters also???
//
// simulate???
//
//
// Hint 1:
//  it is un-optimal to ever change the order of scarecrows
//  (similiar to the observation of non-overlap)
//
// Hint 2:
//  obviously, the left-most scarecrow must have its [y.. endpoint touch the
//  0-pos (x=0)
//
// Hint 3:
//  only way to save time is by... reducing any overlaps???
//  OR ACTUALLY
//      after the first scarecrow,
//      all the right-most touched scarecrow (where crow has encountered it)
//      should continuously move to the right while all the left-most untouched
//      scarecrow should be converging or going left???
//
//      NOTE, since we can half, we should half on the LARGEST gap
//
//      so we should actually create the largest gap possible before the crow
//      touches on ends of the scarecrow which then we must have both ends of
//      (groups) of scarecrows to cut the distance in half
//
//      the distance between the END of the last scarecrow and l cannot be
//      halved
//
// Hint 5:
//     Greedy! (does seem greedy)
//
//
// MAJOR OBSERVATION:
//      - larger value halved is better than many smaller values halved???
//
//      because we are always halving for any distances between scarecrows...
//          by the linearity, we can just sum all the distances (GAPS) between
//          the scarecrows and halve them?
//
//          since it is optimal to halve them, we let the last scarecrow try to
//          reach l-k if possible
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
  I(n, k, l);
  IV(a, n);

  vector<ld> b(n + 1, 0);
  b[n] = (ld)l;

  // auto p = [&](ll ind) { return ind > 0 ? b[ind - 1] : 0; };
  auto p = [&](ll ind) { return ind >= 0 ? b[ind] : 0; };
  // ld t = 0;
  ld t = a[0]; // after 1st step is done
  // II(i, n) {
  for (ll i = 1; i < n; i++) {
    b[i] = min((ld)l,
               min((ld)a[i] + t,
                   max(p(i - 1) + k, (a[i] - t + p(i - 1) + (ld)k) / 2.0L)));

    // time between the two recently placed scarecrows minus k (or overlapping)
    t += max(0.0L, b[i] - p(i - 1) - k);
  }

  ld d = 0;
  // II(i, n + 1)
  for (ll i = 1; i <= n; i++) {
    d += min((ld)k, b[i] - p(i - 1));
  }

  // DBGLN((ld)a[0], (ld)l, d, (ld)a[0] + (ld)l - d);

  ll min_time_twice = (ll)round(2 * ((ld)a[0] + (ld)l - d));

  O(min_time_twice);
  ;
}
