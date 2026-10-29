#include <bits/stdc++.h>
#include <climits>
#include <unordered_map>

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
// score := |b| - # of distinct elements in b
//
//  O.1:
//  NOTICE: score is the same if THE ONLY DISTINCT ELEMENT IS REMOVED
//
// pick [l,r] to remove from a[] s.t. score is still maximized but |b| is
// minimized
//  [l,r] must not be empty
//
// per O.1:
//  by the expression of the score, we actually DO NOT WANT TO REMOVE DUPLICATE
//  ELEMENTS
//  only remove non-duplicate elements and as contiguous as possible. if not
//  possible, remove a SINGLE SMALLEST duplicate element group
//
// will have to come back to double check
//

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n);
  IVLL(a, n);
  if (n == 1) {
    O(1, 1);
    return;
  }

  unordered_map<ll, ll> freq;
  II(i, n) { freq[a[i]]++; }

  pll best = {0, 0}; // sentinel value (if all single-group n-duplicates, it's
                     // best to avoid removing any)
  // pll cur = {1, 1};
  pll cur = {1, 0}; // make sure the current is also following the same rule
  // II(i, n - 1) {
  II(i, n) {
    // if (a[i] != a[i + 1]) {
    if (freq[a[i]] == 1) {
      cur.second++;
    } else {
      // @i == @i+1
      // or rather @i is duplicated

      // always prefer actual value over the empty sentinel
      // if (best.second - best.first < cur.second - cur.first ||
      //     (cur.first == cur.second && cur.second > 0)) {
      //
      //     chatgpt says the above statement allows cur.first==cur.second a
      //     freebie and replace any (including better longer interval) before
      //     it
      //
      //     the easy elegant way is to use <= instead of <
      //     by the nature of sentinel value {0,0}, we just want it replaced AS
      //     SOON AS POSSIBLE whereas before we don't have sentinel values so we
      //     just sort of think of it like minimal CPU processing when they're
      //     the same maxes/mins
      //
      //     only b/c of the presences of sentinel values we need <=
      if (best.second - best.first <= cur.second - cur.first) {

        best = cur;
      }

      // set it to the supposedly the end of the duplicates
      // if still duplicates wlil just move to the next one until the first
      // difference
      cur = {(i + 1) + 1, (i + 1)};
      // on the first freq==1, it will ++ on the .second so it's best to do it
      // -1 and also this creates a subarray length of -1 which will be
      // auto-filted by the sentinel {0,0}
    }
  }
  // if (a[n - 2] != a[n - 1]) {
  //   cur.second++;
  // }
  // if (best.second - best.first < cur.second - cur.first ||
  //     (cur.first == cur.second && cur.second > 0)) {
  if (best.second - best.first <= cur.second - cur.first) {
    best = cur;
  }

  if (best.first == best.second && best.second == 0) {
    O(0);
  } else {

    O(best.first, best.second);
  };
}
