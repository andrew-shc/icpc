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

// start: 1739
//   end: 2129xx

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
// 1 => (1,1,1) => gcd(lcm(1,1)=1,lcm(1,1))=1=gcd(1,1)
// 2 => (1,1,1) => yes
//      (2,1,1) => gcd(lcm(2,1)=2,lcm(1,1)=1)=1=gcd(2,1)
//      (1,2,1)
//      (1,1,2)
//      (2,2,1)
//      (2,1,2)
//      (1,2,2)
//      (2,2,2,)
//
//
// lcm maximizes the powers of PFs (from the integer with the largest PF for
// each PF)
//
// gcd takes all common shared PFs
//
// so gcd(lcm(a,b),lcm(b,c))=gcd(a,c) is like
// for each PFi
//      LHS_PFi = min(max(a_PFi,b_PFi),max(b_PFi,c_PFi))
//      RHS_PFi = min(a_PFI,c_PFI)
//
//      ==>
//              if a_PFI?c_PFI<=b_PFi is uniquely the max ==> LHS != RHS
//              if a_PFI<b_PFI<c_PFI or
//                 c_PFI<b_PFI<a_PFI                     ==> LHS != RHS
//              if b_PFI<=a_PFI?c_PFI                     ==> LHS == RHS
//
//      ==> for each i-th PF, ensure the b's i-th PF is less than or equal a's
//              AND b's
//
//              like pf_power[b][pf] <= pf_power[a][pf]
//                   &&
//                   pf_power[b][pf] <= pf_power[c][pf]
//
//                          H.1:
//                              pf_power[b][pf] <= pf_power[a][pf] && ''
//                                  ==>?  b <= a && b <= c
//                                  yes?
//                          H.2:  say b=4, we can have 27 (3^3), 81 (3^4) since
//                          it only
//                                has 3
//                                      b <= a && b <= c
//
//                               NOOOO we need every PFs of a and c to be AT or
//                               GREATER than b
//                                  so say b=4, the following a,c works
//                                      a=4*2
//                                      c=4
//                                      a=4*81
//                                      c=4*27
//                                      BUT NOT
//                                      a=5
//                                      c=5
//                     ==> a&c needs to be MULTIPLES of b's PFs
//                          (as in >= to any b's PF UNTIL n is reached)
//
//
//
//
//       ==> since (a,b,c) is really just (1..n,1..n,1..n)
//
//
//   for max_b in 1..n:
//      find all prime factors & look back till 1
//
//      consider 60 = 2 2 3 5
//          we can do (60,60,60)
//          or        2   3 5   (+3) and 4 PFs each can be removed once
//                    (60,30,60)
//                    4*(2*1+1)
//                     x2    x2
//
//                    2     5   (+1)
//                    (  ,10,  )
//                    x*(2*2+1)
//
//          (a,b,c)
//             ^
//             find all the combination/configurations of decreasing powers of
//             PFs
//                  decrement different powers => different combination
//                  decrement same powers => no difference
//                      ==> better work in unordered_maps of PFs and powers
//                              (unique number of PFs)!x
//
//                           4! 3! 3! 2! 1!
//
//                           2
//                           5 . 5 . 5 . 5 . 5
//                           7 . 7 . 7 . 7
//                           9 . 9 . 9
//
//                           ok consider
//
//                           3 3 3
//                           7 7 7
//                           9 9 9
//
//                             3 3
//                           7 7 7
//                           9 9 9
//
//                           3 3 3
//                             7 7
//                           9 9 9
//
//                           3 3 3
//                           7 7 7
//                             9 9
//
//                               3
//                           7 7 7
//                           9 9 9
//
//                           3 3 3
//                               7
//                           9 9 9
//
//                           or even
//
//                           3 3 3
//                             7 7
//                               9
//
//                           it can be thought of as every unique prime factors,
//                           you can
//                              1. decide which PFs to choose (say 4, there are
//                              4x3x2x1+1 ways to select them including not
//                              selecting any of them) but this includes
//                              duplicate choices... we do not care about
//                              order.. this can actually be thought of as
//                                  2^4 (where each PFs can be chosen or not and
//                                  elegantly includes not choosing any state)
//
//                                  wait, this is just product of pf_counts[pf]
//
//
//                              2            = 2
//                              5 5 5 5 5 5  = 7
//                              7 7 7 7      = 5
//                              9 9          = 3
//
//                              2*7*5*3 = total amount of different combination
//                              you can do (includes not choosing any or
//                              choosing all)
//
//                              and these are configuration for b starting from
//                              b_max (or max_b)
//
//                              1st configuration say b=max_b means 2*0+1=1
//                              configuration of valid a,c
//                              2nd config say b=(one of the PFs decremented)
//                                  configuration of valid a,c jumpes to the
//                                  optional existence of the removed PF from
//                                  the max_b
//                                  2*1+1=3
//                                  ^ this depends on the AMOUNT it was removed
//                                  (nononono)
//
//                                  no this is like reverse
//
//                                  like
//                                  (2_removed+1) x
//                                  (7_removed+1) x
//                                  (5_removed+1) x
//                                  (3_removed+1) = z
//                                          GIVEN b, what are some valid
//                                          a,c to make valid (a,b,c) into
//                                          2*(z-1)+1
//
//
//        ANOTHER KEY INSIGHT => b <= max_b could or ACTUALLY DEFINITELY
//        includes previous smaller max_b => but the point is what PFs are
//        missing from the max_n => so how does one avoid the later, larger
//        max_b that includes certain b that was previously iterated over?
//              or simpler observation?
//
//
//                           1###
//                           2###
//                           3###
//                           4###
//
//                           .... #...
//                           .... ....
//                           ....
//                           ....
//
//
//
//           a,c increases in combinations => 2*(different configurations from b
//           to max_b)
//
//
//
//    ==> just because b only has these prime factors does not mean we're
//    restricted to it (completely throw the idea away)
//          but there's also some b that is a prime island (if you include it,
//          you have to remove all other PFs especially when n is small compared
//          to the prime island)
//
//
//    for b in 1..n:
//          b
//
// editorial:
//      over-observed? over-complicated
//
//      key re-phrasing: any a,c that are divisible by b (because then a,c will
//      include all the necessary PFs from b)
//
//      trivially: there are n/b configurations/combinations to choose from for
//      one of the a and c and since the triplets just needs an
//      ORDERED,REPLACE-ABLE countings of itself (e.g., independence) => we just
//      need (n/b)*(n/b) ways to do it
//          this also resolves the max_b including previous b because we don't
//          need to find all the ways or the maximal ways the PFs can extend
//          since we just divide the max (the n) by b (floor division)
//
//      OVER COMPLICATED (or failed to realize that extending PFs from b is jsut
//      multiples of b)
//

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n);
  ll the_ways = 0;
  for (ll b = 1; b <= n; b++) {
    the_ways += (n / b) * (n / b);
    // no need for a +1 since each b is a new,
    // unique b which we're counting from
  }
  O(the_ways);
  // DBLOCK {
  //   ;
  //   II(i, n) {
  //     vll pf(1, 1);
  //     ll d = i;
  //     for (ll j = 2; j * j <= d; j++) {
  //       if (d % j == 0) {
  //         d /= j;
  //         pf.PB(j);
  //       }
  //     }
  //     if (d > 1) {
  //       pf.PB(d);
  //     }
  //     DBGLN(i);
  //     DBG_ITER(pf);
  //   }
  // };
}
