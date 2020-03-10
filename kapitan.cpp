#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <climits>

using std::vector;
using std::pair;
using std::make_pair;
using std::priority_queue;
using std::cin;
using std::cout;

#define para pair<int, pair<int, int>>
#define x second.first
#define y second.second
#define id first
#define INF INT_MAX

const int liczba_wysp = 200*1000;
vector<pair<int,int>> G[liczba_wysp];
long long odl[liczba_wysp];
bool odw[liczba_wysp];
int n;
para wyspa[liczba_wysp];



//jesli zwroci true to a zostanie posortowane jako pierwsze (mniejsze)
bool cmp_x (const para& a, const para& b) {
    return a.x < b.x;
}
bool cmp_y (const para& a, const para& b) {
    return a.y < b.y;
}
bool cmp_id (const para& a, const para& b) {
    return a.id < b.id;
}



void dijkstra () {

    int v = 0;

    for (int i=0; i<n; i++) {
        odl[i] = INF;
        odw[i] = false;
    }

    odl[v] = 0;
    priority_queue <pair<int, int>> q;
    int u, w, cost;
    q.push (make_pair(0, v));

    while (!odw[n-1]) {

        u = q.top().second;
        cost = - q.top().first;
        q.pop();

        if (odw[u] == 1) continue;
        odw[u] = true;

        for (const auto& e : G[u]) {
            w = e.second;
            if (cost + e.first < odl[w]) {
                odl[w] = cost + e.first;
                q.push(make_pair (-odl[w], w));
            }
        }
    }
}

int main() {

    std::ios_base::sync_with_stdio(false);

    cin>> n;
    for (int i=0; i<n; i++) {
        cin >> wyspa[i].x >> wyspa[i].y;
        wyspa[i].id = i;
    }

    sort(wyspa, wyspa+n, cmp_x);

    //dodaje lewych i prawych najblizszych
    G[wyspa[0].id].emplace_back(make_pair(wyspa[1].x - wyspa[0].x, wyspa[1].id));
    G[wyspa[n-1].id].emplace_back(make_pair(wyspa[n-1].x - wyspa[n-2].x, wyspa[n-2].id));
    for (int i=1; i<n-1; i++) {
        G[wyspa[i].id].emplace_back(make_pair(wyspa[i].x - wyspa[i-1].x, wyspa[i-1].id));
        G[wyspa[i].id].emplace_back(make_pair(wyspa[i+1].x - wyspa[i].x, wyspa[i+1].id));
    }

    sort(wyspa, wyspa+n, cmp_y);

    //dodaje gornych i dolnych najblizszych
    G[wyspa[0].id].emplace_back(make_pair(wyspa[1].y - wyspa[0].y, wyspa[1].id));
    G[wyspa[n-1].id].emplace_back(make_pair(wyspa[n-1].y - wyspa[n-2].y, wyspa[n-2].id));
    for (int i=1; i<n-1; i++) {
        G[wyspa[i].id].emplace_back(make_pair(wyspa[i].y - wyspa[i-1].y, wyspa[i-1].id));
        G[wyspa[i].id].emplace_back(make_pair(wyspa[i+1].y - wyspa[i].y, wyspa[i+1].id));
    }

    sort(wyspa, wyspa+n, cmp_id);

    dijkstra();

    cout << odl[n-1];

    return 0;
}