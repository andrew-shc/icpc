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

// start: 2038
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
// ABSTRACTION ABSTRACTION ABSTRACTION (AND INVARIANCES)
//
//
//    b1 b2 b3  .  .  .  by
// a1
// a2
// a3
// .
// .
// .
// ax
//
//
// input:
//  a,b STRICTLY increasing => distinct, unique numbering
//  1<=x,y<=n+m
//
//  x <-> n
//  y <-> m
//
//  given nxm matrix, we can get all n of a and m of b except 1 to the choosing
//      (think of this optimal construction as weaving rows and columns)
//
//      so really it's just:
//          if x < n:
//              pick all a
//          else:
//              pick top n-1 a
//          if y < m:
//              pick all b
//          else:
//              pick top m-1 b
//
//          if x >= n && y >= m:
//              pick max(n-th largest a, m-th largest b)
//          elif just x >= n:
//              pick n-th largest a
//          elif just y >= m:
//              pick m-th largest b
//
//  that's it???
//
//
//  THE CATCH: not necessarily distinct/unique across a,b
//
//  regardless,
//      a has n-1 exclusive spot to add its top n-1 unique elements
//      b has m-1 exclusive spot to add its top m-1 unique elements
//
//      the last single one must be shared across both (pick the max of either's
//      top n-th, m-th element)
//
//      if any shared, either a or b has to keep it
//          for each elements that is shared,
//              if the next element of a is larger than the next element of b,
//                  let b take the shared and let a take its next one
//              if the next element of b is larger than the next element of a,
//                  let a take the shared and let b takes its next one
//
//          there could be a trade-off (not greedy)
//              i.e., one could drop-off but maintain stead low decrease rate
//              while the other starts steady but longer, steeper drop-off later
//              on (i mean sum is sum... shouldn't matter?)
//       ==> extended to who to pick who when shared elements occured
//
// answer:
//  max possible cost <== max sum of all unique numbers occured in the matrix
//                ^
//         sum of all unique, occured numbers
//

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n, m, x, y);
  IVLL(a, x); // also sorted??
  IVLL(b, y);

  ll sum = 0;

  // vll exclusive_a;
  // vll exclusive_b;
  // vll duplicate;

  vll mixed;

  ll ai = x - 1;
  ll bi = y - 1;
  ll d = 0;
  while (true) {
    if ((ai >= 0 && bi >= 0) && a[ai] == b[bi]) {
      mixed.PB(a[ai]);
      d++;
      ai--;
      bi--;

      // it was correct before where we do not decrement ai,bi
      // remember, duplicates are handled separately and no need to add any more
      // duplicates if a,b satisfies the reverse max-bounds already
      //
      // but the duplicates refers to these indices...
      // treat dplicates separately
    }
    // else {
    // bool bk = true;

    // else if to ensure the removal of element by el. isntead of 2-by-2
    // to ensure duplicates are covered until neither elements can be added
    // anymore by the lower bounds but this just decreases ai first before bi
    if (ai >= max(0LL, x - n - d) && bi >= max(0LL, y - m - d)) {
      if (a[ai] > b[bi]) {
        mixed.PB(a[ai]);
        ai--;
      } else if (b[bi] > a[ai]) {
        mixed.PB(b[bi]);
        bi--;
      }
    } else if (ai >= max(0LL, x - n - d)) {
      // exclusive_a.PB(a[ai]);
      mixed.PB(a[ai]);
      ai--;
      // bk = false;
    } else if (bi >= max(0LL, y - m - d)) {
      // exclusive_b.PB(b[bi]);
      mixed.PB(b[bi]);
      bi--;
      // bk = false;
    } else {
      break;
    }
    // if (bk) {
    //   break;
    // }
    // }
  }

  DBG_ITER(mixed);
  ST(mixed);
  ll bound = min(n + m - 1, (ll)mixed.size());
  // for (ll i = bound - 1; i >= 0; i++) {
  II(i, bound) {
    // sum += mixed[bound - i - 1];
    sum += mixed[mixed.size() - i - 1];
  }

  // ll ai = 0;
  // ll bi = 0;
  // while (true) {
  //   if (ai >= x && bi >= y) {
  //     break;
  //   } else if (ai < x && (bi >= y || a[ai] > b[bi])) {
  //     sum += a[ai];
  //     ai++;
  //   } else if (bi < y && (ai >= x || b[bi] > a[ai])) {
  //     sum += b[bi];
  //     bi++;
  //   } else {
  //     // a[ai]==b[bi] (when ai < x && bi < y)
  //     // find the next difference (could be 1 element after or many elements
  //     // after)
  //     //
  //     // regardless, the shared elements will be added in some way or form
  //     // until the next difference (is it really greedy?)
  //     //
  //     //
  //     // x x x x x x x x 5 4 3 2 1
  //     // x x x x x x x x 9 1
  //     //
  //     // if x==y: greedy on the first and the next difference(s) (?)
  //     //      but what if a picks its next differing element that is larger
  //     than
  //     //      b? b has to reserve a slot for it and delay its first differing
  //     //      element (although its smaller). if the next differing element
  //     of a
  //     //      is still larger than obviously pick a, but if the next
  //     differing
  //     //      element of a is smaller than b's next differing, it can be
  //     //      problematic if b has already reserved all of its exclusive
  //     spot.
  //     //
  //     //      abstraction?
  //     //      greedy with regret?
  //     //
  //     //    ~~~~ prefix sum a & b (excluding duplicates)
  //     //    re-create a[x+c,n] & b[y+c,m] that excludes cross a-b duplicates
  //     //        and a d[c] for all the duplicates
  //     //
  //     //        WHERE the duplicates (ranks) is important also
  //     //              => maybe all the duplicates are at the end and not
  //     //              important?
  //     //
  //     //            i
  //     //    easier (more systematic) observation?
  //     //
  //     //!    per solution/tutorial:
  //     //!          - confirmation of my prior observations
  //     //!          - did intend to ALSO create a,b,d
  //     //!          - apparently this is an important observation
  //     //!                      take at most n from a[]
  //     //!                      take at most m from b[]
  //     //!!!!!!!!!              take at most n+m-1 from d[] (worst case,
  //     original
  //     //!                      a== original b)
  //     //        IMPORTANT OBSERVATION: d[] can be taken by either a or b so
  //     //        n+m-1. WE DO NOT CARE IF THE DUPLICATES ARE AT THE END OR
  //     //        WHATEVER, just comapre the max across a,b,d until these
  //     //        CONSTRAINTS have been reached (no need to complicate-ly trim
  //     the
  //     //        a's, b's, and d's), just find the max across three until the
  //     //        constraints are satisfied.
  //     //        Greedy! but why greedy?
  //     //              if we take an eleemnt from a,b why not c?
  //     //                      maybe these remaining duplicates are at the end
  //     //                      and useless
  //     //              if we take c why not a,b?
  //     //                      maybe these duplicates are large and should be
  //     //                      incporated before a,b
  //     //                      but then how do we ensure we're not in the case
  //     of
  //     //                      n-1 a's, m-1 b's, n+m-2 d's?? (clearly OOB)
  //     //                clearly if we take only a,b everything's usual
  //     //                      but if we take duplicates... how many can a or
  //     b
  //     //                      take?? either a or b has one less... but how to
  //     //                      codify it?
  //     //!               sort(a[:n]+b[:m]+d)[:n+m-1] ????
  //     //!                 (we guarantee a,b's are valid by only taking first
  //     n,
  //     //!                 first m and also because duplicates only takes less
  //     //!                 than n,m)
  //     //!                   if we take duplicates then either a,b decrease so
  //     //                      a+b      d
  //     //                      n+m      =    ~n+m-1
  //     //                      n+m-1    ++   ~~n+m
  //     //
  //     //                      so like take one duplicates and take one less
  //     from
  //     //                      a+b
  //     //
  //     //                      but if all the duplicates are in a, then
  //     (doesn't
  //     //                      makes sense)
  //     //                      but if all top-n are duplicates then the
  //     remaining
  //     //                      n elements in exclusive-a (if better than say
  //     //                      exclusive-b) will still be taken since the
  //     //                      duplicates will be reserved by b[] since b's
  //     //                      exclusive elements are not as large as a
  //     //
  //     //                      same thing with other way around
  //     //                      if say all m duplicates are at the top and all
  //     //                      exclusive-b elements are better than
  //     exclusive-a,
  //     //                      then a[] will just reserve its space for the
  //     //                      duplicates and push down the more worse
  //     exlusive-a
  //     //                      elements
  //     //
  //     //                      or maybe top-m duplicates but exclusive-a
  //     better
  //     //                      than exclusive-b, so b just reverse these m
  //     //                      duplicates ahead of its own exclusives
  //     //
  //     //                      THE INVARIANT: when taking a duplicate, we do
  //     not
  //     //                      care whether which a,b reserves the duplicates,
  //     we
  //     //                      just know the WORST of a+b (so far) is removed
  //     //                      and whether it was exclusive-a or exclusive-b
  //     it
  //     //                      doesn't matter as they'll (the corresponding
  //     a,b)
  //     //                      just reserve it for the duplicates if the
  //     //                      corresponding a,b has the MORE WORSE exclusive
  //     //                      elements than the opposing b,a
  //     //                 similiar observation made before in which separate
  //     //                 exclusives from duplicates but different in that
  //     still
  //     //                 wanted to take the duplicates in the order of the
  //     input
  //     //                 and question whether a or b takes it would effect
  //     later
  //     //                 decisions (e.g., trade-offs / non-greedy) but the
  //     //                 INVARIANT of taking the next best option (being the
  //     //                 duplicates) IMPLIES taking the worst of a,b (do not
  //     //                 care which) but with the a[:n] b[:m] it simplifies
  //     the
  //     //                 implementation without thinking when to stop looking
  //     at
  //     //                 the worst (when there are more exlusives then the
  //     n,m;
  //     //                 for example)
  //     //            technically we can just find the max across a,b,d??
  //   }
  // }
  // if (x < n) {
  //   II(i, x) { sum += a[i]; }
  // } else {
  //   for (ll i = x - (n - 1); i < x; i++) {
  //     sum += a[i];
  //   }
  // }
  //
  // if (y < m) {
  //   II(i, y) { sum += b[i]; }
  // } else {
  //   for (ll i = y - (m - 1); i < y; i++) {
  //     sum += b[i];
  //   }
  // }
  //
  // if (x >= n && y >= m) {
  //   sum += max(a[x - n], b[y - m]); // remember, 1@-1@=0@d
  // } else if (x >= n) {
  //   sum += a[x - n];
  // } else if (y >= m) {
  //   sum += b[y - m];
  // }

  O(sum);
  ;
}
