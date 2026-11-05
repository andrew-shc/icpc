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
// quadratic over nm? like O((nm)^2)??
//
//
// minimize:
// cost = kx+y
//         ^
//     # of ops (rotating rows)
//           ^
//       sum of visited cells' integer
//
// P.1: lower k => allow more operations (more optimal path)
//      higher k => more restricted operations (less optimal path)
//
// graph reduction???
//
//  dijkstra graph reduction??
//
// === PRELIM IDEA: Dijkstra graph reduction on joint-space between operations
// and movements with increasing operation costs (by k) ===
//   ^^^
//   we can make a path between two adjacent rows where we start with a[i][j]
//   and want to reach a[i+1][j] (no cost) or a[i+1][j+z] (additional z*k cost)
//
//
//
//
//  construct a DIRECTED graph where a dijkstra will be optimized over the cost
//  ~~defined to be over each edges
//
//  construct a DIRECTED graph where a Dijkstra will optimize the shortest
//  (least-cost) path over the cost defined on the edges
//
//
//  define a node with NO CHILD as the final termination node
//
//
// !!!!!!!!!!!!!!!!!!!!!! dijkstra's couldve been done but the editorial did a
// ! cleaner way b/c of the problems' more simpler structure (dp state
// ! transitions)
//
//! editorial 2D/3D DP (cubic complexity)
//
//  per editorla, this is what we can do (more simpler than doing dijkstra)
//
// with cubic complexities we can actually just brute-force a bit
//
//
//  ~~ g(i,j,x) = min(f(i,j-1), f(i-1,j), f(i,j-1-x)+kx)+a[i][j]
//  ~~ g(i,j,x) = min(f(i-1,j), f(i,j-1-x)+kx) + a[i][j]
//  g(i,j,x) = min(f(i,j-1), f(i-1, j-x)+kx) + a[i][j]
//  f(i,j) = min_x g(i,j,x)   // abstract away the decision on x foreach i,j
//
//  ~~~// remember, when we take a value, we assume the operations are fixed on
//  ~~~previous row (no need to track different operations)
//
//  // remember, when we greedily take the values (backwards), we just take the
//  implicit x of that backward values's whatever implicit x value (so we don't
//  have to track x)
// ~~~~~~~~~~~~~~~~~~~~~
//
//
// !!! suppose, f represents the minimum cost for cell i,j (i.e., moving to cell
//! i,j after making optimal shift)
//
//! suppose, let g represent the minimus cost for cell i,j GIVEN A FIXED x
//! a is the original array....
//
// by this, we would want f[n-1][m-1] (or f[n][m-1] with 0-padded rows)
//
// f[i][j]    =
// g[i][j][x] = min(f[i-1][j-x]+kx, f[i][j-x-1])+a[i][j-x];
//                  from going down
//                                  from going right
// ~~~~~~~~~~~~~~~~~~~~~~~~^^^^
//
//
//
// f[i][j]   := min cost at i,j
// g[i][j][x] := min cost at i,j given x
//
//
// clearly,
//  f[i][j] = min_x g[i][j][x]
//
// importantly,
//  g[i][j][x] = min() + a[i][j-x]
//                       ^
//                  a represents UNSHIFTED elements whereas g, given [i][j][x]
//                  ASSUMES a shift of x. hence, a transformation layer in the
//                  index-space is needed (i.e. rotation)
//
//              inside the minimum...
//              we have two options which we'll greedily take the minimum
//                  MAINLY by the important observation that we will NEVER
//                  LOOKBACK (go to higher rows)
//
//              down from above OR towards going left from the right cell
//
//              DOWN FROM ABOVE:
//                  naively, a[i-1][j]
//
//                  but since we're finding the mincost, we do
//                  f[i-1][j]
//
//                  however, f (SAME AS a) are UNSHIFTED,
//                  we have to account for the shifting...
//
//                  since we are already doing +a[i][j-x] at g[i][j][x], we
//                  might as well just leave it at that
//
//                  however, g[i-1][j][x] would be much more elegant cleaner
//                  intuitive way....???
//
//                  f[i-1][j] forces/allows the solution to model independence
//                  of rotation per row while also minimizing the cost (the
//                  intended solution)
//
//              LEFT FROM THE RIGHT:
//                  just do =g[i][j-1][x] ????
//
//                  but for this, since we're in the SAME ROW, we have to use
//                  the g with the same x
//
//
//                  IMPL:
//                      only need to keep it as g_i[j][p]
//
//                  IMPORTANTLY, the boundary case of g implicitly includes the
//                  kx cost (if we decide to use the LEFT from RIGHT)
//
// overall,
//
// g[i][j][x] = min(L->R, U->D) + a[i][(m+j-x)%m]
//                  U->D := f[i-1][j] + kx  // remember, no shifting j, since we
//                  assume the input of g (i.e., the indices of the g is AFTER x
//                  amount of shift and we're going back to the absolute
//                  location i,j with no knowledge of shifting)
//                      can better be thought of as g_x[i][j]
//
//                      and we do not care what x is on the previous row (i.e.,
//                      independent, but make sure it is operated from first to
//                      last row incrementally)
//
//                  L->R := g[i][j-1][x]
//                      // previous element, but since we're on the same row we
//                      DO care that SAME EXACT x-shift is used on the previous
//                      element (and make sure operated in order from left to
//                      right)
// f[i][j] = min_x g[i][j][x] for 1<=x<=m-1
//
//
// IMPORTANTLY, BOUNDARY CASES
//      g[i][0][x] = kx  // implicitly carry the current cost
//      f[0][j] = 0  // makes the expression easier and can be thought of as an
//      extension of the grid where the earlier rows are all 0 (i.e., identity
//      of what we're solving / invariant)
//
//
//
// don't do those weird base cases just check it manually
// basic concept: minimization is just greedily minimizing which directions (OF
// THE TWO DIRECITON) to take from

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n, m, k);

  // vector<pair<ll, vll>> e(n * m, make_pair(0, vll{}));
  // source nodes -> connecting/neighboring nodes' {node index & cost}
  // vector<vector<pll>> e(n * m, vector<pll>{});

  // vector<vll> a(n, vll{});
  vector<vll> a;
  II(i, n) {
    IV(a_i, m);
    a.PB(a_i);
  };

  vector<vll> f(n, vll(m, LLONG_MAX));

  II(i, n) {
    vector<vll> g_i(m, vll(m, 0));

    II(j, m) {
      II(x, m) {
        if (i == 0 && j == 0) {
          g_i[j][x] = k * x + a[i][(j + x) % m];
        } else if (i == 0) {
          g_i[j][x] = g_i[j - 1][x] + a[i][(j + x) % m];
        } else if (j == 0) {
          g_i[j][x] = f[i - 1][j] + k * x + a[i][(j + x) % m];
        } else {
          g_i[j][x] =
              min(f[i - 1][j] + k * x, g_i[j - 1][x]) + a[i][(j + x) % m];
        }
      }
    }

    II(j, m) {
      II(x, m) { // x=0..=m-1
        f[i][j] = min(f[i][j], g_i[j][x]);
      }
    }
  }

  O(f[n - 1][m - 1]);

  // vector<vll> f(n + 1, vll(m, 0));
  // // vector<vll> f(n + 1, vll(m, LLONG_MAX));
  // // f[0][0] = 0;
  //
  // for (ll i = 1; i <= n; i++) {
  //   vector<vll> g_i(m + 1, vll(m, 0));
  //   // not m-1 it is m (we have to include m=0 also)
  //
  //   // boundary case (??)
  //   //  it will just take the neighboring 0 on the left for j>1
  //   //
  //   //  but its confusing to set g_i[j][x]=kx for 1<=j,x<=m
  //   //
  //   //  it just makes more sense to directly incorporate kx in the recurrence
  //   //  relation
  //   //
  //   //  but if it is decided, by greedy, that taking a neighboring left
  //   element,
  //   //  then we will double count k*x
  //   //
  //   // ok actually after thinking about it more times.... this makes sense
  //   // in particularly, ~~
  //   //
  //   II(x, m) { g_i[0][x] = k * x; }
  //
  //   // pre-computing g
  //   II(j, m) {
  //     II(x, m) {
  //       g_i[j + 1][x] =
  //           min(g_i[j][x], f[i - 1][j] + k * x) + a[i - 1][((m + j + x) %
  //           m)];
  //
  //       // +k *x;
  //
  //       // g_i[j + 1][x] =
  //       //     min(g_i[j][x], f[i - 1][j] + k * x) + a[i - 1][((m + j + x) %
  //       //     m)];
  //       // j+x not j-x (we're looking from the perspective of i,j with x
  //       defined
  //       // from g)
  //     }
  //   }
  //
  //   II(j, m) {
  //     f[i][j] = LLONG_MAX;
  //     II(x, m) { f[i][j] = min(f[i][j], g_i[j + 1][x]); }
  //   }
  // }
  //
  // O(f[n][m - 1]);

  // 1st row is all 0s
  // vector<vll> f(n + 1, vll(m, 0));
  // f[1][0] = a[0][0];
  // II(i, n) {
  //   II(j, m) {
  //     ll min_g = j > 0 ? f[i + 1][j - 1] : LLONG_MAX;
  //     II(x, m) { min_g = min(min_g, f[i][(m + j - x) % m] + k * x); }
  //     f[i + 1][j] = min_g + a[i][j];
  //   }
  // }
  //
  // O(f[n][m - 1]);

  // II(i, n) {
  //   II(j, m) {
  //     // go down
  //     // if (i + 1 < n) {
  //     //   e[m * i + j].PB({m * (i + 1) + (j), a[i + 1][j]});
  //     // }
  //
  //     // go right
  //     if (j + 1 < m) {
  //       // e[m * i + j].PB({m * (i) + (j + 1), a[i][j + 1]});
  //       // leave edge cost to only the cost of operations?
  //       // since the node cost can be dynamic?
  //       // but this dynamic has a floor, the cost of the visited cell...
  //       // e[m * i + j].PB({m * (i) + (j + 1), 0});
  //       e[m * i + j].PB({m * (i) + (j + 1), a[i][j + 1]});
  //     }
  //
  //     // go down + right (requires operations)
  //     // (extension of the first, hence the first is commented)
  //     // i guess cubic solution is fine here? (cubic construction)
  //     if (i + 1 < n) {
  //       II(jj, m) {
  //         // if j-k>=0 => makes sense
  //         // if j-k<0 => e.g., -1 (right before) means it takes the largest
  //         // amount of rotation
  //         // e[m * i + jj].PB(
  //         // e[m * i + j].PB(
  //         //     {m * (i + 1) + jj, a[i][jj] + ((m + j - jj) % m) * k});
  //         // e[m * i + j].PB({m * (i + 1) + jj, ((m + jj - j) % m) * k});
  //         e[m * i + j].PB(
  //             {m * (i + 1) + jj, a[i + 1][jj] + ((m + jj - j) % m) * k});
  //       }
  //     }
  //   }
  // }
  //
  // // ll min_cost = 0;
  // vll running_cost(n * m, LLONG_MAX);
  //
  // // e: source v --> [ (destination v, cost to that specific v) ]
  //
  // // Dijkstra over it to find a path that minimizes cost
  // //    optimize over a running cost of going that edge where the running
  // cost
  // //    is the current min cost for going through that edge from the
  // beginning
  // //        or replace the pre-existing cost if it less than the initialized
  // //        cost
  // //
  // // where we do a BFS with 1st selection on the lowest cost EDGE
  // //
  // //    the min running cost should be stored on the NODE
  // //
  // // if a path is explored to have a lower cost, it should update the running
  // // cost of the destination vertex to that new lower cost
  // //
  // // so every edge in this grand BFS (Dijkstra) is merely updating if the
  // // previous node's running cost + the selected edge cost = yield a smaller
  // // cost for the next node?
  // //
  // // if the ending node (node with 0-child) is reached =>
  // //      all the remaining edge's cost will merely just increase the cost
  // (all
  // //      the lowest cost edge has been taken up to the termination node)
  //
  // // (edge cost, (source node, destination node))
  // set<pair<ll, pair<ll, ll>>> running_e;
  //
  // // initial sentinel value
  // running_e.insert({0, {0, 0}});
  // running_cost[0] = a[0][0];
  //
  // // while (true) {
  // while (running_e.size() > 0) {
  //   // DBGLN("????");
  //   DBGLN(running_e.size());
  //
  //   // auto &[edge_cost, c] = *running_e.begin();
  //   auto [edge_cost, c] = *running_e.begin();
  //   // do not use reference &, disastrous when calling erase
  //   running_e.erase({edge_cost, c});
  //
  //   if (running_cost[c.first] + edge_cost < running_cost[c.second]) {
  //     running_cost[c.second] = running_cost[c.first] + edge_cost;
  //   }
  //
  //   // expand neighbors
  //   // fill in the running_cost
  //
  //   // because we know we will not re-visit back (no cycles) on this directed
  //   // graph, we do not need to keep track of visisted nodes (or removing
  //   // visited nodes)
  //
  //   if (e[c.second].size() == 0) {
  //     // reached the termination node (must be at the end of the path)
  //
  //     continue;
  //
  //     // no break right? if we want an exhaustive search
  //   }
  //
  //   for (auto &[neighbors, edge_cost_next] : e[c.second]) {
  //     running_e.insert({edge_cost_next, {c.second, neighbors}});
  //   };
  // }
  //
  // // DBG_ITER(running_cost);
  //
  // // (n-1)*m + m-1
  // O(running_cost.back());
  // O(min_cost);
}
