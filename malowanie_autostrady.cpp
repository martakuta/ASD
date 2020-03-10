#include <iostream>

using std::cin;
using std::cout;

const int M = 1024*1024;
int d[2*M];
bool ozn[2*M];
int p[2*M];
int k[2*M];

void policz_pk(int pole, int pocz, int kon) {

    p[pole] = pocz;
    k[pole] = kon;
    ozn[pole] = false;
    d[pole] = 0;

    int srod = (pocz+kon)/2;

    if (pole < M) {
        policz_pk(pole*2, pocz, srod);
        policz_pk(pole*2+1, srod+1, kon);
    }

}

void maluj(int pole, int a, int b, int c) {

    //cout << "maluj " << p[pole] << "-" << k[pole] << " / " << a << "-" << b << "\n";

    if (pole > 2*M)
        return;

    if (p[pole]==a && k[pole]==b) {
        //cout << "to jest to!  ";
        ozn[pole] = true;
        d[pole] = (b-a+1) * c;
        //cout << "d[pole] = " << d[pole] << "\n";
        return;
    }

    int s = (p[pole]+k[pole])/2;

    if (ozn[pole]) {
        //cout << "oddaje swoje oznaczenie synom\n";
        ozn[pole] = false;
        ozn[pole*2] = true;
        ozn[pole*2+1] = true;
        d[pole*2] = d[pole] / 2;
        d[pole*2+1] = d[pole] / 2;
    }

    if (b <= s) {
        maluj(2 * pole, a, b, c);
    }
    else if (a > s) {
        maluj(2 * pole + 1, a, b, c);
    }
    else {
        maluj(2 * pole, a, s, c);
        maluj(2 * pole + 1, s + 1, b, c);
    }

    if (pole < M) {
        d[pole] = d[pole * 2] + d[pole * 2 + 1];
        //cout << "-------------- suma w polu " << p[pole] << "-" << k[pole] << " wynosi " << d[pole] << "\n";
    }
}

int main() {

    int n, m, a, b;
    char c;
    cin >> n >> m;

    policz_pk(1, 1, M);

    for (int i = 0; i < m; i++) {

        cin >> a >> b >> c;
        //cout << "otrzymalem " << a << " " << b << " " << c << "\n";

        int color;
        if (c == 'B')
            color = 1;
        else
            color = 0;

        maluj(1, a, b, color);

        cout << d[1] << "\n";
    }

    return 0;
}