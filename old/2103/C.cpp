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

// P.1: order matters when segmenting arrays into 3 parts
//      P.1.1: order doesn't matter within each 3-part segmented array

// on paper

// back here

// H.5: if # of +'s > half of # of -'s => always works
//        ++----------- => works
//        -----------++ => works
//          hypothesis wrong
//        --+++---
// RECALL, a MEDIAN of an array is the HALF SMALLEST element in EACH partition
// O.6: this makes observation cleaner, we don't need to find how far each +'s are from each other
//          and if there's a fine continuous trade-off relationship if there's more +'s within each group of +'s

// strat: mix of O.6 and on-paper observations
//  for med(2 <=k's) <= k to work, we need to find at least two partition with 2<=ks
//  we can find 2 +'s in the first 4

// per editorial

// what we have previous observed:
//      the idea of prefix sum and assigning -1 to >k and +1 for <=k (on paper at least)
//                  (prefix sum idea went no where)
// additional observation from the editorial to build the final road: (for case 1&2)
//      PREFIX SUM p, whenever pi>=0, we know thats a valid prefix-subarray
//      MAX SUFFIX PREFIX (SUM) msp, whenever msp{i+1}>=pi, we know THERE EXISTS a prefix sum THAT WORKS (since it means there's prefix sum higher than the current)
//          KEY OBSERVATION: USING MAX and COMPARATOR as an EXISTENCE OPERATION (we don't care where it is exactly since we are only running the suffix part excluding the last element)

void solve([[maybe_unused]] ll T)
{
    READ(n, k);
    READ_VLL(a, n);

    if (n <= 4)
    { // n == 3,4
        ll cnt = 0;
        INC(i, n)
        {
            if (a[i] <= k)
            {
                cnt++;
            }
        }

        if (cnt < 2)
        {
            OUT("NO");
        }
        else
        {
            OUT("YES");
        }
        return;
    }

    INC(jjj, 2)
    { // do this twice
        ll lengthL = 0;
        ll lengthR = 0;
        // ~~~~~~~~~~~~we need the -1 to prevent the branches at the end from running when there are no more elements (but we
        // ~~~~~~~~~~~~~~~~~~default delta to 0 => default to running the branches)
        // actually, if delta is 0 and a is already empty => lengthL,lengthR is 0 => erase on .begin() to .begin() (or .end()) doesnt erase anything
        ll deltaL = 0; // ~~~~ -1;
        ll deltaR = 0; // ~~~~ -1;

        INC(i, a.size())
        {
            if (a[i] <= k)
            { // T (works)
                deltaL++;
            }
            else // ~~~~~~ if (i > 0)
            {    // ~~~~~~ dont -1 on i==0 per the comment on the deltaL,deltaR
                deltaL--;
            }
            lengthL++;

            if (deltaL == 0) // we dont want >= 0; to best support the guarantee, maximize the size
            //      + + - - + - - - - - (partition by + + - - and + and ... is fine)
            //      + + - - - - - - - - (partition by + + - - and ... => NO, we want + and + and ....)
            //      + + - - + ......... (partition by + and + and .... works)
            //      + - - + - - - - - - (partition by + - and - + and .....)
            //          => special case, if only a single +, extend it as much as it can
            //                           if there's two +'s, just take the first (so we can greedily partition them later)
            //          => if the first 4 element has 2 +'s => works
            //                  (we literally dont care any other cases since this is 3 -partition, not some required n-partition)
            //                   ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
            // consider again
            //      - - - - - - + + + + + + + - - - - - -
            //          => if the +'s > (-'s / 2) => works??????
            //      - - + + + - - - - - (partition - - + + and + and - - - .....)
            //      - - + + - + - - - - (becomes - - + + and - + and - - - -)
            //      - - + + + - - - - - (partition - - + + and +)
            //     => actually, if the delta goes from 1 to 2, return to the previous length (from top)
            //                  if the delta goes from -1 to 0, return immediately (from below)
            //          funky ahhhh cases
            //      also when + - +  (we dont want to be too greedy in what we take)
            //      - + - - - - - - - - - - - - - + -
            //      + - - + - - - - - - - - - - - - -
            //      - + - - + - - ...................
            //      + - + - - ..........
            //      + - - + -
            //      + - - - +
            //      + - - +
            //      + - + - ............ (analyze differently when there are n=3,4 / the way it works is so different)
            {
                break;
            }
            else if (deltaL == 2)
            {
                lengthL--;
                break;
            }
        }
        // // if the delta is still positive at the end => just take the left most one
        // //      to fix the issue when there are more <= k then >k (i.e., a surplus of <= k's)
        // //      which we want to conserve the partition
        // if (deltaL > 0)
        // {
        //     lengthL = 1;
        // }

        DEC(i, a.size() - 1)
        {
            if (a[i] <= k)
            { // T (works)
                deltaR++;
            }
            else // ~~~~~~if (i < a.size() - 1)
            {    //  ~~~~~~ dont -1 on i==-1 per the comment on the deltaL,deltaR
                deltaR--;
            }
            lengthR++;

            if (deltaR == 0)
            {
                break;
            }
            else if (deltaR == 2)
            {
                lengthR--;
                break;
            }
        }
        // all of the following erases is linear operations (so like a total of O(2n))

        if (deltaL >= 0 && deltaR >= 0)
        {
            // doesnt matter if they're the same length
            // but always pick the one that's is strictly shorter

            if (lengthL < lengthR)
            { // remove first lengthL elements
                a.erase(a.begin(), a.begin() + lengthL);
            }
            else
            { // remove lengthR last elements
                a.erase(a.end() - lengthR, a.end());
            }
        }
        else if (deltaL >= 0)
        {
            a.erase(a.begin(), a.begin() + lengthL);
        }
        else if (deltaR >= 0)
        {
            a.erase(a.end() - lengthR, a.end());
        }
        else
        {
            // neither deltas are positive (no groups have a median <= k)
            // on the 2nd run => no 2 groups have a median <= k
            // OR
            // the 1st partition took the entire array (on the 2nd run)
            OUT("NO");
            return;
        }
    }
    if (a.size() > 0)
    {
        OUT("YES");
    }
    else
    { // exactly 2 groups *barely* have positive delta (but we want 3 partition)
        OUT("NO");
    }
}

/*
3     500000000
1000 1000000000 1000

*/