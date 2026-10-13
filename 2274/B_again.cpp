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
    v_ps[i] = v_ps[i - 1] + v_in[i];                                           \
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
//
// quadratic DP?
// 2D DP?
// considering n<=50
//
//
//
// . . . . .
// . . . . .
// . . . . .
// . . . . .
// . . . . .
//
//  a1         a1-a2       a1+a2-a3
//  a1-a2      a1+a2       a1-a2+a3
//  a1+a2-a3   a1-a2+a3    a1+a2+a3
//
//  2^n combination
//
//  as n++, there are more combination of whether to use +/-
//  but this 2D DP would only have space for 2n-1 or something along those lines
//
//  => doesn't work
//
//
//  just let s be more extreme?
//      => problem, the new element would be incporated as the next element's s
//          with all the previous element
//
//  but also, if an element itself is large enough then we prioritize that
//  element over the sum... (some obscured observation on trade-offs)
//
// again
//
// a1
// a2+a1 a2-a1
// a3+a2+a1+a1 a3+a2-a1+a1 a3-a2-a1-a1 a3-a2+a1-a1
//
//  observation: this goes back to the original rubber band / fish-tailing / or
//  whatever *that* observation was called
//      we always want all +'s or all -'s
//                         ^ maintaining positive values all the way
//                                    ^ maining raw negative values all the way
//      however, some elements' value might be negative which sort of cancels
//              with other elements' value (in the raw-space)
//                  despite the +'s and -'s are all the same (op-space)
//
//                  since this is assuming if all elements are positive (which
//                  has an easier solution)
//
//  so what now with elements being negative/positive? or, rather, the previous
//  observation (B.cpp) ACTUALLY TRIED to refer to the raw-space not the
//  op-space which resulted in sub-optimal solution??
//
//  2^50??? 100^50???
//
//
// a3  a2  a1  a1
//   +3  +2  +3
//
// a4  a3  a2  a1  a1  a2  a1  a1
//   +4  +3  +2  +3  +4  +2  +4
//
// a5  a4  a3  a2  a1  a1  a2  a1  a1  a3  a2  a1  a1  a2  a1  a1
//   +5  +4  +3  +2  +3  +4  +2  +4  +5  +3  +2  +3  +5  +2  +5
//    |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
//    |   |   |       |   |       |   |   |       |   |       |
//    |   |               |       |   |               |       |
//    |_______________________________|_______________|_______|
//
//
// DP????
//
// waiiiiit
// wait
// wait
// wait
//
// quadratic??
//
// key anti-observation:
//      if a later element is to be incporated,
//          a different +/-'s would work better?
//
//          NO?
//
//   look at the +3 (for example)
//
//  2^50??? (too large)
//
// dp[x] = mmm
//
// rewrite
//
// a5:     +5 a4
//         +5 a3
//         +5 a2
//         +5 a1
//      +5 +4 a3
//      +5 +4 a2
//      +5 +4 a1
//   +5 +4 +3 a2
//   +5 +4 +3 a1
//      +5 +3 a2
//      +5 +3 a1
//+5 +4 +3 +2 a1
//   +5 +4 +2 a1
//   +5 +3 +2 a1
//      +5 +2 a1
//
//
// +5 +4 +3 +2 a1
// +5 +4       a3
// +5 +4       a2
// +5 +4       a1
// +5 +4 +3    a2
// +5 +4 +3    a1
// +5    +3    a2
// +5    +3    a1
// +5 +4    +2 a1
// +5    +3 +2 a1
// +5       +2 a1
// +5          a4
// +5          a3
// +5          a2
// +5          a1
//
//
//
//
// +5          a4
// +5          a3
// +5          a2
// +5          a1
// +5 +4       a3
// +5 +4       a2
// +5 +4       a1
// +5 +4 +3    a2
// +5 +4 +3    a1
// +5 +4 +3 +2 a1
// +5 +4    +2 a1
// +5    +3    a2
// +5    +3    a1
// +5    +3 +2 a1
// +5       +2 a1
//
// trees?
//
// no observation to be made??
//
//
//
// per chatgpt
//
//
// we do want the extremes and actually we do want to apply either the -s or +s
// operation at every index.
//
// key insight: ??

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n);
  IVLL(a, n);

  ll mn = min(0LL, a[0]); // prefix sum min (at most 0)
  ll mx = max(0LL, a[0]); // prefix sum max (at least 0)
  ll ans = a[0];
  // i=0 cannot perform this operation
  for (ll i = 1; i < n; i++) {
    // if elements have been all negative
    //      a[i]-mn keeps option open
    ans = max(ans, max(a[i] - mn, a[i] + mx));

    // mn = {a[i] + mn - s, a[i] + mn, a[i] + mn + s}
    //           where s=mn in this case
    //
    // recall the min/max assumption of them, this means the 2*mn would
    // intrinsically be 0 or negative and opposite goes for 2*mx
    //
    // notice, if there's a super negative element, it is unavoidable (must be
    // taken account regardless) which mn helps (instead of mx)
    //
    // when mx becomes negative, on the next operation, a -s operation negates
    // it (hence, the 0LL in the max) and basically replace prior bad mx with a
    // new element a[i] in hopes of better values
    //
    // this is basically same with mn:
    //          negative elements? continnue please!
    //          if elements keep getting up or very positive => scratch it
    //          everytime until it can start accumulating negative values
    //     the 2x factor just means support the current sign (+/-) of the mn/mx
    // while prefix-ing/DP-ing makes this elegant and concise, did we really
    // need this prefix?
    //      well, it's not really an abstraction of the problem but rather the
    //      problem statement itself
    //
    //      why prefix?
    //
    //
    // if we just write out the relation itself (i.e., EXPAND THE DECISION)
    //
    // a[i] = a[i] - s
    // a[i] = a[i]
    // a[i] = a[i] + s
    //
    //  =>
    //
    // a[i] + s = a[i]
    // a[i] + s = a[i] + s
    // a[i] + s = a[i] + 2s
    //
    // so really there's no intuitive/conceptaul observation but more of a
    // text/mathematical/logical observation to be aware of that INCORPORATES
    // PREVIOUS DECISION (the +s on the LHS) whereas updating a[i] towards
    // itself treats each decision independently and requires extensive
    // exponential case-by-case checking
    //
    // AGAIN, the +s on the LHS incorporates prior decision
    //
    // AGAIN, it transforms the problem to how does one maximize the sum (that
    // incorporates all the individual element's +/- decision) and importantly
    // the NOP can easily be represented also (no op)
    //
    // again, it is because the PROBLEM is asking how does one find the max, but
    // there's the prefix sum explicitly stated that influences which
    // elements/decision-factor => work in the PREFIX-SUM-SPACE no in
    // element-wise space
    //
    // in other words, the sum is the lowest common denominator (i.e.,
    // hardest/most-complex portion of the problem) and hence takes the priority
    // in the abstraction of the solution and also because it can easily include
    // the formulation for no-decision
    mn = a[i] + min(0LL, 2 * mn);
    mx = a[i] + max(0LL, 2 * mx);
  }
  // ans = max(ans, max(a[n - 1] - mn, a[n - 1] + mx));

  O(ans);
  ;
}
