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

// start: 1613
//   end: 1815

// 4132423432241231
//  132 23 322 1231
//  13     3   1 31

// O.1: 4 must be removed
// O.2: 2 can be very problematic, 12x 21 32x 23 ==> 2 can never come after 1/3
//              OR 1/3 can never come before 2 (depending on min. amnt of el.
//              removed)
//      O.2/1:  12x  21 <- works SINCE always ends with 1/3 (absolutely not
//      divisble by 4)
//              32x  23 <- ""
//                 22* <- 2*1 + 2*10 + 2*100 + 2*1000 (for *10, *100, ...,
//                 they're all divisble 4, but the +2 in the beginning shifts it
//                 and infinitely always NOT divisble by 4) ==> safe option
//
//                 212 = 200+12 => not safe/beautiful
//                 232 = 200+32 => not safe/beautiful
//                      => 2*[1/3]2 => not beautiful (since the first 2
//                      represents a number >=20,200,... => always divisble by
//                      4) and 12 or 32 as the last two digit ==> not beautiful
//                 2332 = 2000+11*30+2 => not beautiful (the 11*30 is beautiful
//                      but the +2 shift it to be not beautiful)
//                 2112 = 2000+120-8 => not beautiful
//                 2312 = 2000+3*100+12 => not beautiful
//                 2132 = 2000+100+32 => not beautiful
//                      re-standardize the argument
//                          2332 = 2000+3*100+32
//                          2112 = 2000+1*100+12
//                          2312 = 2000+3*100+12
//                          2132 = 2000+1*100+32
//      O.2/2: even though 10 is not divisble by 4, 100,1000,and above ARE
//          divisbly by 4 => we don't look at the last digit but we look at the
//          last TWO digit dumbass (common 4-divisbility rule)
// O.3: 2 can ONLY exist in the begininning (repeatable to whatever
//      CONTINUOUS/UNBROKEN length)
//          by the observation of 12x and 32x, *12 and *32 will not work
//          (including itself) => no 2 can exist after 1/3
//          but 1/3 can appear in any random order (AFTER THE 2s) since the
//          indivisbility by 2 (not to mention 4)
//      remember, this is a min-op question, not validity question. in what case
//      can 2 exist? regardless of what length, 2 absolutely cannot occur at the
//      end, not even a single 1/3 before (i.e., no tradeoffs to consider)
//          actually, THERE EXISTS A TRADEOFF... consider the next observation
// O.4: 22* exist (actually, it's a specialization of before)
//              this emphasizes a trade-off of whether to remove all 2s AFTER
//              1/3 break
//                  OR remove ALL the 1/3 of the 1/3 break
//
// IMPL:
//      count 4s
//      count 2s after a 1/3 break (2s in the beginning can always exist without
//      tradeoffs)
//      count 1/3s for every 1/3 break (aggregated, not by breaks)
//      the counts represents removal ops and to find the min. # of el that
//      needs to be removed we just find the min count between 2s after 1/3
//      break and 1/3s within every 1/3 break
// edge case: instead of either removing twos after break 1/3 or just break
// 1/3s,
//      there exists an edge case where 2s and the FIRST 1/3 break co-exist but
//      later BOTH 2s and 1/3 breaks cannot.
//
// edge case generalized:
//      actually, what we care about is the groups of 2s and groups of 1/3s and
//      how to best minimize ops (not because they're right after the start or 2
//      after the start but can be N after the start)
//          this mean the first very short-lengthed 2s (and short-lengthed 1/3s)
//          can be removed in favor of second group of largers 2s follwoed by
//          1/3s that would've saved ops
//
// IMPL 2.0:
//      instantiate vll with a count of the lengths of the group that are
//      ASSUMED to be alternating and ALWAYS starts with 2s (i.e., set 0 if the
//      s starts with 1/3s only)
//          find the largest groups of 2s and its corresponmding 1/3s (that
//          always exists AFTER) that should be saved
//              and subtract it from the sums of lengths of other groups (since,
//              by implication, saving other pairs of 2s and 1/3s group will be
//              more ops-intensive)
//      so the vll is really just groups of 2s alternated with groups of 1/3s
//      by the observation that 1/3s followed by 2s cannot exist,
//          this vll that "alternates" can just be fixed to the length of groups
//          of 2s FOLLOWED by 1/3s

// actually, we could also remove all the 2s or 1/3s (so like 3-way but the 2s
// followed by 1/3s is the most complicated and the whole three-way is
// complicated)
// ^^ ~~~~~~~~

// technically speaking the optimal method is to find the largest 2 followed by
// 1/3 group (usual)
//      and remove all 1/3s before the 2 group and 2s after the 1/3 group
//          99% sure this is the most general form
// maybe just do it for every group? sort it. and find it like that?

// IMPL 3.0:
//      vll group2;
//      vll group13;
//      vll pre_group13;
//      vll suf_group2;
//
//      ll min_ops
//      for i:
//          keep group2[i] and group13[i]
//          remove pre_group13[i-1] and suf_group2[i+1]
//          test min_ops by pre13 + suf2

void solve([[maybe_unused]] ll T) {
  READ_S(s); // strings of 1,2,3,4

  ll fours = 0;
  vll group2 = {0};
  vll group13 = {0};
  vll pre_group13 = {0}; //  [0 . . . . .]
  dll suf_group2 = {0};  //  [. . . . . 0]

  bool prev13 = false;
  for (char &c : s) {
    if (c == '4') {
      fours++;
    } else {
      if (c == '2') {
        if (prev13) {
          prev13 = false;
          pre_group13.push_back(pre_group13.back() + group13.back());
          group2.push_back(0);
          group13.push_back(0);
        }
        group2.back()++;
      } else {
        group13.back()++;
        prev13 = true;
      }
    }
  }
  pre_group13.push_back(pre_group13.back() + group13.back());

  for (ll i = group2.size() - 1; i >= 0; i--) {
    suf_group2.push_front(group2[i] + suf_group2.front());
  }

  ll min_ops = LLONG_MAX;
  if (group2.size() > 0) {

    INC(i, group2.size()) {
      DBGLN(i, pre_group13[i], suf_group2[i], group13[i], group2[i]);
      min_ops = min(min_ops, fours + pre_group13[i] + suf_group2[i + 1]);
    }

  } else { // if empty or just 4s
    min_ops = fours;
  }
  OUT(min_ops);

  // ll fours = 0;
  // ll sum_123s = 0;
  // ll remove_2s = 0;
  // ll remove_13s = 0;
  // vll gl; // length of every group that counts 2s followed by 1/3s
  // bool prev_13 = true;
  // for (char &c : s) {
  //   if (c == '4') {
  //     fours++;
  //   } else {
  //     sum_123s++;
  //     if (c == '2') {
  //       if (gl.size() == 0) {
  //         // clean set of 2s with no earlier 1/3
  //       } else {
  //         remove_2s++;
  //       }
  //       if (prev_13) {
  //         prev_13 = false;
  //         gl.push_back(0);
  //       }
  //       gl.end()++;
  //     } else {
  //       prev_13 = true;
  //       gl.end()++;
  //     }
  //   }
  // }
  //
  // if (gl.size() > 0) {
  //   sort(gl.begin(), gl.end()); // smallest to largest
  //   OUT(fours + sum_123s - gl.back());
  // } else {
  //   OUT(fours);
  // }

  // ll fours = 0;
  // ll twos_after_break13 = 0;
  // ll break13s = 0;
  // ll later_twos_and_break13 = 0;
  // bool broken = false;
  // bool first_broken_end = false;
  // for (char &c : s) {
  //   if (c == '4') {
  //     fours++;
  //   } else {
  //     if (c == '1' || c == '3') {
  //       break13s++;
  //       broken = true;
  //       if (first_broken_end) {
  //         later_twos_and_break13++;
  //       }
  //     } else if (broken && c == '2') {
  //       twos_after_break13++;
  //       first_broken_end = true;
  //       later_twos_and_break13++;
  //     }
  //   }
  // }
  // OUT(fours + min(min(twos_after_break13, break13s),
  // later_twos_and_break13));
}
