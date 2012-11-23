#include <stdio.h>
#define maxn 1010
int a[maxn][maxn],b[maxn][maxn];
int n,m;
int min(int x,int y){return x<y?x:y;}
int main(){
	int i,j,k;
	scanf("%d %d",&n,&m);
	for (i=1;i<=n;i++)
		for (j=1;j<=m;j++) scanf("%d",&a[i][j]);
	b[n][m]=a[n][m];
	for (i=n-1;i>0;i--) b[i][m]=min(b[i+1][m],a[i][m]);
	b[0][m]=b[1][m];
	for (j=m-1;j>0;j--){
		b[n][j]=min(b[n-1][j+1],a[n][j]);
		for (i=n-1;i>0;i--){
			b[i][j]=a[i][j];
			if (b[i+1][j]<b[i][j]) b[i][j]=b[i+1][j];
			if (b[i-1][j+1]<b[i][j]) b[i][j]=b[i-1][j+1];
		}
		b[0][j]=b[1][j];
	}
	for (i=1;i<=n;i++){
		for (j=1;j<=m;j++) printf("%d ",b[i][j]);
		printf("\n");
	}
	return 0;
}
