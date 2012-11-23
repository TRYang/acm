#include <stdio.h>
#include <math.h>
typedef long long LL;
LL n,m,dn,dm;
LL f(LL x){
	for (LL i=3;i*i<=x;i+=2)
		if (x%i==0) return i;
	return 0;
}
int work(){
	if (n==2) return 0;
	if (n%2==1){
		dn=n+f(n);
		if (dn==n) return 0;
	}else dn=n;
	if (m%2==1){
		dm=m-f(m);
		if (dm==m) return 0;
	}else dm=m;
	if (dn>dm) return 0;
	if (n<dn) printf("%I64d\n",n);
	while (1){
		printf("%I64d\n",dn);
		if (dn==dm) break;
		LL t=1;
		for (LL i=2;i*i<=dn>>1;i++)
			if ((dn>>1)%i==0){
				if (dn+(i<<1)<=dm && i>t) t=i;
				if (dn+((dn>>1)/i<<1)<=dm && (dn>>1)/i>t) t=(dn>>1)/i;
			}
		dn+=t<<1;
	}
	if (dm<m) printf("%I64d\n",m);
	return 1;
 }
int main(){
	int i,j,k;
	scanf("%I64d %I64d",&n,&m);
	if (!work()) printf("Impossible\n");
	return 0;
}
