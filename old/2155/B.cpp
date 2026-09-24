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

// rephrasing:
//      nxn grid
//      exactly k cells leads to outside of the grid
//      smallest grid: 2x2
// O.1: for a cell to not able to get outside of the grid, it must be within a cycle (there are no dead ends)
//      Q.1.1: how can we form a cycle given k # of cells excluded from a cycle?
//              2-cycle: left,right; up,down; etc...
//              3-cycle: existent => 2-cycle with a cell leading into the 2-cycle => potential generalization??
// H.2: we can let k cells lead to outside of the grid and n^2-k cells point to a 2-cycle (the smallest cycle)
//      Q.2.1: can we do it? if so, how would we construct it?
//          make all cells point right
//          if n^2-k>=2: make a 2-cycle at top-left corner vertically
//              each new cell that's not k, make the cell below the 2-cycle point up...
//              if the left col is filled, go to the right....
//      let's make this easier from top to bottom with 2-cycle horizontal in the top left corner

// BUG NOTE: if all k cells then it works

void solve([[maybe_unused]] ll T)
{
    READ(n, k);
    vector<string> grid;

    if (n * n - k == 1)
    {
        OUT("NO");
        return;
    }

    // cycled cells remaining
    ll r = n * n - k;

    INC(i, n)
    {
        string s;
        if (i == 0 && n * n - k >= 2)
        {
            s = "RL";
            r -= 2;
        }
        ll sz = (ll)s.size();
        s.append(min(r, n - sz), i == 0 ? 'L' : 'U');
        r -= min(r, n - sz);
        s.append(n - s.size(), 'R');
        grid.push_back(s);
    }

    OUT("YES");
    INC(i, n)
    {
        cout << grid[i] << endl;
    }
}