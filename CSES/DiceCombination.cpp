#include <bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef std::vector<ll> vll;
typedef std::deque<ll> dll;

const long long NEG = (long long)-4e18;

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

void solve();

int main() {
  /////////////////////////////////////////////////////////////////////
  //// comment out the sync when working with interactive problems ////
  /////////////////////////////////////////////////////////////////////
  ios_base::sync_with_stdio(false);
  /////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////

  cin.tie(NULL);
  cout.tie(NULL);

  solve();

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

// start:
//   end:

const ll MOD = 1000000007;

// IN DP
// n = 3
//
// 3
// 2 + 1
// 1 + 2
// 1 + 1 + 1
//
// n = 4
// 4
// 3 1
// 2 2
// 2 1 1
// 1 3
// 1 2 1
// 1 1 2
// 1 1 1 1
//
//
// dp[i] = a[i] + dp[i-1]
// hard-code????
//
// instead of DP over the arrays of possible combination (that is quite stupid)
//       per chatgpt, we DP over the sums (e.g., DP over answer)
//
//
// dp[0] = 0
// dp[1] = 1
// dp[2] = 1 + dp[1]    // 2 or 1 1  (later, 2 1 or 1 2)
// dp[3] = 1 + dp[2] + dp[1]   // 3 or 2 1 and 1 2 and 1 1 1
//
//
// per chatgpt, think of it reversed
//      dp[x] = dp[x-1] + dp[x-2] + dp[x-3] + ... // if the last role is 1,2,3,4
// and a base of dp[1] to dp[6]! (thats the hard code that was referred to
// before)
//      instead of manually computing the bases we can just iterate it with
//      bounds set to 0 (per chatgpt)

void solve() {
  READ(n);

  vll dp;

  dp.push_back(1);

  INC(i, n + 1) { // inclusive up to n itself
    if (i == 0)
      continue;

    dp.push_back(0);
    INC(d, 6) { // 0 to 5  exclusive
      if (i - (d + 1) >= 0) {
        dp.back() = (dp.back() + dp[i - (d + 1)]) % MOD;
      }
    }
  }

  OUT(dp.back() % MOD);
}
