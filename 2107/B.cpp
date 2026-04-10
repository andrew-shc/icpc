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

// rephrase: there are n boxes each with ai apples
//          the current players loses if there are no more apples in any boxes
//                                       or the max apples - min apples greater than (>) the difference k (AFTER MOVE).

// properties:
//      - order does not matter on array a => sorting on a is fine

// O.1: since the min-max>k condition is always checked after the current player's move
//          the current player will always optimally avoid meeting the min-max>k condition.
// O.2: an apple will always be decremented among the boxes at the start of each round
//          KEYWORD: DECREMENTED

// O.3: if max-min=k+1, the first player should always try to take an apple from the max
//      O.3.1: if they're multiple maxes, => second player wins
// O.4: if max-min>k+1, the first player always loses => second player wins
// O.5: if max-min<=k, what's the optimal choice?
//      per O.1., to avoid the condition and win, they always seek to reduce the range
//          even if a player intentionally increases the difference to k, the next player will
//          always have the option to try reduce the difference

// O.6: each player can either pick the max to reduce the difference or pick the min to increase the difference
//      O.6.1: picking elements in the middle of the range does nothing

// O.7: ignoring the max-min>k condition,
//      if n%2==0: JERRY wins, else: TOM wins
//          O.7.1: apples will always slowly get reduced (as stated for O.2)
// O.8: re-applying max-min>k condition,
//      if max-min>k+1 (before) => max-min>k (after; always) => current player always lose
//      if max-min=k+1 (before) => max-min=k or k+1
//          if single max => max-min=k<k+1 => continue (on the max-min<k+1 branch)
//          if multi max @k+1 => max-min=k+1 => current player always loses
//      [the loop] if max-min<k+1 (before) => max-min<k+1 (after; always by optimality) => current player always stay for now
//      Q.8.1: is there a way to induce a win/lose before the end of this loop?
//          O.8.1.1: decrease at max will increase the multiplicity/amount of maxes
//                      => the opposing player can increase the range by decreasing the min until the range r after is k
//                          (since the player does not want to lose itself)
//                      => WAIT THIS IS AN EASY FACT, he condition HAPPENS IMMEDIATELY AFTER (something weird is going with this)
//                          per O.1 (again), regardless if they're multiple maxes or some potential way to induce a lost/win early or change their
//                              fate (per O.7)
//                          JERRY and TOM wil always try to stay as long as possible and CAN STAY as long as possible
//                          bc O.1

// O.9: every round an apple is reduced, the range (r) can be incremented or decremented by at most 1.

// =========================================== (an idea realized but didn't fully went through my head)
// O.1*: SINCE the max-min>k kill condition is always checked AFTER the current player's move
//          => whatever they do, they will make themselves LOSE FIRST before the opposing player could lose
//          => we can only rely on the first 2 events to decide the fate of the players
//              (since the player will always find a way to save themselves first regardless of which boxes they chose)
// O.7*: ignoring the max-min>k condition
//      if n%2==0: JERRY wins, else: TOM wins

// strat (per O.8,O.3-O.5)
// 1. max-min > k+1 => JERRY wins
// 2. max-min = k+1 =>
//      max occurs once => continue to 3.
//      max occurs more than once => JERRY wins
// 3. n%2 == 0: JERRY wins, else: TOM wins

// SUM OF ai, NOT THE LENGTH ITSELF (n)

// ~~~~~~~~~~~~~~~~~~~
//      O.8.1: execution path analysis shows the player will always choose max

void solve([[maybe_unused]] ll T)
{
    READ(n, k);
    READ_VLL(a, n);

    sort(a.begin(), a.end()); // min to max (ascending order)

    if (a[n - 1] - a[0] > k + 1)
    {
        OUT("Jerry");
        return;
    }
    else if ((a[n - 1] - a[0] == k + 1) && a[n - 2] == a[n - 1])
    { // && checks if the max happens more than once (we know n>=2)
        OUT("Jerry");
        return;
    }

    ll sum = accumulate(a.begin(), a.end(), 0LL);

    if (sum % 2 == 0)
    {
        OUT("Jerry");
    }
    else
    {
        OUT("Tom");
    }
}

/*
WA2 analysis

2
2 1
1 1
10 3
10 10 10 10 10 10 10 10 10 10

Jerry
you're suppose to sum, not the element length you dumb dumb


*/