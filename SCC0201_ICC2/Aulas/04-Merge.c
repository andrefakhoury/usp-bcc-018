mergesort(v, l, r) { //f
	if (l > r) return;
	m = (l+r)/2;
	mergesort(v, l, m);
	mergesort(v, m+1, r);
	merge(v, l, m, r);
}

merge(v, l, m, r) { //g
	temp = vetor de tamanho (r-l+1);
	i = l;
	j = m+1;
	k = 0;
	while(i <= m && j <= r) {
		if (v[i] <= v[j]) temp[k++] = v[i++]
		else temp[k++] = v[j++];
	}
	while(i <= m) temp[k++] = v[i++];
	while(j <= r) temp[k++] = v[j++];
	for (k = 0, i = l; k <)
}


f(n) = f(n/2) + f(n/2) + g(n);
g(n) = (n-1)*(3a+b) + a + a + b + n*(a+b)
		3an+bn-3a-b+2a+b+na+nb
	 = 4na+2bn-a

f(n) = 2*f(n/2) + g(n)
	   2*(2*f(n/4) + g(n/2)) + g(n)
	   2*(2*(2*f(n/8) + g(n/4)) + g(n/2)) + g(n)
	   2**3 f(n/8) + 2**2 g(n/4) + 2**1 g(n/2) + 2**0 g(n)
// SUBST: (n/(2**k)) = 1 ==> n = 2**k ==> log2(n) = k
	 = 2**k*(f(n/2)) + SUM[0..k-1]{2**i *g(n/2**i)}
	   2**log2(n) f(n/2**k) + ...
	   n * f(1) + ...
	 = n*f(1)  + SUM[0..k-1]{2**i g(n/2**i)}
	 = SUM[0..log2(n)-1]{2**i g(n/2**i)}
	   SUM[0..log2(n)-1]{2**i * (4an/2**i + 2bn/2**i - a)}
	 = SUM[0..log2(n)-1]{4an + 2bn - 2**i a}
	 = 4an * (log2(n)) + 2bn * (log2(n)) - SUM[0..log2(n)-1]{2**i a}
//SUM[0..log2(n)-1]{2**i a} = a*(2**log2(n) - 1)/1 = -an + a
	 = 4*a*n*log2(n) + 2*b*n*log2(n) - an + a
.: f(n) = n*log2(n)