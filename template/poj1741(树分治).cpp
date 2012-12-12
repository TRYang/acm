#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 10010

using namespace std;

int st[maxn],aim[maxn<<1],nxt[maxn<<1],len[maxn<<1],ln;
int ans;
int n,m;

void in_edge(int x,int y,int z){
	aim[ln]=y;
	nxt[ln]=st[x];
	len[ln]=z;
	st[x]=ln++;
}

int f[maxn],tot[maxn];
int tag[maxn];
int q[maxn];
int dis[maxn];
int a[maxn],an;
int b[maxn],bn;

int dp(int x){
	int qn=1;
	q[0]=x;
	tag[x]=1;
	for (int p=0;p<qn;p++){
		int u=q[p],v;
		for (int i=st[u];i!=-1;i=nxt[i])
			if (!tag[v=aim[i]]){
				tag[v]=1;
				q[qn++]=v;
			}
	}
	if (qn==1) return -1;
	
	for (int p=qn-1;p>=0;p--){
		int k=q[p],v;
		tag[k]=0;
		tot[k]=1;
		f[k]=0;
		for (int i=st[k];i!=-1;i=nxt[i])
			if (!tag[v=aim[i]]){
				tot[k]+=tot[v];
				f[k]=max(f[k],tot[v]);
			}
	}
	
	int minf=(n*n),minp=-1;
	int sum=tot[q[0]];
	for (int p=0;p<qn;p++){
		int k=q[p];
		f[k]=max(f[k],sum-tot[k]);
		if (f[k]<minf) minf=f[k],minp=k;
	}
	return minp;
}

void bfs(int sp,int lp){
	int qn=1;
	q[0]=sp;
	dis[sp]=lp;
	tag[sp]=1;
	bn=0;
	for (int p=0;p<qn;p++){
		b[bn++]=dis[q[p]];
		int v;
		for (int i=st[q[p]];i!=-1;i=nxt[i])
			if (!tag[v=aim[i]]){
				tag[v]=1;
				dis[v]=dis[q[p]]+len[i];
				q[qn++]=v;
			}
	}
	for (int p=0;p<qn;p++) tag[q[p]]=0;
}

void work(int x){
	int root=dp(x);
	if (root==-1) return;
	tag[root]=1;
	
	an=0;
	for (int i=st[root],v;i!=-1;i=nxt[i])
		if (!tag[v=aim[i]]){
			if (len[i]>m) continue;
			bfs(v,len[i]);
			sort(b,b+bn);
			for (int k=0,j=bn-1;k<bn;k++){
				while (j>=0 && b[k]+b[j]>m) --j;
				ans-=j+1;
				a[an++]=b[k];
			}
		}
		
	sort(a,a+an);
	for (int k=0,j=an-1;k<an;k++){
		while (j>=0 && a[k]+a[j]>m) --j;
		ans+=j+1;
		if (a[k]<=m) ans+=2;
	}
	
	for (int i=st[root];i!=-1;i=nxt[i])
		if (!tag[aim[i]]) work(aim[i]);
}

int main(){
	while (scanf("%d%d",&n,&m),n || m){
		memset(st,-1,sizeof(st));
		ln=0;
		for (int i=1;i<n;i++){
			int u,v,l;
			scanf("%d%d%d",&u,&v,&l);
			in_edge(u,v,l);
			in_edge(v,u,l);
		}
		ans=0;
		memset(tag,0,sizeof(tag));
		work(1);
		printf("%d\n",ans>>1);
	}
	return 0;
}
