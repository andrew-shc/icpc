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

// IMPORTANT CAVEAT: CARD 1 BEATS CARD n (or else it's an 800 problem)

// O.1: n>n-1>n-2>...>3>2>1>n>n-1>.... the path of which cards beats which is a cycle ONLY when passing through 1,n only
//  O.1.1: it's more than just a path....
//            1 2 3 4 5 n
//          1   ^ ^ ^ ^ <
//          2 <   ^ ^ ^ ^
//          3 < <   ^ ^ ^
//          4 < < <   ^ ^
//          5 < < < <   ^
//          n ^ < < < <
//      for each card from 1 to n, lower cards has a higher chance of getting beaten by higher cards
//      except for 1 which has the equal of chance of losing as the card #2 but an additional chance to win n
// O.2: a player that controls 1,n controls the cycle and can keep optimally playing n to eventually win all
//          (since the opponent does not have 1 to win back n)
//      O.2.1: this can only happen once. the moment either player captures an n, it suggests one of them already has #1 and the game has effectively ended.
//      O.2.2: having #n is not an effective win: you need both 1,n
//      O.2.3: if you don't have both 1,n,or neither, it's not an effective win, but it is still possible to obtain 1,n,both
// O.3: if neither player has the control of both 1,n => both player either has the one and the other (1,n)
// O.4: if Bob has #n, whenever Alice plays #2-#(n-1), Bob (after seeing Alice's) optimally deterministically chooses #n
//                     whenever Alice plays #1, Bob players !#n (ONLY when Bob has other cards) or else, Bob has no other cards to give and loses
// O.5: if Bob has #1, whenever Alice plays #2..#(n-1), => see who has the higher cards (from 2 to n-1)
//                          (if Alice has the higher card except #n (Alice has #(n-1)), Alice eventually wins)
//                          (if Alice has the lower card except #n (Bob has #(n-1)), Bob evenetually wins)
//                          if Alice has other cards, see which one is better?
//        ~~~~~~~~~~~~~~~~~~BUT, Alice has to eventually play #n => Bob plays #1 => Bob wins by holding #1,n
//         ~~~~~~~~~~~~~~~~~NOT IF Alice wins first by FORCING Bob to play ALL his cards
//                     whenever Alice plays #n, Bob optimally deterministically plays #1
//                          if Alice has no other cards, Bob win
//    >>>in both observation, Alice always picks the largest card possible

void solve([[maybe_unused]] ll T)
{
    READ(n);
    READ_S(s);

    if (s[0] == s[n - 1] && s[0] == 'A')
    {
        OUT("Alice");
    }
    else if (s[0] == s[n - 1] && s[0] == 'B')
    {
        OUT("Bob");
    }
    else if (s[n - 1] == 'B')
    { // see if Bob has other cards to play against Alice's 1 card; if not, Bob will eventually lose
        INC(i, n - 1)
        {
            if (s[i] == 'B')
            {
                // Bob has other cards not just #n
                OUT("Bob");
                return;
            }
        }
        OUT("Alice");
    }
    else
    { // Bob has #1
        // if Alice has other card than the n card
        bool only_n = true;
        INC(i, n - 1)
        {
            if (s[i] == 'A')
            {
                only_n = false;
            }
        }
        if (only_n)
        { // alice only has the one and only #n which Bob has #1 to win
            OUT("Bob");
            return;
        }

        if (s[n - 2] == 'A')
        {
            OUT("Alice");
        }
        else
        {
            OUT("Bob");
        }

        // otherwise, we have to check if Alice or Bob has #(n-1) (the next biggest card)
        //      since #n is Alice's....
        // if Alice has #n-1, it can just take all of Bob's card.
        // if Bob has #n-1, it can just take all of Alice's card.
        //      by picking #n-1 when Alice does not pick #n
        //      and picking #1 when Alice does pick #n
    }
}