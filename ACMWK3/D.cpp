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
#define OHYES std::cout << "YES" << std::endl;
#define OHNO std::cout << "NO" << std::endl;

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
  IS(s1);
  I(pos);
  list<char> l(s1.begin(), s1.end());
  // abcd
  // abd <-- smaller (last increasing)
  // acd
  //
  // abcd
  // bcd <-- smaller
  //
  // dcba
  // cba <-- smaller (first decreasing)
  //
  //
  // first decreasing; if not remove the last one

  ll j = 0;
  auto it = l.begin();
  while (pos > l.size() && l.size() > 1) {
    bool removed = false;
    pos -= l.size();

    // DBGLN(pos);

    while (it != l.end() && next(it) != l.end()) {
      if (*it > *next(it)) {
        removed = true;
        it = l.erase(it);
        if (it != l.begin()) {
          it = prev(it);
        }
        break;
      }
      it = next(it);
    }

    // II(i, s1.size() - 1)
    // for (ll i = j; i < s1.size() - 1; i++) {
    //   if (s1[i] > s1[i + 1]) {
    //     // remove i (the first decreasing)
    //     // s1.erase(s1.begin() + i);
    //     s1.erase(i, 1);
    //     removed = true;
    //     j = max(0LL, i - 1); // got to happen before the first decrease
    //     break;
    //   }
    // }
    // remove the last one
    if (!removed) {

      j = l.size() - 1;
      l.pop_back();
      // it = prev(it); // to keep the iterateor right before the end
      it = l.end();
    }
  }
  // breaks whenever pos < latest s1.size()

  // DBGLN(s1.size(), pos, s1[pos - 1]);
  // O(s1[pos - 1]);

  cout << *next(l.begin(), pos - 1);
  // cout << s1.substr(pos - 1, pos);
  // cout << l[pos - 1];
}
