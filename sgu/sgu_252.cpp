#include <stdio.h>
#include <string.h>
#define maxn 210
#define maxm 50000
#define dst 25000
int st[maxn],aim[maxm],link[maxm],ln;
int con[maxm],flow[maxm],cost[maxm];
int f[maxn],g[maxn],e[maxn];
int next[maxn];
int tag[maxn];
int a[3000000];
int maxflow,total;
int source,remit;
int n,m;
void in_edge(int x,int y,int C,int F){
	ln++;
	aim[dst+ln]=y;
	link[dst+ln]=st[x];
	cost[dst+ln]=C;
	con[dst+ln]=F;
	st[x]=dst+ln;

	aim[dst-ln]=x;
	link[dst-ln]=st[y];
	cost[dst-ln]=-C;
	con[dst-ln]=0;
	st[y]=dst-ln;
	
	flow[dst+ln]=flow[dst-ln]=0;
}
int spfa(int sp,int tp){
	int i,p,an=1;
	memset(tag,0,sizeof(tag));
	for (i=0;i<=remit;i++) f[i]=1000000000;
	f[sp]=0;
	tag[sp]=1;
	a[0]=sp;
	for (p=0;p<an;p++){
		tag[a[p]]=0;
		for (i=st[a[p]];i!=-1;i=link[i])
			if (flow[i]<con[i] && f[a[p]]+cost[i]<f[aim[i]]){
				f[aim[i]]=f[a[p]]+cost[i];
				g[aim[i]]=a[p];
				e[aim[i]]=i;
				if (!tag[aim[i]]){
					tag[aim[i]]=1;
					a[an++]=aim[i];
				}
			}
	}
	return f[remit]<1000000000;
}
int opp(int x){
	return x>dst ? dst-(x-dst) : dst+(dst-x);
}
void pr(int sp){
	int i=sp,an=1;
	a[0]=sp;
	while (next[i]!=-1){
		a[an++]=next[i];
		i=next[i];
	}
	printf("%d ",an);
	for (i=0;i<an;i++) printf("%d ",a[i]+1);
	printf("\n");
}
int main(){
	int i,j,k,c;
	scanf("%d %d",&n,&m);
	ln=0;
	memset(st,-1,sizeof(st));
	source=n<<1;
	remit=source+1;
	for (i=0;i<m;i++){
		scanf("%d %d %d",&j,&k,&c);
		j--,k--;
		in_edge(j,n+k,c,1);
	}
	for (i=0;i<n;i++) in_edge(source,i,0,1);
	for (i=0;i<n;i++) in_edge(n+i,remit,0,1);
	total=maxflow=0;
	while (spfa(source,remit)){
		maxflow++;
		total+=f[remit];
		for (i=remit;i!=source;i=g[i]){
			flow[e[i]]++;
			flow[opp(e[i])]--;
		}
	}
	printf("%d %d\n",n-maxflow,total);
	memset(next,-1,sizeof(next));
	memset(tag,0,sizeof(tag));
	for (i=0;i<n;i++)
		for (j=st[i];j!=-1;j=link[j])
			if (aim[j]>=n && aim[j]<source)
				if (flow[j]==con[j]){
					next[i]=aim[j]-n;
					tag[next[i]]=1;
				}
	for (i=0;i<n;i++)
		if (!tag[i])pr(i);	
	return 0;
}
