#include <bits/stdc++.h>
#include <cstdlib>

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using vll = std::vector<ll>;
using dll = std::deque<ll>;
using pll = std::pair<ll, ll>;
using vpll = std::vector<pll>;

const ll NEG = (long long)-4e18;
const ll MOD = 998244353;

// prefix sum
#define PS(v_ps, v_in)                                                         \
  vll v_ps(v_in.size() + 1, 0);                                                \
  for (ll i = 0; i < v_in.size(); i++) {                                       \
    v_ps[i + 1] = v_ps[i] + v_in[i];                                           \
  }

// suffix sum
#define SS(v_ss, v_in)                                                         \
  vll v_ss(v_in.size() + 1, 0);                                                \
  for (ll i = v_in.size() - 1; i >= 0; i--) {                                  \
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

// start: xx 1207
//   end: xx

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
// how is this hard?? => same op-set => can only apply op on positive index =>
//      consider trade-offs against the would-be positives (negatives)
//
// O.1: one-way; anything right of the LAST (+) el. are inaccessible
// H.1: DP???????/
//
//          2 -10 -11   3 -10  15  7 18 16 17 -9
//          2 -8  -19 -16 -26 -11 -4 14 30 47 38
//
//          prefix-sum
//              dp[i] = dp[i-1]+a[i]
//              dp[i] = max(dp[i], -dp[i]) if before the LAST positive el.???
//
//          OR, excluding elements AFTER the last positive el.
//              reverse_dp[i] = reverse_dp[i]+negation_factor*a[i+1]
//              do =max(reverse_dp[i], -reverse_dp[i]) if negation_factor*a[i]>0
//              if negation is chosen:
//                  negation_factor *= -1
//
//          => what this is essential doing is find which RIGHT
//                  OFFSET-DIFFERENCE is optimal in an aggregated way before
//                  ADDING the OPTIMAL RIGHT OFFSET-difference to the LEFT
//                  (REST-OF-THE array) SUM (which we do NOT know if its
//                  optimal)
//                      BECAUSE the OP works from LEFT of the index-of-interest
//                      in an aggregated, left-monotonic way... the aggregation
//                      is too complicated and work piece-by-piece in an
//                      reverse-monotonic way to find the RIGHT-OPTIMAL amount
//               hold up, why do we want to find the optimal first from the LAST
//               INDEX OF POSITIVE to first?
//                  a
//          RECALL, we need to find the ops,
//              ops APPEND @[i] when negation is chosen (index-inclusive)
//

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n);
  IVLL(a, n);

  vll ps_abs(n + 1, 0);
  for (ll i = 0; i < n; i++) {
    ps_abs[i + 1] = ps_abs[i] + abs(a[i]);
  }

  SS(ss_sum, a);

  DBG_ITER(ps_abs);
  DBG_ITER(ss_sum);

  ll max_sum = ss_sum[0];    // default sum
  ll corresponding_ind = -1; // 0@
  II(i, n) {
    DBGLN(max_sum, corresponding_ind);
    if (a[i] > 0) {
      // ps_abs 1@, we're at 0@
      // ss_sum 0@
      if (max_sum < ps_abs[i + 1 - 1] - a[i] + ss_sum[i + 1]) {
        max_sum = ps_abs[i + 1 - 1] - a[i] + ss_sum[i + 1];
        corresponding_ind = i;
      }
    }
  }

  DBGLN(max_sum, corresponding_ind);

  // from C1
  dll ops;
  if (corresponding_ind != -1) {
    a[corresponding_ind] *= -1; // ad-hoc fix idk why it works

    ops.PF(corresponding_ind + 1); // 0@->1@
    II(i, corresponding_ind) {
      if (a[i] > 0 == a[i + 1] < 0) { // sign-flip
        ops.PF(i + 1);
      }
    }
  }

  // // ll before_true_sum = 0;
  // // ll first_pos_sum = 0;
  // // ll first_pos_ind = -1;
  // // bool immutable_last_neg = true;
  // // bool before_first_pos_sum = false;
  // //
  // // DD(i, n) {
  // //   if (a[i] > 0 && immutable_last_neg) {
  // //     immutable_last_neg = false;
  // //     first_pos_sum += a[i];
  // //     first_pos_ind = i; // 0@
  // //   } else if (a[i] > 0 && !before_first_pos_sum) {
  // //     first_pos_sum += a[i];
  // //   } else if (a[i] < 0 && !before_first_pos_sum &&
  // !immutable_last_neg) {
  // //     before_first_pos_sum = true;
  // //     before_abs_sum += abs(a[i]);
  // //     before_true_sum += a[i];
  // //   } else if (before_first_pos_sum && !immutable_last_neg) {
  // //     before_abs_sum += abs(a[i]);
  // //     before_true_sum += a[i];
  // //   }
  // // }
  // //
  // // DBGLN(before_abs_sum, first_pos_sum, before_true_sum,
  // //       first_pos_sum + before_true_sum);
  // //
  // // dll ops;
  // //
  // // if (before_abs_sum < first_pos_sum + before_true_sum) {
  // //   // choose the default (NOP)
  // // } else {
  // //   // choose the + + + + + ... + - (negate or minimize everything up
  // to the
  // //   // last positive number (exclusive) and then do an op on the last
  // //   positive
  // //   // number)
  // //   //
  // //   // Hence, C1 as per the 2nd look of the soln.
  // //   // 0@ -> 1@ (inclusive index, shouldn't trigger the sign-flip at
  // the end)
  // //   ops.push_front(first_pos_ind + 1); // 0@->1@
  // //
  // //   II(i, first_pos_ind) {
  // //     if (a[i] > 0 == a[i + 1] < 0) { // sign-flip
  // //       ops.push_front(i + 1);
  // //     }
  // //   }
  // //
  // //   // of the course the solution mentions prefix/suffix array
  // // }
  //
  // // vll ps(n + 1, 0); // prefix sum
  // // II(i, n) { ps[i + 1] = a[i] + ps[i]; }
  // // ll running_sum = 0;
  // // vll ops;
  // // DD(i, n) {
  // //   if (a[i] < 0) {
  // //     running_sum += a[i];
  // //   } else { // positive => decide
  // //   }
  // // }
  //
  // vll g_nrm(1 + 0, 0);
  // vll g_abs(1 + 0, 0); // just align the g_abs to dp/move
  // vll g_ind(0 + 0, 0); // just align g_ind to g_abs (which aligns to
  // dp/move)
  //                      // g_ind is in 0-index
  // ll immutable_last_neg = 0;
  // bool close = false;
  //
  // for (ll i = n - 1; i >= 1; i--) {
  //   if (!close && a[i] > 0) {
  //     close = true;
  //     g_ind.push_back(i);
  //   } else if (!close && a[i] < 0) {
  //     immutable_last_neg += a[i];
  //   }
  //
  //   if (close) {
  //     if ((a[i] > 0) == (a[i - 1] > 0)) { // same sign
  //       g_nrm.back() += a[i];
  //       g_abs.back() += abs(a[i]);
  //     } else { // different sign on the i-1
  //       g_nrm.back() += a[i];
  //       g_abs.back() += abs(a[i]);
  //       g_nrm.push_back(0);
  //       g_abs.push_back(0);
  //       g_ind.push_back(i - 1);
  //     }
  //   }
  // }
  // // if (!close && a[0] > 0) {
  // //   // have yet to be closed but a positive?
  // //   g_ind.push_back(0);
  // // } else
  // //
  // if (!close && a[0] < 0) {
  //   // have yet to be closed all the way through (all negatives)
  //   O(0);
  //   O("");
  //   return;
  // } else if (close) {
  //   g_nrm.back() += a[0];
  //   g_abs.back() += abs(a[0]); // if different sign, the loop wouldve
  //   created
  //                              // a new element to increment on
  // } else if (!close) {
  //   // all negatives until the last positive at the first index
  //   g_nrm.back() = a[0];
  //   g_abs.back() = abs(a[0]);
  //   g_ind.push_back(0);
  //   close = true; // does nothing, but make the logic more readable
  // }
  //
  // reverse(g_nrm.begin(), g_nrm.end());
  // reverse(g_abs.begin() + 0, g_abs.end());
  // reverse(g_ind.begin() + 0, g_ind.end());
  //
  // // g_ind,g_abs,immutable_last_neg properly filled
  // DBG_ITER(g_ind);
  // DBG_ITER(g_abs);
  // DBG_ITER(g_nrm);
  // DBGLN(immutable_last_neg);
  //
  // PS(ps_abs, g_abs);
  // SS(ss_sum, g_nrm);
  //
  // DBG_ITER(ps_abs);
  // DBG_ITER(ss_sum);
  //
  // // since the maximal way to make many elements + is to make all
  // elements left
  // // of certain index all positive (which probably what led the solution
  // from
  // // the tutorial)
  //
  // ll max_sum_config = 0;
  // ll corresponding_pos_ind = 0;
  //
  // II(i, g_nrm.size()) {
  //   if (g_nrm[i] > 0) {
  //     if (max_sum_config < ps_abs[i] - g_nrm[i] + ss_sum[i + 1]) {
  //       max_sum_config = ps_abs[i] - g_nrm[i] + ss_sum[i + 1];
  //       corresponding_pos_ind = g_ind[i];
  //     }
  //   }
  // }
  // // but sometimes even within a + group you want some of it to remain
  // positive
  // // while the other parts as negative... because it really depends on
  // each
  // // invidiaul index and which one within the + group (even the last +
  // group) it
  // // should sacrifice...............
  // // ==> really just prefix sum on absolute, suffix sum on regular,
  // negation on
  // //            each positive numbers
  //
  // DBGLN(max_sum_config, corresponding_pos_ind);
  //
  // vll ops;

  //
  // // g_abs is already in 3@ where dp/move are in 3@
  // vll dp(g_abs.size(), 0);
  // vll move(g_abs.size(), 0);
  //
  // // dp on positive selection
  // for (ll i = 3; i < g_abs.size(); i++) {
  //   ll choice_a = dp[i - 3] - g_abs[i - 2] - g_abs[i - 1];
  //   ll choice_b = dp[i - 2] - g_abs[i - 1];
  //   DBGLN(i, choice_a, choice_b);
  //   if (choice_a <= choice_b) {
  //     // select choice_b for optimality (greedily maximizes so far)
  //     dp[i] = choice_b + g_abs[i];
  //     move[i] = -2;
  //   } else {
  //     // select choice_a
  //     dp[i] = choice_a + g_abs[i];
  //     move[i] = -3;
  //   }
  // }
  //
  // DBG_ITER(dp);
  // DBG_ITER(move);
  //
  // // compare which one maximizes (two choice) that selects the ops
  // // NOTICE: the first group is always positive so there's no point
  // in looking
  // //        at -2 which will always be a negative group dumbass
  //
  // ll j = g_abs.size() - 1;
  // // if (dp[dp.size() - 1] < dp[dp.size() - 2]) {
  // //   // if the second to the last element maximizes
  // //   j--;
  // // }
  //
  // // index of inversion (index of operation) finder (directly to ops)
  //
  // while (true) {
  //   if (move[j] == -3) {
  //     // +1 to convert g_ind's 0-index to ops 1-index
  //     ops.push_back(g_ind[j - 2] + 1);
  //   } else if (move[j] == 0) {
  //     break;
  //   }
  //   j += move[j]; // move is already in negative delta
  // }

  // vll dp(n + 1, 0);
  // ll neg_factor = 1;
  // DD(i, n) {
  //   if (neg_factor * a[i] < 0) { // if neg, just sum
  //     dp[i] = dp[i + 1] + neg_factor * a[i];
  //   } else { // start of next + group
  //     // start of the next group requires to decide whether
  //     negating it will be
  //     // optimal (maximize)
  //     //  however, since a negation of a group requires
  //     consideration of the
  //     //  negation of the WHOLE SUM of the group,
  //     //      this method is insufficient
  //     //          => requires a split by +,- groups (with the
  //     exclusion of the
  //     //                last - group)
  //     //    + - + - +
  //     //    - + - + -
  //     //    + - + - -
  //     //    - + - - -
  //     //    + - - - -
  //     //    - - - - -
  //     //    - + - - +
  //     //    + - + + -
  //     //    - + - - -
  //     //    + - - - -
  //     //    + - - - +
  //     //    - - + + -
  //     //    - - + - +
  //     //      - + - +
  //     //        + - +
  //     //          - +
  //     //          requires consideration over all possible +/-
  //     config
  //     //             AND where same amount of groups refers to
  //     same scenario
  //     //             (scenario only changes when group counts are
  //     different)
  //     //
  //     // by the nature of DP, we would like to find some
  //     directional invariance
  //     //    (does the decision only affect one of the side and
  //     not depend on the
  //     //    other side?)
  //     //
  //     //      let's suppose we go from the LEFT and say + - + is
  //     optimal, would
  //     //      the DIFFERENT CONFIG of later x x x make + - + no
  //     longer optimal?
  //     //      YES. since if the LATER (RIGHT-SIDE) can have
  //     different amount of
  //     //      negations, it could result in + - + to be - + -
  //     that would be set
  //     //      to LEAST optimal? (but not optimal nonetheless)
  //     //              + - + x x x
  //     //
  //     //      what about going from the RIGHT? say + - + is
  //     optimal and we don't
  //     //      know about x x x. trivially (by the inverse of
  //     previous logic),
  //     //      the NEGATION would not affect the right side. this
  //     is basically
  //     //      the same logic as before but something about the
  //     prev. statement
  //     //      seems off
  //     //              x x x + - +
  //     //
  //     //      oh yes the ambiguity of whether different RIGHT
  //     config of x x x
  //     //      could find a LEFT config that's more compatible &
  //     optimal like say
  //     //      - - +
  //     //
  //     //      KEY IDEA:
  //     //          if x1 x2 x3 + - + THEN x3 MUST be negative
  //     //            => we need to try x3 being positive => x1 x2
  //     x3 - ? ?
  //     //            => we need to find the RIGHT optimality of
  //     either case
  //     <--
  //     //            ??????????? (NO, ITS MORE COMPLICATED)
  //     //                  YET we also need to find the optimality
  //     of either case
  //     //                  of SINGLE LEFT for future
  //     //                  => we need DP that consider (from right
  //     to left
  //     /
  //     //                  reverse direction)
  //     //                      dp1 for [+ -] case (with the
  //     tracked op1)
  //     //                      dp2 for [- +] case (with the
  //     tracked op2)
  //     //                          and at the end compare which dp
  //     has higher
  //     //                          sums and use its ops
  //     //                        logically, this makes sense but
  //     how does that
  //     //                        visually work and how does one
  //     track such ops?
  //     //
  //     //                        actually, to be more logically
  //     specific
  //     //                          if we have                * * *
  //     +
  //     //                            dp1 would compare       * * +
  //     - OR
  //     //
  //     //                            dp2 would compare       * * -
  //     +
  //     //
  //     //                            actually, due to the rigidity
  //     of the
  //     //                            operations, it just applies
  //     to the whole
  //     //                            LEFT side so like
  //     //                        given/started-with * * * + -? x?
  //     //                        compare            - + - + -? x?
  //     OR
  //     //                                           + - + - -? x?
  //     //            ?=existence
  //     //                        again,
  //     //                                v
  //     //                        * * * * + -? . . .
  //     //                        - + - + - -? . . . OR
  //     //                        + - + - + -? . . .
  //     //                case 2  * * * * - +? (we can only operate
  //     on positives)
  //     // IN SUMMARY,
  //     //  for every START of the positive group => decide whether
  //     negation or
  //     //  not of all previous >>prefix<< sum would maximize the
  //     >>overall<< sum >>(with running sum)<< so prefix-sum before
  //     //  also and we can freely include the last negative group
  //     //  (immutable negation)
  //                    additional self-justification:
  //                          if negation of the prefix-sum is
  //                          optimal and decided that the earlier
  //                          index (later op) should be negated
  //                          again for further optimal, the
  //                          previous decision of negation must
  //                          still stand
  //                                  so like..
  //                                  * * * - + -? . . .
  //                                  - + - + - -? . . . <-- pick
  //                                  this
  //                                  + - + - + -? . . . xxx
  //                                  + - + - - -? . . . <-- this
  //                                  yields (if it found to be more
  //                                  optimal)
  //                                  - + - - - -? . . . <--
  //                                  continuing?
  //                                  - + - - + -? . . . <-- what
  //                                  about this??

  //                                compared to
  //                                  - + - + - -? . . . (which
  //                                  could easily be more
  //                                  optimal but failed to
  //                                  consider that) but by
  //                                  observation
  //
  //                                  - + - + - + -? . . .
  //                                  + - + - + - -? . . .
  //                                  (subset push down)
  //                                  + - + - - + -? . . .
  //                                  + - - + - + -? . . . ***
  //                                  - - - + - + -? . . .
  //                                  removal of a (+)
  //                                           section
  //                                            (if we cont.
  //                                            from ***)
  //                                  so any removal or
  //                                  shift-down of + is a valid
  //                                  state to test?
  //                                  + - + - - + -?
  //                                  + - - - - + -?
  //                                  - + - - - + -?
  //                                  - - - + - + -? <--
  //                                  completely UNoptimal when
  //                                  you can just leave it
  //                                  as...
  //                                  - + - + - + -?
  //                                  + - + - - + -? (can't
  //                                  really do anything about
  //                                  it if this optimal)
  //                                  - + - - - + -? UNoptimal
  //                                  compared to...
  //                                  - + - + - + -?
  //                                  + - - - - + -? UNoptimal
  //                                  compared to 2 options...
  //                                  + - + - - + -? or
  //                                  + - - + - + -?
  //
  //                                  maybe DP comparison over a
  //                                  larger atomic blocks?
  //
  //                              point of negation (operation)
  //                                     v   v
  //                                -? + - - + -? vs. =>
  //                                running_sum += a[i];
  //                                  -? + - + -?     =>
  //                                  running_sum += a[i];
  //                                -? + - + - -?     =>
  //                                running_sum += -a[i];
  //                                // the last case is just the
  //                                first case at a different
  //                                point (only makes sense as
  //                                an option for the last +) =>
  //                                there has to be an
  //                                easier/elegant way
  //
  //                                the last case could result
  //                                in + - - + -
  //                                - if we start the process
  //                                again from the 1st +
  //                                      =>
  //                                      wouldnt - + - + - + be
  //                                      better? (more
  //                                      +'s) who tf knows
  //                                      but obviously, + - - +
  //                                      - + would be optimal
  //
  //                                      + - + - + - + - + - +
  //                                      -? **
  //                                      - + - - + - - + - - +
  //                                      -?
  //                                      - + - + - + - + - + -
  //                                      -?
  //                                      + - + - + - + - - + -
  //                                      -?
  //                                      + - - + - - + - - + -
  //                                      -? (at most a spacing
  //                                      of 2 -'s and can start
  //                                      with +/-)
  //
  //                                      // any
  //                                      invariances.....
  //                                        wait wait wait isnt
  //                                        this just dp[i] =
  //                                        a[i] + max(dp[i-2],
  //                                        dp[i-3])
  //                                            but we need to
  //                                            find the OPS not
  //                                            the sum itself
  //                                            (doable if we
  //                                            track the
  //                                            ops...) or
  //                                            forward DP
  //                            dp[i] = a[i] + max(dp[i+2],
  //                            dp[i+3]) move_chosen[i] = 2 or 3
  //                            <-- i think this is fine
  //                            actually
  //                            // is there an easier
  //                            observation???????
  //
  //          b = elements in +/- groups absolutized (all
  //          elements positive) dp[i] = b[i] +
  //          max(dp[i-2]-b[i-1], dp[i-3]-b[i-1]-b[i-2]) compare
  //          dp[-1] and dp[-2] (since they represent two
  //          choices that never co-occur until at the very end)
  //                  AND
  //          move[i] = -2 or -3 (where the positives were
  //          selected) => how does
  //                one compute the index of sign inversion
  //                (index of operation)?  // there has to be an
  //                easier way
  //          // so now you know where's the optimal +'s, but
  //          how does one compute the sign inversion place?
  // (excluding the reference's last always negative group)
  //            x    -3    -3    -3
  //          - + - - + - - + - - + -
  //          + - + - + - + - + - + -
  //              ^     ^     ^
  //              NOTICE: sign changes does not happen on a -2
  //              since its just hopping on existing positives
  //              (or would be existing positives)
  //                  but -3 means sign reversion on the local
  //                  group (-2)'s last element
  // ***
  // ***
  // ***
  // ***
  // ***
  // ***
  // ***
  // ***
  // ***
  // ***
  // ***
  // ***
  // ***
  // ***
  // ***
  // ***
  // ***
  // ***
  // ***
  // ***
  // ***
  // ***
  // ***
  // ***
  // ***
  // ***
  // ***
  // ***
  // ***
  // ***
  // ***
  // ***
  // ***
  //  COMPLETE IMPL v2.0:
  //          abs_g = sum of elements split by +/- groups
  //          absolutized (all
  //                        elements set to be positive)
  //          ind_g = index of the last element (inclusive) of
  //          each group
  //
  //          dp[n+3] // with 3 initial 0s (3-index denoted as
  //          3@i, 1-index
  //                        should be 1@i, and 0-index should be
  //                        0@i)
  //          move[n+3]
  //          for(ll i=3; i<n+3; i++)
  //            dp[i] = b[i] + max(dp[i-2]-b[i-1],
  //            dp[i-3]-b[i-1]-b[i-2])
  //                  // select (-2) or (-3) as the previous
  //                  positive el.
  //            move[i] = -2 or -3 // (follow the choice of the
  //            max)
  //
  //          ll j = 1@n;
  //          while(true)
  //            if(move[3@j] == -3) {
  //            // another way to think about is -3 sort
  //                    of skips a positives or push down a
  //                    positive via sign inversion right before
  //
  //                ops.PB(ind_g[3@(j-2)])
  //            }
  //            j += move[3@j]
  //
  //          return ops
  //  END IMPL
  //
  //
  // consider test case 3
  //
  // 1 -3 2 -1 10
  // =>  + - + - +
  //
  // solution:
  //  + - + - +
  //  - - + - +
  //  + + - - + <-- this is actually possible since it's not
  //  whether the operation is LEFT only but the + -> -
  //  transition merges the + with the negative block... too
  //  lazy to fix this at this poitn
  //
  //
  //  >>>>        + - + - + -?
  //              - - + - + -?
  //              + + - - + -?
  //              - + - - + -?
  //              + - - - + -?
  //              - - - - + -?
  //              + + + + - -? or
  //              - - - - + -? ~~
  //              + - + - + -? << this
  //
  //              + - + - + - + - + -?
  //              - - + - + - + - + -?
  //              + + - - + - + - + -?
  //              - + - - + - + - + -?
  //              + - - - + - + - + -?
  //              - - - - + - + - + -?
  //              + + + + - - + - + -?
  // wait wait
  //
  //            + - + -?
  //            - - + -?
  //            + + - -?
  //            - + - -?
  //            + - - -?
  //            - - - -?
  //
  //  checking the solution for the 2nd time, it refers to C1 so
  //  instead of doing the binary counter thingy it's more like
  //  this
  //            + - + - + - + - + -?
  //            - + - + - + - - + -?
  //            + - + - + - - - + -?
  //            - + - + - - - - + -?
  //            + - + - - - - - + -?
  //            - + - - - - - - + -?
  //            + - - - - - - - + -?
  //            - - - - - - - - + -? <-- much simpler
  //            + + + + + + + + - -?
  //
  //
  //  and of course the solution is just a paragraph or so...
  //
  //  A C1/C2 PROBLEM SHOULD NOT BE THIS COMPLICATED, IF IS LIKE
  //  THIS COMPLICATED, THINK AGAIN SHOULD NOT BE THIS
  //  COMPLICATED SERIOUSLY
  //
  //  KEY INSIGHTS => INSTEAD OF GOING RIGHT TO LEFT, WE
  //  ACTUALLY WANT TO GO FROM LEFT TO RIGHT FOR MAXIMIZATION
  //  PURPOSES
  //
  //
  //                                  INVARIANT: there must
  //                                  exist a + after 3 elements
  //                                  of another + so reverse DP
  //                                  with prefix-sum on
  //                                  4-element atomic blocks??
  //
  //                                  IMPL:
  //                                  a
  //
  //                                  from xxx?
  //
  //                                    better result???
  //
  //                                    ~~~ KEY INSIGHT => THERE
  //                                    ARE NO REGRETFUL
  //                                    ~~ DECISION BECAUSE
  //                                    THEY'VE ALL BEEN
  //                                    ~~ CONSIDERED BEFORE
  //     dp[i] = dp[i - 1] + neg_factor * a[i];
  //     if (neg_factor * a[i] > 0) { // decision allowed
  //       if (dp[i] >= -dp[i]) {     // decided to NOP
  //       } else {                   // decided to NEGATE
  //         dp[i] *= -1;
  //         neg_factor *= -1;
  //       }
  //     }
  //   }
  // }
  O(ops.size());
  OIT(ops);
  ;
}
