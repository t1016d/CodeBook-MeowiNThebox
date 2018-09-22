typedef vector<coor> VP;

// Convex Hull
// keep redundant points or not
VP CH(VP arr, bool keep=false) {
	sort(ALL(arr));
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
