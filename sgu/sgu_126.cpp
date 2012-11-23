#include <stdio.h>
int n,m;
int gcd(int a,int b){return b==0 ? a : gcd(b,a%b);}
int main(){
	int i,j,k;
	scanf("%d %d",&n,&m);
	if (n==0 || m==0){
		printf("0\n");
		return 0;
	}
	k=gcd(n,m);
	k=(n+m)/k;
	long long t=1;
	for (i=0;t<k;i++,t=t+t);
	if (t==k) printf("%d\n",i);else printf("-1\n");
	return 0;
}
