#include <bits/stdc++.h>
#include <climits>

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

// start: 2129
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
// ~~~O.1: a guild is basically a unique onion layer from each vertices within
// the
//      tree (not just from the root)
//
// ~~correction
//  ~~~~O.2: a guild is basically a surrounding envelope from each vertices
//  within
//       the tree (but not an onion since IT CANNOT INCLUDE SUBSET OF ITSELF)
//
//  correction 2.0
//  ~~~O.3: a guild is basical
//
// ~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~
//
//  REPHRASE: a guild is not <=h, a guild IS =h (so not subset for decreasing h,
//  but a layer)
//      hence, a unique guild exists when a tree branches below
//
//
//
// O.1: a (>1 house) unique guild exists AT branching (like a single onion
//                                                     layer)
//        ^^^^^^^^^^^^^^^^^^^^^^^
//            >1-guild
//
// O.2: if >1-guild exists at a lower subtree
//          => ANY nodes that are common of the assumed >1-guild's house would
//             work (at any h)
//          => only ONE of them can take the assumed/selected >1-guild (no
//          double-counting => unique counting)
//          => branches are important here
//      O.2/1: branches arise when there are multiple p_i of the same value
//              (=> ith-node share the same parent)
//
// O.3: we do not care if tree branches 2-way, 3-way, or n-ways
//      we ONLY care about the LOCATION of the branches
//
// consider the root node 1:
//      it can do an additional (++) guilds at each level below as long there
//      are more than >1 house occuping at that level REGARDLESS (INVARIANT) of
//      branches that exists belowi
//
// consider a pre-branching node x:
//      it can do an additional (++) guilds at each level below (within the
//      subtree) as long tehre are more than >1 house occuping at that level
//      (within the subtree) REGARDLESS (INVARIANT) of branching below and
//      branching above
//          for branching above, this is because if there's an another house at
//          the same level but OUTSIDE/EXTERNAL of the subtree it just adds
//          another combination since now we can either have a guild that
//          includes all house in that same level or exclusively select all
//          houses at that level RESTRICTED to the subtree of the branching
//
// any other failed cases?
//      if say the pre-branching node z branches n-way:
//          things as usually
//      but say m of the n-childs of z node further branches
//          then, we have the nodes at 2-level below z possibly have guilds
//          restricted to each m nodes' subtree AND also include z's guild of
//          the 2-level below that contains ALL of them (UNION of ALL of them)
//          since >1-house at the 2-level below while each of the m-nodes does
//          not contain an arrangement where it includes all of the m-nodes'
//          child
//      CE:
//          if the z branches 2-way and the single child m=1 branches 2-way
//          => notice, even though 2-level below has >1-house they're all
//          exclusively part of the m=1 nodes' child (so no unique combination)
//
//          => the houses at that level must NOT BE MONOPILIZED by any one nod
//              (i.e., we can include another single-child node house
//              unbranching or another set of branches)
//          => for the pre-branching node z,
//                  if it ends => ends?
//                  if it branches 1-way => the node below will monopilize all
//                          of the child
//                  if it branches 2-way => continue counting for z
//                      but if any point (not even if the children's children)
//                      monopilize but ANY node below MONOPILIZE the whole
//                      branch => stop counting for z
//
//          or, at each level count how many smallest/most-recent unique branch
//          groups the houses at that level are part of and if >1 => there exist
//          an arrangement where all of the houses at that level are included in
//          a unique guild or maybe a certain amount of the houses are part of
//          another guild from a branch higher then the most-recent
//
//
//
//
//
//
//
// suppose we're at some level with following (*) nodes
//
// * * * * * * * * * * *
// ---------------------  <- root
// ------- --------- ---  <- from higher branch (min. >1 house)
// --- --- ----- --- xxx  <- from a level lower (xxx=same)
//         ---
// you add all the unique bars together at the level
//      DP over levels?
//
// first iteration:
//   dp[level_i]++ from root until the level has been capitilized by some node
//                      below
//   dp[level_i] += 3       a 3-way branch between the root and the current
//                          level?
//   dp[level_i] += 4       a 2-way branch on the left-branch and 2-way branch
//                          on the right?
//   do[level_i] += 1       another branch on the left-branch of the mid-branch?
//                          between the branch affect of the previous and the
//                          next?
//
//   dp[level_i] +=
//
//   dp[level_i] += # of houses @ level i (the smallest
//   level?)
//                                                both-ended base-cases?
//
//   that is a pointless dp (just sum over it => just sum the whole thing)
//
// O.4: monopolization happens when there's a bottle-neck of 1-house at a level
//      (where the number of configuration resets to something)
//
//      O.4/1: however, # of configs can be reduced even before monopolization
//              (e.g., when an entire branch just ends/dies)
//
//
// H.1: for each branching nodes at level H, find the level I where it gets
//      monopolized or the sentinel/imaginary level AFTER the end
//          dp[h+1 to i-1 inclusive]++
//          or just... grand_sum += (i-1)-(h+1) == i-1-h-1 == i-h-2
//              (-2 denotes the exclusion of the level of monopolization or
//              AFTER termination)
//
//      i mean it seems valid?
//
//      how does one determine monopolization or termination for a given
//      branching node z? ALL WITHIN THE SUB-TREE OF THE BRANCHING NODE z (that
//      includes the branching node itself)
//          - monopolization happens when the # of node at the level becomes 1
//                  (=> then the sub-tree takes hold and priority)
//          - termination happens when the # of node at the (imaginary) level
//            becomes 0
//        ==> simply ensure at each levels the # of nodes are >=2 within the
//            sub-tree of the branching node
//
//            is there any sub-quadratic soln.?
//
//          CE: if the branching node and the terminate node occurs at the same
//          level the branching node still monopolizes on the next level
//
// H.2: leaf nodes starts with a value of 1
//          everytime you go up => ++
//          if branched (or merged from down to up) =>
//              sum of branch values + min(branch values) + 1
//
// H.3:
//      guild = n;
//
//      for every leaf node i:
//          depth[i] = 1;
//
//      depth[j]++; for every parent node j of i and so on
//
//      everytime a merge is reached (branch but from bottom to up)
//          => assumes/invariant all the merge below has been handled
//          separately OR no merge below
//
//          guild += min(depth[k] for every branching node k)
//
//          BECAUSE a merge/branch means there are >1 (>=2) houses at that level
//          (which circles back to previous thoughts) => there must exist a
//          separate combination that includes all the sub-trees below from the
//          merging/branching node
//
//  i mean this seems solid?????
//
//
// IMPL:
//      if there exist a DUPLICATE VALUE of p[i] => the VALUE of p[i] is a
//              merging node
//
//  ~~~~~    since node p[i] refers to parent of node i,
//      start with all nodes are set as leaf node
//      for i: set leaf_node[p[i]] = false
//
//      then, in any order, start with the first leaf_node 1@i then recurse (or
//      while loop until p[i]=1)
//          depth[i]++
//          i=p[i]
//
//
// IMPL 2.0:
//      leaf_node[i] (when there is any LACK of reference to i=p[k])
//      merge_node[i] (flagged when there are any duplicate value of i=p[k])
//
// IMPL 3.0:
//      childrens[i]
//          if ==0: => leaf
//          if >=2: => merging
//
//      ~~~~~~~~~~~~~ depth[childrens[i] == 0] = 1
//
//      for k in childrens[i]==0:
//          depth[k]++
//          while p[k] != 1:
//              prev_depth = depth[k]
//              k = p[k]
//              // k will no longer be a leaf node
//              if(prev_depth+1<depth[k]):
//                  depth[k]=prev_depth+1
//
//
//       guilds = n
//
//       for k in childrens[i]>=2:
//          guilds += depth[k]  // already minimized
//
//
//
// test-case:
//
// 2 3 4 5 6 7 8 9 10
// 1 1 3 2 2 4 4 4  3
//
//   /-6
// 1-2-5
//  |
//  |  /-9
//  \3-4-7
//   | \-8
//   |
//   \-10
//
//
// w/o looking at the WA for 5th test case, we need to find the 2nd MAX depth
// not the overall min depth (because we want to exhaustively include all the
// possible guilds => maximize, also)
//
//
//
// editorial:
//
// key idea, we can find the depth from the vertex v and find the relative depth
// w.r.t. the merging nodes by just subtracting the depth of the merging
// node?????????
//
// with the input assumption p[i]<i => for i in 1@1..n:
//                                       for j=1@2..i
//                                          if p[j]==i:
//                                              depth[j] = depth[i]+1
//                                          else:
//                                              break
//                                   => O(n) actually not O(n^2)
//
//                                   max_depth[v]=depth[v] if v is leaf
//
//                              for c children of v
//                                   max_depth[v]=max(max_depth[v],max_depth[c])
//
//
//
//                              ans = n
//                              for all merging node c:
//                                  ans += max_depth[child(v)]-max_depth[v] <--
//                                  just use this key insight to augment my
//                                  existing code instead of re-writing it
//
//
//                              ans = 0
//                              for each node v and its c children (vll of
//                              vll???)
//                              or from
//                              for v=n..1
//                                  ans += 1 + 2nd max of
//                                  max_depth[c]-max_depth[v]
//
// IMPL:
//
//

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n);
  IVLL(p, n - 1); // starts from the 2nd index
  vll children(n, 0);
  II(i, n - 1) { children[p[i] - 1]++; };
  // vll min_depth(n, LLONG_MAX);
  // vpll max2_depth(n, {LLONG_MAX, LLONG_MAX});
  vpll max2_depth(n, {0, 0});
  // ~~~~ assume .first is the max; .second is the second largest
  // remember, we want the most exhaustive amount of guilds
  // actually, a better use of this is instead of max2
  //      the .first is for the max depth of that sub-tree as usual
  //      the .second is the min depth of that sub-tree
  //      because yes you want to the 2 largest max but the 2nd max must be
  //      branched at the branching node itself (any node higher is out of the
  //      sub-tree and any node branched at lower areas are monopolized)
  //
  //
  //  bandage: for childrens[k] == 1 => just max on .first
  //  for childrens[k] == 0 => initialize as usual {1,0}
  //  for childrens[k] >= 2 (merge node) => find the top2 max where each branch
  //  contributes one max at most

  // TLE, use the input assumption of p_i<i => so as we go left of the p vector
  //        if we see a leaf node sure go ahead but if the path has been
  //        traversed by a later node
  //        ==> the more left the p_i is the less deep it is ?
  //              since the i<p_i constraint can be thought of as forcing the
  //              p_i to be further away
  //              OR at same distance from 1
  //
  //                the value of p[i]<i ==> i-th node must have a parent of
  //                smaller index
  //
  //              COUNTER-HYPOTHESIS.1: if we assume i-th node must have a
  //              parent of smaller index,
  //                      COULD the k-th node for k<i have greater depth?
  //                      for a k-th node to have a greater depth then i-th
  //                      node, k-th node has to have some parent at the same
  //                      level as i-th node
  //
  //                              clearly, if k-th node is under i-th node's
  //                              subtree, by the input assumption
  //                              i<p[..p[k]]<p[p[k]]<p[k]
  //                                      HOWEVER, k<i & p[i]<i<=p[k]<k => i<k
  //                                      CONTRADICTION of k<i (contradiction of
  //                                      the counter hypothesis)
  //
  //                              what if the k-th node is child of another node
  //                              j at the same level as i-th node? (e.g.,
  //                              cousins)
  //                                      p[j]<j
  //                                      p[i]<i
  //                                      p[k]<k
  //                                      j<=p[k]
  //                                      ==> j<k
  //
  //                                      what about i-th and j-th node? what
  //                                      can being on the same m-th level tell
  //                                      us? there must be (m-1)-th nodes
  //                                      before it (can be all duplicates =>
  //                                      siblings)
  //
  //                                      m-1<=p[i]    root node req'd
  //                                      m-1<=p[j]       v
  //                                      (m+1+2)<=n<=(2*(m-1)+1+2) =>
  //                                        m+3<=n<=2m+1
  //                                              +additional ofs between k&j
  //
  //                                      m-1<=p[j]<j<k
  //                                      m-1<=p[i]<i   // tells us nothing
  //
  //                                      counter example?
  //
  //                                      k<i => p[k]<k<p[i]<i OR
  //                                             p[k]<p[i]<k<i OR
  //                                             p[i]<p[k]<k<i
  //                                         if k<p[i] => the parent of i-th
  //                                         node has a larger index then k =>
  //                                         p[k]<i => impossible IMPOSSIBLE to
  //                                         have k-th node to have i as the
  //                                         parent => impossible to have k-th
  //                                         node to have a larger depth than i
  //                                         (or i must have a depth larger than
  //                                         k) (invalidates the
  //                                         counter-hypothesis)
  //                                         if p[k]<p[i] => k-th node's parent
  //                                         can never be i-th node's parent =>
  //                                         k can never have a depth more than
  //                                         i
  //                                         if p[i]<p[k] => k-th node's
  //                                         grandparents can be the i-th node
  //                                         => k-th node must have a depth more
  //                                         than i???
  //                                              consider this, if i=n, p[i]=1,
  //                                              then p[2]=1, p[3]=2, p[4]=3,
  //                                              p[5]=4, p[k]=6
  //
  //
  //                                                1
  //                                               / \
  //                                              i   2
  //                                                   \
  //                                                    3
  //                                                     \
  //                                                      4
  //                                                       \
  //                                                        5
  //                                                         \
  //                                                          6
  //                                                           \
  //                                                            k
  //                                 k<i includes p[i]<p[k]<k<i => clearly k has
  //                                 more depth than i (placed last)
  //
  //                                 counter hypothesis is true => k<i does NOT
  //                                 guarantee k-th node to have a depth lower
  //                                 than i
  //
  //                                               k i
  //                                   1 2 3 4 5 6 7 8
  //                             p[x]    1 2 3 4 5 6 1
  //                             clearly o[x]<x

  // input assumption does not help with the aformentioned method
  //
  // suppose we have like a linear tree with each node along the main trunk have
  // a 1-depth leaf. hence, for loop over the while loop on parent-travelling is
  // like n(n+1)/2 => n^2 (quadratic)

  vll depth(n, 0);
  depth[0] = 1;

  // input assumption p[i]<i
  //

  vector<vll> c(n); // 0@

  II(i, n - 1) { c[p[i] - 1].PB(i + 1); }

  // this guarantees O(n) right???
  // YES since sum of each elements' lengths of indices = n-1

  II(i, n) {
    DBGLN(i);
    DBG_ITER(c[i]);
    II(j, c[i].size()) {
      // parent node i, child node c[i][j]
      depth[c[i][j]] = depth[i] + 1;
    }
  }

  // for (ll i = 1; i <= n; i++) {            // parent node i
  //   for (ll j = i - 1; (j < n - 1); j++) { // child node j
  //     if (p[j] == i) {
  //       depth[j + 1] = depth[i - 1] + 1;
  //     } else if (p[j] < i) {
  //       break;
  //       // remember, j is increasing, i stays same
  //       //      as j increases (p[j]<j) p[j] can result in p[j]>i
  //       //      no it doesnt help at all this is still O(n^2) then...
  //     }
  //
  //     // else if (p[j] > i) {
  //     //         break; // ensures O(n) since p[i] < i
  //     //       }
  //     //       i think its suppose to be j=i
  //     //          because i stays constant while j increases
  //   }
  // }

  // find max_depth
  vll true_max_depth(n, 0);

  for (ll i = 0; i < n; i++) {
    if (children[i] == 0) {
      true_max_depth[i] = depth[i];
    }
  }

  DD(i, n) {
    II(j, c[i].size()) {
      // parent node i, child node c[i][j]
      true_max_depth[i] = max(true_max_depth[i], true_max_depth[c[i][j]]);
    }
  }

  // for (ll i = n; i >= 1; i--) {            // parent node i
  //   for (ll j = i - 1; (j < n - 1); j++) { // child node j
  //     if (p[j] == i) {
  //       true_max_depth[i - 1] =
  //           max(true_max_depth[i - 1], true_max_depth[j + 1]);
  //     }
  //   }
  // }
  //
  // vll paths_remaining(children);
  //
  // for (ll i = 1; i < n; i++) {
  //   ll k = i;
  //   if (children[k] == 0) {
  //     // min_depth[k] = 1;
  //     max2_depth[k] = {1, 0};
  //
  //     do {
  //       pll prev = max2_depth[k];
  //       k = p[k - 1] - 1;
  //
  //       max2_depth[k].first = max(max2_depth[k].first, prev.first + 1);
  //       paths_remaining[k]--;
  //       if (children[k] >= 2 && paths_remaining[k] == 0) {
  //         // continue the loop
  //       } else {
  //         // stop and wait till all the previous paths have visited the
  //         merging
  //         // node
  //         break; // break the parent-skipping loop
  //       }
  //       // if (children[k] < 2) {
  //       //   max2_depth[k].first = max(max2_depth[k].first, prev.first + 1);
  //       //   // max2_depth in name but reality is just max2_depth only on
  //       //   // merging/branching node
  //       // } else { // merging/branching node AT k
  //       //
  //       //   // children of branching nodes contributes at most 1 max
  //       //
  //       //   vll possible_depths = {max2_depth[k].first,
  //       max2_depth[k].second,
  //       //                          prev.first + 1};
  //       //   sort(possible_depths.begin(), possible_depths.end());
  //       //   max2_depth[k].first = possible_depths[2];
  //       //   max2_depth[k].second = possible_depths[1];
  //
  //       // vll possible_depths = {
  //       //     prev.first + 1,
  //       //     prev.second + 1,
  //       //     max2_depth[k].first,
  //       //     max2_depth[k].second,
  //       // };
  //       // sort(possible_depths.begin(), possible_depths.end());
  //       // max2_depth[k].first = possible_depths[3];
  //       // max2_depth[k].second = possible_depths[2];
  //
  //       // if (prev.first + 1 > max2_depth[k].first) {
  //       //   max2_depth[k].second = max2_depth[k].first;
  //       //   max2_depth[k].first = prev.first + 1;
  //       // } else if (prev.second + 1 w) {
  //       // }
  //     } while (k != 0);
  //
  //     // ll prev;
  //     // while (p[k - 1] != 1) {
  //     //   prev = min_depth[k];
  //     //   k = p[k - 1] - 1; // 1@k = p[1@k]
  //     //   if (prev + 1 < min_depth[k]) {
  //     //     min_depth[k] = prev + 1;
  //     //   }
  //     // }
  //     // // too lazy to convert this to do-while loop
  //     // // p[k-1]==1 (the parent is the root node)
  //     // prev = min_depth[k]; // dont do it at initilization b/c it skips the
  //     // loop k = p[k - 1] - 1; if (prev + 1 < min_depth[k]) {
  //     //   min_depth[k] = prev + 1;
  //     // }
  //   }
  // }
  //
  // // another bandage .... ensures every children of a merging node is
  // travelled
  // // once
  //
  // // reset
  // for (ll i = 0; i < n; i++) {
  //   // ll k = p[i - 1] - 1; // 0@k is the parent of 0@i (remember p outputs
  //   1@) if (children[i] >= 2) {
  //     // vll possible_depths = {max2_depth[k].first, max2_depth[k].second,
  //     //                        max2_depth[i].first + 1};
  //     // DBGLN("===", k);
  //     // DBG_ITER(possible_depths);
  //     // sort(possible_depths.begin(), possible_depths.end());
  //     max2_depth[i].first = 0;
  //     max2_depth[i].second = 0;
  //   }
  // }

  // NOTE: EVEN ORDER MATTERS
  // we can use the input condition of 1<=p_i<i => i>p_i>=1
  // for (ll i = 1; i < n; i++) {
  for (ll i = n - 1; i > 0; i--) {
    ll k = p[i - 1] - 1; // 0@k is the parent of 0@i (remember p outputs 1@)
    if (children[k] >= 2) {
      // vll possible_depths = {max2_depth[k].first, max2_depth[k].second,
      //                        max2_depth[i].first + 1};
      // DBGLN("===", k + 1, i + 1, max2_depth[i].first + 1);
      // DBG_ITER(possible_depths);
      // sort(possible_depths.begin(), possible_depths.end());
      // DBG_ITER(possible_depths);
      vll possible_depths = {max2_depth[k].first, max2_depth[k].second,
                             true_max_depth[i] - depth[k]};
      DBGLN(k + 1, i + 1, true_max_depth[i], depth[i], depth[k]);
      DBG_ITER(possible_depths);
      sort(possible_depths.begin(), possible_depths.end());
      // smallest to largest

      max2_depth[k].first = possible_depths[2];
      max2_depth[k].second = possible_depths[1];
    }
  }

  ll guilds = n;

  II(k, n) {
    if (children[k] >= 2) { // merge nodes
      DBGLN(k + 1, max2_depth[k].second);
      // DBGLN(k + 1, children[k], min_depth[k] - 1);

      // DBGLN(k + 1, children[k], max2_depth[k].first - 1,
      //       max2_depth[k].second - 1);
      // guilds += min_depth[k] - 1;
      // remember: EXCLUDE at the level of the merging/branching node
      //
      // we want the 2nd max
      guilds += max2_depth[k].second; // - 1
    }
  }
  O(guilds);
}
