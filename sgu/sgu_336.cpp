#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 300010
#define maxm 200010

using namespace std;

struct edge{
	int u,v;
	friend bool operator < (const edge &x,const edge &y){
		return x.v<y.v;
	}
} d[maxm];

struct Query{
	int i,j;
} c[maxm];

struct node{
	int l,r,p;
	friend bool operator < (const node &x,const node &y){
		return x.l<y.l || (x.l==y.l && x.r<y.r);
	}
} q[maxm];

int Head[maxn<<1],pre[4000000],x[4000000],pn;
int st[maxn],aim[maxn],link[maxn],ln;
int Num[maxn],tag[maxn];
int L[maxn],R[maxn];
int s[maxn],sn;
int stack[maxn],next[maxn];
int ans[maxm];
int n,m,tn,qn;

void in_edge(int x,int y){
	aim[ln]=y;
	link[ln]=st[x];
	st[x]=ln++;
}

void Dfs(int x){
	int stn,i,k;
	stack[stn=1]=x;
	next[x]=st[x];
	while (stn>0){
		k=stack[stn];
		if (k<=n){
			s[++sn]=k;
			Num[k]=sn;
			L[k]=R[k]=sn;
		}
		for (i=next[k];i!=-1;i=link[i]){
			next[k]=link[i];
			next[aim[i]]=st[aim[i]];
			stack[++stn]=aim[i];
			break;
		}
		if (i==-1){
			stn--;
			if (stn>0){
				if (next[stack[stn]]>-1) L[stack[stn]]=L[k];else R[stack[stn]]=R[k];
			}
		}
	}
}

void Ins(int p,int tl,int tr,int l,int r,int v){
	if (tl==l && tr==r){
		x[pn]=v;
		pre[pn]=Head[p];
		Head[p]=pn++;
		return;
	}
	int m=(tl+tr)>>1;
	if (l<=m){
		if (r>m){
			Ins(p<<1,tl,m,l,m,v);
			Ins((p<<1)+1,m+1,tr,m+1,r,v);
		}else Ins(p<<1,tl,m,l,r,v);
	}else Ins((p<<1)+1,m+1,tr,l,r,v);
}

void Check(int p,int tl,int tr,int k,int v){
	while (Head[p]>-1){
		if (L[c[x[Head[p]]].j]>v) break;
		if (R[c[x[Head[p]]].j]>=v) ans[x[Head[p]]]=1;
		Head[p]=pre[Head[p]];
	}
	if (tl==tr) return;
	int m=(tl+tr)>>1;
	if (k<=m) Check(p<<1,tl,m,k,v);else Check((p<<1)+1,m+1,tr,k,v);
}

int main(){
	int i,j,k;
	scanf("%d %d",&n,&m);
	for (i=0;i<m;i++) scanf("%d %d",&d[i].u,&d[i].v);
	tn=n;
	ln=0;
	memset(st,-1,sizeof(st));
	memset(tag,0,sizeof(tag));
	for (scanf("%d",&k),qn=0;k>0;k--){
		scanf("%d",&i);
		if (i==1){
			scanf("%d %d",&c[qn].i,&c[qn].j);
			qn++;
		}else{
			scanf("%d %d",&i,&j);
			tn++;
			in_edge(tn,i);
			in_edge(tn,j);
			tag[i]=tag[j]=1;
		}
	}
	sn=0;
	for (i=1;i<=tn;i++)
		if (!tag[i]) Dfs(i);
	for (i=0;i<m;i++){
		d[i].u=Num[d[i].u];
		d[i].v=Num[d[i].v];
	}
	sort(d,d+m);
	for (i=0;i<qn;i++){
		q[i].l=L[c[i].j];
		q[i].r=R[c[i].j];
		q[i].p=i;
	}
	if (qn>0) sort(q,q+qn);
	pn=0;
	memset(Head,-1,sizeof(Head));
	for (i=qn-1;i>=0;i--) Ins(1,1,n,L[c[q[i].p].i],R[c[q[i].p].i],q[i].p);
	memset(ans,0,sizeof(ans));
	for (i=0;i<m;i++) Check(1,1,n,d[i].u,d[i].v);
	for (i=0;i<qn;i++)
		if (ans[i]) printf("YES\n");else printf("NO\n");
	return 0;
}
