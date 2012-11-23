#include <stdio.h>
#include <string.h>
#define maxn 101
int deg[7];
int g[7][7][maxn],gn[7][7];
int f[7];
int a[maxn],b[maxn],tag[maxn];
int n;
int find(int x){return f[x]= f[x]==x ? x : find(f[x]);}
void dfs(int step,int x){
	int i,j;
	if (step==n) return;
	for (i=0;i<7;i++)
		for (j=0;j<gn[x][i];j++)
			if (!tag[g[x][i][j]])
				if (step==n-1 || deg[i]>1){
					deg[x]--;
					deg[i]--;
					tag[g[x][i][j]]=1;
					printf("%d ",g[x][i][j]+1);
					if (a[g[x][i][j]]==x && b[g[x][i][j]]==i) printf("+\n");else printf("-\n");
					dfs(step+1,i);
					return;
				}
}
int check(){
	int i,j,k=-1;
	for (i=0;i<7;i++)
		if (deg[i]>0)
			if (k==-1) k=find(i);else
				if (find(i)!=k) return 0;
	for (i=k=0;i<7;i++)
		if (deg[i]%2==1) k++;
	if (k==1 || k>2) return 0;
	memset(tag,0,sizeof(tag));
	if (k>0){
		for (i=0;i<7;i++)
			if (deg[i]%2==1){
				dfs(0,i);
				return 1;
			}
	}else 
		for (i=0;i<7;i++)
			if (deg[i]>0){
				dfs(0,i);
				return 1;
			}
}
int main(){
	int i,j,k;
	scanf("%d",&n);
	for (i=0;i<7;i++) f[i]=i;
	memset(gn,0,sizeof(gn));
	for (i=0;i<n;i++){
		scanf("%d %d",a+i,b+i);
		g[a[i]][b[i]][gn[a[i]][b[i]]++]=i;
		g[b[i]][a[i]][gn[b[i]][a[i]]++]=i;
		deg[a[i]]++,deg[b[i]]++;
		f[find(a[i])]=find(b[i]);
	}
	if (!check()) printf("No solution\n");
	return 0;
}
