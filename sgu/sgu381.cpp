#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 100010
#define maxm 500010
using namespace std;
int father[maxn<<1];
int tot[maxn<<1];
int tag[maxn<<1];
int n,m;
int Find(int x){
	return father[x]= father[x]==x?x:Find(father[x]);
}
void merge(int x,int y){
	int fx=Find(x),fy=Find(y);
	if (fx==fy) return;
	father[fx]=fy;
	tot[fy]+=tot[fx];
}
int main(){
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;i++){
		father[i]=i;
		father[n+i]=n+i;
		tot[i]=0;
		tot[n+i]=1;
	}
	int flag=1;
	for (int i=0;i<m;i++){
		int u,v,w1,w2;
		scanf("%d%d%d%d",&u,&v,&w1,&w2);
		u--,v--;
		if (u==v) flag=0;
		if (w1==w2){
			merge(u,n+v);
			merge(v,n+u);
		}else{
			merge(u,v);
			merge(n+u,n+v);
		}
	}
	for (int i=0;i<n;i++)
		if (Find(i)==Find(n+i)) flag=0;
	if (flag){
//		for (int i=0;i<n;i++) printf("%d %d\n",Find(i),Find(n+i));
		memset(tag,-1,sizeof(tag));
		int ans=0;
		for (int i=0;i<n;i++){
			int u=Find(i),v=Find(n+i);
			if (tag[u]>-1) continue;
			if (tot[u]>tot[v]) swap(u,v);
			tag[u]=1;
			tag[v]=0;
			ans+=tot[u];
		}
		printf("YES\n%d\n",ans);
		for (int i=0;i<n;i++)
			if (tag[Find(n+i)]==1) printf("%d\n",i+1);
	}else puts("NO");
	return 0;
}
