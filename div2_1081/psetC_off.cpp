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
    // DBG(T);
    int n, h, k;
    cin >> n >> h >> k;
    vector<int> a;
    ll sum = 0;
    ll time = 0;

    for (int i = 0; i < n; i++)
    {
        int ai;
        cin >> ai;
        a.push_back(ai);
        sum += ai;
    }

    if (h % sum == 0)
    {
        time += h / sum * n;       // all the damages summed by full magazine (unaffected by the swap)
        time += (h / sum - 1) * k; // additional reload from each magazine
        cout << time << endl;
        return;
    }
    else
    {
        time += h / sum * n;
        time += h / sum * k;
    }

    vector<int> min_ind(n);
    vector<int> max_ind(n); // reversed
    vector<int> prefix_sum(n);

    for (int i = 0; i < n; i++)
    {

        int r = n - 1 - i;
        if (i == 0 || a[min_ind[i - 1]] > a[i])
        {
            // first it. OR
            // current el is smaller than the min prev el
            min_ind[i] = i;
        }
        else // min prev el is smaller or equal to the current el
        {
            // carry over
            min_ind[i] = min_ind[i - 1];
        }

        if (i == 0 || a[max_ind[r + 1]] < a[r])
        {
            // first it. OR
            // current el is larger than the max prev el
            max_ind[r] = r;
        }
        else // max prev el is larger or equal to the current el
        {
            // carry over
            max_ind[r] = max_ind[r + 1];
        }

        if (i == 0)
        {
            prefix_sum[i] = a[i];
        }
        else
        {
            prefix_sum[i] = prefix_sum[i - 1] + a[i];
        }
    }

    // DBG_ITER(min_ind);
    // DBG_ITER(max_ind);
    // DBG_ITER(prefix_sum);
    // DBG((h % sum));
    // DBG(time);

    for (int i = 0; i < n; i++)
    {
        if (i == n - 1) // we still have to consider for the last index (where swapping doesnt help at all)
        {
            time++;
            break; // break to prevent out of bounds access
        }
        int offset = a[max_ind[i + 1]] - a[min_ind[i]];
        if (a[min_ind[i]] < a[max_ind[i + 1]] && prefix_sum[i] + offset >= h % sum)
        { // we *should* swap if the min ind within the prefix is smaller than the max outside of prefix
            // if this swap also yields the necessary damage to remove the remaining health
            time++;
            break;
        }
        else if (prefix_sum[i] >= h % sum)
        { // no swap could also work if it reaches earlier
            time++;
            break;
        }
        else
        {
            time++;
        }
    }

    // DBG(time);
    cout << time << endl;
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
