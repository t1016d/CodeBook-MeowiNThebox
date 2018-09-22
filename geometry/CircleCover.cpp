#define N 1021

struct Circ {
	coor O;
	db R;
	Circ(coor _o=0, db _r=0): O(_o), R(_r) {}
};

struct CircleCover{
	int C; Circ c[ N ];
	bool g[ N ][ N ], overlap[ N ][ N ];
	// Area[i] : area covered by at least i circles
	db Area[ N ];
	void init( int _C ){ C = _C; }
	bool CCinter( Circ& a , Circ& b , coor& p1 , coor& p2 ){
		coor o1 = a.O , o2 = b.O;
		db r1 = a.R , r2 = b.R;
		tp d2 = abs2(o1-o2);
		db d = abs(o1-o2);
		if( d > r1 + r2 ) return false;
		if( d < max(r1, r2) - min(r1, r2) ) return false;
		//if( d > r1 + r2 ) return false;
		coor u=(o1+o2)*0.5 + (o1-o2)*((r2*r2-r1*r1)/(2*d2));
		db A=sqrt((r1+r2+d)*(r1-r2+d)*(r1+r2-d)*(-r1+r2+d));
		coor v=coor( o1.y-o2.y , -o1.x + o2.x ) * A / (2*d2);
		p1 = u + v; p2 = u - v;
		return true;
	}
	struct Teve {
		coor p; db ang; int add;
		Teve() {}
		Teve(coor _a, db _b, int _c):p(_a), ang(_b), add(_c){}
		bool operator<(const Teve &a)const
		{return ang < a.ang;}
	}eve[ N * 2 ];
	int sign(db x) {
		return x < 0 ? -1 : x > 0;
	}
	// strict: x = 0, otherwise x = -1
	bool disjuct( Circ& a, Circ &b, int x )
	{return sign( abs( a.O - b.O ) - a.R - b.R ) > x;}
	bool contain( Circ& a, Circ &b, int x )
	{return sign( a.R - b.R - abs( a.O - b.O ) ) > x;}
	bool contain(int i, int j){
		/* c[j] is non-strictly in c[i]. */
		return (sign(c[i].R - c[j].R) > 0 ||
				(sign(c[i].R - c[j].R) == 0 && i < j) ) && contain(c[i], c[j], -1);
	}
	void solve(){
		for( int i = 0 ; i <= C + 1 ; i ++ )
			Area[ i ] = 0;
		for( int i = 0 ; i < C ; i ++ )
			for( int j = 0 ; j < C ; j ++ )
				overlap[i][j] = contain(i, j);
		for( int i = 0 ; i < C ; i ++ )
			for( int j = 0 ; j < C ; j ++ ) 
				g[i][j] = !(overlap[i][j] || overlap[j][i] ||
						disjuct(c[i], c[j], -1));
		for( int i = 0 ; i < C ; i ++ ){
			int E = 0, cnt = 1;
			for( int j = 0 ; j < C ; j ++ )
				if( j != i && overlap[j][i] )
					cnt ++;
			for( int j = 0 ; j < C ; j ++ )
				if( i != j && g[i][j] ){
					coor aa, bb;
					CCinter(c[i], c[j], aa, bb);
					db A=atan2(aa.y - c[i].O.y, aa.x - c[i].O.x);
					db B=atan2(bb.y - c[i].O.y, bb.x - c[i].O.x);
					eve[E ++] = Teve(bb, B, 1);
					eve[E ++] = Teve(aa, A, -1);
					if(B > A) cnt ++;
				}
			if( E == 0 ) Area[ cnt ] += PI * c[i].R * c[i].R;
			else{
				sort( eve , eve + E );
				eve[E] = eve[0];
				for( int j = 0 ; j < E ; j ++ ){
					cnt += eve[j].add; 
					Area[cnt] += (eve[j].p % eve[j + 1].p) * .5;
					db theta = eve[j + 1].ang - eve[j].ang;
					if (theta < 0) theta += 2. * PI;
					Area[cnt] +=
						(theta - sin(theta)) * c[i].R*c[i].R * .5;
				}
			}
		}
	}
} oracle;
