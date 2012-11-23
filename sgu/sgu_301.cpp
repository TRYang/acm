#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 2010
#define maxm 200010
#define INF 100000000

using namespace std;

int x[maxn],xn;
int st[maxn],aim[maxm<<1],link[maxm<<1],len[maxm<<1],ln;
int ds[maxn],dt[maxn];
int ans[maxn];
int t[2][maxn];
int n,S,T,m;
void in_edge(int x,int y,int z){
	aim[ln]=y;
	link[ln]=st[x];
	len[ln]=z;
	st[x]=ln++;
}
void dij(int* dis,int sp){
	int tag[maxn];
	int i,j,k;
	for (i=1;i<=n;i++) dis[i]=INF;
	memset(tag,0,sizeof(tag));
	dis[sp]=0;
	for (int p=0;p<n;p++){
		k=-1;
		for (i=1;i<=n;i++)
			if (!tag[i] && dis[i]<INF)
				if (k==-1 || dis[i]<dis[k]) k=i;
		if (k==-1) break;
		tag[k]=1;
		for (i=st[k];i!=-1;i=link[i])
			if (!tag[aim[i]] && dis[k]+len[i]<dis[aim[i]]) dis[aim[i]]=dis[k]+len[i];
	}
}
void ins(int d,int p){
	for (;p<=xn;p+=(p&(p^(p-1)))) t[d][p]++;
}
int ask(int d,int p){
	int res=0;
	for (;p>0;p-=(p&(p^(p-1)))) res+=t[d][p];
	return res;
}
int main(){
	int i,j,k;
	scanf("%d %d %d",&n,&S,&T);
	memset(st,-1,sizeof(st));
	ln=0;
	for (scanf("%d",&m);m>0;m--){
		scanf("%d %d %d",&i,&j,&k);
		in_edge(i,j,k);
		in_edge(j,i,k);
	}
	dij(ds,S);
	dij(dt,T);
	int tot=ds[T];
	memset(ans,0,sizeof(ans));
	for (i=1;i<=n;i++) x[i-1]=ds[i];
	sort(x,x+n);
	xn=unique(x,x+n)-x;
	memset(t,0,sizeof(t));
	for (i=1;i<=n;i++)
		if (ds[i]+dt[i]==tot){
			for (j=st[i];j!=-1;j=link[j])
				if (ds[i]+len[j]+dt[aim[j]]==tot){
					ins(0,upper_bound(x,x+xn,ds[i])-x);
					ins(1,upper_bound(x,x+xn,ds[aim[j]])-x);
				}
		}
	for (i=1;i<=n;i++)
		if (ds[i]<INF && dt[i]<INF && ds[i]+dt[i]==tot){
			ans[i]=1;
			for (j=1;j<=n;j++)
				if (i!=j && ds[j]+dt[j]==tot)
					if (ds[i]==ds[j]) ans[i]++;
			k=ask(0,upper_bound(x,x+xn,ds[i])-x-1)-ask(1,upper_bound(x,x+xn,ds[i])-x);
			ans[i]+=k;
		}
	for (i=1;i<n;i++) printf("%d ",ans[i]);
	printf("%d\n",ans[n]);
	return 0;
}
