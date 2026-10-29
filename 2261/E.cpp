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
// H.1: we can try abstract-ing into groups of '(' delimited by ')'
//      however, this discards the number ')' needed to remove before adjacent
//      groups of '(' can join
//
// H.2: group by duplicate-# of ('s and )'s
//      at every )-group, we can record the number of operation needed to join
//      its two adjacent (-group
//
//      in fact, we can compute every (-group's decision factor and remove the
//      one with the highest factor within the constraint k)
//          the factor can be computed as the increase from max ('s from the
//          adjacent with the larger amount (increased by the number from the
//          lesser adjacent) minus number of `)`'s needed to allow the adjacent
//          groups to merge
//              probably paired with k
//
//
//          but this also suggets it will be dynamic.... DP for greeedy
//          exhaustive search?
//
//
// (((()(((())()((())))())))())
// ----.----..-.---....-....-..
//
//
//          binary search on answer?
//
//
// if k==1: basically greedy.
//          find the single )-group with largest adjacent (-groups
//
// !!!!!!!! post-editorial:
//
// !!! Hint 1: already done in respect to the abstraction?
//  !!!             actually, they want to record the # of opening brackets
//  !!!             before the closest next closing brackets for at EVERY index
//  !!!             of the string
// !!! Hint 2: ???
//
// !! main soln.
// !!!
// !!!  removing () actually removes an (-bracket that needs to be accounted for
// !!!
// !!!
// !!!  describes two cases to handle:
// !!!          (-group in the beginning
// !!!          (-group elsewhere that's confusingly referred as "window" in the
//                          middle
// !!!
// !!!
// !!!
// !!! c[i] actually represents the number of consecutive opening brackets RIGHT
// !!! BEFORE the i-th closing brackets (specifically for every closing
// !    brackets, not fixed to their position but by WHICH closing brackets
// !    themselves)
// !!!
// !!!
// !!!  the two cases describes the FINAL block of (-group
// !!!      1. final (-group is a prefix
// !!!      2. final (-group is somewhere in the middle (a "window" in the
// !                middle)
// !!!
// !!! the summation equation is confusing
// !!!      { sum_{j=l}^r(c[j]) } - (r-l) = { sum_{j-l}^r (c[j]-1) } + 1
// !!!
// !!!  but why should the last closing bracket r not be operated on?
// !        and what makes these prefix vs middle "window" distinction important
// !!!      to be separated?
// !!!
// !!!  recall the cases are separated by the LAST/FINAL conseuctive (-group
// !!!      clearly, if the final is prefix
// !!!
//   no. by the way it is written, they probably mean LAST/FINAL conseuctive
//   (-group as in after all the operations applied in a way that it achieves
//   these final goal (working backwarsd) which means we need to compute a
// min?
// !!!
// !!!  per implementation, they do that!
// !!!
// !!!  in other words,
// !!!      KEY INSIGHT: break the final case into two parts:
// !!!          1. the FINAL (post-op) on the string is a (-group prefix of str
// !!!          2. OR, the FINAL (post-op) on the string is a (-group in the
// !                middle of the str
// !!!
// !!!          + Use c[i] for #'s of ( in the (-group RIGHT BEFORE the i-th's )
// !!!                                      (consecutive groups of '(')
// !!!              - nice properties including easy computation
// !!!              - and stores information in succinct way s.t. the invariance
// !!!                  appears readily where when applying operation on c[i]
// !!!                  keeps the (-count if PREFIX is assumed

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n, k);
  IS(s);

  ll m = n / 2; // n is always even, m is the max amnt of ( => max possible
                // length for any conseuctive (-group

  vll c = {0};
  II(i, n) {
    if (s[i] == '(') {
      c.back()++;
    } else {
      // when ) is reached, create a new element to count for the NEXT )
      // by RBS, the last element must always be )
      c.PB(0);
    }
  }

  PS(ps_c, c);

  ll sums_max = 0;

  // case 1: we assume the answer has all the final (-group/block is a prefix
  // for every ) (cLOSING group)'s preceding exclusive ('s
  // we add the corresponding c[i] with -1 operation to make it happen
  // (remember, c[i] is SUM-INVARIANT under prefix)
  // AND apply the REMAINING operations to ANY closing brackets after
  //      (which by the invariance of where the ( is placed post-op, we can
  //      always compute it directly since it will always merge it with the
  //      prefix)

  II(ops, ps_c.size()) {
    // we begin with no operation (default prefix)
    // we assume each remaining operation can help us one-by-one (+1 score only)
    if (ops <= k) {
      // ll ops_max = max(m, ps_c[ops] + (k - ops));
      ll ops_max = min(m, ps_c[ops + 1] + (k - ops));
      sums_max = max(sums_max, ops_max);

    } else {
      break;
    }
  }

  if (ps_c.size() >= 3) {
    auto score = [&](ll l, ll r) { return ps_c[r] - ps_c[l - 1] - (r - l); };
    dll dq; // deque on incoming indices (1@)
    for (ll i = 1; i < ps_c.size(); i++) {
      // score can at most decrease by 1 per index
      // if the score is found to be decreased, it is better to take out that
      // portion of )-group (-- is caused by ')'-group)
      while (dq.size() > 0 && score(dq.back(), i) < score(i, i)) {
        dq.pop_back();
      }
      dq.push_back(i); // 1@
      while (dq.size() > 0 && dq.front() < i - k) {
        dq.pop_front();
      }
      sums_max = max(sums_max, score(dq.front(), i));
    }
  }

  O(sums_max);

  // // n>=3 => at least one closing bracket
  // // that means if only one closing bracket, then case 1 is already optimal
  // // (???)
  // // what is the suffix is the better one?
  // // if 1 closing bracket <==> "()" is the only case
  // if (ps_c.size() >= 3) {
  //   ll l = 2;
  //   ll r = 2;
  //
  //   DBGLN(sums_max);
  //   while (r < ps_c.size()) {
  //     while (true) {
  //       ll score = ps_c[r] - ps_c[l - 1] - (r - l);
  //
  //       sums_max = max(score, sums_max);
  //       if (r - l + 1 <= k && r < ps_c.size() - 1) {
  //         r++;
  //       } else if (r == ps_c.size() - 1) {
  //         break;
  //       } else { // if we can't go pass k-constraint ASSUMING within r
  //                // ===
  //                // if within r => we can't go pass the k-constraint
  //         break;
  //       }
  //     }
  //     if (r - l > 0 && r < ps_c.size() - 1) {
  //       l++;
  //     } else if (r - l == 0 && r < ps_c.size() - 1) {
  //       l++;
  //       r++;
  //       continue; // no point going through another while loop
  //     } else if (r - l == 0 && r == ps_c.size() - 1) {
  //       break;
  //     } else { // r-l>0 && r==ps_c.size()-1
  //       break;
  //     }
  //
  //     // this is actually un-optimal
  //     // the moment it reaches a section of )'s the score keeps going down
  //     // bit-by-bit one-by-one but the loop immediately terminates to keep it
  //     // from decreasing (but too greedy) because there'a local max after
  //     //
  //     // in fact, yes it is optimal to find the max from a k-constrained
  //     window
  //     // and there's no special rule that can simplify but regardless this
  //     can
  //     // still be implemented in an O(n) way using deque! (without *logn
  //     // anywhere)
  //     //
  //     // but how??
  //     //
  //     // actually this is how we do with dq
  //     //
  //     // first, pop any values dq from the back for any index in the dq that
  //     has
  //     // a score relative to the current fixed r smaller than the score of
  //     just
  //     // r itself (this ensures the dq orders from higher score to lowest
  //     score
  //     // monotonically b/c any index value with score that is lower before
  //     the
  //     // incoming value's score can always be replaced with the latest one
  //     for
  //     // optimal score)
  //     // then, we insert the value itself at the back
  //     // then, we just pop front for any indices that violates the
  //     k-constraints
  //     // (getting too far)
  //     ll local_max = LLONG_MIN; // since score can be negative
  //     while (true) {
  //       ll score = ps_c[r] - ps_c[l - 1] - (r - l);
  //
  //       if (local_max <= score && r - l > 0) {
  //         // always gets ran at least once due to local_max set to LLONG_MIN
  //         local_max = score;
  //         l++;
  //       } else {                   // local_max > score || r-l==0
  //         if (local_max > score) { // reset to the prev. best if possible
  //           l--;
  //         }
  //         break;
  //       }
  //     }
  //   }
  // }
  //
  // O(sums_max);
  //
  // case 2: we assume the answer has all the final (-group to be somewhere in
  // the middle (assume no prefix) with [l,r] where 1<l and l,r are the index of
  // the '(' (hence, re-use c or rather ps_c)
  //
  // recall, as long as r-l < k, we can apply the operation on [l,r]
  // (excluding r)
  //          ACTUALLY, the reason we exclude r because that REPRESENTS THE
  //          RIGHT BOUNDARY ')' of the (-group (and the reason l<1 is it
  //          represents the LEFT-MOST ALLOWED BOUNDARY (but can more right for
  //          the LB))
  //
  //                                            r must stay exclusive for this
  //                                            to work (because c[i] works in
  //                                            the direction of left (or
  //                                            directionally))
  //                                                    v
  // ~~~and the score is sum_{i=l}^{r-1} (c[i]-1)+1 = ps_c[r]-ps_c[l]
  //    score is actually sum_{i=l}^{r} (c[i]-1)+1 = ps_c[r]-ps_c[l]-(r-l)
  //        with r-l<k
  //
  //        but why not r-l<=k???
  //
  //        if k==1: [l==r] (no-operation) but k=1?
  //
  //        read the solution wrong?
  //
  //        yes, IT IS r-l<=k, just the catch that we conceptually exclude "r"
  //        that doesn't use k but counts for the score
  //
  //        then two-pointer on [l,r] constrained on k and greedy on score
  //              (to keep quadratic soln. to linear soln when we can because we
  //              know that to be greedy we have to hit the constraint as much
  //              as possible but sometimes we regret prior decision and pull up
  //              to maximize score)

  // // n>=2 => at least one closing bracket
  // // that means if only one closing bracket, then case 1 is already optimal
  // if (ps_c.size() >= 2) {
  //   // 2ptr needs to stop whenever
  //   //  it stops changing the subarray or like moving up the subarray
  //   //
  //   //  how is this 2-ptr???
  //   //
  //   //  we assume 2-ptr on [l,r] fixed on r (the exhaustive search for the
  //   END
  //   //  the subarray) constrained on k and maximize on score
  //   //
  //   //  in other sense, we check for each subarray's on r, and for each of
  //   them,
  //   //  we know that
  //   //  an increasing index of l can be checked????
  //   //
  //   //  in another sense, if the constraint is matched but if r++ still finds
  //   a
  //   //  better score, we pull l up (with l++) and STOP
  //   //
  //   //  take a breather and see if score can be maximized with l increased..
  //   //  if it doesn't, let r++ continue dragging l++ up
  //
  //   ll l = 2;
  //   ll r = 2;
  //
  //   // on the r == ps_c.size()-2 iteration
  //   // the first loop increases r++
  //   // then this iteration finds all the remaining option including the l++
  //   // while loop
  //   // and this will be the end
  //   // and this also assumes the subarray 2ptr keeps chugging along at the
  //   // bare-minimum one-by-one to the right (or else it becomes an infinite
  //   loop
  //   // that never reaches this condition)
  //   //
  //   // and can be thought of as another way where r==ps_c.size()-1 suggests r
  //   // cannot be increased anymore and same as the iteration that came before
  //   // and hence needs to be breaked
  //   //
  //   //
  //   // note: to keep the 2ptr chugging along, we can't conditionally increase
  //   if
  //   // it increases the max (==> forces into a local optimization)
  //
  //   DBGLN(sums_max);
  //   while (r < ps_c.size() - 1) {
  //     // when r is at -2, we assume the r++ while loop always at least
  //     increases
  //     // r++ at least once before reaching ps_c.size()-2 (because on the prev
  //     it
  //     // l++ must be increased once => r++ must at least increase once until
  //     // reaching ps_c.size()-2)
  //     // so on the next next iteration, the overall while loop will fail
  //     //
  //     // we actually need it to be -1 instead of -2
  //     // since after the l++ loop on the iteration of r=size-2 -> r=size-1
  //     // we still need to test and maximize for this new l* with (l*, r)
  //
  //     // DBGLN("<<", r, ps_c.size() - 1);
  //     // maximize score (within constraint)
  //     // by increasing r
  //     // while (r - l <= k && r < ps_c.size()) {
  //
  //     // we assume the start of thsi loop always have an increasing, new l
  //     while (true) {
  //       // DBGLN("r++", l, r);
  //
  //       // notice: no more random k-ops because we assume NOT prefix under
  //       case
  //       // 2 (and breaking case 1 & 2 does make the problem much easier
  //       because
  //       // of a major assumption that could be hard to generalize: prefixity)
  //
  //       // sums_max = max(sums_max, ps_c[r] - ps_c[l - 1] - (r - l));
  //
  //       ll score = ps_c[r] - ps_c[l - 1] - (r - l);
  //
  //       sums_max = max(score, sums_max);
  //       if (r - l + 1 <= k && r < ps_c.size() - 1) {
  //         r++;
  //       } else if (r == ps_c.size() - 1) {
  //         break;
  //       } else { // if we can't go pass k-constraint ASSUMING within r
  //                // ===
  //                // if within r => we can't go pass the k-constraint
  //         break;
  //       }
  //
  //       // sums_max = max(score, sums_max);
  //       //
  //       // if (r < ps_c.size()) {
  //       //   break;
  //       // } else if (r + 1 - l <= k) {
  //       //   // r will always increase one by one chugging along
  //       //   r++;
  //       //   break;
  //       // } else {
  //       //   break;
  //       // }
  //
  //       // r++;
  //
  //       // key point, we need the == to keep the 2ptr moving (chugging along)
  //       // if (sums_max <= score) {
  //       //   r++;
  //       //   sums_max = score;
  //       // } else {
  //       //   // if score is decreasing (e.g., all closing brackets that
  //       results
  //       //   in
  //       //   // increase from the operational cost (r-l) not just in the
  //       k-space
  //       //   // while the prefix sum ps_c is not increasing)
  //       //   // this actually makes it go back
  //       //   // ~~~~ r--; // remove the effect of the PRE-EMPTIVE r++ and the
  //       //   r--
  //       //   // after the
  //       //   //      // while will make the r go back to the original one
  //       //
  //       //   // ~~~~~~~~~~~~~~~~~~~ this actually creates an infinite loop
  //       //   break;
  //       // }
  //     }
  //     // r--; // the r++ always includes the next failed-condition and r--
  //     // reverts it back
  //
  //     // bool l_increased = false;
  //
  //     // maximize score by increasing l
  //     // SO ACTUALLY WE WERE PARTIALLY CORRECT BEFORE,
  //     // the l++ is not to max score but RELAX the k-constraint as much as
  //     // possible (with the side-effect of increasing score at most 1)
  //     //
  //     // while (r - l >= 0 && l <= r) {
  //
  //     // force increase on left
  //     // r++ must--greedily--always happen to maximize k
  //     // but sometimes k==0 (input relaxation)
  //     if (r - l > 0 && r < ps_c.size() - 1) {
  //       l++;
  //     } else if (r - l == 0 && r < ps_c.size() - 1) {
  //       // since both the inner while loop works in steps by steps
  //       // k==0 makes it restrictive and needs both to jump in the same time
  //       l++;
  //       r++;
  //       continue; // no point going through another while loop
  //     } else if (r - l == 0 && r == ps_c.size() - 1) {
  //       // l++ is invalid
  //       // r++ is invalid
  //       // (l,r) has been checked
  //       // immediate exit
  //       break;
  //     } else { // r-l>0 && r==ps_c.size()-1
  //       // (l,r) has been checked
  //       // r++ is invalid
  //       // l++ is useless since previous loop already identifies this l to be
  //       // maximal
  //       break;
  //     }
  //
  //     ll local_max = LLONG_MIN; // since score can be negative
  //     // and also because the same config will be checked and max'd on the
  //     r++
  //     // while loop
  //     while (true) {
  //       // DBGLN("l++", l, r);
  //
  //       ll score = ps_c[r] - ps_c[l - 1] - (r - l);
  //
  //       // sums_max = max(score, sums_max);
  //
  //       // for simplicty of implementation, the first iteration must be the
  //       same
  //       // as the last iteration of prev. loop's iteration
  //       // nope, we got to try increasing the l++ once at least forcibly
  //       after
  //       // exploring all options from previously fixed r (or else while loop
  //       // since l++ will think it goes down too quick and bad)
  //       if (local_max <= score && r - l > 0) {
  //         local_max = score;
  //         l++;
  //       } else if (local_max > score) {
  //         // this must ensure l++ before this while loop must be incorporated
  //         // actually, if local_max!=LLONG_MIN => EXTRA l++ was ran
  //         if (local_max != LLONG_MIN) {
  //           l--;
  //         }
  //         break;
  //       } else { // local_max <= score && r-l==0
  //         local_max = score;
  //         break;
  //       }
  //
  //       // if (l <= r) {
  //       //   // l_increased = true; // dummy
  //       //   l++;
  //       //   r++;
  //       //   // test on the new r
  //       //   break;
  //       // } else if (r - l - 1 >= 0) {
  //       //   // no break compared to the r++ loop
  //       //   // keeps finding  the maximum fixed on r
  //       //   // because for each r there's a single peak
  //       //   // that's always shifting right (?)
  //       //   //
  //       //   // no there can be multiple peaks => single/multiple-equal
  //       largest
  //       //   // peak within each subarray fixed on r
  //       //   //
  //       //   // but what if that largest peak is smaller than previous peak?
  //       //   what
  //       //   // if there's no peak? (l==r? is reasonable)
  //       //   //
  //       //   // but if this next fixed r has its largest peak smaller than
  //       //   previous
  //       //   // peak?
  //       //   //    remember, peak of the PREFIX SUM (well ps_c[r]-ps_c[l-1])
  //       //   //
  //       //   //    hence, just pick the peak of the PREFIX SUM (subtraction
  //       of
  //       //   two
  //       //   //    prefixes) given an r. so on the next r it can use the same
  //       l
  //       //   //    config if possible unless this new r substantially
  //       decreases
  //       //   the
  //       //   //    max but that's the only max (or relative max within the
  //       //   //    k-constraint) so we still use it until it is outside of
  //       the
  //       //   //    k-constraint and requires search the next maximum
  //       //   //
  //       //   //    but the max requires exhaustive search within the k which
  //       can
  //       //   up
  //       //   //    to n/2 (which means quadratic again) so how do we show
  //       it's
  //       //   //    monotonic?
  //       //   //
  //       //   //    i don't think it can be shown to be monotonic and requires
  //       //   the
  //       //   //    (r-l) calculation to be folded into the prefix?
  //       //   //    nonono
  //       //   //    by our expression of ps_c - ps_c - (r-l)
  //       //   //    it can increase at most 1 (if the section we're 2ptr it on
  //       is
  //       //   //    majority PREFIX closing brackets )- with no open brackets)
  //       //   //
  //       //   //    so actually the moment it stays the same it reaches with
  //       just
  //       //   //        ()()()()()() but since we want to relax our constraint
  //       //   //        we skipp all of these for maximum flexibility
  //       //   //        so keep l++ until it begins to decrease
  //       //   //
  //       //   //
  //       //   l++; // why did i do l-- previously??
  //     }
  //
  //     // l++;
  //
  //     // if (sums_max <= score) {
  //     //   sums_max = score;
  //     //   l_increased = true;
  //     //   l++;
  //     // } else {
  //     //   // l--;
  //     //   break;
  //     // }
  //   }
  //   // l--;
  //   // if (!l_increased) {
  //   //   l++; // forces an increase of l => increase of r at each iteration
  //   //   // r++;
  //   //   // ~~~~keep chugging along (because if just l++, )
  //   // }
  //
  //   // each iteration of this while loop represents different configuration
  //   of
  //   // possible contiguous subarray (and one can see that it is the best if
  //   we
  //   // keep it as contiguous as possible)
  // }
  // // }
  //
  // O(sums_max);

  // ll opens = 0;
  // ll breaks = 0;
  // vll opens_breaks;
  // opens_breaks.PB(0);
  // II(i, n) {
  //   if (s[i] == '(') {
  //     // opens++;
  //     opens_breaks.back()++;
  //   }
  //   if (s[i] == ')') {
  //     // breaks++;
  //     opens_breaks.PB(0);
  //   }
  // }
  //
  // PS(ps, opens_breaks);
  //
  // // ll sum = opens_breaks[0];
  // ll sum_max = 0;
  // for (ll i = 1; i <= max(0LL, (ll)opens_breaks.size() - k); i++) {
  //   // sum += opens_breaks[i];
  //   sum_max = max(sum_max, ps[i + k] - ps[i - 1]);
  // }
  // O(sum_max);
  ;
}
