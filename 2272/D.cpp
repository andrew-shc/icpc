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
// O.1: every maximum independent vertex set has vertices in graph that is
//      excluded from it (which can be connected with a vertices that is in the
//      max. independent vertex set of another graph to extend into the max
//      independent set of the forest)
//
//
// but how does one compute the max independent set?
//
// ~~~ O.2: every vertices is part of a max independent set or not (binary)
//
//      counter-example: triangles
//          needs 3 independent vertex sets
//
// graph reduction?
//
//
//!!! per chatgpt
// 1. we can only add edges (not remove them)
//      => cannot increase max. independent set but may decrease it?
//
//
//
//!!!! editorial paragraph 2:
//!!     when choosing the vertex to connect between trees, within each tree (=>
//!     leaf nodes of 1-adjacent node always exist) every leaf nodes will be
//!     included in SOME (there always exists some) MaximumIVS
//
// 2 conceptual observation can be made to support this:
//      1. a leaf node guarantees to only block 1 vertex from being included in
//      an independent vert. set
//      2. greedy exchange argument:
//          suppose we did not select the leaf node (v), then we must select the
//          leaf node's neighbor (u)
//
//          if we swap u<->v to be included in the independent set, we would
//          MAINTAIN (lower bound) the number of vertices since v is always by
//          itself and we know u has been kicked out
//
//          but also, we leave the opportunity for any nodes adjacent to u to
//          become included in the independent set (>=1) b/c it is NOT a leaf
//          node and that inner node might contain 1 or more edges to other
//          nodes that can readily be included in the independent set (excluding
//          the edge connecting to the leaf node (v))
//
//          this includes cases like
//
//                y*
//                |
//          x --- x --- u --- v
//          *           *
//
//                y*
//                |
//          x --- x --- u --- v
//          *                 *
//
//              notice the (x,u,v) group is treated like an invariant group
//                  where x is always excluded and either ONE of u,v is included
//
//              this easily simplifies the case to the leaf node
//
//
//  IMPL:
//      for every tree, search for the excluded node u (adjacent to a node leaf)
//      connect them up
//          NOTICE: yes we can put k-1 trees' node u and connect with one tree's
//          node v, but we can just connect all the trees' node u for simpler
//          impl but also shows how it doesn't really matter since we're not
//          adding NEW nodes we're only adding NEW edges => MIVS can stay the
//          same (optimal) or go down so might as well just connect all the
//          node-u together
//
//     special case: a disconnected nodes can actually increase the MIVS (0->1
//     edge, but increasing any more edges only make MIVS stay the same or
//     decrease)
//
//     hence, if any trees are single-nodes (edge-less)
//          treat it as node (v) and connect to the designated node (u)
//
//     if all trees are single-nodes,
//          designate one of the tree's node as node (u)
//
//   IMPL:
//      iterate through all k trees
//          if not edge-less:
//              find the node (u) and record it
//          otherwise (edge-less):
//              find the node (v) and record it
//      ~~    at the k-th trees
//
//      if all the trees so far are single-nodes,
//          ~~~ then designate the first tree's single-node as node (u)
//
//
//      otherwise
//
//      blah blah blah stuffy implementation

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(k);
  pll designated_node_u = {-1, -1};
  vpll node_us;
  II(t, k) {
    I(n);
    IVP(e, n - 1);

    vector<vll> adj_list(n, vll{});
    II(e_i, n - 1) {
      adj_list[e[e_i].first - 1].PB(e[e_i].second - 1);
      adj_list[e[e_i].second - 1].PB(e[e_i].first - 1);
    }

    ll node_u, node_v;
    II(i, adj_list.size()) {
      // by the assumption of trees => child node always exist
      // also if n>=3, the parent of this will always have .size() > 1
      // if n==2, then either can be u or v
      if (adj_list[i].size() == 1) {
        node_v = i;
        node_u = adj_list[i][0];
      }
    }

    if (n > 1) {
      if (designated_node_u.first == -1) {
        // un-assigned
        designated_node_u = {t + 1, node_u + 1};
      } else {
        // assigned
        // NOTE, PER LOCAL TREE WE ALWAYS USE NODE U
        node_us.PB({t + 1, node_u + 1});
      }
    } else {
      node_us.PB({t + 1, 1});
    }
  };

  // remember, we can always just connect two node excluded together
  if (designated_node_u.first == -1) {
    designated_node_u = node_us.back();
    node_us.pop_back();
  }

  //   II(t, k) {
  //
  // }

  II(i, k - 1) {
    O(node_us[i].first, node_us[i].second, designated_node_u.first,
      designated_node_u.second);
  }
}

/*
 *
 *
 *
 * proof of orthonormality of matrix A
 *
 *
 *
 *  1  1 -4  1  1  0  0  0
 *  0  1  1 -4  1  1  0  0
 *  0  0  1  1 -4  1  1  0
 *  0  0  0  1  1 -4  1  1
 *  0  0  0  0  1  1 -4  1
 *  0  0  0  0  0  1  1 -4
 *
 */
