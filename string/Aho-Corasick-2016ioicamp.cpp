// AC code of 2016ioicamp 54
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

const int MAXNM=100010;
int pp[MAXNM];

const int sizz=100010;
int nx[sizz][26],spt;
int fl[sizz],efl[sizz],ed[sizz];
int len[sizz];
int newnode(int len_=0) {
	for(int i=0;i<26;i++)nx[spt][i]=0;
	ed[spt]=0;
	len[spt]=len_;
	return spt++;
}
int add(char *s,int p) {
	int l=1;
	for(int i=0;s[i];i++) {
		int a=s[i]-'a';
		if(nx[p][a]==0) nx[p][a]=newnode(l);
		p=nx[p][a];
		l++;
	}
	ed[p]=1;
	return p;
}
int q[sizz],qs,qe;
void make_fl(int root) {
	fl[root]=efl[root]=0;
	qs=qe=0;
	q[qe++]=root;
	for(;qs!=qe;) {
		int p=q[qs++];
		for(int i=0;i<26;i++) {
			int t=nx[p][i];
			if(t==0) continue;
			int tmp=fl[p];
			for(;tmp&&nx[tmp][i]==0;) tmp=fl[tmp];
			fl[t]=tmp?nx[tmp][i]:root;
			efl[t]=ed[fl[t]]?fl[t]:efl[fl[t]];
			q[qe++]=t;
		}
	}
}
char s[MAXNM];
char a[MAXNM];

int dp[MAXNM][4];

void mmax(int &a,int b) {
	a=max(a,b);
}

void match(int root) {
	int p=root;
	for(int i=1;s[i];i++) {
		int a=s[i]-'a';
		for(;p&&nx[p][a]==0;p=fl[p]);
		p=p?nx[p][a]:root;
		for(int j=1;j<=3;j++)
			dp[i][j]=dp[i-1][j];
		for(int t=p;t;t=efl[t]) {
			if(!ed[t])
				continue;
			for(int j=1;j<=3;j++)
				mmax(dp[i][j],dp[i-len[t]][j-1]+(pp[i]-pp[i-len[t]]));
		}
	}
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) {
		int n,m;
		scanf("%d%d",&n,&m);
		scanf("%s",s+1);
		for(int i=1;i<=n;i++)
			scanf("%d",pp+i);
		for(int i=1;i<=n;i++)
			pp[i]+=pp[i-1];
		spt=1;
		int root=newnode();
		for(int i=0;i<m;i++) {
			scanf("%s",a);
			add(a,root);
		}
		make_fl(root);
		for(int i=1;i<=n;i++)
			dp[i][1]=dp[i][2]=dp[i][3]=0;
		match(root);
		printf("%d\n",dp[n][3]);
	}
	return 0;
}
