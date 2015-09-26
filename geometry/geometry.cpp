// correct code of NPSC2013 senior-final pF

#include <bits/stdc++.h>
#define pb push_back
#define F first
#define S second
#define SZ(x) ((int)(x).size())
#define MP make_pair
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
typedef vector<int> VI;

typedef double dou;
struct PT{
	dou x,y;
	PT(dou x_=0.0,dou y_=0.0): x(x_),y(y_) {}
	PT operator + (const PT &b) const { return PT(x+b.x,y+b.y); }
	PT operator - (const PT &b) const { return PT(x-b.x,y-b.y); }
	PT operator * (const dou &t) const { return PT(x*t,y*t); }
	dou operator * (const PT &b) const { return x*b.x+y*b.y; }
	dou operator % (const PT &b) const { return x*b.y-b.x*y; }
	dou len2() const { return x*x+y*y; }
	dou len() const { return sqrt(len2()); } 
};

const dou INF=1e12;
const dou eps=1e-8;
PT inter(const PT &P1,const PT &T1,const PT &P2,const PT &T2) // intersection
{
	if(fabs(T1%T2)<eps)
		return PT(INF,INF);
	dou u=((P2-P1)%T2)/(T1%T2);
	return P1+T1*u;
}

PT conv[500],cat,to;

int main()
{
	int T,N,M;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&N,&M);
		for(int i=0;i<N;i++)
			scanf("%lf%lf",&conv[i].x,&conv[i].y);
		conv[N]=conv[0];
		dou ans=0.0;
		while(M--)
		{
			scanf("%lf%lf%lf%lf",&cat.x,&cat.y,&to.x,&to.y);
			for(int i=0;i<N;i++)
				if(fabs((conv[i]-conv[i+1])%to)>eps)
				{
				//	printf("M:%d i=%d\n",M,i);
					PT at=inter(conv[i],conv[i]-conv[i+1],cat,to);
					if((conv[i]-at)*(conv[i+1]-at)<eps && (at-cat)*to>-eps)
						ans=max(ans,(cat-at).len());
				}
		}
		printf("%.4f\n",ans);
	}
	return 0;
}
