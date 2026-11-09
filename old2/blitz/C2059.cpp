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
// O.1: he must always serve one queue => one queue must be 0 at the end =>
//      min MEX is 1
//
//
// consider cases where all a_ij = 2
//  for every queue at every time 2 customers arrive
//
//  ==> MEX can only be as large as 1 (not 2 or 3 since no queue would have 1)
//
//  ==> find the largest MEX requires looking at the ends
//
// O.2: largest MEX is bounded by n
//      (can be at most n)
//
//      we got to find the queue that sums to 1 from 1-index back
//         sums to 2 from 2-index back
//         susm to 3 from 3-index back
//
// since n=300
//
// we can just do quadratic solution
//
// which can just be used to compute suffix sum
//
// and then at every index of moment of time from END to START
//      for i=n...2
//      - find any suffix sum @i with value of n-i+1
//      - mark each queue with when their SS matches @i
//      -
//
//
// === POINT OF STUCK ===
//
// what happens of
//
// === UNSTUCK: 1 <= a_ij (if 0 is included might be a bit harder)
//
// but what if its like
//
//            1
//          1 1
//      1 1 1 1
//            3
//
// key observation:
//      we prefer a triangle of 1s from the end
//      but sometimes there can be option with highers numbers that are missing
//      from the triangle of 1s. however these higher numbers shorten it but by
//      the time Nikyr wants to reset the queue to 0, he just simply cannot
//      reset the queue with a higher-number-that-would-be-useful-later right
//      now because it does nothing to MEX and it will never be
//
//  hence, find the triangles of 1s until there's a break or stop
//
//  how does one find the 0?
//
//  it's a triangle of 1s with a *required* freebie
//
//  IMPL:
//      find the triangle of 1s
//
//      if all are triangle of 1s:
//          pick the last/largest of the triangle of 1s and move it to be
//          cleared at the very end for x=0
//
//      or, just count the # of 1s for each array and record it in some master
//      array
//
//
// === PRELIMINARILY SOLVED / CHECK OTHER Qs ===
//
//
//
// per WA2,
//
//      even if we're limited to 1s, we still have to consider when both queues
//      have 1s all the way that can be used as a subset
//
//      what we can do is sort the number of 1s of each queue and try to see how
//      long we can construct the triangle/diagonal

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n);
  vector<vll> a;
  II(i, n) {
    IVLL(ai_, n);
    a.PB(ai_);
  }

  // vll records(n + 1, 0);
  vll ones;

  II(i, n) {
    ll cnt = 0;
    DD(j, n) {
      if (a[i][j] == 1) {
        cnt++;
      } else {
        break;
      }
    }
    // records[cnt] = 1; // assignment, not increment
    ones.PB(cnt);
  }

  ST(ones);   // reason we can easily sort compared to if we hadn't assume 1 as
              // the optimal choice is it will be HARD TO DECIDE which queue
              // should be placed later or earlier to be cleared
  ll mex = 1; // assume mex of 0 (same arg as before)

  DBG_ITER(ones);

  // checks triangles from 1-n (n is the max but can be less if there are less
  // triangular ones)
  II(i, ones.size()) {
    // if (ones[i] >= i + 1) {
    if (ones[i] >= mex) {
      mex++;
    } else {
      continue; // skip and continue trying to find the next or none after (or
                // none that can beat the higher required number of ones)
      // break;
    };
  }

  if (mex == n + 1) {
    mex = n;
  }
  O(mex);

  // ll mex = 1; // 0 (assume 0 for simplicty for the last conditional)
  // II(i, n) {
  //   // b/c we assume 0, i..n+1 -> i..n
  //   //                  records[i] -> records[i+1]
  //   if (records[i + 1] == 1) {
  //     mex++;
  //   } else {
  //     break;
  //   }
  // }
  //
  // // mex can never reach n+1 (when x=1...=n) since we need a queue to be 0
  // // with x=0...=n-1 ==> MEX=n
  // if (mex == n + 1) {
  //   mex = n;
  // }
  // // since mex is assumed to start with 1, and the if condition already
  // covers
  // // it when it is all triangle 1s but also when there are some that does not
  // // fit into it, we already know that mex is not using all of it by mex !=
  // n+1
  // // and therefore the ones not using it can just be used by mex as the 0th
  // // starting point
  // O(mex);
}
