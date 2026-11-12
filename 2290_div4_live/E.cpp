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
//
// once 0, stays 0 (on the right-side)
//
// right-side of 0 grows until all are 0
//
//
// if k is odd:
//  odd out odd in (1 in and odd out, parity doesnt change)
// if k is even:
//  even out odd in (parity changes every round)
//
// doesn't matter since we can jsut choose k to be small s.t. part of it cannot
// be added b/c k is too low
//  (maybe except when k=1?? but we can just set i=1)
//
// Alice moves first
//
// whichever can no longer moves loses
//  => on the round where there are no stones left
//  => on the round where there are 1 stones left that the opposing player picks
//      this 1 stone must be on the first element
//      if there's a stone on some other elements then the k will be applied and
//      add max of k new rocks to k-left of it
//
// in reality, we should be going from left to right not right to left?
//
//
// is this order invariant for the order of the operation?
//
// we're just adding the stones???
//              ^
//           invariant of ordering?
//
//           each players also pick ONE stone (any location AS LONG there's a
//           stone)
//
//           however these two players operate... the stones gets added together
//           eventually like merged together
//
//           enough tests cases to just verify by test cases...
//
//           no simulation this grows way tooooooo fast
//
// given some k,
//  when it reaches the lower bound it will be like
//
//  (for example say k=6 where k shouuld be even until)
//
//  1@i = 1 2 3 4 5 6 7 8 9
//        E O E O E O E E E
//                  *
//
//  but other than that, it depends on the parity of k and the current parity of
//  sums of values
//
//  2nd-order parity
//
// consider
//
// 1 2 3 4 5
//
// as
//
// 1 0 0 0 0
// 0 1 0 0 0
// 0 1 0 0 0
// 0 0 1 0 0
// 0 0 1 0 0
// 0 0 1 0 0
// 0 0 0 1 0
// 0 0 0 1 0
// 0 0 0 1 0
// 0 0 0 1 0
// 0 0 0 0 1
// 0 0 0 0 1
// 0 0 0 0 1
// 0 0 0 0 1
// 0 0 0 0 1
//
//
// if SUM == EVEN: (even amnt of Os)
//    Bob wins
// if SUM == ODD: (odd amnt of Os)
//    ALice wins
//-------------
//
// E O E O E O .....
//
// find the number of Os
//
// 2nd-order parity
//
//
// if odd amnt of Os

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n, k);
  IV(a, n);

  // ll cnt_odds = 0;
  //
  // ll ident_sum = 0;
  // II(i, n) {
  //   ident_sum += a[i];
  //
  //   // so if i<k, i takes over
  //   // and clearly i=0 (1@1) means even
  //   //  i=1 (1@2) means odd
  //   //
  //   // but the moment i>=k
  //   //      when (1@(i+1) or 1@(k+1)) means we have k left and entirely
  //   depends
  //   //      on the parity of k
  //   //
  //   // we gotta include the ins and outs
  //   //      remember, we always take odd out
  //   //
  //   // while ident_sum should be correct
  //   //
  //   // the min(k,i) should be the opposite?
  //   //
  //   // because if k is even, it is effectly odd by the 1 out
  //   // if k is odd, it is effectively even by the 1 out
  //   //          (odd in odd out)
  //   //
  //   // even when we hit the lower bounds with i's
  //   //
  //   // say k is very large but we have i=3
  //   //  (0@i=3 but 1@i+1=4th index)
  //   //  so still 3 elments left to add
  //   //  thats odd in but odd out (1 out again)
  //   //  so its effectively even
  //   //  but if say i+1 on the 3rd index adds 2 in (but takes 1 out remember)
  //   //  that is odd (so count 'evens')
  //   //
  //   //  wait but if say i is large and k is 3
  //   //  then odd in odd out means even (yes)
  //   //
  //   // if (min(k, i) % 2 == 1) {
  //   //
  //   // do we also have to consider the a[i] itself???
  //   // if (min(k, i) % 2 == 0) {
  //   //   // if ((min(k, i) * a[i]) % 2 == 0) {
  //   //   // if ((min(k, i) * a[i]) % 2 == 1) {
  //   //   cnt_odds++;
  //   // }
  //   // if ((k <= i + 1) && (i + 1 - k) % 2 == 1) {
  //   //   cnt_odds++;
  //   // } else if ((k > i + 1) && (k % 2 == 1)) {
  //   //   cnt_odds++;
  //   // }
  // }

  // ll cur_sum = a[n - 1];
  // DD(i, n - 1) {
  //   cur_sum += a[i] ;
  //   if (cur_sum % 2 == 1) {
  //   }
  // }

  // ll overall_sum = a[n - 1];
  // DD(i, n - 1) {
  //   a[i] += min(k, i + 1) * a[i + 1];
  //   overall_sum += a[i] - min;
  //   // overall_sum = a[i] - 1;
  //   // overall_sum += min(k, i + 1) * a[i + 1] - 1 + a[i];
  // }

  // ll overall_sum = a[n - 1];
  // ll consecutive_odds = 0;

  vll prefix(n + 1, 0);
  vll delta(n + 1, 0);
  II(i, n) { prefix[i] = a[i] % 2 == 0 ? 0 : 1; }
  DBG_ITER(prefix);
  DD(i, n - 1) { prefix[i] = (prefix[i] + prefix[i + 1]) % 2 == 0 ? 0 : 1; }
  DBG_ITER(prefix);
  DD(i, n - 1) {
    //!!!!!!!!!! LAST CORRECTION BEFORE AC (per chatgpt):
    //              WE'RE WORKING ON DELTA-SPACE HENCE WE SHOULD NOOOOT RECORD
    //              CHANGES STARTING FROM i-th PREFIX (should be i+1-th prefix)
    //
    //              IF WE WERE TO WORK IN PREFIX THEN WE WOULD DO IT FOR
    //              WHATEVER REASON LIKE SAY K-WINDOW SUM BUT WE"RE FINDING THE
    //              CHANGE THE DELTA, ESPECIALLY WHEN AT THE END WE APPLY THE
    //              CHANGES TO THE PREFIX ITSELF
    //
    //              also to be more clear, WE FOCUS ON THE CHANGE IN PARITY OF
    //              THE INCOMING SUM (per the special operation)
    //              WHICH CLEARLY EXCLUDES THE CURRENT PREFIX OF INTEREST (i-th
    //              prefix)
    //
    delta[i] = delta[i + 1] + (((prefix[i + 1] - prefix[min(n, i + k + 1)] +
                                 (delta[i + 1] - delta[min(n, i + k + 1)])) %
                                2) == 0
                                   ? 0
                                   : 1);
    // should be min(n,.) not n-1 (because it should be the first EXCLUDING
    // index)
  }
  DBG_ITER(delta);
  DD(i, n) { prefix[i] = (delta[i] % 2 == 1) ? (prefix[i] ^ 1) : prefix[i]; }

  DBG_ITER(prefix);

  ll odds = 0;
  // II(i, n) { odds += prefix[i]; }
  odds = prefix[0];

  // DD(i, n - 1) {
  //   // at n-2, we only have ONE k-segment
  //   //         times the number of rocks at n-1
  //   // at n-3, we we have TWO k-segment
  //   //         each times the number of rocks at n-2 and n-1
  //   //
  //   // but this is quadtatic... with 10^5 n
  //   //
  //   // prefix/suffix parity?
  //   //
  //   //
  //   //
  //   // E+E=O+O=E
  //   // O+E=E+O=O
  //   //
  //   // E*E=E*O=O*E=E
  //   // O*O=O
  //   //
  //   // if say a[i] is O
  //   //      do nothing
  //   // if say a[i] is E:
  //   //      make all a[i-k..i-1] to E
  //   //
  //   // E spreads out
  //   //
  //   // notice, it depends on the parities of the elements (after operation),
  //   not
  //   // strictly on the partiy of k itself
  //   //
  //   // if a[n-1] is E => overall is E
  //   // if a[n-1] is O => be cautious
  //   //
  //   // since k>=1 (always exist to carry the parities downward)
  //   //  that means, whenever we first reach an E, it will all be E after
  //   //  => count the # of initial CONSECUTIVE odds from the end
  //   //
  //   // but again be cautious we have the -1 offset
  //   //
  //   // if a[n-1] is O => a[n-1] becomes E but maintains the remaining Os
  //   //      invariant
  //   // if a[n-1] is E => a[n-1] becomes O but makes everything else E
  //   //
  //   // so if all Os => becomes all Es (eventually)
  //   //    if all Es => becomes all Os (eventually)
  //   //      more strictly,
  //   //      on the first E, everything after and itself becomes O
  //   (eventually)
  //   //
  //   //
  //   //~~~~
  //   // if a[n-1] is O => case 2 (a[n-1] is E)
  //   // if a[n-1] is E => count the number of elements
  //   // ~~~~
  //   //
  //   // on the first group of odds starting from a[n-1]
  //   //      this is the invariant case (it becomes E and we dont care)
  //   //      ~~~odds++;
  //   //      ~~~()
  //   // else, on the first occurence of even,
  //   //      odds += # of remaining elements + 1;
  //   //          (+1 for itself)
  //   //
  //   // so same case as before apparently
  //   //
  //   // ok so
  //   //
  //   // its a[i-k...i-1]+additional rocks from a[i]
  //   //
  //   //
  //   //
  //   // create a k-window prefix count of odds on the original array?
  //   // dp??
  //   //
  //   //
  //   // if 0-0 or 1-1: even parity
  //   // if 0-1 or 1-0: odd parity
  //   //
  //   // (i+k+1) represents the index (excluded)
  //   // dp[i] = dp[i]-dp[i+k+1]==0  ? 0: 1;
  //   //           b/c if the k-window suffix sum is odd (including i itself),
  //                then it should be updated to 1 (but that means all the
  //                elements before it msut be updated also)
  //
  //                create dp_neg[i] = ~dp[i]??
  //                and just swap the running dp???
  //                but the swap must only be after the current i...
  //
  //   // do another linear pass to count the number of 1s
  //
  //   if (a[i] % 2 == 0) {
  //     odds = i + 1; // 0@i, we have i remaining elements with +1 itself
  //     break;
  //   }
  // }
  //
  //
  // O(nlogn)??? => binary search on answer???
  //
  // check if Alice works? if not, then must be Bob??????
  //
  // !!!!! chatgpt: difference array
  //                    but don't we need the difference immediately??
  //    recall, parity itself works in changes even in an order above
  //
  //    if there's a parity change
  //          => the number of Os changes
  //          => subseq operations will merely reflect that 1-1
  //          (specifically, we're coutning the number parities and finding the
  //          2nd order parity of it. if one changes, the 2nd order changes 1-1)
  //          (similiar to XOR)
  //
  //
  //
  // odds = 0;

  // if its initially odd (say 1 0 0 0 0)
  // Alice should win
  //
  // if any operations add even amnt it changes something (by the -1 offset
  // making it odd)
  // if anyo peration adds odd mant it changes nothing
  // if (ident_sum % 2 == 1) {
  //   cnt_odds++;
  // }

  // bool alice = ((cnt_odds % 2) == 1);

  // alice = (overall_sum % 2) == 1;

  // alice = odds % 2 == 1;

  bool alice = odds % 2 == 1;

  if (alice) {
    O("Alice");
  } else {
    O("Bob");
  };
}
