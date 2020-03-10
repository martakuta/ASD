#include <iostream>
#include <queue>

using std::cin;
using std::cout;
using std::pair;
using std::make_pair;
using std::vector;
using std::priority_queue;
using std::max;

#define mp make_pair

const int N = 100*1000 + 5;
int ilu_prog[N];
vector<int> sas[N];
int ilu_sas[N];
priority_queue<pair<int, int>> pq;

int main() {

    std::ios_base::sync_with_stdio(false);

    int n, m, k, a, b;
    cin >> n >> m >> k;

    for (int i = 0; i < n; i++) {
        cin >> ilu_prog[i];
        ilu_sas[i] = 0;
    }

    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        a--;
        b--;
        sas[b].push_back(a);
        ilu_sas[a]++;
    }

    for (int i = 0; i < n; i++) {
        if (ilu_sas[i] == 0)
            pq.push(mp(-ilu_prog[i], i));
    }

    int zrobione = 0;
    int ilu_zatrudnic = 0;

    while (zrobione < k) {
        int projekt = pq.top().second;
        int programisci = - pq.top().first;
        pq.pop();

        ilu_zatrudnic = max(ilu_zatrudnic, programisci);
        zrobione ++;

        for (int sasiad : sas[projekt]) {
            ilu_sas[sasiad] --;
            if (ilu_sas[sasiad] == 0)
                pq.push(mp(-ilu_prog[sasiad], sasiad));

        }
    }

    cout << ilu_zatrudnic << "\n";

    return 0;
}