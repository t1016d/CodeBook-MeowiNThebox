typedef vector<coor> poly;
const int N = 105;

bool inside(const coor pnt, const poly &P) {
	int n = SZ(P);
	for(int i=0; i<n; i++) {
		coor p1=P[i], p2=P[(i+1)%n];
		if(lt((p1-pnt) % (p2-pnt), 0))
			return false;
	}
	return true;
}

int prv[N], nxt[N];
bool isear(int x, const poly &P) {
	int n = SZ(P);
	int x1 = nxt[x], x2=prv[x];
	coor v=P[x], v1=P[x1], v2=P[x2];
	if(le((v1-v)%(v2-v), 0))	return false;
	poly cand;
	cand.PB(v), cand.PB(v1), cand.PB(v2);
	for(int j=0; j<n; j++) {
		if(j==x or j==x1 or j==x2)	continue;
		if(inside(P[j], cand))
			return false;
	}
	return true;
}

vector<poly> triangulation(const poly &P) {
	bool used[N]={}, ear[N]={};
	int n = SZ(P);
	for(int i=0; i<n; i++)	prv[i] = (i-1+n)%n, nxt[i] = (i+1)%n;
	queue<int> que;
	for(int i=0; i<n; i++) {
		ear[i] = isear(i, P);
		if(ear[i])	que.push(i);
	}
	vector<poly> ret;
	while(true) {
		assert(!que.empty());
		int head=que.front();
		que.pop();
		if(used[head] or !ear[head])	continue;
		poly trian;
		int x1 = nxt[head], x2 = prv[head];
		trian.PB(P[head]), trian.PB(P[x1]), trian.PB(P[x2]);
		ret.PB(trian);
		used[head]=true;
		nxt[x2] = x1, prv[x1] = x2;
		if(prv[x2] == x1)	break;
		
		ear[x1] = isear(x1, P), ear[x2] = isear(x2, P);
		if(ear[x1])	que.push(x1);
		if(ear[x2])	que.push(x2);
	}
	return ret;
}
