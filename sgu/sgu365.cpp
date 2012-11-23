#include <stdio.h>
#include <string.h>
#define maxn 25
long long f[maxn][10],g[maxn][10];
int n;
int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++){
		f[i][1]=1;
		for (int j=2;j<10;j++){
			f[i][j]=1;
			for (int k=i-1;k>0;k--)
				for (int c=0;c<j;c++) f[i][j]+=f[k][c];
		}
	}
	for (int i=n;i>0;i--){
		g[i][1]=1;
		for (int j=2;j<10;j++){
			g[i][j]=1;
			for (int k=i+1;k<=n;k++)
				for (int c=0;c<j;c++) g[i][j]+=g[k][c];
		}
	}
	long long ans=0;
	for (int i=1;i<=n;i++)
		for (int j=i;j<=n;j++)
			for (int c=1;c<10;c++) ans+=f[i][c]*g[j][c];
	ans++;
	printf("%lld\n",ans);
	return 0;
}
