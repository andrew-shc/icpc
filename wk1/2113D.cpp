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
// swap ny two elements in a[] at most once
//
// P.1: player can score at most <=n (the max)
// P.2: swap can be thought of as optimally picking the largest element before
//      or after the losing round so that the player can smoothly continue
//      without going through the losing round (can potentially lose back some
//      round if it means lose much less round...)
//
// P.3: if we swap at i and j (suppose i<j)
//
//      any elements before i is clearly invariant
//
// P.4: if we swap with an earlier element at some losing round
//      (REMEMBER, WINNING CARDS ARE REMOVED AND LOSING CARDS STAY)
//      then we simply lose earlier => sub-optimal
//
//      THEREFORE, we always want to FORWARD SWAP (if we choose to swap)
//
// P.5: an extension of P.3, given i<j, swapping i,j
//      keeps elements after j invariant also
//      (because at the j-th card, if it works, the losing card still stays. and
//      if the j-th card goes earlier to the i-th card, as long all the cards
//      between i and j WINS the dealer cards stays the same till after the j-th
//      card like before)
//      BUT, this only works for WINNING cards in-between => pointless to swap
//      i,j within or at the boundary of a GROUP of winning cards
//
//      if we swap i,j with losing cards in-between,
//          the WINNING dealer cards will be REMOVED
//          but the SAME AMOUNT OF WINNING DeALER CARDS WILL BE REMOVED
//
//          unless the swap made a player card at i shifting the entire stack of
//          the player card up by 1
//
//
//~~~~~
// P.5: if choose to forward swap, we can maintain the # of points (if there's
//      any value that can beat it)
//~~~~
//
//~~~~~~~~~~~~~~~~~~~~~~~~~
//      obviously we don't want to swap if it means we'll lose both rounds at i
//      and at j
//          hence, it means we either DECIDE to
//              ~~ win at i and as-is at j (identity)
//              win at i and lose at j (identity <-- why??)
//              win at i and win at j (best case)
//              lose at i and win at j (better tradeoff)
//
//              lose at i and lose at j (no?)
//              **win at i and win at j (if already win at both rounds, why??)
//                                       unless it means we win more rounds
//
//          hence, it means we either DECIDE to
//              win at i and win at j
//              lose at i and win at j
//
//              but these are all decision based on single-rounds when we should
//              be basing off cumulative increase in rounds...
//
//              some suffix dp...???
//~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//
//!!!! losing a round does not advance the player's position
//!!!!! it will just have to wait for the next minimum on the dealer's side
//!!!!! and is invariant if player's card move up (hence prefix min)
//
//
//~~~~~~~
//! going back to the original observation of how losing a round DOES NOT
//! advance the player's position, we just simply find
//~~~~~~~
//
//!!! binary search on answer (remember, binary search doesn't mean binary
//! results on the most optimal, it also includes integer results)
//
//! so what does it mean to binary search on answer (the # of rounds won by
//! player)?
//
//   we do have the special swap operation.... to play aroudn with
//
//
//!!!!! (post-editorial)
//
// suppose we try to swap with the first losing round/card with an earlier
// larger max, the first losing card will be swapped to an earlier place
//      unless the dealer's next card is smaller, this means the dealer's next
//      card will be larger and in fact will reduce the score of the player
//
//      => swapping a maximum at an earlier location either stays AS IS or
//      REDUCE the score all dependent on what the dealer's next card is
//      (overall, quite bad)
//
//          in other words, there really is NO POINT in swapping with an earlier
//          max
//
//      however, swapping with a suffix max (instead of prefix max) either (3
//          options)
//         1. doesn't help (no max large enough to beat the losing round)
//         2. helps but immediately hits a LARGER CARD from the dealer (after)
//         3. l-cards of the dealer after the losing round is smaler than the
//              newly swapped max on the player-side increasing l+1 amnt
//              (until a higher max from the dealer card at l+1th card is hit)
//
//
// again, importantly, read the problem statement CLEARLY:
//
//      NOTICE, WINNING ONCE <==> TAKING one TOP CARD
//          <=> THERE'S ABSOLUTELY NO SKIPPING CARDS
//
// ALSO, exactly n rounds (not until no more cards)
//
// ALSO, DISTINCT VALUES FOR ALL
//
//
//!! while we can construct in linear-time and check constan-time(??)
//!!  since we're already constructing linearly might as well just check
//! linearly
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
  IV(b, n);

  vll pmn_a(n, 0);
  vll pmn2_a(n, 0); // prefix 2nd min
  vll smx_a(n, 0);
  vll pmn_b(n, 0);

  pmn_a[0] = a[0];
  pmn2_a[0] = a[0];
  pmn_b[0] = b[0];
  smx_a[n - 1] = a[n - 1];

  II(i, n - 1) {
    pmn_a[i + 1] = min(pmn_a[i], a[i + 1]);
    pmn_b[i + 1] = min(pmn_b[i], b[i + 1]);
    smx_a[n - 1 - i - 1] = max(smx_a[n - 1 - i], a[n - 1 - i - 1]);

    if (a[i + 1] > pmn_a[i] && a[i + 1] > pmn2_a[i] && i == 0) {
      pmn2_a[i + 1] = a[i + 1];
    } else if (pmn2_a[i] > a[i + 1] && a[i + 1] > pmn_a[i]) {
      // between => tighten the two minimum's range
      pmn2_a[i + 1] = a[i + 1];
    } else if (pmn2_a[i] > a[i + 1] && pmn_a[i] > a[i + 1]) {
      // below both minimum => shift the minimums up
      pmn2_a[i + 1] = pmn_a[i];
    } else {
      // a[i+1] > pmn2_a[i] && pmn_a[i] > a[i+1]    DOESNT MAKES SENSE
      // pmn2_a[i] > a[i+1] && pmn_a[i] > a[i+1]    pmn_a[i]=a[i+1] =>
      // pmn2_a[i]=pmn_a[i] (look at the condition above)
      //
      // only happens when a[i+1]>pmn_a[i] && a[i+1]>pm2_a[i] && i>0
      //  => does not matter to us
      pmn2_a[i + 1] = pmn2_a[i];
    }
  }

  ll mx_pts = 0; // if neither 1<=win<=n-1 nor win==n, then it must be win==0

  for (ll wins = 1; wins <= n - 1; wins++) {
    // 2nd min (after conditional swapping of suffix max)
    //      is larger than
    //          the prefix min of the dealer with n-wins+1
    //              where the wins denote player wins
    //              and n-wins denote dealer wins
    //              +1 for the added comparison needed on the last dealer card
    //              that is assumed to be lost to the player (needed for
    //              comparisons for the min)
    //
    // the incoming suffix max may be so large it might not be the 2nd min
    // we need a set O(logn) insertion for an !!! O(nlogn)!!!!
    // or just keep track of 2nd min manually also
    //
    //
    // with the newly constructed prefix 2nd min pmn2_a[]
    //
    //  if suffix max > prefix 2nd min: use prefix 2nd min
    //  if prefix 2nd min > suffix max > prefix 1st min: use suffix max
    //  if prefix 1st min > suffix max: use prefix 1st min

    ll c;

    // per chatgpt suggestions and honestly when implementing if there's even a
    // slightest weirdness just do a separate case just for it (in thise wins==1
    // => no official 2nd min)

    if (wins == 1) {
      c = max(pmn_a[0], smx_a[1]);
    } else if (smx_a[wins] > pmn2_a[wins - 1]) {
      c = pmn2_a[wins - 1];
    } else if (pmn_a[wins - 1] > smx_a[wins]) {
      c = pmn_a[wins - 1];
    } else {
      // prefix 2nd max > suffix max > prefix 1st min
      c = smx_a[wins];
    }
    // if (max(pmn_a[wins - 1], smx_a[wins]) > pmn_b[n - 1 - wins + 1]) {
    // if (c > pmn_a[n - 1 - wins + 1]) {
    if (c > pmn_b[n - 1 - wins + 1]) {
      mx_pts = wins;
    }
  }
  // test/check for wins==n
  // simply, all n player cards has an overall prefix min greater than the first
  // minimum of the dealer
  if (pmn_a[n - 1] > pmn_b[0]) {
    mx_pts = n;
  }

  O(mx_pts);
  ;
}
