#include <cstdlib>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long ll;

const int N = 100000 + 10;

struct Treap {
	static Treap mem[N], *pmem;

	int sz, pri;
	ll val, sum, add;
	Treap *l, *r;

	Treap() {}
	Treap(ll _val):
		l(NULL), r(NULL), sz(1), pri(rand()), val(_val), sum(_val), add(0) {}
} Treap::mem[N], *Treap::pmem = Treap::mem;

Treap* make(ll val) {
	return new (Treap::pmem++) Treap(val);
}

inline int sz(Treap *t) {
	return t ? t->sz : 0;
}

inline ll sum(Treap *t) {
	return t ? t->sum + t->add * sz(t) : 0;
}

inline void add(Treap *t, ll x) {
	t->add += x;
}

void push(Treap *t) {
	t->val += t->add;
	if(t->l)	t->l->add += t->add;
	if(t->r)	t->r->add += t->add;
	t->add = 0;
}

void pull(Treap *t) {
	t->sum = sum(t->l) + sum(t->r) + t->val;
	t->sz = sz(t->l) + sz(t->r) + 1;
}

Treap* merge(Treap *a, Treap *b) {
	if(!a || !b)	return a ? a : b;
	else if(a->pri > b->pri) {
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

void split(Treap* t, int k, Treap *&a, Treap *&b) {
	if(!t)	a = b = NULL;
	else if(sz(t->l) < k) {
		a = t;
		push(a);
		split(t->r, k - sz(t->l) - 1, a->r, b);
		pull(a);
	}
	else {
		b = t;
		push(b);
		split(t->l, k, a, b->l);
		pull(b);
	}
}

int main() {
	srand(105105);

	int n, q;
	scanf("%d%d", &n, &q);

	Treap *t = NULL;
	for(int i = 0; i < n; i++) {
		ll tmp;
		scanf("%lld", &tmp);
		t = merge(t, make(tmp));
	}

	while(q--) {
		char c;
		int l, r;
		scanf("\n%c %d %d", &c, &l, &r);

		Treap *tl = NULL, *tr = NULL;
		if(c == 'Q') {
			split(t, l - 1, tl, t);
			split(t, r - l + 1, t, tr);
			printf("%lld\n", sum(t));
			t = merge(tl, merge(t, tr));
		}
		else {
			ll x;
			scanf("%lld", &x);
			split(t, l - 1, tl, t);
			split(t, r - l + 1, t, tr);
			add(t, x);
			t = merge(tl, merge(t, tr));
		}
	}

	return 0;
}
