#include <iostream>
#include <vector>
#include <climits>
#include <queue>
using namespace std;

const int INF = INT_MAX;
int r[200'005];
bool odw[200'005];
int cost[200'005];
vector<int> G[200'005];
int calc[11]; // 0 - do policzenia, 1 - policzony, 2 - nie ma takich fabryk w mieście
int n;


void bfs(int v) {

    for (int i = 1; i <= n; i++) {
        odw[i] = false;
    }

    cost[v] = 0;

    queue<int> q;
    int w;
    q.push(v);

    while (!q.empty()) {
        w = q.front();
        q.pop();

        if (odw[w])
            continue;

        odw[w] = true;

        for (size_t i = 0; i < G[w].size(); i++) {
            if (!odw[G[w][i]]) {
                cost[G[w][i]] = cost[w] + 1;
                q.push(G[w][i]);
            }
        }
    }
}

int main() {

    int a, b;
    int ilePoliczonych = 0;
    cin >> n;

    for (int i = 1; i <= 10; i++)
        calc[i] = 2;

    for (int i = 1; i <= n; i++) {
        cin >> r[i];
        calc[r[i]] = 0;
    }

    for (int i = 1; i <= 10; i++) {
        if (calc[i] == 2)
            ilePoliczonych++;
    }

    for (int i = 1; i < n; i++) {
        cin >> a >> b;
        G[a].emplace_back(b);
        G[b].emplace_back(a);
    }

    int dist = 0, distTu, kto = 0;

    for (int i = 1; i <= n; i++) {
        if (calc[r[i]] == 0) {
            ilePoliczonych++;
            calc[r[i]] = 1;
            bfs(i);
            distTu = 0;
            for (int j = 1; j <= n; j++) {
                if (r[j] == r[i] && cost[j] > distTu) {
                    distTu = cost[j];
                    kto = j;
                }
            }
            bfs(kto);
            for (int j = 1; j <= n; j++) {
                if (r[j] == r[i] && cost[j] > dist)
                    dist = cost[j];
            }
        }
        if (ilePoliczonych == 10)
            break;
    }

    cout << dist << "\n";

    return 0;
}