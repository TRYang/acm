#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 100010

using namespace std;

int f[maxn];
int g[maxn];
int d[maxn];
struct tarray{
	int n;
	int v[maxn];
	void resize(int pn){
		n=pn;
		memset(v,-1,sizeof(v));
	}
	void ins(int p,int x){
		for (;p<=n;p+=(p&(p^(p-1))))
			if (v[p]==-1 || f[x]>f[v[p]]) v[p]=x;
	}
	int find(int p){
		int ret=-1;
		for (;p;p-=(p&(p^(p-1))))
			if (v[p]>-1)
				if (ret==-1 || f[v[p]]>f[ret]) ret=v[p];
		return ret;
	}
} ta,tb;
int x[maxn],xn;
int a[maxn];
int tag[maxn];
int n;
int main(){
	scanf("%d",&n);
	for (int i=0;i<n;i++) scanf("%d",a+i);
	for (int i=0;i<n;i++) x[i]=a[i];
	sort(x,x+n);
	xn=unique(x,x+n)-x;
	memset(g,-1,sizeof(g));
	memset(d,-1,sizeof(d));
	ta.resize(xn);
	tb.resize(xn);
	for (int i=0;i<n;i++){
		f[i]=1;
		g[i]=-1;
		int p=upper_bound(x,x+xn,a[i])-x;
		if (d[p]>-1 && f[d[p]]+1>f[i]){
			f[i]=f[d[p]]+1;
			g[i]=d[p];
		}
		int k;
		if (p>1 && x[p-2]==x[p-1]-1) k=ta.find(p-2);else k=ta.find(p-1);
		if (k>-1 && f[k]+1>f[i]){
			f[i]=f[k]+1;
			g[i]=k;
		}
		if (p<xn && x[p]==x[p-1]+1) k=tb.find(xn-p-1);else k=tb.find(xn-p);
		if (k>-1 && f[k]+1>f[i]){
			f[i]=f[k]+1;
			g[i]=k;
		}
		if (d[p]==-1 || f[i]>f[d[p]]){
			d[p]=i;
		}
		ta.ins(p,i);
		tb.ins(xn-p+1,i);
	}
	int ans=0,ansp;
	for (int i=0;i<n;i++)
		if (f[i]>ans) ans=f[i],ansp=i;
	printf("%d\n",n-ans);
	for (int i=ansp;i>-1;i=g[i]) tag[i]=1;
	for (int i=0;i<n;i++)
		if (tag[i]) printf("%d ",a[i]);
	puts("");
	return 0;
}
