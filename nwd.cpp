#include <iostream>
#include <map>
using namespace std;

//const int M = 4;
const int M = 1024*128;
int d[2*M];
map<int, int> m;

int nwd(int a, int b) {
    if (a < b)
        swap(a, b);
    if (b == 0)
        return a;
    return nwd(b, a%b);
}

int add(int gdzie, int v) {

    gdzie += M;
    d[gdzie] = v;
    while (gdzie > 1) {
        gdzie /= 2;
        if (d[gdzie*2+1] == 0)
            d[gdzie] = d[gdzie*2];
        else
            d[gdzie] = nwd(d[gdzie*2], d[gdzie*2+1]);
    }
    return d[1];
}

int del(int gdzie, int v) {
    return add(gdzie, v);
}

int delLast(int ile) {

    int gdzie = ile + M;
    int deleted = d[gdzie];
    d[gdzie] = 0;
    while (gdzie > 1) {
        gdzie /= 2;
        if (d[gdzie*2+1] == 0)
            d[gdzie] = d[gdzie*2];
        else
            d[gdzie] = nwd(d[gdzie*2], d[gdzie*2+1]);
    }
    return deleted;
}

int main() {

    int n, v, ile = 0;
    char c;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> c >> v;
        if (c == '+') {
            cout << add(ile, v) << "\n";
            m[v] = ile;
            ile++;
        }
        else { //means that c == '-'

            int last = delLast(ile-1);
            ile--;
            int gdzie = m[v];
            m[last] = gdzie;
            m[v] = -1;
            if (ile == 0)
                cout << "1\n";
            else if (gdzie == ile)
                cout << d[1] << "\n";
            else
                cout << del(gdzie, last) << "\n";
        }
        /*for (int j = 1; j <= 2*M; j++)
            cout << d[j] << " ";
        cout << "\n";*/
    }

    return 0;
}