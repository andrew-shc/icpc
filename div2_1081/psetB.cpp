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
    vector<ll> results_ops(t);
    vector<vector<ll>> results_indices(t);
    for (int test_case = 0; test_case < t; ++test_case)
    {
        vector<int> same; // 0 different, 1 same at 0, 2 same at 1
        int n;
        cin >> n;
        string s;
        cin >> s;

        // in reality, we do not care about the order of the binary
        vector<ll> index0;
        vector<ll> index1;
        int n0 = 0;
        int n1 = 0;

        for (int i = 0; i < n; ++i)
        {
            if (s[i] == '0')
            {
                index0.push_back(i + 1);
                n0++;
            }
            else
            {
                index1.push_back(i + 1);
                n1++;
            }
        }

        if (n % 2 == 0)
        {
            int ops;
            bool hold1;
            vector<ll> inds;
            if (n0 % 2 == 0)
            {
                // number of 0s is even, so we flip (and we begin with holding 1)
                ops = n - n0;
                hold1 = true;
            }
            else
            {
                // number of 0s is odd, so no flip (and we begin with holding 0)
                ops = n0;
                hold1 = false;
            }

            // accordion/zipping style
            for (int i = 0; i < ops; ++i)
            {
                if (hold1)
                {
                    inds.push_back(index1.front());
                    index1.erase(index1.begin());
                }
                else
                {
                    inds.push_back(index0.front());
                    index0.erase(index0.begin());
                }
                swap(index1, index0); // swap the indices since we are flipping the binary string after each ops

                hold1 = !hold1;
            }

            results_indices[test_case] = inds;
            results_ops[test_case] = ops;
        }
        else
        {
            if (n0 % 2 == 1)
            {
                vector<ll> inds;
                bool negate = false; // starting at ops == 1 (since ops == 0 means no indices to push)
                for (int i = 1; i <= n; ++i)
                {
                    int expected_n0 = negate ? n - i : i;

                    if (negate)
                    {
                        inds.push_back(index1.front());
                        index1.erase(index1.begin());
                    }
                    else
                    {
                        inds.push_back(index0.front());
                        index0.erase(index0.begin());
                    }
                    swap(index1, index0); // swap the indices since we are flipping the binary string after each ops

                    if (n0 == expected_n0)
                    {
                        results_ops[test_case] = i;
                        results_indices[test_case] = inds;
                        break;
                    }

                    negate = !negate;
                }
            }
            else
            {
                // won't work (it goes into its own separated loop that contains all 1s that can never reach to all 0s)
                results_ops[test_case] = -1;
            }
        }
    }

    for (int i = 0; i < t; ++i)
    {
        cout << results_ops[i] << endl;
        if (results_ops[i] > 0)
        {
            for (const auto &idx : results_indices[i])
            {
                cout << idx << " ";
            }
            cout << endl;
        }
    }
    return 0;
}
