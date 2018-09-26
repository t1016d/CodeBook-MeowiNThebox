typedef vector<coor> poly;
void cut(poly &tar, const coor vec, const db c) {
	poly tmp;
	coor st = tar[0];
	tar.PB(st);
	for(int k = 1; k < SZ(tar); k++) {
		coor ed = tar[k];
		db a = st*vec, b = ed*vec;
		coor v2 = st * ((b-c)/(b-a)) + ed * ((c-a)/(b-a));

		if(le(a, c)) 
			tmp.PB(st);
		if((lt(a, c) and gt(b, c)) || (gt(a, c) and lt(b, c)))
			tmp.PB(v2);
		st = ed;
	}
	tar.clear();
	for(int i=0; i<SZ(tmp); i++)
		tar.PB(tmp[i]);
}

void polyIntersect(poly &P, const poly &Q) {
	for(int i=0; i<SZ(Q); i++) {
		coor v = perp(Q[(i+1)%SZ(Q)]-Q[i])*(-1);
		v = v/abs(v);
		cut(P, v, v*Q[i]);
	}
}
