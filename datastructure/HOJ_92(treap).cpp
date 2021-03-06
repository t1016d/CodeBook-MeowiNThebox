const int INF = 103456789;
struct Treap {
    int pri, sz, val, chg, rev, sum, lsum, rsum, mx_sum;
    Treap *l, *r;
 
    Treap() {}
    Treap(int _val) :
        pri(rand()), sz(1), val(_val), chg(INF), rev(0), sum(_val), lsum(_val), rsum(_val), mx_sum(_val), l(NULL), r(NULL) {}
};
int sz(Treap* t) {return t ? t->sz : 0;}
int sum(Treap* t) {
    if(!t)  return 0;
    if(t->chg == INF)   return t->sum;
    else    return t->chg*t->sz;
}
int lsum(Treap* t) {
    if(!t)  return -INF;
    if(t->chg != INF)   return max(t->chg, (t->chg)*(t->sz));
    if(t->rev)  return t->rsum;
    return t->lsum;
}
int rsum(Treap* t) {
    if(!t)  return -INF;
    if(t->chg != INF)   return max(t->chg, (t->chg)*(t->sz));
    if(t->rev)  return t->lsum;
    return t->rsum;
}
int mx_sum(Treap* t) {
    if(!t)  return -INF;
    if(t->chg != INF)   return max(t->chg, (t->chg)*(t->sz));
    return t->mx_sum;
}
void push(Treap* t) {
    if(t->chg != INF) {
        t->val = t->chg;
        t->sum = (t->sz) * (t->chg);
        t->lsum = t->rsum = t->mx_sum = max(t->sum, t->val);
        if(t->l)    t->l->chg = t->chg;
        if(t->r)    t->r->chg = t->chg;
        t->chg = INF;
    }
    if(t->rev) {
        swap(t->l, t->r);
        if(t->l)    t->l->rev ^= 1;
        if(t->r)    t->r->rev ^= 1;
        t->rev = 0;
    }
}
void pull(Treap* t) {
    t->sz = sz(t->l)+sz(t->r)+1;
    t->sum = sum(t->l)+sum(t->r)+t->val;
    t->lsum = max(lsum(t->l), sum(t->l)+max(0, lsum(t->r))+t->val);
    t->rsum = max(rsum(t->r), sum(t->r)+max(0, rsum(t->l))+t->val);
    t->mx_sum = max(max(mx_sum(t->l), mx_sum(t->r)), max(0, rsum(t->l))+max(0, lsum(t->r))+t->val);
}
Treap* merge(Treap* a, Treap* b) {
    if(!a || !b)    return a ? a : b;
    if(a->pri > b->pri) {
        push(a);
        a->r = merge(a->r, b);
        pull(a);
        return a;
    }
    else {
        push(b);
        b->l = merge(a, b->l);
        pull(b);
        return b;
    }
}
void split(Treap* t, int k, Treap* &a, Treap* &b) {
    if(!t) {
        a = b = NULL;
        return ;
    }
    push(t);
    if(sz(t->l) < k) {
        a = t;
        push(a);
        split(t->r, k-sz(t->l)-1, a->r, b);
        pull(a);
    }
    else {
        b = t;
        push(b);
        split(t->l, k, a, b->l);
        pull(b);
    }
}
void del(Treap* t) {
    if(!t)  return;
    del(t->l);
    del(t->r);
    delete t;
}
