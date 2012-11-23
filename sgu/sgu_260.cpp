#include <stdio.h>
#include <string.h>
#define maxn 210
int g[maxn][maxn];
int a[maxn][maxn];
int x[maxn];
int n;
int Find(int p,int c){
	int i,j,k;
	for (i=p;i<n;i++)
		if (a[i][c]>0){
			for (j=0;j<=n;j++){
				k=a[i][j];
				a[i][j]=a[p][j];
				a[p][j]=k;
			}
			return 1;
		}
	return 0;
}
int check(int d){
	int i,j,k;
	for (i=0;i<n;i++)
		for (j=0;j<n;j++) a[i][j]=g[i][j];
	for (i=0;i<n;i++) a[i][n]=d^g[i][n];
	memset(x,-1,sizeof(x));
	int p=0;
	for (i=0;i<n;i++)
		if (Find(p,i)){
			for (j=p+1;j<n;j++)
				if (a[j][i]>0){
					for (k=i;k<=n;k++) a[j][k]^=a[p][k];
				}
			p++;
		}else x[i]=0;
	for (i=p;i<n;i++)
		if (a[i][n]>0) return 0;
	for (i=p-1;i>=0;i--){
		k=a[i][n];
		for (j=n-1;j>=0;j--)
			if (a[i][j]>0)
				if (x[j]==-1){
					x[j]=k;
					break;
				}else k^=x[j];
	}
	k=0;
	for (i=0;i<n;i++)
		if (x[i]>0) k++;
	printf("%d\n",k);
	for (i=0;i<n;i++)
		if (x[i]==1) printf("%d ",i+1);
	printf("\n");
	return 1;
}
int main(){
	int i,j,k;
	scanf("%d",&n);
	memset(g,0,sizeof(g));
	for (i=0;i<n;i++){
		for (scanf("%d",&k);k>0;k--){
			scanf("%d",&j);
			g[j-1][i]=1;
		}
	}
	for (i=0;i<n;i++) scanf("%d",&g[i][n]);
	k=-1;
	for (i=0;i<2;i++)
		if (check(i)){
			k=0;
			break;
		}
	if (k==-1) printf("-1\n");
	return 0;
}
