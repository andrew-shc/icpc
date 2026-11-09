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
// find the max possible mass of this single final core
//
// P.1:
//      1 1 1 1 1 1 2 1 1 1 1 1
//      1 1 1 1 1 2   2 1 1 1 1
//      1 1 1 1 2     3 1 1 1 1
//      1 1 1 1 3       3 1 1 1
//
//      if all 1s => -1
//
//      ...
//      7 6
//       5+1
//      12 \->
//
//
//      2 1 1 1 1 1 1 1 1 1 1 1
//
//      2 1 1 1 1 1 1 1 1 1 1 2
//
//      1 2 1 1 1 1 1 1 1 1 1 1
//      2   2 1 1 1 1 1 1 1 1 1
//      3     2 1 1 1 1 1 1 1 1
//
//      IF THE ONLY non-ones are at the end...
//
//          pick the largest endpoint non-ones
//
//          2 is the smallest non-ones
//
//          however, when we split it, it will always spit out a one and getting
//          a one so the sum would be just the two ends-points MINUS ONE
//          (generalizes to cases where we only have ONE non-one endpoints)
//
//
//      smalelst n==2
//
//      all_1s_inner just becomes true
//
//      but there's no inner elements so it generalizes to when there's no inner
//      elements so this is fine

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n);
  IV(a, n);

  ll sums = 0;
  bool all_1s = true;
  bool all_1s_inner = true;
  II(i, n) {
    // if (a[i] != -1) {
    // if (a[i] == 1) {
    if (a[i] != 1) {
      all_1s = false;
    }
    if (0 < i && i < n - 1) {
      if (a[i] != 1) {
        all_1s_inner = false;
      }
    }
    sums += a[i];
  }
  if (all_1s) {
    O(-1);
    return;
  }
  if (all_1s_inner) {
    O(a[0] + a[n - 1] - 1);
    return;
  }

  // find the single max possible mass of the final core

  // i mean clearly there's this conservation of mass going on
  // so just sum of a_i????
  //
  // actually sum[a_i]-1
  //
  // where we optimally do the endpoint operations LAST AND SINGLE TIME (2 cores
  // to 1 cores)
  // and remove just the 1 to the environment optimally

  O(sums - 1);
  ;
}
