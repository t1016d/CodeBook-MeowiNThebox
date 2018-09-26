//      1   1
// T =  1   0
//      0   1
//T-1=  1  -1
vector<ll> transform(vector<ll> P, bool inverse) {
	for(int len = 1; 2 * len <= SZ(P); len <<= 1) {
		for(int i = 0; i < SZ(P); i += 2 * len) {
			for(int j = 0; j < len; j++) {
				ll u = P[i + j];
				ll v = P[i + len + j];
				if (!inverse) {
					P[i + j] = u + v;
					P[i + len + j] = u;
				} else {
					P[i + j] = v;
					P[i + len + j] = u - v;
				}
			}
		}
	}
	return P;
}
