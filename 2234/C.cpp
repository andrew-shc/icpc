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

// start: 1020
//   end: 1343

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
// something flood fill
// be careful with multiple peaks
// quadratic solution is fine???
//
// trees??? (nononono) <-- probably for F.
//
// prefix and suffix max? w.r.t. [i]
//  => if a single peak, taking a min of both at each index works
//  => if multple peaks, same thing (think of it like common shadows)
// O(2n) for each n for a O(2n^2)??
//
//
// pair-wise max(wi,next wi) > hi
//          => pair-wise min(hi, next hi) >= wi
//              BUT optimize (ie, wi=min(hi, next hi))
//
//      HOW does this work in the context of FLOOD-FILL
//
//          A.1: pair-wise MIN between (one-side ->) adjacent h_i's
//                  ==> independently MIN between both-sided adjecent h_i's
//             O.1/1: this ONLY works at the valley of the index 0@i since we
//                      want to maximize wi's
//
//          IMPL: this is just like before but like
//                  max(max of previous index, min(hi previous, current hi))
//                      ==> which accounts maximization when both minimum dips
//                          after the first peak while staying true to A.1
//
//              CORRECTION:
//                  wrong A.1. if min(wi, next wi) > next hi exists it would
//                  work but this one sided cycle... ONE-SIDED (weird ass
//                  problem description)
//
//                  ~~when doing prefix/suffix max of pair-wise min
//
//          ==> POST-CORRECTION:
//                  this strongly implies in the case of 1 2 3 4 5 6 100 1
//                                                                    ^
//                                                                 this can hold
//                                                                 6 perfectly
//                                                                 fine
//                                                    since its only checking
//                                                    avoid max(w_i,w_{i+1})>hi
//                                                    => want
//                                                    min(h_{i-1},h_i)>=wi
//                                                    <--
//                                                    correct interpretation
//                                                    (should be??)
//                                           more clear interpretation...
//                                           avoid current's water level
//                                           overflowing itself and the
//                                           next's water level from BACKflowing
//                                           to the current's height
//                                           => we want the current water
//                                           level to stay within the current
//                                           max height to prevent overflow of
//                                           itself and the BACKflowing from
//                                           current's water level to previous's
//                                           vessel
//
//                                           or like just like visualize the
//                                           case of 4 6 itself
//                                                       * *
//                                           consider [1 7 1], we just don't
//                                           need the current to overflow itself
//                                           or the next water level to BACKflow
//                                           into current vessel (notice, we do
//                                           not care if the current water level
//                                           overflows to the next OR the
//                                           previous but only for itself) and
//                                           also importantly constrained to the
//                                           current's height
//
//                                           which implies we only care about
//                                           the water level of the current to
//                                           not overflow itself (at its height)
//                                           or itself BACKflow to the previous
//                                           vessel constrained to the HEIGHT OF
//                                           THE DESTINATION of the flow
//                                           which in this case is the previous
//                                           element so technically speaking we
//                                           can do we can let the water level
//                                           of the next to not BACKflow
//                                           constrained by the height of the
//                                           destination which is the current
//                                           BUT this requires consideration of
//                                           TWO water levels which makes it
//                                           un-elegant (?) and unnecessarily
//                                           messy which goes back to the
//                                           original idea that this is all
//                                           about alignment for easier min/max
//                                           comparison which further validates
//                                           what the suffix max is doing
//                                           actually and we might only just
//                                           need the suffix max.
//
//                                                 ^^^^ O.2 ^^^^
//
//                                              ok we still need prefix but it
//                                              needs to be aligned
//
//                                           ~~min(h_{i})~~
//
//
//
//
//                  suffix only???
//
// after debugging (no soln. checking) => the whole vessel visualization the
// problem tried to gave is confusing af (no point in describing it in the first
// place)
//
//
// ~~~ REDO ~~~~
//
//
// O.1: conditioning 0 say on @i requires, optimally, the w @(i+1) to be h_i
// O.2: when w_i encounters h_i>=w_i ==> optimally raise the water table on
//          w_{i+1} to h_i
// O.3: conditioning 0 @i requires, optimally, the w @(i-1) to be h_{i-1}
//          in-relation to O.1, notice
//                      -1   i   1
//                      -1   0   i   <- w taking value of h
//                       ^       ^
//                same ind.     the prev. ind.
// O.4: when w_i encounters h_i>=w_i ==> can ALSO optimally LOWER the water
//          table w_{i+1} to what the @(i-1) requires
// O.5: the moments where h_i>=w_i can be thought of as a threshold to change
//          (e.g., catalase)
// O.6: to meet the @(i-1) "END" requirement, there must be one more
//          at-or-higher peak to lower it to the END requirement
//
//
// IMPL:
//      if no peaks:
//          min(START requirement, END requirement)
//      if 1 peak:
//          START requirement -> END requirement (where )
// ~~~~
//
//
//
// we still need prefix max/min (with the same across-index-min), but instead of
// pairwise-min
//      we greedily set @(i+1) the value of h_i
//      and @(i+2) <-- h_{i+1} when h_{i+1} >= current prefix max
//

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n);
  IVLL(h, n);

  vll l;
  II(i, n) {
    // prefix max (LEFT of i)
    vll pmx(n, 0);
    vll smx(n, 0);

    // there's a case where either direction hits the one and only highest peak
    // and raises to that level (which actually should be fine)
    for (ll j = i, jj = 0; jj < n; jj++, j = (j - 1 + n) % n) {
      // DBGLN("=", j);
      //~~ j-1 for the min relationship but the j+1 remains because that's the
      //~~ prefix/suffix logic
      //~~      pmx[j] = max(pmx[(j + 1) % n], min(h[(j - 1 + n) % n], h[j]));

      if (j == i) {
        pmx[(j - 1 + n) % n] = h[(j - 1 + n) % n]; // by greedy
      } else {
        // same thing for prefix from suffix
        // pmx[(j - 1 + n) % n] = max(pmx[j], max(h[(j - 1 + n) % n], h[j]));
        // because of the L-shaped test, for prefix we just need to check the
        // max against the current possible height, since the +1 index after
        // peak should just follow whatever the next one is (since the current
        // index meets the threshold to allow the decrease of the water level
        // which is greedily set the next value nchecked on earlier prefix)
        pmx[(j - 1 + n) % n] = max(pmx[j], h[(j - 1 + n) % n]);
      }
    }
    // suffix max (RIGHT of i)
    for (ll j = i, jj = 0; jj < n; jj++, j = (j + 1) % n) {
      // DBGLN(">", j);
      // ~~~      smx[j] = max(smx[(j - 1 + n) % n], min(h[(j - 1 + n) % n],
      // ~~~ h[j]));

      // ~~~ h[i+1] will be skipped unless three-way max is added
      // actually we only care about hte prev hieght h[j] to ensure it meets the
      // requirement
      if (j == i) {
        smx[(j + 1) % n] = h[j]; // by greedy
      } else {
        // smx[(j + 1) % n] = max(smx[j], max(h[(j + 1) % n], h[j]));
        smx[(j + 1) % n] = max(smx[j], h[j]);
      }
    }
    DBGLN(i);
    DBG_ITER(pmx);
    DBG_ITER(smx);

    DBLOCK {
      vll w;
      II(j, n) {
        w.PB(min(pmx[j], smx[j]));
        if (i == j) {
          w.back() = 0;
        }
      }
      DBG_ITER(w);
      DBG_ITER(h);
    }

    // sum
    ll sum = 0;
    II(j, n) {
      if (j != i) { // j==i, always 0
        sum += min(pmx[j], smx[j]);
        // sum += smx[j];
      }
    }
    l.PB(sum);
  }
  OIT(l);
  ;
}
