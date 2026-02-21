#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_set>
#include <cmath>
#include <algorithm>
#include <utility>
#include <map>
#include <unordered_map>
#include <functional>
#include <array>

typedef long long ll;
typedef unsigned long long ull;

const long long NEG = (long long)-4e18;

using namespace std;

int main()
{
    int t;
    cin >> t;
    vector<ll> results(t);
    for (int test_case = 0; test_case < t; ++test_case)
    {
        vector<int> same; // 0 different, 1 same at 0, 2 same at 1
        int n;
        cin >> n;
        string s;
        cin >> s;

        for (int i = 1; i < n; ++i)
        {
            same.push_back(s[i] == s[i - 1]);
        }
    }

    for (const auto &res : results)
    {
        cout << res << endl;
    }
    return 0;
}
