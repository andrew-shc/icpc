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
// P.1: all elements in a cannot be the same
//
//
// clearly by the observation of testcases this would be the best
//
//
// 0 1 2 0 1 2 0 1 2 0 1 2
// 0>1<2
//   1>2<0
//     2>0<1
//       0>1<2
//          etc...
//
// CLEARLY, if we only have adjacent-mutual friends,
//  we must have a_i be something within {0,1,2} (or else it is impossible)
//
// 0 1 2 0 1
// 0-1-2
//   1-2-0
//     2-0-1
//       0-1-0
//         1-0-1
//           0-1-2
//
// 0 1 2 0
// 0-1-2
//   1-2-0
//     2-0-0 (wrong)
//
// 0 1 2 1
// 0-1-2
//   1-2-1   (wrong)
//     2-1-0
//       1-0-1
//         0-1-2
//
//
//
// we can do
//
//  0 1 0 1 0 1 0 1
//
//  but what about odd-length?
//
//  0 1 0 0 1 0 1    ??
//      add the odd-th 2 in!
//
//  0 1 2 0 1 0 1
//  0 1 0 2 1 0 1
//  0 2 1 0 1 0 1
//
//
//
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~P.2: given 3<=n and NO x,y ==>
// ~~     A CONSTRUCTION OF 0,1,2 (%3==0) with [0 1] or [1]
// ~~     FOR THE REMAINING 1 or 2 (of %3==0) ALWAYS HOLD
//
// P.3: RELAXING (NO x,y)
//      IF x,y are adjacent ==> NO CHANGE
//      IF a_y IN adjc(a_x) && a_x IN adjc(a_y):
//          ==> NO CHANGE (MEX does not change, duplicate integers)
//
//      ~~a_y NOT IN adjc(a_x) <=> a_x==a_y
//      ~~a_x NOT IN adjc(a_y) <=> a_y==a_x
//
//      ~~==>
//
//      ~~a_y NOT IN adjc(a_x) <==> a_x NOT IN adjc(a_y)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//
// CONSTRUCTION
//
//      EVEN LENGTH:
//          0 1 0 1 0 1 0 1 0 1 ...
//
//      ODD LENGTH:
//          0 1 0 1 2 0 1 0 1 0 1 ... (insert the odd-th 2 somewhere)
//
//      IF x,y ADJACENT ==> NO CHANGE
//
//
//      let's just check if it's possibel to make a duplicate integer for x,y so
//      we don't have to check for other cases...
//
//      IF EVEN LENGTH && (y-x)%2==0
//          ==> POSSIBLE ==> NO CHANGE
//      IF EVEN LENGTH && (y-x)%2==1
//          ==> !!!
//      IF ODD LENGTH && (y-x)%2==1:
//          ==> POSSIBLE (insert 2 between x,y) ==> NO CHANGE
//      IF ODD LENGTH && (y-x)%2==0:
//          ==> ensure the insert of the 2 is inserted outside of the x,y
//
//
//  010101010101
//   *    *
//
//
//  012012010101 ~~~
//
//  012010120101
//  012010101201
//  (just ensure the 2s inserted in between x,y and another 2 outside of x,y is
//  inserted to ensure the overall parity is not changed)
//
//  (this works for y-x>=3)
//  10210
//  01201
//  *  *
//   *  *
//
//  if y-x==2, case 1 and case 4
//  if y-x==1, they're neighbors
//
//
//
//
//~~~~~
//      IF a_y>=min(adjc(a_x)) && a_x>=min(adjc(a_y)):
//          ==> NO CHANGE??
//
//~~~~~~
//      IF a_y IN adjc(a_x) && a_x IN adjc(a_y):
//          ==> NO CHANGE (MEX does not change, duplicate integers)
//
//
//
// ~~~~~~~
//      OTHERWISE, a_y NOT IN adjc(a_x) && a_x NOT IN adjc(a_y):
//          ==> CHANGE (the new neighbor from the x-y construction creates a new
//                      neighbor)
//
//
//
// NOTE:
//      for x,y's
//          we want the friends to have a mutually different elements

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n, x, y);
  vll a;

  bool odd = n % 2 == 1;
  II(i, n / 2) {
    a.PB(0);
    a.PB(1);
  }

  if ((y - x) == 1 || (y == n && x == 1)) {
    // DUPLICATE ADJ FRIENDS
    if (odd)
      a.PB(2); // 2 can be anywhere
  } else {
    // NON-ADJ FRIENDS

    // assuming no circling back (which would be handled by the DUPLICATE ADJ
    // FRIENDS)

    bool odd_dist_friends = (y - x) % 2 == 1;

    if (!odd && !odd_dist_friends) {
      // even-lengthed, even-distanced => perfect middle always exist

      if (n == 4) {
        // a = {0, 1, 2, 1};
        // remember, we want the non-adj friends to be mutually different
        // but not just mutually different, but ensure the neighbors or the MEX
        // stays invariant

        if (x == 1 && y == 3) {
          a = {0, 1, 2, 1};
        } else { // x==2,y==4
          a = {1, 2, 1, 0};
        }
      } else {
        // insert the 2nd 2 in the beginning or at the end?
        if (x == 1) { // x=1, y<n gauranteed => do at the end
          a.pop_back();
          a.pop_back();
          a.PB(2);
        } else { // x>1 => just do at the beginning (can be y==n)
          a.pop_back();
          a.pop_back();
          a.insert(a.begin(), 2);
        }

        a.insert(a.begin() + ((x + y) / 2) - 1, 2);
      }

      // if (n == 4) {
      //
      // } else {
      //
      //   // insert a 2 between x,y's to ensure odd-distance (no circular
      //   // flipback)
      //   a.insert(a.begin() + ((x + y) / 2), 2);
      //   // it is now odd-lengthed and we need to ensure evenness
      //   // (we always have a space at the end)
      //   // but now 2 spaces at the end by the insertion
      //   a.pop_back();
      //   a.pop_back();
      //   a.PB(2); // tightest-case: x 2 y 2
      //            // 0 1 0 1  (bad)
      //            // x   y
      //            // 0 2 1 2  (good?) SPECIAL CASE!!!
      //            //
      //            // 0 1 2 1 ???
      //            //
      //            // 0 1 2 0 1 2  (fine)
      //            // x       y
      //            //
      //            // fine even with the shortest and longest distances
      //            // well except when y==n
      //            // or y==n-1 for that matter
      //            //
      //            // 0 1 2 0 1 2
      //            //   x   y
      //            //
      //            // 2 0 2 1 0 1 ~~~~~ 0 1 (this works b/c x would be 0 )
      //            //
      //            //
      //            // 0 1 0 1 2 2
      //            //       x   y
      //            //
      //            // 0 1 0 2 1 2
      //            //     x   y
      //            //
      //            // 2 0 1 2 0 1 ~~~~~ 0 1
      //
      //   // well now it is 2 elements too long
      //   //
      //   // the 1st a.insert() -> remove the element at 1@n-1
      //   // the 2nd a.PB() -> remove the element at 1@n-1 (1@n-2)
      // }
    } else if (!odd && odd_dist_friends) {
      // NO CHANGE
      // remember, we want friends to have mutually different elements
      // i.e., (with our construction of only 0/1s) we just want to ensure the
      // non-adj friends have the same neighbors so it doesn't change their own
      // MEX (maintain MEX invariance)
    } else if (odd && !odd_dist_friends) {
      // make the even-distanced into odd-distanced
      a.insert(a.begin() + ((x + y) / 2) - 1, 2);
    } else { // odd-lengthed; odd-distanced (non-adj) friends
      a.PB(2);
    }

    // if (!odd && !odd_dist_friends) {
    //   // NO CHANGE
    // } else if (!odd && odd_dist_friends) {
    //   // a 2 is inserted between x,y
    //   // another 2 is inserted outside x,y
    //   //
    //   //
    //   // (be careful with smaller lengths?)
    //   // if n==3 => ODD
    //   // if n==4 ==> EVEN
    //   //      if (y-x)%2==1 ==> FREINDS (looping back) since
    //   //          y-x==1 => DUP ADJ FRIENDS
    //   //          y-x==2 => EVEN-DISTANCED (not what we want)
    //   //          y-x==3 => By n==4, DUP ADJ FRIENDS (when looping back)
    //   // if n==5 => ODD
    //   // if n==6 => EVEN (smallest case)
    //   //
    //   //
    //   //   2?2?  2?2?
    //   // . . . . . .
    //   // *     *
    //   //
    //   // NOTICE, we always have at least 2 spacing at the end
    //   // this is clearly exhaustively always possible
    //
    //   a.insert(a.begin() + ((x + y) / 2), 2);
    //   a.PB(2);
    // } else if (odd && !odd_dist_friends) {
    //   // insert 2 BETWEEN the odd-distanced friends
    //
    //   // recall no duplicate adjacent friends
    //   // a.PB((x + y) / 2);
    //   //
    //   //
    //   // 1 2 3 4 5 6 7 8
    //   // . . . . . . . .
    //   //     *     *
    //   a.insert(a.begin() + ((x + y) / 2), 2);
    // } else { // odd-lengthed && even-distanced friends
    //
    //   // insert 2 OUTSIDE the odd-distanced friends
    //   a.PB(2);
    //   // because x,y is guaranteed to be not dup-adj friends
    //   // we can always put a 2 at the end that will always be outside of them
    //   // (no-circling back)
    // }
  }

  OIT(a);
  ;
}
