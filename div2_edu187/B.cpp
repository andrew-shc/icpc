#include <bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

const long long NEG = (long long)-4e18;

using namespace std;

void solve()
{
    ull x;
    cin >> x;
    int digits = (int)log10(x) + 1;

    if (digits == 1)
    {
        cout << 0 << endl;
        return;
    }

    int digits_kind[10] = {0};
    int sum = 0;

    for (int i = 0; i < digits; i++)
    {
        int digit = (x / (ull)(pow(10, i))) % 10;

        if (i + 1 == digits)
        {
            // last digit must keep 1 (no leading 0s)
            digits_kind[digit - 1]++;
        }
        else
        {
            digits_kind[digit]++;
        }
        sum += digit;
    }

    ull moves = 0;

    // cout << "####" << x << endl;

    // can't remove 0s (pointless)
    for (int i = 9; i > 0; i--)
    {
        if ((sum - digits_kind[i] * i) > 9)
        {
            moves += digits_kind[i];
            sum -= digits_kind[i] * i;
        }
        else if ((sum - digits_kind[i] * i) < 9)
        {
            int min_di = (int)ceil((double)(sum - 9) / (double)i);
            // cout << "XX" << min_di << endl;
            moves += min_di;
            sum -= min_di * i;
            digits_kind[i] -= min_di;
        }
        else
        {
            // == 9
            moves += digits_kind[i];
            break;
        }

        if (sum <= 9)
        {
            break;
        }
    }

    cout << moves << endl;
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
