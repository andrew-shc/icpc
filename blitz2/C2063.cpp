#include <algorithm>
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
// H.1: remove nodes with 2 largest amount of children?
//      caveat, when a node is removed, its parent will lose one children
//          hence, when 2 nodes with 2-largest amount of childrens are adjacent,
//              one of them will have a children reduced which might result in
//              another node with the same max amnt of children to be the 2nd
//              (i.e., re-calc)
//
//              BUT, we can just do this. since AT MOST 1 children will be
//              reduced, we can first pick 2 largest amount of children
//              tie-breaked by adjacency (target: avoid adjacency). however, if
//              2 largest amnt are strictly greater than others, then adjacency
//              is invariant (although a -1 must be included in the answer)
//
// IMPL:
//      find two nodes with 2-highest count of children
//          ans = node1children + node2children
//      flag if the 2-highest count MUST be adjacent (=> ans--)
//
//      output(ans)
//
//      COUNTER EXAMPLES??
//      while we can look into the orders of the operation, the problem does not
//      care about the orders so we can just optimally select the most
//      intuitiuve order and just forget about the other
//
// checked WA2

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n);
  IVP(ap, n - 1);

  vector<vll> adj_list(n, vll{});
  II(i, n - 1) {
    adj_list[ap[i].first - 1].PB(ap[i].second - 1);
    adj_list[ap[i].second - 1].PB(ap[i].first - 1);
  }

  vll top2_nodes;
  bool adj_required = false;

  auto cnt = [&](const ll v) { return adj_list[v].size(); };
  auto adj = [&](const ll u, const ll v) {
    // assumes adj_list is bidirectional (undirected)
    return find(adj_list[u].begin(), adj_list[u].end(), v) != adj_list[u].end();
  };

  vll v;
  II(i, n) { v.PB(i); }
  sort(v.begin(), v.end(), [&](ll a, ll b) { return cnt(a) < cnt(b); });

  // n>=2

  // PER CHATGPT:
  //      there are indeed cases where the 1st selection is always adj but the
  //      2nd selection can yield non-adj (adjacency is not bidirectional
  //      because the childrens are not always the same with same-count
  //      vertices)
  //
  //    because n nodes and n-1 edges,
  //      (well actually worst case max count is 1 so n^2...)
  //
  //      this actually breaks in a very specific case when all the same-count
  //      nodes are adj to a one central node that was designated as the 1st
  //      selection (what was previously thought of as just leave it alone the
  //      default is the best ACTUALLY implies we got to search w/ the 1st
  //      selection being a neighbor of the previous 1st selection. remember,
  //      this works for direct neighbors, the moment there are same-counted
  //      vertices 2-edges away then this will no longer break)
  //
  //      in this very weird case

  top2_nodes = {v[n - 1], v[n - 2]};
  if (v.size() >= 3 && cnt(v[n - 2]) == cnt(v[n - 3]) &&
      adj(v[n - 1], v[n - 2])) {

    // check for ~~ALTERNATIVE~~ non-adj on
    //      replacement of the 2nd of the 1st max
    //  OR, replacemnet of the 2nd max (between 2nd max and 1st max)
    //
    // regardless, check for non-adj between v[n-2] and any other SAME COUNT

    bool check_flower_edge_case = true;
    DD(i, n - 2) {
      // starts at n-3 (inclusive) and downwards
      if (cnt(v[i]) == cnt(v[n - 2])) {
        if (!adj(v[i], v[n - 1])) {
          top2_nodes = {v[i], v[n - 1]};
          check_flower_edge_case = false;
          break;
        }
      } else {
        // by monotonocity of sorting
        // count will always be less hence imm. breaks
        // check_flower_edge_case = false;
        // ^^ this could be the bug of the bug (remain commented out)
        //      since there can be some useful verticies in here
        break;
      }
    }

    if (check_flower_edge_case && cnt(v[n - 1]) == cnt(v[n - 2])) {
      // suppose n-1 is the center of the flower, we now check for replacing n-1
      // with others
      DD(i, n - 2) {
        // starts at n-3 (inclusive) and downwards
        if (cnt(v[i]) == cnt(v[n - 1])) {
          if (!adj(v[i], v[n - 2])) {
            top2_nodes = {v[i], v[n - 2]};
            check_flower_edge_case = false;
            break;
          }
        } else {
          // by monotonocity of sorting
          // count will always be less hence imm. breaks
          // check_flower_edge_case = false;
          // ^^ this could be the bug of the bug (remain commented out)
          //      since there can be some useful verticies in here
          break;
        }
      }
    }

    // in the flower case, n-1 or n-2 can be the center of the flower
    // if n-1 is the center:
    //  n-1<->n-2 is adj and n-1<->* will also be adj for any * where counts are
    //  same (when there are cases...)
    //
    // if n-2 is the center:
    //  n-1<->n-2 is adj and n-2<->* will also be adj for any * where counts are
    //  same
    //
    //  just check quadratically?
    //
    //  additional observation: if 1st and 2nd max are different
    //      it is optimal and even if 1st is the center (we must keep 1st and if
    //      not keep it then keeping it is still AS good w/ adj)
    //
    //      if 2nd is the center, we don't really care since we're also
    //      iterating through the 2nd (if it has duplicates, if not just keep
    //      it)
    //
    //
    //  only when 1st and 2nd max are the same do we flip them
    //      so instead of checking whether alternatives to n-2 will work when
    //      n-1 is the center of the flower,
    //
    //      we can replace swap(n-1,n-2) s.t. the center of the flower can be
    //      replaced to find other non-adjecents..

    // THE edge case will be known as the flower case
    // bool check_edge_case_flower = true;
    // ll check_edge_case_flower = 2;
    // while (check_edge_case_flower) {
    //   DD(i, n - 2) {
    //     // starts at n-3 (inclusive) and downwards
    //     if (cnt(v[i]) == cnt(v[n - 2])) {
    //       if (!adj(v[i], v[n - 1])) {
    //         top2_nodes = {v[i], v[n - 1]};
    //         // check_edge_case_flower = false;
    //         check_edge_case_flower = 0;
    //         break;
    //       }
    //     } else {
    //       // by monotonocity of sorting
    //       // count will always be less hence imm. breaks
    //       // top2_nodes = {v[n - 1], v[n - 2]};
    //       // check_edge_case_flower = false;
    //       check_edge_case_flower = 0;
    //       break;
    //     }
    //   }
    //   // swap(v[n - 2], v[n - 3]);
    //   swap(v[n - 1], v[n - 2]);
    //   // if 2 different top-2 maxes => no need to check (auto ends when cnt
    //   //        differs)
    //   //          but we could've missed some +1s....!!!
    //   //          still need to check
    //   // if 2 same top-2 maxes => need to check (and will check)
    //
    //   check_edge_case_flower =
    //       check_edge_case_flower == 0 ? 0 : check_edge_case_flower - 1;
    //   // check_edge_case_flower =
    //   //     min(check_edge_case_flower, check_edge_case_flower - 1);
    //   // v will no longer be referenced if the loop is to be terminated at
    //   this
    //   // point (should ONLY be ran at most twice)
    //   //
    //   // well except if it is always adj everywhere
    //   // like in this case: 1--2--3
    //   //
    //   // so we do need to manually stop it
    // }
    // if (check_edge_case_flower) {
    // }
  }

  if (adj(top2_nodes[0], top2_nodes[1])) {
    adj_required = true;
  }

  ll max_no = -1;
  max_no += cnt(top2_nodes[0]);
  max_no += cnt(top2_nodes[1]);
  if (adj_required)
    max_no--;

  O(max_no);

  // consider
  //
  // T=1
  // 3
  // 1 2
  // 2 3
  //
  // 1 -- 2 -- 3
  // *    *
  //
  // either 1/3 are adj => pick 1/2 (per default say)
  //
  // -1 += 1 += 2 -= 1 (by adj)
  // => 3-2 = 1 ???? (should be 0) (no we're counting connected COMPONENTS not
  // edges)

  // default
  // top2_nodes = {v[n - 1], v[n - 2]};
  // DBG_ITER(top2_nodes);
  // /*   if (v.size() >= 3 && v[n - 2] == v[n - 3]) { */
  // if (v.size() >= 3 && cnt(v[n - 2]) == cnt(v[n - 3])) {
  //   // check for non-adj on
  //   //      replacement of the 2nd of the 1st max
  //   //  OR, replacemnet of the 2nd max (between 2nd max and 1st max)
  //   //
  //   // regardless, check for non-adj between v[n-2] and any other SAME COUNT
  //   DBGLN("CHECK FOR NON-ADJ");
  //   DD(i, n - 2) {
  //     // starts at n-3 (inclusive) and downwards
  //     if (cnt(v[i]) == cnt(v[n - 2])) {
  //       if (!adj(v[i], v[n - 1])) {
  //         top2_nodes = {v[i], v[n - 1]};
  //         break;
  //       }
  //     } else {
  //       // by monotonocity of sorting
  //       // count will always be less hence imm. breaks
  //       // top2_nodes = {v[n - 1], v[n - 2]};
  //       break;
  //     }
  //   }
  //
  //   // top2_nodes always defined here
  //   // EXCEPT for cases when its ALL adjacent and valid counting for the
  //   entire
  //   // array
  //   //
  //   // just define it by default above
  // } else {
  //   // if the 2nd and 3rd are different =>
  //   //      exactly 2 1st max (fine)
  //   //  OR, exactly 1 1st max and 1 2nd max (fine)
  //   // top2_nodes = {v[n - 1], v[n - 2]};
  // }

  // if (v[n - 1] == v[n - 2]) {
  //   if (v.size() >= 3 && v[n - 2] == v[n - 3]) {
  //     // check for non-adj on the replacement for the 2nd of the 1st max
  //   } else {
  //     top2_nodes = {v[n - 1], v[n - 2]};
  //   }
  // } else {
  //   if (v.size() >= 3 && v[n - 2] == v[n - 3]) {
  //     // check for non-adj on the 2nd max (between 1st and 2nd max)
  //   } else {
  //     top2_nodes = {v[n - 1], v[n - 2]};
  //   }
  // }

  // why are we doing this whole loop?
  // just look at prior observation:
  //  pick 2 largest that are not adjacent
  //
  //  no quadratic
  //
  //  just pick 2 largest???
  //  suppose x-2,x-1,x => x-1,x are the two largest. if x-1,x are adjacent, x-1
  //  is AS GODD AS x-2 (let alone x-2 is assumed to be not adjacent to x)
  //
  //  ONLY when there are duplicates x-1 or x (for cases of x,x) do we check for
  //  adjacency
  //
  //  if x-1,x,x => again, x,x will always be optimal
  //
  //  IMPL:
  //      pick 2 largest
  //      if >=3-way duplicates on the largest:
  //          pick the non-adjacent one if possible else just pick adjacent
  //          (SAME or better than picking the next largest level/group)
  //      if >=2-way duplicates on the 2nd largest:
  //          pick the non-adjacent one if possible else just pick adjacent
  //
  //
  //  ~~~if the 2 largest are duplicates, pick ones that are not adjacent

  // bool no_parent = false; // if one of the node is the root => --
  // but def. of parent is very abstract here
  // parents are part of the children
  // better to not think of any notion of parents/root
  // but just neighbors of spaghetti
  // II(i, n) {
  //   // DBGLN(i + 1);
  //   // DBG_ITER(top2_nodes);
  //
  //   if (top2_nodes.size() < 2) {
  //     top2_nodes.PB(i);
  //   } else {
  //     DBGLN(i + 1, cnt(top2_nodes[0]), cnt(top2_nodes[1]), cnt(i));
  //     DBG_ITER(top2_nodes);
  //
  //     // auto cnt = [&](const ll v) { return adj_list[v].size(); };
  //     // auto adj = [&](const ll u, const ll v) {
  //     //   // assumes adj_list is bidirectional (undirected)
  //     //   return find(adj_list[u].begin(), adj_list[u].end(), v) !=
  //     //          adj_list[u].end();
  //     // };
  //     ll a = top2_nodes[0];
  //     ll b = top2_nodes[1];
  //     ll c = i;
  //
  //     // if (cnt(c) < cnt(a) && cnt(c) < cnt(b)) {
  //     //   // c is useless
  //     // } else {
  //     // ~~~ c==a || c==b
  //     // c>=a || c>=b || both
  //     if (cnt(a) < cnt(c) && cnt(b) < cnt(c)) {
  //       if (cnt(a) < cnt(b)) {
  //         top2_nodes = {c, b};
  //       } else if (cnt(a) > cnt(b)) {
  //         top2_nodes = {a, c};
  //       } else {
  //         // case a==b<c
  //         //
  //         // the outer last cases check for a==c||b==c not a==b<c
  //         //
  //         // in that case, just do
  //         //
  //         // if !adj(a,c):
  //         //    replace b->c
  //         // else: //whatever, just get c into it
  //         //    replace a->c
  //         if (!adj(a, c)) {
  //           top2_nodes = {a, c};
  //         } else {
  //           top2_nodes = {c, b};
  //         }
  //       }
  //       // note: if cnt(a)==cnt(b), if adj, we should still check for adj
  //       // break.. (but this is all strictly </>)
  //       // this is checked later actually
  //       //
  //       // else if (cnt(a) == cnt(b)) {
  //       //           // else
  //       //         }
  //     } else if (cnt(a) < cnt(c)) {
  //       // replace a w/ c
  //       top2_nodes = {c, b};
  //     } else if (cnt(b) < cnt(c)) {
  //       // replace b w/ c
  //       top2_nodes = {a, c};
  //     } else if (cnt(a) == cnt(c) && !adj(b, c)) {
  //       top2_nodes = {c, b};
  //     } else if (cnt(b) == cnt(c) && !adj(a, c)) {
  //       top2_nodes = {a, c};
  //     }
  //
  //     // ~~~~
  //     // even if its not adjacent, there can be cases where equal count are
  //     // still adjacent and woule be the best to move towards to w/o
  //     adjacency
  //
  //     // else if (adj(a, b)) {
  //     //         // if all other options no longer increase the RAW count
  //     //         // if they're adj, check if we can pick up a +1 by breaking
  //     the
  //     //         // adjacency
  //     //
  //     //         if (cnt(a) == cnt(c) && !adj(b, c)) {
  //     //           // replace a
  //     //           top2_nodes = {c, b};
  //     //         } else if (cnt(b) == cnt(c) && !adj(a, c)) {
  //     //           // replace b
  //     //           top2_nodes = {a, c};
  //     //         }
  //     //       } else {
  //     //         // !adj(a,b) => avoid adjacency if possible
  //     //       }
  //
  //     // else if (cnt(a) == cnt(b) && cnt(b) <= cnt(c) && adj(a, b)) {
  //     //         // only happens w/ a==b==c
  //     //         if (!adj(a, c)) {
  //     //           top2_nodes = {a, c};
  //     //         } else { // b not adjacent to c => replace a
  //     //           top2_nodes = {c, b};
  //     //         }
  //     //         // NOTE: adj(a,b)&&adj(a,c)&&adj(b,c) <=> loops <=> not a
  //     tree
  //     //         //                            ^^ must be false if prev 2 are
  //     //         true
  //     //       }
  //
  //     // technically cnt(a)==cnt(b) is too strict
  //     // we just want to remove any adjaency if possible
  //     // revised:
  //     //      if(a<->b adjacent):
  //     //              if(cnt a==cnt c && !adj(b,c)): replace a!
  //     //              if(cnt b==cnt c && !adj(a,c)): replace b!
  //     // obviously, if cnt a or cnt b is < cnt c
  //     //    replace the smaller of them <-- SMALLER OF THE TWO (if two
  //     smaller)
  //     //    ++ IMPORTANTLY, we do not care about adjacency (even if we
  //     tailored
  //     //    to no adjacency in prior run)
  //     // obviously, if cnt < cnt a or cnt b (just don't)
  //     // when ==, then check for adjacency breaks
  //
  //     //              ~~if(cnt a==cnt c && !adj(a,c)): replace!
  //     //              ~~if(cnt b==cnt c && !adj(b,c)): replace!
  //     //
  //     //
  //     //
  //
  //     // if (cnt(a) == cnt(b) && adj(a, b)) {
  //     //
  //     // } else {
  //     //   // either cnt(a)!=cnt(b) => c will just replace one of them (does
  //     //   not
  //     //   // change the status quo)
  //     //   //    (and also because cnt(a)!=cnt(b), c will be != to one of
  //     //   them)
  //     //   //
  //     //   // OR, not adjacent => already optimal
  //     //   //
  //     //   // by greedy, this will be useless (??)
  //     //   //
  //     //   // but shouldn't we take c in even if it is a<c<=b or b<c<=a ??
  //     //   // adjacency is just a matter of <= or <
  //     //   but we want < since worst case == (w/ adj)
  //     //   but with <= we include == w/o adj but -1!!! w/ adj!!!
  //     // }
  //     // }
  //
  //     // top2_nodes.PB(i);
  //     // auto it = min_element(
  //     //     top2_nodes.begin(), top2_nodes.end(), [&](auto &a, auto &b) {
  //     //       // return adj_list[a].size() < adj_list[b].size();
  //     //       if (adj_list[a].size() < adj_list[b].size()) {
  //     //         return true;
  //     //       } else if (adj_list[a].size() == adj_list[b].size()) {
  //     //         // the tie-breaker
  //     //         return find(adj_list[a].begin(), adj_list[a].end(), b) !=
  //     //                adj_list[a].end();
  //     //       } else {
  //     //         return false;
  //     //       }
  //     //       // PROBLEM, it treats the "tie-breaker" same as something
  //     truely
  //     //       // smaller
  //     //       // better approach
  //     //       //  suppose a is top-1, b is top-2, and c is the incoming
  //     //       //  if c < a && c < b (truely bad)
  //     //       //        ==> array: (a,b)
  //     //       //  otherwise: // equal to one or two of them
  //     //       //      // the only case we would want c to replace one of
  //     them
  //     //       is
  //     //       //      when it tie-breaks (breaks adjacency between a<->b)
  //     //       //          if not adjacent already (let alone equal values),
  //     we
  //     //       can
  //     //       //          truely ignore this case
  //     //       //          otherwise, add it
  //     //       //
  //     //       //      if count(a) == count(b) && a<->b adjacent:
  //     //       //              if a<->c not adjacent:
  //     //       //                  replace b w/ c
  //     //       //              if b<->c not adjacent:
  //     //       //                  replace a w/ c
  //     //       //
  //     //       //              (IMPORTANTLY, even if one of them is not
  //     adjacent
  //     //       //              the other COULD be re-adjacent again with c)
  //     //       //
  //     //       //      // if c == a && adjace
  //     //     });
  //     // top2_nodes.erase(it);
  //
  //     // auto it = min_element(top2_nodes.begin(), top2_nodes.end(),
  //     //                       [&](auto &a, auto &b) {
  //     //                         return adj_list[a].size() <
  //     adj_list[b].size();
  //     //                       });
  //     // if (adj_list[*it].size() < adj_list[i].size()) {
  //     //   top2_nodes.erase(it);
  //     //   top2_nodes.PB(i);
  //     // }
  //   }
  // }

  // gauranteed to be of size 2

  // we could directly do top2_nodes_children_count if only we did not need to
  // re-reference the index again to check for adjacency
  // (althought doing it directly could still be possible)
  // if (find(adj_list[top2_nodes[0]].begin(), adj_list[top2_nodes[0]].end(),
  //          top2_nodes[1]) != adj_list[top2_nodes[0]].end()) {

  // DBGLN(top2_nodes[0] + 1, top2_nodes[1] + 1);
  //
  // // if (T == 3)
  // //   top2_nodes = {1 - 1, 5 - 1};
  //
  // if (adj(top2_nodes[0], top2_nodes[1])) {
  //   // (found, by assumption <=>, the other will find the original also)
  //   //  ==> adjacent
  //   adj_required = true;
  // }
  // // if (adj_list[top2_nodes[0]]) {
  // // }
  //
  // // if we abstractly think of just neighbors (no notion of parents/roots)
  // // 2 vertices removed will always have a SHARED component (in this case, a
  // // SHARED branch)
  // //    => a branch is double-counted (=> -1)
  // //    && if the branch is 1-lengthed (==> adjacent ==> additioanl -1)
  //
  // // ll max_no = 1;
  // // ll max_no = 0;
  // ll max_no = -1;
  // // max_no += adj_list[top2_nodes[0]].size();
  // // max_no += adj_list[top2_nodes[1]].size();
  // max_no += cnt(top2_nodes[0]);
  // max_no += cnt(top2_nodes[1]);
  // if (adj_required)
  //   max_no--;
  //
  // // works eevn with boundary case of n==2: => -1, +=1, +=1, -1
  //
  // O(max_no);
  ;
}

/*
 *
 * 1 -- 2 -- 4 -- 5 -- 6
 * |              |
 * \----3         \-7
 *
 *
 */
