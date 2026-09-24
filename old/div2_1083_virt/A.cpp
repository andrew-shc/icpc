#include <bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

const long long NEG = (long long)-4e18;

using namespace std;

void solve(ll T)
{
    int n;
    cin >> n;

    int p[n];
    int max_ind;
    for (int i = 0; i < n; i++)
    {
        int pi;
        cin >> pi;
        p[i] = pi;

        if (pi == n)
        {
            max_ind = i;
        }
    }

    int tmp = p[0];
    p[0] = p[max_ind];
    p[max_ind] = tmp;

    for (int i = 0; i < n; i++)
    {
        cout << p[i] << " ";
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
