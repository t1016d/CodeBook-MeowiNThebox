const int MAXN=1010;
const int MAXM=5010;
VI e[MAXN];
int low[MAXN],lvl[MAXN],bel[MAXN];
bool vis[MAXN];
int cnt;
VI st;
void DFS(int x,int l,int p) {
	st.PB(x);
	vis[x]=1;
	low[x]=lvl[x]=l;
	bool top=0;
	for(int u:e[x]) {
		if(u==p && !top) {
			top=1;
			continue;
		}
		if(!vis[u]) {
			DFS(u,l+1,x);
		}
		low[x]=min(low[x],low[u]);
	}
	if(x==1 || low[x]==l) {
		while(st.back()!=x) {
			bel[st.back()]=cnt;
			st.pop_back();
		}
		bel[st.back()]=cnt;
		st.pop_back();
		cnt++;
	}
}
int main() {
	int T;
	scanf("%d",&T);
	while(T--) {
		int N,M,a,b;
		scanf("%d%d",&N,&M);
		fill(vis,vis+N+1,0);
		for(int i=1;i<=N;i++)
			e[i].clear();
		while(M--) {
			scanf("%d%d",&a,&b);
			e[a].PB(b);
			e[b].PB(a);
		}
		cnt=0;
		DFS(1,0,-1);
		/*****/
	}
	return 0;
}
