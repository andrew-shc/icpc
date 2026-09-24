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

// O.1: cape worn LEFT @ j => means j is visible anywhere AT or RIGHT of j
//      cape worn RIGHT @ j => means j is visible anywhere AT or LEFT of j
//          ===> LEFT -> AT/RIGHT; RIGHT -> AT/LEFT
// O.2: at each position, the position at the wizard itself is always visible regardless LEFT/RIGHT (reflexive)
// O.3: there can be at most 2*n arrangements
// O.4: a@j=n => 2 arrangements; a@j=n-1 => 2(n-1) arrangements....; a@j=n-2 => 2(n-1)(n-2)
//              (i think it over counts: pick 1 then pick 2 is same as pick 2  then pick 1 => order doesn't matter) nCr? permutation?
//              has to be nCr not nPr
//      O.4.1: a@j=k => 2*[(n-1)C(k-1)]
//                  2 always available (reflexive property)
//                  arrangement only on n-1 remaining positions and visibilities
//                  arrangement represents # of cloaks worn away or towards @ j
// Q.5: but obviously, there are other positions we have to consider...

// ~~~~~~~~~~~~~~~~~~~~~~~ this is like the possibilities of the cloak being turned L/R, but the amount of cloak facing at @j is *exact*
//                      ~~ the question must what are all the possible positions the cloaks facing away can be placed
// O.4: if there's an element a@j=n => 1 arrangement @ each position *except* at j => arrangement of *at most* 2 (overall) @ j
//      O.4.1: a@j=k => 1 arrangement @ each position *except* at j and n-k other positions => arrangement of *at most* 2^(n-k+1) (overall) @ j

// per editorial

// MAJOR OBSERVATION: invariance in the # of views as you go across the list ---->
//          as you increment by one from i to i+1, the state of visbilities on wizards before i and after i+1 don't matter
//          ==> we can just focus on the present arrangement of cape in between i and i+1
// on top of editorial, you can only have 2 arrangements when all 0s (all values dont change)

// +1 +1 => (suggests L L L)

// we also have to ensure the absolute number is correct

// another observation based on editorial: LL RR cant share the middle (ie 3 2 3 cant work)

void solve([[maybe_unused]] ll T)
{
    READ(n);
    READ_VLL(a, n);

    if (n == 1)
    {
        if (a[0] == 1)
        {
            OUT(2); // L or R
        }
        else
        {
            OUT(0);
        }
        return;
    }

    // ll arrangements = 2;
    // ll visibleIL = 1; // from i=0 where the initial arrangement is L
    // ll visibleIR = 1; // from i=0 where the initial arrangement is R
    ll visibilities = 1;
    ll zeroes = 0;
    // bool flip = false;
    bool initial = true; // initial 0-zone
    bool r_r = false;
    bool l_l = false;

    INC(i, n - 1)
    {
        DBGLN(visibilities);
        if (abs(a[i] - a[i + 1]) == 1)
        {
            // arrangements = 1;

            if (a[i + 1] - a[i] == -1)
            { // R,[R]
                r_r = true;
                l_l = false;
                DBGLN("RR", zeroes, initial);
                visibilities++; // R R itself always bring one
                if (initial)
                {
                    if (zeroes % 2 == 1)
                    { // always starts with L and ends with R
                        visibilities += zeroes / 2 + 1;
                    }
                    else
                    {                               // always starts with R and ends with R
                        visibilities += zeroes / 2; // we do not care about the first element
                    }
                }
                else
                {
                    if (zeroes % 2 == 1)
                    { // always starts with L and ends with R
                        visibilities += zeroes / 2 + 1;
                    }
                    else
                    {                               // always starts with R and ends with R
                        visibilities += zeroes / 2; // the previous R R wouldve been included already
                    }
                }

                // (..? L) L R L R L R R
                // (..? R) R L R L R R
            }
            else
            { // L,[L]
                r_r = false;
                l_l = true;
                DBGLN("LL", zeroes, initial);
                if (initial)
                {
                    if (zeroes % 2 == 1)
                    {                               // always starts with L and ends with R
                        visibilities += zeroes / 2; // we do not care about the first element
                    }
                    else
                    { // always starts with R and ends with L
                        visibilities += zeroes / 2;
                    }
                }
                else
                {
                    if (zeroes % 2 == 1)
                    {                               // always starts with L and ends with R
                        visibilities += zeroes / 2; // the previous R R wouldve been included already
                    }
                    else
                    { // always starts with R and ends with L
                        visibilities += zeroes / 2;
                    }
                }

                // (..? L) L R L R L R L L
                // (..? R) R L R L R L L
            }

            initial = false;
            zeroes = 0;
        }
        else if (abs(a[i] - a[i + 1]) > 1)
        {
            DBGLN("XXXX >1");
            OUT(0);
            return;
        }
        else if (a[i] == a[i + 1])
        {
            DBGLN("LR|RL");
            // abs diff = 0
            zeroes++;
        }

        if (i < n - 2 && abs(a[i] - a[i + 1]) == 1 && abs(a[i + 1] - a[i + 2]) == 1 && ((a[i] - a[i + 1]) != (a[i + 1] - a[i + 2])))
        { // you just cant flip, it needs to be buffered by 0s (same values)
            DBGLN("XXXX FLIPS");
            OUT(0);
            return;
        }

        // if (a[i] - a[i + 1] == 1)
        // { // L,[L]
        //   // visible;
        // }
        // else if (a[i] - a[i + 1] == -1)
        // { // R,[R]
        //     visibleIL++;
        //     visibleIR++;
        // }
        // else if (a[i] - a[i + 1] == 0)
        // { // L,R or R,L specifically L,R ... too many possibilities
        //     // visible--;

        //     if (!flip)
        //     {
        //         // if initial is L R L R L R L|R
        //         visibleIL++;
        //     }
        //     else
        //     {
        //         // if initial is R L R L R L L|R
        //         visibleIR++; // offset one position
        //     }
        //     flip = !flip;
        // }
    }

    // if the 0s continued to the end
    // ..... (..? R) R L R L R L R L
    // ..... (..? L) L R L R L R L R
    // ..... (..? R) R L R L R L R
    // ..... (..? L) L R L R L R L

    // we do not care if its initial or not: if it is, we dont care about the first element; if not? handled by other cases
    //      since we assumed they wouldnt be count towards the zeroes then
    DBGLN("~~~~~~~~", zeroes, r_r, l_l, a[0]);
    if (zeroes % 2 == 0)
    { // each pair has an R
        if (!r_r && !l_l)
        { // assuming there's always at least two elements and all 0s
            if (a[0] == visibilities + zeroes / 2)
            {
                OUT(2);
            }
            else
            {
                OUT(0);
            }
            return;
        }
        else
        {
            visibilities += zeroes / 2;
        }
    }
    else
    {
        if (r_r)
        { // last non zero is R R
            visibilities += zeroes / 2;
        }
        else if (l_l)
        { // last non-zero is L L
            visibilities += zeroes / 2 + 1;
        }
        else
        { // zeroes/2 to zeroes/2+1 both work suggesting never hit a R R or L L suggesting all 0s meaning arrangement of 2
            if (a[0] == visibilities + zeroes / 2 || a[0] == visibilities + zeroes / 2 + 1)
            {
                OUT(2);
                return;
            }
            else
            {
                OUT(0);
                return;
            }
        }
    }

    // for not all 0s
    DBGLN("+++++++++++=", visibilities);
    if (visibilities == a[0])
    {
        OUT(1);
        return;
    }
    else
    {
        OUT(0);
        return;
    }

    // DBGLN(absolute, a[n - 1]);
    // if (absolute == a[n - 1])
    // { // valid
    //     OUT(arrangements);
    // }
    // else
    // {
    //     OUT(0);
    // }
}