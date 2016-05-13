const int MAXN=10000;
const int MAXE=100000;

VI e[MAXN+10];
vector<PII> BCC[MAXE];
int bccnt;
vector<PII> st;
bool vis[MAXN+10];
int low[MAXN+10],level[MAXN+10];

void DFS(int x,int p,int l) {
	vis[x]=1;
	level[x]=low[x]=l;
	for(int u:e[x]) {
		if(u==p)
			continue;
		if(vis[u]) {
			if(level[u]<l) {
				st.PB(MP(x,u));
				low[x]=min(low[x],level[u]);
			}
		}
		else {
			st.PB(MP(x,u));
			DFS(u,x,l+1);
			if(low[u]>=l) {
				PII t=st.back();
				st.pop_back();
				while(t!=MP(x,u)) {
					BCC[bccnt].PB(t);
					t=st.back();
					st.pop_back();
				}
				BCC[bccnt].PB(t);
				bccnt++;
			}
			low[x]=min(low[x],low[u]);
		}
	}
}

int main() {
	int T,N,M;
	scanf("%d",&T);
	while(T--) {
		scanf("%d%d",&N,&M);
		for(int i=0;i<N;i++)
			e[i].clear();
		int cnt=0;
		while(1) {
			int x,y;
			scanf("%d%d",&x,&y);
			if(x==-1 && y==-1)
				break;
			cnt++;
			e[x].PB(y);
			e[y].PB(x);
		}
		for(int i=0;i<N;i++) { // no multi-edge
			sort(ALL(e[i]));
			e[i].erase(unique(ALL(e[i])),e[i].end());
		}
		fill(vis,vis+N,0);
		while(bccnt)
			BCC[--bccnt].clear();
		DFS(0,-1,0);
		/***/
	}
	return 0;
}
