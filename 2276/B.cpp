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
//

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  IS(s);
  // count the number of groups of 3 1's and 3 0's?
  // 1111111
  //  ^ ^ ^
  //  ^ ^
  //  ^
  //
  //  or like given a group-length of n, we can get (n-1)/2
  //  remember it's unordered, we only care about the "topology" or the holes
  //  so it's literally just (n-1)/2 # of ways
  //
  //
  // 1111111
  // 1011111 <
  // 1110111 <
  // 1111101 < same
  //
  //  v  v
  // 000111
  // 010111 < different
  // 000101 < so multiplied across 1/0-groups?
  // 010101
  //
  // also consider the boundaries
  // which is fine we just count the 1/0's end to end but only assume we can
  // operate
  // actually the boundary case makes the answer easier
  //
  // 10001110001
  //  010111010 = 0101010
  //  000101000 = 01010
  //
  //  // i think a better way is to count the maximum number of alternatings and
  //  just go off of that b/c the following are just same
  //  010111000
  //  000101000
  //  000111010
  //
  //  consider the special cases
  //
  //  01010101
  //  01110101 < like joining them
  //  01000101 < same as above
  //
  //  01010111 < well joining them just adds +1 possibilities (regardless of
  //  position)
  //
  //  CHANGE AT MOST ONE CHARACTER
  //
  //  possibilities = {1,2,3}????
  //
  //  what about adjaceny
  //
  //  0000111010000
  //  independently checked

  // ll max_holes_additional = 0;
  // ll possibilities = 1;
  ll p_joining = 0;   // -1
  ll p_splitting = 0; // +1
  ll cnt = 0;
  II(i, s.size() - 1) {
    if (s[i] != s[i + 1]) {
      cnt++;
      if (cnt >= 3) {
        p_splitting = 1;
        break;
      }
      cnt = 0;
    } else {
      cnt++;
    }
  }
  cnt++; // if the last one different cnt is just 1
  if (cnt >= 3) {
    p_splitting = 1;
  }
  II(i, s.size() - 2) {
    if ((s[i] != s[i + 1]) && (s[i + 1] != s[i + 2])) {
      p_joining = 1;
      break;
    }
  }
  DBGLN(p_joining, p_splitting);
  O(1 + p_joining + p_splitting);
}
