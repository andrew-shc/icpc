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

// rephrase compute each element of the r array (ri) where it is a max of 2^p_j+2^q_(i-j)
//                  i.e., from 0 to i inclusive (0-index) and adding the numbers of p from left and q from right of i
//                                      ^^ the max of the two-sum of 2-power

// consider 2^3 + 2^3 vs 2^2 + 2^4
//            8 + 8        4 + 16
//              16           20
//   i.e., we CANNOT naively find the max in the p and q itself

// max(2^p_j + 2^q_(i-j)) = max(2^p_j) + max(2^q_(i-j)) over j = 0 to i
// isnt this like prefix and suffix max?

// for each increase in i.. what does it change? we have an additional 2^p_i + 2^q_0 to consider
//      and with the increase in i, every previous q_{i-j} becomes q_{i-j+1} for j=0 to old i (or i-1)
//      recompute all previous max but there's has to be an easier way
//      this +1 in the q suggests all the element in q corresponding to p is being shift one to the right, DP-able?
//      the new max can appear anywhere (not necessarily adjacent to the old max)
// major problem: the corresponding elements in q (in its entirety) keeps shifting to the right which requires recomputation of the entire sums and 10^5 must be O(n) or O(nlogn)
// this change in correspondence is the opposite of invariance... any invariance in here? maybe from the max?

// something with the power of 2s and permutation?
// 2^9 + ? > 2^8 + 2^7?
// 512 + ? > 256 + 128 (yes)

// 2^n = (4/2)*2^(n-1) > 2^(n-1) + 2^(n-2) = 2^(n-1) + 2^(n-1)/2 = (3/2)*2^(n-1)

// MAJOR OBSERVATION: if an element is the largest, then regardless what the other number, it will beat all other combinations
//      COROLLARY: if there are two combination with the max (of a given subarray), then we just compare who has the larger second number

// so everytime we increase i, compute the prefix max of p (and find its index to compute its corresponding q)
//                             compute the prefix max of q (and find its index to compute its corresponding p)
//          then given each prefix max of p and q, pick whichever is larger, and if p==q, pick whichever is larger (doesnt matter if the 2nd is same that means the correspondence is same on both sides)
//          => this can be simplified to just computing pseudo-r from p and pseudo-r from q and find which one is larger
// remember to update the smaller summand

// order matters

ll powmod(ll base, ll exp)
{
    ll res = 1;
    ll b = base % MOD;
    while (exp > 0)
    {
        if (exp & 1)
        {
            res = (res * b) % MOD;
        }
        b = (b * b) % MOD;
        exp >>= 1;
    }
    return res;
}

void solve([[maybe_unused]] ll T)
{
    READ(n);
    READ_VLL(p, n);
    READ_VLL(q, n);

    // output with modulo

    // prefix max of the indices
    ll pm_pi = 0;
    ll pm_qi = 0;

    vll r;
    INC(i, n)
    {
        if (p[pm_pi] < p[i])
        {
            pm_pi = i;
        }

        if (q[pm_qi] < q[i])
        {
            pm_qi = i;
        }

        // pm_qi = i - j
        // j = i - pm_qi

        // so at each new index, we stick with the largest in p and q and recompute
        // its correspondence and pick whichever is the larger one

        // DBGLN(1LL << (p[pm_pi]) + 1LL << (q[i - pm_pi]), 1LL << (p[i - pm_qi]) + 1LL << (q[pm_qi]));
        // DBGLN(p[pm_pi], q[i - pm_pi], p[i - pm_qi], q[pm_qi]);
        // DBGLN(1LL << p[pm_pi], 1LL << q[i - pm_pi], 1LL << p[i - pm_qi], 1LL << q[pm_qi]);

        // r.push_back(
        //     max(
        //         (1LL << (p[pm_pi])) + (1LL << (q[i - pm_pi])),
        //         (1LL << (p[i - pm_qi])) + (1LL << (q[pm_qi]))));

        // this needs special ways to compute the answer

        // ~~~~ 2^x mod y =? (2^z) mod y * [(2^{x-z}) mod y] let's say for mod < 2^x < 2*mod where z is the cutoff right to the next mod-interval
        // ~~~~ since 2^x === 2^z mod y (since z is right large enough to pass the next y)

        // 2*2*2*2 mod 3 = 2*2 mod 3 (yes???? why????)
        // 4*4*4*4 mod 7 = 4 mod 7 ()
        // 256 mod 7 = 4 mod 7
        // 36*7+4 mod 7 = 4 mod 7 ????
        // its like as if xk+r = 0k+r
        // proof by induction on x such that 2^x mod 7 = 1
        // ^^ ~~~~~~~~~~
        // if the factor is within the modulo, it will take several factors to loop back to the same number within modulo
        // consider a number y that is barely above the MOD, tell me why (2*y)%MOD equals y%MOD+y%MOD
        //      that justs (y+y)%MOD which is definitely y%MOD + y%MOD
        //          since (MOD+(y-MOD) + MOD+(y-MOD)) % MOD = [2*MOD + 2*(y-MOD)] % MOD = 2*(y-MOD) = 2*(y%MOD)
        //                  suppose MOD<=y<2*MOD but can be generalized by implicitly finding a hidden factor s.t. y-k*MOD is right below it and so on and so forth
        //      (5+5)%4 = 5%4+5%4 (its like as if each number's remainder gets aggregated, but at a certain point another one final mod outside is needed)
        //      (5+5+5+5+5)%4 = 1 = (5%4+5%4+5%4+5%4+5%4)%4 = 5%4 = 1
        //      (5*5)%4 = (5*(5%4))%4
        //  now, this can be intuitively generalized to powers which is just 2^x = 2*2*2*2*2*... = 2+2+2+ (2^(x-1) times)

        // hence, 2^x % y = ((2^z)%y)^(x-z) (given a proper x, but this can be done repeatedly further)

        // how to safely exponentiate within the nlogn limits (currently O(n))
        // since we can order the modulo however we like, we can try doing it in a binary exponential to counteract another linear within a linear (quadratic)
        // 2^m = MOD => m=ceil(log2(MOD)), the x right above the MOD is m (let's start with that)
        // if x<ceil(log2(MOD)) => do computation as usual
        // if x>=ceil(log2(MOD)) =>
        //      compute 2^m%MOD (where x -= m)
        //      ah so does this until x<m
        // but that's just n/m.... how binary?
        // x>m? what about x>m+m? x>(m+m)+(m+m)? if x<over some exponential of m start going down
        // x>m? compute x1=2^m%MOD
        //      x>2*m? compute x2=(x1*x1)%MOD
        //          x>2*2*m? compute x3=(x2*x2)%MOD
        //              x>2*2*2*m?   (less than that now?)
        //          if x>=2*2*m: x -= 2*2*m; xf*=x2
        //          or, if x<2*2*m, v go down
        //      if x>= 2*m: x-= 2*m; xf*=x1
        // this is like O(2*log2n) overall O(2nlogn) ?????????
        // precompute the values??????

        // ok just use the fast exponentiation
        // uses the fact that   1. (x%mod)^y%mod=(x^y)%mod
        //                      2. along the exponents bit, if bit is on, multiply by that base but don't if the bit is off (???)
        //                          (the base continues to be squared...)
        // given an exponent lets say 100110 (2+4+32=38)... and x^38 = x^(2+4+32) = x^2+x^4+x^32
        //      = x^2+(x^2)^2+((((x^2)^2)^2)^2)^2
        //   this is really convenient fact
        //      and with our previous observation on mod on powers, these all can just be modded
        //   another convenient fact by ~~~distributive property~~~ exponential rule (REMEMBER WE ARE WORKING IN EXPONENTS):
        //      = 2^(x^2 + ....)
        //      = 2^x^2 * 2^(x^2)^2 * ....

        // ll pmp = 1;
        // ll qmp = 1;
        // ll pmq = 1;
        // ll qmq = 1;

        ll p_max;
        ll q_max;
        if (p[pm_pi] > q[pm_qi])
        {
            p_max = p[pm_pi];
            q_max = q[i - pm_pi];
        }
        else if (p[pm_pi] < q[pm_qi])
        {
            p_max = p[i - pm_qi];
            q_max = q[pm_qi];
        }
        else
        {
            // p == q have the same max, check which has the larger of the smaller

            if (q[i - pm_pi] >= p[i - pm_qi])
            { // p[pm_pi] has the larger (doesnt matter if equal) of the smaller than q[pm_qi]'s
                p_max = p[pm_pi];
                q_max = q[i - pm_pi];
            }
            else
            {
                p_max = p[i - pm_qi];
                q_max = q[pm_qi];
            }
        }

        r.push_back((powmod(2, p_max) + powmod(2, q_max)) % MOD);

        // r.push_back(
        //     max(
        //         (1LL << (p[pm_pi])) + (1LL << (q[i - pm_pi])),
        //         (1LL << (p[i - pm_qi])) + (1LL << (q[pm_qi]))) %
        //     MOD);
    }

    OUT_ITER(r);
}

/*

1045576686 MY OUTPUT

 998244353 MOD

  47332333 EXPECTED
*/