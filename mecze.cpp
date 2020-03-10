#include <iostream>
#include <algorithm>
using std::cin;
using std::cout;
using std::string;

long long tab[40*1000+1];

int main() {
    std::ios_base::sync_with_stdio(false);

    int n, m, nr;
    cin >> n >> m;

    for (int i=1; i<=n; i++)
        tab[i] = 0;
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            cin>> nr;
            tab[nr] *= 2;
            if (j >= n/2)
                tab[nr] += 1;
        }
    }

    std::sort(tab+1,tab+n+1);

    for (int i=2; i<=n; i++) {
        if (tab[i] == tab[i-1]) {
            cout << "NIE\n";
            return 0;
        }
    }

    cout << "TAK\n";
    return 0;
}