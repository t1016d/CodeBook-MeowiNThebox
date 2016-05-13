#include <bits/stdc++.h>
#define PB push_back
#define MP make_pair
#define F first
#define S second
#define SZ(x) ((int)(x).size())
#define ALL(x) (x).begin(),(x).end()
#ifdef _DEBUG_
	#define debug(...) printf(__VA_ARGS__)
#else
	#define debug(...) (void)0
#endif
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
typedef vector<int> VI;

const int MAXN = 300000 + 10;

bool q[MAXN];

struct DisJointSet {
	int p[MAXN], sz[MAXN], gps;
	vector<pair<int*, int> > h;
	VI sf;

	void init(int n) {
		for(int i=1; i<=n; i++) {
			p[i] = i;
			sz[i] = 1;
		}
		gps = n;
	}

	void assign(int *k, int v) {
		h.PB(MP(k, *k));
		*k = v;
	}

	void save() {
		sf.PB(SZ(h));
	}

	void load() {
		int last = sf.back();	sf.pop_back();
		while(SZ(h) != last) {
			auto x = h.back();	h.pop_back();
			*x.F = x.S;
		}
	}

	int find(int x) {
		return x==p[x] ? x : find(p[x]);
	}

	void uni(int x, int y) {
		x = find(x), y = find(y);
		if(x == y)	return ;
		if(sz[x] < sz[y])	swap(x, y);
		assign(&sz[x], sz[x]+sz[y]);
		assign(&p[y], x);
		assign(&gps, gps-1);
	}
} djs;

struct Seg {
	vector<PII> es;
	Seg *tl, *tr;

	Seg() {}
	Seg(int l, int r) {
		if(l == r)	tl = tr = NULL;
		else {
			int m = (l+r) / 2;
			tl = new Seg(l, m);
			tr = new Seg(m+1, r);
		}
	}

	void add(int a, int b, PII e, int l, int r) {
		if(a <= l && r <= b)	es.PB(e);
		else if(b < l || r < a)	return ;
		else {
			int m = (l+r) / 2;
			tl->add(a, b, e, l, m);
			tr->add(a, b, e, m+1, r);
		}
	}

	void solve(int l, int r) {
		djs.save();
		for(auto p : es)	djs.uni(p.F, p.S);

		if(l == r) {
			if(q[l])	printf("%d\n", djs.gps);
		}
		else {
			int m = (l+r) / 2;
			tl->solve(l, m);
			tr->solve(m+1, r);
		}

		djs.load();
	}
};

map<PII, int> prv;

int main() {
	freopen("connect.in", "r", stdin);
	freopen("connect.out", "w", stdout);

	int n, k;
	scanf("%d%d\n", &n, &k);
	if(!k)	return 0;

	Seg *seg = new Seg(1, k);
	djs.init(n);
	for(int i=1; i<=k; i++) {
		char op = getchar();
		if(op == '?') {
			q[i] = true;
			op = getchar();
		}
		else {
			int u, v;
			scanf("%d%d\n", &u, &v);
			if(u > v)	swap(u, v);
			PII eg = MP(u, v);
			int p = prv[eg];
			if(p) {
				seg->add(p, i, eg, 1, k);
				prv[eg] = 0;
			}
			else	prv[eg] = i;
		}
	}
	for(auto p : prv) {
		if(p.S) {
			seg->add(p.S, k, p.F, 1, k);
		}
	}
	
	seg->solve(1, k);
    
    return 0;
}
