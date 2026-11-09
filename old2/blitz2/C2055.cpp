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
// 4
//
// 3 3
// DRRD
// 0 2 3
// 0 0 0
// 3 1 0
// 4 5
//
// DRRRRDD
//  0 1  0  2 3
//  0 0  0  0 0
// -1 0 -3 -3 0
//  0 0  0 -1 0
//
// 2 3
// RRD
// 0 0 0
// 0 1 0
//
// 5 5
// DDDDRRRR
// 0 25  2  9 11
// 0  6 13 20 22
// 0 17 24  1  8
// 0  3 10 12 19
// 0  0  0  0  0
//
// Output
// Copy
//
// 1 2 3
// 2 3 1
// 3 1 2
//
// -6  1  0  2   3
//  7 -1  3  2 -11
// -1  0 -3 -3   7
//  0  0  0 -1   1
//
//  0 -1  1
//  0  1 -1
//
// 18 25  2  9 11
//  4  6 13 20 22
// 15 17 24  1  8
// 21  3 10 12 19
//  7 14 16 23  5
//
//
//
// P.1: the path always crosses every column or row
//      P.1/1: we have the DoF to arbitrarily decide what "x" is
//              (an easy choice is to set x=0)
//      P.1/2: we can just compute the sum of existing elements and use the
//      difference against "x" to find the difference needed (?????)
//      P.1/3: we can simplify the problem by assigning all corners of the paths
//      to 0 ==> every elements on the path will not be affected by the decision
//      made by on the other path (hopefully this does not make it impossible)
//
//      for each straight segments (horizontal/vertical),
//          say a segment of 5-lengthed in a 10x10 matrix
//
//          a+b+c+d+e + sum of 4 other elements = x
//                      (assume the other one is a
//                      corner)
//          a + sum of 9 other elements = x
//          b + ... = x
//          c + ... = x
//          d + ... = x
//          e + ... = x
//          +
//         ...
//          =
//          x
//
//          5 variables, 6 equations... (might be impossible???)
//
//          a = x-s_a
//          +
//          b = x-s_b
//          +
//          c = x-s_c
//          +
//          d = x-s_d
//          +
//          e = x-s_e
//          =
//      x-s_abcde
//
//          ==>
//
//          5*x -s_a-s_b-s_c-s_d-s_e = x - s_abcde
//          4*x = s_a+s_b+s_c+s_d+s_e - s_abcde
//          x = (s_a+s_b+s_c+s_d+s_e - s_abcde)/(5-1)   for each segments
//
//          more generally
//              c_* := sum of columns at the column of * (excluding *
//                      itself/themselves)
//              r_* := sum of rows at the row of * (excluding *
//                      itself/themselves)
//              i_* := identity
//              a_* := adjoint (identity <-> the other direction)
//                             (or, col <-> row)
//
//          for each segments with length of y excluding corners:
//              x = (sum_{k in seg} i_k - a_{union k in seg} ) / (y-1)
//
//
// a 2 3
// * b *
// 3 1 c
//
// well 1-1 = 0 (we're dividing by 0)
//
//
//
//
//!!! Hint 1.
//!             nx+mx = sum of grid + unknowns on the path
//!     =>    (n+m)*x = values not on the path + 0 DoF values on the path (the
//!                     non-corners) + interior corners
//
// Hint2-3 helped nothing...
//
// wait...
//
// recall on the last worked problem, some problems are not meant to be thought
// of visually/intuitively but rather mathematically/logically/textually
//
// in this case, we know the values collapse when we arbitrarily pick an x
// starting from the top left (or bottom right). the values sort of just
// collapse onto themselves. however, eventually we reach to the last cell which
// we don't know since there's like 2 equations and 1 variables that might lend
// us a NO SOLUTION. However, we have a guarantee where (n+m)*x = sum of the
// board (except the last cell) + the last cell
//
// don't even try to understand it, just think about it logically
//
// if this AC, this proves that thinking textually sometimes are needed. (as in
// just thinking abt a problem textually once some facts/axioms/properties are
// written down textually)

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n, m);
  IS(path);
  vector<vll> alts;
  II(i, n) {
    IV(row, m);
    alts.PB(row);
  }

  // per input constraint, we can linearly do O(nm) over nm
  ll x = 0; // chosen selected x (CONSTANT)
  ll i = 0;
  ll j = 0;
  bool updown = path[0] == 'D'; // false: <->, true: up/down
  // for (auto &directions : path) {
  // II(k, path.size()) {
  for (ll k = 1; k < path.size(); k++) {
    ll sum = 0;
    if (!updown) {
      // calculate vertical slice (intersecting/crossing a horizontal segment)

      II(ii, n) {
        if (ii != i)
          sum += alts[ii][j];
      }
    } else {
      // calculate horizontal slice (intersecting/crossing a vertical segment)

      II(jj, m) {
        if (jj != j)
          sum += alts[i][jj];
      }
    }

    alts[i][j] = -sum;

    if (path[k - 1] == 'D') {
      i++;
    } else {
      j++;
    }
    if (path[k] == 'D') {
      updown = true;
    } else {
      updown = false;
    }

    // if (directions == 'D') {
    // if (path[k] == 'D') {
    //   i++;
    //   updown = true;
    // } else {
    //   j++;
    //   updown = false;
    // }
  }
  { // one more time??
    ll sum = 0;
    if (!updown) {
      // calculate vertical slice (intersecting/crossing a horizontal segment)

      II(ii, n) {
        if (ii != i)
          sum += alts[ii][j];
      }
    } else {
      // calculate horizontal slice (intersecting/crossing a vertical segment)

      II(jj, m) {
        if (jj != j)
          sum += alts[i][jj];
      }
    }

    alts[i][j] = -sum;
  }

  ll sum_board = 0;
  II(ii, n) {
    II(jj, m) {
      if (!(ii == n - 1 && jj == m - 1)) {
        sum_board += alts[ii][jj];
      }
      // if (ii != n - 1 && jj != m - 1) {
      //   sum_board += alts[ii][jj];
      // } else {
      //   DBGLN("SKIPPED");
      // }
    }
    // DBGLN(sum_board);
    // DBG_ITER(alts[ii]);
  }

  // by the guarantee that the sum of board must be a constant
  alts[n - 1][m - 1] = -sum_board;

  // sum of cells (except the last cell) + the last cell = (n+m)*x = 0
  // sum o cells = - the last cell???? (why it not negative???)

  // DBLOCK {
  //   // verify the observation is true
  //
  //   II(i, n) {}
  // }

  II(i, n) {
    OIT(alts[i]);
  }

  ;
}
