#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define LL long long

vector<int> G[500*1000+5];
LL suma[500*1000+5]; //suma odleglosci
LL liczba[500*1000+5]; //liczba wierzcholkow od ktorych juz mam informacje
int info[500*1000+5]; //na ile informacji jeszcze czeka + ile jeszcze przekaze (1/0)

int main() {

    LL n, a, b;
    cin >> n;
    //cout << n << "_";
    int u, zostalo = n, ostatni;

    for (int i = 0; i < n - 1; i++) {
        cin >> a >> b;
        //cout << a << "*" << b << "*";
        G[a].emplace_back(b);
        G[b].emplace_back(a);
    }

    queue<int> q;

    for (int i = 1; i <= n; i++) {
        if (G[i].size() == 1) {
            q.push(i);
            info[i] = 1;
            suma[i] = 0;
            liczba[i] = 1;
            zostalo --;
        }
        else {
            info[i] = G[i].size();
            suma[i] = 0;
            liczba[i] = 0;
        }
    }

    while (!q.empty()) {
        u = q.front();
        q.pop();

        //cout << u << "(" << liczba[u] << ", " << suma[u] << "): ";

        for (auto w : G[u]) {
            //cout << ", " << w << "(" << info[w] << ", " << zostalo << ")";
            if (info[w] > 0 && !q.empty()) {
                info[w] --;
                info[u] --;
                suma[w] += suma[u] + liczba[u];
                liczba[w] += liczba[u];
                //cout << "*";
                if (info[w] == 1) {
                    q.push(w);
                    zostalo --;
                    liczba[w] ++;
                    //cout << "*";
                }
            }
            //wpp. juz byl odwiedzony
        }
        //cout << "\n";
        ostatni = u;
    }

    //cout << "ostatni: " << u << "\n";
    q.push(ostatni);

    //for (int i = 1; i <= n; i++) {
    //    cout << i << " " << liczba[i] << ", " << suma[i] << "\n";
    //}

    while (!q.empty()) {
        u = q.front();
        q.pop();

        //cout << u << "(" << liczba[u] << ", " << suma[u] << "): ";

        for (auto w : G[u]) {
            //cout << ", " << w << "(" << liczba[w] << ")";
            if (liczba[w] < n) {
                suma[w] = suma[u] + n - 2*liczba[w];
                liczba[w] = n;
                q.push(w);
                //cout << "*";
            }
            //wpp. juz jest policzony
        }
        //cout << "\n";
    }

    for (int i = 1; i <= n; i++) {
        cout << suma[i] << "\n";
    }

    return 0;
}
