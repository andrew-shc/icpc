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
// notice: if there's a value that is inter-linked / overlapping
//          either first requires some special op or one of the pairs of
//          similiar value will need to be removed for the other to be merged
//
// start with the lowest numbers
//      if there's a pair of it but separated...
//          since removal of any numbers that are in between that are strictly
//          larger is detrimental, it is locally-optimal (greedy) to skip it
//        i.e., incrementally
//
// (probably read in doubles)
//
// O.1: if no duplicates => simple max of the array
// O.2: if we can join two largest max together, do that
//      because if we join lesser two max together, it will either just equal to
//      the max or less than THE max (which in other words just leave the array
//      as it is with an already largest max)
//
//      O.2/1: it is NOT GREEDY to REMOVE THE LARGEST MAX
//      O.2/2: check for other max's INDEPENDENTLY (e.g., imagine the array
//          partitioned by the largest max)
//
//          (subarray recursion?)
//
//      O.2/3: we want k additional largest max if possible
//             or 2k additional 2nd-largest max if possible
//
//      O.2/4: suppose 2^m is THE MAX
//              to increase the max we would want...
//
//              1,3,7,..,2^l-1 additional 2^m
//              OR
//              2,6,10,..,2^l+2 additional 2^(m-1)
//
//              2^l amount of additional 2^m 's
//              or some combinations of it...
//              '
//
//
// NOTE: we continue playing UNTIL a single number remains (always a single
//       number at the end)
//
// greedily merge?
//  it is never optimal to keep lesser elements that cannot be merged without
//  removing a larger element(s) (in the case just use the larger elements)
//
//  recursion????
//
//  Python?
//
//  partition
//
//
//
// working in log-space
//
// it becomes 1...100
//
// when adding adjacent duplicate numbers it's just incrementing them in
// logspace also
//
//
// 1 1 => 2
//
// 3 3 => 4
//
//
// this is not codeforce
//
//
// it could easily be some easy DP
//
//
// DP of hashmaps
//
// or just a running hashmaps
//
// running frequency maps

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n);
  // IV(a, n);
  vll a;
  II(i, n) {
    ld ai;
    cin >> ai;
    a.PB((ll)log2(ai));
  }

  function<ll(vll)> recur = [](vll part) {
    if (part.size() <= 1) {
      return part[0];
    }
    max_element(part.begin(), part.end());
    II(i, part.size()) {}
    return 0LL;
  };

  ;
}
