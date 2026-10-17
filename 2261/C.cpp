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
//
// remove SINGLE element
//          OR
// remove EVEN-SUMMED elementS
//                           ^
//
// player with empty array => loses
// MOG goes first
// LARP goes second
//
//
// if there is n-1 even-summed elements:
//  MOG loses
// if there is n even-summed elements:
//  MOG wins
//
// if an n-lengthed array has a sum of odd
//      we can always remove THE odd element to get even
//
//
// 1. IF n even-summed elements:
//      MOG takes all => LARP loses
// 2. IF n-1 even-summed elements (or n odd-summed elements):
//      if any player MAKES the remaining elements even-summed
//          their next turn will be instantly a lose position
//      b/c of that
//          both players take one by one move
//          even if it is just odd all the way down
//          in that logic,
//              if n%2==0:
//                  LARP wins
//              if n%2==1:
//                  MOG wins
//
//              in order to switch this fate
//                  we have to remove ODD-AMOUNT-of-ELEMENTS
//                  (even amoutn does not change anything)
//
//      but what about a part of it an even?
//          what if we take an ODD AMOUNT of pure evens?
//          MOG can do that to change his fate
//          MOG can also optimally take the LARGEST ODD AMOUNT of EVEN-SUM
//              s.t. LARP does not have a way to take an ODD AMOUNT of EVEN-SUM
//              to change the fate
// in other words
//
// 1. IF n even-summed elements:
//      MOG wins
//
// 2. IF n%2==0:
//      MOG takes the largest EVEN # of EVEN-SUMMED elements
//          (#>=2)
//          s.t. MOG can only take 1
//
//      since n is odd-summed, then n-1 must be even summed
//          (since we can just take that one 2k+1 odd amount out and we do not
//          care if there's EVEN amount of odd)
//      so MOG takes n-1
//
//      n 1
//      0x  <-- MOG wins
//
//      wait LARP always wins??
//
//      M L
//      6 5
//      4 3
//      2 1
//      0x
//
//      6 4 <-- we got to take EVEN EVEN
//      3 2
//      1 0x
//
//      2 1
//      0x
//
//      4 3
//      2 1
//      0x
//
//      sure n%2==0, but n>=4 ()
//          but MOG must find an even # (#>=2)
//
//
//      MOG wins
// 3. IF n%2==1:
//      LARP can then take the largest EVEN # (uh-oh)
//
//      (mog must find an odd #)
//      so MOG MUST take the largest ODD # of EVEN-SUMMED
//          however, since n is assumed to be odd-summed
//              n-1 is even
//              n-2 is odd
//              LARP always have 2 left
//              if the remaining 2 is even summed (LARP takes all, LARP wins)
//              if the remianing 2 is not even
//                  LARP takes, MOG takes, LARP takes, MOG loses => LARP wins
//      if MOG doesnt take it
//          LARP will always find the largest EVEN # of EVEN-SUMMED
//              (since n is assumed to be odd-sumed, n-1 is even and can be
//              found for even-sum)
//
//              MOG will always be left a single element for LARP to only take
//              the remininag and win
//
//
// MOG
// LARP
// MOG
// LARP
//
//
// ~~~~~~~~~~~~~~~~~~~~~~
//
//
// IF n==1 || all n elements are even summed:
//  MOG wins
// IF n%2==0:
//      LARP wins by fate
//      but MOG can change fate by removing even #
//          find the largest even # of even_sum
//          however, this is taken by prior if
//          and if the largest even # is say n-2
//              MOG wins
//          but even+even=odd (we assumed all n elements are odd)
//              so MOG takes the largest even # (at most n-2)
//              but LARP can always take the remaining 2 with EVEN-SUM
//              LARP wins always
//
// IF n%2==1:
//      MOG wins by fate
//      but LARP can change fate by removing even #
//          however, we assumed all n elements are odd summed
//          whatever LARP finds to be even, MOG can find the remaining to be
//          even (even+even=odd)
//          so LARP must take 1, and MOG can take the other one
//
//          and continue
//
//          if any takes EVEN-SUMMED, the other can find all REMAINING elements
//          to be EVEN-SUMMED (and just accelerates the fate of the player whose
//          chooses even)
//
//
//      however, LARP can always take all the ODD elements out
//          because (even+even=odd) (even #-of even + odd #-of even =even)
//                                     ^
//                                  so then LARP does this
//                                  but that just accelerates? because the other
//                                  play can just still take even # of even
//
// even+even=odd???
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  1000000 999999 5 4 3 2
//  E       O      O E O E
//
//  E E E O O O
//
//  MOG takes E E O O
//  LARP takes O/E
//  MOG takes E/O (last el)
//  MOG wins
//
//
//  ohhhhhhhh yes odd+odd=even ???
//        but E E O O E O
//                    ---
//                    odd
//
//  but we can enforce even+odd
//
//  noo we assumed n_sum to be odd
//
//  even+odd=odd
//
// just think of it like this
//
//
// # of E/# of 0
//
// E#/E# => Moggity
// >=2/O# => Moggity (Moggity takes one less E# and E# of O leaves with E+O to
//                  force Larpity
//                  to take 1 and Moggity to take the remaining one)
//      pretty tight conditions
// 1/O# => Moggity (Moggity takes E#O so Larpity is left with 1/1 again)
// 1/1 => Larpity
// 2/1 => 1/1 => Moggity
// 1/2 => Moggity
// 2/2 => Moggity
// 3/2 => Moggity
// 2/3 => 1/1
// 1/3 => 1/1
// 3/1 => 1/1
//
//
// >1/>=1 => 1/1 => Moggity
// >1/ =0 => Moggity
// =0/E# => Moggity
// =0/1 => Moggity
// =0/3 => =0/2 or =0/1 => Larpity **************************8
// =0/5 => =0/4 or =0/1 or [=0/3] => Moggity
// =0/7 => =0/3 => Moggity
// =1/E# => Moggity
// =1/1 => Larpity
// =1/3 => 1/1 => Moggity
// =1/5 => 1/1 => Moggity
// =1/7 => 1/1 => Moggity
//
// so only 0/3 or 1/1 in the beginning => Larpity
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//
// ~~~ =0/O#>=3 => Larpity
//
//
//
//
// 0/O#>=3 => Larpity (Moggity takes whatever number, there's always an
//                  even_sum
//                  for Larpity to take all)
// 0/1  => Larpity
// 1/E# => Moggity (leave with 1/0 again)
// 0/E# => Moggity (per case 1)

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n);
  IVLL(a, n);

  ll n_sum = 0;
  ll Es = 0;
  ll Os = 0;
  II(i, n) {
    // n_sum += a[i];
    if (a[i] % 2 == 0) {
      Es++;
    } else {
      Os++;
    }
  }

  if ((Es == 1 && Os == 1) || (Es == 0 && Os == 3)) {
    O("LARPITY");
  } else {
    O("MOGGITY");
  }

  // if ((n % 2 == 0 && n >= 4) || n_sum % 2 == 0 || n == 1) {
  //   // if n==1: mog takes
  //   // if n%2==0 & n>=4: mog always finds an EVEN amnt of even sum
  //   //          even if n_sum%2==1
  //   //          removing both odd elements =>
  // if (n % 2 == 1 && n_sum % 2 == 0) {
  // if (!((Es == 0 && (Os % 2 == 1 && Os >= 3)) || (Es == 1 && Os == 1))) {
  //   O("MOGGITY");
  // } else {
  //   O("LARPITY");
  // };
}
