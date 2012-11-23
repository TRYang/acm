#include <stdio.h>
#include <string.h>
#define maxn 210
#define maxm 10010
int f[maxn][maxm],g[maxn][maxm];
int a[maxn];
int tag[maxn];
int ans;
int n,m;
int main(){
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",a+i);
	memset(f,0,sizeof(f));
	f[0][0]=1;
	for (int i=0;i<n;i++)
		for (int j=0;j<=m;j++)
			if (f[i][j]){
				f[i+1][j]=1;
				if (j+a[i+1]<=m) f[i+1][j+a[i+1]]=1;
			}
	memset(g,0,sizeof(g));
	g[n+1][0]=1;
	for (int i=n;i>0;i--)
		for (int j=0;j<=m;j++)
			if (g[i+1][j]){
				g[i][j]=1;
				if (j+a[i]<=m) g[i][j+a[i]]=1;
			}
	ans=0;
	for (int i=1;i<=n;i++){
		tag[i]=1;
		for (int j=0;j<=m;j++)
			if (f[i-1][j] && g[i+1][m-j]) tag[i]=0;
		ans+=tag[i];
	}
	printf("%d\n",ans);
	for (int i=1,flag=0;i<=n;i++)
		if (tag[i]){
			if (flag) printf(" ");
			flag=1;
			printf("%d",a[i]);
		}
	return 0;
}
