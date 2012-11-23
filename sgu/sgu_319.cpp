#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 60010

using namespace std;

struct node{
	int x,l,r,p,tag;
	friend bool operator < (const node &x,const node &y){
		return x.x<y.x;
	}
} a[maxn<<1];
int y[maxn<<1],yn;
int tree[maxn<<3];
int pre[maxn];
long long s[maxn];
int n,an;
long long cal(long long x,long long y){return x*y;}
node com(int x,int l,int r,int p,int tag){
	node res;
	res.x=x;
	res.l=l;
	res.r=r;
	res.p=p;
	res.tag=tag;
	return res;
}
void swap(int &x,int &y){
	int tmp;
	tmp=x;
	x=y;
	y=tmp;
}
void ins(int p,int tl,int tr,int l,int r,int v){
	if (tl==l && tr==r){
		tree[p]=v;
		return;
	}
	if (tree[p]>-1){
		tree[p<<1]=tree[(p<<1)+1]=tree[p];
		tree[p]=-1;
	}
	int m=(tl+tr)>>1;
	if (l<=m){
		if (r>m){
			ins(p<<1,tl,m,l,m,v);
			ins((p<<1)+1,m+1,tr,m+1,r,v);
		}else ins(p<<1,tl,m,l,r,v);
	}else ins((p<<1)+1,m+1,tr,l,r,v);
}
int ask(int p,int tl,int tr,int k){
	if (tl==tr || tree[p]>-1) return tree[p];
	if (k<=(tl+tr)>>1)
		return ask(p<<1,tl,(tl+tr)>>1,k);
	else
		return ask((p<<1)+1,((tl+tr)>>1)+1,tr,k);
}
int main(){
	int i,j,k;
	scanf("%d",&n);
	scanf("%d %d",&j,&k);
	a[0]=com(0,0,k,0,0);
	a[1]=com(j,0,k,0,1);
	y[0]=0;
	y[1]=k;
	an=yn=2;
	s[0]=cal(j,k);
	for (i=1;i<=n;i++){
		int x1,x2,y1,y2;
		scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
		if (x1>x2) swap(x1,x2);
		if (y1>y2) swap(y1,y2);
		a[an++]=com(x1,y1,y2,i,0);
		a[an++]=com(x2,y1,y2,i,1);
		y[yn++]=y1;
		y[yn++]=y2;
		s[i]=cal(x2-x1,y2-y1);
	}
	sort(y,y+yn);
	yn=unique(y,y+yn)-y;
	sort(a,a+an);
	memset(tree,-1,sizeof(tree));
	for (i=0;i<an;i++){
		a[i].l=lower_bound(y,y+yn,a[i].l)-y;
		a[i].r=lower_bound(y,y+yn,a[i].r)-y;
		if (!a[i].tag){
			pre[a[i].p]=ask(1,0,yn-1,a[i].l);
			s[pre[a[i].p]]-=s[a[i].p];
			ins(1,0,yn-1,a[i].l,a[i].r,a[i].p);
		}else{
			ins(1,0,yn-1,a[i].l,a[i].r,pre[a[i].p]);
		}
	}
	sort(s,s+n+1);
	for (i=0;i<=n;i++) printf("%I64d ",s[i]);
	printf("\n");
	return 0;
}
