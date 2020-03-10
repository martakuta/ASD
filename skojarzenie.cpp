#include <iostream>
#include <vector>
#include <climits>
using namespace std;

const int INF = INT_MAX;

vector<pair<int, int>> G[100'005];
int opt[50'005];

//zwraca -1 jesli krawedz nie istnieje, wpp wage znalezionej krawedzi
int znajdzKrawedz(int a, int b) {
    for (auto edge : G[a]) {
        if (edge.first == b)
            return edge.second;
    }
    return -1;
}

int main() {

    int n, m, a, b, u, w, x, y, z, j;
    cin >> n >> m;
    //cout << n << "*" << m << "_";

    if (n % 2 == 1) {
        cout << "-1\n";
        return 0;
    }


    for (int i = 0; i < m; i++) {
        cin >> a >> b >> w;
        //cout << a << "-" << b << "-" << w << "*";
        G[a].emplace_back(make_pair(b, w));
        G[b].emplace_back(make_pair(a, w));
    }

    u = znajdzKrawedz(1,2);
    y = znajdzKrawedz(1, 3);
    z = znajdzKrawedz(2, 4);
    if (u == -1) {
        /*if (y == -1 || z == -1) {
            cout << "-1\n";
            return 0;
        }
        else {*/
        opt[1] = INF;
        //}
    }
    else {
        opt[0] = 0;
        opt[1] = u; // 2/2 = 1
    }

    for (int i = 4; i <= n; i += 2) {

        j = i / 2;

        x = znajdzKrawedz(i-1, i);
        y = znajdzKrawedz(i-1, i-3);
        z = znajdzKrawedz(i, i-2);

        if (opt[j - 1] == INF && (y == -1 || z == -1)) {
            cout << "-1\n";
            return 0;
        }

        if (x == -1) {
            if (y == -1 || z == -1 || opt[j - 2] == INF)
                opt[j] = INF;
            else
                opt[j] = opt[j - 2] + y + z;
        }
        else if (y == -1 || z == -1) {
            opt[j] = opt[j - 1] + x;
        }
        else {
            if (opt[j - 1] == INF)
                opt[j] = opt[j - 2] + y + z;
            else if (opt[j - 2] == INF)
                opt[j] = opt[j - 1] + x;
            else if (opt[j - 2] + y + z < opt[j - 1] + x)
                opt[j] = opt[j - 2] + y + z;
            else
                opt[j] = opt[j - 1] + x;
        }
    }

    cout << opt[n / 2] << "\n";

    return 0;
}