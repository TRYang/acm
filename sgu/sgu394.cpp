#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 100010

using namespace std;

struct node{
	int x,y,w;
	void read(){
		scanf("%d%d%d",&x,&y,&w);
	}
	friend bool operator < (const node &x,const node &y){
		return x.x<y.x;
	}
} a[maxn],c[maxn];
struct rec{
	long long sx,sy,tx,ty;
} b[maxn];
long long x[maxn<<1];
long long y[maxn*3];
int xn,yn;
int st[maxn<<1],ay[maxn<<1],by[maxn<<1],nxt[maxn<<1],ln;
int dx[maxn<<1];
int tree[(maxn*3)<<2];
int bn,cn;
int tot[maxn];
int n,m;
void Add(int x,int sy,int ty,int dd){
	ay[ln]=sy;
	by[ln]=ty;
	dx[ln]=dd;
	nxt[ln]=st[x];
	st[x]=ln++;
}
void ins(int p,int tl,int tr,int l,int r,int v){
	if (tl==l && tr==r){
		tree[p]+=v;
		return;
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
	if (tl==tr) return tree[p];
	int m=(tl+tr)>>1;
	return tree[p]+(k<=m?ask(p<<1,tl,m,k):ask((p<<1)+1,m+1,tr,k));
}
void updata(int p,int f){
	tot[p]+=ask(1,1,yn,f);
}
void work(int ds){
	bn=cn=0;
	xn=yn=0;
	for (int i=0;i<n;i++)
		if ((a[i].x+a[i].y)%2==ds){
			c[cn].x=a[i].x+a[i].y;
			c[cn].y=a[i].y-a[i].x;
			c[cn].w=i;
//			printf("%d : (%d,%d)\n",i,c[cn].x,c[cn].y);
			cn++;
			y[yn++]=a[i].y-a[i].x;
		}
	sort(c,c+cn);
	for (int i=0;i<n;i++){
		int dw;
		if ((a[i].x+a[i].y)%2==ds) dw=(a[i].w%2==0)?a[i].w:a[i].w-1;else
			dw=(a[i].w%2==1)?a[i].w:a[i].w-1;
		b[bn].sx=(long long)a[i].x-dw+a[i].y;
		b[bn].tx=(long long)a[i].x+dw+a[i].y;
		b[bn].sy=(long long)a[i].y-dw-a[i].x;
		b[bn].ty=(long long)a[i].y+dw-a[i].x;
//		b[bn].pr();
		x[xn++]=b[bn].sx;
		x[xn++]=b[bn].tx;
		y[yn++]=b[bn].sy;
		y[yn++]=b[bn].ty;
		bn++;
	}
	sort(x,x+xn);
	xn=unique(x,x+xn)-x;
	sort(y,y+yn);
	yn=unique(y,y+yn)-y;
	memset(st,-1,sizeof(st));
	ln=0;
	for (int i=0;i<bn;i++){
		b[i].sy=upper_bound(y,y+yn,b[i].sy)-y;
		b[i].ty=upper_bound(y,y+yn,b[i].ty)-y;
		b[i].sx=lower_bound(x,x+xn,b[i].sx)-x;
		b[i].tx=lower_bound(x,x+xn,b[i].tx)-x;
		Add(b[i].sx,b[i].sy,b[i].ty,1);
		Add(b[i].tx,b[i].sy,b[i].ty,-1);
	}
	for (int i=0;i<cn;i++) c[i].y=upper_bound(y,y+yn,c[i].y)-y;
	memset(tree,0,sizeof(tree));
	for (int i=0,p=0;i<xn;i++){
		while (p<cn && c[p].x<x[i]){
			updata(c[p].w,c[p].y);
			p++;
		}
		if (p==cn) return;
		for (int k=st[i];k!=-1;k=nxt[k])
			if (dx[k]>0) ins(1,1,yn,ay[k],by[k],dx[k]);
		while (p<cn && c[p].x==x[i]){
			updata(c[p].w,c[p].y);
			p++;
		}
		if (p==cn) return;
		for (int k=st[i];k!=-1;k=nxt[k])
			if (dx[k]<0) ins(1,1,yn,ay[k],by[k],dx[k]);
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;i++) a[i].read();
	memset(tot,0,sizeof(tot));
	work(0);
	work(1);
	int ans=0;
	for (int i=0;i<n;i++)
		if (tot[i]>m) ++ans;
	printf("%d\n",ans);
	if (ans){
		for (int i=0;i<n;i++)
			if (tot[i]>m) printf("%d ",i+1);
		puts("");
	}
	return 0;
}
