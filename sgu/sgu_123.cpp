#include <stdio.h>
long long f[41],ans;
int n;
int main(){
	int i,j,k;
	scanf("%d",&n);
	f[0]=f[1]=1;
	for (i=2;i<n;i++) f[i]=f[i-1]+f[i-2];
	ans=0;
	for (i=0;i<n;i++) ans+=f[i];
	printf("%I64d\n",ans);
	return 0;
}
