#include <stdio.h>
#include <string.h>
#define maxn 100010
#define maxm 300010
int st[maxn],aim[maxm<<1],nxt[maxm<<1],ln;
int edge[maxm][2];
int deg[maxn];
int tag[maxn];
int root[maxn],rn;
int f[maxn];
int father[maxn];
int n,m;
void in_edge(int x,int y){
	aim[ln]=y;
	nxt[ln]=st[x];
	st[x]=ln++;
}
void work(int x){
	int r=-1;
	for (int i=st[x];i!=-1;i=nxt[i])
		if (nxt[i]==-1 || deg[aim[i]]>2){
			r=aim[i];
			break;
		}
	root[rn++]=r;
	f[r]=-1;
	tag[r]=1;
	for (int i=st[r];i!=-1;i=nxt[i]){
		tag[aim[i]]=1;
		for (int j=st[aim[i]];j!=-1;j=nxt[j])
			if (aim[j]!=r) f[aim[i]]=aim[j];
	}
}
int Find(int x){return father[x]=father[x]==x?x:Find(father[x]);}
int main(){
	scanf("%d%d",&n,&m);
	memset(st,-1,sizeof(st));
	for (int i=1;i<=n;i++) father[i]=i;
	for (int i=1;i<=m;i++){
		scanf("%d%d",&edge[i][0],&edge[i][1]);
		++deg[edge[i][0]];
		++deg[edge[i][1]];
		father[Find(edge[i][0])]=Find(edge[i][1]);
		in_edge(edge[i][0],edge[i][1]);
		in_edge(edge[i][1],edge[i][0]);
	}
	rn=0;
	for (int i=1;i<=n;i++)
		if (!tag[i] && deg[i]==2) work(i);
	// for (int i=1;i<=n;i++) printf("%d %d\n",i,f[i]);
	char type[30];
	while (scanf("%s",type)!=EOF){
		if (type[0]=='D'){
			int p;
			scanf("%d",&p);
			int u=edge[p][0],v=edge[p][1];
			if (f[u]==-1){
				tag[v]=0;
			}else
			if (f[v]==-1){
				tag[u]=0;
			}else{
				f[u]=f[v]=-2;
			}
		}else{
			int x,y;
			scanf("%d%d",&x,&y);
			if (x==y) puts("0");else
			if (Find(x)!=Find(y)) puts("-1");else
			if (f[x]==y) puts("1");else
			if ((f[x]==-2 && !tag[x]) || (f[y]==-2 && !tag[y])) puts("-1");else
			if (f[x]==-1){
				if (tag[y]) puts("1");else
				if (tag[f[y]]) puts("2");else puts("-1");
			}else
			if (f[y]==-1){
				if (tag[x]) puts("1");else
				if (tag[f[x]]) puts("2");else puts("-1");
			}else{
				int t1,t2;
				if (tag[x]) t1=1;else
				if (tag[f[x]]) t1=2;else t1=-1;
				if (tag[y]) t2=1;else
				if (tag[f[y]]) t2=2;else t2=-1;
				if (t1==-1 || t2==-1) puts("-1");else printf("%d\n",t1+t2);
			}
		}
	}
	return 0;
}