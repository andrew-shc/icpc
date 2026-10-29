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
// ~~~~ if there's any element that are NOT 2-duplciate => NO
//
// when they say "increase" they refer to the increment of the numbers' value
// (not the count of it)
//
//
//
// if an element >=2-duplicate => put 1 in the other
//
// refer g-2 as the number of extra duplicates it can help for LATER 1-duplicate
// elements
//
// if any 1-duplicates occur before any >2-duplicates => NO
//
// if there any ODD extra duplicates at the end that were left un-used =>
// DIRECTLY
//      NO
//   but it also means there were 1-duplicate elements below that will never be
//   duplicated ~~~~
//
//   (EVEN extra duplicates are fine at the end as it can be split)
//
//   consider this case, 2 2 4 4 5 5 5 6 6 6
//      clearly this is fine since we just need a 5->6
//
//
//
// TC-2 confusing..
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ^^^^
//
// 6
// 2 2 2 4 4 4
//
// (2 2 4 4) (2 4)
//    ^
//    once this ++'d => becomes 3 which will not happen on either bag unless the
//    4 2s?
//    KEY PROBLEM: the original pre-condition of requiring the number in bag 1
//    to be present in bag 2 also operates and modifies the same number that
//    breaks the pre-cond
//
// look back later
//
//
// going from least to most
// 2 2 2 4 4 4
//     ^
//     every odd amount of duplicates: either leave it and say immediately no
//          or TRY with +1 (if only a single element itself => NO)
//          on the next integer redo the process
//
//          just simply iterate going up one by one with n up to 1000 at most
//
//

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n); // even always
  IVLL(a, n);

  vll freq(n, 0);
  II(i, n) { freq[a[i] - 1]++; }

  // BY TESTCASE: it is greedy to actually keep the 2 but increase rest of the
  // extranouse numbers higher
  // and is unrelated to the parities properties because the original duplicates
  // can actuall self-increase like an unfolding stairs
  //      (say a many duplicate at integer x, immediately it seems impossibel to
  //      achieve x+2, but the moment we can get many of the x's to become
  //      x+1's, x+2 becomes achievable)
  // 2 2 2 2 2 2 becomes
  // 2 2 3 3 3 3 becomes
  // 2 2 3 3 4 4 so on and so forth

  II(i, n) {
    // if (freq[a[i] - 1] % 2 == 1 && freq[a[i] - 1] >= 3) {
    // i not a[i]
    if (freq[i] >= 3) {
      if (i == n - 1) {
        if (freq[n - 1] % 2 == 1) {
          // %2==1, not just ==1, because this is the end
          OHNO;
          return;
        } else {
          // happily ever after
        }
      } else {
        freq[i + 1] += freq[i] - 2;
      }
      // don't care about the current a[i]-1 since we will never look back (no
      // regret)

      // if (freq[a[i]] == 0) {
      //   OHNO;
      //   return;
      // } else {
      //   freq[a[i]]++;
      // }
    } else if (freq[i] == 1) {
      OHNO;
      return;
    }
  }
  OHYES;

  // ST(a);
  // unordered_map<ll, ll> freq;
  // map<ll, ll> freq; // KEY NOTE: ORDERED BY KEYS
  // II(i, n) { freq[a[i]]++; }
  //
  // // using ordered map to ensure the updates are in order
  // for (auto &[k, v] : freq) {
  //   if (v % 2 == 1 && v >= 3) {
  //     if (freq[k + 1] == 0) {
  //       OHNO;
  //       return;
  //     } else {
  //       freq[k + 1]++;
  //     }
  //   } else if (v == 1) {
  //     OHNO;
  //     return;
  //   }
  // }
  // OHYES;

  // even numbers are fine
  // odd numbers -> it is GREEDY to always move the one up (no need for 3 or 5
  // since O+O=E and the various parity properties of O/E)
  //        and also impossible (breaks the chain) if one moves the
  //        evenly-paired duplicates themselves
  //
  // check for any single elements!
  // or, rather, check for any ODD numbers that have an empty, unfilled number
  // next
  ;
}
