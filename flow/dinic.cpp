const int MAXV=300;
const int MAXE=10000;
const int INF=(int)1e9+10;
// ^ config those things

struct E {
	int to,co;//capacity
	E(int t=0,int c=0):to(t),co(c) {}
}eg[2*MAXE];

// source:0  sink:n-1
struct Flow {
	VI e[MAXV];
	int ei,v;
	void init(int n) {
		v=n;
		ei=0;
		for(int i=0;i<n;i++)
			e[i]=VI();
	}
	void add(int a,int b,int c) { //a to b ,maxflow=c
		eg[ei]=E(b,c);
		e[a].PB(ei);
		ei++;
		eg[ei]=E(a,0);
		e[b].PB(ei);
		ei++;
	}
	
	int d[MAXV],qu[MAXV],ql,qr;
	bool BFS() {
		memset(d,-1,v*sizeof(int));
		ql=qr=0;
		qu[qr++]=0;
		d[0]=0;
		while(ql<qr && d[v-1]==-1) {
			int n=qu[ql++];
			VI &v=e[n];
			for(int i=SZ(v)-1;i>=0;i--) {
				int u=v[i];
				if(d[eg[u].to]==-1 && eg[u].co>0) {
					d[eg[u].to]=d[n]+1;
					qu[qr++]=eg[u].to;
				}
			}
		}
		return d[v-1]!=-1;
	}
	int ptr[MAXV];
	int go(int n,int p) {
		if(n==v-1)
			return p;
		VI &u=e[n];
		int temp;
		for(int i=ptr[n];i<SZ(u);i++) {
			if(d[n]+1!=d[eg[u[i]].to] || eg[u[i]].co==0)
				continue;
			if((temp=go(eg[u[i]].to,min(p,eg[u[i]].co)))==0)
				continue;
			eg[u[i]].co-=temp;
			eg[u[i]^1].co+=temp;
			ptr[n]=i;
			return temp;
		}
		ptr[n]=SZ(u);
		return 0;
	}
	int max_flow() {
		int ans=0,temp;
		while(BFS()) {
			for(int i=0;i<v;i++)
				ptr[i]=0;
			while((temp=go(0,INF))>0)
				ans+=temp;
		}
		return ans;
	}
}flow;
