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

// recall: a GCD of between integers is the intersection of all the prime factors in each integers
// to maintain the intersection of all the prime factors in each integers
//     => each integers is flexible to change its factors as long its the factor is not part of the intersection
//          (e.g., add or remove)
//     => since the intersecting prime factors must be present and a is already the largest
//     => you can only remove prime factors (from b lets say since a matches b)
//     => a
// so we can run sieves on the first pass on a (find the factors) maybe like a multiset
//  then find the intersection?
//

// HOLD UP RE-INTERPRETING THE QUESTION: WE CAN ONLY DO THIS AT MOST ONCE FOR EACH INDEX
// so just find if the element is flexible (i.e., at least one prime factor can be removed)

// MISREAD QUESTION AGAIN:
//      for ALL l<r subarray => since if you enlarge the subarray the intersection of pf will always get smaller
//          => its just the intersection of all the numbers again (I think?)
//          => but the smaller the intersection the more flexible you can modify the original array (so no)
//          => mutually pair-wise intersection of the prime factors offers the smallest flexibility
//   technically speaking, increasing the elements of the original array is the safest...
//   but since we can only decrease elements, we just have to check if the neighbor of the elements
//      supports a reduction of its own prime factor (and whether its neighbor's neighbor can)
//   in fact, the more you enlarge the subarray, the more relaxed the conditions are... (ie, the large subarray strictly depends on smaller subarrays necessity of the condition)
//      so we can just focus on mutually pair-wise intersection of the PFs
//   check left flexibility (for i=1..n-1 but -1 index comparison)
//   check right flexibility (for i=1..n-1 but -1 index comparison)
//   nah just do another pass

// per editorial after hint 1 (and glancing at discord discussion)

// since for each element we cant have them go below the gcd of either side
// then we have to find the number at that element that barely satisfies both sides' gcd, (least multiples of both gcd)
// hence lcm(gcd,gcd)
// if the number is less than the current element, it is possible to apply the ops

void solve([[maybe_unused]] ll T)
{
    READ(n);
    // we start with a == b
    READ_VLL(a, n);
    READ_VLL(b, n); // upper limit

    ll ops = 0;
    INC(i, n)
    {
        if (i == 0)
        {
            if (gcd(a[i + 1], a[i]) < a[i])
            {
                ops++;
            }
        }
        else if (i == n - 1)
        {
            if (gcd(a[i - 1], a[i]) < a[i])
            {
                ops++;
            }
        }
        else
        {
            if (lcm(gcd(a[i - 1], a[i]), gcd(a[i + 1], a[i])) < a[i])
            {
                ops++;
            }
        }
    }

    OUT(ops);

    // if (T == 157)
    // {
    //     cout << n << "-";
    //     for (auto el : a)
    //     {
    //         cout << el << "A";
    //     }
    //     cout << endl;
    //     // OUT(n);
    //     // OUT_ITER(a);
    //     // OUT_ITER(b);
    // }

    // sieves

    // unordered_map<ll, ll> gcd_pf;
    // vector<unordered_map<ll, ll>> vpf;
    // INC(i, n)
    // {
    //     unordered_map<ll, ll> pf;
    //     pf[1] = 1; // 1 is always present as a prime factor
    //     for (ll f = 2; f * f <= b[i]; f++)
    //     {
    //         while (b[i] % f == 0)
    //         {
    //             b[i] /= f;
    //             if (pf.count(f) == 0)
    //             {
    //                 pf[f] = 1;
    //             }
    //             else
    //             {
    //                 pf[f]++;
    //             }
    //         }
    //     }
    //     if (b[i] > 1) // the element itself is a prime factor
    //     {
    //         if (pf.count(b[i]) == 0)
    //         {
    //             pf[b[i]] = 1;
    //         }
    //         else
    //         {
    //             pf[b[i]]++;
    //         }
    //     }

    //     // if (gcd_pf.empty())
    //     // {
    //     //     gcd_pf = pf;
    //     // }
    //     // else
    //     // { // find the intersection of prime factors
    //     //     for (auto &[k, v] : gcd_pf)
    //     //     {
    //     //         if (pf.count(k) == 0 && gcd_pf.count(k) > 0)
    //     //         {
    //     //             gcd_pf.erase(k);
    //     //         }
    //     //         else if (pf.count(k) > 0 && gcd_pf.count(k) > 0)
    //     //         {
    //     //             gcd_pf[k] = min(pf[k], gcd_pf[k]);
    //     //         }
    //     //         // else (if pf > 0 and gcd == 0, ignore we always want to find the intersection)
    //     //     }
    //     // }

    //     // DBG_MAP(pf);
    //     vpf.push_back(pf);
    // }
    // // DBG_MAP(gcd_pf);

    // vector<bool> left_flexibility(n, false);
    // vector<bool> right_flexibility(n, false);
    // left_flexibility[0] = true;
    // // a[0] != 1;
    // right_flexibility[n - 1] = true;
    // // a[n - 1] != 1;

    // // right flexibility
    // for (ll i = 0; i < n - 1; i++)
    // {
    //     // what is a flexibility? only when the index @i has a unique factor not present in the gcd
    //     //          i.e., a factor not present in the other
    //     for (auto &[k, v] : vpf[i])
    //     {
    //         // given a key's value, is it strictly greater than right's prime factors?
    //         if (v > 0)
    //         {
    //             if (vpf[i + 1].count(k) == 0 || vpf[i + 1][k] < v)
    //             {
    //                 right_flexibility[i] = true;
    //             }
    //         }
    //     }
    // }

    // // left flexibility
    // for (ll i = 1; i < n; i++)
    // {
    //     for (auto &[k, v] : vpf[i])
    //     {
    //         // given a key's value, is it strictly greater than right's prime factors?
    //         if (v > 0)
    //         {
    //             if (vpf[i - 1].count(k) == 0 || vpf[i - 1][k] < v)
    //             {
    //                 left_flexibility[i] = true;
    //             }
    //         }
    //     }
    // }

    // DBG_ITER(left_flexibility);
    // DBG_ITER(right_flexibility);

    // // if the last is all flexible == 1
    // // if the first is all flexible == 1
    // // if their's a chain of right flexibility to the next's left flexibility == +1
    // // ==> find the largest group (local)

    // // the following also suggests we can only get pairs of operations (which makes sense)
    // // read my own algo wrong, single one is also possible??

    // // this is wrong, you can apply operations in multiple different places as long it doesnt affect the flexibility
    // // adjacent flexibilities

    // // DUE WE JSUT HAVE TO CHECK LEFT == RIGHT FLEXIBLITY PER INDEX, THE TEST CASE WAS WARPING MY ILLUSION
    // //   THEY ARE INDEPENDENT (L<R DOES NOT MEAN SUBARRAY, ITS BEING CHECKED FOR ALL SUBARRAYS)

    // ll current_local = 0;
    // ll largest_local = 0;
    // INC(i, n)
    // {
    //     // if (i == 0 || i == n - 1)
    //     // {
    //     if (left_flexibility[i] && right_flexibility[i])
    //     {

    //         if (1 <= i && i <= n - 2)
    //         {
    //             // DBGLN(1, i, n - 2);
    //             if ((gcd(a[i - 1], a[i]) * gcd(a[i + 1], a[i])) != a[i])
    //             {
    //                 current_local++;
    //             }
    //         }
    //         else
    //         {
    //             current_local++;
    //         }
    //     }

    //     //     else
    //     //     {
    //     //         largest_local = max(largest_local, current_local);
    //     //         current_local = 0;
    //     //     }
    //     // }

    //     // if (i > 0)
    //     // {
    //     //     if (left_flexibility[i] && right_flexibility[i - 1])
    //     //     {
    //     //         current_local++;
    //     //     }
    //     //     else
    //     //     {
    //     //         largest_local = max(largest_local, current_local);
    //     //         current_local = 0;
    //     //     }
    //     // }
    // }
    // // largest_local = max(largest_local, current_local);

    // // OUT(largest_local);
    // OUT(current_local);
}

/*

7
10
2 4 8 16 32 64 128 256 256 256
2 4 8 16 32 64 128 256 256 256
10
2 4 8 16 32 64 128 256 512 512
2 4 8 16 32 64 128 256 512 512
10
2 4 8 16 32 64 128 256 384 384
2 4 8 16 32 64 128 256 384 384
2
1 1
1 1
2
69 69
69 69
2
23 69
23 69
2
7 15
7 15

0
0
1
0
0
1
2

1
6
1 2 3 6 4 5
1 2 3 6 4 5

3

1            1
2          2 1 << (2)
3          3 1
6        3 2 1        (edge case: when left and right when multiplied equals to the current exactly, its only when the factors deemed gcd on one side with the remaining factors exactly part of the gcd of the other side)
4        2 2 1 << (2)
5          5 1 << (5)

*/