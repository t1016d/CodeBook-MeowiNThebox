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

const int MAXC=30;
ll C[MAXC][MAXC];

inline ll H(int n,int s) {
	debug("%d,%d %lld\n",n,s,C[n+s-1][s]);
	return C[n+s-1][s];
}

inline int dgt(ll x,ll t) {
	return x/t%10;
}

ll f(ll x) {
	if(x==0)
		return 0;
	ll t=1;
	int lg=1;
	while(t<=x)
		t*=10, lg++;
	t/=10;
	lg--;
	if(x==1000000000000000000ll)
		t=x, lg=19;
	int state=0;
	int lst=-1;
	ll ans=0;
	while(t) {
		if(lst==-1) {
			for(int i=lg-1;i>0;i--) {
				ans+=H(i+1,8)+H(i+1,9)-10;
			}
			for(int i=1;i<x/t;i++) {
				ans+=H(lg,9-i)+H(lg,i)-1;
			}
			lst=x/t%10;
		}
		else {
			if(state==1) {
				for(int i=lst;i<dgt(x,t);i++) {
					ans+=H(lg,9-i);
				}
			}
			else if(state==-1) {
				debug("OAO 1\n");
				for(int i=min(lst,dgt(x,t)-1);i>=0;i--) {
					ans+=H(lg,i);
				}
			}
			else {
				for(int i=lst;i<dgt(x,t);i++) {
					ans+=H(lg,9-i);
				}
				for(int i=min(lst,dgt(x,t)-1);i>=0;i--) {
					ans+=H(lg,i);
				}
				debug("OAO\n");
				if(lst<dgt(x,t))
					ans--;
			}
			if(state==1) {
				if(dgt(x,t)<lst)
					break;
			}
			if(state==-1 && dgt(x,t)>lst)
				break;
			if(state==0) {
				if(dgt(x,t)>lst)
					state=1;
				if(dgt(x,t)<lst)
					state=-1;
			}
			lst=dgt(x,t);
		}
		debug("%lld %d %d ...\n",t,lg,state);
		t/=10;
		lg--;
		if(t==0)
			ans++;
	}
	return ans;
}

int main() {
	for(int i=0;i<MAXC;i++)
		for(int j=0;j<=i;j++)
			C[i][j]=(j==0 || i==j)?1:(C[i-1][j-1]+C[i-1][j]);
	int m;
	ll l,r;
	scanf("%d",&m);
	while(m--) {
		scanf("%lld%lld",&l,&r);
		printf("%lld\n",f(r)-f(l-1));
	}
	return 0;
}
