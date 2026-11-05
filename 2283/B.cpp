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
// min # of elements that needs to be removed so the resulting string s is
// rhythmic which means
//      1. periodic (by the existential quanitifer of k, any string is periodic
//      for a given k that includes up to the length of the entire string)
//      2. only a single 1 in the first period of the string (where period is
//      the lowest k)
//
//
// n==1 is aways rhythmic
//
// assume we sort a[]
// *********** ASSUME WE SORT A[]****** HOW DID WE FORGET THIS??????
//
// if all elements in a[] are multiples of a[0]
//      => rhythmic (period only decreases while maintaing a single 1 in the
//      first p-lengthed period)
//
// if ANY elements in a[] are NOT multiples of a[0]
//      => clearly, the period will follow the LCM cycles of all the elements
//         and if the LCM cycle is greater than even the first a[0] => bad
//
//      (really, any elements in a[] not multiples of a[0] => bad)
//
// REMEMBER, WE'RE FINDING THE MIN # OF ELEMENTS TO BE REMOVED SO THE LCM CYCLE
// EQUALS TO a[0] (not a yes/no)
//
// stratify the elements in array a by their multiplicity
//
// e.g.,
//
//      2: 2,4,6,8
//      3: 6,9,15,21,33
//      .
//      .
//      .
//
//      clearly, if we can only remove either 2 or 3, removing (2).size() will
//      be the better options
//
//      but given all these unique multiplicities, we have to find the biggest
//      one (because we can ONLY have one of them or else LCM is greater than
//      them and etc etc etc)
//
//      INCLUDE DUPLICATES
//
//      we have to ensure that we're not double-counting the same prime factors
//
//      instead of summing all the other factors we want to remove from the
//      freq_map (which can double-count) we just want to keep the current
//      multiplicities so just do a.size()-currently selected multi.size()
//
//
//      consider 12, 18
//
//      2x2x3
//      2x3x3
//
//      recall LCM??
//
//      this has a LCM of 6
//
//      yes 1 is correct (b/c we don't have the initial 6 so it must start 12 or
//      18 and remove the other unforateunely)
//
//      but if it's 6,12,18 should be 0 which is what this is returning....
//
//      look at the bounds, if a[i]>n ==> ignore (keep them, doesn't do
//      anything)
//
//      a[i]==n does impact b/c it will add a 1 that will effect it but a[i]>n
//      absolute no
//
//
//      m-k???
//
//
//      10^18 zeroes
//      m=10^18
//
//
//      exclude any factors within 10^18-mult=..=10^18 ???

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n); // n>=1
  IV(a, n);

  ST(a);
  // ll excluded = 0;

  // duplicates are fine
  unordered_map<ll, ll> freq_multiplicities;

  // quadratic fine over a.size()
  II(i, n) {
    // if (a[i] > n) {
    //   // omit it from the reduction of min_num defined as n-freq (-freq)
    //   // where lesser freq
    //   // nononono
    //   // keep a separate tracker of all the elements >n
    //   // that will always be included regardless (- # the amnt)
    //   //
    //   // excluded++;
    //   // continue;
    //   //
    //   //
    //   // but we assume the string goes on forever? no m is defined
    // }

    // bool existed = false;
    for (auto &[mult, freq] : freq_multiplicities) {
      if ((a[i] % mult) == 0) {
        freq++;
        // existed = true;

        // no break
      }
    }

    // ~~this removes duplicates~~
    // this implicitly omits large numbers that has been incorporated to earlier
    // factors when it is perfectly valid for itself to be one if not (BAD)
    //
    // if
    // (!existed) {
    //   freq_multiplicities[a[i]]++;
    // }

    // more generalized case (BETTER)
    if (freq_multiplicities[a[i]] == 0) {
      freq_multiplicities[a[i]]++;
    }
  }

  // ll min_num = LLONG_MAX;
  ll min_num = n;

  // 10^18 => 18 zeroes
  // ll m = 1'000'000'000'000'000'000LL;

  // DBG_MAP(freq_multiplicities);
  for (auto &[mult, freq] : freq_multiplicities) {
    // ll offset = 0;
    // II(i, n) {
    //   if (a[i] > m - mult) {
    //     offset++;
    //   }
    // }

    min_num = min(min_num, n - freq);
    // min_num = min(min_num, n - freq + offset);
    // min_num = min(min_num, n - freq - offset);
    // min_num = min(min_num, n - freq - excluded);
  }

  O(min_num);
  ;
}
