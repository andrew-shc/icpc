#include <bits/stdc++.h>
#include <climits>
#include <unordered_map>

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
//  for a number n to have a digit 7
//      18+9=27
//
//  it has to have an eight at that digit
//  and to have an eight at that digit it has to have a nine and so on (almost
//  like decrement in mod space 8 like -1 (mod 8) )
//      or maybe mod-10
//
//
//  18+9=27
//  19+9=28+9=37
//
//  61+9 = 70 <-- another case, carry bits
//
//  60+9 -> 69+9 -> 78+9
//  60+99 -> 159+99 -> 178
//
//  so two cases:
//      - have a carry bit increase the later digit
//      - add 9 to the current digit repeatedly until it flips back to 7
//
//
//  8+9=17
//  6+9->15+9->24+9->33+9->42+9->51+9->60+9->69+9->78+9->87
//                                                 *      *
//
//  possibly the max ops is 9 (since 6 comes right before 7 and 9, in base 10,
//                             sort of goes backwards one by one)
//                             this makes sense since 7 is inclusive of the
//                             mod-cycle, because it would take 10 times to
//                             REPEAT the 7 but 7 is what we want IF we did not
//                             have it already so at most 9 times from the
//                             worst-possible scenario
//
//                             but noticed, the earlier digits could have
//                             reached 7 earlier also since it's like 06+9
//
//                             what about 66? that carry bit makes the next
//                             digit goes forward
//
//                             so we should try 86 (8 is right after 7, and 6 is
//                             right before 7)
//
//  66+9->75+9->
//        *
//
//
//  86+9->95+9->104+9->113+9->122+9->131+9->140+9->149+9->158+9->167+9->176
//
//  9 times
//  but carry bits could simplify or quicken the process or minimize the ops
//  but in this case carry digit (the one digit left) actually get's delayed
//  with a double 4
//
//  and actually the more general case CAN be thought of just carry bits
//
//  9+9+9=27
// 1
//  99+99+99 = 198+99 = 297
//
//   9 -> 8 -> 7
//
//
//  8->9->0->1->2->3->4->4->5->6->7
//                             *
//  6->5->4->3->2->1->0->9->8->7->6
//                      ^
//                     carry bit delays
//
//
//
// process of -1 (mod 10)
//                   process of carry-bit flipping
//                  *
//   2->1->0->9->8->7<-6<-5<-4<-3<-2
//                               ~~~
//                               because carry-bit gets delayed depending where
//                               the 0 is on the right-digit of it, 2 should
//                               always be used via the process of -1(mod 10)
//                               for minimal ops
//
//          but remember this is not 9,90,900
//          we're doing 9,99,999
//
//
// because of the bit carry, the max ops needed are 5 (2 can work either way)
//
//
// but what about with 3 digits?
//      carry bit delays so what if we're like
//
//      88888888888888881 ?
//      90000000000000000
//      90000000000000009
//
//      but by the process of -1(mod10), we should decrease the 8
//
//      88888888888888881+99
//      88888888888888980
//
//
//      77777777777777777+9
//      77777777777777786
//
//      88888888888888888+9
//      88888888888888897
//
//      99999999999999999+9
//     100000000000000008
//     100000000000000017
//
//     because 1,0's are further then the 8, we can ignore special cases where
//     the bit flips cascades down to the end
//
//     for cases like
//
//     6666666666666666661+9 (k=9)
//     6666666666666666670
//
//     6666666666666666661+99 (k=99)
//     6666666666666666760      (because of the 90, it just propogates the carry
//                              bit to the end of k)
//
//     1 is further away than 6 (hence, 1 ops)
//
//     2222222222222222222+9
//     2222222222222222231+9  (notice how 3,1 are equally far from 7)
//     2222222222222222240
//
// in this case doing the same amount of 9s would be quicker
//      like say 2222
//
//      we do 2222+9999
//         ->12221
//
//
//
//  so actually with just 9,99,999
//      the middle digits stays the same
//
//
//      because we can do same amount of digits of 9, worst we can always do the
//      process of -1 mod 10 (not limited to set amount of digits from n)
//
//
// in other words 0 is always present
//
//                *
// 2->1->0->9->8->7<-6<-5<-4<-3
//
//
// 15 + 9 = 26 + 9 = 35
//
// 015 + 99 = 114 + 99 = 213 + 99
//
// 15 + 999 = 1014
//
//
// 15 + 9 = 24 + 9 = 33 + 9 = 42 + 9 = 51 + 9 = 60 + 9 = 69 + 9 = 78
//
//
// 12345689
//

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n);

  ll min_ops = 3; // 0 is always available to use and just requires 3 operations
                  // 0->9->8->7

  unordered_map<ll, ll> ops = {{9, 2}, {8, 1}, {7, 0}, {6, 1}, {5, 2},
                               {4, 3}, {2, 4}, {1, 4}, {0, 3}};

  // 51+9+9=60+9=69

  ll zeroes = 0;

  while (n != 0) {

    // min_ops = min(min_ops, ops[n % 10]);
    n /= 10;
    // switch (n % 10) {
    // case 9:
    //   min_ops = min(min_ops,
    // }
    // if (n % 10 == 9) {
    // }
  }

  O(min_ops);
  ;
}
