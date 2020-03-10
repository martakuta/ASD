#include <iostream>
#include <climits>
using namespace std;

//const int N = 4;
const int N = 512*1024;
const int INF = INT_MAX;
int d1[2*N];
pair<int, int> d2[2*N]; //first - pierwsze wystapienie 2, second - ostatnie
int d3[2*N];
int d12[2*N]; //pierwsza dwojka po jakiejs jedynce


void czyJest() {

    //if (d1[1] < d2[1].second && d2[1].first < d3[1] && d1[1] < d3[1])
    if (d12[1] != INF && d12[1] < d3[1])
        cout << "TAK\n";
    else
        cout << "NIE\n";
}

void addToTrees(int p, int a) {
    
    if (a == 1) {
        d1[p + N - 1] = p;
        d2[p + N - 1] = make_pair(INF, -INF);
        d3[p + N - 1] = -INF;
    }
    else if (a == 2) {
        d1[p + N - 1] = INF;
        d2[p + N - 1] = make_pair(p, p);
        d3[p + N - 1] = -INF;
    }
    else {// pf (a == 3)
        d1[p + N - 1] = INF;
        d2[p + N - 1] = make_pair(INF, -INF);
        d3[p + N - 1] = p;
    }
    d12[p + N - 1] = INF;
}

void updateTrees(int p) {

    p += N - 1;

    while (p > 1) {
        p /= 2;
        d1[p] = min(d1[2*p], d1[2*p+1]);

        d2[p].first = min(d2[2*p].first, d2[2*p+1].first);
        d2[p].second = max(d2[2*p].second, d2[2*p+1].second);

        d3[p] = max(d3[2*p], d3[2*p+1]);

        if (d1[p] == INF) {
            d12[p] = INF;
        } else {
            if (d12[2*p] != INF) {
                d12[p] = d12[2*p];
            } else if (d1[2*p] != INF && d2[2*p+1].first != INF && d1[2*p] < d2[2*p+1].first) {
                d12[p] = d2[2*p+1].first;
            } else if (d12[2*p+1] != INF) {
                d12[p] = d12[2*p+1];
            } else {
                d12[p] = INF;
            }
        }
    }
}

void printTrees() {
    for (int i = 0; i < 2*N; i++) {
        cout << i << "   ";

        if (d1[i] == INF)
            cout << "- ";
        else
            cout << d1[i] << " ";

        if (d2[i].first == INF)
            cout << "- ";
        else
            cout << d2[i].first << " ";

        if (d2[i].second == -INF)
            cout << "- ";
        else
            cout << d2[i].second << " ";

        if (d3[i] == -INF)
            cout << "- ";
        else
            cout << d3[i] << " ";

        if (d12[i] == INF)
            cout << "- ";
        else
            cout << d12[i];

        cout << "\n";
    }
}



int main() {

    int n, a;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a;
        addToTrees(i, a);
    }

    for (int i = n + N; i < 2 * N; i++) {
        d1[i] = INF;
        d2[i] = make_pair(INF, -INF);
        d3[i] = -INF;
        d12[i] = INF;
    }

    for (int i = N-1; i > 0; i--) {

        d1[i] = min(d1[2*i], d1[2*i+1]);

        d2[i].first = min(d2[2*i].first, d2[2*i+1].first);
        d2[i].second = max(d2[2*i].second, d2[2*i+1].second);

        d3[i] = max(d3[2*i], d3[2*i+1]);

        if (d1[i] == INF) {
            d12[i] = INF;
        } else {
            if (d12[2*i] != INF) {
                d12[i] = d12[2*i];
            } else if (d1[2*i] != INF && d2[2*i+1].first != INF && d1[2*i] < d2[2*i+1].first) {
                d12[i] = d2[2*i+1].first;
            } else if (d12[2*i+1] != INF) {
                d12[i] = d12[2*i+1];
            } else {
                d12[i] = INF;
            }
        }
    }

    //printTrees();

    czyJest();

    int m, p;
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> p >> a;
        addToTrees(p, a);
        updateTrees(p);
        //printTrees();
        czyJest();
    }

    return 0;
}