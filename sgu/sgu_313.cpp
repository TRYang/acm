#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 50010

using namespace std;

typedef long long LL;

struct node{
	int x,p,f;
	friend bool operator < (const node &x,const node &y){
		return x.x<y.x;
	}
} a[maxn<<1];
int level[maxn<<1];
int len[maxn<<1];
LL totl[maxn<<3];
LL totv[maxn<<3];
LL getL,getv;
int stack[maxn<<1],stn;
int match[maxn];
int N;
int n,m;
void Ins(int p,int tl,int tr,int k,LL r,LL v){
	totl[p]+=r;
	totv[p]+=r*v;
	if (tl==tr) return;
	int m=(tl+tr)>>1;
	if (k<=m) Ins(p<<1,tl,m,k,r,v);else Ins((p<<1)+1,m+1,tr,k,r,v);
}
void get(int p,int tl,int tr,int l,int r){
	if (tl==l && tr==r){
		getL+=totl[p];
		getv+=totv[p];
		return;
	}
	int m=(tl+tr)>>1;
	if (l<=m){
		if (r>m){
			get(p<<1,tl,m,l,m);
			get((p<<1)+1,m+1,tr,m+1,r);
		}else get(p<<1,tl,m,l,r);
	}else get((p<<1)+1,m+1,tr,l,r);
}
void cal(int sp){
	int i,j,k;
	stack[stn=1]=sp;
	for (i=(sp+1)%N;i!=sp;i=(i+1)%N){
		k=stack[stn];
		if (stn==0 || a[i].f==a[k].f){
			stack[++stn]=i;
		}else{
			if (a[i].f==0) match[a[i].p]=a[k].p;else match[a[k].p]=a[i].p;
			stn--;
		}
	}
}
int main(){
	int i,j,k;
	scanf("%d %d",&n,&m);
	for (i=0;i<n;i++){
		scanf("%d",&k);
		a[i].x=k;
		a[i].p=i;
		a[i].f=0;
	}
	for (i=0;i<n;i++){
		scanf("%d",&k);
		a[n+i].x=k;
		a[n+i].p=i;
		a[n+i].f=1;
	}
	sort(a,a+n+n);
	N=n<<1;
	level[0]=0;
	for (i=0;i<N-1;i++)
		if (a[i].f==0) level[i+1]=level[i]+1;else level[i+1]=level[i]-1;
	len[0]=a[0].x==a[N-1].x ? 0 : a[0].x+m-a[N-1].x;
	for (i=1;i<N;i++) len[i]=a[i].x-a[i-1].x;
	int minl=0,maxl=0;
	for (i=0;i<N;i++) minl=min(minl,level[i]);
	for (i=0;i<N;i++) level[i]-=minl-1;
	for (i=0;i<N;i++) maxl=max(maxl,level[i]);
	for (i=0;i<N;i++){
		Ins(1,1,maxl,level[i],len[i],level[i]);
	}
	LL ans=-1,ansp;
	for (k=1;k<=maxl;k++){
		LL tmp;
		getL=getv=0;
		get(1,1,maxl,k,maxl);
		tmp=getv-getL*k;
		getL=getv=0;
		if (k>1) get(1,1,maxl,1,k-1);
		tmp+=getL*k-getv;
		if (ans==-1 || tmp<ans){
			ans=tmp;
			ansp=k;
		}
	}
	printf("%I64d\n",ans);
	for (i=0;i<N;i++)
		if (level[i]==ansp){
			cal(i);
			break;
		}
	for (i=0;i<n-1;i++) printf("%d ",match[i]+1);
	printf("%d\n",match[n-1]+1);
	return 0;
}
