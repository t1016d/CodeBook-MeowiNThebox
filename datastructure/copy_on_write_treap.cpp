#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <climits>
#include <cstring>
 
using namespace std;
 
const int N = 1000000 + 10;
 
struct Treap {
    char val;
    int sz, refs;
    Treap *l, *r;
 
    Treap() {}
    Treap(char _val):
        val(_val), sz(1), refs(0), l(NULL), r(NULL) {}
};
 
Treap* make(Treap* t) {
    return new Treap(*t);
}
 
Treap* make(char _val) {
    return new Treap(_val);
}
 
void print_ref(Treap* t) {
    if(!t)  return ;
    print_ref(t->l);
    printf("%d ", t->refs);
    print_ref(t->r);
}
 
void print(Treap* t) {
    if(!t)  return ;
    print(t->l);
    putchar(t->val);
    print(t->r);
}
 
void takeRef(Treap* t) {
    if(t)   t->refs++;
}
 
void dropRef(Treap* t) {
    if(t) {
        char c = t->val;
        t->refs--;
        if(t->refs <= 0) {
            dropRef(t->l);
            dropRef(t->r);
            delete t;
        }
    }
}
 
int sz(Treap* t) {
    return t ? t->sz : 0;
}
 
int rnd(int m) {
    static int x = 851025;
    return (x = (x*0xdefaced+1) & INT_MAX) % m;
}
 
void pull(Treap* t) {
    t->sz = sz(t->l) + sz(t->r) + 1;
}
 
Treap* merge(Treap* a, Treap* b) {
    if(!a || !b) {
        Treap* t = a ? make(a) : make(b);
        t->refs = 0;
        takeRef(t->l);
        takeRef(t->r);
        return t;
    }
 
    Treap* t;
    if( rnd(a->sz+b->sz) < a->sz) {
        t = make(a);
        t->refs = 0;
        t->r = merge(a->r, b);
        takeRef(t->l);
        takeRef(t->r);
    }
    else {
        t = make(b);
        t->refs = 0;
        t->l = merge(a, b->l);
        takeRef(t->l);
        takeRef(t->r);
    }
 
    pull(t);
    return t;
}
 
void split(Treap* t, int k, Treap* &a, Treap* &b) {
    if(!t)  a = b = NULL;
    else if(sz(t->l) < k) {
        a = make(t);
        a->refs = 0;
        split(a->r, k-sz(t->l)-1, a->r, b);
        takeRef(a->l);
        takeRef(a->r);
        pull(a);
    }
    else {
        b = make(t);
        b->refs = 0;
        split(b->l, k, a, b->l);
        takeRef(b->l);
        takeRef(b->r);
        pull(b);
    }
}
 
void print_inorder(Treap* t) {
    if(!t)  return ;
    putchar(t->val);
    print_inorder(t->l);
    print_inorder(t->r);
}
 
char s[N];
 
int main() {
    int m;
    scanf("%d", &m);
    scanf("%s", s);
    int n = strlen(s);
    int q;
    scanf("%d", &q);
 
    Treap* t = NULL;
    for(int i = 0; i < n; i++) {
        Treap *a = t, *b = make(s[i]);
        t = merge(a, b);
        dropRef(a);
        dropRef(b);
    }
 
    while(q--) {
        int l, r, x;
        scanf("%d%d%d", &l, &r, &x);
        r++;
 
        Treap *a, *b, *c, *d;
        a = b = c = d = NULL;
        split(t, l, a, b);
        dropRef(a);
        split(b, r-l, c, d);
        dropRef(b);
        dropRef(d);
        split(t, x, a, b);
        dropRef(t);
        Treap* t2 = merge(c, b);
        dropRef(b);
        dropRef(c);
        t = merge(a, t2);
        dropRef(a);
        dropRef(t2);
 
        if(t->sz > m) {
            Treap* t2 = NULL;
            split(t, m, t2, a);
            dropRef(a);
            dropRef(t);
            t = t2;
        }
    }
 
    print(t);
    putchar('\n');
 
    return 0;
}
