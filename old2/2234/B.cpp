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

// start: 0953
//   end: 1020

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
// H.1: is there an O(1) or even a way to search for palindromes?
//          xyzyx
//          x*10000+y*1000+z*100+y*10+x <= n ? (no elegant solutions??)
//          x*(10000+1)+y*(1000+10)+z*100
//          x*(10001)+y*(1010)+z*100 <= n (5 digit)
//          x*(1001)+y*(0110)         <= n (4 digit)
//          ...
//                   vv
//          m1*00011000+
//          m2*00100100+
//          m3*01000010+
//          m4*10000001+
//          12z        =n (4*2 digit)
//
//     ~~~~ O.2<-H.1: if n has >=10_000 => always possible
//     O.2<-H.1: let b=n\12 and a=n%12 where it satisfies except for cases
//     where
//               n%12==10
//
//               xy
//               vv
//          m1*0110+
//          m2*1001+
//          12z    =n
//
//          we can always assign  z=n/12 (or b=n\12)
//
//          then for n%12:
//              0
//              1
//              2
//              3
//              4
//              5
//              6
//              7
//              8
//              9
//             10 <-- the only bad case
//             11
//
//             22 (10+12) <-- fixes it
//
//          O.2/1: IF n%12==10 AND n/12>0 ==> b=n\12-12,a=10+12=22
//          O.2/2: 10 IS THE ONLY CASE THAT DOES NOT WORK
//
//
// O.1: IF n%12==0 OR n==palindrome => let a OR b = n (accordingly) and the
//          opposing summand to 0

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n);
  if (n == 10) {
    O(-1);
  } else if (n % 12 == 10) {
    O(n % 12 + 12, 12 * (n / 12 - 1));
  } else {
    O(n % 12, 12 * (n / 12));
  };
}
