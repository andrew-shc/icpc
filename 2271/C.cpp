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
// 1. find array a with the max. beauty |a| -f(a)
// 2. find one that maximizes |a|
//
// so find |a| -f(a) first and if multiple find the one with the largest |a|
//
// f(a) = # of non-empty subarrays s.t. all elements within it when XOR'd = 0
//              => all elements within it have even parity
//
//
//
//
//              0 0 0 1 1 1
//              1 1 1 0 0 0
//              1 0 1 0 1 0
//              0 1 0 1 0 1
//          XOR 0 0 0 0 0 0
//
//          we're trying to find a CONSTRUCTION that satisfies this
//
// IF |a| == 1 THEN it must only have 0
// IF |a| == 2 THEN both elements must be equal
// IF |a| == 3 THEN whatever
//
// but we actually not trying to maximize the sum of a[],
//      we're actually MAXIMIZING THE # OF SUBARRAYS with XOR = 0
//
//      isnt this just 0 0 0 0 0???
//
// NONONONON WE'RE MINIMIZING THE # of SUBARRAYS | XOR = 0
//
//
// so
// IF |a| == 1 THEN any a!=0 is fine
// IF |a| == 2 THEN ... remember every element can be 0 to at most n (inclusive)
// IF |a| == 3
//
//
// the point of stopping is when |a| - f(a)
//     |a|++ => f(a)++ => no point in increasing anymore
//
// when n = 1
//  we only have 0b0,0b1
//
//       0,1,0
//       3-0 ???
//
//       3-0
//
//       0 XOR 1 = 1
//       1 XOR 0 = 1
//       0 XOR 1 XOR 0 = 1
//
//       0 itself is an "XOR" = 0
//
//       so it should 3-2=1
//
// H.1       can we omit 0?
//
//       1 1 0 XOR=0       1 1 0 0
//       vs.
//       1 1 1 XOR=1       1 1 1 1
//
//
//
//       do 0s make the problem harder
//
//
//
// n=5 (remember, 0<=a[i]<=n)
// deeper => |a|++ (good)
// any subarrays with ALL bits w/ even parity => f(a)++ (bad)
// we want... every increase of |a|++,
//              f(a) to increase at most 1
//              if f(a) increases more than 1 => stop
// KEY INVARIANCE: an additional element always makes f(a) stay the same or
//                  increase (never decrease f(a)) (but we want f(a) to stay the
//                  same or increase at most 1)
//
//      every additional element we can check like this...
//          check for all bits with having even parity from the new element
//          itself to slowly include all the elements before it to the first
//          element
//
//  0 1 0 1  f==
//  0 0 1 0  f==
//  0 1 0 0  f++ (bad)
//
//
// n=5
//      0 1 0 1
//
//      0 0 0 1 f==
//      0 0 1 0 f==
//      0 1 0 0 f==
//      0 0 0 0 f++
//      0 0 1 1 f==
//      0 1 0 1 f== (notice, the powers of 2 really helps)
//      0 1 0 0 f++ (repeats of powers of 2 bad)
//      0 0 1 0 (something went wrong we're suppose to check for parities also)
//
//
// n=2  0b10
//
//     0 1 f==
//     1 0 f==
//     0 0 f++
//     0 1 f==
//     1 0 f++
//     1 0 f++
//     0 1 f++>1 (but if we move the 0 0 at the end it won't)
//
//
// n=2
//     0 1 f==
//     1 0 f==
//     0 1 f==
//     1 0 f++ (@ 1st index)
//     1 0 f++ (@ the index before)
//     0 1 f++ (@ 3rd index)
//     0 0 f++ (@ 3rd index)  NOTICE: 0 is a freebie at the end (NO IT IS NOT IT
//     ITSELF ++)
//
// n=2
//     0 1 f==
//     1 0 f==
//     0 1 f==
//     1 0 f++ (1@1)
//     0 1 f++ (1@2)
//     1 0 f++ (1@3)
//     0 1 f++ (1@4)      <- ???
//     1 0 f++>2 (1@5,1@1)
//     ~~ 0 0
//
// n=1 (0b1)
//     1 f==
//     1 f++ (1@1)
//     0 f++ (1@3,itself)
//     1 f++ (1@2)
//     1 f++>1 (1@3,1@1)
//
// more standardized
//
// n=1 0b1
//      1 f==
//      1 f++ (1@1)
//      1 f++ (1@2)
//      0 f++ (1@3, itself) <-- seems to only work for n=1
//
// n=3 0b11
//      0 1 f==
//      1 0 f==
//      0 1 f==
//      1 0 f++ (1@1)
//      0 1 f++ (1@2)
//      1 0 f++ (1@3)
//      0 1 f++ (1@4)
//                          would 1 1 help at all???
//                          having all 1s just accelerate the process to f++>1
//                          (bad) instead of splitting each bits to expand or
//                          spread out
//
// n=1+4+8+32=45    0b101101
//
//      0 0 0 0 0 1
//      0 0 0 0 1 0
//      0 0 0 1 0 0
//      0 0 1 0 0 0
//      0 1 0 0 0 0
//      1 0 0 0 0 0
//      0 0 0 0 0 1
//      0 0 0 0 1 0
//      0 0 0 1 0 0
//      0 0 1 0 0 0
//      0 1 0 0 0 0
//      1 0 0 0 0 0
//      0 0 0 0 0 1
//      0 0 0 0 1 0
//      0 0 0 1 0 0
//      0 0 1 0 0 0
//      0 1 0 0 0 0
//      1 0 0 0 0 0
//      0 0 0 0 0 1
//      0 0 0 0 1 0
//      0 0 0 1 0 0
//      0 0 1 0 0 0
//      0 1 0 0 0 0 << 3 4 4 4 4 4
//

//      1 0 0 0 0 0  << has to be excluded or at the end its 4 4 4 4 4 4 (XOR=0)
//                      instead of 3 4 4 4 4 4 (XOR=1)
//      wouldnt
//      0 0 0 0 0 0 help? (no remember, it cycles one more time with 2 2 2 2 2 2
//      XOR=0 but that's with elements that STARTS with XOR=1 but 0 starts with
//      XOR=0)
//
//      again, things like 0 0 1 0 0 1 are UNoptimal because it accelerates the
//      process (shortens |a|)
//
//      again, we can't add 0 0 0 0 0 0 in the beginning because then all the 2
//      2 2 2 2 2 2 will pair with it like maggots and increase f>1
//
//
//
// IMPL:
//      k = 2^log2(n)
//      3 times
//      for i in 1..=k:
//          append(1 << i-1)
//      1 more time of
//      for i in 1..<k:
//          append(1 << i-1)
//
//
//  ~~~~~~~
//
//  0 0 0 0 0 1
//  0 0 0 0 1 1
//  0 0 0 1 1 1
//  0 0 1 1 1 1
//  0 1 1 1 1 1
//  1 1 1 1 1 1
//  1 1 1 1 1 2
//  1 1 1 1 2 2
//  1 1 1 2 2 2
//  1 1 2 2 2 2
//  1 2 2 2 2 2
//  2 2 2 2 2 2 <-- ++
//  2 2 2 2 2 3
//  2 2 2 2 3 3
//  2 2 2 3 3 3
//  2 2 3 3 3 3
//  2 3 3 3 3 3
//  3 3 3 3 3 3
//  3 3 3 3 3 4
//  3 3 3 3 4 4
//  3 3 3 4 4 4
//  3 3 4 4 4 4
//  3 4 4 4 4 4
//
//  3 4 4 4 4 4
//  3 4 4 4 4 6
//  3 4 4 4 4 4
//  3 4 4 4 4 5 ??? (remember, this means 4 is included within so 3 4 4 4 4 4
//  would be added twice => ++>1)
//
//
//  n=2
//
//  0 1
//  1 1
//  1 2
//  2 2 ++
//  2 3
//  3 3
//  3 4
//  3 5 ??? k=8??
//
//  0 1
//  1 0
//  0 1
//  1 0
//  0 1
//  1 0
//  0 1
//
//
//  n=3
//
//  1 1 <<??? (no?? f++>1)
//  0 1
//  1 0
//  0 1
//  1 0
//  0 1
//  1 0
//  0 1
//
//
//  n = 5 (0b101)
//
//  ~~0 0 1 << 0 0 0 clearly doesnt work, neither 1 0 0 nor 0 0 1
//  0 1 0 <<??? seems like it has something to do with middle bits
//              mostl ikely with the order of adding the bits always starts with
//              the right-most and ENDS with left-most but putting it in the
//              center out-syncs this (also remember since we start with adding
//              bits on the RIGHT-MOST, doing an extra ... 1 results in even
//              partiy with the last one having +2 while the 1 .... results in
//              all even parity with same parity numbers earlier)
//  0 0 1
//  0 1 0
//  1 0 0
//  0 0 1
//  0 1 0
//  1 0 0
//  0 0 1
//  0 1 0
//  1 0 0
//  0 0 1
//  0 1 0 << 3 4 4 remember, any increase on the 4 would double count 3 4 4???
//
//
//
// again
//
// n = 45  0b101101  (also at this point adding them at both ends does not
// change anything other than how the additional stuff is added in the order of)
//
//      0 0 0 0 0 1
//      0 0 0 0 1 0
//      0 0 0 1 0 0
//      0 0 1 0 0 0
//      0 1 0 0 0 0
//      1 0 0 0 0 0
//      0 0 0 0 0 1
//      0 0 0 0 1 0
//      0 0 0 1 0 0
//      0 0 1 0 0 0
//      0 1 0 0 0 0
//      1 0 0 0 0 0
//      0 0 0 0 0 1
//      0 0 0 0 1 0
//      0 0 0 1 0 0
//      0 0 1 0 0 0
//      0 1 0 0 0 0
//      1 0 0 0 0 0
//      0 0 0 0 0 1
//      0 0 0 0 1 0
//      0 0 0 1 0 0
//      0 0 1 0 0 0
//      0 1 0 0 0 0 << 3 4 4 4 4 4  (no 1 0 0 0 0 0 or 0 0 0 0 0 1)
//                                                  since ^ results in
//                                                  2 2 2 2 2 2
//                                                  to
//                                                  2 2 2 2 2 3
//                                                  but, to
//                                                  2 2 2 2 2 4
//                                                  while also having
//                                                  0 0 0 0 0 2 in the start
//      0 0 0 0 1 0 << 3 4 4 4 5 4 (in earlier numbers it will)
//      0 0 0 1 0 0 << 3 4 4 5 5 4 (2 2 2 2 2 2 becomes 2 2 2 3 3 2) (it has an
//      offset of 1 somewhere)
//      0 0 1 0 0 0    3 4 5 5 5 4
//      0 1 0 0 0 0    3 5 5 5 5 4
//      0 0 0 1 0 0
//      0 0 1 0 0 0 ??
//
//      bit-cycles???
//
// clearly, +2 does nothing (cycles back the parity)
//
//    +0 +0 +0 +0 +0 +0 we can do 000000->111111->222222->333333->344444
//    +0 +0 +0 +0 +1 +0 we can do
//    000010->111121->222232->333343->344454->444454?
//    +0 +0 +0 +0 +0 +1 000001->000002->222224
//
//    000000->222222->333333->444443->
//
// k=2^(floor(log2(n))+1)-1??? lmao unlikely
//
//                 <
// +0 +0 +0 +0 +0 +0
// +0 +0 +0 +0 +0 +1 <- nope, since we start adding it here at some point it
//                      will have an extra XOR=0
// +0 +0 +0 +0 +1 +0 <- good, since the point of adding it is fine
// +1 +0 +0 +0 +0 +0 <- bad, because before it completes the last one is already
//                      filled
// +0 +0 +0 +1 +1 +0 <- good, since the point of adding it is fine and not where
//                          the 2 last bits are being added before
// +0 +1 +0 +0 +1 +0 <- is actually fine since we're still only completing a
//                          cycle at the end but do beware that the order of
//                          shifting cycles might matter ????
// +0 +0 +0 +1 +1 +0 -> end at 344444
// +0 +0 +1 +1 +1 +0 -> 344454 -> 455554 -> 566664 -> 677774 -> 788884 ->
//                      remember going from end to beginning is like
//                       000010 -> 111110 -> 222220 -> 333330 -> 344440 ->
//                       344440 -> 455551 (parities completely out of cycle)
//                       nono
//                       its like
//                       100000 -> 111110 -> 222221 -> 333332 -> 444443 ->
//                       455554 (the original cycle then continues at an off by
//                       one)
//                      from bottom / end
// +0 +1 +1 +1 +1 +0 ->                            (going to the previous cycle)
// 010000->121111->232222->343333->353333->454444->554444->
//
// easier observation?
//
// 000000
// 000001
// 111112
// 222223
// 333334
// 344444
//     |
// 344454 000010
// 455565 111121
// 566676 222232
// 677787 333343
// 788887 444443
//    |
// 788987 000100
// 899X98 111211
//
//        until
//        010000
//
// meta-cycle this log2(n) times (but be careful with <=n)
//                                if >n: skip? but some bits will lag and just
//                                increase complexity..
//
//                                if say <=0b101101
//                                but we need 0b110000
//                                can we do 0b100000
//                                          0b010000 to fix it?
//                                  but this expands the array so why not do it
//                                  for every?
//                                  oh of course we are only increasing it bit
//                                  by bit not 0b110000 so no worries
// 000001
// 344444
// 000010
// 444443 788887
// 000100
// 444434 888877
// 001000
// 444344 888778
// 010000
// 443444 887788
// 100000
// 434444 877888
// ------
//
// 01
// 10
//
// 001
// 010
// 100 with k>2 would cycling work or is this just specific cases
//
// 344
// 443
// 434
//
// 000001
// 000010
//     xx
// 000100
//    xxx
//
// 000001
// 000010
// 000001
// 000010
// 000001
// 000010
// 000001
// 000100
// 000001
// 000010
// 000001
// 000010
// 000001
// 000010
// 000001
// 000100
//
// POST COMPETITION
//
// ok think of it like this
//
// b1 b2 b3 b4 b5 b6
// nonono
//
//
//       max atomic sub-units (|a| = 7)
//         v v
// 0 0 0 0 0 1
// 0 0 0 0 1 0
// 0 0 0 0 0 1
// 0 0 0 0 1 0
// 0 0 0 0 0 1
// 0 0 0 0 1 0
// 0 0 0 0 0 1
// 0 0 0 1 0 0
// 0 0 0 0 0 1
// 0 0 0 0 1 0
// 0 0 0 0 0 1
// 0 0 0 0 1 0
// 0 0 0 0 0 1
// 0 0 0 0 1 0
// 0 0 0 0 0 1
// 0 0 1 0 0 0
//         x x
// 0 1 0 0 0 0
//         x x
// 1 0 0 0 0 0 --> 1111XX...
//
// ---------------
//
// 0 0 0 0 0 1
// 0 0 0 0 1 0
// 0 0 0 0 0 1
// 0 0 0 0 1 0
// 0 0 0 0 0 1
// 0 0 0 0 1 0
// 0 0 0 0 0 1
// 0 0 0 1 0 0
// 0 0 0 0 0 1
// 0 0 0 0 1 0
// 0 0 0 0 0 1
// 0 0 0 0 1 0
// 0 0 0 0 0 1
// 0 0 0 0 1 0
// 0 0 0 0 0 1
// 0 0 1 0 0 0
// 0 0 0 0 0 1
// 0 0 0 0 1 0
// 0 0 0 0 0 1
// 0 0 0 0 1 0
// 0 0 0 0 0 1
// 0 0 0 0 1 0
// 0 0 0 0 0 1
// 0 0 0 1 0 0 ??? <-- this actually works since within each atomic sub-units
//                      XOR always 1, and the moment it goes out the left 4 bits
//                      gets changed to keep the condition true
//
//
// Hint 3:
//      ~~~
//
//      ~~~~~ major missed observation:~
//          as long as x!=y ==> x^y!=0
//          XOR a_i != 0 when a_i are all different ?? (nope)
//
//          0 0 0 0 0 1
//          1 1 1 1 1 0
//          1 1 1 1 1 1
//          2 2 2 2 2 2
//
// ok Hint 1-3 all mentions "prefix XOR"
//      how would this help us????
//
// suppose prefix_xor[i] = prefix_xor[i-1] ^ a_i
//      => tells us the parity so far
//          major (?) observation: we only care about the running parity
//                                 that tells us all the necessary info whether
//                                 a_i keeps f the same, increments f, or even
//                                 >1 increment of f
//                                 (assuming we know prefix_xor[i-1] is valid as
//                                 whatever valid means)
// (sort of checked the main solution that prefix_xor[0]=0)
//      prefix_xor[0]=0 makes sense since we're initializing all the parities to
//                          "empty"
//      prefix_xor[1]=prefix_xor[0]^a_0  injects additional parities from a_i
//      prefix_xor[2]=prefix_xor[1]^a_1  as long !=0 ==> works?
//
//      okok but this only helps us with checking the validity but we want
//      CONSTRUCTION??
//
//  p_{l-1}=pr <=> [l,r] has an XOR=0 (since whatever elements from l to r
//  inclusive adds did not change the prior parity means the offset for each
//  parity was even hence XOR is 0 from l to r)
//      ok but how does that help with construction?
//
//      ==> ONLY when p_{l-1}=pr DO [l,r] has an XOR=0
//              similiar to the previous construction of
//                    ... 0 1
//                    ... 1 0
//                    ... 0 1
//                    ... 1 0
//                    ... 0 1
//                    ... 1 0
//                    ... 0 1
//      ==> if there are say p_1=p_2=p_3 => not just f+=2 bad, but f+=3 bad
//              since p_1=p_3 also
//              and goes without saying this is just bad
//              so why only p_1=p_2?
//                  because it increments f by at most 1 while |a| increments by
//                  1
//                  whereas p_1=p_2=p_3 (because of the p_1=p_3)
//                      actually makes f+=3 while |a| at most increases by 2
//                      (bad)
//              ^^^^^ hint 2
//      ==> we only want at most one p_1=p_2 equality
//              OK but how does this help with construction?
//              note: x is the k here
//              sensible that ai<=n<2k
//                                 ^
//                                 key idea, if n=2k, then ai<=n=2k<=4k
//                                 (the upper bound just goes to the next
//                                 available power)
//            which becomes ai<=n<=2k-1
//              which the prefix_xor clearly in [0,2k-1]
//                  (2k-1 is the same idea as 2^x-1 where all the bits are 1s)
//   SINCE prefix_xor can only have at most 2 of the same value and a range of
//   [0,2k-1] of the underlying value with 0 taken from p0=0 (ok but 0 is a
//   sentinel value??? => but also implies the XOR for any intervals starting at
//   a1)
//      we get 2k-1 possible value itself for the prefix_xor itself
//      (to enforce uniqueness => maximum possible beauty of 2k-1, remember the
//      sentinel 0 is excluded)
//          and obviously we would want every prefix_xor's value to appear one
//          more time (double it basically)
//
//              for a total length for the prefix_xor (which translates to total
//              actual length of the underlying array) of 4k-1 (NOT 2(2k-1)=4k-2
//              b/c 0 is sentinel)
//
//              ok? how does one CONSTRUCT it?
// MAJOR INSIGHT:
//
//              WE CAN CONSTRUCT a FROM prefix_xor!!!!
//
//   by the rules of XOR a[i]=prefix_xor[i-1]^prefix_xor[i]
//      because of the nature of XOR, 2nd order XOR basically returns to
//      identity
//
//          a[0],a[1]
//        0,p[0],p[1]  <- since bit change == parity change
//          a[0],a[1]  <- parity change == bit change
//              key idea is that on a per-bit basis, a partiy change (XOR-space)
//              is an equivalent to bit change (identity-space) and vice versa
//
//
// IMPL:
//
// a[]
// p=0
// for i in 1..=2k-1: // knowing the max |a| actually helps A LOT
//      << p^i
//      << p^i^i <==> p
//      p = p^i^i <==> p
//
//      hold up
//
//  1    0 0 1
//  1    0 0 1
//  2    0 1 0
//  2    0 1 0
//  3    0 1 1
//  3    0 1 1
//  4    1 0 0
//  4    1 0 0
//  5    1 0 1
//  5    1 0 1
//    clearly, every other elements are XOR=0 to the next element of it
//    but magically XOR!=0 for every other pairs of intervals <==> a!=b means
//    a^b != 0 duh!
//
//
// notice, 0 does not appear because it will just create an extra XOR=0 of
// itself but thats only at most 1 and should not decrease beauty????
// shouldnt 0 be included??
//
// it's actually suppose to be included
// in fact, the reasoning is suppose to be it is NOT 4k because 0 is sentinel so
// we take one off not from 4k-2
//
//  => this is reasonable since it starts with 0 implicitly
//
//
//
// ok but what if the ai is > n....
//
//
// because some elements in this construction goes >n
// the solution actually specifically did it this way:
//
// for prefix_xor:
// [0 to x-1 to 0] + [x to 2x-1 to x]
//
// that ways the largest bit gets cancelled
// out while the transition from end of first and start of the second part is x
//
// recall, k<=n<2k

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n);
  vll a;

  ll k = 0;
  while (n > 0) {
    n >>= 1;
    k++;
  }
  DBGLN(k);

  k = pow(2, k - 1);

  // prefix_xor returns
  vll prefix_xor;
  II(i, k) { prefix_xor.PB(i); }
  DD(i, k) { prefix_xor.PB(i); }
  II(i, k) { prefix_xor.PB(k + i); }
  DD(i, k) { prefix_xor.PB(k + i); }
  // 4k

  II(i, prefix_xor.size() - 1) { a.PB(prefix_xor[i] ^ prefix_xor[i + 1]); }
  // 4k-1

  // a.PB(0);
  // for (ll i = 1; i < 2 * k; i++) { // not <= 4*k-1
  //   a.PB(i);
  //   a.PB(i);
  // }

  // if (k <= 2) {
  //   II(_i, 3) {
  //     II(i, k) { a.PB(1 << (i)); }
  //   }
  //   II(i, k - 1) { a.PB(1 << (i)); }
  //
  // } else {
  //   for (ll cycle = 0; cycle < k - 1; cycle++) {
  //     II(_i, 3) {
  //       II(i, k) { a.PB(1 << ((i + cycle) % k)); }
  //     }
  //     II(i, k - 1) { a.PB(1 << ((i + cycle) % k)); }
  //   }
  // }

  O(a.size());
  OIT(a);

  ;
}
