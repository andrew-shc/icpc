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
//  ~~if there are k
//
//  if k==n:
//      should always increase (smallest to largest)
//  if k==1:
//      should always decrease (largest to smallest)
//
//  AT LEAST ONE VERY PLEASANT DONATIONS
//
//  P.1: if all numbers are duplicate => k must be n
//       if 2 numbers are duplicate =>
//
//
//  increase then decrease
//
//  even with   4 5 5 5 5 5
//
//  consider 4 5 5 5 5 5 5
//
//  k==n:
//      4 5 5 5 5 5 5 5
// or,  5 5 5 5 5 5 5 6
// NOT  5 5 5 5 5 5 5 4 (k==n-1)
//  k==1:
//      6 5 5 5 5 5 5 5
//  k==2:
//      5 6 5 5 5 5 5 5
//  k==3:
//      5 5 6 5 5 5 5 5
//
// THEREFORE,
//      if all values are the same, k must be n
//      OTHERWISE,
//          we can always recorder a to conform to a k
//              ??? (if we just take the largest values, and take the remaining
//              lowest value, yes we care about the slope, but this also
//              guarantees the next average after the kth element will be AT or
//              below assuming there's a higher value between 1st and kth
//              element which is assumed when not all elements are same)
//
// consider 5 5 5 5 5 4
//
// (can we achieve k=1???)
//
// if we take the k largest and sort it
// and take the n-k smallest and sort it reversed
//
// can we just verify if this works or not?
//
// is that operation optimal?
//
// i think we just need to check for duplicates
//

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n, k); // EXACTLY k very pleasant donations
  IV(a, n);

  bool all_same = true;
  II(i, n - 1) {
    if (a[i] != a[i + 1]) {
      all_same = false;
      break;
    }
  }

  if (all_same && (k != n)) {
    O("NO");
  } else {
    vll ordered_donations;

    ST(a);

    II(i, k) {
      // ordered_donations.PB(a[n - 1 - i]);
      // ordered_donations.PB(a[n - 1 - k + i]);
      ordered_donations.PB(a[n - k + i]);
    }
    II(i, n - k) { ordered_donations.PB(a[n - k - i - 1]); }

    // check again if duplicates messes things up since this configuration
    // should be an optimal config

    ll k_real = 1;
    II(i, n - 1) {
      // after the operation (since it uses sort) we know that the moment it
      // goes down it msut be the end (but it can stay teh same longer than
      // expected due to duplicates => bad)
      if (ordered_donations[i] <= ordered_donations[i + 1]) {
        k_real++;
      } else {
        break;
      }
    }

    if (k_real > k) {
      OHNO;
      return;
    }

    O("YES");
    OIT(ordered_donations);
  };
}
