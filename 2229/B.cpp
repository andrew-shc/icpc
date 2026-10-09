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

// start: 1137
//   end: xx (next day)

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
// O.1:
//  let's say 2 largest DIFFERENT/SAME maxes (across both arrays) on a[1] and
//  b[1]
//      swapping them makes no change to the answer SINCE bi always takes it and
//      ai always takes it since they're both max
//
// IF the 2 largest DIFFERENT/SAME maxes (across both arrays) are on a[1] and
// b[2] (independent of each other in indices)
//      there are trades off to consider on how much sum of b will be brought
//      down just to slighty increase the max(a) when the maxes are replaced by
//      at most 3rd largest max
//
// i mean just prefix max?? and prefix sum??
//
// lets consider over n
//
// n=1: INVARIANT to swapping at the only ind i=0
// n=2:
//      1 9
//      4 5  (swapping 1<->4 does not thing to the max but decreases the sum and
//      hence the ans)
//           (swapping 9<->5 does nothing per O.1)
//
//      8 9
//      4 5
//          (swapping 8<->4 does increase the ans)
//          (swapping 9<->5 always decreases to depends on the swap before on
//          what degree it decreases)
//
//     feels like there's some cascading involved....
//
//     consider
//          8 7 6 5 3
//          1 1 1 1 1
//                      (8<->1 => +7,-1)   1 1 1 1 1
//                      (7<->1 => +6,-1)   8 7 6 5 3 = 1+29 = 30
//                      (6<->1 => +5,-1)
//                      (5<->1 => +4,-2)
//                      (3<->1 => +2,-1)
//
//              or      (7<->1 => +6,0)    8 1 1 1 1
//                      (6<->1 => +5,0)    1 7 6 5 3 = 8+22 = 30
//                      (5<->1 => +4,0)
//                      (3<->1 => +2,0)
// H.1: just put the max to a[] and swap all the indices where a[i]>b[i] (except
// for where a[i] is the max.)
//      COUNTER-EXAMPLE: 7 7 7 7 7 9
//                       7 7 7 7 7 1  => max(A)+sum(B)=9+5*7+1
//                           vs. 9<->1=> max(A)+sum(B)=7+5*7+9 (with -2 +8
//                           exchange)
//                       7 7 7 7 7 1
//                       7 7 7 7 7 9
//
//     CE.1              when the difference of two largest max of A are SMALLER
//                       than the index-difference of the LARGEST max,
//                          one should just swap the index at the largest max
//
//     H.1/1: is this the only CE?
//              cascade--an extension of CE.1?
//
//              what if the difference between 2nd and 3rd largest max of A are
//              smaller than the index-diff of the 2nd largest max (L-shaped
//              difference) => theoretically, we can just impl like this (sort
//              on A and swap largest element for each index to A)
//
//              1 7 8 9
//              1 1 1 1
//
//              or actually sort of brute force it? (DOESNT HAVE TO BE ELEGANT)
//
//                  compute the max for pair-wise across-index (pwai)
//                  compute the min for (pwai)
//                  sum the MAX of pwai
//                  sum the MIN of pwai
//
//                  for each a[i]:
//                      max over =MAX+pwai_min[i]  // since we always want the
//                          pair-wise max of across-index we always compute the
//                          sum of it and the selected max's completenary min
//
//              ==> DOES NOT HAVE TO BE ELEGANT <==
//                  ==> ACTUALLY, CAN BE ELEGANT: FIND THE MAX OF PWAI_MIN
//
// P.1: INDEX-INVARIANCE across A,B (feel free to sort index-by-index across
// both arrays)
//

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n);
  IVLL(a, n);
  IVLL(b, n);

  ll max_sum = 0;
  // vll pwai_min;
  ll max_of_pwai_min = 0;
  II(i, n) {
    max_sum += max(a[i], b[i]);
    max_of_pwai_min = max(max_of_pwai_min, min(a[i], b[i]));
    // pwai_min.push_back(min(a[i], b[i]));
  };
  O(max_sum + max_of_pwai_min);
}
