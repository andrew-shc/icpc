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

// O.1: min ops is n, max ops is 2*n (mostly useless observation, since we're not given # of ops to restrict the edge cases)
// O.2: a substring reversal can AT MOST reduce 2 ops. consider the following:
//          01001110
//            |   |  <-- reversed portion
//          01111000
//        1->0 and 1->0 in the beginning and at the end of the substring has been replaced with
//        1->1 and 0->0 => which saves on op.2 (reducing unnecessary finger movements)
//
//      O.2.1: if you find a pair of (1->0*, 1*->0) or (0->1*, 0*->1), you can always use your single allotted substring reversal to reduce 2 ops
//                  (we don't about the characters within the substring)
//                  => which returns the answer
//      O.2.2: if you find a pair of (1->0*, 0*->1) or (0->1*, 1*->0)
//                  => does nothing. reversing the substring still yields the same characters at its end (where the ends matters)
//                  => same thing when the outside of the substring is the same also
//                          (0->x*, y*->0) or (1->x*, y*->1)
//                  or again a generalization of O.2.2
//                          (x->0*, 0*->y) or (x->1*, 1*->y)
//      O.2.3: (1->1*, 0*->0) or (0->0*, 1*->1) is the remaining case, but reversing on this actually adds cost (bad)
//                  so O.2.1 is the only way to apply reverse substring for reducing 2 ops... what about reducing 1 ops?
// H.3: you can only reduce cost by 2 (you cannot reduce cost by 1 except when reversing the whole (?) string)
//      if you can reduce 1 ops on one end, (if they were originally different and became same => originally different)
//          then, that means the ends of the substring are different/opposing (i.e., to reduce any ops, the ends of the substring must be different)
//              => if the ends are same originally, it will be different now (+1 cost)
//                 if the ends are different originally, it will be same now (-1 cost)
//              => so a total of 0 cost or 2 cost reduction
//      what about the special case?
//          you can only reduce 1 cost if the substring that is used to reverse the string is touching at the end of the string
//              since that end does not care (effectively, the ends are always matching => allowing -1 cost)
//              BUT ONLY AT THE FINAL end, not at the beginning of the string where we start with 0 and reversing the string effects the cost
//                  in the beginning

// strat
//      find (1->0*, 1*->0/E) or (0/B->1*, 0*->1/E) where E denotes the end and B denotes the beginning
//      if E is present (at the end), -1 ops
//      if E is not present (not at the end), -2 ops (prefer this)
// O.4: since an end always exist (i.e., pick a character at the end), we can always reduce by 1 ops if an opposing adjacent local pair is found
//          (when there are only 1)

// strat II:
//      find number of 1->0 (end type 1)                            + if 1 is at the end
//      find number of 0->1 (end type 2) + if 1 is at the beginning + if 0 is at the end
//  if any of them occurs more than once (excluding endend) => -2 ops
//  if any of them occurs once (with endend required) => -1 ops
//  if no occurrence => 0 ops reduced (regardless of the endend)

// REMEMBER: we are REVERSEING SUBSTRING, NOT INVERTING SUBSTRING

// per editorial solution
// we can actually simplify the solution by observing that
//      that if we certain amount of adjacent bit flips, we can deduce directly whether we can reduce the cost by 2, by 1, or none
//      e.g., 0000111111000
//          has to imply a change of +1,+1 => reduction of cost of 1 is possible
//      MAIN IDEA: the end can always be treated as a freebie what wont change the number of adjacent bit flips (wont increase or decrease of otherwise a pair-wise inc/dec => +0 or +2)
//      MAIN IDEA 2 (MISSED OBSERVATION): each change always suggests an alternating order (0->1 to 1->0)
//          so we technically dont have to split into two values to store individual changes since if the 1st change is 0->1, second change is always 1->0

void solve([[maybe_unused]] ll T)
{
    READ(n);
    READ_S(s);

    if (n == 1)
    {
        OUT(1 + (s[0] == '1' ? 1 : 0));
        return;
    }

    ll base_ops = 0;
    ll type1 = 0;
    ll type2 = 0;
    bool type1end = s[n - 1] == '1';
    bool type2end = s[n - 1] == '0';
    INC(i, n)
    {
        if (i == 0 && s[i] == '1')
        {
            type2++;
            base_ops += 1; // switch
        }

        if (i < n - 1)
        {
            if (s[i] != s[i + 1])
            {
                base_ops += 2; // press current and switch for next
            }
            else
            {
                base_ops += 1; // just press current
            }

            if (s[i] == '1' && s[i + 1] == '0')
            {
                type1++;
            }
            if (s[i] == '0' && s[i + 1] == '1')
            {
                type2++;
            }
        }

        if (i == n - 1)
        {
            base_ops++; // previous character already switched for you
        }
    }

    if (type1 >= 2 || type2 >= 2)
    {
        OUT(base_ops - 2);
    }
    else if ((type1 == 1 && type1end) || (type2 == 1 && type2end))
    {
        OUT(base_ops - 1);
    }
    else
    {
        OUT(base_ops);
    }
}