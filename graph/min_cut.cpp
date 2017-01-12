const int MAXN = 500 + 50;
int w[MAXN][MAXN];
ll cost[MAXN];
bool out[MAXN];

int N, M;
ll go(int V) {
	fill(cost, cost + N, 0);
	cost[0] = -1;
	int nxt = 0, lst = 0;
	for(int i = 0; i < N; i++) {
		if(out[i]) continue;
		cost[i] += w[0][i];
		if(cost[i] > cost[nxt]) nxt = i;
	}
	while(V > 2) {
		int u = nxt;
		if(cost[u] <= 0) return 0;
		cost[u] = -1;
		for(int i = 0; i < N; i++) {
			if(cost[i] == -1 || out[i]) continue;
			cost[i] += w[u][i];
			if(cost[i] > cost[nxt]) nxt = i;
		}
		V--;
		lst = u;
	}
	if(cost[nxt] <= 0) return 0;
	out[nxt] = true;
	for(int i = 0; i < N; i++)
		w[i][lst] = w[lst][i] = (w[lst][i] + w[nxt][i]);
	return cost[nxt];
}

ll min_cut() {
	fill(out, out + N, false);
	ll res = go(N);
	for(int v = N - 1; v > 1; v--) {
		res = min(go(v), res);
		if(res == 0) return res;
	}
	return res;
}
