#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 2010
#define maxm 200010

using namespace std;

struct edge{
	int u,v,w,f;
	int p;
	void read(){
		scanf("%d%d%d%d",&u,&v,&f,&w);
	}
	friend bool operator < (const edge &x,const edge &y){
		return x.w<y.w;
	}
} a[maxm];
int st[maxn],aim[maxm],nxt[maxm],ln;
int e[maxn],en;
int d[maxn],dn;
int c[maxn],cn;
int father[maxn];
int n,m,N;
void in_edge(int x,int y){
	aim[ln]=y;
	nxt[ln]=st[x];
	st[x]=ln++;
}
void init(){
	for (int i=1;i<=n;i++) father[i]=i;
}
int Find(int x){
	return father[x]= father[x]==x?x:Find(father[x]);
}
int main(){
	scanf("%d%d%d",&n,&N,&m);
	for (int i=0;i<m;i++) a[i].read();
	for (int i=0;i<m;i++) a[i].p=i+1;
	sort(a,a+m);
	memset(st,-1,sizeof(st));
	ln=0;
	for (int i=0;i<m;i++) in_edge(a[i].f,i);
	en=0;
	init();
	for (int i=0;i<m;i++){
		int fx=Find(a[i].u),fy=Find(a[i].v);
		if (fx!=fy){
			father[fx]=fy;
			e[en++]=i;
		}
	}
	int ans=-1,ansp;
	for (int i=1;i<=N;i++){
		int cost=0;
		init();
		for (int k=st[i];k!=-1;k=nxt[k]) father[Find(a[aim[k]].u)]=Find(a[aim[k]].v);
		dn=0;
		for (int k=0;k<en;k++){
			int fx=Find(a[e[k]].u),fy=Find(a[e[k]].v);
			if (fx!=fy){
				cost+=a[e[k]].w;
				father[fx]=fy;
				d[dn++]=e[k];
			}
		}
		if (ans==-1 || cost<ans){
			ansp=i;
			ans=cost;
			cn=dn;
			for (int j=0;j<cn;j++) c[j]=a[d[j]].p;
		}
	}
	sort(c,c+cn);
	printf("%d %d %d\n",ans,ansp,cn);
	for (int i=0;i<cn;i++) printf("%d\n",c[i]);
	return 0;
}
