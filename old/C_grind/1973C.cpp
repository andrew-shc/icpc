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

// O(n) or O(nlogn)  (N<=10^5)

// O.1: max score possible is n/2-1 (n is even)

// H.2: is the max score always possible?
//         1 2 3 4 5 6
//         4 6 3 5 2 1
//         5 8 6 9 7 7  (max score reached)
//
//         1 2  6 5 4 3
//         4 3  6 1 5 2
//         5 5 12 6 9 5 (max score reached)
//
//         1 2 3 4  5 6
//         4 3 6 2  5 1
//         5 5 9 6 10 7
//    to reach max score, you only need to find m=n/2-1 maximums
//    we can actually find any m overlapping-triplets (w/ one non-overlap)
//    given these indices, the worst case triplets are is largest,smallest,2nd largest
//                  which can be counteracted with        smallest,largest,2nd smallest
//                                                              6,1,5
//                                                              1,6,2
//                                                              7 7 7 (the worst case => shift 1)
//        6 1  5 2 3 4
//        4 3  6 1 5 2
//       10 4 11 3 8 6
//        1 2  6  5  3 4
//        . .  6  1  5 .
//   is there a formal proof to this?

//      we can find the reciprocal q where ai = n+1 for all i
//          1 2 6 5 4 3
//          6 5 1 2 3 4
//          7 7 7 7 7 7
//          6 8 7 7 7 7
//          6 8 7 8 6 7

/*
            3 6 1 5 4 2
            4 1 6 2 3 5
            7 7 7 7 7 7
            7 8 7 6 7 7 (1 <-> 2)
            6 8 7 6 8 7 (3 <-> 4)
or
            712 2 7 7 7 (1 <-> 6)
            712 210 7 4 (2 <-> 5)

            if q is reciprocal to p, then each pair, (pi,qi) has a reciprocal pair where the value of pi and qi are swapped
                when the pairs are swapped, one side becomes larger and the other side becomes smaller

            and since n>=4, there must be at least m unique parts of the pair ((pi,qi) , (qi,pi)) allowing the creation
                of m maxes OR mins (but how do we guarantee maxes) or what happens when two maxes become adjacent???


            ~~~~ since there are m amount of maxes => every max can mutually exclusively s

*/

/*
refined strat

given a reciprocal permutation q

XDDX
XDDDDX
XDDDDDDX

within the D (so excluding the ends), we find the mins on the odd index (first part) and even index (second part)

given a part, if every min has a larger index on the other part => works. if not, next part must work

since if one part has an element thats the largest within the D-section (excluding the ends), that means the other part must not contain the largest

that means every element in the other part has a larger element on this part.

but, what if a part has two of the largest? that means the other part has two elements that can take swap with those two

so.. what if a part has the largest and the smallest? that means the other part must have a smaller element to pair with the largest (creating a max)
        BUT a larger element that swaps with the smallest (creating a min)


*/

// PER EDITORIAL: n/2-1 maximums is possible FOR ANY PERMUTATION
// first, locate the n
//    if n is on odd indices (such as the first position)
//      put all the largest-half q's on odd indices
//      put all the smallest-half q's on even indices
// recall the reciprocal permutation? that finds the equilibrium value first at n+1 for all i
//      now if we make the odd indices larger with largest-half, the even indices must *equally* get smaller with smallest-half
//          since indices can range from 1...n, but we guarantee top-half being n/2+1...n, we can always put the largest to the smallest
//              in a worst-case scenario resulting in a guarantee of all even values >=n+1 IF we put the largest to the smallest
//          the even indices that has values ranging from 1...n has the bottom-half 1...n/2
//              in a worst-case scenario we apply the largest available q-values to the smallest (n/2 worst case / remember, we always take n & n/2-1 numbers for the remaining) guaranteeing <=n
//  WLOG, n on even indices works also

void solve([[maybe_unused]] ll T)
{
    READ(n); // 4<=n is even
    READ_VLL(p, n);

    bool odd = (distance(p.begin(), max_element(p.begin(), p.end())) + 1) % 2;

    // extract the evens and the odds first
    vpll evens;
    vpll odds;
    INC(i, n)
    {
        if (i % 2 == 0)
        { // odd in 1-index
            odds.push_back({p[i], i});
        }
        else
        {
            evens.push_back({p[i], i});
        }
    }

    // sorting on pairs always compare first (and since permutation, itll never be equal and compare second)
    sort(evens.begin(), evens.end());
    sort(odds.begin(), odds.end());

    vll q(n, 0);

    if (odd)
    { // put largest element to the smallest on odd indices (even index for 0-index)
        INC(i, n / 2)
        {
            q[odds[i].second] = n - i; // n to n-n/2+1=n/2+1
        }
        INC(i, n / 2)
        {
            q[evens[i].second] = n / 2 - i; // n/2 to 1
        }
    }
    else
    { // put largest element to the smallest on even indices
        INC(i, n / 2)
        {
            q[odds[i].second] = n / 2 - i;
        }
        INC(i, n / 2)
        {
            q[evens[i].second] = n - i;
        }
    }

    DBLOCK
    {
        vll c(n, 0);
        INC(i, n)
        {
            c[i] = p[i] + q[i];
        }

        DBG_ITER(p);
        DBG_ITER(q);
        DBG_ITER(c);
    }

    OUT_ITER(q);
}