#include <iostream>

const int mod = 1000*1000*1000 + 7;

bool szereg[100*1000+5];

struct node {
    node *parent, *lson, *rson;
    unsigned long long rr, gr, rg, gg;
    bool gal; //true - Gal, false - Rzymianin
    int l, r;
    bool rev;
};

void print_tree_inorder(node* t) {

    if (t == nullptr)
        return;

    print_tree_inorder(t->lson);
    std::cout << " " << t->gal << "  |  " << t->rev << "  | " << t->l << " | " << t->r << " | ";
    std::cout << t->rr << ", " << t->gr << ", " << t->rg << ", " << t->gg << "\n";
    print_tree_inorder(t->rson);
}

void print_tree(node* t) {

    std::cout << "gal | rev | l | r | rr,gr,rg,gg\n";
    print_tree_inorder(t);
    std::cout << "_______________________________\n\n";
}

int how_many_sons(node* t) {

    int sum = 0;

    if (t != nullptr)
        sum = t->l + t->r + 1;

    return sum;
}

void count_sons(node* t) {

    if (t != nullptr) {
        t->l = how_many_sons(t->lson);
        t->r = how_many_sons(t->rson);
    }
}

void modulo_gr(node* t) {
    t->rr %= mod;
    t->gr %= mod;
    t->rg %= mod;
    t->gg %= mod;
}

void count_gr(node* t) {

    //zliczam dla lewego poddrzewa (1) oraz samego t (2)

    unsigned long long mrr = 0, mgr = 0, mrg = 0, mgg = 0;
    if (t->gal)
        mgg = 1;
    else
        mrr = 1;

    node *l = t->lson, *r = t->rson;

    if (l == nullptr) {
        t->rr = mrr;
        t->gr = mgr;
        t->rg = mrg;
        t->gg = mgg;
    }
    else {
        t->rr = l->rr * mrr + l->rr * mgr + l->rg * mrr + l->rr + mrr;
        t->gr = l->gr * mrr + l->gr * mgr + l->gg * mrr + l->gr + mgr;
        t->rg = l->rr * mrg + l->rg * mrg + l->rr * mgg + l->rg + mrg;
        t->gg = l->gr * mrg + l->gg * mrg + l->gr * mgg + l->gg + mgg;
        modulo_gr(t);
    }
    
    //zliczam dla wynikowego poprzedniego (1) i prawego poddrzewa (2)
    
    if (r != nullptr) {
        mrr = t->rr;
        mgr = t->gr;
        mrg = t->rg;
        mgg = t->gg;
        t->rr = mrr * r->rr + mrr * r->gr + mrg * r->rr + mrr + r->rr;
        t->gr = mgr * r->rr + mgr * r->gr + mgg * r->rr + mgr + r->gr;
        t->rg = mrr * r->rg + mrg * r->rg + mrr * r->gg + mrg + r->rg;
        t->gg = mgr * r->rg + mgg * r->rg + mgr * r->gg + mgg + r->gg;
        modulo_gr(t);
    }
}

unsigned long long sum_gr(node* t) {

    unsigned long long wynik = t->rr + t->gr;
    wynik %= mod;
    wynik += t->rg;
    wynik %= mod;
    wynik += t->gg;
    wynik %= mod;

    return wynik;
}

void right_rotate(node* t) {

    //std::cout << "right rotate\n";

    node* u = t->lson;
    t->lson = u->rson;
    if (t->lson != nullptr)
        t->lson->parent = t;
    u->rson = t;
    node *grandpa = t->parent;
    t->parent = u;
    u->parent = grandpa;
    if (grandpa != nullptr && grandpa->lson == t)
        grandpa->lson = u;
    else if (grandpa != nullptr)
        grandpa->rson = u;
    t->l = how_many_sons(t->lson);
    u->r = how_many_sons(u->rson);
    count_gr(t);
    count_gr(u);
}

void left_rotate(node* t) {

    //std::cout << "left rotate\n";

    node* u = t->rson;
    t->rson = u->lson;
    if (t->rson != nullptr)
        t->rson->parent = t;
    u->lson = t;
    node *grandpa = t->parent;
    t->parent = u;
    u->parent = grandpa;
    if (grandpa != nullptr && grandpa->lson == t)
        grandpa->lson = u;
    else if (grandpa != nullptr)
        grandpa->rson = u;
    t->r = how_many_sons(t->rson);
    u->l = how_many_sons(u->lson);
    count_gr(t);
    count_gr(u);
}

void push_down(node* t) {

    node* help = t->lson;
    t->lson = t->rson;
    t->rson = help;
    int help1 = t->l;
    t->l = t->r;
    t->r = help1;
    t->rev = false;
    unsigned long long help2;
    if (t->lson != nullptr) {
        t->lson->rev = !t->lson->rev;
        help2 = t->lson->gr;
        t->lson->gr = t->lson->rg;
        t->lson->rg = help2;
    }
    if (t->rson != nullptr) {
        t->rson->rev = !t->rson->rev;
        help2 = t->rson->gr;
        t->rson->gr = t->rson->rg;
        t->rson->rg = help2;
    }
    count_gr(t);
}

node* find_node(node* t, int x) {
    //ta funkcja jednoczesnie spycha w dol spotkane odwrócenia

    if (t->rev)
        push_down(t);

    while ((x == 1 && t->lson != nullptr) || (x - 1 != t->l)) {
        if (t->l > x - 1) {
            t = t->lson;
        } else {
            x = x - t->l - 1;
            t = t->rson;
        }
        if (t->rev)
            push_down(t);
    }
    return t;
}

node* splay(node* t, int x) {

    t = find_node(t, x);

    while (t->parent != nullptr) {
        if (t->parent->parent == nullptr) {
            if (t == t->parent->lson) {
                //std::cout << "lewy syn korzenia\n";
                right_rotate(t->parent);
            } else {
                //std::cout << "prawy syn korzenia\n";
                left_rotate(t->parent);
            }
        }
        else if (t == t->parent->lson && t->parent == t->parent->parent->lson) {
            //std::cout << "lewy syn lewego węzła\n";
            right_rotate(t->parent->parent);
            right_rotate(t->parent);
        }
        else if (t == t->parent->rson && t->parent == t->parent->parent->rson) {
            //std::cout << "prawy syn prawego węzła\n";
            left_rotate(t->parent->parent);
            left_rotate(t->parent);
        }
        else if (t == t->parent->rson && t->parent == t->parent->parent->lson) {
            //std::cout << "prawy syn lewego węzła\n";
            left_rotate(t->parent);
            right_rotate(t->parent);
        }
        else {
            //std::cout << "lewy syn prawego węzła\n";
            right_rotate(t->parent);
            left_rotate(t->parent);
        }
    }
    //teraz x-ty wezel jest w korzeniu
    return t;
}

node* join(node* t, node* u) {

    //std::cout << "join\n";

    if (t == nullptr)
        return u;
    if (u == nullptr)
        return t;

    int t_size = t->l + t->r + 1;
    int u_size = u->l + u->r + 1;

    if (t_size > u_size) {
        //lewe drzewo jest wieksze, szukam jego max eltu - łącznika
        //std::cout << "t\n";
        t = splay(t, t_size);
        t->rson = u;
        u->parent = t;
        t->r = how_many_sons(t->rson);
        count_gr(t);
        return t;
    }
    else {
        //prawe drzewo jest wieksze, szukam jego min eltu - łącznika
        //std::cout << "u\n";
        u = splay(u, 1);
        u->lson = t;
        t->parent = u;
        u->l = how_many_sons(u->lson);
        count_gr(u);
        return u;
    }
}

node* build_tree(int p, int k) {

    /* node consist of:
     * node *parent, *lson, *rson;
     * int rr, gr, rg, gg;
     * bool gal; //true - Gal, false - Rzymianin
     * int l, r;
     * bool rev; //reversed
     */

    int s = (p + k + 1) / 2;

    node* t = new node;
    t->gal = szereg[s];
    t->rev = false;

    if (p == k) {
        t->lson = nullptr;
        t->rson = nullptr;
    }
    else if (p + 1 == k) {
        t->lson = build_tree(p,p);
        t->rson = nullptr;
        t->lson->parent = t;
    }
    else {
        t->lson = build_tree(p, s-1);
        t->rson = build_tree(s+1, k);
        t->lson->parent = t;
        t->rson->parent = t;
    }

    count_gr(t);
    count_sons(t);

    return t;
}

std::pair<node*, node*> split(node* t, int x) {
    //element dzielacy trafi do lewego drzewa wynikowego (czyli pierwszego z pary)

    //std::cout << "split(" << x << ")\n";

    if (x == 0) {
        return std::make_pair(nullptr,t);
    }

    node* u = nullptr;
    t = splay(t, x); //chce zeby korzeniem t stal sie element dzielacy

    if (t->rson != nullptr) {
        u = t->rson;
        u->parent = nullptr;
        t->rson = nullptr;
        count_gr(t);
        count_sons(t);
    }
    return std::make_pair(t,u);
}

struct triple {
    node* out_left;
    node* main;
    node* out_right;
};

triple* split3(node* t, int p, int k) {

    std::pair<node*, node*> help = split(t, k);
    node* main = help.first;
    node* out_right = help.second;

    help = split(main, p-1);
    node* out_left = help.first;
    main = help.second;

    auto ans = new triple;
    ans->out_left = out_left;
    ans->main = main;
    ans->out_right = out_right;

    return ans;
}

node* join3(triple* t3) {

    node* t = join(t3->out_left, t3->main);
    t = join(t, t3->out_right);
    return t;
}

node* check(node* t, int p, int k) {

    triple* t3 = split3(t, p, k);

    //print_tree(t3->main);

    unsigned long long wynik = sum_gr(t3->main);
    std::cout << wynik << "\n";

    return join3(t3);
}

node* reverse(node* t, int p, int k) {

    triple* t3 = split3(t, p, k);

    t3->main->rev = !t3->main->rev;
    unsigned long long help = t3->main->gr;
    t3->main->gr = t3->main->rg;
    t3->main->rg = help;

    return join3(t3);
}


int main() {

    int n, m, p, k;
    char z;
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        std::cin >> z;
        szereg[i] = (z == 'G');
    }

    node *t = build_tree(1, n);
    t->parent = nullptr;
    //print_tree(t);

    for (int i = 0; i < m; i++) {
        std::cin >> z >> p >> k;
        if (z == '?') {
            t = check(t, p, k);
        }
        else { // z == O
            t = reverse(t, p, k);
        }
        //print_tree(t);
    }

    return 0;
}