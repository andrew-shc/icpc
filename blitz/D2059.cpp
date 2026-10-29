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
// what do they mean by min total cost??
//
// so there are two tokens on two different graphs with different edge config
// (but same amount of vertices)
//
// given the starting position of the two tokens, we want to find given
// infinite-runtime whats the minimum possible accumulated divergence between
// the token in g1 and token in g2
//
//
// TC#1:
//      - tokens in both graphs starts in the exact same position
//      - tokens in both graphs has the same shared edge config
//      -       => minimal 0 divergence throughout the infinite-runtime
//
//      in summary, same starting position and SOME shared common path
//
// TC#2:
//      - tokens in both grpahs has the same shared edge config
//      - BUT DIFFERENT STARTING POSITION
//      - and by the assumption of always moving the token to one of the
//      adjacent vertices => divergence always exist => -1
//
//      in summary, different starting position with RIGID/INFLEXIBLE SHARED
//      subset path that results in always a non-zero divergence
//
// TC#3:
//      -
//
//
// P.1: by the assumption of UNDIRECTED graphs,
//      we can always walk "BACKWARDS" (go back to the originating vertices)
//      => 2-loop always exist
//
//          (actually, this shows that TC#1 would be possible if the starting
//          position differ by even amount of distance)
// P.2: by the assumption of CONNECTED graphs,
//      m_{1,2} >= n-1
//          if m_{1,2} == n-1:
//              one or both of the respective g_{1,2} is a TREE (no loops)
//
//      ^^ actually useless property by the nature of undirected graphs
//      (UNconditionals existence of 2-loops)
//
// P.3: we start counting the cost of operation EXCLUDING the starting vertex
//
// P.4: there must exist a shared 2-loop (i.e., shared edge invariant to the
//      ordering)
//      ==> or else, this is STRICTLY nonzero-div. => -1
//
//
// IMPL:
//
//      find all the 2-loops and compute the lowest cost for
//              even distance and odd distance (from the starting vertex)
//              to either ends/vertices of the 2-loop... (4 combination)
//
//      i
//
//
// ~~~~ P.4: the moment we are able to have both tokens match on the same
// ~ vertices (we do not have the guarantee the grpahs have the same edges, even
// ~ if the same vertices, 0-divergence 2-loop cannot be formed unless the
// ~ destination vertice is arrived from the same vertice also)
//
//
// === TEMPORARILY STUCK: COMPLEXITY OF SOLN. ===
//
//  !!!! 1. classic example of graph reduction! (ICS 46!)
//  !!!! 2. both m_1 and m_2 are at a quadratic-soln-space constraint!!!
//          quadratic solutions are fine!!
//
//      we can reduce this problem as follows:
//          create the unified graph G*=(V*,E*)
//
//          V* := V1 x V2       as a tuple
//          E* := (V1 x V2) x (neighbors(V1) x neighbors(V2))
//
//
//          recall, 1K shared nodes, 2K edges from each graphs,
//              quadratic construction and solution are fine
//
//          then, we just use Dijkstra's over it
//          where the cost of an edge is the cost of the RECEIVING NODE (of the
//          edge) VALUE'S differences
//
//          (Dijkstra will find the minimal cost over cost defined over edges as
//          long the costs are not negative)
//
//      (AND REMEMBER, WE ONLY CARE ABOUT THE MIN COST, NOT TRACKING PATHS =>
//      DIJKSTRA HELPS)
//
//      and also b/c greedy
//
// Dijkstra implementation:
//
//      1. we store/cache/"DP" the current node's min cost value
//      2. we use DFS???
//              no BFS on the min-cost
//
//      3. end point is defined whenever (v1, v2) s.t. v1==v2
//

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n, s1, s2);

  // vpll g1, g2;
  vector<vll> adj_list_g1(n); // there suppose to be vectros of vectors
  vector<vll> adj_list_g2(n);
  // vpll edge_list; // separate edge list (again) to check for case -1 (do we
  // need it though?) can't dijkstra handle it? especially with the other -1
  // case like in TC#2 where merely determining the edges won't be enough?
  //
  // because even when two graphs crosses at the same vertex
  // point, edges still matter. this goes back to the case -1
  // WITHOUT EXPLICIT HANDLING (i.e., DIRECT OUTPUT OF -1). if
  // edges completly differ, the unified graph is merely going
  // through this graph as usual but cannot be used to compute
  // final cost when (v1 == v2) in which it will be ignored
  //
  // this is what good[] does in their solution and which we
  // would name it as valid_2loops;

  set<pll> edge_list; // O(nlogn) instead of O(n^2)
  vector<bool> valid_2loops(n, false);
  I(m1);
  II(i, m1) {
    I(a, b);
    a--;
    b--;
    // g1.PB({a, b});
    adj_list_g1[a].PB(b);
    adj_list_g1[b].PB(a);
    if (a < b) {
      swap(a, b);
    }
    // edge_list.PB({a, b});
    edge_list.insert({a, b});
  }
  I(m2);
  II(j, m2) {
    I(c, d);
    // g2.PB({c, d});
    c--;
    d--;
    adj_list_g2[c].PB(d);
    adj_list_g2[d].PB(c);

    if (c < d) {
      swap(c, d);
    }

    if (edge_list.find({c, d}) != edge_list.end()) {
      valid_2loops[c] = true;
      valid_2loops[d] = true;
    }
    // if (find(edge_list.begin(), edge_list.end(), {c, d}) != edge_list.end())
    // {
    // }

    // if (edge_list.find({c, d}) != edge_list.end()) {
    // }
    // if (c < d) {
    //   swap(c, d);
    // }
    // edge_list.PB({c, d});
  };

  vector<vll> min_cost(n, vll(n, LLONG_MAX));
  set<pair<ll, pll>> dijkstra; // auto-sorts on first
  min_cost[s1 - 1][s2 - 1] = 0;
  dijkstra.insert({0, {s1 - 1, s2 - 1}});
  while (!dijkstra.empty()) {
    // DO NOT &[], once erase() is called it will be a dangling pointer
    auto [c, v] = *dijkstra.begin();
    dijkstra.erase(dijkstra.begin());

    // find the adjacent of v.first and v.second
    for (auto &adj_v1 : adj_list_g1[v.first]) {
      for (auto &adj_v2 : adj_list_g2[v.second]) {
        // how do we traverse?
        // what does dijkstra say about minimzing cost??
        // dijkstra.insert({cost??, {adj_v1, adj_v2}})

        ll adj_cost = abs(adj_v1 - adj_v2);

        if (adj_cost + min_cost[v.first][v.second] < min_cost[adj_v1][adj_v2]) {
          // to get to the adjacent, it must go through an additional adjacent
          // cost. but somehow this is less, so we update the min_cost matrix
          // value
          // ELSE, it is already optimal and just ignore
          // this is sort of our "visisted" state in Dijkstra
          //
          // !!!! make sure to remove the element also in the beginning (done at
          // the beginning of inside of the while loop)

          // !!! also make sure to UPDATE the sentinel value min_cost (we don't
          // need the value, just there for sorting purposes)
          // and also CONDITIONALLY erases if that elements even exist before
          dijkstra.erase({min_cost[adj_v1][adj_v2], {adj_v1, adj_v2}});
          min_cost[adj_v1][adj_v2] = adj_cost + min_cost[v.first][v.second];
          dijkstra.insert({min_cost[adj_v1][adj_v2], {adj_v1, adj_v2}});
        }
      }
    }
  }

  // now, we just count all the min_cost possible on the pre-computed matrix on
  // the cases where u==v (but also that they have the same edges which is where
  // valid_2loops come in)

  ll min_cost_real = LLONG_MAX;
  II(i, n) {
    DBGLN(i + 1, valid_2loops[i], min_cost[i][i]);
    if (valid_2loops[i]) {
      min_cost_real = min(min_cost_real, min_cost[i][i]);
    }
  }

  if (min_cost_real != LLONG_MAX) {
    O(min_cost_real);
  } else {
    O(-1);
  }

  // dijkstra

  // construction of G* via adj list
  //    index ref to vector<pair<vll, ll>> where ll is the cost
  //    we don't even have to record the underlying state it actually
  //    represents
  //
  // actually, this is the only tine when adj matrix useful
  // not because the graph is bidirectional but because we have two graphs to
  // sort of "combine" or go through the combinations
  //
  // but how would we know which vertices to go next? (just go through the
  // constructed the adj list BECAUSE THAT'S GIVEN TO US!)
  //      shouldn't we include both direction of the edges?
  //      like say we start with vertex 5, if we always assume the neighbor
  //      has a higher value how would we index/find the neighbor of smaller
  //      value?
  //
  //      the solution does do it! (confirmed)
  vector<vpll> adj_list;
}
