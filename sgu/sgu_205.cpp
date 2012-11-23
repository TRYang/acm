#include <stdio.h>
#include <string.h>
#define maxn 1010
#define maxm 130
#define INF 1000000000
int f[maxn][maxm];
int d[maxm][maxm];
int b[maxn];
int a[maxn];
int n,m,s;
int min(int x,int y){return x<y?x:y;}
int aabs(int x){return x>=0?x:-x;}
void Find(int x,int y){
	if (x==0) return;
	b[x]=y;
	for (int i=0;i<s;i++)
		if (f[x-1][i]+aabs(a[x]-d[(i&(m-1))][y])==f[x][y]){
			Find(x-1,i);
			return;
		}
}
int main(){
	int i,j,k;
	scanf("%d",&n);
	for (i=1;i<=n;i++) scanf("%d",a+i);
	scanf("%d %d",&m,&s);
	for (i=0;i<m;i++)
		for (j=0;j<s;j++) scanf("%d",&d[i][j]);
	for (i=0;i<s;i++) f[0][i]=INF;
	f[0][0]=0;
	for (i=1;i<=n;i++)
		for (j=0;j<s;j++){
			f[i][j]=INF;
			for (k=0;k<s;k++) f[i][j]=min(f[i][j],f[i-1][k]+aabs(a[i]-d[(k&(m-1))][j]));
		}
	int ans=INF;
	for (i=0;i<s;i++) ans=min(ans,f[n][i]);
	printf("%d\n",ans);
	for (i=0;i<s;i++)
		if (f[n][i]==ans){
			Find(n,i);
			break;
		}
	for (i=1;i<=n;i++) printf("%d ",b[i]);
	printf("\n");
	return 0;
}
