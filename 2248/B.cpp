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

// start: 1019
//   end: 1216xx

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
// P.1: the enablement to re-arrange at the end <==>
//      we only care about the SET equality of integers between array a and b
//          (unordered)
//
// ~~~ O.1: let k be the #s of difference between set a and set b
//          ==> then, n-2k == m ==> n = m+2k
//
//       ~~~~ O.1/1: suppose k=0 but n > m
//                  we can always reduce n -> m?
//       O.1/2: n < m ==> NO
//
// O.2: if min(a)>min(b) || max(a)<max(b) => NO
//      O.2/2: if k=0 but n>m (&& O.2) =>
//                  then we can always find a missing element of b into a and
//                  replace the 2 elements into 1 (-k not -2k actually)
//
//
//
// IMPL:
//      compute k
//
//      if min(a)>min(b) || max(a)<max(b):
//          return NO
//      elif n-k < m:  // too much differences to accomodate m into n
//          return NO
//      else: b is within range of a && differences supports the length
//          return YES?
//
//          first, we can quickly set and find the min(b) and max(b)
//          then, we can take any two integers (in a but not in b)
//              and assign a value within the two integer (not in a but in b)
//
//          more generally, every element in b but not in a must have a pair of
//          elements (in a but not in b) to be removed and replaced with an
//          element in b into a[]
//
//          by the n-k<m logic, we actually need 2k integers of a[] not in b[]
//              that can be replaced with k integers in b[] but missing in a[]
//
//          HOWEVER, is there a CE where there's more or less differences?
//              if there's too much differences (i.e., in b not in a)
//                  this original conditional already handles it
//              but if there's smaller amount of differences where
//                  n-k != m and where n-k > m?
//
//                  then, we can just select x<y where x is in m and y is not in
//                      m or the opposite and replace them with the one that is
//                      in m
//                      ==> effectively, reduce elements in a but not in b one
//                      by one until a==b
//                          because we just need to remove the one WASTE
//                          integer, we can find ANY USEFUL integer below or
//                          above the WASTE integer and remove it by replacnig
//                          it with the same USEFUL integer
//
//                          ==> logically/computationally tight
//
//          refer the elements that are in a but not in b as WASTE
//          refer the elements that are in a and in b as USEFUL
//          refer the elements that are not in a but in b as MISSING
//          HOWEVER, we have to be careful with the MISSING integers as it needs
//              a pair of WASTE integer that surrounds the MISSING integer
//              (intervals?/schedules?)
//
//          O.3: it is sub-optimal to take 2 USEFUL integer and replace it with
//                  1 USEFUL integer (since it only decreases the range of
//                  possibilities and the already use-to-be larger amount of
//                  USEFUL integer that is now reduced)
//
//               it is sub-optimal to take 1 USEFUL & 1 WASTE integer and
//                  replace it with 1 USEFUL since it just reduces the range of
//                  possibilities
//
//               ==> it is optimal to just take 2 WASTE integer to replace it
//               with a USEFUL integer****
//
//          consider the case where n=5 and m=4 with 1 WASTE integer => k=0
//               that meeans n-k>m (the WASTE integer DOES NOT HAVE TO BE
//               duplicates) and we just take any USEFUL integer and take the
//               single WASTE and output the same USEFUL integer again
//
//          hence, the point of difficulty is whether all pairs of WASTE integer
//          can replace it with a USEFUL integer???
//              for example, what if all the WASTE integer is in the median but
//              the USEFUL integer are all off-median?
//
//              for example, the 2 USEFUL is at the bounds of b.
//
//              then, 1 USEFUL+1 WASTE just removes the waste and must replace
//              it with the 1 USEFUL or else the range is reduced (a NO) but we
//              also need additional USEFULs in the off-median
//
//          so let us rewrite the formula as n-k-d=m
//
//              where k is the # of differences against b,
//                  (needs WASTE -= 2 to produce USEFUL++)
//                    d is the # of extra, duplicate waste from b (WASTE-k)
//                   (needs 1 WASTE & 1 USEFUL to keep the same USEFUL== but
//                   WASTE--)
//
//      assuming b[] is within/at the range of a[]
//
//              n=WASTE+USEFUL
//              n=k+d  +m
//       k-- => WASTE -= 2; USEFUL++ (requires WASTE_1 <= MISSING <= WASTE_2)
//              how does one ensure for every MISSING is bounded by its own
//              exclusive pair of WASTE?
//
//                  we require WASTE == n-USEFUL == n-m >= 2k
//                  but this is just the max possible waste (doesnt account for
//                  the +1 effect post-op)
//
//       d-- => WASTE --; USEFUL==  (no range restriction, very flexible)
//
//
//       suppose, n = USEFUL_WASTE + UTTER_WASTE + USEFUL
//                n = 2k + d + m
//          if USEFUL_WASTE >= 2k => good
//          if USEFUL_WASTE < 2k => bad
//
//          UTTER_WASTE can be obliterated to 0 with no consequences
//
//          W for WASTE and M for MISSING
//
//          1 2 3 4 5 6 7 8 9 10
//          W W     * W   W W W
//              M M *   M
//
//          at first, we have 6 WASTE = 2 * 3 MISSINGS
//              good right?
//              actually good
//
//              actually we want the reverse example
//
//          1 2 3 4 5 6 7 8 9 10
//              W * W W W W W
//          M M   *           M
//
//                  6 WASTE = 2 & 3 MISSING
//                  good right?
//
//                  but, none of the W bounds ANY of the Ms even for the
//                  following case. 1 M is bounded but the 2 other M is
//                  unbounded (the middle M does not have un-taken EXCLUSIVE
//                  pairs to consume)
//
//          W     * W W W W W
//            M M *           M
//
//
//            we can do this
//
//            prefix_C
//            if W:
//              prefix_C++  // supports 1 additional M later)
//            if M:
//              prefix_C-- (M needs to take it for at least one side of it)
//            if prefix_C < 0:
//              NO  // too much M opened
//
//            if prefix_C >= M:
//              YES  // enough REMAINING prefix_C to close all the Ms
//            else:
//              NO  // not enough REMAINING prefix_C to close all the
//                      outstanding Ms
//
//
//            // conceptually... all the Ms requires 1 unique Ws on its left
//            //        then at the end it just needs M
//            //    but what if there's a case where most of the Ws are in the
//            middle
//            //    and not at the end?
//            //    since prefix_C>=0 throughout, we can assume say small amount
//            of    Ms appear after before the final group of Ws
//            //    then all the extra Ws that came before the last group of M
//            (that comes before the lat group of W) will close all necessary
//            outstanding Ms before it and the final group of Ws will close the
//            final group of Ms even if the Ms are more then the final group of
//            Ws (????)
//
//            consider
//
//            W W M W W W W W W W W W W W W M M W
//            that's bad regardless
//
//            just prefix_C and suffix_C w/o checking the end condition?
//
//            where prefix_C checks if enough Ws are front loaded to open enough
//            of the M
//
//            where suffix_C checks if enough Ws are front loaded (from behind)
//            to close enough of the M
//
//            but remember this is by count so it is orderless. do order matter?
//
//            actually, with prefix_C & suffix_C, this enforces that for ever M,
//              M+1<=W         @ M*             W>=M+1
//              before    the M of interest     after
//            to ensure there is always a spot for a pair of W just for M*
//
//            is this too strict? nope.
//
//              if +1 -1 +1 -1 +1 this actually passes
//
//                  we still need the post condition???
//
//                  which only ensures even parity... (which is needed it seems
//                  like since these can be shared for some reason)
//
//                  suppose even parity, would this still work?
//                      likely yes, especially with suffix check also but seems
//                      like it could still leave room for error in the middle
//
//
//
//
//            if there are extra Ws, we can just apply the other FREEBIE
//            operation to W-- while maintaing USEFUL integers.
//
//            hopefully this is the correct answer
//
// IMPL:
//      if B is out of the range of A:
//          bad (NO)
//      else:
//          prefix_C/suffix_C over the value-space (not index-space)
//
//          given ordered_set(A), ordered_set(B) // O(nlogn) is fine
//          or just sorted vll a, sorted vll b
//          compute a joined vll c = {-1,1} in the order of the values of both
//                                     M W                                a,b
//          do prefix_C/suffix_C for condition
//
//          if both pass, => works (and extra Ws are freebies/fine/ignorable)
//
//          => YES
//              ALSO, THE ASSUMPTION THAT THE VALUES ARE DISTINCT HELPS A LOT
//                  LIKE A LOT A LOT
//
//          else
//          => NO
//

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n, m);
  IVLL(a, n);
  IVLL(b, m);
  ST(a);
  ST(b);

  if (b[0] < a[0] || a[n - 1] < b[m - 1]) { // B is out of range of A
    O("NO");
  } else {
    unordered_set<ll> as(a.begin(), a.end());
    unordered_set<ll> bs(b.begin(), b.end());

    ll in = 0;
    ll im = 0;
    ll total_m_count = 0;
    vll c;
    // ignore USEFUL numbers
    // if a.contains(bi) => skip
    // if b.contains(ai) => skip
    // if !a.contains(bi) => MISSING (-1)
    // if !b.contains(ai) => WASTE (+1)

    II(_i, n + m) {
      if (im > m - 1) {
        if (!bs.contains(a[in])) {
          c.PB(1); // WASTE
        }
        in++;
        continue;
      }
      if (in > n - 1) {
        if (!as.contains(b[im])) {
          c.PB(-1); // MISSING
          total_m_count++;
        }
        im++;
        continue;
      }
      if (a[in] < b[im]) {
        if (!bs.contains(a[in])) {
          c.PB(1); // WASTE
        }
        in++;
      } else {
        if (!as.contains(b[im])) {
          c.PB(-1); // MISSING
          total_m_count++;
        }
        im++;
      }
    }

    ll prefix_c = 0;
    II(i, c.size()) {
      prefix_c += c[i];
      if (prefix_c < 0) {
        O("NO");
        return;
      }
    }
    ll suffix_c = 0;
    DD(i, c.size()) {
      suffix_c += c[i];
      if (suffix_c < 0) {
        O("NO");
        return;
      }
    }
    if (suffix_c < total_m_count || prefix_c < total_m_count) {
      O("NO");
      return;
    }
    O("YES");
    return;
  };
}
