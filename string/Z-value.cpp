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
#define pb push_back
#define F first
#define S second
#define SZ(x) ((int)(x).size())
#define MP make_pair
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
typedef vector<int> VI;

char S[1000010];
int Z[1000010];

int main()
{
	int len=0,lenS;
	gets(S);
	for(;S[len];len++);
	lenS=len;
	gets(S+len+1);
	for(len++;S[len];len++);
	S[len]='*';
	int bst=0;
	Z[0]=0;
	for(int i=1;i<len;i++)
	{
		if(Z[bst]+bst<i) Z[i]=0;
		else Z[i]=min(Z[bst]+bst-i,Z[i-bst]);
		while(S[Z[i]]==S[i+Z[i]]) Z[i]++;
		if(Z[i]+i>Z[bst]+bst) bst=i;
	}
	bool first=1;
	for(int i=lenS+1;i<len;i++)
		if(Z[i]>=lenS)
		{
			if(first)
				printf("%d",i-lenS-1),first=0;
			else
				printf(" %d",i-lenS-1);
		}
	puts("");
	return 0;
}
