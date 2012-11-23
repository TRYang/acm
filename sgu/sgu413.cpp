#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <bitset>
#define maxn 110
#define maxm 1010

using namespace std;

int father[maxn],tot[maxn];
int tag[maxn];
int a[maxn][maxn],an[maxn];
int ans[maxn];
int n,m;
int N;
void in_edge(int x,int y){
	a[x][an[x]++]=y;
}
int Find(int x){
	return father[x]= father[x]==x?x:Find(father[x]);
}
void dfs(int x){
	tag[x]=1;
	for (int i=0;i<an[x];i++){
		int u=a[x][i];
		if (tag[u]) continue;
		dfs(u);
		if (ans[u]==-1){
			father[u]=x;
			tot[x]+=tot[u];
		}
	}
	if (tot[x]>1){
		ans[x]=++N;
	}
}
int work(int root){
	memset(tag,0,sizeof(tag));
	for (int i=0;i<n;i++) father[i]=i;
	for (int i=0;i<n;i++) tot[i]=1;
	memset(ans,-1,sizeof(ans));
	N=0;
	dfs(root);
	return ans[root]!=-1;
}
int main(){
	int tn;
	for (scanf("%d",&tn);tn;tn--){
		scanf("%d%d",&n,&m);
		memset(an,0,sizeof(an));
		for (int i=0;i<m;i++){
			int u,v;
			scanf("%d%d",&u,&v);
			--u,--v;
			in_edge(u,v);
			in_edge(v,u);
		}
		for (int i=0;i<n;i++) random_shuffle(a[i],a[i]+an[i]);
		for (int i=0;i<n;i++)
			if (work(i)) break;
		for (int i=0;i<n-1;i++) printf("%d ",ans[Find(i)]);
		printf("%d\n",ans[Find(n-1)]);
	}
	return 0;
}
