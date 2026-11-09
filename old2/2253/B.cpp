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

// start: 1814
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
// in other words, ensure no duplicate elements are adjacent with an option to
// swap elements AT MOST once (after removal/de-duplication)
//
//
// note
//
//
// 11112222
// 11121222
// **    **
//
// swap still has limited improvemented (but still an improvement
// nonetheless)
// but can keep an extra 2 modules (in the best case scenario for a swap)
// for any two-duplicate-groups with both having a length >=2
//
// this could also work for
//
//     v v one-sided swapping (1)
// 3 2 1 1 2 3
// 3 1 2 1 2 3
// 3 2 1 2 1 3
//
//
// per chatgpt, the fact that swapping happens AFTER removal does matter
//
// 1 1 1 2
// 1 1 2 1
// but regardless this is just more conditions... not elegant
//
//
// soln. says to abstract the input raw-space as block-space invariant to
// duplicate element ordering
//      AGAIN: ABSTRCTION ABSTRACTION ABSTRACTION (INVARIANCES)
//
// and, yes, we can only increase +0, +1, or +2 and it did suggest a
// case-by-case approach in blocks
//
// +2: requires 2 adjacent >=2-lengthed blocks (that's all it needs)
//                          ^ new insight: removal can always reduce this to ==2
//                          (to optimally allow the swap to work)
// +1: requires at least one >=2-lengthed blocks adjacent to a 2 1-lengthed
// block or another >=2-lengthed block or at the end
//      can't be another >=2-lengthed block (that's the +2 case)
//      can't be the end (the block can't swap anything)
//      so adjacent to another 1-lengthed block with block beyond being the END
//      or a block of different element
//              we don't want 1 1 4 1 1 2 1 <-- ~~~~~ this actually works
//                            1 1 4 1 2 1 1
//
//              but we want   1 1 4 1 1 2 3
//
// +0: means all ==1-lengthed blocks
//

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n);
  IVLL(a, n);

  ll m = n;

  vpll blocks;
  blocks.PB({a[0], 1});
  for (ll i = 1; i < n; i++) {
    if (a[i - 1] == a[i]) {
      blocks.back().second++;
      m--;
    } else {
      blocks.PB({a[i], 1});
    }
  }

  II(i, blocks.size() - 1) {
    if (blocks[i].second >= 2 && blocks[i + 1].second >= 2) {
      O(m + 2);
      return;
    }
  }

  // swap ->
  II(i, blocks.size() - 1) {
    if (blocks[i].second >= 2 && blocks[i + 1].second == 1 &&
        (i < blocks.size() - 2 ? blocks[i].first != blocks[i + 2].first
                               : true)) {
      O(m + 1);
      return;
    }
  }

  // swap <-
  for (ll i = 1; i < blocks.size(); i++) {
    if (blocks[i - 1].second == 1 && blocks[i].second >= 2 &&
        (1 < i ? blocks[i - 2].first != blocks[i].first : true)) {
      O(m + 1);
      return;
    }
  }

  O(m);
  return;

  // ll max_modules = n;
  // bool swapped2 = false;
  // bool swapped1 = false;
  // II(i, n - 1) {
  //   if (a[i] == a[i + 1]) {
  //     // adjacent duplicates
  //     max_modules--;
  //   }
  //
  //   if (i < n - 3 && ((1 <= i ? a[i - 1] != a[i] : true) && a[i] == a[i + 1]
  //   &&
  //                     a[i + 1] != a[i + 2] && a[i + 2] == a[i + 3] &&
  //                     (i < n - 4 ? a[i + 3] != a[i + 4] : true))) {
  //     // max_modules += 2;
  //     swapped2 = true;
  //   }
  //
  //   // if (i < n - 3 && (!swapped2 && (a[i] == a[i + 1] && a[i + 1] != a[i +
  //   2]
  //   // &&
  //   //                                 a[i + 2] == a[i + 3]))) {
  //   //   // max_modules += 2;
  //   //   swapped2 = true;
  //   // }
  //
  //   // usually works by checking and matching a a b or a b b
  //   //
  //   // only case it doesnt work if the swap jsut moves the elemnets around as
  //   in
  //   //
  //   // a a a b a a a  <-- this would not at all
  //   // x a a b a a x  <-- this would +1
  //   //   * * ^ * *
  //   //
  //   //   super un elegant
  //   //   whatever editorial's soln. doesn't seem that much better
  //   //
  //   //  ok more generalized elegant condition
  //   //
  //   //
  //   //
  //   //   --- <<<<<<<< swap
  //   // a * ^ b or
  //   // a * ^ b
  //   //
  //   // 1. a == *
  //   // 2. b == ^
  //   // 3. * != ^
  //   // 4. a != ^
  //   // 5. * != b
  //   //
  //   // if all these 5 conditions satisfy, we can swap AND +2
  //   //      this is just the +2 case
  //   //
  //   //
  //   // x a * ^ b y
  //   //
  //   // 1. * != ^
  //   // 2L. a == *
  //   // 3L. x != a (or OOB)
  //   // 4L. * != b (additional checks)
  //   // ~~~~~~~~~~~ 4L. a != ^
  //   // 2R. b == ^
  //   // 3R. y != b (or OOB)
  //   // ~~~~~~~~~~~ 4R. b != *
  //   //
  //   // we do not care if the outer x/y is different from ^/x--respectively
  //
  //   if (i < n - 2) {
  //     if ((1 <= i ? a[i - 1] != a[i] : true) &&
  //         (i < n - 3 ? a[i + 1] != a[i + 3] : true) &&
  //         (a[i] == a[i + 1] && a[i + 1] != a[i + 2])) {
  //       swapped1 = true;
  //     }
  //   }
  //   if (i < n - 2) {
  //     if ((i < n - 3 ? a[i + 2] != a[i + 3] : true) &&
  //         (1 <= i ? a[i - 1] != a[i + 1] : true) &&
  //         (a[i] != a[i + 1] && a[i + 1] == a[i + 2])) {
  //       swapped1 = true;
  //     }
  //   }
  //
  //   // if (i == 0) {
  //   //   if (a[i] == a[i + 1] && a[i + 1] != a[i + 2]) {
  //   //     swapped1 = true; // swap <-
  //   //   }
  //   // } else if (i == n - 3) {
  //   //   if (a[i] != a[i + 1] && a[i + 1] == a[i + 2]) {
  //   //     swapped1 = true; // swap ->
  //   //   }
  //   // } else if (1 <= i && i < n - 3) {
  //   //   // assymetry due to inner-swap <- just needs to check 1 to the left
  //   //   // while for the inner-swap -> we need to check 3 to the right
  //   (since
  //   //   the
  //   //   // window of reality is really just from i+1 to i+3)
  //   //   if ((a[i - 1] != a[i] && a[i] == a[i + 1] && a[i + 1] != a[i + 2])
  //   ||
  //   //       (a[i] != a[i + 1] && a[i + 1] == a[i + 2] && a[i + 2] != a[i +
  //   3]))
  //   //       {
  //   //     swapped1 = true;
  //   //   }
  //   // }
  //
  //   // if (i == n - 3 || i == 0) {
  //   //   if ((a[i] == a[i + 1] && a[i + 1] != a[i + 2]) ||
  //   //       (a[i] != a[i + 1] && a[i + 1] == a[i + 2])) {
  //   //     swapped1 = true;
  //   //   }
  //   // } else if (1 <= i && i < n - 3) {
  //   //   if ((a[i] == a[i + 1] && a[i + 1] != a[i + 2]) ||
  //   //       (a[i] != a[i + 1] && a[i + 1] == a[i + 2])) {
  //   //   }
  //   // }
  //
  //   // if (i < n - 3 &&
  //   //     (!swapped1 && (a[i] == a[i + 1] && a[i + 1] != a[i + 2] &&
  //   //                    a[i + 1] != a[i + 3]) ||
  //   //      (a[i] != a[i + 2] && a[i + 1] != a[i + 2] && a[i + 2] == a[i +
  //   3])))
  //   //      {
  //   //   swapped1 = true;
  //   // }
  // }
  //
  // if (swapped2) {
  //   max_modules += 2;
  // } else if (swapped1) {
  //   max_modules += 1;
  // }
  //
  // O(max_modules);
  ;
}
