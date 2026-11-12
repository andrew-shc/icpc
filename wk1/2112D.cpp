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
// we can make n good pairs (u,v)
//      if we alternate each edges except TWO ADJ. EDGES
//      (because trees have n-1 edges, we need to utilize two edges to make
//      three good pairs instead of two)
//
//
// for every node, we can color them as alternating colors
//  where we have {sink=only incoming edges, source=only outgoing edges} nodes
//
// this will give us n-1 good pairs
//
//~~~~~
// to get n good pairs,
//  we pick ONLY A 2-DEGREE node and flip one of the edges
//      NO, we need to have a node with an adjacent duplicate COLOR/STATE
//  --> y <- x -> z <-  (2 edges <-> 2 good pairs)
//  --> y <- x <- z <-  (2 edges <-> 3+??? good pairs)
//
//  so it becomes this which is better (suppose x,z are both sink)
//~~~~~~
//
//
// pick a 2-DEG NODE
//      set one of the edge to be incoming
//      set the other edge to be outgoing
//      mark the vertex connected via the incoming edge as source node
//      mark the vertex connected vai the outgoing edge as sink node
//      (so making the alternating source/sink node one MORE apart)
//
// BECAUSE this alternating construction is the MINIMUM possible ways to make
// good pairs (n-1 good pairs), if we try to do it on a >2-deg NODE, it will NOT
// WORK (and might increase in terms of combinations, not linearly)
//      because we cannot decrease the amount of the good pairs anymore than the
//      min construction
//
// HENCE, in both directions, we need SOME node that is EXACTLY  2-degree
//
//
//
//
//

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n);
  IVP(edges, n - 1);

  vector<vll> adj_list(n, vll{});
  II(i, n - 1) {
    adj_list[edges[i].first - 1].PB(edges[i].second - 1);
    adj_list[edges[i].second - 1].PB(edges[i].first - 1);
  }

  ll node_ind = -1;
  II(i, n) {
    if (adj_list[i].size() == 2) {
      node_ind = i;
      break;
    }
  }

  if (node_ind == -1) {
    // bad, no 2-deg node found
    OHNO;
  } else {
    OHYES;

    // construction by BFS from node_ind

    // we assume [0] is the source and [1] is the sink
    O(adj_list[node_ind][0] + 1, node_ind + 1);
    O(node_ind + 1, adj_list[node_ind][1] + 1);
    erase(adj_list[adj_list[node_ind][0]], node_ind);
    erase(adj_list[adj_list[node_ind][1]], node_ind);

    // source <-> sink
    vll cur_sources = {adj_list[node_ind][0]};
    vll cur_sinks = {adj_list[node_ind][1]};
    while (cur_sources.size() > 0 || cur_sinks.size() > 0) {
      // source
      for (auto &source_ind : cur_sources) {
        // source_ind -> (modified) adj
        for (auto &adj_ind : adj_list[source_ind]) {
          O(source_ind + 1, adj_ind + 1);
          erase(adj_list[adj_ind], source_ind);
          cur_sinks.PB(adj_ind);
        }
      }
      cur_sources.clear();

      // sink
      for (auto &sink_ind : cur_sinks) {
        // (modified) adj -> sink_ind
        for (auto &adj_ind : adj_list[sink_ind]) {
          O(adj_ind + 1, sink_ind + 1);
          erase(adj_list[adj_ind], sink_ind);
          cur_sources.PB(adj_ind);
        }
      }
      cur_sinks.clear();
    }
  }

  ;
}
