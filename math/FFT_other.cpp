/* FFT code from shik in CodeForces*/
/* zj a577*/
#include <bits/stdc++.h>
using namespace std;
const int N=300000;

const double PI=acos(-1.0);
struct vir{
    double re,im;
    vir( double _re=0, double _im=0 ):re(_re),im(_im){}
};
vir operator +( vir a, vir b ) { return vir(a.re+b.re,a.im+b .im); }
vir operator -( vir a, vir b ) { return vir(a.re-b.re,a.im-b .im); }
vir operator *( vir a, vir b ) { return vir(a.re*b.re-a.im*b .im,a.re*b.im+a.im*b.re); }
vir x1[2*N],x2[2*N];

int rev( int x, int len ) {
    int r=0,i;
    for ( i=0; i<len; i++,x>>=1 ) r=(r<<1)+(x&1);
    return r;
}
void change( vir *x, int len, int loglen ) {
    for ( int i=0; i<len; i++ )
        if ( rev(i,loglen)<i ) swap(x[rev(i,loglen)],x[i]);
}
void fft( vir *x, int len, int loglen ) {
    change(x,len,loglen);
    int i,j,s,t=1;
    for ( i=0; i<loglen; i++,t<<=1 ) {
        for ( s=0; s<len; s+=t+t ) {
            vir a,b,wo(cos(PI/t),sin(PI/t)),wn(1,0);
            for ( j=s; j<s+t; j++ ) {
                a=x[j]; b=x[j+t]*wn;
                x[j]=a+b; x[j+t]=a-b;
                wn=wn*wo;
            }
        }
    }
}
void dit_fft( vir *x, int len, int loglen ) {
    int i,j,s,t=len>>1;
    for ( i=0; i<loglen; i++,t>>=1 ) {
        for ( s=0; s<len; s+=t+t ) {
            vir a,b,wn(1,0),wo(cos(PI/t),-sin(PI/t));
            for ( j=s; j<s+t; j++ ) {
                a=x[j]+x[j+t]; b=(x[j]-x[j+t])*wn;
                x[j]=a; x[j+t]=b;
                wn=wn*wo;
            }
        }
    }
    change(x,len,loglen);
    for ( i=0; i<len; i++ ) x[i].re/=len;
}

char a[N],b[N];
int ans[2*N];

int main()
{
	int na,nb,len=1,loglen=0;
	while(scanf("%s%s",a,b)==2)
	{
		for(int i=2*N-1;i>=0;i--)
			x1[i]=x2[i]=0.0;
		for(na=0;a[na];na++);
		for(nb=0;b[nb];nb++);
		for(int i=na-1;i>=0;i--)
			x1[i]=(double)(a[na-i-1]-'0');
		for(int i=nb-1;i>=0;i--)
			x2[i]=(double)(b[nb-i-1]-'0');
		while(len<=2*max(na,nb)+5)
		{
			len*=2;
			loglen++;
		}
		fft(x1,len,loglen);
		fft(x2,len,loglen);
		for(int i=0;i<len;i++)
			x1[i]=x1[i]*x2[i];
		dit_fft(x1,len,loglen);
		for(int i=len-1;i>=0;i--)
			ans[i]=(int)round(x1[i].re+0.01);
		for(int i=0;i<len;i++)
		{
			if(ans[i]>=10)
			{
				ans[i+1]+=ans[i]/10;
				ans[i]%=10;
			}
		}
		bool zero=0;
		for(int i=len-1;i>=0;i--)
		{
			//printf("%d\n",ans[i]);
			if(zero)
				printf("%d",ans[i]);
			else if(ans[i]>0)
			{
				printf("%d",ans[i]);
				zero=1;
			}
		}
		if(!zero)
			printf("0");
		puts("");
	}
	return 0;
}
