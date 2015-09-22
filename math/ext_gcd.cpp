// find one solution  (x,y)  of  ax+by=gcd(a,b)
void ext_gcd(int a,int b,int &g,int &x,int &y)
{
	if(!b){ g=a; x=1; y=0; }
	else{ ext_gcd(b, a%b, g, y, x); y -= x*(a/b); }
}
