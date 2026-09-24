#include <bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef std::vector<ll> vll;
typedef std::deque<ll> dll;

const long long NEG = (long long)-4e18;

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

// rephrase: cost of permutation is in terms of LENGTH

// O.1: for a permutation to be sorted in ascending order => a[i] = i (for 1-indexed i)
// O.2: the min cost (ie the min length) is the first and last occurrence of a[i] != i
//  O.2.1: if it's not in ascending order, there's always two or more occurrence (ie at least a pair of mismatch)
// H.3: we can always greedily set all the numbers in the 0 to be in descending order (if # of 0 > 1)
//         suppose @i (s.t. a[i] = 0), we can let a[i]=i. but bc of 0, we can switch them up to be descending
//          => H.3 is true
//  C,3,1  a[i] != i includes when a[i] == 0 (when # of 0 > 1)
// O.4: if there's 1 zero outside of pre-defined out-of-order, that 1 zero can't be included...
//      preferably create two loops one for finding max/min of 0s and another for max/min of regular and we find the max range
//      only if # of 0s > 1

// O.5: if there's only 1 zero, it's not it always be ascending and proper, it is either must be in-order or out-order
//          determined by other elements.
//  O.5.1: out-order only when the MEX is not equal to the index of the single zero
//                         (ie the single missing #)
//              => the number mustve swapped with another regular (either L or R)
//              => if 1 zero, allow it to be part of either L or R (if only either is present, but both present => L-R range could be larger)

// redo everything

// zeroes == 1 is fine as long a regular mismatch occurs

// so.... zL,zR,rL,rR if three or all of them is all zero => 0
// else, exclude the 0s and find the min/max of them.
// but if 1 zero is present, check if the MEX is it => if so, exclude the zero; if nah, include the zero
//      ie if every other elements is the index of the zero

// per editorial, we can just check from left and from right and break the moment we find a mismatch
//      with 0s filled to the least optimal if # of it is > 1

void solve([[maybe_unused]] ll T)
{
    READ(n);

    ll zeroes = 0;
    // ll zLI = 0; // 1-index of the last 0
    // cost under 0 only
    ll zL = 0;
    ll zR = 0;
    // cost for regular
    ll rL = 0;
    ll rR = 0;

    vll a;
    INC(i, n)
    {
        ll ai;
        cin >> ai;
        a.push_back(ai);

        if (ai == 0)
        {
            zeroes++;
            // zLI = i + 1;
            if (zeroes == 1)
            {
                zL = i + 1;
            }
            else
            {
                zR = i + 1;
            }
        }
        else if (ai != i + 1)
        {
            if (rL == 0)
            {
                rL = i + 1;
            }
            else
            {
                rR = i + 1;
            }
        }
    }

    // include the single zero if the 1-index of it is not in the vector (ie the index has to be in the 0)
    //  regardless how many pre-defined mismatches (as long # of zeroes is 1; if >1, then greedily is possible)
    bool include_1zero = zeroes == 1 && find(a.begin(), a.end(), zL) != a.end();

    DBGLN(zL, zR, rL, rR);

    vll indices;
    if (rL != 0)
        indices.push_back(rL);
    if (rR != 0)
        indices.push_back(rR);
    if (zeroes >= 2 || include_1zero)
    { // dont add a single zero if two regular indices are present
        // do add the single if only one regular indices are present
        if (zL != 0)
            indices.push_back(zL);
        if (zR != 0)
            indices.push_back(zR);
    }

    if (indices.size() >= 2)
    {
        OUT(*max_element(indices.begin(), indices.end()) - *min_element(indices.begin(), indices.end()) + 1);
    }
    else
    {
        OUT(0);
    }

    // if (zeroes == 1)
    // {

    //     if (rL != 0 && r)
    //     {
    //         OUT(abs(zLI - rL) + 1);
    //     }
    //     else if (rR != 0)
    //     {
    //     }
    // }
    // else
    // {

    //     ll L, R;
    //     if ((zeroes > 1 && zL != 0) && rL != 0)
    //     {
    //         L = min(zL, rL);
    //     }
    //     else if (zeroes > 1 && zL != 0)
    //     {
    //         L = zL;
    //     }
    //     else if (rL != 0)
    //     {
    //         L = rL;
    //     }
    //     else
    //     {
    //         L = 0;
    //     }

    //     if (zeroes > 1 && zR != 0 && rR != 0)
    //     {
    //         R = min(zR, rR);
    //     }
    //     else if (zeroes > 1 && zR != 0)
    //     {
    //         R = zR;
    //     }
    //     else if (rR != 0)
    //     {
    //         R = rR;
    //     }
    //     else
    //     {
    //         R = 0;
    //     }

    //     if (L != 0 && R != 0)
    //     {
    //         OUT(R - L);
    //     }
    //     else
    //     {
    //         OUT(0);
    //     }
    // }
}

/*

2
7
1 2 3 4 5 6 7
7
1 0 3 2 5 4 7

0
5  <--- xxxx (getting 3)

*/