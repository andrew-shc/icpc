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

// start: 1657
//   end: xx

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
// O.1: check how many largest possible amount of elements in a[] are < in b[]
//      O.1/1: this can be done by counting number of elements that are L.T. by
//              smallest to largest for each in a[] and b[]
//      O.1/2: if there are G.T. for remaining elements => -1 (impossible)
//      O.1/3: IF they're all =='s => only sort, dont add anything anymore to
//              any elements
//      O.1/4: IF there are multiple <'s, THEN 2ND STAGE OPS. can be OPTIMIZED
//              (must be)
//          H.1<-O.1/4: are the number of operations even optimize-able?
//
//              suppose, 2 2 1
//                       1 2 3
//                       * ~ x
//                       x * ~
//
//                       1 2 2
//                       1 2 3
//              IMPL-WISE, going from b--sorted--
//              NOTICE: b is already sorted (IE, STRICTLY INCREASING BROTHER)
//
//              going back to H.1, consider this case then
//
//
//                      6 2 3 1
//                      4 4 4 5
//
//                      technically, we can just move 6 up to 5.
//
//                      but more improtantly, it doesn't matter if 2,3,1 goes to
//                      the 1st/2nd/3rd fourth because ??? ~~~
//
//                      yes it doesn't matter just find the SHORTEST distance
//
//                      moving 6 to up to 5 is x3 times, yet moving 2,3,1 each
//                      (in order) onec to the left is same
//
// O.2: when a pair of elements crosses path with another pair, the distance it
//      has to travel (i.e., 2nd stage ops) is minimized within the intersecting
//      range
//
//
//     +5 +3 +1 -1 -3 -5  = 9 should be 15...
//      6  5  4  3  2  1
//      1  2  3  4  5  6
//
// O.3: try to let the elements with the longest travel move first??? (there
// should be an easier way to count swappings)
//
// i swear this is bubble sort but counting number of times the value were
// sorted/compared
//
//
//
//      4 7 1 6 2 5 3 <<
//      1 2 3 4 5 6 7
//
//      1 4 7 6 2 5 3 (1) 2 swaps
//      1 2 4 7 6 5 3 (2) 3 swaps
//      1 2 3 4 7 6 5 (3) 4 swaps
//      1 2 3 4 5 7 6 (4) 0 swaps
//                    (5) 2 swaps
//                6 7 (6) 1 swaps
//                    (7) 0 swaps = 12 swaps (the testcase also says 12 doesnt
//                    provide a counter-example)
//
// too lazy to exhaustively find what's the best way and just go reverse and
// test...
//
// H.2: however you swap, it is always the same amount of operations => minimal
// by default
//      i mean intuitively since b is already in an increasing order and we're
//      going from the left most point and slowly sort it up, any swappings
//      would either help the larger elements closer to the right location and
//      if not, (e.g., a: 5 2 3 1 vs b: 1 2 3 5 where the 1 moves the 2 out of
//      the place) it is merely because fundamentally the 1 has to cross the 2
//      at some point and counter-intuitively would always make the 2 1-move
//      inefficient unless the 1 and 2 are already ordered (w.r.t just to 1 and
//      2)
//
//      ==> not definitely proven, but let's try this....
//
//
//
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//
//
//
// what happens if there are multiple elements that are < compared to array b?
// (more flexible?)
//      - mark then
//      - while we still want to find the smallest distance to swap from a low
//      index
//
// O.4: b is STRICTLY increasing => no duplicates
//
//
// theoretically speaking....
//
//      we can just... look at b
//      /1 if there's ONE element exactly that or less, have that element in a[]
//              traverse to the same location at b[]
//      /2 if there's >1 element => pick the closest one (omfg it cant be that
//      easy
//                                                      right)
//              the reason /2 works because we KNOW/ASSUME the next element must
//              be larger (which could mean more options at closer travel
//              distance OR same options as before but ~~no changes~~ INCREASES
//              1-unit of distance if this later element pick a closer element
//              when the earlier element picks a further element ACTUALLY
//              increases one unit of distance)  <-- distance as in operations
//              BECAUSE taking a farther elements forces the earlier elements
//              (if it was the remaining one for the next larger element in b[])
//              to be one step further than need to be
//
// KEY INSIGHT: USE THE MANY USEFUL PROPERTIES OF b[]
//
//
// IMPL:
//      FOR each elements bb in b
//          pick the closest available one <- compute distance // NO NEED TO BE
//                                                                EXTRA-FANCY
//                                                                QUADRATIC
//                                                                ALLOWED
//          erase element
//          ops += distance

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n);
  IVLL(a, n);
  IVLL(b, n);

  ll ops = 0;
  ll erased = 0;
  II(i, n) {
    II(j, a.size()) {
      if (a[j] <= b[i]) {
        ops += erased + j - i;
        a.erase(a.begin() + j);
        erased++;
        break;
      }
    }
  }

  if (a.size() > 0) { // that means there are some elements in a | a[j] > b[i]
                      // for some j, for all i
    O(-1);
    return;
  }

  // vll ind(n, 0);
  // iota(ind.begin(), ind.end(), 0);
  //
  // // DBG_ITER(ind);
  //
  // sort(ind.begin(), ind.end(), [&](int i, int j) { return a[i] < a[j]; });
  //
  // vll static_ind(ind);
  //
  // DBG_ITER(ind);
  //
  // ll ops = 0;
  // // ll correction = 0;
  // II(i, n) {
  //   if (a[static_ind[i]] > b[i]) {
  //     O(-1);
  //     return;
  //   } else {
  //     // i represents the elements we have traversed (subtracted) (subtract
  //     1)
  //     //      since less distance to cover
  //     // ind[i] represents where the value is in a and how much it needs to
  //     be
  //     //    traversed to the expected point i (added)
  //     // correction represents how many times the element has been MOVED DOWN
  //     //    (shifting other elements from i+1 to ind[i] further up/away)
  //     //      which adds 1
  //     // actually is there an easier way to do this....
  //     // honestly just do two loops as intended (n=2000)
  //
  //     ops += ind[i] - i; // distance
  //
  //     // correction
  //     if (ind[i] - i > 0) { // if they're not as the same location
  //       II(j, n) {
  //         if (i <= ind[j] && ind[j] < ind[i]) {
  //           ind[j]++;
  //         }
  //       }
  //     }
  //   }
  // }

  O(ops);

  ;
}
