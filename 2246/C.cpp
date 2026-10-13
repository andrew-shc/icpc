#include <bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using vll = std::vector<ll>;
using dll = std::deque<ll>;
using pll = std::pair<ll, ll>;
using vpll = std::vector<pll>;

const ll NEG = (long long)-4e18;
const ll MOD = 1000000007;
//             1000000007
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

// start: 1736
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
// given -1 1 1 2 3
//
// 1 1 has an alternating sum of 0
// 1 2 1 also
// 2 3 1 also
//
// or
// 1 3 2
//
// DP
//
// -1 1
// 1 -1
//
// += [1]
//
// no change in #
//
//  += [2]
//
// 1 -1  the -1 -> 2 1
// 1 2 1
//
// 1 -1
// 1 1 2 -> -1 -> 1 2
//
//
//
//
// alternating sum is
//
//
// + - + - + - + - + - ..
// ^ starts positive
//
//
// (???)O.1: IF we do DP (or something like it), we have to add elements TWO by
// TWO
//      unless it is another duplicate element (which we then just multiply it
//      by the # of unique locations the original element resides in so when
//      swapped it can be counted differently => # of unique index position of
//      the original el.)
//
//      because incorporating 1 element either shifts the carefully balanced
//      alternating sum to >0 or <0
//
//      HOWEVER, this assumes ALL elements are used; what if they're not?
//
//      (also why is it non-decreasing as if the soln is suppose to be linear or
//      sub-quad.)
//
//      for example:
//          say 3 5 8
//
//          3 5 does not work whatsoever
//
//          on
//          += [8]
//
//          3 8 5
//          5 8 3
//          but that requires the insertion of the incoming element to the
//          middle actually didn't we say insert in pairs of elements?
//
//          say we start with the 1st element only and insert pair by pair
//                  (and one more at the end if even)
//
//          += [5 8]
//
//          3 8 5 works
//
// O.2: given a seq, all odd and even indices can be swapped freely
//          suppose l even indices and k odd indices, then l!+k! free
//          additional arrangements.
//
//      since this part is easy to calculate, let us abstract the definition of
//      two sets of seq being different to actually different values (not just
//      swapping) and lengths
//
//      O.2/1: what about swapping values across even and odd indices?
//             when you swap them, they must be equal or else it goes out of
//             balance (swap in even amount of elements with half odd and half
//             even)
//
//             1. if a pair of odd/even-indices are equal => x2 count
//             2. if 2 pairs of odd/even-indices are equal => x2 count
//
//             too many "observations" is there a more elegant, concise thematic
//             observation?
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Hint 1: the subseq must contain an even # of elements from every group of
//          equal numbers??
//
//          i'm pretty sure there can be odd # of elements for SOME group of
//          equal? numbers??
//
// Hint 2: # of ways to pick an even size subseq == # of ways to pick an odd
//          size subseq
//
//          no useful??
//
// Hint 3:
//          simple formula for only positive elements
//
//          p1 p2 p3 p4 p5
//
//          p1-p2+p3-p4 its complicated becauuse p1+p3=p2+p4
//              and even more complicated with cases like
//          p1-p2+p3 => p1+p3=p2
//
// O.3... hopefully a much concise, nice-to-work-with observation
//          sum of selected elements to be added (ordered)
//          = sum of selected elements to be subtracted (ordered)
//
//          O.3/1: the # of selected elements to be subtracted must be equal to
//          or one less than the # of selected elements to be added
//
//          O.3/2: clearly, it can easily flip the other way around (if the
//                  amounts are same per O.3/1)
//
//          O.3/3: with over length and O.3/1... this could be manageable
//
//          O.3/4:  0 = 0
//                  p1 = n1
//                  p1+p2 = n1
//                  p1+p2 = n1+n2
//                  p1+p2+p3 = n1+n2
//                  p1+p2+p3 = n1+n2+n3
//
//                  two pointers???
//
//                  problem, given selected sequence length we have to find all
//                  the possible arrangements it has... leading up to  quad
//                  soln.?
//
//
// 1 1 2 => 1-1 or 1-2+1... how does one systematically pick a number?
//
// break up into 2 cases? even and odd lengthed subseq? (inspired by the hints)
//
// consider even-lengthed subseq (actually splitting cases like this helps
// consider its just two kinds of cases yet they have rather quite a diffirerent
// interaction with the sum that warrants a separation or else it will just be
// too complicated to handle in a uniform way)
//      EVEN CASE:
//          0 = 0
//          p1 = n1  => basically pair-wise matching
//          p1+p2 = n1+n2  ==> needs to find all the additive combination
//          p1+p2+p3 = n1+n2+n3
//              consider 1+2+3 = 8-1-1 => pair-wise matching would not work, DP
//                                        over subseq length to sum would not
//                                        work
//
//              ADDITIVE COMBINATION:
//                  -1 +  6 = 5
//                   1 +  4 = 5
//                   2 +  3 = 5 ==> half-way point is reached
//                   3 +  2 = 5         looking further down is looking for
//                   4 +  1 = 5         different arranagements of existing
//                   6 + -1 = 5         selected numbers
//
//                  -1 + -1 +  7 = 5
//                  -1 +  1 +  5 = 5
//                  -1 +  7 + -1 = 5
//                  etc...
//
//                  -1 + 6 = 3 + 2 ???/
//
//                  or even
//
//                  1 + 4 = 2 + 3??
//
//                  1 2 4 3 => 1-2+4-3=0
//     ODD CASE: per O.3/1
//          p1+p2 = n1
//          p1+p2+p3 = n1+n2
//          p1+p2+p3+p4 = n1+n2+n3
//
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// MISSED ASSUMPTION FROM THE PROBLEM: A SUBSEQ MUST HAVE A STRICTLY INCREASING
// INDEX
//      1<i1<i2<...<ik<=n
//
//  clearly,
//      i<j => a[i] <= a[j] (excluding 0)
//
//  EVEN CASE: (seen the 1st proof the soln.)
//      ai1-ai2 +ai3-ai4 +... => every pair of +'s and -'s must be 0 or negative
//          => PAIR-WISE 0 REQUIRED (and also mainly b/c of the strictly
//          increasing index that helps reduce problem complexity)
//
//  ODD CASE:
//      ai1 -ai2+ai3 -ai4+ai5 => every later pairs must be 0 or positive
//          => the sum of later pairs (excluding ai1) must be 0 or positive
//          => ai1 must be 0 or -1
//          => the SUM of later pairs must be 0 or 1
//       since every later pairs (individual pairs) must be 0 or positive
//          => every later pairs must be 0 but allow A pair to have a pair-sum
//             of 1
//
// O.4: k1 != k2 AND strictly increasing indices AND same length
//          ==> it just mean an index got removed and another index got inserted
//
// O.5: for EVEN-lengthed subseq => pair-wise sum MUST be 0
//      for ODD-lengthed subseq =>
//          1. ai1 MUST be -1
//          2. ONLY ONE later pair MUST have a pair-sum of 1
//          3. remaining later pairs MUST have a pair-sum of 0
//
// O.6: suppose i<j and both their indices are getting further apart it is less
//      likely for a[i]-a[j] or a[j]-a[i] to be 0 ==> the moment the pair-sum is
//      no longer 0, it will no longer be 0 because of the non-decreasing
//      condition => no point in further looking => only look for pairs within
//      the same\duplicate numbers (except for the pair-sum that needs 1 then
//      look for at most one value of difference away)
//
//      ==> LOOK FOR DUPLICATE VALUES!! (and adjacent one-off values!)
//
// O.7: given say 3 3 3 3 3 (a group of duplicates)
//       the 1st has 4 choices
//       the 2nd has 3 choices
//       so given a n-lengthed duplicates
//          we get n(n-1)/2 choices to select that duplicates for the indices
//
//       however, we can also select multiplie PAIRS (esp. when n>3)
//
//       so,
//       on the 3rd has 2 choices (but also has a choice for another pair before
//       it)
//
//       DP???
//
//       5 of say some number X
//
//       x 4 3 2 1
//         x 3 2 1
//       1 x x 2 1
//       1 2 x x 1
//
//       say 7
//
//                 v v 1 additional pairs???
//       x 6 5 4 3 2 1
//         x 5 4 3 2 1
//       1 x x 4 3 2 1
//       1 2 x x 3 2 1
//       1 2 3 x x 2 1
//       1 2 3 4 x x 1
//       ^ ^ 1 additional pairs?
//
//       consider this say 7
//       1-pair [l1,r1]
//       2-pair [l1,r1] [l2,r2]
//       3-pair [l1,r1] [l2,r2] [l2,r2]
//
//       the 2nd proof shows that the # of subseq with even # from each group is
//       2^(group size-1) ????
//
//   x x x x 8 possible subseq per 2^(4-1)?????
//
//   3 2 1   = 6
//     2 1   = 3 ** double-counted
//       1   = 1 ** double-counted
//   - - 1   = 1 = 11??1
//   1   - - = 1 = 8!! (but why)
//
//   [ ]
//   [   ]
//   [     ]
//     [ ]
//     [   ]
//       [ ]
//   [ ] [ ]
//   [ ] [ ]
//
//
//   1 2 3 4
//
//   (1,2)-(3,4)
//   (1,3) (2,3)
//   (1,4) (2,4) (3,4)-(1,2)
//
//   2x2x2x1....
//
//   ok given a set of element of size n,
//   there are 2^n ways to make a unique subseq out of it (unordered)
//
//      say n=4 => 2^4 = 16
//
//   . . . .   (none)
//   . . . x ~ (picked last ind)
//   . . x . ~
//   . . x x
//   . x . . ~
//   . x . x
//   , x x .
//   . x x x ~
//   x . . . ~
//   x . . x
//   x . x .
//   x . x x ~
//   x x . .
//   x x . x (invalid)
//   x x x . (invalid)
//   x x x x
//
//   insight:
//      whenever there are odd bits, remove that combination
//          => whenever we select/choose odd amounts (regardless of order)
//                  IMPORTANT: regardless of order is NOT because we want a
//                  subset (which is inherently order-less),
//                             rather, it's because we want a subSEQ that is
//                             strictly increasing (i.e., portion of an ordered
//                             combination that can be treated as unordered)
//                             AND it's not because 2^n is unordered and we're
//                             trying to converted from an ordered to an
//                             unoordered but rather because we just want an
//                             intrinsic formula that counts the combinations in
//                             an unordered way (or treated like an unordered
//                             way) with no extrinsic conversion (w.r.t.
//                             permutation)
//
//                             in other words, just use the choose formula.
//                             permutation is unrelated (not for the problem)
//              2^n-n choose 1-n choose 3-n choose 5- etc..
//
//              2^n-sum(n!/k!(n-k)!) where k is odd
//
//                      -n!/(n-1)!-n!/(n-3)!-etc...
//
//                      PFDs??
//           ==> new axiom to learn, odd parities = even partities on
//               binaries/subsets ==> n/2,n/2 ==> since we want just an even
//               parity we get 2^n/2 => 2^(n-1)
//
//   trivially, for d unique/distinct numbers, we get 2^(n-d) combination
//   (including -1) for even
//
//   now, with an odd number, we require an initial -1 and another pair with
//      odd pair-sum (don't we just need 1??? b/c recall that this is a
//      non-decreasing array with a strictly increasing index subseq)
//
//      O.8/1
//      soln. did correctly say we just need to find the locations of (v,v+1)
//      (we strictly only want one and only one, no less no more)
//
//      O.8/2
//      the soln. mentions the odd pair-sum to be in the -1 group which makes
//      sense since if we have -1 -1 -1 -1 -1 -1
//              we can technically take 1@4 (4th index) or even 1@6 (6th index)
//              and ignore the earlier indices and continue on
//
//      O.8/3
//      because there are no 0s, the problem is much more easier and we do not
//      have to consider the possibilities of (v,v+1) interacting with the
//      special -1 group in the beginning
//
//   if initial -1 exist,
//      the -1 is taken from the group of -1s so like 2^(n-d-1)
//           ^^ this is probably wrong because if we take the whole -1 group out
//           it's the same result??
//
//           oh no if we take the whole -1 group out its the 2^(n-d-(g-1))
//              where g is the # of -1s
//
//      O.8/1
//      find #s of (v,v+1) for >=1 groups
//          MULTIPLIED separately to 2^(n-d-1)
//
//      O.8/2
//      suppose g is the # of -1s
//          g is the # of ADDITIONAL possibilities for the incoming -1 to come
//          in (multiplied)
//
//          however, if g is even, then there is a 2^g/2 (half-chance)
//          combinations the first elemeent gets taken? but the -1 in 2^(n-d-1)
//          already factors this in so the -1 pairs can only be started from the
//          2nd index (another half the # of combinations removed)
//
//          so like
//
//          -1 -1 -1 -1 -1 -1   vvv summed
//           *  -  -  -  -  -  2^(g-1-1) * (g-5)
//           *  *  -  -  -  -  2^(g-2-1) * (g-4)
//           *  *  *  -  -  -  2^(g-3-1) * (g-3)
//           *  *  *  *  -  -  2^(g-4-1) * (g-2)
//           *  *  *  *  *  -  2^(g-5-1) * 5   << do we include this?? (no)
//                                             remember, if we expand this to
//                                             individual combination, it is
//                                             clearly seen that it is just a
//                                             specialization of the next case
//                                                  notably, the last element is
//                                                  assuemd to be never picked
//                                                  by the logic of 2^(g-1)
//                                                  because it can never be
//                                                  chosen
//           *  *  *  *  *  *          1 * (g)
//                             -------------
//                             all sorts of combination for -1 in odd case
//
//                             MULTIPLIED
//
//                             by all the combination possibile after with
//                             2^(n-d-1) since they're INDEPENDENT from the
//                             choice within the -1 groups as long two things
//                             are satisfied:
//                                  1. -1 is taken individually
//                                  2. a SINGLE (x,x+1) pair is found
//
//                             conditional independence??
//
//
//           which depends on how much of the -1s are taken to make a pair-sum 0
//
//
//          note, some double countings are involved. consider the following..
//
//          * * * * * - -  1.
//          * * * * * * *  7 ways to select the -1
//                   WHICH INCLUDES
//                  * - -  that assumes no subSEQ are chosen
//                          (- - is empty)
//
//                         but the case 1. already has that counted
//                  * - -
//
//          unless we do inclusion-exclusion, there's must be an easier way
//
//          by this logic, the formulae would be
//              +2^(g-1-1)
//              +2^(g-2-1)
//              +2^(g-3-1)
//              +2^(g-4-1)
//              +1          // 1-remaining spot => no subSEQ can be selected
//                              GIVEN the individual -1 is selected at @-2
//              +1          // 0-remaining spot => -1 is selected at @-1
//
//              and also we assume g>=3
//
//              this can be simplified as
//              if g==1:
//                  +1
//              if g==2:
//                  +2
//              if g>=3:
//                  +2+2^(k*(g-1)-k(k+1)/2)   for k=g-2
//
//
// IMPL:
//
//
// mod math rules:
//
//      (x+y)%m == (x%m+y%m)%m
//      (x*y)%m == (x%m * y%m)%m
//      modular exponentiation is useless when there are large intermediates
//
//
//
//
// according to chatgpt there's some errors..
//
//
// going back to the editorial:
//
// for the -1 group, we actually want ODD selection!!!!!! (that's where the odd
// came from)
//
//
// and by previous logic, it is just 2^{g-1}!!!!!! (same as the even case)
//  because by the special property of number of even parities,
//  the number of odd parities is the same
//
// so actually it's literally just 2^{n-d}*v (if -1 is present)
//
//

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n);
  IVLL(a, n); // -1 or >=1 (but no 0), non-decreasing order

  // ll m = 0;

  ll d = 1;
  ll v = 0;
  ll g = 0;
  II(i, n) {
    if (i != n - 1) {
      if (a[i] != a[i + 1]) {
        d++;
      }
      if (a[i] + 1 == a[i + 1]) {
        v++;
      }
    }
    if (a[i] == -1) {
      g++;
    }
  }

  // EVEN case  2**(n-d)
  ll even = 1;
  II(_ii, n - d) {
    even = (even * 2) % MOD; // assumes prior even has been MODded }
  }

  // ODD case
  ll odd = 0; // 2**(n-d-g+1)
  if (g > 0) {
    odd = 1;
    II(_ii, n - d) { odd = (odd * 2) % MOD; }
    odd = (odd * v) % MOD;
    // odd = 1;
    // II(_ii, n - d - g + 1) { odd = (odd * 2) % MOD; }
    // // EDGE CASE TO CONSIDER:
    // //  -1 1   (n=2,d=2,g=1)
    // //          n-d-g+1=2-2-1+1=0
    // //          ends with =1 for 1 possibility which is fine (should be fine)
    // odd = (odd * v) % MOD;
    // // v = 0 => impossible
    //
    // ll g_combs = 0;
    // if (g <= 2) {
    //   g_combs = g;
    // } else {
    //   g_combs = 1;
    //   // +2^(k(g-1)-k(k+1)/2)
    //   ll k = g - 2;
    //   II(_ii, k * (g - 1) - (k * (k + 1)) / 2) {
    //     g_combs = (g_combs * 2) % MOD;
    //   }
    //   g_combs = (g_combs + 2) % MOD;
    // }
    // // // last case where no 0 pair-sum is picked, just -1 individually
    // // for (ll f = 2; f <= g - 1; f++) {
    // //   // 2**(g-f)*(f-1)
    // //   // binpow? (binpow standards for BINARY power not because of binary
    // as
    // //   in
    // //   // 2^x)
    // //   //
    // //   // say 2^33 = ((((2^2)^2)^2)^2)^2 * 2
    // //   // (nope work with bits)
    // //   ll exp = 1; // per the observation below setting exp=2 is fine and
    // //   nicely
    // //               // works with base = base*base
    // //   // no per the observation, base=2 is fine but exp needs to be =1
    // (start
    // //   // with =1)
    // //   ll pows = g - f; // g-2 to g-(g-1)=1
    // //                    // this for loops only runs whenever g-1>=2 => g>=3
    // //   // which means the first the for loops allows to run it's when
    // //   // 2^(1) * 1 (so at least one exponent guaranteed starting from 2)
    // //   ll base = 2;
    // //   while (pows) {
    // //     // assumes base has been modded before
    // //     if (pows & 1) {
    // //       exp = (exp * base) % MOD; // * not +
    // //                                 // remember,
    // //                                 // 2^7= 2^0b0111 = 2^1*2^2*(2^2)^2 =
    // //                                 // 2^(1+2+2^2)=2^(7)
    // //                                 // not 2^1+2^2+2^4
    // //     }
    // //     base = (base * base) % MOD;
    // //     pows >>= 1;
    // //   }
    // //   // ll exp = 1;
    // //   // ll pows = g - f;
    // //   // while (pows >= 2) {
    // //   //   exp = exp * 2;
    // //   //   pows /= 2;
    // //   // }
    // //   g_combs = (g_combs + (exp % MOD) * ((f - 1) % MOD)) % MOD;
    // // }
    // odd = (odd * g_combs) % MOD;
  }

  O((odd + even) % MOD);
  // O(m % MOD); // number of different subSEQ with alternating sum of 0
  // where the lengths are different or the indices are swapped
  // (or have different value simply)
  ;
}
