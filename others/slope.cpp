bool bye(PLL p1, PLL p2, PLL p3) {
    ll a1 = p1.F, b1 = p1.S;
    ll a2 = p2.F, b2 = p2.S;
    ll a3 = p3.F, b3 = p3.S;

    return (a1-a3)*(b2-b1) >= (b3-b1)*(a1-a2);
}
/* slope is decreasing */
while(SZ(ch)>=2 && bye(ch[SZ(ch)-2], ch.back(), v[i]))  ch.pop_back();
