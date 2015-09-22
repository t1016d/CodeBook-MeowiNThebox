// NTUJ1263
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

bool is(ll x)
{
	ll l=1,r=2000000,m;
	while(l<=r)
	{
		m=(l+r)/2;
		if(m*m==x)
			return 1;
		if(m*m<x)
			l=m+1;
		else
			r=m-1;
	}
	return 0;
}

VI odd,even;
int in[300];
VI e[300];
int match[300];
bool vis[300];

bool DFS(int x)
{
	vis[x]=1;
	for(int u:e[x])
	{
		if(match[u]==-1 || (!vis[match[u]]&&DFS(match[u])))
		{
			match[u]=x;
			match[x]=u;
			return 1;
		}
	}
	return 0;
}

int main()
{
	int N;
	while(scanf("%d",&N)==1)
	{
		odd.clear();
		even.clear();
		for(int i=0;i<N;i++)
			e[i].clear();
		for(int i=0;i<N;i++)
		{
			scanf("%d",in+i);
			if(in[i]%2==0)
				even.pb(i);
			else
				odd.pb(i);
		}
		for(int i:even)
			for(int j:odd)
				if(is(1ll*in[i]*in[i]+1ll*in[j]*in[j]) && __gcd(in[i],in[j])==1)
					e[i].pb(j), e[j].pb(i);
		int ans=0;
		fill(match,match+N,-1);
		for(int i=0;i<N;i++)
			if(match[i]==-1)
			{
				fill(vis,vis+N,0);
				if(DFS(i))
					ans++;
			}
		printf("%d\n",ans);
	}
	return 0;
}
