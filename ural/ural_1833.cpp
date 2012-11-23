#include <stdio.h>
#include <string.h>
#define maxn 510
#define maxm 100010
int st[maxn],aim[maxm<<1],nxt[maxm<<1],ln;
double ans[maxn];
int n,K,m;
void in_edge(int x,int y){
	aim[ln]=y;
	nxt[ln]=st[x];
	st[x]=ln++;
}

int tag[maxn];
int mx[maxn],my[maxn];
int usedx[maxn],usedy[maxn];

int dfs(int x){
	if (tag[x]) return 0;
	tag[x]=1;
	for (int i=st[x];i!=-1;i=nxt[i])
		if (my[aim[i]]==-1 || dfs(my[aim[i]])){
			my[aim[i]]=x;
			mx[x]=aim[i];
			return 1;
		}
	return 0;
}

void minimumCover(){
	memset(mx,-1,sizeof(mx));
	memset(my,-1,sizeof(my));
	for (int i=0;i<n;i++){
		memset(tag,0,sizeof(tag));
		dfs(i);
	}
	
	memset(usedx,0,sizeof(usedx));
	memset(usedy,0,sizeof(usedy));
	memset(tag,0,sizeof(tag));
	for (int i=0;i<n;i++)
		if (mx[i]==-1) dfs(i);
	for (int i=0;i<n;i++)
		if (mx[i]>-1)
			if (tag[i]) usedy[mx[i]]=1;else usedx[i]=1;
}

int main(){
	scanf("%d%d%d",&n,&K,&m);
	memset(st,-1,sizeof(st));
	ln=0;
	for (int i=0;i<m;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		u--,v--;
		in_edge(u,v);
		in_edge(v,u);
	}
	minimumCover();
	for (int i=0;i<n;i++) ans[i]=(usedx[i]+usedy[i])*K*1.0/2.0;
	for (int i=0;i<n;i++) printf("%.2lf\n",ans[i]);
	return 0;
}