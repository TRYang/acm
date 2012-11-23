#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 15

using namespace std;

int edge[100][2],en;
int idx[maxn],deg[maxn],rank[maxn];
int a[maxn][maxn],an[maxn];
int n,m;
int r[maxn];
int tag[maxn][maxn];
int ansp[maxn];
int ans;
int check(int x){
	for (int i=0;i<an[x];i++){
		int c1=a[x][i]>>4,c2=(a[x][i]&15);
		if (tag[r[c1]][r[c2]]){
			for (int j=i-1;j>=0;j--){
				c1=a[x][j]>>4;
				c2=(a[x][j]&15);
				tag[r[c1]][r[c2]]--;
			}
			return 0;
		}
		tag[r[c1]][r[c2]]++;
	}
	return 1;
}
void remove(int x){
	for (int i=0;i<an[x];i++){
		int c1=(a[x][i]>>4),c2=(a[x][i]&15);
		tag[r[c1]][r[c2]]--;
	}
}
void dfs(int dep,int dn){
	if (dep==n){
		if (dn<ans){
			ans=dn;
			memcpy(ansp,r,sizeof(r));
		}
		return;
	}
	if (dn>=ans) return;
//	for (int i=0;i<dn;i++){
	int x=idx[dep];
	for (int i=dn-1;i>=0;i--){
		r[x]=i;
		if (check(x)){
			dfs(dep+1,dn);
			remove(x);
		}
		r[x]=-1;
	}
	r[x]=dn;
	if (check(x)){
		dfs(dep+1,dn+1);
		remove(x);
	}
	r[x]=-1;
}
bool cmp(int x,int y){
	return deg[x]>deg[y];
}
int main(){
	scanf("%d%d",&n,&m);
	for (int i=0;i<m;i++){
		char buffer[5];
		scanf("%s",buffer);
		int c1=buffer[0]-'a',c2=buffer[1]-'a';
		edge[en][0]=c1;
		edge[en++][1]=c2;
		if (c1!=c2){
			deg[c1]++;
			deg[c2]++;
		}else deg[c1]++;
	}
	for (int i=0;i<n;i++) idx[i]=i;
	sort(idx,idx+n,cmp);
	for (int i=0;i<n;i++) rank[idx[i]]=i;
	for (int i=0;i<en;i++){
		int u=edge[i][0],v=edge[i][1];
		if (rank[u]>=rank[v]){
			a[u][an[u]++]=(u<<4)|v;
		}else{
			a[v][an[v]++]=(u<<4)|v;
		}
	}
//	for (int i=0;i<n;i++){
//		printf("%d:\n",i);
//		for (int j=0;j<an[i];j++) printf("%d %d\n",a[i][j]>>4,a[i][j]&15);
//	}
	ans=n;
	for (int i=0;i<n;i++) ansp[i]=i;
	dfs(0,0);
	printf("%d\n",ans);
	memset(an,0,sizeof(an));
	for (int i=0;i<n;i++) a[ansp[i]][an[ansp[i]]++]=i;
	for (int i=0;i<ans;i++){
		for (int j=0;j<an[i];j++) printf("%c",'a'+a[i][j]);
		puts("");
	}
	return 0;
}
