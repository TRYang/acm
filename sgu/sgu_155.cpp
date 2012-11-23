#include <stdio.h>
#include <algorithm>
#include <string.h>
#define maxn 50010

using namespace std;

struct node{
	int k,a,p;
	friend bool operator < (const node &x,const node &y){
		return x.k<y.k;
	}
} a[maxn];
int par[maxn],lc[maxn],rc[maxn];
int q[maxn][2],qn,c[maxn];
int tree[maxn<<2];
int n;
void Init(int p,int tl,int tr){
	if (tl==tr){
		tree[p]=tl;
		return;
	}
	Init(p<<1,tl,(tl+tr)>>1);
	Init((p<<1)+1,((tl+tr)>>1)+1,tr);
	if (a[tree[p<<1]].a<a[tree[(p<<1)+1]].a) tree[p]=tree[p<<1];else tree[p]=tree[(p<<1)+1];
}
int ask(int p,int tl,int tr,int l,int r){
	if (tl==l && tr==r) return tree[p];
	int m=(tl+tr)>>1;
	if (l<=m){
		if (r>m){
			int t1=ask(p<<1,tl,m,l,m),t2=ask((p<<1)+1,m+1,tr,m+1,r);
			if (a[t1].a<a[t2].a) return t1;else return t2;
		}else return ask(p<<1,tl,m,l,r);
	}else return ask((p<<1)+1,m+1,tr,l,r);
}
int main(){
	int i,j,k;
	scanf("%d",&n);
	for (i=0;i<n;i++){
		scanf("%d %d",&a[i].k,&a[i].a);
		a[i].p=i+1;
	}
	sort(a,a+n);
	Init(1,0,n-1);
	qn=1;
	q[0][0]=0;q[0][1]=n-1;c[0]=tree[1];
	for (k=0;k<qn;k++)
		if (q[k][0]<c[k] || c[k]<q[k][1]){
			if (q[k][0]<c[k]){
				c[qn]=ask(1,0,n-1,q[k][0],c[k]-1);
				lc[a[c[k]].p]=a[c[qn]].p;
				par[a[c[qn]].p]=a[c[k]].p;
				q[qn][0]=q[k][0];
				q[qn++][1]=c[k]-1;
			}else lc[a[c[k]].p]=0;
			if (c[k]<q[k][1]){
				c[qn]=ask(1,0,n-1,c[k]+1,q[k][1]);
				rc[a[c[k]].p]=a[c[qn]].p;
				par[a[c[qn]].p]=a[c[k]].p;
				q[qn][0]=c[k]+1;
				q[qn++][1]=q[k][1];
			}else rc[a[c[k]].p]=0;
		}
	printf("YES\n");
	for (i=1;i<=n;i++) printf("%d %d %d\n",par[i],lc[i],rc[i]);
	return 0;
}
