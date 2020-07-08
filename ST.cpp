#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <cmath>

using namespace std;

const int neutral = 0;

struct node {
    int a;

    node() : a(neutral) {

    }

    node(int a) : a(a) {};
};

const int MAXN = 1e5;
node t[4 * MAXN];
vector<int> a;

node refresh(node &l, node &r) {
    return node(l.a + r.a);
}

void build(int v, int l, int r) {
    if (r - l == 1) {
        t[v].a = a[l];
        return;
    }
    int m = (l + r) / 2;
    build(2 * v + 1, l, m);
    build(2 * v + 2, m, r);
    t[v] = refresh(t[2 * v + 1], t[2 * v + 2]);
}

node ask(int v, int l, int r, int askl, int askr) {
    if (l >= askr || r <= askl) {
        return node();
    }
    if (l >= askl && r <= askr) {
        return t[v];
    }
    int m = (l + r) / 2;
    node tl = ask(2 * v + 1, l, m, askl, askr), tr = ask(2 * v + 2, m, r, askl, askr);
    return refresh(tl, tr);
}

void change(int v, int l, int r, int pos, int x) {
    if (r - l == 1) {
        t[v] = node(x);
        return;
    }
    int m = (l + r) / 2;
    if (m > pos) {
        change(2 * v + 1, l, m, pos, x);
    } else {
        change(2*v+2,m,r,pos,x);
    }
    t[v] = refresh(t[2*v+1],t[2*v+2]);
}

int main() {
    int n;
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    build(0, 0, n);
    change(0,0,n,2,2);
    cout << ask(0, 0, n, 0, n).a<<'\n';
}
