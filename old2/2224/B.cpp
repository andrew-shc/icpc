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

#define INC(i, n) for (ll i = 0; i < n; i++)

#define DEC(i, n) for (ll i = n; i >= 0; i--)

#define OUT_ITER(a)                                                            \
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
#define OUT(...) cout_vars(__VA_ARGS__)

#define READ_S(s)                                                              \
  string s;                                                                    \
  cin >> s;

#define READ_VLL(a, n)                                                         \
  vll a;                                                                       \
  for (ll i = 0; i < n; i++) {                                                 \
    ll ai;                                                                     \
    std::cin >> ai;                                                            \
    a.push_back(ai);                                                           \
  }

template <typename... Args> void read_vars(Args &...args) {
  (std::cin >> ... >> args);
}
#define READ(...)                                                              \
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

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// END MACROS
///////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

void solve(ll T);

int main() {
  /////////////////////////////////////////////////////////////////////
  //// comment out the sync when working with interactive problems ////
  /////////////////////////////////////////////////////////////////////
  ios_base::sync_with_stdio(false);
  /////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// START ACTUAL CODE
///////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

// start: 16:43
//   end: xxxxxxx

// mex for each i
// 1 3 5 7 9 0 2 4 6  8
// 0 0 0 0 0 2 4 6 8 10
// ^^^ ~~~~

// YOU CAN RE-ARRANGE ARBITRARILY TO MAXIMIZE SUM
// obviously, a1 should be the max and an should be the minimum (note:
// duplicates can exist)
//   if the minimum is not 0, ~~~ WAIT we want MEX to be the largest

// if the min>0, mex always 0 ==> max*n
// if the min=0, how much consecutive integer can it go? (DUPLICATE == WASTED
// SPACE FOR MAX / IF MAX > the largest consecutive n from 0)
//     assume m to be the amount of integers that can consecutively connect from
//     0 to m-1            ~~~~~~~consecutive the last consecutive n from 0 we
//     can go, we then want to optimize => max*(n-m) + m(m+1)/2 + m*(n-m)
//              place the max after the end of m???

// i think first we need to find the m (by sorting) and the max
//  m(m+1)/2 + m*(n-m) + max*(n-m) <== for optimizing mex (greedily)
//  max*n <== for optimizing max (greedily)

// k(k+1)/2 + k*(n-k) + max*(n-k) <== vary over 0<=k<=m lol to find the greatest
// (very unelegant soln.)
// for each k++ ==> -max, +k, +(n-k) == -max + n (visually, since the vertical k
// is same as the prefix distance)

// side notes, if there are duplicates, we immediate go to the next mex or just
// go to the max

// OR, another option is putting 1 MAX in the beginning if its worth it to swap
// it against losing an m ==> test +max*m - m === +(max-1)*m ==> hold up, unless
// (max-1)*m is negative, this is a freebie (i.e., place the max in the front
// then deal MEX)
//      ONLY WORKS
// what if the max is <=m???? what about the various length?
// there's a tradeoff w.r.t. length :(

// actually, we always want the best of both world, the most m (for optimal mex)
// and the most max (for optimal max)
// SO the question becomes WHERE SHOULD THE MAX BE?
//  IF max>m ==> ALWAYS MAX FIRST, then the remaining MEX
//  IF max=m ==> they're the same actually (can be visually seen also)
//  ^^ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// >>>> can we do this without sorting?? (prob not / side question)

// binary search over answer??
// linear search over answer??

// MAJOR INSIGHT: since max works like one way, we should linear search over
// where to put the max (which could include the m)

// post-soln. (don't be lazy on verifying certain hypothesis)
// it is always optimal to put the max in the first place

// re-deduction:
// max, whether it is the m or a higher max
// if we show putting the original m (if it were the max) in the first place is
// optimal, then any max would always be optimal
//      => assuming we have max at the last element of the m MEX numbers (mth
//      element), if we move the original m to the beginning (effectively
//      chopping the m MEX into m-1 MEX), then we gain +(m-1)*m (for max) and
//      only lose m (for MEX) (from the 1-shifted MEX numbers)

// no clue why the editorial is so confusing and not talking about it (other
// than making the implementation DIRECTLY easier but sometimes max is the mth
// MEX)

// 0 1 -> (0 + 1) + (1 + 2) -> 4
// 1 0 -> (1 + 0) + (1 + 1) -> 3

// when the editorial said the "first" position, it meant in 0-index, not
// 1-index (i.e., @1 not @0) (checked code)

void solve([[maybe_unused]] ll T) {
  READ(n); // >=1
  READ_VLL(a, n);

  if (n == 1) {
    OUT(a[0] + (a[0] == 0 ? 1 : 0));
    return;
  }

  // n>=2

  // if (a[0]) {
  // }
  //

  sort(a.begin(), a.end());

  // always put the largest in the beginning (DO NOT SHARE 0, even if 1 is the
  // max, it would be the same since if a[0] is set to 0, MEX will be 1 but max
  // will be 0 at that point)
  // well except when MEX continues after which can be 2...
  // 0-exception still needed
  // DOUBLE COUNTER-ARG
  //  MEX IS ORDER-LESS, 0 is included so IT WOULD BE AUTOMATICALLY GO UP TO 2
  //      FIX => MEX BEFORE THE ROTATION?????
  //      no elegant solution; just consider the edge case (better realized this
  //      time) when the first two element is 1,0 => m should at least be 2
  //              why is this a uniq edge case? 2+,0 => goes back to the
  //              standard 1 and 0,0 => (another edge case) goes back to 1 but
  //              MEX also includes 1 for the first 0 also (unlike before)

  //  swap(a[0], a[n - 1]);
  rotate(a.begin(), a.end() - 1,
         a.end()); // keeps the ordering correct for 1 to n-1 (0-index)

  // ll m = a[0] == 1 && a[1] == 0
  //            ? 2
  //            : 0; // EDGE CASE (when 1,0 uniquely lets MEX results in 2)

  DBG_ITER(a);

  ll m = 0;

  // happens via max (since there's only 1 max we can just gate it after ONCE)
  bool bridged = false; // m continues to go up with a gap
  bool overflowed = false;

  // m continues to go up with a gap (we treat the local duplicates
  // in the original as TRUE global duplicates) to not waste space

  // effect of bridged || overflowed ==> +1 ADDITIONAL increment on and after
  // (since the MAX is not exactly part of it) ==> max_sum +=
  // vertical_correction; YET horizontal_correction (-1) on m*(n-m-1) becoming
  // m*(n-m-2)

  ll vertical_corrections = 0;
  ll horizontal_corrections = 0;

  for (ll i = 1; i < n; i++) {
    // if (a[i] == m) {
    //   m++;
    // }

    // placed before overflow & bridged to satisfy another edge case of [1,0]
    if (a[i] == m) { // standard MEX increment
      m++;
    }

    if (!overflowed && !bridged) {
      if (a[i] == m && a[0] == m) {
        m++; // would a[0] instantly aid the MEX m?
        overflowed = true;
        vertical_corrections++;
        horizontal_corrections++;
        continue;
      } else if (a[i] != m && a[0] == m) {
        m++;
        bridged = true;
        vertical_corrections++;
        horizontal_corrections++;

        continue;
      }
    } else if (a[i] == m) {
      vertical_corrections++;
    }
  }

  ll max_sum = a[0] * n;

  // + (m * (m + 1)) / 2 +
  //                m * max(n - m - 1, 0LL); // EDGE CASE, m == 2 but n == 2 for
  //                the
  //                                         // special case of [1,0] and
  //                                         [1,0,...]
  //                                         // where it starts with 2

  // we only care about min of 0 for MEX (where min must be at the [1])
  // 1 goes to the MEX of 2 at [1] but the other 1 will be added from the
  // standard m

  // fixed by the more general vertical/horizontal(?) corrections
  /*   if (a[0] == 1 && a[1] == 0) {
      max_sum += 1;
    } else if (a[0] == 0 && a[1] == 0) { // count the earlier 0 at [0]
      max_sum += 1;
    } */

  // nope not fixed on the special case of [0,0]
  if (a[0] == 0 && a[1] == 0) { // count the earlier 0 at [0]
    max_sum += 1;
  }

  max_sum += (m * (m + 1)) / 2; // starting at [1] ends at [m+1]
  max_sum += m * (n - m - 1);   // -horizontal_corrections
  max_sum += vertical_corrections;

  DBGLN(m, n, n - m - 1, vertical_corrections, horizontal_corrections);

  // if (a[0] == 0) { // EDGE CASE (when MAX = MEX = 0)
  //   max_sum++;
  // }
  OUT(max_sum);
}

//   if (n == 1) {
//     OUT(a[0] + (a[0] == 0 ? 1 : 0));
//     return;
//   }
//
//   // un-elegant brute-force
//
//   // smallest to largest
//   sort(a.begin(), a.end()); // O(nlogn)
//
//   if (n > 2) {
//     swap(a[1], a[n - 1]);
//   }
//
//   // put the max to the first (EDGE CASE: except when max is 1 and 0 present)
//   /*   if (!(a[0] == 0 && a[n - 1] == 1)) {
//       rotate(a.begin(), a.end() - 1, a.end());
//     }
//    */
//   // ll mx = a[n - 1];
//   ll m = 0; // edge case vaguely resolved by editorial?? edge
//             // case: max=0 shares the first element of MEX
//             // (that's the only thing either will ever share)
//
//   for (ll i = 0; i < n; i++) {
//     if (a[i] == m) {
//       m++;
//     }
//   }
//
//   if (m == 0) {
//     a[0] = a[1];
//   }
//
//   DBG("!!!! ");
//   DBG_ITER(a);
//
//   DBGLN(a[0], a[1], n, m, (m * (m + 1)) / 2);
//
//   ll largest_sum = a[0] + a[1] * (n - 1) + ((m * (m + 1)) / 2) + m * (n - m);
//
//   // 0 in the beginning might be included hence no more -1
//   // ~~~~ -1 for the included max inserted @1 (EDGE CASE, when 0
//   // is shared the MEX sort of just 1 shifts BACK)
//
//   // if (a[0] == 0 && a[n - 1] == 1) {
//   //   largest_sum += n - 1;
//   // }
//   OUT(largest_sum);
//
//   /*   ll largest_sum = mx * n;
//     ll running_sum_reversed = mx * n; // as if max is in the front always and
//     the
//                                       // MEX optimization is shifted to the
//                                       end
//                                       // ==> needs careful balance still
//     ll running_sum =
//         largest_sum; // initially greedy on max-op, but slowly to greedy
//         overall
//                      // with the inclusion of greedy on m
//     INC(k, m) {
//       running_sum = running_sum - mx + n;
//       // largest_sum_reversed;
//       largest_sum = max(largest_sum, running_sum);
//     }
//
//     largest_sum = max(largest_sum, largest_sum + (mx - 1) * m); // if we
//     OUT(largest_sum);
//    */
//   // ll mx = a[0];
//   // ll mn = a[0];
//   // // ll mex = a[0] == 0 ? 1 : 0;
//   // // ll sum = mx + mex;
//   //
//   // for (ll i = 1; i < n; i++) {
//   //   mx = max(mx, a[i]);
//   //   mn = min(mn, a[i]);
//   //   /*     if (a[i] == mex) {
//   //         mex++;
//   //       }
//   //       sum += mx + mex; */
//   // }
//   //
//   // ll sum = mx * n + mn;
// }
