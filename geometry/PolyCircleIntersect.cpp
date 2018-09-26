// Divides into multiple triangle, and sum up
// oriented area
int sign(db x) { return x < 0 ? -1 : x > 0; }
db area2(coor pa, coor pb, db r){
	if( abs(pa) < abs(pb) ) swap(pa, pb);
	if( abs(pb) < EPS ) return 0;
	db S, h, theta;
	db a = abs( pb ), b = abs( pa ), c = abs(pb - pa);
	db cosB = (pb * (pb - pa)) / a / c, B = acos(cosB);
	db cosC = (pa * pb) / a / b, C = acos(cosC);
	if(a > r){
		S = (C/2)*r*r;
		h = a*b*sin(C)/c;
		if (h < r && B < PI/2) S -= (acos(h/r)*r*r - h*sqrt(r*r-h*h));
	}else if(b > r){
		theta = PI - B - asin(sin(B)/r*a);
		S = .5*a*r*sin(theta) + (C-theta)/2*r*r;
	}else S = .5*sin(C)*a*b;
	return S;
}
db area(coor ori, db r, const poly &P) {
	db S = 0;
	int n = SZ(P);
	for(int i = 0; i < n; ++i) {
		coor v1=P[i]-ori, v2=P[(i+1)%n]-ori;
		S += area2(v1, v2, r) * sign(v1%v2);
	}
	return fabs(S);
}
