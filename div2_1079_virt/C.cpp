#include <bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

const long long NEG = (long long)-4e18;

#define DBG(...)                                     \
    do                                               \
    {                                                \
        std::cout << "[" << #__VA_ARGS__ << "] = ["; \
        _dbg_print(__VA_ARGS__);                     \
        std::cout << "]" << std::endl;               \
    } while (0)

template <typename T>
void _dbg_print(T &&t) { std::cout << t; }

template <typename T, typename... Args>
void _dbg_print(T &&t, Args &&...args)
{
    std::cout << t << ", ";
    _dbg_print(args...);
}
#define DBG_ITER(arr)           \
    do                          \
    {                           \
        cout << #arr << " = ["; \
        bool _dbg_first = true; \
        for (auto &x : arr)     \
        {                       \
            if (!_dbg_first)    \
                cout << ", ";   \
            cout << x;          \
            _dbg_first = false; \
        }                       \
        cout << "]" << endl;    \
    } while (0)

using namespace std;

void solve(ll T);

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    ll T = 1;

    cin >> T;

    while (T--)
    {
        solve(T);
    }

    return 0;
}

void solve(ll T)
{
    ull p, q;
    cin >> p >> q;

    if (p % 2 == 0 && q % 3 == 0 && p / 2 == q / 3)
    {
        cout << "Bob" << endl;
    }
    else if (p / 2 > q / 3)
    {
        // if the numerator is relatively larger wrt 2/3, Alice can always pick the denom.
        // Bob cant bring the number down by picking the num. enough times

        // CORRECTION: Bob CAN bring it down due to the fact that numerator can be brought down
        // quicker (in halves) then a denominator which is in thirds.
        // assume the optimal strat here is Alice always denom. and Bob always num.
        // if Alice chooses num., Bob can always choose denom. to cancel the effect (preventing overshooting)

        if (p % 2 == 0 && q % 3 == 1)
        {
            // (num offset, denom offset) (0,1) -> (0,0) -> (1,0) -> (1,2) -> (0,2) -> (0,1) -> (1,1) -> (1,0)
            // after 5 turns same thing again but opposite turns

            // this brings p to an integer factor down faster than q can
            cout << "Alice" << endl;
        }
        else if (p % 2 == 0 && q % 3 == 2)
        {
            // same as above
            cout << "Alice" << endl;
        }
        else if (p % 2 == 1 && q % 3 == 1)
        {
            // whatever Alice chooses, Bob can choose the remaining one with 1 offset
            cout << "Bob" << endl;
        }
        else if (p % 2 == 1 && q % 3 == 2)
        {
            // Alice must pick p
            cout << "Alice" << endl;
        }
    }
    else if (p / 2 < q / 3)
    {
        // if the denom. is relatively larger wrt 2/3, Alice can always pick the num.
        // Bob cant bring the number up by picking the denom. enough times
        cout << "Alice" << endl;
    }
    else
    { // p / 2 == q / 3 but each are not divisible by 2, 3 respectively (very close)
        // so same integer k factor (up to flooring)
        // recall, Alice gets to go first
        if (p % 2 == 0 && q % 3 == 1)
        {
            // this brings p to an integer factor down faster than q can
            cout << "Alice" << endl;
        }
        else if (p % 2 == 0 && q % 3 == 2)
        {
            // same as above
            cout << "Alice" << endl;
        }
        else if (p % 2 == 1 && q % 3 == 1)
        {
            // whatever Alice chooses, Bob can choose the remaining one with 1 offset
            cout << "Bob" << endl;
        }
        else if (p % 2 == 1 && q % 3 == 2)
        {
            // Alice must pick p
            cout << "Alice" << endl;
        }
    }
}