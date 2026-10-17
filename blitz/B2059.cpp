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

// start: 1927 (B2059-B2069)
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
// isn't this just asking the smallest i s.t. b_i != i
//
// GENERAL QUESTION: OPTIMAL PARTITIONING
//      - concat. sub-arrays with even indices (1@i=2,4,6...) => b[]
//      - find the min @i s.t. b_i != i
//
// O.1: at least k-1 1-lengthed subarrays at the end
// O.2: n==k, basically every other elements of a (i=2,4,6,...)
// O.3: if k==2 (best case), we can arbitrarily choose the 1st partition s.t.
//      the 1st element of the 2nd partition results in b_i != i for a minimal
//      cost of 1 (assuming not all elements of b_i is 1 or only the 1st element
//      is 1 and all other are 2)
// O.4: 1st element is always excluded
//
//
// min @i s.t. b_i != i ==> for all 1<=j<i, b_j == j (almost like MEX)
//
// we want to minimize the b_j = j
//
// on the contrary, in what case b_j = j MUST exist? (cannot be avoided)
//  on WHAT CONDITIO0N would it always result in b_j=j for some i<=j<i
//
// for example, b_1=1
//      ==> all 2nd partioning's 1st element must have 1
//      ==> k=n, 2nd element must be 1
//          k=n-1, 2nd/3rd element must be 1
//          k=n-2, 2nd/3rd/4th element must be 1
//          k=n-l, element i=2,3,4,...,l+2 must be 1
//
// what about b_2=2
//      ==> all 2nd partioning's 1st element must have 1
//              all 2nd partition's 2nd element OR 4th partition's 1st element
//              must have 2
//
//      invariance: a-th partition, b-th element, for j-th b_j=j,
//          must be a/2+b-1=j
//
//
//      ==> k=n, 4th element must be 2 (4/1)
//          k=n-1, 3rd element must be 2 (2nd partition's 2nd element) (2/1)
//            XOR, 4th element must be 2 (4th partition's 1st element) (4/1)
//          k=n-2, 3rd element must be 2 (2/2)
//            XOR, 4th element must be 2 (4/1)
//            XOR, 5th element must be 2 (4/1) +1 shift from (2/2)
//          k=n-3,
//
//  again for b_1=1
//      x x x x x x x x x x
//  k=n
//      x * x x x x x x x x
//  k=n-1
//      x * * x x x x x x x
//      x [ ]
//      [ ] x
//  k=n-2
//      x * * * x x x x x x
//      x [   ]
//      [ ] [ ]
//      [   ] x
//  k=n-3
//      x * * * * x x x x x
//      x [     ]
//      [ ] [   ]
//      [   ] [ ]
//      [     ] x
//
//  again for b_2=2
//      x x x x x x x x x x
//  k=n
//          v
//      x * x x x x x x x x
//  k=n-1
//          v v v
//      x * * x x x x x x x
//      x [ ]
//      [ ] x
//      x x x x
//      x x [ ] x
//      x x x x [ ]  << impossible (need's 4 x's before reaching 5-th, an odd
//      index)
//  k=n-2
//          v v v v
//      x * * * x x x x x x
//      x [   ]
//      [ ] [ ]
//      [   ] x
//  k=n-3
//      x * * * * x x x x x
//      x [     ]
//      [ ] [   ]
//      [   ] [ ]
//      [     ] x

//
//
//
//      ~~~~~
//      ==> if k=n, basically 2nd element must have 1
//                  (2nd partioning 1st element must have 1)
//          if k=n-1, the 2nd partioning's 1st element must have 1
//
//
//
//
//
//
//~~~~~~~~~~~~~~~~~~~~~~~~
//
// for example in TC#2:
//      n==k and duplicate elements makes that certain element unavoidable
//          (i.e., the partitioning restricts to must always use the given
//          ordering of the ordered SET of a)
//      suppose k=n-1
//          we allow a partioning of 2-len'd subarray somewhere
//              ==> again, duplicate elements
//                  in fact, TC#2 is overly tight, with always 2-duplicate
//                  element k=n-(2-1) disables this possibilities
//
//                  k>=n-(2-1)
//
//      in general, suppose d s.t. all duplicates in a are >=d-duplicates
//          if k>=n-(d-1)=n-d+1
//
//          we must follow the ordering given by a[]
//
//          can't we overlap??
//
//
// ^^^ ~~~~~~~~~~~~~~~~~~~~~~~~~~~`
//
//
// stuck
// `

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n, k); // k<=n, k is even, k is # of subarrays
  IVLL(a, n);

  ll min_cost = 0;

  O(min_cost);
  ;
}
