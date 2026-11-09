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
  vpll a;                                                                      \
  for (ll i = 0; i < n; i++) {                                                 \
    ll ai, bi;                                                                 \
    std::cin >> ai >> bi;                                                      \
    a.push_back({ai, bi});                                                     \
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
// if x >= max(a)-min(a):
//      output 1
// if x >= max(a)-min(a)-a.size():
//      output 1??? (maybe output 2 because the border distances)
//
// abstraction:
//
// inter_el_distances[]
//
// @0,@n-1 must be included
// inter_el_distances
//
// or just distances[]
// @0,@n-1 must be included
//
// if a distance (inner only) is not to be included,
//  the adjacent distances MUST be included
//
// technically,
//  if x == a.size():
//      every elements can have an adjacent y cells => O(1)
//      (if a mutually-adjacent elements does not exist yet)
//
//  suppose z is the # of elements that are in groups of just themselves
//
//  if x >= z:
//      then every individual groups can become a mutually-adjacent groups
//      => O(1)
//
//  else:
//      means there will be some elements in the z[] that must remain in the
//      groups themselves (but then setting other elements to adjacent is not
//      optimal because the min k will never reach them when there's some higher
//      value present)
//
//      then we need to go from the largest distance (excluding the single
//      largest distance in the interior) and cut them into halves
//
//      but it also depends how large are they, if it is super large then its
//      probably best to have multiple x's to partition them just for that
//
//      .....
//
//      DP?
//
//      BS on answer?
//
//      MINIMUM k
//      if k works, then k+1 must work, but k-1 may not work
//          k (answer-space) is monotonic
//
//      but for each k, can we check it in a linear pass?
//          naive (assume x=0):
//              we check each distances and distances <=k => works
//
//              but this is too strict
//
//              MST?
//
//              we order the distances, (that would be nlogn * logn...)
//
//              dp?
//
//              dp on BS on ans?
//
//              knapsack?
//
//              // dp: x by distances
//
//              dp[x][i] = dp[x][i-1], dp[x][i]+dp[x][i-2]
//
//              // we either take the most recent distance and optimally omit
//              the most recent distance
//              // OR, we take the previous distance and optimally omit the
//              current (but then on the next step we might omit it again =>
//              needs longer range)
//
//              dp[x][i] = dp[x][i-2]+dp[x][i-1], do[x][i-2]+dp[x][i]
//
//              // say distances = [x y z w]
//              // if we're at z,
//                      we can take x,z
//                      or take x,y,z
//
//                      so on the next iteration,
//                      we can take y,w
//                      or take y,z,w
//
//                      because we guarantee @i and @i-2 are always taken
//                      (@i-2 always taken because DP at that point is always
//                      taken)
//
//                      actually, we should not conditionally take or not take
//                      the current but the previous
//
//                      so like
//
//                      we can take x,z
//                      or,         y,z
//
//                      so on the next iteration,
//                      we can take y,w
//                      or,         z,w
//
//                      since we always assume the current index is taken, we
//                      can safely do the above operation (where the first
//                      element either @i-1 or @i-2 are assumed to be always
//                      take by themselves gauranteeing the distances to be
//                      valid)
//
//                      so waht now? how are we going to aggregate them?
//
//                      dp[x][i] = dp[x][i-2]+distances[i],
//                                 dp[x][i-1]+distances[i]
//
//                      this abstracts the decision of whether to take or skip
//                      but we still don't know how to aggregate them unless
//                      we're summing them on something
//                          (which includes skipping the largest max inner
//                          distance)
//
//                          minimize them?
//
//                      dp[x][i] = min(dp[x][i-2]+distances[i],
//                                     dp[x][i-1]+distances[i])
//
//                          and records the indices somehow??
//
//                          dp for k?
//
//                      dp[x][i] = min(max(dp[x][i-2],distances[i]),
//                                     max(dp[x][i-1],distances[i]))
//
//                      nononono
//
//                      we just need three arrays?
//
//                      remove chosen_distances[i-3]
//                      chosen_distances[i-2], chosen_distances[i-1],
//                      chosen_distances[i]
//
//                      taken chosen_distances[n-1]
//
//                          by this logic, we optimally choose which pairs (as
//                          distances) to minimize their distances (for k)
//
//                          minimize the INITIAL choice of distances
//
//                          BECAUSE,
//                              we if try to break those unchosen distances, it
//                              is unoptimal when we can allocate the same
//                              amount of x's to those chosen distances
//
//                       suppose optimally_selected_distances =
//                                  chosen_distances[n-1]
//
//                       i think this is B.S. on ans
//
//                       but once we optimally select these distances, we can
//                       sort them (we no longer care about the orders)
//
//                       start with k=optimally_selected_distances[n-1]
//                              or  k=osd[n-1]
//
//                       but now with x...
//
//                       it is optimal to always use all x if possible
//                       now suppose x<z:
//
//                       B.S. on levels of distances?
//
//
//                       suppose we start with the largest
//
//                       osd[n-1]
//                       what does it take to make it k?
//
//                       osd[n-1]/m <= k
//
//                          10/5 <= 2 (valid)
//                          14/5 <= 2 (valid)
//
//                          or we want the current osd[n-1] to be into as many
//                          groups of k-length as possible so
//
//                          osd[n-1]/k
//
//                          10/5 = 2 (needs 1 partition)
//                          14/5 = 2 (needs 1 partition?? nope, needs 2)
//
//                          ceil(10/5)=2
//                          ceil(11/5)=3
//
//                          0 1 2 3 4 5 6 7 8 9
//                          * * * * * ^ ^ ^ ^ ^
//
//                          0 1 2 3 4 5 6 7 8 9 10
//                          * - - - - * - - - - *
//
//                          (technically k=4 because k itself describes a
//                          distance so inclusive on both ends) (actually,
//                          because it is inclusive this would still need to be
//                          k=5)
//
//                          so ceil(osd[i]/k)-1 partitions
//
//                          NOTE: if we need 2 paritions we can just do
//                              * * - - - - - - - * *
//                              so max of 2 partitions
//
//                          actually, would it be always optimal to put 2 of
//                          them like that? or is there a tradeoff to spitting
//                          the distances in half?
//
//
//                          has to be simpler observation overall
//
//
// suppose x=1
//      we can also remove the largest by putting one extra y's into the
//      distance of the largest??
//
//
//
//!!!! per editorial
//! the only additional useful idea is just with a linear pass we just need to
//! check if any distances are <=2k (that means we can plop a *y* in the middle
//! to split it in halves of k,k) (reverse idea)
//
// but what about those y=a[i]+1 that "serves those lone bad cells"?
//
//
// if it is <=2k: x--
// if it is  >2k: x-=2
//
//  but what they mentioned is DISJOINT CONSECUTIVE PAIRS
//
// if there's a DISJOINT pair of cells with inter-cell distance of k+1=...=2k
//      then x--
//
// any extraneous lone bad cells
//      x--
//
// but why not >2k: x-=2 ??
//
// if its >2k: we basically treat them as individual cases
//
//  so what would've been disjoint pairs of cells with <=2k
//  becomes two lone bad-cells with both >k => x-- and x-- => x-=2
//
// so rather k+1=..=2k can be thought of as a special case
//  where we can conserve the amnt of x taken
//
// while <=k basically means its fine (valid)
//
// and >2k will just be individually handled
//
// but say
//
// *  *                     *  *
//
// by this logic, wouldnt we need x-=2?
//  when we can just pair the 1st and the 2nd pairs together ignoring the middle
//  gap?
//
// disjoint means exclusive to all k's that share at least one of its side with
//  <=k distance
//
// same thing thing when >2k
//
//  so we can just compare cell by cell or rather distance by distance (3-cells)
//  (i.e., per editorial "matching on path")
//
//  and can be locally greedy (no need for DP unless we're memoizing the sum of
//  some sort)
//
//

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;

  I(n, x);
  IV(a, n);

  vll d;
  II(i, n - 1) { d.PB(a[i + 1] - a[i]); }

  ll hi = a[n - 1] - a[0];
  ll lo = 1;
  ll mi;
  ll k;
  while (lo <= hi) {
    mi = lo + (hi - lo) / 2;

    vll status = d;
    II(i, d.size()) {
      if (d[i] <= mi) {
        status[i] = 1;
      } else if (d[i] <= 2 * mi) {
        status[i] = 2;
      } else if (2 * mi < d[i]) {
        status[i] = 3;
      }
    }

    // ll x_needed = 0;
    // ll bad_cells = mi < d[0] && d[0] <= 2 * mi ? 1 : 0;
    // ll lone_bad_cells = 2 * mi < d[0] ? 1 : 0;
    ll x_needed = 0;
    ll bad_cells = (status[0] == 2) ? 1 : 0;
    ll lone_bad_cells = (status[0] == 3) ? 1 : 0;

    II(i, d.size() - 1) {
      if (status[i] == 3 && status[i + 1] == 3) {
        lone_bad_cells++;
      } else if (status[i] >= 2 && status[i + 1] >= 2) {
        bad_cells++;
        if (status[i] == 2 && status[i + 1] == 2) {
        } else if (status[i] == 3 && status[i + 1] == 2) {
          x_needed += lone_bad_cells;
          lone_bad_cells = 0;
        } else {
          x_needed += bad_cells / 2 + bad_cells % 2;
          bad_cells = 0;
        }
      } else {
        x_needed += bad_cells / 2 + bad_cells % 2;
        x_needed += lone_bad_cells;
        bad_cells = 0;
        lone_bad_cells = 0;
      }
      // if (mi < d[i] && d[i] <= 2 * mi && mi < d[i + 1] && d[i + 1] <= 2 * mi)
      // {
      //   bad_cells++;
      // } else if (2 * mi < d[i] && 2 * mi < d[i + 1]) {
      //   lone_bad_cells++;
      // } else {
      //   // changing status of the distance
      //   // no consistent cell to be determined
      //   x_needed += bad_cells / 2 + bad_cells % 2;
      //   bad_cells = 0;
      //   x_needed += lone_bad_cells;
      //   lone_bad_cells = 0;
      // }
    }

    // bad_cells +=
    //     ((mi < d[d.size() - 1]) && (d[d.size() - 1] <= 2 * mi)) ? 1 : 0;
    // lone_bad_cells += (2 * mi < d[d.size() - 1]) ? 1 : 0;
    bad_cells += status[status.size() - 1] == 2 ? 1 : 0;
    lone_bad_cells += status[status.size() - 1] == 3 ? 1 : 0;
    x_needed += bad_cells / 2 + bad_cells % 2;
    x_needed += lone_bad_cells;

    DBGLN(x_needed, x, lo, hi, mi);

    if (x_needed > x) {
      // invalid
      lo = mi + 1;
    } else {
      // valid: try lower/smaller/tighter lengths
      hi = mi - 1;
      k = mi;
    }
  }

  O(k);

  // I(n, x);
  // IV(a, n);
  //
  // vll distances;
  // II(i, n - 1) { distances.PB(a[i + 1] - a[i]); }
  // // distances
  // vll d = distances;
  //
  // DBG_ITER(distances);
  //
  // ll hi = a[n - 1] - a[0];
  // // ll lo = 0;
  // ll lo = 1;
  // ll mi;
  // ll k;
  // while (lo <= hi) {
  //   mi = lo + (hi - lo) / 2;
  //
  //   ll x_needed = 0;
  //   // ll mi2s = mi < d[0] && d[0] <= 2 * mi ? 1 : 0;
  //   // ll mi2ss = 2 * mi < d[0] ? 1 : 0;
  //   ll bad_cells = mi < d[0] && d[0] <= 2 * mi ? 1 : 0;
  //   ll lone_bad_cells = 2 * mi < d[0] ? 1 : 0;
  //
  //   // II(i, distances.size()) {
  //   II(i, distances.size() - 1) {
  //     // DBGLN(i, distances[i], x_needed, mi2s, mi2ss);
  //
  //     if (mi < d[i] && d[i] <= 2 * mi && mi < d[i + 1] && d[i + 1] <= 2 * mi)
  //     {
  //       // mi2s++;
  //       bad_cells++;
  //     } else if (2 * mi < d[i] && 2 * mi < d[i + 1]) {
  //       // mi2ss++;
  //       lone_bad_cells++;
  //     } else {
  //       // changes, either <=mi->mi< <=2*mi
  //       // or <=2*mi-><2*mi
  //       //
  //       // whatever it is, during a change we don't add anything
  //
  //       x_needed += bad_cells / 2 + bad_cells % 2;
  //       // x_needed += mi2s / 2 + mi2s % 2;
  //       // mi2s = 0;
  //       bad_cells = 0;
  //       // x_needed += mi2ss - 1;
  //       // mi2ss = 0;
  //       x_needed += lone_bad_cells;
  //       lone_bad_cells = 0;
  //     }
  //
  //     // per chatgpt's insight as cell-by-cell rather than distances
  //
  //     // if ((mi < distances[i] && distances[i] <= 2 * mi && mi <
  //     distances[i]
  //     // &&
  //     //      distances[i + 1] <= 2 * mi) ||
  //     //     (i == 0 && mi < distances[0] && distances[0] <= 2 * mi) ||
  //     //     (i == distances.size() - 2 && mi < distances[i + 1] &&
  //     //      distances[i + 1] <= 2 * mi)) {
  //     //   mi2s++;
  //     // }
  //     //
  //     // if (distances[i] > 2 * mi) {
  //     //   // separator
  //     //
  //     //   x_needed += mi2s / 2 + mi2s % 2;
  //     //   mi2s = 0;
  //     // }
  //     //
  //     // if ((distances[i] > 2 * mi && distances[i + 1] > 2 * mi) ||
  //     //     (i == 0 && distances[i] > 2 * mi) ||
  //     //     (i == distances.size() - 2 && distances[i + 1] > 2 * mi)) {
  //     //   x_needed++;
  //     // }
  //     //
  //     // if (distances[i] <= mi) {
  //     //   // x_needed += mi2s / 2 + mi2s % 1;
  //     //   // if (x_needed > 0) {
  //     //   if (mi2s > 0) {
  //     //     x_needed += (mi2s - 1) / 2 + (mi2s - 1) % 2;
  //     //   }
  //     //   mi2s = 0;
  //     //   // because when we reach a <=mi block or coming from a <=mi
  //     //   // block-distance, the cell would prefer to use that distance to
  //     //   avoid
  //     //   // spending x, hence -1 on the RHS (and LHS depends on the first
  //     //   <=2*mi)
  //     //
  //     //   mi2ss = 0;
  //     // } else if (distances[i] <= 2 * mi) {
  //     //   if (i > 0 && distances[i - 1] <= mi) {
  //     //     // no-op
  //     //     // we'll let it slide since that cell would just use the mi side
  //     //   } else {
  //     //     mi2s++;
  //     //   }
  //     //   mi2ss = 0;
  //     // } else { // >2*mi
  //     //
  //     //   // x_needed += (mi2s - 1) / 2 + (mi2s - 1) % 2;
  //     //   x_needed += (mi2s) / 2 + (mi2s) % 2;
  //     //   mi2s = 0;
  //     //   // however, coming from the >2*mi side, <=2*mi si the preferred
  //     side
  //     //   // hence no -1
  //     //
  //     //   // if (i == 0 || i == distances.size() - 1) {
  //     //   if (i == 0 || i == distances.size() - 1) {
  //     //     // while for both <=mi case and <=2*mi case, they implicitly
  //     //     // handle the boundary cases (e.g., the x_needed incremeents
  //     after
  //     //     the
  //     //     // for loop)
  //     //
  //     //     // >2*mi case always need their exclusive OWN one at boundary
  //     cases
  //     //     // but the ending boundary case can result in double count so we
  //     do
  //     //     // that separately
  //     //     //
  //     //     // we do need to double count b/c think of it this way
  //     //     //    when we get >2*mi, it's a length in between
  //     //     //    while mi2ss==1 handles the cases on the left-endpoint of
  //     the
  //     //     //    length
  //     //     //    i==distances.size()-1 handles it from the right-endpoint
  //     of
  //     //     the
  //     //     //    length
  //     //     //
  //     //     //    and also if i==0 it handles the right end point case
  //     //     //    and if mi2ss==1 right after, then we do it again (so even
  //     //     before
  //     //     //    i==0 case does +=2 at the front ends but not at the back
  //     ends
  //     //     //    yet)
  //     //     //
  //     //     //    or a better way to think about is mi2ss denotes the
  //     previous
  //     //     //    length is also this 3rd case
  //     //     x_needed++;
  //     //   }
  //     //
  //     //   // if (mi2ss == 1 || i == distances.size() - 1) {
  //     //   if (mi2ss == 1) {
  //     //     x_needed++;
  //     //   }
  //     //
  //     //   mi2ss = 1; // always, to denote we're in the lone bad cell zone
  //     //   // basically a flag to say the previous distance is also that
  //     (which
  //     //   // means if we have 3 distances >2*mi, then there would be
  //     //   x_needed+=2)
  //     //
  //     //   // if (i == 0) {
  //     //   //   x_needed++;
  //     //   //   continue;
  //     //   // }
  //     //   // // if (i == distances.size() - 1) {
  //     //   // //   x_needed++;
  //     //   // //   continue;
  //     //   // // }
  //     //   //
  //     //   // // x_needed += mi2s / 2 + mi2s % 1;
  //     //   // x_needed += mi2s / 2 + mi2s % 2;
  //     //   // mi2s = 0;
  //     //   //
  //     //   // // mi2ss++;
  //     //   // // if (mi2ss == 2) {
  //     //   // if (mi2ss == 1) {
  //     //   //   // mi2ss = 0;
  //     //   //   x_needed++;
  //     //   // } else {
  //     //   //   mi2ss++;
  //     //   // }
  //     //   //
  //     //   // // actually if its at the end then we need another one at
  //     //   // the very end if (i == distances.size() - 1) {
  //     //   //   // mi2ss = 0;
  //     //   //   x_needed++;
  //     //   // }
  //     // }
  //   }
  //   // x_needed += mi2s / 2 + mi2s % 1;
  //   // x_needed += (mi2s - 1) / 2 + (mi2s - 1) % 2;
  //   // x_needed += (mi2s) / 2 + (mi2s) % 2;
  //
  //   bad_cells +=
  //       ((mi < d[d.size() - 1]) && (d[d.size() - 1] <= 2 * mi)) ? 1 : 0;
  //   lone_bad_cells += (2 * mi < d[d.size() - 1]) ? 1 : 0;
  //   // x_needed += mi2s / 2 + mi2s % 2;
  //   x_needed += bad_cells / 2 + bad_cells % 2;
  //   // x_needed += mi2ss - 1;
  //   x_needed += lone_bad_cells;
  //
  //   // since this is at the end we always want to include all possible mi2s
  //
  //   // DBGLN(x_needed, mi2s, mi2ss);
  //
  //   // for (ll i = 1; i < n - 1; i++) {
  //   //   if (a[i] - a[i - 1] <= mi || a[i + 1] - a[i] <= mi) {
  //   //     // good
  //   //   } else if (a[i] - a[i - 1] > 2 * mi && a[i + 1] - a[i] > 2 * mi) {
  //   //     // lone bad cell
  //   //     x_needed++;
  //   //     // i++;
  //   //   } else { // at least both side is mi+1=...=2*mi or one of the side
  //   is
  //   //   >2mi
  //   //     x_needed++;
  //   //     i++;
  //   //     // 3 cases:
  //   //     // left side is <=2*mi, right side is <=2*mi
  //   //     //      => clearly this and the next forms a distance of 2*mi
  //   //     //          so use an x and skip the next element (since now it is
  //   //     //          covered and this is better then doing x+=2 with
  //   treating
  //   //     it
  //   //     //          as 2 lone bad cell)
  //   //     // left side is <=2*mi, right side is  >2*mi
  //   //     //      => only happens when there's only one distance of it
  //   <=2*mi
  //   //     //          but either disjoint pairs of <=2*mi before are taken
  //   or
  //   //     <=mi
  //   //     //          before it
  //   //     //          (but cannot be a disjoint consecutive since this case
  //   //     would
  //   //     //          be skipped thn)
  //   //     //
  //   //     //          no skip but x_needed++
  //   //     //          (no skip because we have to check if the next is a
  //   lone
  //   //     bad
  //   //     //          cell or not, we're not taking a mutual pairs)
  //   //     // left side is  >2*mi, right side is <=2*mi
  //   //     //      => assuming left_side is handled, this right side can be a
  //   //     //      a good cell with <=mi on ITS right (forgotten sub-case
  //   from
  //   //     case
  //   //     //      1) but again anything can happen so we do
  //   //     //
  //   //     //          x_needed++;
  //   //     //
  //   //     //      BUT there could be a disjoint pair coming up so no
  //   x_needed++
  //   //     //      and do nothing (not enough info)
  //   //     //              like the right side's distance becomes the left
  //   //     side's
  //   //     //              distance of case 1 (or case 2)
  //   //     //
  //   //     //
  //   //     //              or make my life easier and just pre-compute the
  //   //     distance
  //   //     //              and do a second linear pass on distances
  //   //   }
  //   // }
  //
  //   DBGLN(x_needed, x, lo, hi, mi);
  //
  //   if (x_needed > x) {
  //     // invalid
  //     lo = mi + 1;
  //   } else {
  //     // valid: try lower/smaller/tighter lengths
  //     hi = mi - 1;
  //     k = mi;
  //   }
  // }
  //
  // O(k);

  // x is the opposite?
  // just flip all the choices for <=x??? (linear pass)
  // and find the distance between cells?
  // and fine the 2nd largest distance?
  // (we can always split the largest distnce unless its at the end)
  // or rather we need pairs actually
  // but doesn't have to be mutually exclusive pairs
  // so any really

  // vll b; // b for BLACK!!
  // ll j = 0;
  // II(i, x + 1) {
  //   if (j < n && a[j] == i) {
  //     // omit
  //     j++; // by the inp assumption a[i]<a[i+1]
  //   } else {
  //     b.PB(i);
  //   }
  // };
  //
  // // unless j == n, this runs at least once
  // for (ll i = j; j < n; j++) {
  //   b.PB(a[j]);
  // }
  //
  // // cells to turn BLACK
  // set<ll> inter_el_distance;
  // ll first_distance;
  // ll last_distance;
  // II(i, b.size() - 1) {
  //   inter_el_distance.insert(b[i + 1] - b[i]);
  //   if (i == 0) {
  //     first_distance = b[i + 1] - b[i];
  //   }
  //   if (i == b.size() - 2) {
  //     last_distance = b[i + 1] - b[i];
  //   }
  // }
  //
  // // 2<=n but the following could happen
  // // a=[0,1] x=1
  // //
  // // no cells to turn black (we need 0)
  // //
  // // but seems like based off the output required 1<=k, it seems like we will
  // // always provide at least 2 elements to be colored black
  //
  // DBLOCK {
  //   vll d(inter_el_distance.begin(), inter_el_distance.end());
  //   DBG_ITER(d);
  // }
  //
  // while (x > 0) {
  //   ll inner_distance = *next(inter_el_distance.rbegin());
  //
  //   if (first_distance >= max(last_distance, inner_distance)) {
  //     // if (first_distance % 2 == 1) {
  //     // prefer to move the +1 into the inner
  //     //
  //     inter_el_distance.insert(first_distance / 2 + (first_distance % 2));
  //     first_distance = first_distance / 2;
  //     // }
  //   } else if (last_distance >= max(first_distance, inner_distance)) {
  //     inter_el_distance.insert(last_distance_distance / 2 +
  //                              (first_distance % 2));
  //     first_distance = first_distance / 2;
  //   } else { // inner_distance is STRICTLY largest
  //            // NOTICE, we can conserve one of the x in the inter_el_distance
  //            // b/c we can always (when SELECTING a pair of cells) to "break"
  //            // the largest
  //     i
  //   }
  //   x--;
  // }
  //
  // if (inter_el_distance.size() == 1) {
  //   O(*inter_el_distance.begin());
  // } else {
  //   ll inner_distance = *next(inter_el_distance.rbegin());
  //   O(max(inner_distance, max(first_distance, last_distance)));
  // }

  // the x here means available DoFs to minimize k
  // x as in additional cells to paint black to BREAK UP those long distances
  // the optimal placement for x is to break apart the largest distance by
  // halves => (half,half) or (half,half+1)
  //                                  ^
  //                       prefer to be in the inner

  // if(inter_el_distance.size() == 0) {
  // O(0);
  // } else if(inter_el_distance.size()==1)
}
