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
// O.1: when picking k-lengthed odd-sum subseq, 0s are freebies
//      O.1/1: for a k-lengthed subseq to be odd, it just needs odd 1s basically
//
// O.2: if all 0s => no operations are possible (0--same-- or -1--impossible--)
// O.3: whenever performing the operation, it always takes odd amount of 1s
//      s.t. there will always be an additional odd amount of 0s => after 1
//      operation, a single 0 must always appear (unless the array is all 0s)
//
//      ==> if b is all 1s (unless a is all 1s), then -1
//      is this the only case of -1?
//
//      if b is all 0s, since odd+odd=even, we can always make a into all 0s
//      if b has a single 0 and a with a single 1, THEN we can just invert a
//          to have a single 0 and rest of it as 1 (but remember not all 1)
//
// IMPL:
//
// if a==b:
//      O(0)
// elif b is all 1:
//      // assuming a!=b => a must have a 0 => a cannot get rid of the 0
//      O(-1)
// elif whenever the # of a[i]=1,b[i]=0 is odd:
//      // we can just set all a[i]=1 to be flipped
//      // remember, a[i]=0,b[i]=1 are freebies, we can just select any a's with
//                  0 with no reprecussion
//      // AND a[i]=1,b[i]=1 we do not care, leave it as it is
//      O(1)
// elif whenever the # of a[i]=1,b[i]=0 is even:
//      // split it into odd+odd
//      // remember, a[i]=0 are freebies (regardelss of b[i])
//
//      O(2)
//
// that's all???
//
// how do we know that's all???
//
// 0 is only possible whenever a==b
// -1 is only possible whenever b is all 1 (and a is not, taken from prior false
// condition, since any 0s ruins the possibility of making a as all 1)
//      for the op to work it needs odd-sum => there will always be odd 0s
//      produced post-op
//
// i think so then??
//
//
// per soln., there's a special case of when
//      all a's are 0s but since we already checked for a==b => a's are all 0s
//      AND b's have 1s => no-op can be done to make 0s to 1s
//          (despite 0s being freebie, it needs a requirement of at least 1
//          present or a single case to avoid where a is ALL 0s)
//      => -1
//
//
// ~~~~
//  SPECIAL CASE: b is all 1 is only impos
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
  IVLL(a, n);
  IVLL(b, n);

  bool a_is_b = true;
  bool a_is_all_0 = true; // a cannot increase a single 1 at all
  bool b_is_all_1 = true; // a cannot increase to all 1s
  ll num_of_a1_b0 = 0;
  II(i, n) {
    if (a[i] != b[i]) {
      a_is_b = false;
    }
    if (a[i] == 1) {
      a_is_all_0 = false;
    }
    if (b[i] == 0) {
      b_is_all_1 = false;
    }
    if (a[i] == 1 && b[i] == 0) {
      num_of_a1_b0++;
    }
  }

  if (a_is_b) {
    O(0);
  } else if (b_is_all_1 || a_is_all_0) {
    O(-1);
  } else if (num_of_a1_b0 % 2 == 1) {
    O(1);
  } else { // %2==0
    O(2);
  }

  ;
}
