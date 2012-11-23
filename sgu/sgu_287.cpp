#include <stdio.h>
#include <string.h>
long long f[5000000];
long long n;
int m;
int main(){
	int i;
	scanf("%I64d %d",&n,&m);
	for (i=1;i<=m;i++) f[i]=0;
	f[m+1]=1;
	for (i=m+2;f[i-1]<n;i++) f[i]=f[i-1]+1+f[i-m-1];
	printf("%d\n",i-1);
	return 0;
}
