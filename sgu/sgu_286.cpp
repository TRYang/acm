#include <stdio.h>
#include <string.h>
#define maxn 1010
int b[maxn][maxn];
bool g[maxn][maxn];
bool a[maxn][maxn];
int q[maxn*maxn];
int r[maxn];
int deg[maxn];
int from[maxn],tag[maxn];
int n,m;
void Make(){
	int i,p,qn=0,k;
	memset(tag,0,sizeof(tag));
	for (i=1;i<=n;i++)
		if (deg[i]>0){
			tag[i]=1;
			q[qn++]=i;
		}
	for (p=0;p<qn;p++){
		tag[q[p]]=0;
		if (deg[q[p]]==0) continue;
		int rn=1;
		r[0]=q[p];
		while (1){
			k=r[rn-1];
			for (i=1;i<=n;i++)
				if (g[k][i]){
					deg[k]--;deg[i]--;
					g[k][i]=g[i][k]=0;
					a[k][i]=1;
					r[rn++]=i;
					break;
				}
			if (r[rn-1]==q[p]) break;
		}
		for (i=0;i<rn-2;i++)
			if (deg[r[i]]>0 && !tag[r[i]]){
				tag[r[i]]=1;
				q[qn++]=r[i];
			}
	}
}
int dfs(int x){
	if (tag[x]) return 0;
	tag[x]=1;
	for (int i=1;i<=n;i++)
		if (a[x][i])
			if (from[i]==-1 || dfs(from[i])){
				from[i]=x;
				return 1;
			}
	return 0;
}
int main(){
	int i,j,k;
	scanf("%d %d",&n,&m);
	memset(g,0,sizeof(g));
	memset(deg,0,sizeof(deg));
	for (i=0;i<n*m>>1;i++){
		scanf("%d %d",&j,&k);
		g[j][k]=g[k][j]=1;
		b[j][k]=b[k][j]=i+1;
		deg[j]++;
		deg[k]++;
	}
	memset(a,0,sizeof(a));
	Make();
	memset(from,-1,sizeof(from));
	k=0;
	for (i=1;i<=n;i++){
		memset(tag,0,sizeof(tag));
		if (dfs(i)) k++;
	}
	if (k<n) printf("NO\n");else{
		printf("YES\n");
		for (i=1;i<=n;i++) printf("%d\n",b[from[i]][i]);
	}
	return 0;
}
