int ori(const coor o, const coor a, const coor b) {
	tp val = (a-o)%(b-o);
	return gt(val, 0) - lt(val, 0);
}
bool SegmentIntersect(const coor p1, const coor p2, const coor q1, const coor q2) {
	if( eq((p2-p1)%(q2-q1), 0) ) {
		if( ori(p1, p2, q1) )	return false;
		return le( ( p1 - q1 ) * ( p2 - q1 ), 0) ||
		       le( ( p1 - q2 ) * ( p2 - q2 ), 0) ||
			   le( ( q1 - p1 ) * ( q2 - p1 ), 0) ||
			   le( ( q1 - p2 ) * ( q2 - p2 ), 0);
	}
	return (ori( p1, p2, q1 ) * ori( p1, p2, q2 ) <= 0) &&
	       (ori( q1, q2, p1 ) * ori( q1, q2, p2 ) <= 0);
}
