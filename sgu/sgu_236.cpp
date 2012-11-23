#include <stdio.h>
#include <string.h>
#define maxn 55
#define maxm 3000
#define eps 1e-6
int st[maxn],aim[maxm],nxt[maxm],ln;
double cost[maxm];
int C[maxn][maxn],T[maxn][maxn];
int n,m;
void in_edge(int x,int y){
	aim[ln]=y;
	nxt[ln]=st[x];
	st[x]=ln++;
}
int tag[maxn];
double dist[maxn];
int pre[maxn];
int spfa(int u){
	tag[u]=1;
	for (int i=st[u];i!=-1;i=nxt[i]){
		int v=aim[i];
		if (dist[u]+cost[i]<dist[v]){
			dist[v]=dist[u]+cost[i];
			pre[v]=u;
			if (tag[v]) return v;
			int ret=spfa(v);
			if (ret!=-1) return ret;
		}
	}
	tag[u]=0;
	return -1;
}
int negcir(){
	memset(dist,0,sizeof(dist));
	memset(tag,0,sizeof(tag));
	for (int u=1;u<=n;u++){
		int ret=spfa(u);
		if (ret!=-1) return ret;
	}
	return -1;
}
int check(double mid){
	for (int i=1;i<=n;i++)
		for (int j=st[i];j!=-1;j=nxt[j])
			cost[j]=mid*T[i][aim[j]]-C[i][aim[j]];
	return negcir();
}
int a[maxn];
int main(){
	scanf("%d%d",&n,&m);
	memset(st,-1,sizeof(st));
	ln=0;
	double sc=0;
	for (int i=0;i<m;i++){
		int u,v,c,t;
		scanf("%d%d%d%d",&u,&v,&c,&t);
		in_edge(u,v);
		C[u][v]=c;
		T[u][v]=t;
		sc+=c;
	}
	double l=0,r=sc,mid;
	while (r-l>eps){
		mid=(l+r)/2.0;
		if (check(mid)>-1) l=mid;else r=mid;
	}
//	printf("%.2lf\n",l);
	int k=check(l);
	if (k==-1) puts("0");else{
		int an=1;
		a[0]=k;
		for (int i=pre[k];i!=k;i=pre[i]) a[an++]=i;
		printf("%d\n",an);
		for (int i=an-1;i>0;i--) printf("%d ",a[i]);
		printf("%d\n",a[0]);
	}
	return 0;
}
