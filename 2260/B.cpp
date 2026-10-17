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

// start: 0855
//   end: 1005

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
  I(x, y, k);

  // y/x + y mod x
  // sum: for i=0..<k: y+k mod x+k
  // isn't this just (y mod x) * k  ??
  //      nonono it's not in the reverse direction its the forward direction
  //
  //    initial offset = y mod x
  //    += k(k-1)/2
  //
  //    3 10   %= 1    /= 3
  //    4 11   %= 3    /= 2
  //
  //    for each increase in k, the MOD DECREASES by (y/x)%i times
  //          plus +1 for the additional employee
  //          for i=1...<k
  //
  //          so more like the MOD goes by += (1-y/x)%i
  //                  on the i-th month
  //
  //
  //  x=3 y=8 k=6
  //
  //   8 3  y%x=2    y/x=2
  //   9 4  y%x=1    y/x=2
  //  10 5  y%x=0    y/x=2
  //  11 6  y%x=5    y/x=1
  //  12 7  y%x=5    y/x=1
  //
  //   so more like the next mod (i-th mod) is prev_mod += (1-y/x)%i
  //                                                        ^
  //                                                b/c of one additional
  //                                                employee
  //    as long y/x>1, decrements will happen WHILE
  //            y/x=1, means the modulo will stay constant
  //
  //    y%x+
  //    y%x+(1-y/x)%(x+i)
  //    y%x+(1-y/x)%(x+1)+(1-(y+1)/(x+1))%(x+2)
  //
  //  y   % x
  // (y+1)%(x+1) += (1- y   / x   )  mod x+1
  // (y+2)%(x+2) += (1-(y+1)/(x+1))  mod x+2
  // (y+3)%(x+3)
  //
  //    some mathematical relation missing?
  //
  //        initially y may be very large compared to x,
  //              but as both increases by say sum large number +l
  //              the fraction eventually approaches to 1
  //
  //              for example, 100/10 (wow, 10 projects)
  //                  becomes 100+1_000_000_000/10+1_000_000_000
  //                  => 1_000_000_100 / 1_000_000_010
  //                  => floors to 1
  //                  => sanity check that (y+1)/(x+1) eventually becomes 1
  //
  //  or more simply put
  //    y%x + (y+1)%(x+1) + (y+2)%(x+2) + (y+3)%(x+3) + .... = answer
  //    <=>
  //    y%x +
  //    y%x + (1-(y)/(x))%(x+1) +
  //    y%x + (1-(y)/(x))%(x+1) + (1-(y+1)/(x+1))%(x+2)
  //    y%x + (1-(y)/(x))%(x+1) + (1-(y+1)/(x+1))%(x+2) + (1-(y+2)/(x+2))%(x+3)
  //
  //  10^12 supports linear soln.? nope, sub-linear only
  //
  // ~~~~ mis-read the problem?
  //
  //
  //!!!!!!!! per editorial, it's just brute-force
  //
  // previously observed that when y/x < 2 (i.e., y < 2x) the y mod x just
  // becomes y-x
  //!!!! we just need to find the i-th month where it becomes that
  //!  since y<=10^6, we can linearly iterate up to the constraint 10^6 and just
  //!  do k-last_y * (y-x)
  //!       we want the moment (y+i)/(x+i) < 2
  //(re-deriving)              ==> y+i < 2(x+i)
  //                           ==> y+i < 2x+2i ==> y < 2x+i (all integer)
  //                                          ==> y-2x<i
  //                                          ==> i <= y-2x (for the manual sum)
  //                           or when k is reached (exclusively)

  ll sum = 0;
  II(i, min(k, y - 2 * x + 1)) { sum += (y + i) % (x + i); };
  // y-2x-k+1  (remember, 0@-1@=-1@ +1-> 0@)
  // wait no k is the max, but we just shift the whole thing down
  // nononon should be min(0, y-2x-k+1)
  //      if k reached first,`then y-2x+1 should reflect that??
  //      this is easier
  //
  //      note, x=10 y=1 k=1 case is possible
  //      which could result in min(1, 1-20+1)
  //      where the for loop auto bounds but the following does not
  //      when there are so much employees but so little projects
  k -= max(0LL, min(k, y - 2 * x + 1));
  sum += (y - x) * k;
  // sum += (y - x) * min(k, y - 2 * x - k);
  O(sum);
}
