#include <stdio.h>
#include <math.h>
double l;
long long L,tot,v,t;
int n;
int main(){
	int i,j,k;
	scanf("%lf %d",&l,&n);
	L=floor(l*10000+1e-4);
	tot=0;
	for (i=0;i<n;i++){
		scanf("%I64d %I64d",&t,&v);
		tot+=t*v*10000;
		tot%=L;
	}
	if (L-tot<tot) tot=L-tot;
	printf("%.4lf\n",(double)tot/10000);
	return 0;
}
