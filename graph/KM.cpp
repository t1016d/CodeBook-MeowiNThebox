const int INF=1016; //> max(a[i][j])
const int MAXN=650;
int a[MAXN][MAXN]; // weight [x][y] , two set of vertex
int N; // two set: each set have exactly N vertex
int match[MAXN*2], weight[MAXN*2];
bool vis[MAXN*2];

bool DFS(int x) {
	vis[x]=1;
	for(int i=0;i<N;i++) {
		if(weight[x]+weight[N+i]!=a[x][i]) continue;
		vis[N+i]=1;
		if(match[N+i]==-1 || (!vis[match[N+i]]&&DFS(match[N+i]))) {
			match[N+i]=x;
			match[x]=N+i;
			return 1;
		}
	}
	return 0;
}

int KM() {
	fill(weight, weight+N+N, 0);
	for(int i=0;i<N;i++) {
		for(int j=0;j<N;j++)
			weight[i]=max(weight[i], a[i][j]);
	}
	fill(match, match+N+N, -1);
	for(int u=0;u<N;u++) {
		fill(vis, vis+N+N, 0);
		while(!DFS(u)) {
			int d=INF;
			for(int i=0;i<N;i++) {
				if(!vis[i]) continue;
				for(int j=0;j<N;j++)
					if(!vis[N+j])
						d=min(d, weight[i]+weight[N+j]-a[i][j]);
			}
			for(int i=0;i<N;i++)
				if(vis[i])
					weight[i]-=d;
			for(int i=N;i<N+N;i++)
				if(vis[i])
					weight[i]+=d;
			fill(vis, vis+N+N, 0);
		}
	}
	int ans=0;
	for(int i=0;i<N+N;i++) ans+=weight[i];
	return ans;
}
