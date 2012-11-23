#include <stdio.h>
#include <string.h>
#define maxn 1010
int f[maxn][2][2];
int a[maxn];
int n;
int ans;
int main(){
	int i,j,k;
	scanf("%d",&n);
	for (i=1;i<=n;i++) scanf("%d",a+i);
	memset(f,0,sizeof(f));
	f[0][0][0]=1;
	for (i=1;i<=n;i++)
		for (j=0;j<2;j++)
			for (k=0;k<2;k++)
				if (f[i-1][j][k]>0){
					if (i==1 || (i>1 && j+k==a[i-1])) f[i][0][j]+=f[i-1][j][k];
					if (i==1 || (i>1 && j+k+1==a[i-1])) f[i][1][j]+=f[i-1][j][k];
				}
	ans=0;
	for (i=0;i<2;i++)
		for (j=0;j<2;j++)
			if (i+j==a[n]) ans+=f[n][i][j];
	printf("%d\n",ans);
	return 0;
}
