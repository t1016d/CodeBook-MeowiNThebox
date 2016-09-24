typedef pair<int,ll> PIL;
const int MAXV=60;
const int MAXE=6000;
const int INF=(int)1e9+10;
const ll cINF=(ll)1e18+10;
// ^ config those things

struct E {
	int to,ca,cost;//capacity, cost
	E(int t=0,int c=0,int co=0):to(t),ca(c),cost(co) {}
}eg[2*MAXE];

// source:0  sink:n-1
struct Flow {
	VI e[MAXV];
	int ei,n;
	void init(int n_) {
		n=n_;
		ei=0;
		for(int i=0;i<n;i++)
			e[i]=VI();
	}
	void add(int a,int b,int c,int d) {
		//a to b ,maxflow=c, cost=d
		eg[ei]=E(b,c,d);
		e[a].PB(ei);
		ei++;
		eg[ei]=E(a,0,-d);
		e[b].PB(ei);
		ei++;
	}
	
	PII d[MAXV]={};
	bool inq[MAXV]={};
	queue<int> que;
	VI pe;
	bool SPFA() {
		fill(d, d+n, MP(INF,INF));
		d[0]=MP(0,0);
		que.push(0);
		inq[0]=1;
		while(!que.empty()) {
			int v=que.front(); que.pop();
			inq[v]=0;
			for(int id:e[v]) {
				if(eg[id].ca>0 && MP(d[v].F+eg[id].cost,d[v].S+1)<d[eg[id].to]) {
					d[eg[id].to]=MP(d[v].F+eg[id].cost,d[v].S+1);
					if(!inq[eg[id].to]) {
						que.push(eg[id].to);
						inq[eg[id].to]=1;
					}
				}
			}
		}
		return d[n-1].F<INF;
	}
	PIL go(ll cb=cINF) {
		// cost_bound
		if(!SPFA()) return MP(0,0);
		pe.clear();
		int fl=INF;
		for(int v=n-1;v!=0;) {
			for(int id:e[v]) {
				int u=eg[id].to;
				const E& t=eg[id^1];
				if(t.ca>0 && MP(d[u].F+t.cost,d[u].S+1)==d[v]) {
					fl=min(fl, t.ca);
					v=u;
					pe.PB(id^1);
					break;
				}
			}
		}
		if(d[n-1].F>0) fl=min(1ll*fl, cb/d[n-1].F);
		for(int id:pe) {
			eg[id].ca-=fl;
			eg[id^1].ca+=fl;
		}
		return MP(fl, 1ll*fl*d[n-1].F);
	}
	PIL max_flow() {
		PIL ans=MP(0,0),temp;
		while((temp=go()).F>0) {
			ans.F+=temp.F;
			ans.S+=temp.S;
		}
		return ans;
	}
} flow;
