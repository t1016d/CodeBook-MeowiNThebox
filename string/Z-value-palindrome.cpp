// AC code of NTUJ1871
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

char in[100100];
char s[200100];
int z[200100];

int main()
{
    while(gets(in))
    {
        int len=1;
        for(int i=0;in[i];i++)
        {
            s[len++]='*';
            s[len++]=in[i];
        }
        s[len]=0;
        z[0]=0;
        z[1]=0;
        int bst=1;
        for(int i=1;i<len;i++)
        {
            z[i]=min(bst+z[bst]-i,z[bst+bst-i]);
            while(s[i+z[i]+1]==s[i-z[i]-1])
                z[i]++;
            if(z[i]+i>bst+z[bst])
                bst=i;
        }
        /*for(int i=1;i<len;i++)
            putchar(s[i]);
        puts("");
        for(int i=1;i<len;i++)
            printf("%d",z[i]);
        puts("");*/
        bool yes=0;
        for(int i=3;i<len;i+=2)
            if(z[(i+1)/2]==i/2 && z[(i+len)/2]==(len-i-1)/2)
                yes=1;
        if(yes)
            puts("www");
        else
            puts("vvvvvv");
    }
    return 0;
}
