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
// P.1: Bitwise OR suggests every bit-place must be occupied by at least one
//      restaurant (the bit-place must be 1)
//
// O.1: if the max a_i is say 8, DO NOT increase all the restaurants to a_i
//      or else there's no other bits to occupy other than 0b1000 when 0b1111
//      could be achieved (depending on n)
// O.2: POWERS OF 2 and whether a_i CAN BE INCREASED TO IT 2^x-1
// O.3: un-optimal to set a[i-1]=a[i] when a[i-1] < a[i]
//
//
// IF n==1: ==> a_i
// IF n>=2:
//      IF max(a_i) = 2^x-1: already optimal
//      IF say some a[i-1] < 2^x-1 < a[i] (or >)
//          increase the lower to that
//
// but what if none of none of these elements include 2^x-1
//
// say 5 and 6
//
// 6=00110
// 5=00101
//   -----
//       7!!!
//
// 12=001100
// 10=001010
//    ------
//      1110 not-optimal
// change 10 to 11 and get
//    001011 => optimal
//
//
// largest element is
//
//   some binary 1010110110111
//   if we have adj element == 1
//   icnrease it till the following
//                101001001000 (always possible => optimal)
//
// the question becomes what's the minimum?
//
// what if
//  1010110110111
//  1010110010000?
//  ^     ^^ ^
//  ^     ^^ can be set to 1 (or, all next one to 1
//  ^     ^importantly, this is 1>0
//  ^     cannot be set to 1
//  ^
//  the moment this bit becomes 0, we can just do 01111....
//
//  FIND THE MINIMUM!!!
//
//  if log2(min) < log2(max):  // lesser bit counts
//      ==> pow(2,log2(max)+1)-1
//  else:
//      // compare the min vs max
//      // since it is always optimal to use the min, can we do this eeven if
//      min/max arent adjacent??
//      // yes, even if the min is next to a LOCAL max, we can always use ANY
//      amount of operations to make that LOCAL max THE max (AND the min can
//      always include the local max)
//
//      1010110110111
//      1000000000000 < this is better (no special reverse ordering)
//      1010110100000 < suppose this is the LOCAL max
//      1001111111111 < we can set the min for all bits to be 1 (after setting
//      the next 1 to be 0 from the largest)
//                          ^^ is that actually the largest?
//
//      1010000000000 < isn't this the larger one??? or in fact,
//
//
//      the first bit in this config?
//        1
//        0
//
//      log2(max&(~min))  <== the bit place for the largest 1,0 config
//      then the max delicay is === min + pow(2,log2(max&(~min)))-1
//
//      but wait, if we do this, then it's basically the max but with the first
//      set of 0s gone, unusable, but after the 2nd 1 it can just be all 1
//
//      so in reality, it's just
//          pow(2,log2(max)+1)-1 (all 1s) no
//          nononono
//
//          if the min is large enough that's problematic
//
//          we just want the max with all the bits after the first bit-place
//          with (1,0) to be all 1s
//              or in ther words, the first (1,0) of the min so go back
//
//
//              min+pow(2,log2(max&(~min)))-1  ??
//                        ^^^^^^^^^^^^^^^^
//                          finds the first place with (1,0)
//                     power 2 then -1 (ensures 1,0) but all (x,1) after
//
//                 no need to do complex add
//
//              just do max|( pow(2,log2(max&(~min)))-1 )
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
  IVLL(a, n);

  if (n == 1) {
    O(a[0]);
    return;
  }

  ll mn = LLONG_MAX;
  ll mx = 0;

  II(i, n) {
    if (a[i] < mn) {
      mn = a[i];
    }
    if (a[i] > mx) {
      mx = a[i];
    }
  }

  if (mn == mx) {
    O(mx);
  } else if ((ll)(log2(mn)) < (ll)(log2(mx))) {
    O((ll)pow(2, (ll)log2(mx) + 1) - 1);
  } else { // first bit is the same for mn & mx (1,1)
    O(mx | ((ll)pow(2, (ll)log2(mx & (~mn))) - 1));
    // mx & ~mn first the first (1,0)
    // log2 of it find the bit place of that (inclusive of 0)
    // pow2((ll)log2) just finds the power of it (remove the other bits after
    // the first (1,0))
    // -1 flips all 1s after
    //
    // | just ors it
  };
}
