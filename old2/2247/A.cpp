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

// start: 1836
//   end: 1921xx

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
// -1 -1 1 1 -1 -1 1 1 -1 -1
//
// 1. you can always make all of them -1 or 1?
//
// either make -1 -1 into 1 1
// or -1 1 into 1 -1 (move the -1 to the right)
//
// however, if it is at 1 1 1 1 1 -1
// we can't do anything about it
//
// in fact, if there are odd amount of -1s => bad
//
// or, odd amount of 1s
//
//
// KEY OBSERVATION:
//      if its 1 -1 or -1 1 => does not change the sum
//      if its 1 1 or -1 -1 => changes the sum +/- 2 => if the sum is even
//      doable, if sum is not => NO
//
//
//
//      1 1 -1 1 1 1 -1 1 1 1 1 1 <-- can move the -1 down to next to each other
//      1 1 1 1 1 -1 -1 1 1 1 1 1 <-- this now can be wait yea its already
//      s%2==0
//
//
//      what coun
//
//
//      1 -1 -1 -1 this magically doesnt????
//      1 -1 -1 -1 -1 -1 this works
//
//
//      1 -3 = -2  just do a +2?
//
//      so
//
//      1 1 1 -1?????
//
//      BUT
//
//      1 -5 = -4
//      3 -3 = 0
//
//      oh its +/-4

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n);
  IVLL(a, n);

  if (n == 2 && a[0] + a[1] != 0) {
    O("NO");
    return;
  }

  ll neg = 0;
  ll pos = 0;
  ll s = 0;
  II(i, n) {
    s += a[i];
    // if (a[i] == -1) {
    //   neg++;
    // } else {
    //   pos++;
    // }
  }

  if (s % 4 == 0) {
    O("YES");
  } else {
    O("NO");
  }
  // if (neg % 2 == 1 || pos % 2 == 1) {
  //   O("NO");
  // } else {
  //   O("YES");
  // }

  // if ((n % 2 == 0 && n > 2) || (n == 2 && a[0] + a[1] == 0)) {
  //   O("YES");
  // } else {
  //   O("NO");
  // }
  // if (n % 2 == 1 || n <= 2) {
  //   O("NO");
  // } else {
  //   O("YES");
  // }
}
