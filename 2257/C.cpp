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

// start: 18:11
//   end: 20:15

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
// because the root vertices is also counted, we basically want to find the
// minimal amount of camers over the entire tree (including single-children
// single-path trees)
//
// basically, we do not want to skip 2 adjacent edges with NO cameras..
//
//
// note: we output the ending vertex (away from the root) on edges w/ cameras
//
// best-case: n/2
//
// optimal realistic case:
//      - say a node v with c children node
//      - if node v has camera (to the edge that comes before it)
//          - c-1 children needs camera to uniquely determine it
//      - if node v does NOT have camera
//          - all c children needs it
//      - and continue alternating if single-child and recurse using this rule
//
//  notice, abstraction: we only care about the length between levels (and just
//  the NUMBER of children)
//
//
//  1-length: branch (cam?) - branch
//  2-length: branch (cam?) - single - branch
//  etc...
//
//  can we find the min. from the top or from the bottom or from both?
//
//  the only point of inefficiency is selecting which children node to be the 1
//  camera-less node WHEN the parent node is cam'd (the -1 part in c-1)
//      OR, choosing the single child node to be cam-less forcing the parent
//      node to be cam'd
//
//      to know whether a children is cam-less requires nonlocal knowledge
//      (parent knowledge) to prevent multiple child node to be cam-less (which
//      would be hard to do from a child's POV)
//          => let the decision on which child to be cam-less reside on the
//          parent node (parent of the branching)
//
//
//  keep a parent -> child mapping
//  and a
//      ~~~node -> (min cam if its cam'd, min cam if its de-cam'd)
//                      .first                  .second
//      do this isntead
//
//          node -> (# of cam's in config 1, # of cam's in config 2)
//                    .first                       .second
//
//  leaf node (l): (sets the config)
//      .first = 1
//      .second = 0
//
//  parent of a single leaf node (p[l]):
//      .first = 1
//      .second = 1
//
// p[p[l]]:
//      .first = 2
//      .second = 1
//            =    {1,0}
//            =    {1,1}
//            =    {2,1}
// p[p[p[l]]] =    {2,2}
// p[p[p[p[l]]]] = {3,2}
//
// p[p[p[p[p[l]]]]]] = {3, 3}
//
// 2 cases, {k,k} or {k, k-1}
//
// now say the parent of {3,3} is a parent of 3 child nodes with
//                   the config that's about to increase
//      {3,3} itself {x, }    {+1,=0}
//      {5,4}        { ,x}    {=0,+1}
//      {8,7}        { ,x} or {=0,+1}
//
//      if all are cam'd, then all child node goes as usual
//          all child node's are {+1,+1}
//
//          the parent strictly enforces NO cam on itself
//              and so {+0, +0}
//
//      if c-1 are cam'd, the child without camera will take the value where it
//          is not expected to increase in its entirety
//
//          b/c if c-1 has the OPTION to not be cam'd, it'll just take the
//          default option (and prefer the option or config with =0)
//
//          else, increase on both config {+1,+1}
//
//          the parent strictly enforces YES cam on itself
//
//          and so {+1,+1}
//
//
//      so we can compactify it as {+1,+0}
//                                   ^  ^
//                                   ^  parent YES cam on itself (c-1,1)
//                                   ^    c-1 same as below
//                                   ^    the 1, take the min config
//                                   ^      (apply standard rule may add +1)
//                                   ^ parent NO cam on itself (sum of all
//                                   the children's MINIMUM configs+1)
//
//          NOTICE: the decision on the branching node destroys most of the
//          configs/optimization on later child branches (but adds additional
//          config of its own)
//
//              so the branching node can be thought of as re-constructing the
//              decisions in a new way
//
//      IMPL: (would going from the root have an easier implementation?)
//
//          initialize vpll of nodes @{-1,-1}
//          mark leaf nodes with {1,0}
//          single-child parent traversal (UNTIL THE CHILD OF NEXT BRANCHING
//          NODE):
//              more more reliably: (towards the parent)
//                  if the current node is a branching node, just do @{+1,=0}
//
//~~~~
//              more reliably:
//                  if child is a branching node: {+1,=0}
//                  if child is just another single-child node:
//                      just the child of the child
//              ~~~~~ @{==,==} ? d{+1,=0} : d{=0,+1}
//
//
// is there a more elegant approach?
//      (i.e., simpler impl)
//
//  thereh as to be easier way... this is literally like two coloring graphs or
//  something
//
//
//  there's a total of n nodes
//      leaf node: 2 configs (arbitrarily)
//      branching node: 2 configs
//
//      branching to branching:
//          always starts with cam'd to whatever the length between the two
//          branching nodes
//          UNLESS, the start of this single-branch path is the 1 child (-1) w/o
//          the +1 cam requirement
//          UNLESS, the end of this single-branch path is the parent that
//              REQUIRES +1 cam (to enable the "c-1")
//
//      is the c-1 option always optimal
//          (worst case)
//          consider this: yes that 1 child node does not need a cam (-1 good?)
//              but requires the parent node to have a cam (+1 bad)
//                  => net benefit = 0
//
//          (best case?)
//          the parent node already requires a camera node and a child node
//          takes this opportunity (net = -1)
//              but the parent node requiring it requires two consideration:
//                  the length of the single-child path length AND
//                  whether the beginning of this path required a camera or not
//                  (DID NOT SAY FORCED TO HAVE NO CAMERA)
//
//      vpll dp[]???
//
//
//  more elegant concise observation???
//
// ~~~~~~~~~~~~~~~~~~~~~ MISREAD PROBLEM there's a separate vector m that flags
// which vertices has dams that the beaver might arrive to
//
// at most need m-1 cameras
//      (if m-1 camera shows no beaver => the beaver went to that one other
//      camera)
//
//  if 2 dams are in different branches, definitely need separate cameras for
//      them (up to m-1)
//  if a dam is a parent of some other dam, definitely need separate cameras (up
//      to m-1)
//          consider placing camera before the two dams (inclusively the parent)
//                  ==> (no info)
//          consider placing camera between the two dams (exclusively the
//                  parent) => (no info) we don't know if the beaver went to the
//                  earlier dam since the cam CAN ONLY SEE THE CURRENT EDGE
//          even on the parent (since the beaver could've just went to the child
//          one as a bypass)
//
//  always m-1???
//
//  consider this, 4 dams
//
//  we place a cam on the first and the third
//
//  if 1 hit, the beaver can still go to the second or stay at the first.... nvm
//
//!!!       confirmed by editorial
//!!!       editorial further mentions the need to exclude the root node's
//! camera (if a dam is at the root node) else just print one less of them
//

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n);
  IVLL(p, n - 1);
  I(m);
  IVLL(a, m);

  // O(m - 1);

  vll cams(a);
  ST(cams);
  cams.erase(cams.begin());

  // bool root_present = false;
  // II(i, m) {
  //   if (a[i] == 1) {
  //     root_present = true;
  //   } else {
  //     cams.PB(a[i]);
  //   }
  // }

  // if (!root_present) {
  //   // cams.pop_back();
  //   // actually, we want to pop first since if we place the camera too early
  //   we
  //   // don't know if it went to the parent one or the child one and by the
  //   // gaurantee of p[i] < i we just pick the single earliest element to be
  //   // removed (which includes root)
  // }

  cams.insert(cams.begin(), (ll)cams.size());
  OIT(cams);
  ;
}
