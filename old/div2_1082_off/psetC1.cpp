#include <bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

const long long NEG = (long long)-4e18;

using namespace std;

void solve()
{
    int n;
    cin >> n;
    // int a[n];

    vector<ll> seq;
    ll min = -1; // ie first element
    ll last_el = -1;

    for (int i = 0; i < n; i++)
    {
        ll ai;
        cin >> ai;
        // a[i] = ai;

        if (min + 1 <= ai && ai <= last_el + 1)
        {
            // in the valid range from pre-existing increments
            // it can only increase the max by 1 <--- WE DO NOT CARE ABOUT MAX, since
            //    that suggests a smaller element (smaller by more than 1) before the MAX can exist, which does
            //    not work with the algo
            // ONLY set last element by ai

            // pass
        }
        else
        {
            // outside the available range
            seq.push_back(ai);
            min = ai;
        }
        last_el = ai;
    }

    cout << seq.size() << endl;
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
        solve();
    }

    return 0;
}
