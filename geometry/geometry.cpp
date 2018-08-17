#include <bits/stdc++.h>
#define PB push_back
#define F first
#define S second
#define SZ(x) ((int)(x).size())
#define ALL(x) (x).begin(),(x).end()
#define MP make_pair
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
typedef vector<int> VI;

typedef double tp;
typedef double db;

const tp PI = acos(-1.0);
const tp INF = 1e18;
const tp EPS = 1e-9;

bool eq(tp a, tp b) {
	return a-b<=EPS && b-a<=EPS;
}
bool lt(tp a, tp b) {
	return a < b-EPS;
}
bool le(tp a, tp b) {
	return lt(a, b) or eq(a, b);
}
bool gt(tp a, tp b) {
	return lt(b, a);
}
bool ge(tp a, tp b) {
	return le(b, a);
}

struct coor {
	tp x, y;
	coor(tp _x=0, tp _y=0): x(_x), y(_y) {}
	coor operator+(const coor p) const {
		return coor(x+p.x, y+p.y);
	}
	coor operator-(const coor p) const {
		return coor(x-p.x, y-p.y);
	}
	coor operator*(const tp a) const {
		return coor(x*a, y*a);
	}
	coor operator/(const tp a) const {
		return coor(x/a, y/a);
	}
	tp operator*(const coor p) const {
		return x*p.x + y*p.y;
	}
	tp operator%(const coor p) const {
		return x*p.y - y*p.x;
	}
	bool operator<(const coor p) const {
		if(y*p.y<0)
			return y>0;
		if(y==0 and x>0)
			return true;
		if(p.y==0 and p.x>0)
			return false;
		return (*this)%p>0;
	}
	bool operator==(const coor p) const {
		return eq(x, p.x) && eq(y, p.y);
	}
	void input() {
		cin >> x >> y;
	}
};

tp abs2(const coor a) {
	return a*a;
}
db abs(const coor a) {
	return sqrt((db)(a*a));
}

coor line_inter(const coor p1, const coor v1, const coor p2, const coor v2) // intersection
{
	if(eq(v1%v2, 0.0))
		return coor(INF, INF);
	tp k = ((p2-p1)%v2) / (v1%v2);
	return p1 + v1*k;
}
void CircleInter(coor o1, tp r1, coor o2, tp r2) {
	if(r2>r1)
		swap(r1, r2), swap(o1, o2);
	tp d = abs(o2-o1);
	coor v = o2-o1;
	v = v / abs(v);
	coor t = coor(v.y, -v.x);

	tp area;
	vector<coor> pts;
	if(d > r1+r2+EPS)
		area = 0;
	else if(d < r1-r2)
		area = r2*r2*PI;
	else if(r2*r2+d*d > r1*r1){
		tp x = (r1*r1 - r2*r2 + d*d) / (2*d);
		tp th1 = 2*acos(x/r1), th2 = 2*acos((d-x)/r2);
		area = (r1*r1*(th1 - sin(th1)) + r2*r2*(th2 - sin(th2))) / 2;
		tp y = sqrt(r1*r1 - x*x);
		pts.PB(o1 + v*x + t*y), pts.PB(o1 + v*x - t*y);
	} else {
		tp x = (r1*r1 - r2*r2 - d*d) / (2*d);
		tp th1 = acos((d+x)/r1), th2 = acos(x/r2);
		area = r1*r1*th1 - r1*d*sin(th1) + r2*r2*(PI-th2);
		tp y = sqrt(r2*r2 - x*x);
		pts.PB(o2 + v*x + t*y), pts.PB(o2 + v*x - t*y);
	}
	//Area: area
	//Intersections: pts
}

typedef vector<coor> VP;

// Convex Hull
bool cmp(coor a, coor b) {
	if(a.x != b.x)
		return a.x < b.x;
	return a.y < b.y;
}
// keep redundant points or not
VP CH(VP arr, bool keep=false) {
	sort(ALL(arr), cmp);
	VP upper, lower;
	for(int i=0; i<SZ(arr); i++) {
		if(i>0 and arr[i] == arr[i-1])
			continue;
		coor c = arr[i];
		while(SZ(upper)>=2) {
			int last = SZ(upper)-1;
			coor a = upper[last-1], b=upper[last];
			if(lt((c-a)%(b-a), 0) or (!keep and le((c-a)%(b-a), 0)))
				upper.pop_back();
			else
				break;
		}
		upper.PB(c);
		while(SZ(lower)>=2) {
			int last = SZ(lower)-1;
			coor a = lower[last-1], b=lower[last];
			if(gt((c-a)%(b-a), 0) or (!keep and ge((c-a)%(b-a), 0)))
				lower.pop_back();
			else
				break;
		}
		lower.PB(c);
	}
	for(int i=SZ(upper)-2; i>0; i--)
		lower.PB(upper[i]);
	return lower;
}

int main() {
	return 0;
}
