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

// rephrase: for gcd of all elements to be above 1, they must'nt be co-prime and have a common factor that's not just 1
// rephrase: each operation you can simultaneously add multiple elements ai with k (default is 0)

// O.1: if k is odd (i.e., %2==1), you can keep adding elements until they're all even (%2==0) since two odds make an even
//      O.1.1: 2 is the closest smallest prime after shifting the odd k down by 1
//      O.1.2: generalization? given k, shift down by 1? find smallest prime kp? (%kp=z) then add k z times to that number?
//              ~~~~~~~~ k*z (since z<kp<=k => we can certainly do it within the limits of k operations)
//              each time we add k, (since kp=k-1), %kp=z+1 => kp-z times actually
//      O.1.3: we dont even need to find the smallest factor of kp (k-1), since 0<=z<=kp<k suggests kp-z<k (well within limits of k)
// error: div by 0, can we do kp=k+1?
//      if kp=k+1 =>  0<=z<=k<kp => kp-z=k+1-z => <=k (if we exclude k+1-z=k+1 when z is 0)
//              wait this is possible, if z is 0, we just dont do anything (SO LETS DO KP=K+1)
//      wait wait if kp=k+1, then %kp=z suggests we need to add z times not k+1-z
// special case if k=1, kp=2? (we just let it be ai%2)
// just do a special case for k is odd (includes 1) not elegant

// k=2 is just impossible......

void solve([[maybe_unused]] ll T)
{
    READ(n, k);
    ll kp = k + 1;

    INC(i, n)
    {
        ll ai;
        cin >> ai;

        ai += k * (ai % kp != 0 ? ai % kp : 0);
        cout << ai << " ";
    }
    cout << endl;
}