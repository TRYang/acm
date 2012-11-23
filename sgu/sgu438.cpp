#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 55
#define maxm 4000010
#define MAXN 10010
#define inf 10000000

using namespace std;

int st[MAXN],aim[maxm],nxt[maxm],ln;
int flow[maxm],con[maxm];
int level[MAXN],q[MAXN],stack[MAXN],next[MAXN];
int e[MAXN];
int x[maxn],y[maxn],c[maxn];
int n,m,D,W;
int ans;
int source,remit;
int maxflow;
int dist(int p,int q){
	return (x[p]-x[q])*(x[p]-x[q])+(y[p]-y[q])*(y[p]-y[q]);
}
void in_edge(int x,int y,int f){
	aim[ln]=y;
	nxt[ln]=st[x];
	flow[ln]=0;
	con[ln]=f;
	st[x]=ln++;
	aim[ln]=x;
	nxt[ln]=st[y];
	flow[ln]=con[ln]=0;
	st[y]=ln++;
}
void bfs(){
	int qn=1;
	q[0]=source;
	memset(level,-1,sizeof(level));
	level[source]=1;
	for (int p=0;p<qn;p++)
		for (int i=st[q[p]];i!=-1;i=nxt[i])
			if (level[aim[i]]==-1 && flow[i]<con[i]) level[q[qn++]=aim[i]]=level[q[p]]+1;
}
void dfs(){
	int stn=1;
	stack[1]=source;
	next[source]=st[source];
	while (stn){
		int k=stack[stn],i;
		if (k==remit){
			int delta=inf;
			for (int i=stn;i>1;i--){
				int x=e[stack[i]];
				delta=min(delta,con[x]-flow[x]);
			}
			int p=-1;
			for (int i=stn;i>1;i--){
				int x=e[stack[i]];
				flow[x]+=delta;
				flow[x^1]-=delta;
				if (flow[x]==con[x]) p=i;
			}
			maxflow+=delta;
			if (maxflow>=m) return;
			stn=p;
			continue;
		}
		for (i=next[k];i!=-1;i=nxt[i])
			if (level[aim[i]]==level[k]+1 && flow[i]<con[i]){
				next[k]=nxt[i];
				next[aim[i]]=st[aim[i]];
				stack[++stn]=aim[i];
				e[aim[i]]=i;
				break;
			}
		if (i==-1){
			level[k]=inf;
			--stn;
		}
	}
}
int check(int t){
	source=n*t*2;
	remit=source+1;
	memset(st,-1,sizeof(st));
	ln=0;
	for (int i=0;i<n;i++)
		for (int j=0;j<t;j++){
			in_edge(i*t*2+(j<<1),i*t*2+(j<<1)+1,c[i]);
		}
	for (int i=0;i<n;i++){
		if (y[i]<=D){
			for (int j=0;j<t;j++) in_edge(source,i*t*2+(j<<1),inf);
		}
		if (W-y[i]<=D){
			for (int j=0;j<t;j++) in_edge(i*t*2+(j<<1)+1,remit,inf);
		}
	}
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			if (dist(i,j)<=D*D){
				for (int k=0;k<t-1;k++) in_edge(i*t*2+(k<<1)+1,j*t*2+(k+1<<1),inf);
			}
	maxflow=0;
	while (1){
		bfs();
		if (level[remit]==-1) break;
		dfs();
		if (maxflow>=m) return 1;
	}
	return maxflow>=m;
}
int main(){
	scanf("%d%d%d%d",&n,&m,&D,&W);
	for (int i=0;i<n;i++) scanf("%d%d%d",x+i,y+i,c+i);
	if (D>=W){
		puts("1");
		return 0;
	}
	int L=1,R=(m<<1),mid;
	ans=-1;
	while (L<=R){
		mid=(L+R)>>1;
		if (check(mid)){
			R=mid-1;
			ans=mid+1;
		}else L=mid+1;
	}
	if (ans>-1) printf("%d\n",ans);else puts("IMPOSSIBLE");
	return 0;
}
