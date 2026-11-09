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

#define INC(i, n) for (ll i = 0; i < n; i++)

#define DEC(i, n) for (ll i = n; i >= 0; i--)

#define OUT_ITER(a)                                                            \
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
#define OUT(...) cout_vars(__VA_ARGS__)

#define READ_S(s)                                                              \
  string s;                                                                    \
  cin >> s;

#define READ_VLL(a, n)                                                         \
  vll a;                                                                       \
  for (ll i = 0; i < n; i++) {                                                 \
    ll ai;                                                                     \
    std::cin >> ai;                                                            \
    a.push_back(ai);                                                           \
  }

template <typename... Args> void read_vars(Args &...args) {
  (std::cin >> ... >> args);
}
#define READ(...)                                                              \
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

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// END MACROS
///////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

void solve(ll T);

int main() {
  /////////////////////////////////////////////////////////////////////
  //// comment out the sync when working with interactive problems ////
  /////////////////////////////////////////////////////////////////////
  ios_base::sync_with_stdio(false);
  /////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// START ACTUAL CODE
///////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

// start: 14:24
//   end: 14:35 (11min)

// basically, either Shaunuk always win before special move OR Shaunuk always
// win after special move.

void solve([[maybe_unused]] ll T) {
  int n, k;
  cin >> n >> k;

  ll five = 0;
  INC(i, n) {
    ll ai;
    cin >> ai;
    five += ai;
  }

  // Shaunuk going first, Shaunuk wins if all array sums to 1 => Shaunuk wins if
  // all array sums to odd => Shaunuk wins if either the array before spceial
  // move sums to odd or after the special move sums to odd
  // but, on the special move, the other starts with the fresh all k's, so it
  // must be even

  if ((five % 2 == 1) || ((n * k) % 2 == 0)) {
    OUT("YES");
    return;
  }
  OUT("NO");
}
