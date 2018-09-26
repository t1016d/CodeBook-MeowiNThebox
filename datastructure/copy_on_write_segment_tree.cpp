const int N = ;
const int Q = ;
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
