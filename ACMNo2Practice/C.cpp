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
// when using operation 1
//      the difference seq flips from the later element minus the current
//      elements into current element minus the later element
//
//
// a1 a2 a3 ... a_{n-2} a_{n-1} a_n
//
// a_{n-1}-a_n a_{n-2}-a_{n-1}
//
// when reversed is
//
// a_2-a_1 a_3-a_2
// a_1-a_2 a_2-a_3
//
// and an element is removed (OP#2 reduces one length)
//
//
// O.1: if all the elements are positive => leave it as it is and sum it
//              ^^^
//           we want to reach this point
// O.2: if all the negatives are 1-spaced away, we can always apply (or not)
//          OP#1 to make all elements positive via OP#2
//      ^^^ NO ~~~~
//
// but when there are negatives on some areas.... DP -- exhaustive search?
// greedy?
//
// SUM! got to think in sum
//
// sum all the other elements and sum all EVERY OTHER ELEMENTS
//      part A                          part B
//
//
//  telescoping.....
//
//
//
//  9 7 9 -9 9 -8 7 -8 9
//  9   9    9    7    9
//    7   -9   -8   -8
//
//
// O.3: TELESCOPING SUM we only care about the a1 and an???
//          or -a1 and -an??
//
// can we always maximize the ends?
//
//  so technically
//      -a1      an
//       a1     -an
//
//  once we find the difference it would be
//
//       -(a2-a1)      (an-a{n-1})
//                or
//        (a2-a1)     -(an-a{n-1})
//
//
//       -(a1-a2)      (a{n-1}-an)
//                or
//        (a1-a2)     -(a{n-1}-an)
//
//              if say a3 is the last elements
//
//         a2-a1-(a3-a2)
//
//
// O.4: is every elements will be positive/negative
//
//
//
//
// answer on two choices:
//      reverse on the first time and at the last time??
//
//
// greedy?
//
// at any point, check whether continuing the operation is worth it? or leave it
// as a sum of itself
//
// if either -(a[2..n]-a[1..n-1])
//            (a[2..n]-a[1..n-1])
//        are larger than sum of a[1...n]:
//     then apply the operation
// else:
//      return the sum  // because op#2 always decreases(?)
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
  if (n == 1) {
    O(a[0]);
  } else {
  };
}
