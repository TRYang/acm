#include <stdio.h>
long long f[61];
int n;
int main(){
	int i,j,k;
	scanf("%d",&n);
	f[0]=1;
	for (i=2;i<=n<<1;i+=2){
		f[i]=0;
		for (j=0;j<=i-2;j++) f[i]+=f[j]*f[i-2-j];
	}
	printf("%I64d %d\n",f[n<<1],n+1);
	return 0;
}
