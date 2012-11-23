#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 5010
#define maxm 100010

using namespace std;

int st[maxn],aim[maxn<<1],nxt[maxn<<1],w[maxn<<1],ln;
int father[maxn];
int fp[15][maxn];
int level[maxn],dis[maxn];
int e[maxm][3],en,ew[maxm];
int idx[maxm];
int ans[maxn];
int n,m;
void in_edge(int x,int y,int z){
	aim[ln]=y;
	nxt[ln]=st[x];
	w[ln]=z;
	st[x]=ln++;
}
void dfs(int x){
	for (int i=st[x];i!=-1;i=nxt[i])
		if (level[aim[i]]==-1){
			level[aim[i]]=level[x]+1;
			fp[0][aim[i]]=x;
			dis[aim[i]]=dis[x]+w[i];
			dfs(aim[i]);
		}
}
bool cmp(int x,int y){
	return ew[x]<ew[y];
}
int lca(int x,int y){
	if (level[x]<level[y]) swap(x,y);
	for (int i=14;i>=0;i--)
		if (level[x]-(1<<i)>=level[y]) x=fp[i][x];
	if (x==y) return x;
	for (int i=14;i>=0;i--)
		if (fp[i][x]!=fp[i][y]){
			x=fp[i][x];
			y=fp[i][y];
		}
	return fp[0][x];
}
int Find(int x){return father[x]= father[x]==x?x:Find(father[x]);}
int main(){
	scanf("%d%d",&n,&m);
	memset(st,-1,sizeof(st));
	ln=0;
	en=0;
	for (int i=0;i<m;i++){
		int u,v,len,t;
		scanf("%d%d%d%d",&u,&v,&len,&t);
		if (t){
			in_edge(u,v,len);
			in_edge(v,u,len);
		}else {
			e[en][0]=u;
			e[en][1]=v;
			e[en++][2]=len;
		}
	}
	memset(level,-1,sizeof(level));
	level[1]=0;
	fp[0][1]=-1;
	dis[1]=0;
	dfs(1);
	for (int j=1;j<15;j++)
		for (int i=1;i<=n;i++)
			if (fp[j-1][i]>-1) fp[j][i]=fp[j-1][fp[j-1][i]];else fp[j][i]=-1;
	for (int i=1;i<=n;i++) father[i]=i;
	for (int i=0;i<en;i++) idx[i]=i;
	for (int i=0;i<en;i++) ew[i]=dis[e[i][0]]+dis[e[i][1]]+e[i][2];
	sort(idx,idx+en,cmp);
	memset(ans,-1,sizeof(ans));
	for (int i=0;i<en;i++){
		int k=idx[i];
		int u=e[k][0],v=e[k][1],r=lca(u,v);
		for (int i=Find(u);i!=Find(r);){
			int p=Find(fp[0][i]);
			ans[i]=ew[k]-dis[i];
			father[i]=p;
			i=p;
		}
		for (int i=Find(v);i!=Find(r);){
			int p=Find(fp[0][i]);
			ans[i]=ew[k]-dis[i];
			father[i]=p;
			i=p;
		}
	}
	for (int i=2;i<n;i++) printf("%d ",ans[i]);
	printf("%d\n",ans[n]);
	return 0;
}
