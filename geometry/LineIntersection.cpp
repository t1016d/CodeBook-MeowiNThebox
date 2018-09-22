coor line_inter(const coor p1, const coor v1, const coor p2, const coor v2) { 
	if(eq(v1%v2, 0.0))
		return coor(INF, INF);
	db k = ((p2-p1)%v2) / (v1%v2);
	return p1 + v1*k;
}
