#include <bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef std::vector<ll> vll;
typedef std::deque<ll> dll;

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

// O.1: to maximize the number of days (Mani), optimally choose the cell closest to Hamid
//      Q.1.1: the left or right adjacent of Hamid?
//      O.1.2: ^^ the side with lesser amount of walls (to force Hamid with less options)
// O.2: Hamid will always optimally choose the side with the least amount of walls (since he can always traverse empty cells)
// O.3: HOWEVER, after Hamid hit the wall, Mani can still build the wall in Hamid's previous direction, possibly delaying Hamid with walls all the way
// O.4: Hamid is like placed in a group of EMPTY and trying to enlarge the EMPTY cell since Mani is always placing a wall in the direction of
//              where Hamid decides its the optimal direction
// O.5: pretty sure Hamid can select one optimal direction to go for the rest of this simulation to get the optimal # of days
//      O.5.1: the optimal direction... a comparison of number of days needed to go in either L or R
//                  per O.2, go with less walls
//                  COUNTEREXAMPLE: ####x....#..#...#
//                                  4321     12345678
//                  COUNTERCOUNTEREXAMPLE:   #.#.#.#...x...#..#..#
//                                           7654321       1234567
//      O.5.2: the optimal direction is the smallest distance between the first and to the extreme cell (the last cell does not always have to be *originally* wall)
//      Q.5.3: switch direction midway? or place wall behind the direction Hamid is going?
//              O.5.3: if one is distinctively closer, choosing the further one does not help.
//                      if one is same distance either side, choose the other direction is the same
//                      if you place a wall behind the direction Hamid is going, Hamid decides the direction is already optimal and you're just making it a freebie for Hamid
//                      => no need to switch midway && placing wall behind suboptimal
// O.6: if the optimal direction is the smallest distance, does the number of pre-existing walls matter?
//      no, since you will always encounter a wall in the optimal direction whether it was present or not (Mani will always jsut have the right amount
//      of operations to select an EMPTY->WALLED or have a surplus (too much walls in the remaining cells))
// REMEMBER, MANI STARTS FIRST (THE WALL BUILDING)

void solve([[maybe_unused]] ll T)
{
    READ(n, x);
    READ_S(s);

    if (x == 1 || x == n)
    {
        OUT(1);
        return;
    }

    // excluding the first #
    ll ldist = 0;
    ll rdist = 0;
    for (int i = x; i < n; i++)
    { // technically going from x+1 (0-index)
        if (s[i] == '#')
        {
            break;
        }
        rdist++;
    }
    for (int i = x - 2; i >= 0; i--)
    { // technically going from x-1 (0-index)
        if (s[i] == '#')
        {
            break;
        }
        ldist++;
    }

    // number of total days to escape
    ll ldist2 = x - ldist;
    ll ldist2worst = x;
    ll rdist2 = n - x - rdist + 1;
    ll rdist2worst = n - x + 1;

    // Mani has the first choice, so he obviously will choose the one the direction with the smallest # of days and make it as large as possible
    // to make the other direction seems as good as the originally good or became the better option (as a 2nd best option)

    // RECALL: LOWER IS BETTER => HIGHER IS WORSE
    if (ldist2 > rdist2)
    { // rdist2 is the best --> make it as worst as it can be (can still be better then rdist2 still)
        OUT(min(ldist2, rdist2worst));
    }
    else if (ldist2 < rdist2)
    {
        OUT(min(ldist2worst, rdist2));
    }
    else
    {
        // if both are equal, one of them will always be present regardless of Mani's decision
        OUT(ldist2);
        // why is this not in the earlier 2 cases?
        //      you cant place walls on both sides requiring 2 ops
        //      but when equal, then placing wall one side makes it worst and placing he other wall makes it worst
        //          but actually they all must have one of ldist2==rdist2
    }

    // OUT(max(ldist2, rdist2));
    return;
}

/*

3
10 5
..........
10 5
...#......
10 5
.....#....

1
5
5  <-- got 6 due to the oddness of the grids and depending on x itself

*/