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
// just set it to all 1s??
//
//
// 1 1 1 1 1 1
//
//
// 2 2 2 2 2 2
//
// 1 2 3 1 2 3
//
// 1 1 2 1 1 1 (even => -1 longest plaindrome)
// ~~~ * *   * * *
//
// 1 1 2 1 1 (+1)
// 1 1 1 1 1 ~~(~~~~)  this is fine correct (5x*) actually 5!
//
//
// 1 1 1 2 1 1 1 (odd => same.. :( ??? )
//
// wait by factorial all 1s should work no?
//
//
// 1 1 1 1 1 1 (longest palindrome is 6)
//              but 6! possible subsequence?
//
//
// SUBSEQ, by definition, IS STILL ORDERED
//  => we still need one deletion
//
// 1 1 2 1 1 1
//
// 1 1 2 1 1  => f(a)=5
//
// 1 1 2 1 1
// 1 1   1 1 1
//
// ~~
//   1   1 1 1
// 1     1 1 1
// 1 1     1 1
// 1 1   1   1
// 1 1   1 1
// 1 1 2 1 1
// ~~
//
// 1 1 1 2 1 1 1
//~~~~~~~~~~~ ^^
//
//
// 1 2 1 2 1 2
//~~~~~~~~~~
//
// maybe instead of maximizing g(a), minimize f(a)?
//
//
// 1 2 3 4 5 6  f(a)=1
// 1
//   2
//     3
//       4
//         5
//           6  g(a)=n (we want g(a)>n)
//
// 1 1 1 2 2 2  (intuitive observation? 3!>3 and 3!>3)
//
// 1 1 2 1 2 2
//
// 1   2 1
//   1 2 1
//     2 1 2
//     2 1   2
// 1 1 1
//     2   2 2
//
//
//
// 1 2 2 1 1 2  but is f(a)=3???
//
// 1   2 1
// 1   2   1
// 1 2   1
// 1 2     1
//   2   1   2
//     2 1   2
//   2     1 2
//     2   1 2
//              g(a)>n
//
// f(a)=4 BECAUSE 2 1 1 2
//
// 1 2 1 1 1 1
// 1 2 1
// 1 2   1
// 1 2     1
// 1 2       1
//     1 1 1
//       1 1 1
//     1   1 1
//     1 1   1
//              g(a)>n
//           IS f(a)=3???
// nope,
//     1 1 1 1
//
// 1 2 1 1 2 1
//
// 1 2 1 2 1
// but
//
// 1 2 1 1 3 1
//
// 1 2 1 3 1 no longer valid
// but
//
// 1 2 1
// 1 2   1
// 1   1 1
//     1 1   1
//     1   3 1
//       1 3 1
//
// but
// 1    1 1   1
//
//
// 1 2 4 1 3 1
// 1     1   1
// 1 2   1
// 1   4 1
//       1 3 1
//
//
// 1 2 3 4 2 1 ??
// 1 2     2 1 (nope)
//
// 1 2 3 4 5 1
// 1 2       1
// 1   3     1
// 1     4   1
// 1       5 1
//
//
// 1 1 2 3 4 1
// 1 1       1
// 1   2     1
// 1     3   1
// 1       4 1
//   1 2     1
//   1   3   1
//   1     4 1  g(a)>n
//              f(a)=3??
// base on the observation of TC.1, seems like this will be f(a)=3!!
//
// we only have 3 duplicates max (resulting in 2x1,?,1 combinations)
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
  I(n); // n>=6

  // vll a(1, n);
  // vll a(n, 1);
  // vll a = {1, 1};
  vll a = {1};
  II(i, n - 2) { a.PB(i + 1); }
  a.PB(1);

  OIT(a);
  ;
}
