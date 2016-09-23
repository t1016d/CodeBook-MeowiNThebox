// correct code of NPSC2013 senior-final pF

#include <bits/stdc++.h>
#define PB push_back
#define F first
#define S second
#define SZ(x) ((int)(x).size())
#define MP make_pair
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
typedef vector<int> VI;

typedef double db;
typedef pair<db, db> PDD;

PDD operator+(const PDD &a, const PDD &b) {
    return MP(a.F+b.F, a.S+b.S);
}
PDD operator-(const PDD &a, const PDD &b) {
    return MP(a.F-b.F, a.S-b.S);
}
PDD operator*(const PDD &a, const db &b) {
    return MP(a.F*b, a.S*b);
}
PDD operator/(const PDD &a, const db &b) {
    return MP(a.F/b, a.S/b);
}
db dot(const PDD &a, const PDD &b) {
    return a.F*b.F + a.S*b.S;
}
db cross(const PDD &a, const PDD &b) {
    return a.F*b.S - a.S*b.F;
}
db abs2(const PDD &a) {
	return dot(a, a);
}
db abs(const PDD &a) {
    return sqrt( abs2(a) );
}

const db PI = acos(-1);
const db INF = 1e18;
const db EPS = 1e-8;

PDD inter(const PDD &p1, const PDD &v1, const PDD &p2, const PDD &v2) // intersection
{
	if(fabs(cross(v1, v2)) < EPS)
		return MP(INF, INF);
	db k = cross((p2-p1), v2) / cross(v1, v2);
	return p1 + v1*k;
}
void CircleInter(PDD o1, db r1, PDD o2, db r2) {
	if(r2>r1)
		swap(r1, r2), swap(o1, o2);
	db d = abs(o2-o1);
	PDD v = o2-o1;
	v = v / abs(v);
	PDD t = MP(v.S, -v.F);

	db area;
	vector<PDD> pts;
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

int main() {
	return 0;
}
