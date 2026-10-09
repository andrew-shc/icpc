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

// start: xx 1137 (read this on a previous day
//   end: xx 1206

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
// O.1: we can always select any non-optimal [i] to make it optimal (negate: +
//      to -)
//
//
// H.1: something to do with odd/even length
//      + + + +
//      - - - -
//
//      - + - +
//      + - + -
//      - + - -
//      + - - -
//      - - - -
//
//      + - + - +
//      - + - + -
//      + - + - -
//      - + - - -
//      + - - - -
//      - - - - -
//
//      H.1->1: just find the LAST positive int and output the output 1-index
//          from the LAST and decrement to the FIRST?? (1-index)
//
//
//          CE.1: the ops needed along each index is RELATIVE to the last
//          positive index
//
//                v v v v v
//              + + - + - +
//              - - + - + -
//              + + - + - -
//              - - + - - -
//              + + - - - - <--
//
//                  v v   v
//              + + + - + +
//              - - - + - -
//              + + + - - - <--
//
//
// O.2<-CE.1: instead of one-by-one index, find group-by-group (START-OF) index
//      SINCE when
//      the last group turns + then we do not need to meddle with elements in
//      the group that are already +
//
// O.3: by the reverse order of vector appending & the ops, IMPL-WISE can just
//      append the START-OF index of each group's append-by-append
//

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n);
  IVLL(a, n); // ASSUME NO 0s

  // ll last_positive_ind = -1; // default to [0] or @1 for simplicity-sake
  // (even
  //                            // if all negative actually NONONONO)
  //
  // II(i, n) {
  //   if (a[i] > 0) {
  //     last_positive_ind = i;
  //   }
  // }
  //

  dll ops; // reverse insertion (0th -> 1st op)
           // APPENDING IS IDENTITY INSERTION, PUSH FRONT IS REVERSE INSERTION

  // note: this continues the sign-change-test until the index before the end
  // the end will simply check for if it's + (append it), if not, (don't)
  // whether the last end is different from the end-1 ind is factored by the
  // LOOP comparison already
  //  if same, don't append (AS IS) and let the END-OP deal with it (if it
  //  continues to be + then just append END, if - then NOP for the rest of the
  //  group) if different,
  //      - to + (FIRST-INDEX of - group needs to be appended either way since
  //        it will be negated to + group when the unoptimal END + must be
  //        negated to -)
  //      + to - (FIRST INDEX of + group needs to be appended anyways since its
  //        the FIRST + even when END is optimal -)
  II(i, n - 1) {
    if (a[i] > 0 == a[i + 1] < 0) { // sign-flip
      ops.push_front(i + 1);
    }
  }
  if (a[n - 1] > 0) {
    ops.push_front(n);
  }

  // // II macro handles <0 as NOP
  // II(i, last_positive_ind + 1) { ops.push_back(last_positive_ind - i + 1);
  // }

  O(ops.size());
  OIT(ops);
}
