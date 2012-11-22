#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 2010

using namespace std;

int g[maxn][maxn],gn[maxn];
int a[maxn][maxn],b[maxn][maxn];
int ans[maxn][4],ansn;
int stack[maxn],stn;
int tag[maxn];
int n;
void Del(int u,int v){
	ans[ansn][2]=u;
	ans[ansn++][3]=v;
	b[u][v]=b[v][u]=0;
	for (int i=0;i<gn[u];i++)
		if (g[u][i]==v){
			swap(g[u][i],g[u][gn[u]-1]);
			--gn[u];
			break;
		}
	for (int i=0;i<gn[v];i++)
		if (g[v][i]==u){
			swap(g[v][i],g[v][gn[v]-1]);
			--gn[v];
			break;
		}
}
void dfs(int x,int des){
	stack[++stn]=x;
	tag[x]=1;
	if (x==des){
		for (int i=1;i<stn;i++)
			if (!a[stack[i]][stack[i+1]]){
				int tu=stack[i],tv=stack[i+1];
				Del(tu,tv);
				break;
			}
		return;
	}
	for (int i=0;i<gn[x];i++)
		if (!tag[g[x][i]]) dfs(g[x][i],des);
	--stn;
}
void build(int u,int v){
	memset(tag,0,sizeof(tag));
	stn=0;
	ans[ansn][0]=u;
	ans[ansn][1]=v;
	dfs(u,v);
	b[u][v]=b[v][u]=1;
	g[u][gn[u]++]=v;
	g[v][gn[v]++]=u;
}
int main(){
	scanf("%d",&n);
	for (int i=1;i<n;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		a[u][v]=a[v][u]=1;
	}
	memset(gn,0,sizeof(gn));
	for (int i=1;i<n;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		g[u][gn[u]++]=v;
		g[v][gn[v]++]=u;
		b[u][v]=b[v][u]=1;
	}
	ansn=0;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			if (a[i][j] && !b[i][j]){
				build(i,j);
			}
	printf("%d\n",ansn);
	for (int i=0;i<ansn;i++) printf("2 %d %d %d %d\n",ans[i][0],ans[i][1],ans[i][2],ans[i][3]);
	return 0;
}
