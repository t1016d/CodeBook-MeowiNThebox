typedef pair<coor, coor> line;
bool cmp(line a, line b) {
	return polar(a.F, b.F);
}
vector<line> HalfPlaneInter(vector<line> hplanes) {
	hplanes.PB(MP(coor(1, 0), coor(-INF, -INF)));
	hplanes.PB(MP(coor(0, 1), coor(INF, -INF)));
	hplanes.PB(MP(coor(-1, 0), coor(INF, INF)));
	hplanes.PB(MP(coor(0, -1), coor(-INF, INF)));
	sort(ALL(hplanes), cmp);
	VI need;
	int boss=0;
	for(int i=1; i<SZ(hplanes); i++){
		if(!eq(hplanes[boss].F.atan(), hplanes[i].F.atan())) {
			need.PB(boss);
			boss=i;
			continue;
		}
		coor v = hplanes[i].F, u = hplanes[i].S-hplanes[boss].S;
		if(v%u>0)
			boss = i;
		if(i==SZ(hplanes)-1)
			need.PB(boss);
	}
	deque<line> dque;
	for(int i=0; i<SZ(need); i++) {
		line cur = hplanes[need[i]];
		if(i==0) {
			coor st = cur.S - cur.F/cur.F.abs()*INF;
			dque.push_back(MP(st, cur.S));
			continue;
		}
		coor st, ed;
		while(!dque.empty()) {
			line last = dque.back();
			dque.pop_back();
			coor v = last.S-last.F;
			coor p = line_inter(cur.S, cur.F, last.F, v);
			if(le((p-last.F)*(p-last.S), 0)) {
				dque.push_back(MP(last.F, p));
				st = p;
				break;
			}
		}
		if(dque.empty())
			return vector<line>();
		if(le(cur.F.atan(), PI))
			ed = st + cur.F/cur.F.abs()*INF;
		else
			while(!dque.empty()) {
				line head = dque.front();
				dque.pop_front();
				coor v = head.S-head.F;
				coor p = line_inter(cur.S, cur.F, head.F, v);
				if(le((p-head.F)*(p-head.S), 0)) {
					dque.push_front(MP(p, head.S));
					ed=p;
					break;
				}
			}
		dque.push_back(MP(st, ed));
	}
	vector<line> ret;
	while(!dque.empty()) {
		ret.PB(dque.front());
		dque.pop_front();
	}
	return ret;
}
