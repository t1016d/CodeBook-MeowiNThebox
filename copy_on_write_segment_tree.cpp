#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 50000 + 10;
const int Q = 10000 + 10;

struct Seg {
	static Seg mem[N*80], *pmem;

	int val;
	Seg *tl, *tr;

	Seg() :
		tl(NULL), tr(NULL), val(0) {}

	Seg* init(int l, int r) {
		Seg* t = new (pmem++) Seg();
		if(l != r) {
			int m = (l+r)/2;
			t->tl = init(l, m);
			t->tr = init(m+1, r);
		}
		return t;
	}

	Seg* add(int k, int l, int r) {
		Seg* _t = new (pmem++) Seg(*this);
		if(l==r) {
			_t->val++;
			return _t;
		}

		int m = (l+r)/2;
		if(k <= m)	_t->tl = tl->add(k, l, m);
		else		_t->tr = tr->add(k, m+1, r);

		_t->val = _t->tl->val + _t->tr->val;
		return _t;
	}
} Seg::mem[N*80], *Seg::pmem = mem;

int query(Seg* ta, Seg* tb, int k, int l, int r) {
	if(l == r)	return l;

	int m = (l+r)/2;

	int a = ta->tl->val;
	int b = tb->tl->val;
	if(b-a >= k)	return query(ta->tl, tb->tl, k, l, m);
	else			return query(ta->tr, tb->tr, k-(b-a), m+1, r);
};

struct Query {
	int op, l, r, k, c, v;

	bool operator<(const Query b) const {
		return c < b.c;
	}
} qs[Q];
int arr[N];
Seg *t[N];
vector<int> vec2;

int main() {
	int T;
	scanf("%d", &T);

	while(T--) {
		int n, q;
		scanf("%d%d", &n, &q);

		for(int i = 1; i <= n; i++) {
			scanf("%d", arr+i);
			vec2.push_back(arr[i]);
		}
		for(int i = 0; i < q; i++) {
			scanf("%d", &qs[i].op);
			if(qs[i].op == 1)	scanf("%d%d%d", &qs[i].l, &qs[i].r, &qs[i].k);
			else	scanf("%d%d", &qs[i].c, &qs[i].v);

			if(qs[i].op == 2)	vec2.push_back(qs[i].v);
		}
		sort(vec2.begin(), vec2.end());
		vec2.resize(unique(vec2.begin(), vec2.end())-vec2.begin());
		for(int i = 1; i <= n; i++)	arr[i] = lower_bound(vec2.begin(), vec2.end(), arr[i]) - vec2.begin();
		int mn = 0, mx = vec2.size()-1;

		for(int i = 0; i <= n; i++)	t[i] = NULL;
		t[0] = new (Seg::pmem++) Seg();
		t[0] = t[0]->init(mn, mx);
		int ptr = 0;
		for(int i = 1; i <= n; i++) {
			t[i] = t[i-1]->add(arr[i], mn, mx);
		}

		for(int i = 0; i < q; i++) {
			int op = qs[i].op;
			if(op == 1) {
				int l = qs[i].l, r = qs[i].r, k = qs[i].k;
				printf("%d\n", vec2[query(t[l-1], t[r], k, mn, mx)]);
			}
			if(op == 2) {
				continue;
			}
			if(op == 3)	puts("7122");
		}

		vec2.clear();
		Seg::pmem = Seg::mem;
	}

	return 0;
}
