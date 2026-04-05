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

// rephrase, you have [a,c] vs [b,d]
//      if d<=0, b can't attack a
//      if c<=0, a can't attack b

// O.1: each round at most one HP will be reduced
// O.2: if knight dies, then the opponent can't reduce the other's HP (the other will eventually win) => if c or d becomes 0 => effectively dead for them
//          O.2.1: killing knight vs killing player is the same => optimally, pick the minimum of either
//          O.2.2: you can only reduce their HP via your knight => if your knight's HP is higher than your opponent's HP you win... bruh
//              O.2.2.1: actually, if their knight's HP is higher but their HP themselves are smaller, they still lose
//              O.2.2.2: otherwise, you actually have no way of killing them because they will always optimally try to attack your knight
//              O.2.2.3: unless you yourself have an hp higher or equal than their knight's (per round, they will get you before you can)
// O.3: supposedly the game can never draw (there will be a player who will effectively die first in this strictly alternating rounds of this game)

// ok im overcomplicating something simple

// given [a,c] vs [b,d]
// if c>=d => a wins
// if c<d  => b wins
// but
// if a<d  => b wins (except when c>=d and a>=c => ok so three way equality then)
// if a>=d => b shouldnt attack a's (no info)
// if b<=c => a wins
// if b>c  => no info (same as above; except when c<d)

// [a  c]
//   vs
// [b  d]

// a vs b who wins?

// if min(a,c) >= d => a wins regardless?
// if min(a,c) < d => b wins (b will get to a before c get to d)
//          however, if c >= b, a wins just by targetting b or if b>d, a wins just by targetting d
//                              so c >= min(b,d)?
//                      c < b, b wins
// so min(a,c) >= d || c >= min(b,d) ???
//      ==> the smallest of either will get attacked by d but a wins since d will be exhausted by then (defensive)
//              OR if the knight is larger or equal than the smallest of both meaning a also wins by attacking the weakpoint of b (offensive)
//                      except when d can obliterate a,c hence this needs to be an AND

// so min(a,c) >= d && c >= min(b,d)??
//        if c is lesser than b or d then whatever it does it can't finish off b even when the minimum of a,c is larger than d????
//              if the smallest of a,c is larger than d, then c must be larger than d, but if b is less than d and somehow b is smaller than or equal to c
//              , b loses (a wins)
//                      NOTE: when i flip c's perspective of c is greater than or equal to b -> a wins to b's perspective
//                                      we still say b is less than or EQUAL to c -> b loses since we are NOT NEGATING THE STATEMENT (just changing perspective)

//  but if c is smaller than b (but still larger than d), then d<c<b => d<b => min(b,d) < c (Gellyfish wins)
//          since if c is larger than d (or equal to), it can obliterate b's d (effective lost)
//          however, if d is strictly larger than the min of a,c, a loses which means min(a,c)<d which correctly breaks the condition
//          but what if c>=min(b,d)? => then that means c can still attack b or d first to gain wins so Gellyfish (a) should still win
//              but with min(a,c)<d and c>=min(b,d) =>
//                      d>c then it must be d>c>=b => a can still win? i think it depends on the difference ON THE DIFFERENCE NOT COMPARISONS THATS THE LIKELY SOURCE OF CONTRADICTION
//                      d>a then c>=(b or d)

// min(min(b,d),min(a,c))    is the max amount of rounds it'll take for b to obliterate a or run out of its own hp [whichever is the smallest] (optimally)
//                                  since the opposing round picks the smallest hp to get the effective obliteration (since this is the optimal)

// actually, since optimally each player wants to keep attacking the other....
//      it would be comparing between min(b,d) and min(a,c)?
//          if one's min hp is lower then the other, it gets obliterated
//              since we don't care about the knight if their own hp is lower, but if the knight is larger it is just same as obliterating the player itself (effective death)
//              and when a knight is obliterated, it is same as obliterating the player (no more exchanging attacks => converge to a solution/win)
//          but it is also same thing with the other end => both will keep on losing their lowest hp until it either can return the attack or it gets obliterated by itself
//      min(a,c) >= min(b,d) => a wins

// ---------------------------- MAJOR FAILURE IN TODAY'S A ----------------------------
// Failure to let the observation sink in when there the optimal choice for each player or really the only effects of their choice is the reduction of the other's HP
//      in other words, each player's own hp reflects the number of rounds left they have
// And the optimal choice is to pick the smallest of both since obliterating the knight is same as obliterating the player itself (effective death since no knight no reduction of opponent's hp)
// So therefore the final answer is the opponents will pick your smallest hp (i.e., the minimum round you have) and the minimum round they have and find which one
//      gets obliterated asap (which one minimum is the lesser of the two)
// ------------------------------------------------------------------------------------

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// d-min(a,c)  is the amount it'll take for b to obliterate a (greedily / optimally)
// c-min(b,d)  is the amount it'll take for a to obliterate b (greedily / optimally)
// (previously with comparison, it only checks if these are negatives or not; now, we are considering the actual turns themselves which is the actual
//   correct option)
// if a obliterates b in the SAME or LESS rounds than what b takes to a, then a wins first (SAME because "a" gets the first turn)
// if b obliterates in strictly LESS rounds then the other way, then b wins first
// what if negatives? a obliterates b in NEGATIVE rounds?
//          ****no this is the wrong calculation**** this is calculating how many extra rounds left after obliteration

void solve([[maybe_unused]] ll T)
{
    READ(a, b, c, d);
    // if (a >= min(b, d) && d <= min(a, c))
    // if (min(a, c) >= d && c >= min(b, d))
    if (min(a, c) >= min(b, d))
    {
        OUT("Gellyfish");
    }
    else
    {
        OUT("Flower");
    }
}