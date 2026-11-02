#include <algorithm>
#include <bits/stdc++.h>
#include <climits>
#include <unordered_set>

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

// start: 1914
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
// P.1: 0 is always present
//
//
// DP?
//
// O.1: only 1/-1 except for AT MOST ONE elements
//      => adjacent elements densely pack/occupy the range in sums
//
// O.2: every subarray sum starts with 0 and slowly go to the extremes
//      => max range: [min=longest continuous -1s, max=longest continuous 1s]
//
// IMPL:
//
//      abstract a into consecutive (+) (-) groups
//
//      keep track of global_max/global_min
//                   running_max/running_min
//
//      if (+):
//          running_max+= (+)
//          global_max += max(global_max, running_max)
//      elif (-):
//          running_max += max(running_max - |(-)|, 0)
//
//          // do the same but opposite for the mins
//
//          // => the range of values on ONE side of the (*)
//                  (the # that is not 1/-1s)
//
//          // => given two ranges from either side of the (*)
//          //    PROBLEM: we don't want global_max since it may include cut-off
//          places (places that reached 0 that makes it no longer greedy)
//
//      // DO WE NEED TO ABSTRACT?
//      // NO? B/C WE CAN JUST CHECK INDIVIDUAL #s 1/-1s AND WHETHER 0 IS
//      REACHED
//
//      // then how would (*) interact?
//      // brute force?
//
//      IF (*)>0: affects the (+)
//      IF (*)<0: affects the (-)
//
//
//
// === STUCK: there's a non 1/-1 element ===
//
//  just brute force it? not everything has to be elegant...
//
//
// CASE 1: EXCLUDE (*)
// CASE 2: INCLUDE (*) on each side
// CASE 3: INCLUDE (*)...
//      we have to wrap it around in all sorts of combinations??
//
//      no all sorts of combinations. because we'reo nly
//      incrementing/decrementing by 1 its fine (recall the abstraction)
//
//      both directions should be symmetric so let's just start with the (*)
//      if it exists
//
//
//
// getting MLE???
//
// chatgpt says it's from a bug in the code rather than an implementation data
// structure choice problem
//
//
//
// !!!!! editorial
//
//!!!! Paragraph 0.5 & O(n) complexity
//
//  remember, we're working in subarrays. two pointer windowing would work here
//  because the way the problem is structured linearly on the array and
//  achieving all the possible sums merely depends on the length of the subarray
//
//  notably,
//      if the current window subarray sum is <=0,
//          shift L,R to the next (+)
//      otherwise:
//          R++
//
//      (do the opposite for negative sums)
//      (do the reverse for all 2 previosu ways)
//
//      (so like 4x two pointer)
//          ^^
//          remember, we should not be boxing ourselves up with elegant solution
//          with arbitratry definition of "elegancy" (e.g., only go forward)
//
//
//      we can do this O(n)
//
//          by doing two pointers on the pre-computede individual sums also....
//
//      ~~center_sum
//      ~~special_sum
//
//      by trial and error, it seems like we do not want to reset to the next
//      number but when we reach a different sign (1 to -1 or -1 to 1) we want
//      to slowly go explore the other direction as much as possible to explore
//      as much possible kind of sums as possible
//
//
//  ~~~~~
//
//
//  go back to the original solution and remove the stops (per chatgpt / before
//  somehow it worked on the testcases but sometimes there will be more 1s or
//  -1s then the special (*) element after 0 is reached)
//
//  (per chatgpt) despite the original solution was b/c of the lack of combining
//  both seq., the fear that there is more to it was unfounded and it was just
//  simply the lack of combining both seq. and the original soln. was already
//  quite close to what the editorial is doing
//
//
//
//
//
//!!!!! per editorial
//
//!!! P4-5:
//      given prefix sum, notice ps[r]-ps[l]
//
//      for every fixed r we find the minimum ps[l] within the range of r
//
//      IMPL-WISE:
//          for every increase in r, is ps[r-1] < ps[l]?
//              then pick the latest ps[r-1]
//                  (same things happens if we fix l and find the largest r)
//
//              => for max subarray sum
//
//              (opposite for min subarray sum)
//
//
//      but when we reach the special (*) element
//          we ignore all prefix sums before the element and only search for the
//          smallest element on and after the special element (because now we
//          assume we're looking for the smallest subarray sum exclusively when
//          the special (*) element is included)
//
//          remember, the left endpoint is exclusive (1@l-1)
//
//      so basically if the (*) is positive (some really large #) and we're
//      finding the max subarray sum, then usually we'll just exclude any
//      elements before it....
//
//!!! editorial observation: (basically what we did with L/R below is just
//! excluding the special element (*))
//!!      and by the observaiton that any subarray sum excluding the strange
//! elements will always intersect by 0, we actually just find a pair of small
//! prefix and largest suffix (where each prefix/suffix must be on the same side
//! w.r.t. the special el. (*))
//! and for the subarray sum WITH the special el. (*), we just ensure the prefix
//! and the suffix crosses the (*)'s index
//
//! i.e., maintain the smallest prefix before (*) and maintain the largest
//! suffix after (*) for the subarray-sum including (*)
//
// and do the same for the min subarray-sum
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

  ll si = -1;
  II(i, n) {
    if (a[i] != 1 && a[i] != -1) {
      si = i;
      break;
    }
  }

  PS(pa, a);

  // optimal subarray sum (min and max)
  pll optimal_ss_ALL = {0, 0};
  // again but only for on si or after
  pll optimal_ss_R = {
      2000000000,
      -2000000000,

  };
  // {LLONG_MAX, LLONG_MIN};

  // ~~~.first=min, .second=max
  // .first=min, .second=max
  // optimal choice of min/max PREFIX values
  pll optimal_p_L = {0, 0};
  // optimal choices for min/max PREFIX values AFTER the special (*) if it
  // exists
  // (after a given the incrementing R)
  pll optimal_p_R = {
      2000000000,
      -2000000000,
  };
  // {LLONG_MAX, LLONG_MIN};

  // first likely refers to the L/R, second likely refers to M

  II(i, n) {
    if (i == si) {
      optimal_p_R = optimal_p_L;
      optimal_p_L = {pa[si + 1], pa[si + 1]};
    }

    // where pa[i+1] refers to pa[R]
    //  so we're directly computing the optimal sum (not the optimal indices we
    //  did before)
    //
    //
    optimal_ss_ALL = {
        min(optimal_ss_ALL.first, pa[i + 1] - optimal_p_L.second),
        max(optimal_ss_ALL.second, pa[i + 1] - optimal_p_L.first)};
    optimal_ss_R = {min(optimal_ss_R.first, pa[i + 1] - optimal_p_R.second),
                    max(optimal_ss_R.second, pa[i + 1] - optimal_p_R.first)};

    // optimal L choice for pa[L] (to be subtracted)
    optimal_p_L = {min(optimal_p_L.first, pa[i + 1]),
                   max(optimal_p_L.second, pa[i + 1])};
  }

  vll sums;

  // mn > mx
  if (optimal_ss_R.first > optimal_ss_ALL.second) {
    for (ll k = optimal_ss_ALL.first; k <= optimal_ss_ALL.second; k++) {
      sums.PB(k);
    }
    for (ll k = optimal_ss_R.first; k <= optimal_ss_R.second; k++) {
      sums.PB(k);
    }

    // mx < mn
  } else if (optimal_ss_R.second < optimal_ss_ALL.first) {
    for (ll k = optimal_ss_R.first; k <= optimal_ss_R.second; k++) {
      sums.PB(k);
    }
    for (ll k = optimal_ss_ALL.first; k <= optimal_ss_ALL.second; k++) {
      sums.PB(k);
    }
  } else {
    for (ll k = min(optimal_ss_ALL.first, optimal_ss_R.first);
         k <= max(optimal_ss_ALL.second, optimal_ss_R.second); k++) {
      sums.PB(k);
    }
  }

  O(sums.size());
  OIT(sums);

  //   pll mx = {0, 0};
  //   pll mn = {0, 0};
  //
  //   II(i, n) {
  //     if (pa[i] < pa[mx.first]) {
  //       // exclusive (so -1)
  //       mx.first = i;
  //     }
  //     if (pa[i + 1] > pa[mx.second + 1]) {
  //       mx.second = i;
  //     }
  //
  //     if (pa[i] > pa[mn.first]) {
  //       mx.first = i;
  //     }
  //     if (pa[i + 1] < pa[mx.second + 1]) {
  //       mx.second = i;
  //     }
  //   }
  //
  //   ll maximum = pa[mx.second] - pa[mx.first];
  //   ll minimum = pa[mn.second] - pa[mn.first];
  //   for (ll k = minimum; k <= maximum; k++) {
  //     sums.PB(k);
  //   }
  // } else {
  // ensure they're on the same side
  // pll mx_ex = {0, 1};
  // // ensure they cross the 0@si
  // pll mx_in = {0, n - 1};
  //
  // pll mn_ex = {0, 1};
  // pll mn_in = {0, n - 1};

  // // .first=starting,   .second=ending
  // // minimize L, maximize R
  // pll mx_L = {0, 1}; // .first<=si, .second<=si
  // pll mx_R = {0, 1}; // .first >si, .second >si
  // pll mx_M = {0, 1}; // .first<=si, .second >si
  // // maximize L, minimize R
  // pll mn_L = {0, 1}; // .first<=si, .second<=si
  // pll mn_R = {0, 1}; // .first >si, .second >si
  // pll mn_M = {0, 1}; // .first<=si, .second >si
  //
  // // NOTICE, we don't need to separately check for ==si, just <= and > on si
  //
  // if (si == -1) {
  //   II(i, n) {
  //     // maximize
  //     if (pa[i] < pa[mx_L.first]) {
  //       mx_L.first = i;
  //     }
  //     if (pa[i] > pa[mx_L.second]) {
  //       mx_L.second = i + 1;
  //     }
  //     // minimize
  //     if (pa[i] > pa[mn_L.first]) {
  //       mn_L.first = i;
  //     }
  //     if (pa[i] < pa[mn_L.second]) {
  //       mn_L.second = i + 1;
  //     }
  //   }
  //   // mx_L's are correctly index-shifted (+1 on .second)
  //   ll mx = mx_L.first <= mx_L.second ? pa[mx_L.second] - pa[mx_L.first] : 0;
  //   ll mn = mn_L.first <= mn_L.second ? pa[mn_L.second] - pa[mn_L.first] : 0;
  //
  //   DBGLN(mx_L.first, mx_L.second);
  //   DBGLN(mn_L.first, mn_L.second);
  //
  //   for (ll k = mn; k <= mx; k++) {
  //     sums.PB(k);
  //   }
  // } else {
  //   mx_R = {si, si + 1};
  //   mx_M = {0, si + 1};
  //   mn_R = {si, si + 1};
  //   mn_M = {0, si + 1};
  //   II(i, n) {
  //     // maximize
  //     if (i <= si) {
  //       if (pa[i] < pa[mx_L.first]) {
  //         mx_L.first = i;
  //       }
  //       if (pa[i + 1] > pa[mx_L.second]) {
  //         mx_L.second = i + 1;
  //       }
  //       if (pa[i] < pa[mx_M.first]) {
  //         mx_M.first = i;
  //       }
  //     } else { // i >si
  //       if (pa[i] < pa[mx_R.first]) {
  //         mx_R.first = i;
  //       }
  //       if (pa[i + 1] > pa[mx_R.second]) {
  //         mx_R.second = i + 1;
  //       }
  //       if (pa[i + 1] > pa[mx_M.second]) {
  //         mx_M.second = i + 1;
  //       }
  //     }
  //     // minimize
  //     if (i <= si) {
  //       if (pa[i] > pa[mn_L.first]) {
  //         mn_L.first = i;
  //       }
  //       if (pa[i + 1] < pa[mn_L.second]) {
  //         mn_L.second = i + 1;
  //       }
  //       if (pa[i] > pa[mn_M.first]) {
  //         mn_M.first = i;
  //       }
  //     } else { // i >si
  //       if (pa[i] > pa[mn_R.first]) {
  //         mn_R.first = i;
  //       }
  //       if (pa[i + 1] < pa[mn_R.second]) {
  //         mn_R.second = i + 1;
  //       }
  //       if (pa[i + 1] < pa[mn_M.second]) {
  //         mn_M.second = i + 1;
  //       }
  //     }
  //   }
  //
  //   ll mxL = mx_L.first <= mx_L.second ? pa[mx_L.second] - pa[mx_L.first] :
  //   0; ll mnL = mn_L.first <= mn_L.second ? pa[mn_L.second] - pa[mn_L.first]
  //   : 0; ll mxR = mx_R.first <= mx_R.second ? pa[mx_R.second] -
  //   pa[mx_R.first] : 0; ll mnR = mn_R.first <= mn_R.second ? pa[mn_R.second]
  //   - pa[mn_R.first] : 0; ll mxM = mx_M.first <= mx_M.second ?
  //   pa[mx_M.second] - pa[mx_M.first] : 0; ll mnM = mn_M.first <= mn_M.second
  //   ? pa[mn_M.second] - pa[mn_M.first] : 0; ll mx = max(mxL, mxR); ll mn =
  //   min(mnL, mnR);
  //
  //   DBGLN(si);
  //   DBGLN(mx_L.first, mx_L.second);
  //   DBGLN(mn_L.first, mn_L.second);
  //   DBGLN(mx_R.first, mx_R.second);
  //   DBGLN(mn_R.first, mn_R.second);
  //   DBGLN(mx_M.first, mx_M.second);
  //   DBGLN(mn_M.first, mn_M.second);
  //
  //   DBGLN(mxL, mnL);
  //   DBGLN(mxR, mnR);
  //   DBGLN(mxM, mnM);
  //
  //   if ((mn <= mxM && mxM <= mx) || (mn <= mnM && mnM <= mx) ||
  //       (mnM <= mn && mn <= mxM) || (mnM <= mx && mx <= mnM)) {
  //     // assume they can be merged
  //     // can be thought of as the moment ONE of the ends is merge-able then
  //     // there are NO holes that requires two separate loops (check the 2nd
  //     // conditional)
  //
  //     mx = max(mx, mxM);
  //     mn = min(mn, mnM);
  //
  //     for (ll k = mn; k <= mx; k++) {
  //       sums.PB(k);
  //     }
  //   } else {
  //     // un-merge-able
  //
  //     if (mx < mnM) {
  //       for (ll k = mn; k <= mx; k++) {
  //         sums.PB(k);
  //       }
  //       for (ll k = mnM; k <= mxM; k++) {
  //         sums.PB(k);
  //       }
  //     } else { // mxM < mn (or else it would be merge-able which would be
  //              // handled above)
  //       for (ll k = mnM; k <= mxM; k++) {
  //         sums.PB(k);
  //       }
  //       for (ll k = mn; k <= mx; k++) {
  //         sums.PB(k);
  //       }
  //     }
  //   }
  // }

  // II(i, n) {
  //   if (pa[i] < pa[mx_L.first]) {
  //     mx_L.first = i;
  //   }
  // }

  // II(i, n) {
  //   if (i < si) {
  //     if (pa[i] < pa[mx_ex.first]) {
  //       mx_ex.first = i;
  //     }
  //     if (pa[i + 1] > pa[mx_ex.second + 1]) {
  //       mx_ex.second = i;
  //     }
  //   } else if (i == si) {
  //
  //   } else { // i>si
  //   }
  // }
  // }

  // O(sums.size());
  // OIT(sums);

  // vll sum_pos_I = {0}; //  1 ->  x
  // vll sum_neg_I = {0}; // -1 -> -x (reversed)
  // vll sum_pos_R = {0};
  // vll sum_neg_R = {0};
  //
  // // 1@
  // PS(psa, a);
  //
  // ll L, R;
  //
  // L = 0;
  // R = 1;
  // while (true) {
  //   if (R > n) {
  //     break;
  //   }
  //
  //   ll ss = psa[R] - psa[L];
  //   if (ss <= 0) {
  //     L = R - 1; // L <- R
  //     L++;
  //     R++;
  //   } else {
  //     R++;
  //   }
  //   if (sum_pos_I.back() < ss) {
  //     sum_pos_I.PB(ss);
  //   }
  // }
  //
  // L = 0;
  // R = 1;
  // while (true) {
  //   if (R > n) {
  //     break;
  //   }
  //
  //   ll ss = psa[R] - psa[L];
  //   if (ss >= 0) {
  //     L = R - 1; // L <- R
  //     L++;
  //     R++;
  //   } else {
  //     R++;
  //   }
  //
  //   if (sum_neg_I.back() > ss) {
  //     sum_neg_I.PB(ss);
  //   }
  // }
  //
  // L = n - 1;
  // R = n;
  // while (true) {
  //   if (L < 0) {
  //     break;
  //   }
  //
  //   ll ss = psa[R] - psa[L];
  //   if (ss <= 0) {
  //     L = R - 1; // L <- R
  //     L--;
  //     R--;
  //   } else {
  //     L--;
  //   }
  //   if (sum_pos_R.back() < ss) {
  //     sum_pos_R.PB(ss);
  //   }
  // }
  //
  // L = n - 1;
  // R = n;
  // while (true) {
  //   if (L < 0) {
  //     break;
  //   }
  //
  //   ll ss = psa[R] - psa[L];
  //   if (ss >= 0) {
  //     L = R - 1; // L <- R
  //     L--;
  //     R--;
  //   } else {
  //     L--;
  //   }
  //
  //   if (sum_neg_R.back() > ss) {
  //     sum_neg_R.PB(ss);
  //   }
  // }
  //
  // vll sums_v;
  //
  // ll spI = 0;
  // ll snI = sum_neg_I.size() - 1;
  // ll spR = 0;
  // ll snR = sum_neg_R.size() - 1;
  // ll end_attempts = 0;
  // while (end_attempts <= 1) {
  //
  //   vll tests;
  //   if (sum_pos_I.size() > 0)
  //     tests.PB(sum_pos_I[spI]);
  //   if (sum_neg_I.size() > 0)
  //     tests.PB(sum_neg_I[snI]);
  //   if (sum_pos_R.size() > 0)
  //     tests.PB(sum_pos_R[spR]);
  //   if (sum_neg_R.size() > 0)
  //     tests.PB(sum_neg_R[snR]);
  //
  //   DBG_ITER(sum_pos_I);
  //   DBG_ITER(sum_neg_I);
  //   DBG_ITER(sum_pos_R);
  //   DBG_ITER(sum_neg_R);
  //
  //   DBGLN(sum_pos_I.size(), sum_neg_I.size(), sum_pos_R.size(),
  //         sum_neg_R.size());
  //   DBGLN(spI, snI, spR, snR);
  //   DBG_ITER(tests);
  //   DBG_ITER(sums_v);
  //   if (tests.size() == 0) {
  //     break;
  //   }
  //
  //   // ll test = min(min(sum_pos_I[spI], sum_neg_I[snI]),
  //   //               min(sum_pos_R[spR], sum_neg_R[snR]));
  //   ll test = *min_element(tests.begin(), tests.end());
  //   DBGLN(test);
  //
  //   // if (sums_v.size() == 0) {
  //   // sums_v.PB(test);
  //   //   if (spI < sum_pos_I.size() - 1 && test == sum_pos_I[spI])
  //   //     spI++;
  //   //   if (0 < snI && test == sum_neg_I[snI])
  //   //     snI--;
  //   //   if (spR < sum_pos_R.size() - 1 && test == sum_pos_R[spR])
  //   //     spR++;
  //   //   if (0 < snR && test == sum_neg_R[snR])
  //   //     snR--;
  //   // } else {
  //   // if (sums_v.back() < test) {
  //   // if (sums_v.size() == 0 || sums_v.back()) {
  //   if (sums_v.size() == 0 || sums_v.back() < test) {
  //     sums_v.PB(test);
  //   }
  //
  //   if (spI < sum_pos_I.size() - 1 && test == sum_pos_I[spI]) {
  //     spI++;
  //   } else if (spI == sum_pos_I.size() - 1 && test == sum_pos_I[spI]) {
  //     sum_pos_I = {};
  //     spI = 0;
  //   }
  //
  //   if (0 < snI && test == sum_neg_I[snI]) {
  //     // DBGLN("WTF????");
  //     snI--;
  //     // } else if (snI == sum_neg_I.size() - 1 && test == sum_neg_I[snI]) {
  //   } else if (snI == 0 && test == sum_neg_I[snI]) {
  //     // DBGLN("HELLO???????");
  //     sum_neg_I = {};
  //     snI = 0;
  //   }
  //
  //   if (spR < sum_pos_R.size() - 1 && test == sum_pos_R[spR]) {
  //     spR++;
  //   } else if (spR == sum_pos_R.size() - 1 && test == sum_pos_R[spR]) {
  //     sum_pos_R = {};
  //     spR = 0;
  //   }
  //
  //   if (0 < snR && test == sum_neg_R[snR]) {
  //     snR--;
  //     // } else if (snR == sum_neg_R.size() - 1 && test == sum_neg_R[snR]) {
  //   } else if (snR == 0 && test == sum_neg_R[snR]) {
  //     sum_neg_R = {};
  //     snR = 0;
  //   }
  //
  //   // } else {
  //   //   if (spI < sum_pos_I.size() - 1)
  //   //     spI++;
  //   //   if (0 < snI)
  //   //     snI--;
  //   //   if (spR < sum_pos_R.size() - 1)
  //   //     spR++;
  //   //   if (0 < snR)
  //   //     snR--;
  //   // }
  //   // }
  //
  //   // if (spI == sum_pos_I.size() - 1 && spR < sum_pos_R.size() - 1 && snI
  //   == 0
  //   // &&
  //   //     snR == 0) {
  //   //   end_attempts++;
  //   // }
  // }

  // ll si = -1;
  // II(i, n) {
  //   if (a[i] != 1 && a[i] != -1) {
  //     si = i;
  //     break;
  //   }
  // }
  //
  // // ordered set / auto-orders it in ascending order
  // // set<ll> sums;
  // unordered_set<ll> sums;
  //
  // DBG_ITER(a);
  // DBGLN(si);
  // if (si == -1) {
  //   ll running_max = 0;
  //   ll global_max = 0;
  //   ll running_min = 0;
  //   ll global_min = 0; // likely to be negative
  //   II(i, n) {
  //     if (a[i] == 1) {
  //       running_max++;
  //       global_max = max(global_max, running_max);
  //
  //       running_min = min(running_min + 1, 0LL);
  //     } else if (a[i] == -1) {
  //       running_max = max(running_max - 1, 0LL);
  //
  //       running_min--;
  //       global_min = min(global_min, running_min);
  //     }
  //   }
  //
  //   DBGLN("si == -1", global_min, global_max);
  //   for (ll k = global_min; k <= global_max; k++) {
  //     sums.insert(k);
  //   }
  // } else {
  //   // special group (*) exists
  //
  //   // bruteforce
  //   ll offset = 1;
  //   while (offset >= 0) {
  //     ll L_running_max = 0;
  //     ll L_global_max = 0;
  //     ll L_running_min = 0;
  //     ll L_global_min = 0;
  //     ll R_running_max = 0;
  //     ll R_global_max = 0;
  //     ll R_running_min = 0;
  //     ll R_global_min = 0;
  //     ll G_running_max = a[si];
  //     ll G_global_max = a[si];
  //     ll G_running_min = a[si];
  //     ll G_global_min = a[si];
  //
  //     if (offset == 0) {
  //       if (a[si] > 0) {
  //         L_running_max = a[si];
  //         L_global_max = a[si];
  //         R_running_max = a[si];
  //         R_global_max = a[si];
  //         // also needs to reset the min also
  //         L_running_min = a[si];
  //         L_global_min = a[si];
  //         R_running_min = a[si];
  //         R_global_min = a[si];
  //       } else if (a[si] < 0) {
  //         L_running_min = a[si];
  //         L_global_min = a[si];
  //         R_running_min = a[si];
  //         R_global_min = a[si];
  //         // same thing as above (reset the max also)
  //         L_running_max = a[si];
  //         L_global_max = a[si];
  //         R_running_max = a[si];
  //         R_global_max = a[si];
  //       }
  //     }
  //
  //     // bool max_stop = false;
  //     // bool min_stop = false;
  //
  //     // for (ll i = si - offset; 0 <= i; i--) {
  //     for (ll i = si - 1; 0 <= i; i--) {
  //       if (a[i] == 1) {
  //         // if (!max_stop)
  //         L_running_max++;
  //         L_global_max = max(L_global_max, L_running_max);
  //
  //         if (offset == 0) {
  //           L_running_min++;
  //           if (L_running_min > 0) {
  //             // break;
  //             // you can't reset if we assume a[i] to be selectedi this
  //             // subcase min_stop = true;
  //           }
  //         } else {
  //           L_running_min = min(L_running_min + 1, 0LL);
  //         }
  //       } else if (a[i] == -1) {
  //         if (offset == 0) {
  //           L_running_max--;
  //           if (L_running_max < 0) {
  //             // break;
  //             // max_stop = true;
  //           }
  //         } else {
  //           L_running_max = max(L_running_max - 1, 0LL);
  //         }
  //
  //         // if (!min_stop)
  //         L_running_min--;
  //         L_global_min = min(L_global_min, L_running_min);
  //       }
  //     }
  //
  //     // reset flags
  //     // max_stop = false;
  //     // min_stop = false;
  //
  //     // for (ll i = si + offset; i < n; i++) {
  //     for (ll i = si + 1; i < n; i++) {
  //       DBGLN(i, a[i], n);
  //       if (a[i] == 1) {
  //         // DBGLN("HELLO?", R_global_max, R_running_max);
  //         // if (!max_stop)
  //         R_running_max++;
  //         R_global_max = max(R_global_max, R_running_max);
  //         // DBGLN("??HELLO?", R_global_max, R_running_max);
  //
  //         if (offset == 0) {
  //           R_running_min++;
  //           if (R_running_min > 0) {
  //             // break;
  //             // do nothing (breaking affects pre-mature termination
  //             // for--say--the max)
  //             //
  //             // do nothing as in no min to 0 (just leave it as it is or
  //             // increase => NOP)
  //             //
  //             // because R_running_min-- still runs we need a flag
  //             // min_stop = true;
  //           }
  //         } else {
  //           R_running_min = min(R_running_min + 1, 0LL);
  //         }
  //       } else if (a[i] == -1) {
  //         if (offset == 0) {
  //           R_running_max--;
  //           /*             if (L_running_max < 0) { */
  //           if (R_running_max < 0) {
  //             // break;
  //             // max_stop = true;
  //           }
  //         } else {
  //           R_running_max = max(R_running_max - 1, 0LL);
  //         }
  //
  //         // if (!min_stop)
  //         R_running_min--;
  //         R_global_min = min(R_global_min, R_running_min);
  //       }
  //     }
  //
  //     DBGLN(L_global_min, L_global_max, R_global_min, R_global_max);
  //
  //     for (ll k = L_global_min; k <= L_global_max; k++) {
  //       sums.insert(k);
  //     }
  //     for (ll k = R_global_min; k <= R_global_max; k++) {
  //       sums.insert(k);
  //     }
  //     if (offset == 0) {
  //       // special case, when we include the special element, we can combine
  //       // both ranges
  //       //
  //       //  => but technically don't we need the stops???
  //       //
  //       //  remember, we're not optimizing for the EXTREMES, we're optimizing
  //       //  for the MOST AMOUNT OF UNIQUE #s we can obtain
  //       //
  //       //  and the 0s just means we would have the min to handle it
  //       //
  //       //
  //       //  but what if both mins and maxs touched 0???
  //       //
  //       //  omg just do a simple sum with it included for goodness sake
  //       //
  //       //  or a simple range with the special (*) included it
  //       //
  //       //  wait aren't we already doing with the offset==0 ????????????/
  //       //
  //       //  yes
  //       //
  //       //  so the new max range is really
  //       //          NOT [min(L_global_min, R_global_min), max(L_global_max,
  //       //          R_global_max)]
  //       //
  //       //      BUT RATHER...
  //       //          honestly just do the whole thing again but combined
  //       //
  //
  //       for (ll i = 0; i < n; i++) {
  //         DBGLN(i, a[i], n);
  //         if (a[i] >= 1) {
  //           // DBGLN("HELLO?", R_global_max, R_running_max);
  //           // if (!max_stop)
  //           G_running_max += a[i];
  //           G_global_max = max(G_global_max, G_running_max);
  //           // DBGLN("??HELLO?", R_global_max, R_running_max);
  //
  //           if (offset == 0) {
  //             G_running_min += a[i];
  //             if (G_running_min > 0) {
  //               // break;
  //               // do nothing (breaking affects pre-mature termination
  //               // for--say--the max)
  //               //
  //               // do nothing as in no min to 0 (just leave it as it is or
  //               // increase => NOP)
  //               //
  //               // because R_running_min-- still runs we need a flag
  //               // min_stop = true;
  //             }
  //           } else {
  //             G_running_min = min(G_running_min + a[i], 0LL);
  //           }
  //         } else if (a[i] <= -1) {
  //           if (offset == 0) {
  //             G_running_max += a[i];
  //             /*             if (L_running_max < 0) { */
  //             if (G_running_max < 0) {
  //               // break;
  //               // max_stop = true;
  //             }
  //           } else {
  //             G_running_max = max(G_running_max + a[i], 0LL);
  //           }
  //
  //           // if (!min_stop)
  //           G_running_min += a[i];
  //           G_global_min = min(G_global_min, G_running_min);
  //         }
  //       }
  //
  //       for (ll k = G_global_min; k <= G_global_max; k++) {
  //         sums.insert(k);
  //       }
  //     }
  //
  //     offset--;
  //   }
  // }
  //
  // vll sums_v(sums.begin(), sums.end());
  // ST(sums_v);
  //
  // O(sums_v.size());
  // OIT(sums_v);
  ;
}
