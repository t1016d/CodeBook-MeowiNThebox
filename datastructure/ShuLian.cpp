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

const int MAXN = 10000 + 10;

vector<PII> e[MAXN];
int val[MAXN];
int sz[MAXN], max_son[MAXN], p[MAXN], dep[MAXN];
int link[MAXN], link_top[MAXN], cnt;

void find_max_son(int u) {
	sz[u] = 1;
	max_son[u] = -1;
	for(int i=0; i<SZ(e[u]); i++) {
		PII tmp = e[u][i];
		int v = tmp.F;
		if(v == p[u])	continue;

		p[v] = u;
		dep[v] = dep[u]+1;
		val[v] = tmp.S;
		find_max_son(v);
		if(max_son[u]<0 || sz[v]>sz[ max_son[u] ])	max_son[u] = v;
		sz[u] += sz[v];
	}
}

void build_link(int u, int top) {
	link[u] = ++cnt;
	link_top[u] = top;
	if(max_son[u] > 0)	build_link(max_son[u], top);
	for(int i=0; i<SZ(e[u]); i++) {
		PII tmp = e[u][i];
		int v = tmp.F;
		if(v==p[u] || v==max_son[u])	continue;

		build_link(v, v);
	}
}

int query(int a, int b) {
	int res = -1;
	int ta = link_top[a], tb = link_top[b];
	while(ta != tb) {
		if(dep[ta] < dep[tb]) {
			swap(a, b);
			swap(ta, tb);
		}

		res = max(res, seg->qry(link[ta], link[a], 1, cnt));
		ta = link_top[a=p[ta]];
	}

	if(a != b) {
		if(dep[a] > dep[b])	swap(a, b);
		a = max_son[a];
		res = max(res, seg->qry(link[a], link[b], 1, cnt));
	}

	return res;
}
