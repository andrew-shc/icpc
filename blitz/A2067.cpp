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

// start: 1848
//   end: 1913

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

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  // x+1=y (possible obviously)
  // x-10=y
  //
  // 1
  // ...
  // 9    9
  // 10   1
  // 11   2
  // ...
  // 19  10
  // 20   2 (8)
  // ...
  // 29  11
  // 30   3 (8)
  // ...
  // 99  18
  // 100  1 (17)
  //
  // 109  10
  // 110   2 (8)
  //
  //
  // if x+1==y
  //      xxxx1..xxxx8 -> xxxx2..xxxx9
  //   if x+2==y
  //        10 ->
  //
  // does any config work??
  //
  //
  // carry carry
  //
  // (x+1)0<-9
  //
  // 123449 -> 123450 (1+2+3+4+9 -> 1+2+3+4+5+0)
  //                          +8 (or rather +9 -> the rest +1)
  //                                                          ^
  //                                                          CARRY!
  //
  //                                                          when going from 9
  //                                                          to 0, there's
  //                                                          always a carry
  //                                                          that can either +1
  //                                                          or +1 and reset 9s
  //                                                          to 0
  //
  //                                                          hence, y=x+1
  //                                                          definitely works
  //
  //                                                          y=x+9x(numbers of
  //                                                          9 -> 0) and the +1
  //                                                          CARRY
  // or
  // 1000<-999 (27 -> 1)
  // 10000<-9999 ( 36 ->1)
  //
  //
  // x=1 y=11 => NO
  //
  //
  //
  I(x, y);
  if (y == x + 1) {
    OHYES;
  } else if ((y - x - 1) % 9 == 0 && x >= 9 && y - x - 1 < 0) {
    // checks if the difference in digits minus the CARRY bit results in the
    // amount about discrete amount of digit 9s reset to 0s
    //
    // also x >= 9
    //
    // 9 -> 11?
    // 9 -> 2
    // obviously no
    // n=9 -> n+1=10 must work
    // x=9 -> y=1
    // 1-9-1 = -9%9==0
    //
    // y-x-1 msut be negative if it were to be assuemd as resetting all the 9s
    // to 0s +1 (net result, negative delta)
    OHYES;
  } else {
    OHNO;
  };
}
