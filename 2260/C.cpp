#include <bits/stdc++.h>
#include <climits>
#include <cmath>

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

// start: 1006
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
// given initial x,y -> find the (max x^y, min ops)
//                                  1.       2.
//
// P.1: operation goes one way (x-=1, y+=1) only until x==0
//~~~ P.2: x+y=s, we only need to check for (s,s-m) for m>=floor(s/2) +1 if odd
//~~~              (but impl-wise may not be the case)
//~~~          (since, at a certain point, it becomes symmetric)
// P.2: can only check for cases where (0<=s<=x,y<=t<=y+x)
//      P.2/1: if x>y, first x-y cases are symmetric. HENCE,
//              only need to check for
//                  (0<=s<=min(x,(x+y)/2),y<=t<=y+x)
//                                    ^ floor-div
// P.3: (h,~h) is the best case (max value)
//          conceptually, maximize the differing bits
// P.4: (h,h) is the worst case (all same bits making XOR = 0)
//
// y-x becomes
// y+(~x+1)
// -10 = 11101 -> 11110
// 10000 - 10 = 10000+
// 10000 + 10 = 10010
//      nonononoo
//
// 10000 - 10 = 01110
// 10000 + 10 = 10010
//
// 10000 - 11 = 01101
// 10000 + 11 = 10011
//
// nope (bc its invalid)
// 10101 - 10 = 10011
// 10101 + 11 = 11000
//
// 10101 - 10 = 10011
// 10101 + 10 = 10111
//
// given x,y
//  good
// v v
// 10001010
// 00101010
//  ^ ^^^^^
//    bad
//
// can we directly make the bad into good?
//
// consider
// 1
// 1
//
// 1 - 1 = 00
// 1 + 1 = 10
//
// 01
// 01
// becomes
// 00
// 10
//
// 100 - 1 = 011
// 100 + 1 = 101
//
// 011 - 1 = 010
// 011 + 1 = 100
//
// 001 - 1 = 000
// 001 + 1 = 010
//
// 010 - 1 = 001
// 010 + 1 = 011
//
//
//
// can't we just do
//
// x = 0000000000
// y = 1111100101??
// ^ = 1111100101 (y)
//
// 0^y=y
//
//
// H.1: is x^y the max? is 0^y=y the max? x^0=x the max if y==0?
//      is h=~h even achievable or even the max?
//      assume h=~h is the case...
//
//          x=1,y=0
//          x=2,y=1
//          x=3,y=4
//          x=4,y=3
//          x=5,y=2 (or 10)
//
//          0
//          1
//
// or by implementation..
//
// from left-most bit to right-most bit
//
// if (1,0) or (0,1) => good, leave it as it is
// if (1,1) => -1 on one of the number
// if (0,0) => +2^{bit place} on one of the number
//
// remember, +1 on one means -1 on the other...
//
// if (1,0) || (0,1) ==> GOOD / LEAVE IT
// if (1,1) ==> (-1,+1) becomes (0,1) (at that bit place)
//                assuming the +1 is not all 1s (or else it becomes (0,0))
// if (0,0) ==> (-1,+1) becomes (0,1)
//                assuming the -1 is not all 0s
//
//
// notice, we can do either (-1,+1) or (+1,-1) either works
//         AND there's a special assumption that
//              the +1 is not all 1s after
//              the -1 is etc.etc.etc.
//
// easier observation??
//
// H.1: the more random the later (lesser-sig) bits are,
//      the better it will be conceptually (?)
//
// 111111 +1=1000000
// 100000 -1=0011111
//        -1=1111110
//        +1=1000001
//
//
// O.1: actually it is opposite of H.1 where we prefer to have all the same 1s
// or 0s.
//      conceptually, mixing 1/0s reduces the effectiveness but can't we just
//      +/- on that base index?
// 1 => only changes when +1 on all 1s (after) or -1 on all 0s (after)
// 1
//
//
// on the b-th place
// 1 => changes when +2^{b-1}
// 1 => changes when -2^{b-1}
//
// to make it easier, let us avoid changing the greater-sig (left) bits
//
//                  bad
// 1 => -2^{b-1} => 0
// 1 => +2^{b-1} => 0
//
//
//
//
//
//
//
// easier observation?
//
//
//!!!!! simplify XOR to AND/OR
//      a[i] XOR b[i] <=> (a[i]==0 AND b[i]==1) OR (a[i]==1 AND b[i]==0)
//
//      ok no this is just as observed as before..
//
//
// ok p1-p3 is literally as observed before...
//
//!!!!! per soln. we can do the following
//!              s=x+y
//          set the first bits of x to the first bit of (s=x+y)
//              which requires adding some number like
//                  if s[0] == 0b1 && s[0] != x[0]:
//                      x += int(s[0+1:]-x[0+1:])
//                      y -= " "
//   // recall: s=x+y <==> s[i]=x[i]^y[i]^c[i] (c for carry from previous bit)
//   // but this doesn't seem optimal?
//   // but remember, y -= s[i+1:]-x[i+1:] == y[i+1:]
//                  else:
//                      no operation needed
//
//
//
//
//
// ~~~~~~~~~~~~~~~~~~~~~~
//
//
// 01010 x
// 01100 y
// ----- +
// 10110 s
// ?
//
//
// ~~~~~~~~~~~~~~~~~~~~~~
//
// x+y = x-k+y+k = s
//
// O: +/- x,y's don't affect the sum (makes sense)
//
// THEREFORE, given s = some bit array
//              we can split s to be {a,b}
//                  where a+b=s (again with the prior observation)
//                  but also because we can *arbitrarily, by choice* to avoid
//                  both 1's in a,b to avoid the complex case of carrying
//
// key problem: how does x-k+y+k = s  allow this *arbitrary choice to let a,b be
// mutually exclusive per-index bits*?
//
//      an extension:
//          x-k1-k2-k3-k4+y+k4+k2+k3+k1 = s
//
//          (commutative?)
//          by the property of invariant ordering of the summands,
//              whatever +k's or -k's we decided to do,
//              as long the *arbitrarily designed* a,b results in a+b=s,
//                  where the various decision of k1...k4 (icnrease y and
//                  decrease x) OBVIOUSLY results in equal sum of the opposing
//                  effect but WE DID NOT CARE what the intermediate form looks
//                  like (in between different sums and worrying about carries
//                  and ordering)
//
//  in this way, h=~h is always possible from prior observation as long as a+b=s
//
//  but how do we minimize operation?
//
//  *arbitrarily* pick a or b to be the closest to x (say b)
//
//  we continue increasing b until >x then increase a (remember, a+b=s)
//
//  at the end, just count a (the y)
//      remember, a+b=s (i.e., complementary operations <=> equal
//      distance/op-count)
//
//
//
// IMPL:
//      compute s=x+y
//              m=log2(s)
//
//      // m=0 binary length of 1 (or 2^0)
//      for(ll i=m; i>=0; i--) {
//          if((1 << m) > x) {
//              b += 1 << m;
//          } else {
//              a += 1 << m;
//          }
//      }
//
//          max x XOR y,    the "k"
//      O((1 << (m+1)) - 1, x-a)
//
//
//
// x=3 y=1
//
// max XOR = 4, min ops = 3
//
// 11
// 01
//
// 000
// 100
// --- XOR=4
// 100
//
//
// but what about our soln?
//
// 11
// 01   s=4 100
//
//          just b/c x+y=s does not mean all bits of s are present
//          in fact, by the mutually exclusive construction of the bits, the
//          max XOR is just s
//

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(x, y);

  ll s = x + y;
  ll m = (ll)log2(s); // truncate/floor
  ll a = 0;
  for (ll i = m; i >= 0; i--) {
    // ensure s has a bit of 1 at m-th place
    // AND, if so, is this additional 1 t m-th place under x so a can
    // incorporate it?
    // if ((((s >> m) & 1) == 1) && (a & (1 << m)) <= x) {
    //   a &= (1 << m);
    // }

    // if ((((s >> i) & 1) == 1) && (a & (1 << i)) <= x) {
    //   a &= (1 << i);
    // }

    if ((((s >> i) & 1) == 1) && (a | (1 << i)) <= x) {
      a |= (1 << i);
    }
  }

  // O((1 << (m + 1)) - 1, x - a);
  O(s, x - a);

  /*
   * IN SUMMARY,
   *
   * C has more layered observation but the implementation is still
   * STRAIGHTFORWARD. complex implementation means something wrong. (missing key
   * obsv.)
   *
   * the commutative property of summands has been seen before. it can appear
   * anywhere such as here where the operation is on adding and where we only
   * care about the END RESULT (b/c sum implicitly includes all the summand)
   * AND ALSO THE END RESULT IS THE INVARIANT (e.g., x+y=s) which means we did
   * not have to inspect the bits in each x,y's BETWEEN operations.
   *
   * in other words, if we can see that the sum also IMPLICITLY handles the
   * unnecessary complex bit carries and those cascading bit flips, we would not
   * have to implement all that.
   *
   * again, C has easy implementation.
   *
   */
}
