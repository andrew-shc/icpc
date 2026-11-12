#include <algorithm>
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
// P.1: if two cells have x-dist OR y-dist < (or <= ??) k => one will be
// obtained (optimally) but the would have to be destroyed
//          (assuming we can't just throw the dynamite such that it only takes
//          out one of each on the boundary at different locations)
// P.2: on the kth square-radius is the boundary
//          k-1th (and smaller) < kth square-radius are considred STRICTLY
//          inside the square
//
// P.3:
//      IF k==1: we can always take all the gold (=>sum of g's)
//      IF k > n-1 && k > m-1: everything will be destroyed (=>0)
//
// P.4: IF the initial empty square (x,y) has no gold bars STRICTLY within the
//      k-square => sum of all golds
//
//      P.4/1: of all empty sqaures '.', pick the one with the smallest amount
//      of golds STRICTLY within the k-square???? (to prevent destruction)
//
// KEY OBSERVATION (??): after picking an initial empty square, we can ALWAYS
//      OPTIMALLY (GREEDILY) go step-by-step to pick up all the golds on the
//      boundary cases
//
// ~~~~ IF 2k-1>=min(n,m): everything will be destroyed
//
// 2D DP??
//
//

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n, m, k);
  vector<string> mine(n, "");
  II(i, n) {
    IS(mine_i);
    mine[i] = mine_i;
  }

  vector<vll> dp(n + 1, vll(m + 1, 0));
  II(i, n) {
    II(j, m) {
      // dp[i + 1][j + 1] = dp[i + 1][j] + dp[i][j + 1] - 2 * dp[i][j] +
      //                    (mine[i][j] == 'g' ? 1 : 0);
      dp[i + 1][j + 1] =
          dp[i + 1][j] + dp[i][j + 1] - dp[i][j] + (mine[i][j] == 'g' ? 1 : 0);
    }
  }

  ll invariant_max = dp[n][m];
  ll max_gold = 0;
  II(i, n) {
    II(j, m) {
      if (mine[i][j] == '.') {
        // DBGLN(i, j);
        // ll x = clamp(i + 1 - k, 0LL, n);
        // ll y = clamp(j + 1 - k, 0LL, n);
        // ll X = clamp(i + 1 + k, 0LL, n);
        // ll Y = clamp(j + 1 + k, 0LL, n);
        // ll xi = clamp(i + 1 - k + 1, 0LL, n);
        // ll yi = clamp(j + 1 - k + 1, 0LL, n);
        // ll Xi = clamp(i + 1 + k - 1, 0LL, n);
        // ll Yi = clamp(j + 1 + k - 1, 0LL, n);
        // ll xi = clamp(i + 1 - k + 1, 0LL, n);
        // ll yi = clamp(j + 1 - k + 1, 0LL, m);
        // ll Xi = clamp(i + 1 + k - 1, 0LL, n);
        // ll Yi = clamp(j + 1 + k - 1, 0LL, m);
        // b/c we are being inclusive w.r.t. the square that we're computing the
        // sum of, we need to make the EXCLUSION exclusive (the subtraction)
        // hence, the following (-1s on the small xi,yi)
        ll xi = clamp(i + 1 - k + 1 - 1, 0LL, n);
        ll yi = clamp(j + 1 - k + 1 - 1, 0LL, m);
        ll Xi = clamp(i + 1 + k - 1, 0LL, n);
        ll Yi = clamp(j + 1 + k - 1, 0LL, m);

        // ll outer_gold = dp[X][Y] - dp[x][Y] - dp[X][y] + dp[x][y];
        ll inner_gold = dp[Xi][Yi] - dp[xi][Yi] - dp[Xi][yi] + dp[xi][yi];
        // max_gold = max(max_gold, invariant_max - (outer_gold - inner_gold));
        max_gold = max(max_gold, invariant_max - inner_gold);

        DBGLN(xi, yi, Xi, Yi);
        DBGLN(i, j, invariant_max, inner_gold);
      }
    }
  }

  O(max_gold);
  ;
}
