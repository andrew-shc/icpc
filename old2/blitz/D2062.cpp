#include <bits/stdc++.h>
#include <climits>
#include <stack>

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
//
// P.1: the operation (u,v) is weird in that u is the parent and any subtree of
//      v (inclusive) are incremented (i.e., u decides the DIRECTION of the
//      subtree of v)
// P.2: we can ignore the operation (u,v) and abstract this codification as an
//      conceptual assumption that describes given a node v,
//          we can increment (++)
//              ALL NODES
//              OR, ALL NODES except ONE OF THE BRANCHES of v
//                  (i.e., the selected/chosen parent branch)
//                  (e.g., at leaf node, it can just increment itself when it
//                      treats the only path to it as the parent path)
//
// === STUCK: ONLY COMPLEX OBSERVATION, HYPOTHESIZED THERE'S MUST BE EASIER
// OBSERVATION ===
//
//
// it could be thought of as some sort of "graph DP" instead of the standard
// linear DP in that we can break the problem down to its substructure where we
// want a subtree to all have the same value and eventually (as long you don't
// operate within the same subtree again) it can effectively be invariant to all
// other operations outside of the subtree (and hence some form of DP)
//      BUT, it can also describe some form of GREEDY ON GRAPH (on
//      position/subregion/subtree) where when a subtree are balanced then as
//      long we apply any operations outside fhte node (which is optimal
//      anyways) it will MAINTAIN that status
//
//
//
//!!  PER EDITORIAL
//!!      PARAGRAPH 1:
//          re-imagine the invariance where if the subtree is already balanced,
//          applying any operation outside of it keeps the status of the subtree
//          invariant (that is: balanced)
//!!!           this can be more specifically put on the subtree of v
//!!!             (inclusive). HOWEVER, however we extend the u, the only thing
//!                 that changes are the values of the v-subtree (starting from
//!                 v) INVARIANT to how far apart v and u are because we only
//!                 care about the state of balanced which starts from comparing
//!                 local adjacent vertices' values together which means for
//!                 ever specific case of v we only start to look for its
//!                 nearest adjacent value and applying operation to v changes
//!                 the status between its adjacent value (doesn't matter if the
//!                 adjacent value is balanced with more than 1 elements except
//!                 v). and many observation can be made to reinforce the
//!                 solution but the key idea is for a tree to be balanced we
//!                 start looking to its immediate neighbor, and if say 2-nodes
//!                 apart is when the node v becomes unbalanced with that node,
//!                 there's a closer node that we can use to compare against (to
//!                 simplify the impl of the observation)
//!                     think 5 == 5 == 5 <= 6
//!                                     *, impl-wise, we can just look for
//!                                     locally different values
//!                 NO GRAPHS NEEDED (YET) JUST OBSERVATION
//!
//!          hence, the values are the sum of abs-diff between their adjacent
//!          vertices value (while the status of balanced needs to be compared
//!          edge by edge, the operation can ONLY CHANGE/MUTATE THE STATE OF
//!          BALANCED EDGE-BY-EDGE => HENCE, sum of abs-diff on every edge)
//!             since the state of balanced does not care about the fixed-point
//!             value, but rather the equality of each vertices' value, we have
//!             the DoF to ARTBIRARILY pick a vertex to start off from (the DoF
//!             to answer the question: minimal value possible)
//
//  and then we have the 2nd DoF: the initial value to pick that would best
//  yield the minimal value possible. remember, the sum of abs-diff suggests we
//  want to minimize..... (do we need graphs??)
//      overlaps??? (but this is absolute and overlaps are fine)
//      what is not fine is "ARTIFICIALLY CREATING" overlaps
//
//  KEY OBSERVATION: lowest value is not always the best value CLEARLY by the
//          sum of adjacent differences
//
//  ANOTHER OBSERVATION:
//          if there's a 3 exclusive ranges of values in a 3-adjacent nodes,
//              the center node cannot change the fate of the sum of abs diff
//              but the two outer nodes can certainly change the fate (in  which
//              we want to minimize the range)
//
//          let's say we have the GLOBAL max and the GLOBAL min
//
//          where the GLOBAL max is the highest value any node NEEDS to be
//              (like if the node with the highest or the equally high adjacent
//              nodes can be matched at a lower value then the theoretical max
//              of the highest range of that node's constraint)
//          and the GLOBAL min (same exception as above)
//
//              ^^ that doesn't matter because the sum of diffs only care about
//              NEIGHBORED, LOCALLY-ADJACENT values
//
//
//      again, if there are any overlapping constraints for any adjacent
//      vertices ==> use the shared values
//
//      visually, this can be thought of as an attempt to maximize the
//      "TERRACING" of these values within the given constraints.
//
//          again, if a given constraint is exclusively in the middle against
//          all of its neighboring veritces, whatever value that vertices take
//          it doesn't matter (the higher neighbor and the lower neighbor
//          cancels => but this requires at least one high and at least one low
//          neighros (exclusively))
//
//          we can generalize this to given any selected neighrboing value, if
//          the node-of-interest's value is in the middle, then the sum of
//          abs-diff does not matter
//
//  ~~~~~
//
//       ~   but what if we have say 3 equally-larger neighbor and 1 lower
//        ~  neighbor... wouldn't it make sense to say the sum of differences to
//         ~ be 1 rather than 3 or even 4? (because we can just update the
//         single
//          ~one so like THREE birds in one stone??)
//
//~          was PARAGRAPH#1 just a high-level soln.?
//~
// ~             ^^ well that's because that's counting the ops (which we don't
//  ~            care) we just want to minimize the values while the above
//   ~           expression just helps the thinking of the coming paragraph.
//
//              ~~~~~~~~~~~
//
//
//
//!!!!!!    PARAGRAPH 2
//      yes we do need to traverse the graph it seems like
//
//
//
//  notice: the sum of diffs only treats the edge as bidirectional/undirecteed
//  (i.e., counts each edge once) despite through the process, that same node
//  might need to be increased twice, but on the second time, one side of the
//  node has already been terraced/corrected so that whole direction does not
//  need to be added anymore (e.g., if that side has the largest max of the
//  graph tree)
//      (because, for every node that needs to be corrected once makes that
//      whole value to be monotonic in some direction, and another duplicate
//      correction to make it flat/terraced)
//
//  FOR finding the optimal INITIIAL value:
//      we want to minimize the sum of diffs (minimize the increment)
//
//      by the observation of intermediate monotonicity (before
//      terracing/flattening), it implies the max will
//
//      9 4 6 5 4 3 2 1
//   1.
//     11 6 6 5 4 3 2 1
//   2.
//      9 4 6 6 6 6 6 6
//     11 6 6 6 6 6 6 6
//
//          notice anything?
//          11 is the best possible answer
//
//
//      actually the soln can be simplified to an easier observation of
//      achieving some form of monotonicity w.r.t. some node but this requires
//      iterating through every possible node to be considered as the root
//
//
//~  also we are able to arbitrarily pick the 1st node as the root
//~      <== the optimal answer (min possible value of a balanced tree) is
//~      INVARIANT to the choice of some "starting" root/node
//
//
// the editorial is actually referring to a 2-step soln. not a more specific
// soln. on paragraph 2
//
// while the final answer would be a_root + sum max(a_u-a_fa(u),0)
//                                                       ^
//                                                       NOTICE
//                     this is NOT SOME NAIVE SUM OF DIFFS
//                          nor abs-diffs
//
//                          its the "ANY LARGEST" (getting confused between Step
//                          1 & Step 2 in the provided impl.)
//                     this is >>~~~ANY LARGEST~~~<< ~~~~>>SUM OF<<~~~ POSITIVE
//                     DIFFERENCES AMONGST ITS CHILDREN (no adding up against
//                     individual children, just a max-consideration for all of
//                     its children)
//                          ==> basically, we're just trying to find the sum of
//                          max differences between each node u against each of
//                          its neighboring node
//                              (because, we can ONLY GO UP, we just need to
//                              find what it takes to get the adjacent max w/o
//                              double-counting)
//
//                              and going back to the earlier observation of the
//                              invariance by the simulatenous increments of all
//                              the child nodes, we also INDEPENDENTLY
//                              accumulate the increments needed for every node
//                              to reach to its neareset max (we can sum because
//                              we can treat each of such operation as
//                              independent from each other)
//
//                              reaching to its nearest max makes that nearest
//                              max and the current levelled INDEPENDENT of
//                              what's going on elsewhere (the
//                              differences/gradient/derivative is still present
//                              elsewhere by the simulatenous increment or
//                              no-increment except at the point of change)
//
//
//!!!!! EDITORIAL CODE ITSELF
//!         uses dfs since we want to find the leaf node first and notice how it
//!         initializes the low constraint first since we do want the minimal
//!         value possible but also monotonic up where the leaves are the
//!         farthest edge of the root (assumed to be the max at the end) hence
//!         we start with the smallest first
//!                 the max(subtraction,0) is basically like a CONDITIONAL
//!                 addition. if not monotonic then add the amnt it takes to
//!                 make the subtree monotonic. (and the child with the largest
//!                 also w/o double-counting like not summing against all
//!                 children that are larger than the current node since a child
//!                 that is larger but not the largest can set the current node
//!                 to that largest while also maintaing monotonicity against
//!                 other childrens ensuring minimization during the flattening)
//
//
//~~~~PIGGYBACK the larger
//~~!                 node where we can arbitrarily operate with
//~~!                 u=any-of-its-child and v=the-current-node)
//
//                  for the step 1 (initialization)
//                  step 2 just sums these differences
//                      (clearly makes sense if there are different values of
//                      the children, assigning one of the children as the
//                      parent increases all other values including the original
//                      parent but as per the prior observation it just
//                      integrates and vaporizes the difference between teh
//                      selected children treated as parent node u (during the
//                      operation) which is INDEPENDENT from the operation of
//                      other children so we can just sum it)
//                          if we want to bring it closer to a "probabilistic"
//                          analogy, it is probably better to use the term
//                          "MUTUALLY EXCLUSIVE" rather than "INDEPENDENT" since
//                          we're summing
//
//~             and correction from the previous, but it seems like we want to
//~             sum it? (i guess in the case when the node branches, if they're
//~             not monotonic,)
//
//
//   all that remains with one question:
//      how are all these steps independent/invariant from the selected root
//      node?
//
//      if we let the root node walk to any of its adjacent node,
//          we at most change the direction of a SINGLE edge (per chatgpt)
//          and we can intuitively do some induction on it to show it would not
//          matter to let the root node walk to any other places
//
//      so, the question comes down is it invariant to let the selected root
//      node walk to ONE of its adjacent node?
//          flipping an edge,
//
//              just like before, think in step 1 (init) and step 2
//              (flattening/monotonicitizing)
//
//
//          step 1 (init):
//              worst-case, the upper limit severely restricts and makes it
//              invariant to such cases
//
//          step 2 (monotonicitizing):
//              the CONDITIONAL SUMMATION
//                  if it is to be summed (condition passed)
//                      then flipping the edge, the new node's running value at
//                      that step is already the max that the entire other nodes
//                      in the graph ought to reach towards
//                  if it is not be summed (hit the 0 floor),
//                      then flipping the edge, the new node's running is no
//                      longer the max and NOW needs that summation (and it
//                      makes sense since the conditional summation is basically
//                      the difference which when the edge is flipped just flips
//                      the CONDITIONAL SUMMATION which makes the transformation
//                      process to walk to a selected node invariant to the
//                      resulting final summation)
//
//                      this also works on boundary cases like on the leaf nodes
//
//                  (rough idea brought by chatgpt, IIRC)
//
//
//
//

#define IVP(ap, n)                                                             \
  vpll ap;                                                                     \
  for (ll i = 0; i < n; i++) {                                                 \
    ll ai, bi;                                                                 \
    std::cin >> ai >> bi;                                                      \
    ap.push_back({ai, bi});                                                    \
  }

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n);
  // vpll constraints;
  // II(i, n) {
  //   I(li, ri);
  //   constraints.PB({li, ri});
  // }
  // vpll edges;
  // II(i, n) {
  //   I(ui, vi);
  //   edges.PB({ui, vi});
  // }
  IVP(constraints, n);
  IVP(edges, n - 1);

  // IMPL:
  //
  //      STEP 1 (INIT):
  //            by the invariance, we just arbitrarily select the first node as
  //            our root node to start everything
  //
  //            apply DFS:
  //                 a[i] = clamp(max(neighbors of a[i] one-sided by
  //                 DFS),l[i],r[i])
  //      STEP 2 (MONOTONICITIZATION NEEDED LEFT BY CONDITIONAL SUMMATION):
  //            delta = 0;
  //            apply DFS:
  //                 delta += max(neighbors of a[i] one-sided by DFS - a[i], 0)
  //
  //
  //
  //    inspired by the editorial's impl,
  //          we can fold these two step into a single DFS
  //          and, inspired again, the DFS can be done w/o a stack and directly
  //          operate on the adjaceny list since the adjaceny list will describe
  //          all the needed running neighbors at the current node of the DFS
  //          (which also means removal directly on the adjacent list as needed
  //          for visitation of nodes)
  //
  //          well it's because they used recursion, but with while loop we
  //          still need to keep a stack in track

  // vector<ll, vll> adj_list(n);
  vector<vll> adj_list(n);
  II(i, n - 1) {
    adj_list[edges[i].first - 1].PB(edges[i].second - 1);
    adj_list[edges[i].second - 1].PB(edges[i].first - 1);
  }

  // the optimal initial values
  vll a(n, 0);
  ll min_val_balanced = 0;
  // 2-step folded DFS

  // due to the nature of this problem (needs simulatenous reference to both the
  // parent and the childe), a recursion might be better

  function<void(ll)> dfs = [&](ll v) {
    ll mx = constraints[v].first;
    for (auto &neighbors : adj_list[v]) {
      erase(adj_list[neighbors], v);
      dfs(neighbors);
      mx = max(mx, a[neighbors]);
    }
    a[v] = min(mx, constraints[v].second);

    // CONDITIONAL SUMMATION
    for (auto &neighbors : adj_list[v]) {
      min_val_balanced += max(a[neighbors] - a[v], 0LL);
    }
  };

  dfs(0);

  // REMEMBER, we want the actualy underlying value
  // so we still need to be fixed on some node's value in this case a[0]
  O(min_val_balanced + a[0]);

  // stack<ll> cur_path;
  // cur_path.push(0);

  // while (true) {
  //   // traverse until a leaf node is reached
  //   if (adj_list[cur_path.top()].size() > 0) {
  //     vll &neighbor_neighbor = adj_list[adj_list[cur_path.top()].back()];
  //     erase(neighbor_neighbor, cur_path.top());
  //     adj_list[cur_path.top()].pop_back();
  //     cur_path.push(adj_list[cur_path.top()].back());
  //   } else {
  //     // no more neighbors (including self-ref neighbors)
  //     // OR, a leaf node
  //
  //     a[cur_path.top()] = constraints[cur_path.top()].first;
  //
  //     cur_path.pop();
  //   }
  // }
  // while (true) {
  //   if (cur_path.size() > 0) {
  //     // lower B
  //     // a[cur_path.top()] = constraints[cur_path.top()].first;
  //
  //     // iterate through the neighbors
  //     for (auto &neighbor : adj_list[cur_path.top()]) {
  //       if (neighbor != cur_path.top()) {
  //         cur_path.push(neighbor);
  //         continue;
  //       }
  //     }
  //
  //     // NOTE: after this point, we assume all neighbros have been computed
  //
  //     // upperB
  //     a[cur_path.top()] =
  //         min(max(constraints[cur_path.top()].second, a[cur_path.top()]),
  //             constraints[cur_path.top()].second);
  //
  //     cur_path.pop();
  //   } else {
  //     break;
  //   }
  // }

  ;
}
