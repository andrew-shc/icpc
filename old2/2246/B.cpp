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

// start: 2009
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
// n=1
// n=2
// wait n is up to 50 <<<<
// 1 <= n <= 50
//
// 2^50?? no
//
// n^50?
//
// a1 + a2 + a3 + a4 + ... + an | ai    s.t. for each i
//
//
// a1 + a2 + a3 + a4 + ... + an = a1a2a3a4*...*an
//
// consider n=3
//
// 1 + 4 + 5 = 12,,,,,,,,
//
//
// a1 + x = a1*x
// a1 = a1*x-x = (a1-1)*x => a1/(a1-1) = x
//    ==> x= a1*x-a1 = (x-1)*a1
//    ==> x/(x-1) = a1
//
//    any positive integer x/(x-1)
//
//    2/1 ??? a1=2??
//    3/2
//    5/4
//
//
//
// 2 + x = 2*x
//
// a1 + x = a1*x
// a1 + a2 + x = a1*a2*x
//
// a1 -a1*a2*x = -a2 - x
// a1*(1-a2*x) = -a2-x
// a1 = (a2+x)/(a2*x-1)
//
// 1<=n<=50 how does one brute force this...
//
// 5*1 + 5*2 + 5*3 + 5*4 = 5*10
//
// i mean 5*1..4 divides 5*10
//
// what about
//
// 1+2+3+4=10? nope..
// 2*1+2*2+2*3+2*4=2*10
//
// interestingly no since 2*4=8=2*2*2 does not divide 20=2*2*5
//
//
// sooo
//
// 5*1 + 5*2 + 5*3 + 5*4 + 5*5 + 5*6 + 5*7 + 5*8 + 5*9 + 5*10 = 5*55
//                                                       5*2*5  5*5*11 nope
//
// 2*2 + 2*4 + 2*6 + 2*8 + 2*10 + 2*12 = 2*42
//                                2*2*3*2
//                                       2*3*7  nope
//
//
//                             lcm??? gcd???
//
//
//
//
//
//    say PF of 2*2*2*3*3*7*9*9*9
//              i
//
//
//
// a1+a2+a3+a4+a5 = a1 * a2 * a3 * a4 * a5??????
//
// 1 + 2 + 3 + 4 + 5 = 1*2*3*4*5 = 120 nonono
//
// n(n+1)/2 = n/2*(n+1)!/n! = (n+1)n * n!
//
//
//
//
//
//
//
//
//
// a1+a2+a3+a4+x = a1*a2*a3*a4*x
//
// suppose we let it be
// n*(n-1)/2 + x = x(n-1)!
// n*(n-1)/2 = x(n-1)!-x = x*((n-1)!-1)
//
// n*(n-1)/2 * 1/((n-1)!-1) = x
//
// n*(n-1)/[2(n-1)!-2] = x   for positive integer x
//
// n=3 => 6/[2]=3=x
//
//
// n(n+1)/2
//
// 2 + 4 + 8 + 16 + 32 = 2^1+2^2+2^3+2^4+2^5 =
//
//
//
// 4 + 2 +
//
//
//
// 2*4*8*16*32
//
//
// is n=2 impossible?? the only impossible one??
//
// x+y=xy
//
// this is the infamouse 2+2=2*2 but has to be duplicates....
//
// but thats when + == x but we're trying to find divisbility
//
//
// suppose x+y=m
// we want x|m and y|m
//  where x|m => m=kx
//        y|m => m=ly
//
// and x+y=m where m => m=kx,m=ly which means k=y & x=l => m=xy
//
// 2 looks to be impossible
//
// x+y+z=xyz?
//
//
// 1 + 9 + 2 + 6 = 18
// 1   3*3 2   2*3  2*3*3
//
//
// taken the hint from the editorial
//
// 1 + 2 + 3 + 4 +... = n(n+1)/2
// n + 2n + 3n + 4n +... = n*n(n+1)/2
// nah fuck what is this no way this actually helped....
//
// key idea: kn divides n*n*(n+1)/2 for k<=n
//                    (n-k+k)*n*(n+1)/2 = (n-k)*n*(n+1)/2 + k*n*(n+1)/2
//
//  from another perspective: n*n(n+1)/2 divided by kn always yields an integer
//       n(n+1)/(2k) => always an integer since n(n+1) is always an even where
//       n(n+1)=2m results in m/k but is m/k always an integer??? no...?
//
//
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//
//
// hint: iteravely each element
//
// n=1: any (unconstrained)
// n=2: 2+2=2*2... duplicates => -1 (per soln.)
// n=3: 1+2+3=1*2*3 => 1,2,3|6
// n=4: 1+2+3+4=1*2*3*4=24 => 1,2,3,4|24
// n=5: 1+2+3+4+5=1*2*3*4*5=120 => 1,2,3,4,5|120
//
// n(n+1)/2 = n! ?????
//
// we technically don't need "="....
//
// it's literally the idea before... the question never asked sum be the product
// just divisbility and i guess a proof is needed since by-inspection clearly
// Gaussian sum works clearly
//
// 1 + 2 + 3 + 4 + 5 = 1 * 2 * 3 * 4 * 5
// the question never asked for sum=product, it asked whether individual
// elements divides the sum
//
// 1,2,3,4,...,n|n(n+1)/2
//
// 1+2=3
// 2 does not divide 3.... wtf
//
// 1+2+3+4+5+6+7+8+9+10 => 55
// 7 does not divide 55
//
//
// ok instead do thsi
//
// 1+2+6 nope
//
// a1 = [1]
// a3 = [1 2 3]
// an = [1 2 3 ... sum a{n-1}]
//
// i guess be truely open minded to some exotice edge cases like thsi?
//
// suppose a!=b
// lcm(a,b) >= 2*max(a,b) (since 2 is the smallest PF)
// 2*max(a,b) > a+b (remember, a!=b)
//
// however, we supposed a solution a,b exist. (for n=2)
// a,b|a+b => lcm(a,b)|a+b (makes sense since lcm is some common multiple of
//                          BOTH a,b esp. when a,b individually divides a*b,
//                          supposedly)
// we expect a solution, we get lcm(a,b)|a+b
// we also expect unique solution a!=b, we get lcm(a,b)>a+b => clearly lcm(a,b)
// does not divide a,b
//
// ~~~~overall, why n=2 conceptually does not work can be thought of as the
// requirement of distinctive integer~~~~
//
// lcm(1,2,3)=6>1+2+3=6 contradiction?
//
// what kind of proof is this?
//
// accuracy high but recall bad
//
// but it mentions a!=b, how would three-way inequality work??
//
// logic/proof through lcm/gcd seems common (might want to keep that in mind)

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n);

  if (n == 1) {
    O(1);
  } else if (n == 2) {
    O(-1);
  } else {
    vll a = {1, 2, 3};
    ll running_sum = 6;

    II(i, n - 3) {
      a.PB(running_sum);
      running_sum += running_sum;
    }

    OIT(a);
  }

  ;
}
