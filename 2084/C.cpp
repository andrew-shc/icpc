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

// P.1: a & b are permutation-equivariant
//      P.1.1: a & b are equivariantly unordered
//              OUTPUT cares about order => ORDERED
// P.2: a,b are BOTH permutation of length n

// O.1: pick two indices i,j *about center* does nothing <=> nop
// O.2: for a,b to be reverses of each other, ai=b{n+1-i} => a{n+1-i}=bi
//              => ai,bi <-> b{n+1-i},a{n+1-i} (criss-cross pattern)
//      O.2.1: ai != bi (since a,b are permutation and must satisfy a unique CRISS-CROSS PATTERN)
//          O.2.1.2: criss-cross patterns come in 2 indices (i.e., n/2 patterns (excluding 1 if odd))
//      O.2.2: if n is odd, ONE ai==bi MUST exist (the center pivot)
// H.3: as long we identify n//2 criss-cross patterns +1 straight pattern (if odd)
//              => we can do it within n ops (whether within n ops is just going to skip, trust the intuition)
//      if you take a side of the criss cross box pattern, you can always swap it to ANY position along the array
//          and we can choose THE position that makes the criss-cross patern fit the reverse constraint
//      since if there's one side of a pattern that's off, there's another side of another pattern that's off => always works
//          since at the end, there will be a minimum of 2 places wrong, and with a single swap everything fixes itself
//      if the condition is satisfied, it is always possible within n ops
//          since for each first half of index, if a left side of criss-cross is checked but its right side happens again on the first half, swap it with another criss-cross
//              on the exact reverse-correct opposite half
//          and some eyeballing, this should also work on the latter half

// strat:
//      HOW DO WE IDENTIFY CROSS PATTERNS LINEARLY OR NLOGN?
//      REMEMBER, A & B ARE PERMUTATIONS
//      ok we have to output the operations themselves
//      WE HAVE TO OUTPUT THE OPS

// ops-aware strat
//      iterate over criss crosses => record (a,b) within ordered set O(logn)
//      if (b,a) is in the set found O(logn) (duplicate box) => swap with edge on n+1-i (where i is the previous box's index)
//      if (b,a) is on the set found O(logn)
// ops-aware strat (II)
//      for the exclusive first half => record all the second duplicate edges (n/4)
//      for the exclusive second half => record all the first duplicate edges (n/4)
//      then, we know there's same amount of duplicates and swap them across the center (at most <n/4)
//      at the later half
//          if an element is out of order compared, get p[2nd] -> p[reverse 1st]
//              dont care where the swapped element goes (we guarantee 2nd and reverse 1st are all on the later half)
//          next element, in-order? skip
//          next element, out-of-order? we guarantee 2nd<reverse 1st, swap those two again
//      originally thought about keeping track of path swap (but thats WAY TOO COMPLICATED AND UNNECESSARY)

/*
ops-aware strat (refined)
1. validate if its possible: O(n)
2. if odd, swap the straight pattern to middle: O(1), +1 ops
3. iterate over first half (exclusive), find duplicates: O(n/2)
4. iterate over the second half (exclusive), find duplicates: O(n/2)
5. swap the duplicates (guarantee same amount of duplicates across the center): +n/4 ops
6. iterate over first half (excl): if p[reverse 1st].first != p[index of p[1st].second].first
        swap reverse 1st with index of p[1st].second (how would you find the index of p[1st].second?)

ok there's a better way

iterate along the array linearly on the first half
    if the x-box is new/unique => RECORD its index
    if the x-box is duplicate => mark it
iterate along the array linearly on the second half (exclusive) same direction
    if p[p[i].second].second != p[i].first ()

ok there's an EVEN better way

given the current array,

give a sorted array where we construct a properly reversed a,b FROM SCRATCH
    BY BIPARTITE MATCHING, there would be AT MOST N/2 operations

WE MATCH the indices from the messy to the constructed version
    will be ordered on .first (array a) for FIRST HALF, then we construct the SECOND HALF by doing DOUBLE FLIP
        reverse order-wise and reverse pair-wise

META-OBSERVATION: THIS CONSTRUCTED VERSION IS PERMUTATION ORDERED ON .FIRST (FIRST HALF) AND ON .SECOND (SECOND HALF) / reversed

THEN, ON the original (FIRST HALF):
    if original[i].first != i:
        swap i and original[i].first

=> FIRST HALF's .first is same as the constructed version
    SECOND HALF's .second is unordered

    SECOND HALF's .second should be the same as the reverse permutation as the constructed version

    // if .first == .first:
    //     skip
    // if .first != .first:
    //     swap .first


    doesnt work on odd with arbitrary straight pattern
    MAJOR OBSERVATION: THE ANSWER JUST REQUIRES THE INDEX, NOT THE VALUE ITSELF
        the levels of requirements from an answer
            1. YES/NO (is it possible) (already done, prob wouldve been an A/B problem) (existence)
            2. # of operations (we dont care about out the order) (count-aware)
            3. LIST of operations each containing the indices (index-aware)
            4. somehow requireing the output of the values (value-aware)
        SO TECHNICALLY, IF WE HAVE A STRAIGHT PATTERN ON ODD N, WE JUST LET THE STRAIGHT PATH CONTAIN THE n/2+1
            (and have it separately operated first and change the values)
            now, we can assume the values must be in permutation format


    SO on the 2nd half
        if original[i].second != n-i:
            swap n-i and original[i].second


if p[i].first == p[n-1-i].second && p[i].second == p[i].first:
    continue (no swap needed)
else: (i am probably missing an observation here, an observation where as long they're out of order, there's an easy way to get the ops)
            THE HARD PART, WE NEED TO FIND THE INDEX OF THESE OPS
OUT()


*/

//  pair up a,b
//  order on a
//  iterate on pairs, get a, find the associated b, index b's value on the vpll (indexed on a), and check if a's corresponding b corresponds to the old a

/*
ops-aware strat (refined II)
1. pre-condition check
2. if n%2 is odd, swap the index of the straight pattern with center index
        2.1: if straight pattern's value is not n/2+1, find all instance of n/2+1 and swap values

// now, straight pattern is @ center and has the value of n/2+1 (construction-safe)

3. ON FIRST HALF i=0..n/2:
    if original[i].first != i:
        swap @i with @(index of original[i].first == i)
        OUT(i, index of original[i].first == i)
4. ON SECOND HALF i=ceil(n/2)..n-1:
    if original[i].second != n-i:
        swap @i and @(index of original[i].second == n-i)
        OUT(i, index of original[i].second == n-i)

// 2-pointer??? wtf is this

// 1400 constructive impl greedy ds (obviously missing a key observation)

// u cant skip the paths...... maybe with this new construction idea we can re-integrate the path idea

n=9
1 2 4 6 9 7 3 5 8

1 2 3 4 5 6 7 8 9

3<-4 (3, 7)
4<-  ()

hold up..........

let's say we get 4, we swap 4 with 6, then swap 6 with 7, then swap 7 with 3, continue
1 2 3 4 9 6 7 5 8

then, swap 9 with 8, swap 8 with 5

not that hard. gotta play the cases more (as if i have to try playing around with more cases at every possible idea)
1 2 3 4 5 6 7 8 9

1 2 3 4 x 6 7 8 9
4 3 2 1   9 8 7 6

wtf

ok forget about this construction-aware. now we played with enough cases on the path idea, it should be simple

lets just say we swap p[n-1]

wtf is this question and 1400???????????

the idea of needing to keep track of the indices........



*/

// per editorial

// as you iterate along the first half over i. then, ensure @(index of k s.t. p[k].first == p[i].second) is at n+1-i
//      this ensures any duplicate edges of the x-boxes are placed at n+1-i
//      and if the duplicate edges are already there, then leave it there
//          => abstracts the details of duplicates away
//      ORIGINALLY, i thought of swapping n+1-i with i itself if duplicate
//          but we can do it better by PINNING the current i and just find wherever its other pair to the correct spot
//              since if we're already at i, swapping the element itself with anything else doesn't really matter (what matter is itself w.r.t. to its pair)
//              like for the first half *incrementally* (incrementally to implicitly remove the duplicates out)
//          ensuring all previous j<i (and n+1-i<n+1-j) are satisfied with the order
//      ORIGINALLY, thought finding the index k would be hard esp we have to update at every swaps
//          but given an index array (i.e., inverse mapping where we want a value and get the index) can just be equally swapped
//          (call this mapping m)

// impl strat
// first if n is odd, identify the straight pattern, swap it with whatever lies at the center (n+1)/2
// at each pairs
//      assign the mapping m[p[i].first] = i
// at each pairs
//      always replace the p[m[p[i].second]] with p[n+1-i] (or n-i for 0-index)
//      swap the value
//      and swap the mapping with m[x] <-> m[y]
//      OUT(m[p[i].second] with n+1-i)

/*
SUMMARY:
First problem worked where the output is to provide the index values for each operation
-> notice the invariance that as we progress the first half (exclusive)
        we don't care with the pre-existing order (subject to the fixing of the initial convention)
        and force the later half to follow the first half's convention's order
            this is done by swapping the expected location of position of the b[i]'s in array a to n+1-i (1-ind)
        (instead of the original idea of swapping the current with the expected, which creates complex cycles and traversals)
            TIPS: WHEN SWAPPING INDEX, IT IS NOT AS DIRECT AS YOU THINK
                IT CAN BE OPERATION THAT DOES NOT INCLUDE THE CURRENT INDEX i LIKE IN THIS PROBLEM

& got stuck contemplating on adding the inverse mapping m (JUST DO IT NEXT TIME)
& swap() function helped a lot
*/

void solve([[maybe_unused]] ll T)
{
    READ(n);
    READ_VLL(a, n);
    READ_VLL(b, n);

    // 1-indexed
    vll m(n + 1, 0); // mapping between value to position
    INC(i, n)
    {
        m[a[i]] = i;
    }

    // operation indices
    vll ops1;
    vll ops2;

    ll straight_ind = -1;
    INC(i, n)
    {
        if (a[i] == b[i])
        { // discovered a straight pattern
            if (n % 2 == 0 || straight_ind != -1)
            { // not possible if n is even or we already have a straight pattern
                OUT(-1);
                return;
            }
            straight_ind = i;
        }
        else if (b[m[b[i]]] != a[i])
        { // discovered non x-box pattern
            OUT(-1);
            return;
        }
    }

    // pre-condition checked, now find the ops
    // given the pre-condition check, every pair has another pair paired in a reversed way
    // which requires at least one to be a[i]==b[i] when n is odd
    if (n % 2 == 1 && (straight_ind + 1 != (n + 1) / 2))
    { // it is possible the straight_ind is right on the center
        ops1.push_back(straight_ind + 1);
        ops2.push_back((n + 1) / 2);
        swap(a[straight_ind], a[(n + 1) / 2 - 1]);
        swap(b[straight_ind], b[(n + 1) / 2 - 1]);
        swap(m[a[straight_ind]], m[a[(n + 1) / 2 - 1]]);
    }

    INC(i, n / 2)
    {
        // note: my original idea wouldve swapped i<->j
        // but easier way is to do n+1-i <-> j regardless
        ll k = n - 1 - i; // 0-index
        ll j = m[b[i]];
        if (k == j)
        { // per output requirement, no repeated indices
            continue;
        }
        ops1.push_back(k + 1); // output in 1-index
        ops2.push_back(j + 1);

        swap(a[k], a[j]);
        swap(b[k], b[j]);
        swap(m[a[k]], m[a[j]]);
    }

    OUT(ops1.size());
    INC(i, ops1.size())
    {
        OUT(ops1[i], ops2[i]);
    }

    // ll straights = 0;
    // ll straight_ind = 0;
    // // vpll p;
    // set
    // vll m;
    // vll ops;
    // INC(i, n)
    // {
    //     p.push_back({a[i], b[i]});
    //     if (a[i] == b[i])
    //     {
    //         straights++;
    //         straight_ind = i;
    //     }
    // }

    // if (n % 2 == 0 && straights == 0)
    // {
    //     // pass
    // }
    // else if ((n % 2 == 1 && straights == 1))
    // {
    //     ops.push_back(straight_ind);
    //     ops.push_back(0);

    //     pll temp = p[straight_ind];
    //     p[straight_ind] = p[0];
    //     p[0] = temp;
    // }
    // else
    // {
    //     OUT(-1);
    //     return;
    // }

    // vpll p;
    // INC(i, n)
    // {
    //     p.push_back({a[i], b[i]});
    // }

    // // sort(p.begin(), p.end()); // ascending on first, p[i].first == i

    // ll criss_crosses = 0;
    // ll straights = 0;
    // vpll ops;

    // for (ll i = 0; i < p.size(); i++)
    // {
    //     if (p[p[i].second].second == i)
    //     { // match criss cross pattern
    //         criss_crosses++;
    //         p.erase(p.begin() + i, p.begin() + i + 1);
    //         // somewhere future guaranteed by the criss cross pattern from the branching
    //         p.erase(p.begin() + p[i].second, p.begin() + p[i].second + 1);
    //         i--;
    //     }
    //     else if (p[i].first == p[i].second)
    //     {
    //         straights++;
    //     }
    // }

    // if (n % 2 == 1 && (criss_crosses == n / 2 && straights == 1))
    // {
    //     OUT(ops.size());
    //     INC(i, ops.size())
    //     {
    //         OUT(ops[i].first, ops[i].second);
    //     }
    // }
    // else if (n % 2 == 0 && (criss_crosses == n / 2 && straights == 0))
    // {
    //     OUT(ops.size());
    //     INC(i, ops.size())
    //     {
    //         OUT(ops[i].first, ops[i].second);
    //     }
    // }
    // else
    // {
    //     OUT(-1);
    // }
}