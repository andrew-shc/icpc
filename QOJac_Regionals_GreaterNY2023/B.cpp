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
  vpll a;                                                                      \
  for (ll i = 0; i < n; i++) {                                                 \
    ll ai, bi;                                                                 \
    std::cin >> ai >> bi;                                                      \
    a.push_back({ai, bi});                                                     \
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
//

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n);
  IV(a, n);

  // vll prefix_min(n, 0);
  // vll suffix_max(n, 0);
  //
  // prefix_min[0] = a[0];
  // II(i, n - 1) { prefix_min[i + 1] = min(a[i + 1], prefix_min[i]); }
  // suffix_max[n - 1] = a[n - 1];
  // DD(i, n - 1) { suffix_max[i] = max(a[i], suffix_max[i + 1]); }

  vll prefix_max(n, 0);
  vll suffix_min(n, 0);

  prefix_max[0] = a[0];
  II(i, n - 1) { prefix_max[i + 1] = max(a[i + 1], prefix_max[i]); }
  suffix_min[n - 1] = a[n - 1];
  DD(i, n - 1) { suffix_min[i] = min(a[i], suffix_min[i + 1]); }

  vll pivot_candidates;

  if (n > 1) {

    // do we really need the <=?
    //
    // consider such case
    //
    //  4 5 10 9 23
    //
    //  4 5      23 (pivot values)

    II(i, n) {
      // SPLIT THE IF STATEMENTS (or else the boundary case will land in the
      // in-between case which can cause OOB)
      if (i == 0) {
        if (a[i] < suffix_min[i + 1]) {
          pivot_candidates.PB(a[i]);
        }
      } else if (i == n - 1) {
        if (prefix_max[i - 1] < a[i]) {
          pivot_candidates.PB(a[i]);
        }
      } else if (prefix_max[i - 1] < a[i] && a[i] < suffix_min[i + 1]) {
        // in between
        pivot_candidates.PB(a[i]);
      }

      // XL<=p
      // XR>p
      // but shouldn't matter by the empty exception and the uniqueness of a

      // if (i == 0 && a[i] < suffix_max[i + 1]) {
      //   pivot_candidates.PB(a[i]);
      // } else if (i == n - 1 && prefix_min[i - 1] < a[i]) {
      //   pivot_candidates.PB(a[i]);
      // } else if (prefix_min[i - 1] < a[i] && a[i] < suffix_max[i + 1]) {
      //   // in between
      //   pivot_candidates.PB(a[i]);
      // }

      // if (pivot_candidates.size() == 100) {
      //   break;
      // }
    }
  } else { // n==1
           // do we assume n==1 is UNpartitioned??/
           //
           // either one of them could be empty.
           //
           // ONE of them (??)
           //
           // the <= must allow this to happen
    pivot_candidates.PB(a[0]);
  }
  pivot_candidates.insert(pivot_candidates.begin(), pivot_candidates.size());
  if (pivot_candidates[0] > 100) {
    pivot_candidates.resize(101);
    // 100 elements + 1 initial element for the size (for output)
  }
  OIT(pivot_candidates);
  ;
}
