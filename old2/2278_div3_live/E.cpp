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
// P.1: if 2 adj negatives --> 2 adj positives!
//      P.1/2: if 2 adj positives --> 2 adj negatives (bad bad UNoptimal)
// P.2: single negatives stay at the same position
//      (def. single negatives are surrounded by positives both-sided)
//      P.2/1: sign is invariant to the underlying value, we can swap out a
//      neighboring value that is smaller (+) so when negated it becomes smaller
// P.3: if there's an odd-sized (-) group
//      leave the smallest (-) as (-) because O=E+O=O+E=E+O+E
//      except when the odd-th (-) is one before both sides of the ends
// ~~P.4: swaps (like the bubble sort) ensures any elements can reach anywhere
// ~~     (i.e., any order is possible)
// ~~     P.4/1: reduce odd-lengthed (-) groups into single negatives
// ~~     P.4/2: by P.4, place all the smallest values into these and negate
// them
//
//      P.4 only works when we have alternating negatives and positives,
//          or else it will replace 2 positives with 2 new negatives
//
// ~~~~ P.2: separated odd amount of negatives? -->
//
//
// IMPL:
//  1.
//
// === STUCK: if we have odd-lengthed -1s, which side to take? what about middle
// -1s? ===
//  === SIMPLER OBSERVATION? ===
//
//
// per chatgpt:
//
// a_i = -a_{i+1}
// a_{i+1} = -a_i
//
// s_i*a_i = s_{i+1}*a_{i+1}
// s_{i+1}*a_{i+1} = s_{i}*a_{i}
//
// by the invertibility of signs, we can either set (s_i,s_{i+1}) = (1, -1)
//                                              OR  (s_i,s_{i+1}) = (-1, 1)
//
// NOTICE, this confirms an intuitive observation where either (-1)^(i-1) or
// (-1)^(i) works
//
// WITHOUT the intuitive observation where alternating signs == arbitrary
// swapping,
//  if we JUST LOOK at the strict mathematical transformation observation of a_i
//  and the alternating signs of s_i (containing only {-1, +1}),
//      the operation in identity-space
//          a_i := -a_{i+1}
//          a_{i+1} := -a_i
//
//      can be transformed into b_i = s_i*a_i
//          b_i := b_{i+1}
//          b_{i+1} := b_i
//
//      AGAIN, WITHOUT THINKING INTUITIVELY, just thinking in textual math/logic
//          one can see in the transformed-space, the operation is just swapping
//
//      then we just invert the transformation to get the original a_i again,
//      optimally
//
// CONCLUSION
//      one must quickly iterate millions of ways to breakdown the problem (more
//      realistically like hundreds) where one or a few ways would yield some
//      fruit (i.e., succesful)
//          if we go back to the start with a fresh eye, we must iterate all
//          possible ways....
//
//        - intuitive observation (usually Div2 A/B)
//          - invariances
//        - mathematical/logical reasoning textually/written-down (here)
//          - sums (e.g., commutativity, associativity)
//          - or like above (this question)
//          - IMPORTANTLY, abandon all intuitive/visual understanding on them
//        - techniques
//          - excluding greedy b/c of its ad-hoc nature
//          - binary search on answer? (monotonicity in answer-space)
//          - recursion <=> DP? memoization? repeated pass?
//          - DP with index being the answer?
//          - windowing/two-pointers?
//          - graph reduction?
//        - bitwise operations
//          - properties of XOR, parities (%2)
//          - AND/OR (any/all)
//        - BRUTE FORCE!!! (or implementation-heavy)
//          - pure utter ugly in-elegance
//        - floats/doubles
//          - optimization methods like gradients (or constrained gradients)
//          - probabilities
//        - combinatorics
//          - properties/intuition of LCM/GCD
//          - sieve
//          - bezout ident.
//        - combinations of all the aformentioned stuff (e.g., exponential
//        combinations of all of the above)
//
//
//

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n);
  IV(a, n);

  // ST(a);

  II(i, n) { a[i] *= i % 2 == 0 ? 1 : -1; }

  ST(a); // take n/2 lowest and negate them and take n/2+n%2 highest and ident.
         // them
  ll sum = 0;

  II(i, n) {
    if (i < n / 2) {
      sum -= a[i];
    } else {
      sum += a[i];
    }
  }

  O(sum);
  ;
}
