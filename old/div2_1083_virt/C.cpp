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
    int n;
    cin >> n;

    vector<vector<int>> a;

    for (int i = 0; i < n; i++)
    {
        int li;
        cin >> li;
        vector<int> ai;

        for (int j = 0; j < li; j++)
        {
            int aij;
            cin >> aij;
            ai.push_back(aij);
        }

        reverse(ai.begin(), ai.end());

        unordered_set<int> existed;
        // DBG(T);
        // DBG_ITER(ai);

        for (int j = 0; j < ai.size(); j++)
        {
            if (!existed.count(ai[j]))
            {
                existed.insert(ai[j]);
            }
            else
            {
                ai.erase(ai.begin() + j);
                j--;
            }
        }

        // DBG(T);
        // DBG_ITER(ai);
        a.push_back(ai);
    }

    // Define comparator lambda separately for readability
    auto comparator = [](const vector<int> &a, const vector<int> &b)
    {
        for (int i = 0; i < min(a.size(), b.size()); i++)
        {
            if (a[i] != b[i])
            {
                return a[i] < b[i];
            }
        }
        return a.size() < b.size(); // if all elements equal, shorter vector comes first
    };

    sort(a.begin(), a.end(), comparator);

    // DBG(T);

    // for (auto &ai : a)
    // {
    //     DBG_ITER(ai);
    // }

    vector<int> Q;

    while (!a.empty())
    {
        vector<int> smallest = a.front();
        a.erase(a.begin());

        for (auto &s : smallest)
        {
            Q.push_back(s);
            for (int i = 0; i < a.size(); i++)
            {
                for (int j = 0; j < a[i].size(); j++)
                {
                    if (a[i][j] == s)
                    {
                        a[i].erase(a[i].begin() + j);
                        j--;
                    }
                }

                if (a[i].empty())
                {
                    a.erase(a.begin() + i);
                    i--;
                }
            }
        }

        sort(a.begin(), a.end(), comparator);

        // DBG(T);

        // for (auto &ai : a)
        // {
        //     DBG_ITER(ai);
        // }
    }

    for (auto &q : Q)
    {
        cout << q << " ";
    }
    cout << endl;
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
