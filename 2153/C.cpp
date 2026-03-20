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
    ios_base::sync_with_stdio(false);
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

// remember: we are maximizing perimeter
// O.1: polygons requires >= 3 sticks (pre-constrained by test cases)
// O.2: symmetrical polygon requires at most 2 unique single stand alone sticks with rest requiring duplicates (for the flipside)
// O.3: no one stick (the max length) of a theoretical polygon with k sticks can be greater than or equal to the sum of
//                                              k-1 remaining sticks' length
//      max-stick cannot be on the even sides, restricting max-stick to the "odd" sides (on the line of symmetry).
//      so check if any of the odd sided sticks (can have none, single, or two) are well-defined
//          Q.3.1: if the odd sides don't satisfy... move to the next two?... until the last one... and until none if neither is satisfied
//          O.3.2: if there are a single pair of even sides, then an odd side must be present.
// O.4: if the odd sides are equal in length, we can simplify our case analysis by treating it as if it was moved to side
//      => types of polygons: all even sides (all sides has its duplicate counterpart), one odd side, two odd side (different length)
// O.5: there must be at least ONE PAIR of even sides

// given n sticks.... we can form polygon with max perimeters by...
//      matching all duplicates --> even sides, pick two largest stick --> two odd sides (if possible)

void solve([[maybe_unused]] ll T)
{
    READ(n);
    // READ_VLL(a, n);

    // cout << 705084822 + 226069413 + 226069413 + 226069413 << endl;

    set<ll> buffer;
    ll perimeter = 0;
    ll even_sides = 0;
    INC(i, n)
    {
        ll ai;
        cin >> ai;

        // if (T == 49)
        // {
        //     cout << ai << "-";
        // }

        if (buffer.count(ai) == 0)
        {
            buffer.insert(ai);
        }
        else
        { // matched duplicates
            buffer.erase(ai);
            perimeter += ai * 2;
            even_sides++;
        }
    }

    if (even_sides == 0)
    {
        DBGLN("=0 EVEN SIDES");
        // no even sides => no symmetry :(
        OUT(0);
        return;
    }
    else // even_sides >= 1
    {    // add 2 largest odd sides if any still available
        DBGLN(">0 EVEN SIDES");

        if (buffer.size() == 0)
        {
            DBGLN("BUFFER 0");
            OUT(perimeter);
            return;
        }

        bool chosen = false;
        for (auto it = buffer.rbegin(); next(it) != buffer.rend(); ++it)
        {
            DBGLN("FIND 2:", *it, perimeter, *next(it), perimeter + *next(it));
            if (*it < perimeter + *next(it))
            {
                DBGLN("FOUND", *it, perimeter, *next(it));
                perimeter += *next(it) + *it;
                chosen = true;
                break;
            }
        }
        DBGLN("FIND 1:", *buffer.rbegin(), perimeter);

        // ANOTHER BUG: this shouldve been the first smallest element in the buffer
        if (!chosen && *buffer.begin() < perimeter)
        {
            DBGLN("FOUND 1");
            perimeter += *buffer.begin(); // ANOTHER BUG forgot to change rbegin to begin after changing the condition
            chosen = true;
        }

        // conclusion: with even just a pair of even sides, you can still have 1-2 odd sides
        //      just have to consider that just an even side itself does not make it valid

        if (even_sides == 1 && !chosen)
        {
            DBGLN("EVEN 1 & NO ODD SIDES");
            OUT(0);
        }
        else
        {
            DBGLN("EVEN >1 or 1-2 ODD SIDES");
            OUT(perimeter);
        }
        return;
    }
}

/*
TESTING EDGE CASES

1
6
5 5 9 18 25 47
19

shouldn't be 5+5+9+18?
actually the algo produced a better result of 53

1
6
1000000000 1000000000 1000000001 1000000002 1000000003 1000000004



from the test cases extracted from the website (not available during contest / bad habit)

1
4
705084822 226069413 226069413 226069413

>>0
<<678208239

*/