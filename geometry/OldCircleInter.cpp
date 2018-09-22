void CircleInter(coor o1, db r1, coor o2, db r2) {
	if(r2>r1)
		swap(r1, r2), swap(o1, o2);
	db d = (o2-o1).abs();
	coor v = o2-o1;
	v = v / v.abs();
	coor t = coor(v.y, -v.x);

	db area;
	vector<coor> pts;
	if(d > r1+r2+EPS)
		area = 0;
	else if(d < r1-r2)
		area = r2*r2*PI;
	else if(r2*r2+d*d > r1*r1){
		db x = (r1*r1 - r2*r2 + d*d) / (2*d);
		db th1 = 2*acos(x/r1), th2 = 2*acos((d-x)/r2);
		area = (r1*r1*(th1 - sin(th1)) + r2*r2*(th2 - sin(th2))) / 2;
		db y = sqrt(r1*r1 - x*x);
		pts.PB(o1 + v*x + t*y), pts.PB(o1 + v*x - t*y);
	} else {
		db x = (r1*r1 - r2*r2 - d*d) / (2*d);
		db th1 = acos((d+x)/r1), th2 = acos(x/r2);
		area = r1*r1*th1 - r1*d*sin(th1) + r2*r2*(PI-th2);
		db y = sqrt(r2*r2 - x*x);
		pts.PB(o2 + v*x + t*y), pts.PB(o2 + v*x - t*y);
	}
	//Area: area
	//Intersections: pts
}
