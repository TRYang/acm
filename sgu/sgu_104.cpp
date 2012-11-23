#include <stdio.h>
#include <string.h>
#define maxn 101
int a[maxn][maxn],ans[maxn];
int f[maxn][maxn],g[maxn][maxn];
int n,m;
int main(){
	int i,j,k,p;
	scanf("%d %d",&n,&m);
	for (i=1;i<=n;i++)
		for (j=1;j<=m;j++) scanf("%d",&a[i][j]);
	memset(f,0,sizeof(f));
	for (i=1;i<=n;i++){
		k=f[i-1][i-1];
		p=i-1;
		for (j=i;j<=m;j++){
			f[i][j]=k+a[i][j];
			g[i][j]=p;
			if (f[i-1][j]>k) k=f[i-1][j],p=j;
		}
	}
	for (k=-100000,i=n;i<=m;i++)
		if (f[n][i]>k) k=f[n][i],j=i;
	printf("%d\n",k);
	for (i=n;i>0;i--){
		ans[i]=j;
		j=g[i][j];
	}
	for (i=1;i<=n;i++) printf("%d ",ans[i]);printf("\n");
	return 0;
}
