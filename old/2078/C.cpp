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

// rephrase: find a pairwise-distinct array a with a1=a2-a3+a4-.... from b
//                where b is the arbitrarily-shuffled version of a (with one of the element in a removed)
// rephrase: a is the shuffled version b with an extra arbitrary element
// key difficulty: pairwise distinct (i.e., every element is unique)

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// vvvvvvvvvvvvvv ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// strat
// find the -,+,- sum and let that sum be a1
// but, if the sum is already in the element
//  we can let ~~~~~

// ~~~~~~~~~~~~~~~~~ O.1: if the sum is in b[] => there's larger +'s then -'s => ???

// O.1: since a[] goes from 1 to 2n+1 => there will always be a subtraction at the end
//      O.1.1: => n -'s and (n-1) +'s
// O.2: if the sum is in b[] => there's a + that when replaced with a 0 (impossible) the *remaining sum* is 0
//          O.2.1: we can let the minimum - go down by the max of +'s + 1 and let the + be the max of +'s +1
//                      since given the input constraint, b is smaller than the allowed range of a

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// severely misunderstood the problem, you CANNOT modify any elements in the array
// you can ONLY RE-ORDER THEM

// O.1: if the sum given the current order AS IS is NOT in b[] and is positive => just insert the sum in the beginning
// O.1: if the sum S is negative => re-order s.t. all the largest values are on the +'s and smallest on the the -'s (to create a new max)
// O.2: if the sum given the current order AS IS is IN b[] => got to find a new order where the sum is not in b[]
//      O.2.1: that means if we remove the current element that is the sum, the remaining sum is 0
//      O.2.2: => put all the largest values on the +'s and the smallest values on the -'s to ensure max is reach
//      O.2.3: => if the sum IS the max, swap the smallest largest (in +) with the largest smallest (in -)
//                  since they're distinct, the sum S (which is also the max) will be reduced a bit
//                  Q.2.3.1 is this new sum unique / pairwise distinct?
//              9 1 8 2 7 3 6 4 = 30-10 = 20
//              l
//                  O.2.3.2: the max can never be in the array b => we can always re-shuffle to produce a max to compute the sum S
//                  O.2.3.3: but that's only when there's +'s, but we also have -'s. what this means is if there's a max, we can only go down (not up like before)
//

// it's literally just sorting the array and putting half largest on the +'s and half smallest on the -'s and copmuting the sum S and inserting it in the beginning
// literally bruh moment

// ~~~~~~~~~~~~~~~~~ ^^^^^^^^^^^^ ~~~~~~~~~~~~~~~~~~~~~~

// redo again

/*
the new strat

ASSUMING pair-wise distinctness
we re-order to put all top half largest on +'s and bottom half smallest on -'s => ensure the sum is the largest (which must be positive)

however, this does not ensure uniqueness since this sum can still equal to a *duplicate* largest in the top half
        if we remove the largest in b, because of the +/-'s, we will have more -'s (too long to prove)

so, we let t


// skip the proof; impl directly (with some guessing)


*/

// the ultimate counter-example
/*

a 9 11 8 10 7 9 6
where b is
    11 8 10 7 9 5 (yes, the sum is in b and its actually not always the first but can happen anywhere)
        is it possible to make a bandage where we just find the match

*/

/*
new observation (after aligning from +largest of the top half with -smallest of the bottom half to
                                     +largest of the top half with -largest of the bottom half)
    which revealed the following property

if we do top half - bottom half => the min sum is n^2
 and the elements are perfect

*/

// check editorial (it's a 1500, struggling a lot on 1500)

/*
just because these special conditions are next to these basic conditions like constraints
DOES NOT MEAN they are not as important or not much to observer or think about as the
    basic range-based constraints (which truly does not have much to think about)

we can observe and think about the condition of the summation and rewrite it as
a2n = a1 + (a3-a2)+ (a5-a4) + ... + (a2n-1-a2n-2) + a2n+1
    KEY IDEA: we move the + on the RHS to the LHS so the whole thing becomes reversed with more +'s then -'s

    MORE +'s then -'s

so, as long we put all the largest number on the positives, the sum is always positive
AND if we put a1 as the largest, we can always show that a2n will be larger than the max => distinct, unique

reverse engineering:
    we basically want a2n to be the largest while having the sum being the pre-existing largest element
        BY HAVING ALL THE NEXT LARGEST NUMBER ON THE NEGATIVES (the idea makes sense now, you have the max on the sum,
            now the remaining + element MUST the largest despite rest of the +'s having the smallest)

            these contradictions appear everywhere

the strat:

put the largest on a1 and the next largest on the evens (except a2n)
put the remaining smallest on the odds
put a2n as the calculated sum

*/

void solve([[maybe_unused]] ll T)
{
    READ(n);
    READ_VLL(b, 2 * n);

    sort(b.begin(), b.end());

    ll sum = b[2 * n - 1];
    INC(i, n - 1)
    {
        sum += b[2 * n - 2 - i]; // excludes n-1
        sum -= b[i];             // excludes n-1
    }
    sum += b[n - 1];

    vll a;
    a.push_back(b[2 * n - 1]);
    INC(i, n - 1)
    {
        a.push_back(b[i]);
        a.push_back(b[2 * n - 2 - i]);
    }
    a.push_back(sum);
    a.push_back(b[n - 1]);

    OUT_ITER(a);

    // vll a;
    // ll sum = 0;
    // INC(i, n)
    // {
    //     // instead of constructing it as from the extremes
    //     // let us construct it as from top half and bottom half from right to left

    //     a.push_back(b[2 * n - 1 - i]); // +
    //     // a.push_back(b[i]);             // -
    //     a.push_back(b[n - 1 - i]); // -
    //     sum += b[2 * n - 1 - i] - b[i];
    // }
    // auto sum_it = find(a.begin(), a.end(), sum);
    // // if (sum == b[2 * n - 1])
    // if (sum_it != a.end()) // what happens if the sum matches to a (-) element in a?
    //                        // => it means we will have a duplicate
    //                        // => but the following method of inverting should fix it?
    //                        // => if we take the original duplicate sum (which actually can be a negative element)
    //                        //       if it is a negative element, we are taking it from a negative slot => dud

    // { // if the sum is as large as the largest
    //     // => make the sum smallest (invert it), move the duplicate to a1 (so expect the sum to be the largest)
    //     //        and, insert a new element where it is a1+ the "smallest" (which is the largest after inversion)
    //     //        which ensures uniqueness
    //     int sum_idx = sum_it - a.begin();

    //     // sum can technically be anywhere (intuition wrong)
    //     // ~~~~~~~~~~~~~~~~~~~~~~we can move the largest negative
    //     //        move the duplicate positive to the beginning (as our new sum)
    //     // expect to insert our new element in the duplicate positive's original position
    //     // we can move the largest negative @+1 to the end (as before)
    //     //      we can re-apply rotate again after calculating everything
    //     // but ensure the duplicate positive's original position is returned
    //     //      if we do a left rotate, the duplicate positive's should be swapped to its adjacent right
    //     //  ~~~~~~~~~~~^^^^^^^
    //     // we got to swap the biggest negative's location @+1 to right after duplicate positive's position
    //     // then, we move the duplicate positive to the beginning
    //     // then, our new counter-acting new element will be placed at the duplicate positive position
    //     //  left rotate
    //     //  ensure it stays

    //     ll old_sum = sum;
    //     sum -= b[2 * n - 1];
    //     sum *= -1;
    //     sum -= 2 * b[n - 1];

    //     // move new element into dup. pos.
    //     a[sum_idx] = old_sum - sum;
    //     // swap biggest negative to some random negative right after dup. pos. (to ensure the largest neg. stays)
    //     swap(a[1], a[sum_idx + 1]);

    //     // then, the dup. pos. reappears in the begining
    //     a.insert(a.begin(), old_sum);

    //     // apply left rotate  from the 1st index and onwards
    //     // at the end

    //     // moving in the new element and moving out the old duplicate positive to the beginning
    //     // a[sum_idx] = old_sum - sum;
    //     // // a.insert(sum, a[0] - sum);
    //     // a.insert(a.begin(), old_sum);

    //     // swap the biggest negative to right after duplicate positive's position

    //     // // we have our a1 inserted and our a2 (the old_sum-sum)
    //     // rotate(a.begin() + 2, a.begin() + 3, a.end());
    //     rotate(a.begin() + 1, a.begin() + 2, a.end()); // rotate to a.begin()+2
    //     // exclude the first element (the largest which will be our new target sum as a1)
    //     // rotate left, this will rotate the largest +'s into -'s while also keeping the single largest - (in the beginning) as - (the last) (ensuring smallest)

    //     // sum *= -1;

    //     // if we remove the first +, there will be more -, and we want the largest element to be on -
    //     //  this is basically inverting the sum yes, but also we're removing the smallest
    //     //      so we move the next largest element to be inverted and add as smallest
    //     //      => yes, we invert the sum. we remove the largest. but we also move an element to cross the +/- boundary.

    //     // +,-
    //     // sum -= b[2 * n - 1];
    //     // sum *= -1;
    //     // sum -= 2 * b[n - 1]; // originally, it was barely in the - region. however, after inversion, it became positive.
    //     //      but recall we remove an element from the + region, so we can move an element from - to the + (or after inversion, + to -)
    //     //      and so the element originally barely in the - region is the element that will be converted from + to - (after inversion)

    //     // so the largest is a1 and the new smallest sum is calculated
    //     // the new element at a2 shall be a1+smallest sum (to cancel out the sum and to ensure the a1 sum is achieved)
    //     //  which is ensured to be unique
    //     // a.insert(a.begin() + 1, a[0] - sum); // since we already added the largest but removed it from the original b-partition
    //     // make sure its -sum (since the sum is now the minimum, we want to cancel its effect)
    //     OUT_ITER(a);
    // }
    // else
    // {
    //     a.insert(a.begin(), sum);

    //     OUT_ITER(a);
    // }

    // for (ll i = 1; i < 2 * n; i += 2)
    // {
    //     b[i] *= -1;
    // }
    // // make the array in +-+-+- as if there will be another element appended in the beginning

    // ll sum = accumulate(b.begin(), b.end(), 0);
    // auto sum_it = find(b.begin(), b.end(), sum);
    // auto [mn_it, mx_it] = minmax_element(b.begin(), b.end());
    // // if (sum_it != b.end())
    // // {
    // //     // found the sum in the array b
    // //     // removing the element that is the sum (S>0), we get the remaining sum to be 0
    // //     //      - pick the max and pick the min (sign corrected / maybe 0 from the previous op but at most a single 0 exists)
    // //     //      - subtract the min with another (max+1) and add the 0 with (max+S) (which is guaranteed to be positive)
    // //     //          => this ensures the new numbers are distinct (more smaller than the min and more larger than the max)
    // //     //          => while also ensuring the remaining sum equals the element same (we subtract an additional max+1 while also adding an additional max+1)
    // // }
    // // else
    // // {
    // // sum not found => append the sum in the beginning
    // //  if the sum S is <=0, add (max+1)-S to the max to
    // //      ensure pairwise distinct where max=max+(max+1-S) and S=max+1

    // // wait, cant we put the duplicate sum in this case also?
    // // if sum S found in b (regardless if its the max or not), we got to change an element not the S (changing the element S itself will also the change the sum exactly)
    // //      ^ happens when the +'s or the -'s are split on the opposite sign
    // //   we can decrement a min and increment a max by 2 => this clearly ensures pairwise distinctness
    // //      since the made a new minimum, a new maximum by increasing it by 2, and a new sum that is only increased by 1
    // //      however, S+1 might exist if S is not the max, so, we do S=S+max
    // ///     and to achieve that, we re-apply the whole thing again netting us...
    // //      max = max+max+max
    // //      min = min-max
    // //        S = S+max
    // //        => clearly ensures pairwise distinctness (since S>0 and max>0 and min<0)

    // // ~~~~~~~~~~~~~~~~~~~~
    // // if sum S found in b, max = max+max => the new sum S'=S+max
    // //      ensures pairwise distinct since S>0
    // //      EXCEPT when the sum is in the b AND IS THE MAX

    // // there's a problem, |min|>|max|, so we should be doing max(abs(min),max)
    // //      (what if we let the sum be min accidentally since we internally treat them as negatives?)

    // ll r = max(abs(*mn_it), *mx_it);
    // if (sum_it != b.end())
    // { // pairwise distinctness since S>0,max>0,min<0 by input constraint (assumption)
    //     *mx_it += r + r;
    //     *mn_it -= r;
    //     sum += r;
    // }
    // else if (sum <= 0)
    // { // S>0, so the max will reach to the new max and sum will reach between the old max (take its place) or higher (if the min is lower)
    //     // but what if the r+1>max and S is quite low, will the sum reach to the new max??? (create duplicate values?)
    //     // REMEMBER S>0 I MEAN -(s) > 0 (MISUNDERSTOOD MY OWN REASONING)
    //     *mx_it += r + 1 - sum; // previous sum is negative so this must be positive
    //     sum = r + 1;
    // }

    // // now we assume the sum is always positive and valid for the construction of a

    // vll a(2 * n + 1, 0);

    // a[0] = sum;
    // INC(i, 2 * n)
    // {
    //     a[i + 1] = abs(b[i]);
    // }

    // OUT_ITER(a);
    // // }
}