#include <stdio.h>
#include <string.h>
#define maxn 11

typedef long long lint;

lint f[maxn][27][1<<maxn];
int a[2][100000][2],an[2];
int now,next;
int n,m;
int x;
lint v;
lint ans;

void dfs(int p,int s1,int s2,int t){
	if (p==n){
		if (f[x][t][s1]==0){
			a[next][an[next]][0]=t;
			a[next][an[next]++][1]=s1;
		}
		f[x][t][s1]+=v;
		return;
	}
	dfs(p+1,s1,s2,t);
	int k=s1|s2;
	if (p==0) k<<=1;else k>>=(p-1);
	if ((k&7)==0) dfs(p+1,s1|(1<<p),s2,t+1);
}
int main(){
	int i,j,k;
	scanf("%d %d",&n,&m);
	now=0;
	an[0]=1;
	a[0][0][0]=0;a[0][0][1]=0;
	f[0][0][0]=1;
	for (i=1;i<=n;i++){
		next=now^1;
		an[next]=0;
		for (j=0;j<an[now];j++){
			v=f[i-1][a[now][j][0]][a[now][j][1]];
			x=i;
			dfs(0,0,a[now][j][1],a[now][j][0]);
		}
		now=next;
	}
	ans=0;
	for (i=0;i<an[now];i++)
		if (a[now][i][0]==m) ans+=f[n][a[now][i][0]][a[now][i][1]];
	printf("%I64d\n",ans);
	return 0;
}
