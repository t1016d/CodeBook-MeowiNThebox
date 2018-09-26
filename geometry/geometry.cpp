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

const db PI = acos(-1.0);
const tp INF = 1e18;
const tp EPS = 1e-9;

bool eq(tp a, tp b) { return a-b<=EPS && b-a<=EPS; }
bool lt(tp a, tp b) { return a < b-EPS; }
bool le(tp a, tp b) { return !lt(b, a); }
bool gt(tp a, tp b) { return lt(b, a); }
bool ge(tp a, tp b) { return !lt(a, b); }

struct coor {
	tp x, y, z;
	coor(tp _x=0, tp _y=0, tp _z=0): x(_x), y(_y), z(_z) {}
	coor operator+(const coor p) const { return coor(x+p.x, y+p.y, z+p.z); }
	coor operator-(const coor p) const { return coor(x-p.x, y-p.y, z-p.z); }
	coor operator*(const tp a) const { return coor(x*a, y*a, z*a); }
	coor operator/(const tp a) const { return coor(x/a, y/a, z/a); }
	tp operator*(const coor p) const { return x*p.x + y*p.y + z*p.z; }
	db atan() const {
		db ret = atan2(y, x);
		if(ret<0)	ret += 2*PI;
		return ret;
	}
	bool operator==(const coor p) const { return eq(x, p.x) && eq(y, p.y) && eq(z, p.z); }
	void input() { cin >> x >> y; }
	// 2D only
	tp operator%(const coor p) const { return x*p.y - y*p.x; }
	bool operator<(const coor p) const {
		if(x != p.x)	return x<p.x;
		if(y != p.y)	return y<p.y;
		return z<p.z;
	}
};
tp abs2(const coor a) { return a.x*a.x+a.y*a.y+a.z*a.z; }
db abs(const coor a) { return sqrt(abs2(a)); }
coor perp(const coor p) { return coor(-p.y, p.x); } // +0.5pi

bool polar(const coor a, const coor b) {
	// integral
	if(a.y*b.y<0)			return a.y>0;
	if(b.y==0 and b.x>0)	return false;
	if(a.y==0 and a.x>0)	return true;
	return a%b>0;
	//floating
	return a.atan() < b.atan();
}

