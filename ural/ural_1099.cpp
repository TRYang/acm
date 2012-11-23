#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
#define maxn 300
#define maxm 90010

using namespace std;

int match[maxn];						//标记是否匹配
int st[maxn],aim[maxm],nxt[maxm],ln;
int q[maxn];
int level[maxn];
int father[maxn];
vector<int> ar[maxn];
vector<int> a;
int n,m;
void in_edge(int x,int y){
	aim[ln]=y;
	nxt[ln]=st[x];
	st[x]=ln++;
}
int lca(int p,int q){
	int ret=0;
	while (ret<ar[p].size() && ret<ar[q].size() && ar[p][ret]==ar[q][ret]) ret++;
	return ret-1;
}
int FindAlterRoad(int sp){
	int qn=1;
	memset(level,-1,sizeof(level));
	level[q[0]=sp]=1;
	ar[sp].clear();
	ar[sp].push_back(sp);
	for (int p=0;p<qn;p++){
		int x=q[p];
		for (int i=st[x];i!=-1;i=nxt[i]){
			int u=aim[i];
			if (match[u]==u) continue;
			if (level[u]==-1){			//u是未访问的点
				if (match[u]==-1){		//u是未匹配的,找到增广路
					a=ar[x];
					a.push_back(u);
					return 1;
				}else{					//u是已匹配的点
					int v=match[u];
					if (level[v]!=-1) continue;
					ar[v]=ar[x];
					ar[v].push_back(u);
					ar[v].push_back(v);
					level[u]=0;
					level[v]=1;
					q[qn++]=v;
				}
			}else
			if (level[u]==1){			//u和x同为偶点.形成花
				int root=lca(u,x);
				vector<int> tmp=ar[x];
				for (int i=ar[u].size()-1;i>root;i--){
					int y=ar[u][i];
					tmp.push_back(y);
					if (level[y]==0){
						level[y]=1;
						ar[y]=tmp;
						level[y]=1;
						q[qn++]=y;
					}
				}
				tmp=ar[u];
				for (int i=ar[x].size()-1;i>root;i--){
					int y=ar[x][i];
					tmp.push_back(y);
					if (level[y]==0){
						level[y]=1;
						ar[y]=tmp;
						level[y]=1;
						q[qn++]=y;
					}
				}
			}
		}
	}
	return 0;
}
int MaximumMatch(){
	int ret=0;
	memset(match,-1,sizeof(match));
	for (int i=0;i<n;i++)
		if (match[i]==-1)
			if (FindAlterRoad(i)){
				for (int i=0;i<a.size();i+=2){
					int u=a[i],v=a[i+1];
					match[u]=v;
					match[v]=u;
				}
				ret++;
			}else match[i]=i;
	return ret;
}
int main(){
	scanf("%d",&n);
	memset(st,-1,sizeof(st));
	ln=0;
	int u,v;
	while (scanf("%d%d",&u,&v)!=EOF){
		u--,v--;
		in_edge(u,v);
		in_edge(v,u);
	}
	int ans=MaximumMatch();
	printf("%d\n",ans<<1);
	for (int i=0;i<n;i++)
		if (match[i]>i) printf("%d %d\n",i+1,match[i]+1);
	return 0;
}