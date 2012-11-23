#include <stdio.h>
#include <string.h>
#define maxn 19
long long f[maxn][2];
int n,m;
int main(){
	int i,j,k;
	//freopen("test.txt","r",stdin);
	scanf("%d %d",&n,&m);
	f[1][0]=1;f[1][1]=m-1;
	for (i=2;i<=n;i++){
		f[i][0]=f[i-1][1];
		f[i][1]=(m-1)*(f[i-1][0]+f[i-1][1]);
	}
	printf("%I64d\n",f[n][1]);
	return 0;
}
