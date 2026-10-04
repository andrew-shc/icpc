#include <bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using vll = std::vector<ll>;
using dll = std::deque<ll>;
using pll = std::pair<ll, ll>;
using vpll = std::vector<pll>;

const ll NEG = (long long)-4e18;
const ll MOD = 998244353;

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
#define DBLOCK if (false)
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

void solve(ll T);

int main() {
  /////////////////////////////////////////////////////////////////////
  //// comment out the sync when working with interactive problems ////
  /////////////////////////////////////////////////////////////////////
  ios_base::sync_with_stdio(false);
  /////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// START ACTUAL CODE
///////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

// start: 14:40
//   end: xxxx

// min ops. on bit flipping till all element values reach the value @p1
// like an onion peeling from both ends and p1 should be the center to minimize
// ops.

// invariant: the width or amount of 1's or 0's and only care about the change
// between 1<->0 invariant: when either ends' value (initially) equals to x
// (a[p1])

// find the most flips from @0 to @k-1 and @k+1 to @n-1

// impl: count number of times adjacent values change/flip and subtract 1 IF the
// respective end is same as x (for both sides of k)
// ---

// lets force-implement two-pointers
// actually, we just need the # of min. ops.
// just linearly single-loop count all the switches (but impl-wise seems to be
// more complicated)
//
// any adjacent changes ==> +1
// if the first a[0] == a[k] ==> -1

// counter-example: when left is 3 and right is 1 (raw values with ends
// correction)
// 1 0 1 0* 1

// 1 0 1 0* 1
// 0 1 0 1  0
// 0 0 1 0  0
// 0 0 0 1  0
// 0 0 0 0  0 (4 ops, not 3 nor 1... why?)

// O.1, after ends correction it is the left and right is always odd amount
// O.2, after ends correction + de-dupe, it follows an alternating narrowing
// triangle of 1s and 0s
// O.3: if there's an opposing bit on the adjacent of the index-of-interest,
// then it requires two ops
//      since it flips the adjacent and needs to flip back its own
//

void solve([[maybe_unused]] ll T) {
  // k == 1 (ez version)
  READ(n, k);
  READ_VLL(a, n);
  READ(p1);

  ll x_ap1 = a[p1 - 1];

  ll left = 0;  // number of de-duped end-corrected opposing bits (left-side of
                // the index-of-interest)
  ll right = 0; // (right-side)
  INC(i, p1) {  // last pair is p1-2 to p1-1
    if (a[i] != a[i + 1] && a[i] != x_ap1) {
      left++;
    }
  }

  for (ll i = p1 - 1; i < n - 1;
       i++) { // first pair is p1-1 to p1 and last pair is n-2 to n-1
    if (a[i] != a[i + 1] &&
        a[i + 1] != x_ap1) { // think of it as the direction flipped hence i+1
      right++;
    }
  }

  // functioanlity already fixed by the new version
  /*   // using max since, elegantly-speaking, it requires an opposing bit in
    between
    // the index-of-interest and the ends
    // or else it just wraps to 0
    if (a[0] == x_ap1) {
      left = max(left - 1, 0LL);
    }
    if (a[n - 1] == x_ap1) {
      right = max(right - 1, 0LL);
    }
   */
  ll min_ops = max(left * 2, right * 2);
  OUT(min_ops);
}
