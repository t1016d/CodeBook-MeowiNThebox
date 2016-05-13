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

const int MAXN=1010;
const int MAXM=5010;
VI e[MAXN];
int low[MAXN];
int lvl[MAXN];
bool vis[MAXN];
int cnt;
int bel[MAXN];

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

VI eb[MAXN];

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
		for(int i=0;i<cnt;i++)
			eb[i].clear();
		for(int i=1;i<=N;i++)
			for(int u:e[i])
				if(bel[i]!=bel[u])
					eb[bel[i]].PB(bel[u]);
		int ans=0;
		for(int i=0;i<cnt;i++) {
			sort(ALL(eb[i]));
			if(unique(ALL(eb[i]))-eb[i].begin()==1)
				ans++;
		}
		ans=(ans+1)/2;
		printf("%d\n",ans);
	}
	return 0;
}
