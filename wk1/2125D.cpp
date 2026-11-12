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
  // cin >> T;

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
// ~~~~P.1: probability that each cell is covered by ONE segments EXACTLY is
//
//       prod_{for each cells} of the following:
//          sum_{all possible segments at current cell}
//              (+ probability)(1 - probability of all other intersecting
//              segments)
//
//!!!!!!!!!!!!!!!!!
//
//!! basic pre-req: by modular arithmetic, x/y <=> x*y^-1 (mod) === x*y^(M-2)
//!(mod)
//      the mod-div only works when the divisor is coprime
//      and because the MOD M we're given is prime, most mod-div works except 0
//      might need some special consideration
//
//! => basically, we want x*y^(M-2)
//!    (might want to use binpow)
//! and ensure x,y is coprime (reduced form)
//
//
//=== STUCK: each cells cannot independently calculate the probabilities of the
// existence of the segment (yes the probability is just the segment and no need
// to divide by the area and all that stuff but do calculate the probability of
// one suggests the existence of the segment on other cells also NOT
// INDEPENDENT between cells...)
//
//
//
//
//!!! per editorial
//
// just do intervals on end (why end? b/c its easier since we're moving from
// 0->n)
//      however, if we're doing something like suffix (going backwards /
//      reverse) then do intervals on start makes sense (and look backwards)
//
// and just do it???

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n, m);
  vector<tuple<ll, ll, ll, ll>> segments;
  II(i, n) {
    I(l, r, p, q);
    // segments.PB({l, r, p, q});
    segments.PB({r, l, p, q});
    // makes it easier to sort by ends
  }
  // ST(segments);

  auto binpow = [](ll b, ll p) {
    ll r = 1;
    ll x = b;
    while (p) {
      if (p & 1) {
        r = (r * x) % MOD;
      }
      x = (x * x) % MOD;
      p >>= 1;
    }
    return r;
  };

  vll dp(m + 1, 0);
  vector<vector<tuple<ll, ll, ll, ll>>> segs_pos(
      m, vector<tuple<ll, ll, ll, ll>>{});

  // dp[0] represents the initial probability where NO segments exists
  // dp[0] = PROD OF (1-p/q) = PROD OF (q-p)/q
  //                                   (q-p)*q^(M-2)  (mod M)
  dp[0] = 1;
  for (auto &[r, l, p, q] : segments) {
    dp[0] = (dp[0] * ((q - p) * binpow(q, MOD - 2) % MOD)) % MOD;
    segs_pos[r - 1].PB({r, l, p, q});
  }
  // O(nlogn)

  II(i, m) {
    for (auto &[r, l, p, q] : segs_pos[i]) {
      // dp[l-1] b/c we're accessing intervals before the selected segments and
      // 1@->1@
      //
      // from dp[l-1] we multiply it by the EXISTENCE of segment p/q
      //             and cancel out (remove) the tern that assumes NON-EXISTENCE
      //             of segment (q-p)/q
      //             which can easily be removed from dp[l-1] since all dp's
      //             carry out (or start from) dp[0] that already includes all
      //             the pre-computed products
      //
      //  p/q * (q-p)/q = (pq-pp)/q^2 = p(q-p)/q^2
      //                            === p(q-p)*q^(M-3)    (mod M)
      //
      //
      // CANCEL OUT MEANS DIVIDE NOT MULTIPLY LIKE
      //
      // p/q * 1/((q-p)/q) = p/q*q/(q-p) = p/(q-p)
      //                                 === p*(q-p)^(M-2)   (mod M)

      // dp[i + 1] =
      //     (dp[i + 1] +
      //      (dp[l - 1] * (p * ((q - p) * binpow(q, MOD - 3)) % MOD) % MOD) %
      //          MOD) %
      //     MOD;

      dp[i + 1] =
          (dp[i + 1] + dp[l - 1] * ((p * binpow(q - p, MOD - 2)) % MOD) % MOD) %
          MOD;
    }

    // if no segments end at dp[i+1=r], then it would just be 0 (for impossible)
  }
  DBG_ITER(dp);

  // ll x, y;

  // at dp[m-1], it will include the sum of all the valid probabilities (across
  // different segments ending at the last cell) that has each cell covered by
  // exactly one segment

  O(dp[m]);
  ;
}
