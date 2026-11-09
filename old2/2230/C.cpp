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

// start: 1823
//   end: 1952?

// 1 3 1 3 1 3 1  <-- extreme zigzag.. requires a duplicate-adjacent before
//          inserting a new number
//
// 3 3 3 1 1 5 1 1 3  <--- also allows blips (single-zigzag in nested dup-adj)
//
// 1 1 2 2 3 3 1
//
// 1 3 5 3 xxxx
//
// circle condition FEELS like a weight to prevent too much change, as if
//      it needs duplicate-adjacents before allowing it to add a new, unique
//      element unseen for the past 2 element

// P.1: /1 if sum is less than 2 ==> 0
//      /2 if all cn==1 ==> 0
//      /3 if n<=2 ==> c1+c2
//      /4 if all cn>=2 ==> all

// O.1: all 2s or all 3s are fragile (cannot support any 1s) EXCEPT when the
// overall n==2 (or REDUCED TO n==2)
//          2s cannot b/c both sides surrounding the 1 would be single-el apart
//          3s cannot b/c one of the sides surrounding the 1 would be single-el
//          apart
// O.2: the point of solving are the 1s and how different kidns of >4s can
//          surround 1s
// O.3: cycles only helps with when n is REDUCED TO 2 (cycles don't matter, just
//          whether n==2 or n>2 can vary the problem space a lot)
// O.4: 4s can support 2 1s (since the 4s can split into 2+2 that can be shared
//          with any 1s in between)
//      O.4/1: 2+2+1? (the 1 does not help) ==> 2+3 (always broken into >=2)
//                          x2y3
//      O.4/2: >4s can be broken into atomic 2s (or a single remainder 3s) to
//          join 1s, even heterogenously? (nope, must be homogenously)
//      O.4/3: only >=2s can directly join with another >=2s, 1s absolutely
//          CANNOT join heterogenously
//              x x * x x * y y (x * y fails the condition)
//              x x * x x y y * y y (only >2s can directly join another >2s)
// O.5: it is OPTIMAL to keep >=4s grouped/clumped together because their inner
//      2-atomics can be shared and doubled with another 1s (e.g., >= 6s) that
//      MAXIMIZES 1s usage ==> avoid any zigzags and help out the blips (the 1s)
//
//      2 -> 1 1s (homo) no hetero
//      3 -> 1 1s (homo) no hetero
// O.6: 4 -> 2 1s (homo)
//      4 -> 1 1s (hetero)
//      6 -> 3 1s (homo)
//      6 -> 2 1s (hetero)
//      Xs -> X/2 1-cards or one less when mixed with other >=2s
//
//      O.6/1: it is always optimal to utilize hetero (since just a single more
//          >=4s while keeping same amount of 1s)
//              ==> greedily take all >=2s (don't stop to check the trade-off
//              with a single 4s)

// IMPL:
//          include all >=2s automatically (which is optimal)
//          count number of 1s (#)
//          if no >=2s => P.1/2 ==> 0
//
//          if homo:
//              => a single >=2s
//              run the homo rulebook
//                  if 2,3: supports a single 1s A+=min(#,1) #-=min(#,1)
//                  if X: supports X/2 1s A+=min(#, X/2) #-=min(#,X/2)
//
//          ELSE if hetero:
//              => multiple >=2s
//              if has >=4s:
//                  run the hetero rulebook
//                      if X: supports X/2-1 1s A+='' #-=''
//
//          OUT A

// ~~~~ O.1: all 2s => cannot support any 1s (except for just "2 1")
// ~~~~ O.1:

// 2 2 2 2 2 2 2 2 2
// 2 2 2
// 2 2 1 x => all 2s are fragile
//                  1s are useless and hopeless ==> can never be recovered and
//                  one-way to removal
//              hence, 2 2 (4)
//
// 2 3 1 => x x y y y z (nope)
//          x x y y z y (nope)
//          x y x y z y
//          y x y z x y
//          ... H.1: since 2s are fragile, we can try surrounding 1s with 3s
//                      however, it means one side only has 1 el. (bad) and the
//                      other side has 2 el. (fine)
//                          the 1 el. is fine when transitioning to itself
//                          (e.g., mod-cycling) but cannot include transitions
//                          to different el.
// 3 3 1 => x x x y y y z
//          x x y y z y x
//
// 3 3 2 => x x x y y y z z (follows P.1/4)
//
// 2 4 1 => x x y y y y z
//          x x y y z y y (yes)

void solve([[maybe_unused]] ll T) {
  READ(n);
  READ_VLL(c, n);

  // pre-cond check forgot
  // P.1/2 resolved automatically
  // P.1/1: sum less than 2 => [ 1 1] (falls under P.1/2) or [2] (the edge case)
  //        double-checking: [3] is valid
  //                           [2] handled (the edge case)
  //                           [1] handled already
  if (n == 1 && c[0] == 2) {
    OUT(0);
    return;
  }

  ll ones = 0;
  ll ones_supported = 0;
  ll homo_correction = 0; // applies to ones supported if homo
  ll ans = 0;
  bool is_homo = true;
  for (ll &ci : c) {
    if (ci == 1) {
      ones++;
    } else {
      if (ans > 0) { // another >=2s existed before ==> hetero
        is_homo = false;
      }
      ans += ci;
      if (ci == 2 || ci == 3) {
        homo_correction += 1;
      } else if (ci >= 4) {
        ones_supported += ci / 2 - 1; // floor division
        homo_correction += 1;
      }
    }
  }

  DBG_ITER(c);
  DBGLN(ones, ones_supported, homo_correction, ans);

  if (is_homo) {
    ones_supported += homo_correction;
  }

  ans += min(ones, ones_supported); // max supported or max available ones
  OUT(ans);
}
