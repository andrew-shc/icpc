#include <bits/stdc++.h>
#include <climits>
#include <unordered_set>

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
  // ios_base::sync_with_stdio(false);
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
//
// P.1: x_i != y_i =>
//          Obj A: no self-referential verticies in the graph
//          Obj B: no diagonal coordinates
//
// P.2: suppose x_i < x_j (querying as i,j):
//          Obj A: 0 if there's no path (distinctively Obj A, Md != 0 if
//                  |x_i-x_j| > 0)
//                 edge-length of the shortest path
//
//                 but since a directed graph can at most have the
//                 largest-shortest-path in edge-length to be a single line w/o
//                 loops... n-1 is the longest edge-length it can have
//                 and ONLY a pair of verticies can have n-1 edge-length
//                 and other must have <n-1
//
//          Obj B: requires the Manhattan distance Md to be
//          greater than or equal to |x_j-x_i|
//                      resp=Md=|x_i-x_j|+|y_i-y_j| >= |x_i-x_j|
//
//                  but not all x's will have 1s or ns....
//
// === STUCK: x's DONT ALWAYS HAVE THE MIN 1 OR MAX n ===
//
//
// O.1: Object A is a DIRECTED graph while...
//      Object B is clearly BIDIRECTIONAL (by the commutative/associative
//      properties of Mahattan distance)
//
//      O.1/1: we now need to find whether a distance between two nodes in a
//      directed graph are exclusively/ALWAYS different when switching the
//      input orders i,j (remember, a single query contains two indices)
//
//      OR, rather it is impossible!
//          this can easily occur... unfortunately
//
//          x=[2 1 1]
//          y=[1 2 3]
//
//          1 <-> 2 (equal path distance)
//
//
// !!!! PARAGRAPH 2:
//!             permutation or not
//!             if it's NOT a permutation
//
//!!!~~~~~!!!~~~~~~ UTTER CONFUSION
//
//
// Object A refers to the vertices themselves while Object B refers to the
// INDICES of the x/y-array AND it is assumed (IF OBJECT A) all vertices from 1
// to n (uniquely) that always with n edges
//
// OBVIOUSLY, IF x IS NOT A PREMUTATION, THERE OBVIOUSLY EXISTS A VERTEX WITH NO
// ---outgoing---PATH TO ANY OTHER VERTEX which would clearly yield a 0
// (distinctvely Object A)
//
// or else, manhattan distance will always produce a non-zero output
// (by xi != yi)
//
//
// HOWEVER, IF IT IS A PERMUTATION OF SORT
//
//      note the n DIRECTED edges in an n-vertex graph
//
//      (1 loop exist and only a single directed loop)
//      (actually, 1 loop doesn't have to exist, they can all direct or pointed
//      towards a point of convergence)
//
//
//  worst-case scenario: 1 loop exist but IT IS DIRECTED
//      the only 1 BIDIRECTIONAL loop that exists is a 1-loop (adjacent
//      vertices)
//
//      or in other words if path == 1
//
//  what we can do is
//      if the jury returns path == 1
//      if we flip the arg and the path == 1 again ==> Object A?
//
//      consider the case for Object B
//
//      (5,7) and (6,7)
//          different x but same y with a symmetric Manhattan distance of 1...
//
//!! briefly checked paragraph 3 and it similiar to the aformentioned P.2 of
//! Object B
//
//      since now we assume permutation, given manhattan distance (BUT WITH
//      ARBITRARY INDEX PLACEMENT)
//
//      find the index of x=1 and x=n
//          and by MD we expect a minimum distance of n-1
//          (object B)
//
//      however, with object A,
//          we either have a single large DIRECTED LOOP
//          or, a DIRECTED LOOP somewhere
//
//!!! oh yea of course the bidirectionality
//!     basically, we combine the observation of 1<->n for MD
//!     and also the symmetric (or rather the lack thereof) for a DG
//

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n);
  IVLL(x, n);

  unordered_set<ll> uniq(x.begin(), x.end());

  ll left_out = 0;
  bool is_pmt = true;

  // 0@
  ll ind_1 = 0;
  ll ind_n = 0;

  II(i, n) {
    if (x[i] == 1) {
      ind_1 = i;
    } else if (x[i] == n) {
      ind_n = i;
    }

    if (uniq.count(i + 1) > 0) {
      // we could do == 1 but we need to record the integer that was LEFT OUT
    } else {
      left_out = i + 1;
      is_pmt = false;
    }
  }

  if (is_pmt) {
    // remember, input to Obj B works in index-space

    O("?", ind_1 + 1, ind_n + 1);
    I(resp1);
    if (resp1 == -1) {
      exit(1);
    }

    O("?", ind_n + 1, ind_1 + 1);
    I(resp2);
    if (resp2 == -1) {
      exit(1);
    }

    if (resp1 >= n - 1 && resp2 >= n - 1) {
      O("! B");
    } else {
      // because of the directed-ness of the graph in Obj A, it is unlikely
      // (impossible) for any two alternating nodes to have THAT kind of path
      // length bidirectionally
      //
      // and also remember ind_1 != ind_n (in other words even if the
      // index-space is treated as a vertex-space for Obj A, they're always
      // distinct)
      O("! A");
    }
  } else { // 1-query max
    O("?", left_out, left_out == 1 ? 3 : 1);
    I(resp1);
    if (resp1 == -1) {
      exit(1);
    }

    if (resp1 == 0) {
      // must be Obj A
      O("! A");

    } else {
      // must be Obj B (because strictly <=>)
      O("! B");
    }
  }

  //   unordered_set<ll> uniq(x.begin(), x.end());
  //
  //   if (uniq.size() == n) {
  //     // PERMUTATION
  //   } else {
  //     // NOT A PERMUTATION (1-QUERY MAX)
  //
  // }

  // // 2 queries
  // O("?", 1, 1);
  // I(resp1);
  // if (resp1 == -1) {
  //   exit(1);
  // }
  //
  // O("?", 1, 1);
  // I(resp2);
  // if (resp2 == -1) {
  //   exit(1);
  // }
  //
  // // output
  // O("! A");
  // O("! B");
  //
  ;
}
