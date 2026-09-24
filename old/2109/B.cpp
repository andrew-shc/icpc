#include <bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using vll = std::vector<ll>;
using dll = std::deque<ll>;
using pll = std::pair<ll, ll>;
using vpll = std::vector<pll>;

const ll NEG = (long long)-4e18;
const ll MOD = 998244353;

#define INC(i, n) \
    for (ll i = 0; i < n; i++)

#define DEC(i, n) \
    for (ll i = n; i >= 0; i--)

#define OUT_ITER(a)                 \
    {                               \
        for (auto &el : a)          \
        {                           \
            std::cout << el << " "; \
        }                           \
        std::cout << std::endl;     \
    }

template <typename... Args>
void cout_vars(Args... args)
{
    ((std::cout << std::fixed << std::setprecision(10) << args << " "), ...) << std::endl;
}
#define OUT(...) \
    cout_vars(__VA_ARGS__)

#define READ_S(s) \
    string s;     \
    cin >> s;

#define READ_VLL(a, n)         \
    vll a;                     \
    for (ll i = 0; i < n; i++) \
    {                          \
        ll ai;                 \
        std::cin >> ai;        \
        a.push_back(ai);       \
    }

template <typename... Args>
void read_vars(Args &...args)
{
    (std::cin >> ... >> args);
}
#define READ(...)   \
    ll __VA_ARGS__; \
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

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// END MACROS ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

void solve(ll T);

int main()
{
    /////////////////////////////////////////////////////////////////////
    //// comment out the sync when working with interactive problems ////
    /////////////////////////////////////////////////////////////////////
    ios_base::sync_with_stdio(false);
    /////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////

    cin.tie(NULL);
    cout.tie(NULL);

    ll T = 1;

    cin >> T;

    ll t = T;
    while (t--)
    {
        solve(T - t);
    }

    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// START ACTUAL CODE ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

// start:
//   end:

// O.1: to minimize turns for Mouf, always optimally take the largest portion without the monster
//          since intuitively (can't prove this logically), the quicker the reduction
//          of the size of the grid, the less cuts Mouf has to do to reach 1x1 grid
// O.2: Fouad will optimally always move the to the center to minimize the portion Mouf can take
//          (think of it like extending the binary search sequence as much as possible)

// strat:
//      Mouf has 4 option, pick one largest (even if there's multiple largest => symmetric anyways)
//          (a-1)*m =>   a   x m
//          (n-a)*m => n-a+1 x m
//          n*(b-1) =>   n   x    b
//          n*(m-b) =>   n   x  m-b+1
//              except if any are 0s
//              when all are 0s => end (don't increment)
//              else (after picking) => increment
//      Fouad will update to (n//2 , m//2)
//              if n or m (or both) are odd, picking either the floor or the ceil changes nothing (symmetric)
// can this be done in a binary search way??? depends heavily on n,m and a,b position (possibly too many edge cases to consider)

// so only when n x m becomes 2x2 (or either the # of rows or columns is 2) and a,b is 1,1 => returns to 2x2????
//      im sorry am i capping???
//      if i pick (n-a)*m, which would be (2-1)*2 => reduce 2 by cutting row-wise so 2x2 becomes 1x2
//                             but i becomes 2x2???? don't we need the +1???
// SHOULD BE THE OPPOSITE

//          (a-1)*m => n-a+1 x m         (remove the earlier rows before a, keep the rows including a and after)
//          (n-a)*m =>   a   x m
//          n*(b-1) =>   n   x  m-b+1
//          n*(m-b) =>   n   x    b

// 2x2 grid becomes (by option 2) 1x2 resulting in a,b of 0,2
//      so when the floor is 0, stay at 1

// n represent # of rows as height, whereas a represents the x-position (the col...) so i flipped n,m and a,b (i am so braindead rn it seems)

//          (a-1)*n =>   n   x  m-a+1
//          (m-a)*n =>   n   x    a
//          m*(b-1) => n-b+1 x m
//          m*(n-b) =>   b   x m

//             a = m/2
//             b = n/2

// per input constraint and description, I WAS originally correct they did not flip a,b omfg (not in Cartesian)

// the test cases shows the number of rounds is generally higher when both plays optimally...

// if there's a distinct maximum that reduces max amount of grids, thats the optimal choice
//    but if there's multiple maximum... there seems to be a preference to choose which then...
//

// WA on 2: likely some edge cases... n,m starts at 2 minimally
//   consider 2,2 & 2,2
//   (2-1)*2 -> 2-2+1,2 == 1,2 => (1,1)

//    ..........
//    ..........
//    ..........
//    ..........
//    ..........
//    ....#.....
//    ..........
//    ..........
//    ..........
//    ..........

// ok maybe if they're both multiple maxes then there's some preference???

// equal maxxes only happens when both n==m and when n,m are both odds

// .....
// .....
// ..#..
// .....
// .....

// +1

// .....
// ..#..
// .....

// +1

// ...
// .#.
// ...

// +1

// .#.
// ...

// +1

// .#.

// +1

// #.

// +1

// #

// 5 5 3 3
// 6
// =6

// likely some edge cases where equal maxxes and picking either yields different numbers of turns
// and how would we achieve that??
// if... there are equal maxes orthogonally/adjacent-wise => it just means that side has odd #s and symmetric
// there can't be equal maxes diagonally (exclusively)????
//      => or else all four partitions are equal

/*

.....
..#..
-----
-----

..#..
-----

..#--

.#-

#-

#

or...

...--
..#--
...--
...--

...
.#.
---
---

.#.
---

.#-

#-

#

so...

4 5 2 3
5

???

*/

// another MAJOR OBSERVATION:
//      cutting along horizontal vs along the vertical are INDEPENDENT

// another thing, after the initial cut (we take the smallest), its just log2 after
//  let's a row is 7 -> 3 (take the smaller partition always) -> 2 -> 1
//      which is just ceil(log2(7)) operations (ceiling because any extra row within the last domain partition of the last integer in log2 gets absorbed in the operations)
//      8 -> 4 (take the smaller) -> 2 (take the smaller) -> 1
//  9 -> 5 -> 3 -> 2 -> 1

ll g(ll x)
{
    return (ll)ceil(log2(x));
}

void solve([[maybe_unused]] ll T)
{
    READ(n, m, a, b);

    ll ops = 1 + min(
                     g(min(a, n - a + 1)) + g(m),
                     g(n) + g(min(b, m - b + 1)));
    OUT(ops);

    // ll cnt = 0;
    // while (true)
    // {
    //     map<ll, pll> choices;
    //     choices[(a - 1) * m] = make_pair(n - a + 1, m);
    //     choices[(n - a) * m] = make_pair(a, m);
    //     choices[n * (b - 1)] = make_pair(n, m - b + 1);
    //     choices[n * (m - b)] = make_pair(n, b);

    //     //          (a-1)*m =>   a   x m
    //     //  (n-a)*m => n-a+1 x m
    //     //  n*(b-1) =>   n   x    b
    //     //  n*(m-b) =>   n   x  m-b+1

    //     //          (a-1)*m => n-a+1 x m         (remove the earlier rows before a, keep the rows including a and after)
    //     //          (n-a)*m =>   a   x m
    //     //          n*(b-1) =>   n   x  m-b+1
    //     //          n*(m-b) =>   n   x    b

    //     // OUT(
    //     //     (a - 1) * m,
    //     //     n * (b - 1),
    //     //     (n - a) * m,
    //     //     n * (m - b), n, m, a, b);

    //     if (choices.rbegin()->first != 0)
    //     {
    //         tie(n, m) = choices.rbegin()->second;
    //         DBGLN("==", n, m);

    //         // this should be a ceil actually
    //         //   eliminating max and makes sense when either n or m is odd we take the center and if even just take the earlier one
    //         //      (like flooring to an earlier, and that's what i sort of mean by flooring, as in for even there's symmetric choice and
    //         //      we just choose the earlier one, but for odds, always center)
    //         a = (n + 1) / 2;
    //         b = (m + 1) / 2;
    //         cnt++;
    //     }
    //     else
    //     {
    //         // no choice of operations reduce any more (we're at the smallest 1x1 grid now)
    //         break;
    //     }
    // }

    // OUT(cnt);
}

/*

....
.#..
----
----

.#..     .#--
----  or ..--

         #.
.#--  or --

#-    or #-

\_ same _/
    ??

4 4 2 2
4


....-----        .........
....-----        .........
...#-----        ...#.....
....-----   or   ---------
....-----        ---------
....-----        ---------
....-----        ---------
....-----        ---------

....        .....----
....        ....#----
....        .....----
.#..   or
----
----
----
----

....        ...--
.#..   or   ..#--
----        ...--
----

.#..        ..-
----   or   .#-
            ..-

.#--        .-
       or   #-
            .-

#-          .
       or   #
            -

#           #
       or   -


x           #
       or

8 9 3 4

// an observation: if Fouad is on an even location, the produced values


according to Claude, the only case this greedy doesn't always work is on the initial round
where the Fouad can be at any position....


consider the following

.....#.....
...........
...........
...........
...........
...........
...........
...........
...........
...........


vs.

.....#.....  or  .....#-----
-----------      ......-----

-----#.....  or  ..#---
                 ...---

     ..#---  or  .#.
                 ---

     .#-     or  .#-

     #-      or  #-

     #       or  #

*/