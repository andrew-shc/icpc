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

// start: 1927 (B2059-B2069)
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
// isn't this just asking the smallest i s.t. b_i != i
//
// GENERAL QUESTION: OPTIMAL PARTITIONING
//      - concat. sub-arrays with even indices (1@i=2,4,6...) => b[]
//      - find the min @i s.t. b_i != i
//
// O.1: at least k-1 1-lengthed subarrays at the end
// O.2: n==k, basically every other elements of a (i=2,4,6,...)
// O.3: if k==2 (best case), we can arbitrarily choose the 1st partition s.t.
//      the 1st element of the 2nd partition results in b_i != i for a minimal
//      cost of 1 (assuming not all elements of b_i is 1 or only the 1st element
//      is 1 and all other are 2)
// O.4: 1st element is always excluded
//
//
// min @i s.t. b_i != i ==> for all 1<=j<i, b_j == j (almost like MEX)
//
// we want to minimize the b_j = j
//
// on the contrary, in what case b_j = j MUST exist? (cannot be avoided)
//  on WHAT CONDITIO0N would it always result in b_j=j for some i<=j<i
//
// for example, b_1=1
//      ==> all 2nd partioning's 1st element must have 1
//      ==> k=n, 2nd element must be 1
//          k=n-1, 2nd/3rd element must be 1
//          k=n-2, 2nd/3rd/4th element must be 1
//          k=n-l, element i=2,3,4,...,l+2 must be 1
//
// what about b_2=2
//      ==> all 2nd partioning's 1st element must have 1
//              all 2nd partition's 2nd element OR 4th partition's 1st element
//              must have 2
//
//      invariance: a-th partition, b-th element, for j-th b_j=j,
//          must be a/2+b-1=j
//
//
//      ==> k=n, 4th element must be 2 (4/1)
//          k=n-1, 3rd element must be 2 (2nd partition's 2nd element) (2/1)
//            XOR, 4th element must be 2 (4th partition's 1st element) (4/1)
//          k=n-2, 3rd element must be 2 (2/2)
//            XOR, 4th element must be 2 (4/1)
//            XOR, 5th element must be 2 (4/1) +1 shift from (2/2)
//          k=n-3,
//
//  again for b_1=1
//      x x x x x x x x x x
//  k=n
//      x * x x x x x x x x
//  k=n-1
//      x * * x x x x x x x
//      x [ ]
//      [ ] x
//  k=n-2
//      x * * * x x x x x x
//      x [   ]
//      [ ] [ ]
//      [   ] x
//  k=n-3
//      x * * * * x x x x x
//      x [     ]
//      [ ] [   ]
//      [   ] [ ]
//      [     ] x
//
//  again for b_2=2
//      x x x x x x x x x x
//  k=n
//          v
//      x * x x x x x x x x
//  k=n-1
//          v v v
//      x * * x x x x x x x
//      x [ ]
//      [ ] x
//      x x x x
//      x x [ ] x
//      x x x x [ ]  << impossible (need's 4 x's before reaching 5-th, an odd
//      index)
//  k=n-2
//          v v v v
//      x * * * x x x x x x
//      x [   ]
//      [ ] [ ]
//      [   ] x
//  k=n-3
//      x * * * * x x x x x
//      x [     ]
//      [ ] [   ]
//      [   ] [ ]
//      [     ] x

//
//
//
//      ~~~~~
//      ==> if k=n, basically 2nd element must have 1
//                  (2nd partioning 1st element must have 1)
//          if k=n-1, the 2nd partioning's 1st element must have 1
//
//
//
//
//
//
//~~~~~~~~~~~~~~~~~~~~~~~~
//
// for example in TC#2:
//      n==k and duplicate elements makes that certain element unavoidable
//          (i.e., the partitioning restricts to must always use the given
//          ordering of the ordered SET of a)
//      suppose k=n-1
//          we allow a partioning of 2-len'd subarray somewhere
//              ==> again, duplicate elements
//                  in fact, TC#2 is overly tight, with always 2-duplicate
//                  element k=n-(2-1) disables this possibilities
//
//                  k>=n-(2-1)
//
//      in general, suppose d s.t. all duplicates in a are >=d-duplicates
//          if k>=n-(d-1)=n-d+1
//
//          we must follow the ordering given by a[]
//
//          can't we overlap??
//
//
// ^^^ ~~~~~~~~~~~~~~~~~~~~~~~~~~~`
//
//
// stuck
//
//
//
// suppose b_1=1
//
// k=n-1
// a: x * * x x x x x x x x
// 1/2 1
// b: 1 x x x x x x x x x x
//
// -> b_2=2
//
// k=n
// a: x x x * x x x x x x x
// b: x 2 x x x x x x x x x
// k=n-1
//
// b: x 2
//   1/2 2
//
// k=n-2:
// b: x 2
//  1/2/3
//
//
//  whats the missing observation?
//
//
// actually, a better observation is to slowly look in the order of b_i=i
//      from where the first b_1=1 occurs, does the k support it?
//      and conditions where b_2=2 should occur next
//      and this is better because the moment the chain is broken we have  found
//      our first b_i!=i
//
// think k as the remaining degrees of freedom
//
// if @2 = 1, no DoF used
// if @i = 1, i-2 DoF used (assuming i>=2)
//              which can be thought of as the more the 1 is misplaced
//              the more k it has to use
// optimal k=0
//
// x 1 x 2 x 3 x 4 x 5 x 6 x 7 x ...
// x x 1 ? (always 1 is used)
// either
// [x x] [1] or [x] [x 1] (but the latter is actually invalid so just the 1st)
//                          ^^ i think its this missing codified observation
//                          that made the rest needlessly complicated
// x x x 1 (always 2 used)
//
// regardless what happens before, invariant to before (inclusive 1)
// v ... find the next 2
// ~ 2 (~~~impossible) POSSIBLE as [~ 2]
//
// for every adjacent element, one DoF is used (to increase the earlier
//      partition's length to accomodate the incoming b_i=i)
// for any element separated by one, zero DoF is used
// for any element separated by more than one, the same rule applies with i-2
//      DoF used
//
// if multiple choices are present, it is OPTIMAL to be greedy on k
//      (prefer spacing elements by one if possible)
//
//      if we're in a case like this
//
//      x 1 2 2 3
//      by that logic, we should do
//        *   * *
//      but we need to take one DoF because 2/3 are adjacent
//
//        * *   *
//      doing this is jsut as same (just moves the one DoF usage earlier)
//
//      but with the first logic, if there are say
//      x 1 2 2 3 3 3 3
//      the first logic supports the optiaml usage of k (by not using any DOF)
//
//      however, the second logic uses one DoF AOT in *anticipation* that the
//      next group is ADJACENT but the anticipation is NOT always true, so it
//      can result in needlessly take one additional k
//
//      (because what happens if after 3, worst-case it requires all k usage?
//      the 2nd logic fails but 1st logic supports it that would yield an
//      OPTIMAL PARTITIONING)
//
//
//  what about
//      x 1 2 x 2 3?
//      does it matter? (both requires one DoF)
//          in this case, it doesn't matter. upon 3, both decision results in an
//          additional DoF required for 3 (unless cases like duplicate 3s like 3
//          3 or 3 3 3)
//
//      [x] [1 2] [x] [2 3]
//      [x] [1] [2 x] [2 3]
//
//      x 1 2 x 2 3 3
//      [x] [1 2] [x 2] [3] [3]
//      [x] [1 2] [x 2 3] [3]
//      [x] [1] [2 x] [2 3] [3]
//      [x] [1] [2 x] [2] [3] [3] << notice, same thing again. we just simple
//                                  have MORE INFORMATION on the later usage of
//                                  DoF to reduce the k-usage simply because the
//                                  later elements might have duplicates to
//                                  support one-off spacing (0 DoF usage)
//
//      edge case: when a higher element is in between say
//
//      x 1 2 3 2 3
//
//      [x] [1 2 3] [2 3]
//      [x] [1 2] [3 2] [3]
//      [x] [1] [2 3] [2 3]   << also noticed it seems like it is generlaly
//                          preferred to have smaller subarrays that is as close
//                          to their intended indices
//
//             in this case, the later 2 is better but only if the later 3 is
//             present
//
//      no way this is DP
//
//      this can be more simply put:
//          if adjacent conseuctive element: k--
//          if 1-spaced: k==
//          if >=2-spaced conseuctive element: k-=
//
// IMPL:
//      find the earliest b_1=1 (@2... reduce k as needed)
//      find the latest b_l=l
//
// ~~~~~O.5: a spacing of AT LEAST ONE between increasing consecutive elements
// ~    are
// ~    REQUIRED NONONONONONO
//
//
// !!!!! post-editorial: (of course 2 paragraphs only => unlikely to be DP =>
// !! some
// !!!!! very dead simple observation missing)
//
//  if k=n: check array explicitly as intended
//  if k=n-1: ONLY ONE b_i=i *can* be shifted 1 to the right
//  if k=n-2: ONLY TWO b_i=i *can* be shifted 1 to the right (or ONLY ONE can be
//              shifted 2 to the right)
//
//      it has a pattern of a summation of up to k (the different k the k DoF)
//
//      if shift left, k--
//      if shift right, k--
//          while both results in equal shift at the EOD,
//          the shift left collapses the 1-space and squeezes it out to the
//          right (k-- due to increasing the previous partition) while the shift
//          right pulls the 1-space to 2-space (hence, k-- also)
//
//          but the invariant is shift left 1 (at most 1 really) and shift right
//          1 is the same so shift left 1 can be folded into shift right 1
//
//          by this nature, shoudln't we prefer shift left 1? to promote more
//          options to discover later b_i=i?
//          it seems like this is some tradeoff to consider
//              1. shift left to allow more options to find higher b_i=i
//              2. shift right to minimize the k DoF usage (unless we know there
//              will be surplus k??)
//
//
// !!!!!!!!!!!!!!!! when it means optimal partioning IT MEANS OPTIMAL PARTIONING
//                  SUCH THAT THE MIN COST IS REDUCED
//                  => FIND THE PARTIONING S.T. b_i != i ON THE *LOWEST* i
//
// !!!!!!! by this logic, answer is at most 2 when all segments are 1
// !        however, if, say, a 2 is present, we can always configure the
//          subarrays to fold the 2 into the off-index (odd-index)
//          or if all 2 but few 1s, fold all the 1s into the off-index so i=1
//          is, again, the lowest or if 1s are all congregated in the beginning
//          => 2
//
//          for a 3 to happen, it needs both i=1,i=2 to be covered in all
//          exhaustive cases (which mostly seems impossible) since we can do all
//          1s on the first (i=2) or all 2s on the first (i=1) and avoid both 1s
//          and 2s in the first
//

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n, k); // k<=n, k is even, k is # of subarrays
  IVLL(a, n);

  ll min_cost = 1;
  if (n == k) {
    for (ll i = 1; i < n; i += 2) {
      if (a[i] == min_cost) {
        min_cost++;
      } else {
        break;
      }
    }
  } else { // n-k (similiart to the editorial)
           // if it is all 1 from 2 to 2+n-k
    // for every decrease in subarray, the longer we can make the 1st subarray
    // to be until the 1st el. of the 2nd subarray no longer is 1 (which then we
    // can just make it b_1!=1 with min cost of 1)
    bool all_ones = true;
    for (ll i = 2; i <= 2 + n - k; i++) {
      if (a[i - 1] != 1) {
        all_ones = false;
        break;
      }
    }
    if (all_ones) {
      min_cost = 2;
    } else {
      // pass
      // we can use the not one as the 1st index
    }
  }

  O(min_cost);
  ;
}
