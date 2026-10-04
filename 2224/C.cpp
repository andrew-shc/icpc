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

// start: 7:02
//   end: x

// P.1: you can only swap brackets up and down
// P.2: find an EXISTENCE of valid bracket seq for both
// P.3: a regular bracket seq. just needs a closing bracket (at some point) for
// every opening bracket

// O.1: if @i, both are (,( or ),) ==> moot (no point in checking it)
// O.2: it can be thought of travelling between a,b but at each time the path
// must push one index to the future
// O.3: ( is +1, ) is -1
//      at @0: both must be (,( (since all starts at 0 and we do not want
//      negatives)
//         @1: anything
//         @2: maintain non-negatives on BOTH sides (nope not initially, can be
//         swapped to maintain non-negativity)
//         ....
//         @-1: both must be ),) (since we want the ends to be 0)
// O.4: at any index, swapping can yield same +1,+1 (-1,-1) or in twos +1,-1 <->
// -1,+1 (difference of two)

// H.1: just check both must start with ( and end with ) and just ensure equal
// amounts of (,) per seq.?
//      what could go wrong?
//      COUNTER-EXAMPLE: ()))))((((()
//                       ()))))((((()
//          the moment both are ),) yet 0 (both must result in negative levels
//          => NOT REGULAR)

// H.2: for each seq. count the #s of ('s and )'s. add the first pair (both must
// be +1 or '(' )

// post-soln.
//
//
// we can do instead of what the soln is doing is if ai=bi, make sure they have
// complementary ai=bi later. if not => NO (impossible to be regular). if yes,
// omit them and ignore it.
//      IMPORTANT PROPERTY: since a0,b0 must be '(', an-1,bn-1 must be ')'
//
// now, for each indices, let's look at seq. A and suppose we want to greedily
// shorten/close the seq. A (i.e., try to use `)` -1 as much as possible)
//      => if 0 (i.e., before [i] there's as much `)` as `(`) then we flip a[i]
//      to `(` (resulting in `b` to be `)` which means `b` greedily
//      opens/elongates `(`)
//   i mean i guess its elegant?
//

// ~~~~~~~~~~~~~~~~~~~~~~~~~

// would assuming half ('s and half )'s help?
//      assuming both seq's must start and end with ( and )  && independently
//      checking levels on equal pairs (which will be tested separately from
//      differing pairs)
//
//      greedily swapping in ) for seq. A to close as much of it as possible =>
//      greedily swapping in ( for seq. B to open as much of it as possible
//
//          in this inner environment, assume the initial ( and the final ) is
//          covered (NEEDS TO BE CHECKED)
//              the inner DIFFERING pairs ALWAYS AAAAAAAAALWAYS WORK since the
//              equal pairs must come in twos and since seq's are even the
//              DIFFERING PAIRS must be even
//                  => ALWAYS POSSIBLE (even amount of differing pairs) ==>
//                  close,open <-> open,close as long the environemnts of the
//                  differing pairs are in an positive environment set-up by the
//                  equal pairs (e.g., equal pairs, treated as a single seq.
//                  must have a level of >=0 always)
//                      REMEMBER: we start with a +1 level (both seq.) and get
//                      +1/-1 (each seq. A/B) but for seq. B it could be
//                      invalidated since the second equal pairs might be
//                      another closing parenthesis that originally works on a
//                      +1 level but now on a 0 level (-> -1 level) which would
//                      be undoable in this method
//
//               (()())
//               ())(() <-- impossible case....
//
//  let's work from the backwards. assuming the the two subsequence ARE regular,
//  in WHAT cases flipping them yield the two subsequence as IRregular? (if
//  that's impossible, that means we can just check if individual subseq. are
//  regular)
//          KEY INSIGHTS: the opposing subseq MUST have the opposing amounts of
//          ('s and )'s so one can swap them until these groupings are equal
//          within each seq. <==> it's just re-stating the number of differing
//          pairs...
//
//
//  another insight: (codeforce solutions/tutorial are so useless)
//      two charts of the seq's levels: on matching (equal) pairs they go up and
//      down at the same time and cannot be changed in anyways; hence,
//      independently checked for regularity
//          for opposing pairs, the two lines would diverge exactly the opposite
//          direction, which means if the two lines are already at 0 (by the
//          previous and/or coming matching pairs)
//              this will be always be irregular since by the observation of
//              divergence, one of the seq must have negative level
//                  ==> higher the level within the opposing pairs island
//                  (surrounded by matching pairs) the more extreme the
//                  divergence can be
//                      but to make our matter simpler, it is always the best to
//                      keep the divergence minimal (hence, the solution
//                      mentions something about always trying to close with ')'
//                      but open '(' whenever it's not possible )
//                          ==> by the observation of even amount of
//                          opposing/differing pairs, divergence will always be
//                          0 by the end
//                              but keep in mind the matching pairs zone can
//                              diverge for a long time (optimally diverge by at
//                              most 1) if the opposing pair island only has an
//                              odd amount of pairs (the remaining odd pairs
//                              will exist) where the divergence can cause
//                              issues when one of the seq's level dips below 0
//                              while the other seq's level scrapes by AT 0
//
//          what assumptions were used so we can pre-cond on it:
//              observation of even amount of opposing pairs <== even amount of
//              matching pairs (required)
//
//          implementation:
//              check for even, reciprocol amount of matching pairs
//              then go element by element
//
//              for each element
//                  if matching
//                      increment/decrement both seq's level,
//                      divergence=0 (as a separate book-keeping variable for
//                      easier impl.)
//
//                  else if differing
//                      if NOT diverged:
//                          increment A & decrement B (either works, but
//                          choose one for the rest), divergence++
//                      if diverged: (divergence will jsut be 0 and 1 can be
//                      bool)
//                          decrement A & increment B
//
//                  if both level A & level B >= 0 (althought in practice B's
//                  level would be more problematic)
//                      good / continue
//                  else:
//                      bad / break / irregular
//

void solve([[maybe_unused]] ll T) {
  READ(n);
  READ_S(a);
  READ_S(b);

  bool both_reg = true;

  ll cnt = 0;
  INC(i, n) {
    if (a[i] == b[i] && a[i] == '(') {
      cnt++;
    } else if (a[i] == b[i] && a[i] == ')') {
      cnt--;
    }
  }

  if (cnt != 0) {
    both_reg = false;
  } else {
    ll a_level = 0;
    ll b_level = 0;
    bool diverged = false;
    INC(i, n) {
      if (a[i] == b[i]) { // matching
        if (a[i] == '(') {
          a_level++;
          b_level++;
        } else {
          a_level--;
          b_level--;
        }
      } else { // opposing pairs (we pick our own order)
        if (diverged) {
          a_level--;
          b_level++;
        } else {
          a_level++;
          b_level--;
        }
        diverged = !diverged;
      }

      if (a_level >= 0 && b_level >= 0) {
        // we good, continue checking
      } else {
        both_reg = false;
        break;
      }
    }
  }

  /*   ll eq_levels = 0;
    ll a_levels = 0; // excluding equals
    ll b_levels = 0;
    ll ta = 0;
    ll tb = 0;
    INC(i, n) {
      if (a[i] == b[i]) {
        if (a[i] == '(') {
          eq_levels++;
          ta++;
          tb++;
        } else {
          eq_levels--;
          ta--;
          tb--;
        }
      }
      if (eq_levels < 0) {
        both_reg = false;
        break;
      }
      if (a[i] ==
          b[i]) { // i guess we really ignore the ai==bi case and try to set
                  // ai='(' if there are MORE ')' before (excluding ai==bi)
        continue;
      }

      if (a[i] == '(') {
        a_levels++;
        ta++;
      } else {
        a_levels--;
        ta--;
      }
      if (b[i] == '(') {
        b_levels++;
        tb++;
      } else {
        b_levels--;
        tb--;
      }

      // greedily flip ai's `(` to `)`
      if (a[i] != b[i] && a_levels > 1) {
        a_levels -= 2;
        b_levels += 2;
        ta -= 2;
        tb += 2;
      } else if (a[i] != b[i] && a_levels <= -1) {
        a_levels += 2;
        b_levels -= 2;
        ta += 2;
        tb -= 2;
      }

      // if at any point the prefix at one of the seq falls below, (inverted
      // grouping) there's no hope in getting it back (because the extra
    negative
      // levels must exist on at least one of the seq. but you're just pushing
      // around at this point)
      if (ta < 0 || tb < 0) {
        both_reg = false;
        break;
      }
    }

    if (eq_levels > 0) {
      both_reg = false;
    }
    // if at the END the prefix is still above (dangling parenthesis) => NO
    // (remember we havent checked for equal ( or ) but if we checked it we
    don't
    // need this)
    if (a_levels > 0 || b_levels > 0) {
      both_reg = false;
    } */

  if (both_reg) {
    OUT("YES");
  } else {
    OUT("NO");
  }
}
