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

// start:
//   end:

// P.1: movements are tiled/repeated along the grid max nxm span (mod's exist to
// ensure 1-index consistency)
// P.2: since it's only Y/N, we can simplify the problem by treating A as tiled
// on both axis (if it makes it any easier)

// O.1: staircase up or down from one corner
// O.2: x-movement must not be divisble by m (except if x-mov is 1)
//          same with y-mov

// impl
//      divisbility check requires the sieve again
//      check if b divides m and a divides n
//         WE ARE CHECKING FOR ANY SUBDIVISION, NOT SUB-FACTORS

// H.1: 5x4 movement grid and 6x6 board grid the rows/y-axis will get filled but
// the x-axis won't since both 4 and 6 shares a 2 which means every other
// columns does NOT get filled EXCEPT when any of the values of concern are 1
// (automatic true)
//      so really if the gcd>1 (or a common factor that is more than 1)
//      same thing with movement 6 and board 9 (yes sometimes overlaps the
//      board's border but will always leave a gap of 2)

// counter-example by testcase: there's an example where both axis' gcd=1 and
// yet it says NO (doesnt fill the whole grid)
// O.3: => 17x17 movement grid and 18x18 room grid ==> clearly both gcd==1 yet
// this does not cover all of the room
// we can just simulate it (largely fixed path with two initial option) (or
// think of it like that)
//  actually, the room grid only covers on all Axy where xy are multiples of the
//  gcd (clearly, more general then the initial impl.)
// DEF: call this the gcd-movement (y,x)
//          ~~~~~~~~~~~~ IMPORTANT PROPERTIES: you can start anywhere on the
//          grid in factors
//          ~~~~~~~~~~~~ of y and x

//  if the only available gcd-mov is (1,1) => ABSOLUTELY does not cover the room
//  grid
//          so WHAT absolutely covers ALL the tiles??
//      clearly x=y => NO
//      gcd-mov of (>1,>1) => NO, clearly repeats
//      gcd-mov of (=1,>1) => NO   ~~~~~~~~~~~~~~~~~~~~~~~~~~DEPENDS....
//             ~~~~~~~~~~~~~~ (=1,=2) => since this is gcd, that means the x-mov
//             repeats but
//             ~~~~~~~~~~~~~~ shifts down 1, still skips every other columns...
//             NO...
//              (=1,=2) => regardless, since this is gcd, it still skips every
//              other columns....
//      gcd-mov of (=1,=1) => DEPENDS
//             consider a movement grid of (1,3) and a room grid of (7,7)
//                      CLEARLY, gcd-mov of (=1,=1)
//          IIRC, there's COULD be an edge case where the stairs repeat at a
//          diagonal offset despite (=1,=1)
// simulate or math: intersection
//  10^9 infeasible

// *************************************
// down 2, side 1
// 1 . .
// . . 3
// . 2 .
//
// down 3, side 1
// 1 2 3
// . . .
// . . .
//
//
// down 2, side 1
//
// 1 . . . .
// . . . 4 .
// . 2 . . .
// . . . . 5
// . . 3 . .
//
// 1 . . 4 . .
// . . . . . .
// . 2 . . 5 .
// . . . . . .
// . . 3 . . 6
// . . . . . .
//
// down 6, side 5 (7x7)
// 1 . . x . . .
// . . . 7 . . x
// . . x . . . 6
// . . 5 . . x .
// . x . . . 4 .
// . 3 . . x . .
// x . . . 2 . .
//
// oops probably counted wrong but seems to be we do need to have these stairs
// wrapped around tightly

// seems to be very hard to completely cover the room systematically for now
// (keeps forming loops for non-offset of 1 at least) so what cases will it
// cover all the room....
//
// proof? hypo?
//
//       w
//     x * z
//       y
//
// if ANY tile visited by staircase can visit any of its orthogonal tiles, then
// the room grid CAN BE COMPLETELY COVERED (FINITELY)
//
// HOWEVER,
//      TO VISIT ANY one of the x,y,z,w ==> THE STAIRCASE MUST HAVE a%n
//      or b%m to be 1 or -1 (if both are 1 or -1, they're fine also since this
//      is alternating paths / not a true staircase)
// HOWEVER HOWEVER,
//      ONCE you selected vertically (w,y) or horizontally (x,z), you cannot
//      select the element across (*)
//          so if w, y is impossible; if x, z is impossible
//      ADDITIONALLY,
//          once an axis is picked, you cannot select the element on the
//          opposing axis
//              if one of w,y is selected, x,z is impossible to select
//              if one of x,z is selected, w,y is impossible to select
//      THEREFORE,
//          you can only pick ONE orthogonal axis within A SINGLE STEP (both a &
//          b) (invariance: either move in the beginning is fine, just the
//          alternation that is important)
//
// HYPO: IF you can only pick ONE orthogonal elements within A SINGLE STEP (both
// a & b), what about for MULTIPLE STEP???
//      IF w is selected, then either w+1 is selected (same col.) or w+1 is
//      selected but at whatever twice the horizontal movements
//          which theoretically (depending on various factors) allows one to
//          select another element?

// ~~~~     TO VISIT ANY **2** of the x,y,z,w
//      (two of them)

// post-sol
// insights 1: why did i select square grids as my only examples?
// insights 2: start with an assumption that loops exists (should've seen per
// many examples), how many tiles are visited within a loop (given a,b,m,n) and
// compare that against the total number of tiles in the room insights 3:
// insights 3: n x m = lcm x gcd and 2lcm is the number of states needed for the
// loop too lazy: even with the proof of contradiction for case 3 (gcd=2), it's
// still confusing how that 1-1 equates to exactly nxm tiles visited just from
// the disproving a tile is visited by both directions (actually, it makes
// sense)

void solve([[maybe_unused]] ll T) {
  READ(n, m, a, b);

  // gcd(n,a) == gcd(m,b) == 1
  // gcd(n,m) <= 2 (interesting how it comes back to the structure of the room
  // itself)

  if (gcd(n, a) == 1 && gcd(m, b) == 1 && gcd(n, m) <= 2) {
    OUT("YES");
  } else {
    OUT("NO");
  }

  /*   bool covers_all = true;

    if (b > 1) {
      while (m % b == 0) {
        m /= b;
      }
      if (m == 1) { // b divides m ==> nope
        covers_all = false;
      } else {
        // there's a prime factor in m that b does not have
      }
    }

    if (a > 1) {
      while (n % a == 0) {
        n /= a;
      }
      if (n == 1) {
        covers_all = false;
      } else {
      }
    }

    if (covers_all) { */

  // if (((a == 1 || n == 1) && (b == 1 || m == 1)) ||
  //     ((m % b != 0) && (n % a != 0))) {
  //   OUT("YES");
  // } else { // if either gcd(a,n) or gcd(b,m) >1  in ANY CAPACITY => it will
  //          // repeat along the grid with holes except for 1 cases
  //   OUT("NO");
  // }
}
