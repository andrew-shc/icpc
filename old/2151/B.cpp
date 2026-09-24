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

// recall, final answer should be what cells (the indices of the cells that) are black

// O.1: given 1 op B within first i cmds, every following operations will be shifted by next available white cells (and fill the last one)
//      O.1.2: given 2 op B within first i cmds, every following ops will be shifted by 2 next available white cells (and fill the last one)
//      O.1.3: given X opB's, every following ops will move X
// O.2: first cell never gets filled (as is)
// O.3: at most n additional black cells (opB => guarantees +1, opA => at most 1 additional)
// O.4: opA always moves +1 to the right, opB moves variable to the right (both moves right)
//      O.4.1: each additional opB filles every other white cells (skipping all black cells)
//          starting with filling the first white cell
//          O.4.1.1: at each new step, the previously white cell gets filled and we skip an extra white cell (after all the a's if present) to fill the next (as we go across the cells)
//      O.4.2: opA will go to the next right-adjacent cell after all opBs

// MAJOR OBSERVATION (IN HINDSIGHT):
//      WHEN OP B is the latest/last/recent operation @i: OP B finds the next white cell (as defined above)
//      AFTER (to prepare for future operations): WE ASSUME OP B finds the next NEXT white cell
//  (assuming the recently filled cell as black)
//  ~~ this is assuming we are filling all white cells to black for every operation
//          but the question is asking which cells will be filled given a set of operations, which can skip
//          certain white cells as it traverse through a
//  O.1: if it remains black stays black => the input is a subset of the output (more black cells at the end)
//  O.2: both observation A,B moves right only
//  O.3: op B jumps to MEX(A) (excluding 0)
//  O.4: output should be in (ordered) set
//  O.5: opA and opB is same if the next cell is white, else diverges

void solve([[maybe_unused]] ll T)
{
    READ(n, m);
    READ_S(s);
    READ_VLL(a, m);

    vll f;
    ll ind = 1;
    ll ai = 0;
    ll nb = 0;
    bool max_a = false;

    if (a[ai] == ind) // cell @ ind is in the black cell list
    {
        f.push_back(1);
        ai++;
    }
    for (auto &c : s)
    {
        if (c == 'A')
        {
            ind++;
            if (!max_a && a[ai] == ind) // cell@ind is in the filled cell list
            {
                ai++; // next index in the filled cell list
                if (ai >= m)
                {
                    max_a = true;
                }
            }
            f.push_back(ind); // regardless, we will be re-including it in the final list
        }
        else
        {
            ind++; // assume the next cell is white (regardless of the current)
            nb++;

            // ll cnt = nb * 2 - 1;
            // bool last = nb > 1 ? false : true;
            // while (true) // if cell@ind is black, skip until the next white
            // {
            //     if (!max_a && a[ai] == ind)
            //     {                     // still black cells
            //         f.push_back(ind); // black cell re-included

            //         ai++;
            //         if (ai >= m)
            //         {
            //             max_a = true;
            //         }
            //         ind++;
            //     }
            //     else if (!last)
            //     { // @ind is no longer black cell but not last (skip current white & fills the other)

            //         // cnt--;
            //         ind++;
            //         last = true;
            //     }
            //     else
            //     { // @ind is no longer black cell and last (operation B fills this cell)
            //         f.push_back(ind);
            //         // ind++;
            //         break;
            //     }
            // }

            while (true) // if cell@ind is black, skip until the next white
            {
                if (!max_a && a[ai] == ind)
                {                     // still black cells
                    f.push_back(ind); // black cell re-included

                    ai++;
                    if (ai >= m)
                    {
                        max_a = true;
                    }
                    ind++;
                }
                else
                { // @ind is no longer black cell
                    f.push_back(ind);
                    ind++;
                    break;
                }
            }

            // once we fill closest white cell, we assume this is filled and increment
            //  till AT the next white cell to prepare for later operations

            while (true) // if cell@ind is black, skip until the next white
            {
                if (!max_a && a[ai] == ind)
                {                     // still black cells
                    f.push_back(ind); // black cell re-included

                    ai++;
                    if (ai >= m)
                    {
                        max_a = true;
                    }
                    ind++;
                }
                else
                { // @ind is no longer a black cell (originally)
                    // (found the next white cell on what B would do for later ops)

                    // f.push_back(ind);
                    // ind++;
                    break;
                }
            }

            // # of b's (nb) == 1 => fill now
            // mb == 2 => fill the next next white
            // mb == 3 => fill the next next next white
        }
    }
    for (int i = ai; i < m; i++)
    {
        f.push_back(a[i]);
    }

    OUT(f.size());
    OUT_ITER(f);
}