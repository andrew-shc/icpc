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

void solve(ll T)
{
    ull s, m;
    cin >> s >> m;

    ull c[61] = {0}; // c form of s

    for (int i = 60; i >= 0; i--)
    {
        if (((s >> i) & 1) || c[i])
        {
            int actual = ((s >> i) & 1);

            // ith bit is present in s
            if ((m >> i) & 1)
            {
                // m supports the ith bit
                c[i] += actual;
            }
            else
            {
                // m does not support the ith bit
                if (i == 0)
                {
                    cout << -1 << endl;
                    return;
                }
                else
                {
                    c[i - 1] += (c[i] + actual) * 2;
                    c[i] = 0;
                }
            }
        }
    }

    // DBG(T);
    // DBG_ITER(c);

    // we already now max c works so we're just skipping a step
    // if mid works => try smaller values to minimize; if mid doesn't work => try bigger value to ensure it works again
    //    monotonicity enables this (almost like Newton's method or those root approximation method)
    ull left = 0;
    ull right = *max_element(begin(c), end(c));
    ull mid;
    ull prev_successful_mid = *max_element(begin(c), end(c));

    while (left <= right)
    {
        mid = left + (right - left) / 2;
        // DBG(mid);
        // DBG(prev_successful_mid);

        // find if mid works

        ull c_mid[61];
        memcpy(c_mid, c, sizeof(c));

        bool failed = false;

        for (int i = 60; i >= 0; i--)
        {
            // NOTE: bitwise operations are really very different from logical ops
            if ((((m >> i) & 1) != 1) && c_mid[i] > 0)
            {
                // ith bit not supported by m (but c has values in it)
                if (i == 0)
                {
                    // failed to meet the requirement
                    failed = true;
                    break;
                }
                else
                {
                    c_mid[i - 1] += c_mid[i] * 2;
                    c_mid[i] = 0;
                }
            }
            else if (c_mid[i] > mid)
            { // ith bit supported by m but doesnt fit within mid
                if (i == 0)
                {
                    // failed
                    failed = true;
                    break;
                }
                else
                {
                    c_mid[i - 1] += (c_mid[i] - mid) * 2;
                    c_mid[i] = mid;
                }
            }
        }
        // DBG_ITER(c_mid);

        if (failed)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }

        // if (left == mid) // due to floor division, the final state will always be whenever the mid is LOW
        // {
        //     if (failed)
        //     {
        //         // failed at the last step (back track to the most recent success)
        //         cout << prev_successful_mid << endl;
        //     }
        //     else
        //     {
        //         // success at the last step
        //         cout << mid << endl;
        //     }
        //     return;
        // }

        // if (failed)
        // {
        //     left = mid;
        // }
        // else
        // {
        //     right = mid;
        //     prev_successful_mid = mid;
        // }
    };

    cout << left << endl;

    // // we only need to check if the least sig. bit of m supports s (least sig. bit of m at least divides s)
    // // almost like checking if m provides us enough resolution to obtain s
    // for (int i = 0; i < 64; i++)
    // {
    //     if (m >> i & 1)
    //     {
    //         if (s % (1 << i))
    //         {
    //             // enough res
    //             break;
    //         }
    //         else
    //         {
    //             // the only case if we can't construct the array (because resolution too low to fit s)
    //             cout << -1 << endl;
    //             return;
    //         }
    //     }
    // }
}

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
