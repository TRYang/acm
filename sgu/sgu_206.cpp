#include <stdio.h>
#include <string.h>
#define maxn 410
int cost[maxn];
int father[70],level[70];
int w[maxn][maxn];
int lx[maxn],ly[maxn];
int sx[maxn],sy[maxn];
int match[maxn];
int g[70][70];
int n,m,ny;
void dfs(int x){
	for (int i=1;i<=n;i++)
		if (g[x][i]>0 && level[i]==-1){
			level[i]=level[x]+1;
			father[i]=x;
			dfs(i);
		}
}
int max(int x,int y){return x>y?x:y;}
void Make(int p,int u,int v,int c){
	if (u==v) return;
	if (level[u]>level[v]){
		int k=g[father[u]][u];
		w[k][p]=max(w[k][p],cost[k]-c);
		Make(p,father[u],v,c);
	}else{
		int k=g[father[v]][v];
		w[k][p]=max(w[k][p],cost[k]-c);
		Make(p,u,father[v],c);
	}
}
int DFS(int x){
	sx[x]=1;
	for (int i=1;i<=ny;i++)
		if (!sy[i] && lx[x]+ly[i]==w[x][i]){
			sy[i]=1;
			if (match[i]==-1 || DFS(match[i])){
				match[i]=x;
				return 1;
			}
		}
	return 0;
}
void Best_match(){
	int i,j,k;
	for (i=1;i<n;i++){
		lx[i]=-100000000;
		for (j=1;j<=ny;j++) lx[i]=max(lx[i],w[i][j]);
	}
	memset(ly,0,sizeof(ly));
	memset(match,-1,sizeof(match));
	for (i=1;i<n;i++)
		while (1){
			memset(sx,0,sizeof(sx));
			memset(sy,0,sizeof(sy));
			if (DFS(i)) break;
			int d=100000000;
			for (j=1;j<n;j++)
				if (sx[j])
					for (k=1;k<=ny;k++)
						if (!sy[k] && lx[j]+ly[k]-w[j][k]<d) d=lx[j]+ly[k]-w[j][k];
			for (j=1;j<n;j++)
				if (sx[j]) lx[j]-=d;
			for (j=1;j<=ny;j++) 
				if (sy[j]) ly[j]+=d;
		}
}
int main(){
	int i,j,k;
	scanf("%d %d",&n,&m);
	memset(g,0,sizeof(g));
	for (i=1;i<n;i++){
		scanf("%d %d %d",&j,&k,cost+i);
		g[j][k]=g[k][j]=i;
	}
	memset(level,-1,sizeof(level));
	level[1]=0;
	dfs(1);
	memset(w,0,sizeof(w));
	for (i=n;i<=m;i++){
		scanf("%d %d %d",&j,&k,cost+i);
		Make(i-n+1,j,k,cost[i]);
	}
	ny=m-n+1;
	if (ny<n-1) ny=n-1;
	Best_match();
	for (i=1;i<n;i++) cost[i]-=lx[i];
	for (i=n;i<=m;i++) cost[i]+=ly[i-n+1];
	for (i=1;i<=m;i++) printf("%d\n",cost[i]);
	return 0;
}
