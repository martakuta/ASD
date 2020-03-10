#include <iostream>
#include <vector>
#include <climits>
#include <queue>

using std::cin;
using std::cout;
using std::vector;
using std::pair;
using std::priority_queue;
using std::make_pair;

#define LL long long

vector<pair<LL, LL>> G[200*1000+3];
LL odl[200*1000+3];
bool odw[200*1000+3];
const LL inf = LONG_LONG_MAX;
LL n;

void dijkstra(LL v) {
    for (LL i = 1; i <= n; i++) {
        odl[i] = inf;
        odw[i] = false;
    }
    odl[v] = 0;
    priority_queue<pair<LL, LL>> pq;
    pq.push(make_pair(0, v));
    LL cost,w;

    while (!pq.empty()) {
        cost = -pq.top().first;
        w = pq.top().second;
        pq.pop();

        if (odw[w])
            continue;
        odw[w] = true;

        for (LL i = 0; i < G[w].size(); i++) {
            LL x = G[w][i].first;
            if (odl[x] > G[w][i].second + cost) {
                odl[x] = G[w][i].second + cost;
                pq.push(make_pair(-odl[x], x));
            }
        }
    }
}

LL find_way(LL d, LL v) {
    for (LL i = 1; i <= n; i++) {
        odw[i] = false;
    }

    std::queue<pair<LL, LL>> visit;
    std::queue<LL> answer, ret;

    visit.push(make_pair(v, 0));
    answer.push(v);
    LL w, x = 0, cost;

    while (!visit.empty()) {
        w = visit.front().first;
        cost = visit.front().second;
        visit.pop();

        if (odw[w])
            continue;
        odw[w] = true;

        for (LL i = 0; i < G[w].size(); i++) {
            x = G[w][i].first;
            if (cost + G[w][i].second + odl[x] == d) {
                visit.push(make_pair(x, cost + G[w][i].second));
                answer.push(x);
            }
        }
    }

    LL poprz = 0;
    double sred = ((double)d)/2;

    while (!answer.empty()) {
        x = answer.front();
        answer.pop();

        if (odl[x] < sred)
            break;

        poprz = x;
    }

    if (odl[poprz] == sred)
        return poprz;

    double przy_x = (double)odl[x] - sred;
    double przy_poprz = (double)odl[poprz] - sred;
    if (przy_x < 0)
        przy_x = -przy_x;
    if (przy_poprz < 0)
        przy_poprz = -przy_poprz;

    if (przy_x > przy_poprz)
        return poprz;
    else if (przy_x < przy_poprz)
        return x;
    else if (x < poprz)
        return x;
    else
        return poprz;
}

int main() {

    LL a, b, d;
    cin >> n;

    for (LL i = 1; i < n; i++) {
        cin >> a >> b >> d;
        G[a].push_back(make_pair(b, d));
        G[b].push_back(make_pair(a, d));
    }

    dijkstra(1);

    LL maxi1 = 0, maxi2 = 0;
    LL wierzch1 = 1, wierzch2 = 1;

    for (LL i = 1; i <= n; i++) {
        if (odl[i] > maxi1) {
            maxi1 = odl[i];
            wierzch1 = i;
        }
    }

    dijkstra(wierzch1);

    for (LL i = 1; i <= n; i++) {
        if (odl[i] > maxi2) {
            maxi2 = odl[i];
            wierzch2 = i;
        }
    }

    LL magazyn = find_way(maxi2, wierzch2);

    cout << magazyn << "\n";

    return 0;
}
