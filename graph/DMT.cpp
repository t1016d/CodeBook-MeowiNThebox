const int MAXN = 200000 + 10;

VI e[MAXN], re[MAXN];
int par[MAXN], num[MAXN], t, rn[MAXN];
int sd[MAXN], id[MAXN];
PII p[MAXN];
VI sdom_at[MAXN];

void dfs(int u) {
	num[u] = ++t;
	rn[t] = u;
	for(int v : e[u]) {
		if(num[v])	continue;
		par[v] = u;
		dfs(v);
	}
}

void LINK(int x, int y) {
	p[x].F = y;
	if(sd[y] < sd[p[x].S])	p[x].S = y;
}

int EVAL(int x) {
	if(p[p[x].F].F != p[x].F) {
		int w = EVAL(p[x].F);
		if(sd[w] < sd[p[x].S])	p[x].S = w;
		p[x].F = p[ p[x].F ].F;
	}
	return p[x].S;
}

void DominatingTree(int n) {
	// 1-indexed
	par[1] = 1;
	fill(num, num+n+1, 0);
	fill(rn, rn+n+1, 0);
	t = 0;
	dfs(1);

	for(int i=1; i<=n; i++) {
		p[i] = MP(i, i);
	}
	for(int i=1; i<=n; i++) {
		sd[i] = (num[i] ? num[i] : MAXN+10);
		id[i] = i;
	}
	for(int i=n; i>1; i--) {
		int v = rn[i];
		if(!v)	continue;
		for(int u : re[v]) {
			int w = EVAL(u);
			sd[v] = min(sd[v], sd[w]);
		}
		sdom_at[rn[sd[v]]].PB(v);
		LINK(v, par[v]);

		for(int w : sdom_at[par[v]]) {
			int u = EVAL(w);
			id[w] = (sd[u]<sd[w] ? u : par[v]);
		}
		sdom_at[par[v]].clear();
	}

	for(int i=2; i<=n; i++) {
		int v = rn[i];
		if(!v)	break;
		if(id[v] != rn[sd[v]])	id[v] = id[id[v]];
	}
}
