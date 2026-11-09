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
// P.1: odd-lengthed subarrays are good by default (NOT SUBSEQ)
// P.2: even-lengthed subarrays are good if both-sides of their medians are
//      equal
//
// P.3: if all elements are the same, you have n(n+1)/2 good subarrays
// P.4: 1-lengthed subarrays are always good, (lower-bounded by n)
//
//
//
// 6 3 2 3 5 3 4 2 3 5
//
// 2 2 3 3 3 3 4 5 5 6
//
//
// ELEMENTS ARE ONLY UP TO 10 (WTF???)
//
// bucket?
//
// similiar quadratic rule with n(n+1)/2???
//
// because order no longer matters, we just have to ensure there are DUPLICATE
// values within an interval
//
// and how would we find all possible combinations of intervals that has these
// duplicates??
//
// windowing????
//
//
// Hint 1:
//  a_i = {1,2}
//
//  (generalized) when n>10 => duplicates unavoidable => some even-lengthed
//  subarrays will be good
//
// Hint 2:
//  summation? makes sense if we do not care about orders
//
//  whenever the sum = 0 => not good (median differs)
//
//  but requires quadratic checking....
//
//
// !!! TWO MAJOR OBSERVATION
//
// - bruteforce over x (due to limited range of x: 1 <= x <= 10)
//      and individually map a[i]<=x to -1 and a[i]>x to +1
//      (summation is order invariant by the properties of addition)
//
//      and check if x appears (prefix)
//
// - we can check for each interval whether the sum is 0 just by doing a linear
// pass
//      consider a smaller central interval that has a sum of 0 (even-lengthed),
//
// NOTICE: if we want to find any intervals with prefix-sum of 0 (fixed R
// varying over L), we just need to count/freq (collapse the indices of 0s)
// of previous 0s!
//
//
// but remember the x will be sorted by the order (b/c we're finding the median)
//
// but it still needs to touch the element with x before we can do that^^

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n);
  IV(a, n);

  ll num_good_subarrs = (n * (n + 1)) / 2;

  DBGLN("=========", num_good_subarrs);

  for (ll x = 1; x <= 10; x++) {
    DBGLN(x);

    ll ps = 0;
    // ll cnt0s = 0;
    // don't worry about space complexity (linear at most by the collapse of
    // counts/freq)
    unordered_map<ll, ll> freq_cnts; // all cnts before last_occ'd x
    unordered_map<ll, ll> buf_cnts;
    // all cnts (temp) after last_occ'd x (SO FAR)

    // freq_cnts[0]++;
    buf_cnts[0]++;

    ll last_occ = LLONG_MAX;

    // bool valid = false;
    II(i, n) {
      if (a[i] == x) {
        // valid = true;
        last_occ = i;

        DBG_MAP(freq_cnts);
        DBG_MAP(buf_cnts);
        for (auto &[k, v] : buf_cnts) {
          freq_cnts[k] += v;
        }
        buf_cnts.clear();

        // for (auto &[k, v] : freq_cnts) {
        //   num_good_subarrs -= (v * (v + 1)) / 2;
        // }
      }

      // <=x< or <x<= shouldn't matter since we're only checking for 0s
      // (will result in -1 or 1 or the opposite way)
      ps += (a[i] <= x) ? -1 : 1;
      // notice, 0 will only occur whenever subarray is even-lengthed

      // for every prefix occured AFTER the last occured x
      //    we can form a valid BAD subarray whenever subarray sum is 0 => with
      //    however many SAME/EQUAL prefx-sums BEFORE the last occured x
      //
      //    (without counting subarrays that don't have an x occured between
      //    them)
      buf_cnts[ps]++;
      DBGLN(i, ps, freq_cnts[ps], buf_cnts[ps]);
      num_good_subarrs -= freq_cnts[ps];

      // if (valid) {
      //   freq_cnts[ps]++;
      // }

      // if (ps == 0 && valid) {
      //   // cnt0s++;
      //   // num_good_subarrs -= cnt0s;
      // }

      // but what if the overall length is odd???
      // and say
      //
      //        *,*,*,*,*,*,*
      //          - - - - - -  has a prefix sum of 0 (exclude last)
      //                       (REMEMBER: this is bad and is a decrement)
      //        - - - - - - -  always has a prefix sum of non-0...
      //
      //                  so how does one count that later one?
      //
      //                       ~~=> the 1st element must have a "sum" of 0
      //                       ~~ (contradiction) why?
      //
      //
      // we actually need to find the frequency for each possible prefix sums
      //
      // and count the # of ways to pick a pair of them to form an interval
      // (without ordering because it is ordered as in the choose-2 function
      // will not double count the reverse ordering of what would be the same)
      //
      // we do match EQUAL prefix sums because it suggests that when we take the
      // subarrays of them, it will go back to a subarray sum of 0s (when the
      // removed prefix takes the outstanding side of the sums like too positive
      // or too much x< or the other way around from the current prefix sum s.t.
      // the current prefix sum with the left portion removed becoems a subarray
      // sum of 0 and hence why we just need to count the number of equal
      // subarray sum among it)
      //
      // but how does one ensure x is present? (avoid double-counting)
      //
      // we just need at least ONE x
      //
      // we can choose the L LEFT of x and the R RIGHT of x
      //
      // so like # of counts left of x TIMES # of counts right of x??
      //
      // prefix and suffix boolean?
      //
      // or actually just the LEFT-most occurence x and RIGHT-most occurence x
      //
      // or prefix sum on x?
      //
      // and do a min on it? (e.g., intersection where the subarray count of x
      // == 0 is always a subset??)
      //
      //
      // since we're iterating on R (and collapsing the various L)
      // we find the last occurence of x (b/c any subarrays with L greater than
      // the index of the last occurence of x is invalid bad subarray)
      //
      // if we find an occruency of x we flush the buffer (move the counts) to
      // the overall counts again...
    }
  }

  O(num_good_subarrs);
  ;
}
