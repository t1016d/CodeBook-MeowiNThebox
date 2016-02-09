/***
Test OJ 265
trivial string matching

input:
abc
abccbabbabc

output:
0 8

***/
#include <bits/stdc++.h>
#define PB push_back
#define F first
#define S second
#define SZ(x) ((int)(x).size())
#define MP make_pair
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
typedef vector<int> VI;

char S[500010],T[500010];
int K[500010];

int main()
{
	gets(S);
	gets(T);
	K[0]=-1;
	int a=-1;
	for(int i=1;S[i];i++)
	{
		while(a!=-1 && S[a+1]!=S[i])
			a=K[a];
		if(S[a+1]==S[i])
			a++;
		K[i]=a;
	}
	VI ans;
	a=-1;
	for(int i=0;T[i];i++)
	{
		while(a!=-1 && S[a+1]!=T[i])
			a=K[a];
		if(S[a+1]==T[i])
			a++;
		if(!S[a+1])
		{
			ans.PB(i-a);
			a=K[a];
		}
	}
	bool first=1;
	for(int u:ans)
	{
		if(first)
			printf("%d",u),first=0;
		else
			printf(" %d",u);
	}
	puts("");
	return 0;
}
