#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 100010
#define inf 1000000100

using namespace std;

struct node{
	int x,y;
	node(){}
	node(int _x,int _y){
		x=_x;
		y=_y;
	}
	void read(){
		scanf("%d%d",&x,&y);
	}
	friend bool operator < (const node &a,const node &b){
		return a.y>b.y;
	}
} a[maxn],ta[maxn];
int x[maxn],xn;
int n;
long long ans;
int stackl[maxn],stackr[maxn];
int split_a(node *a,int n,int px){
	int tn=0;
	for (int i=0;i<n;i++)
		if (a[i].x<=px) ta[tn++]=a[i];
	int an=n;
	for (int i=n-1;i>=0;i--)
		if (a[i].x>px) a[--an]=a[i];
	for (int i=0;i<tn;i++) a[i]=ta[i];
	return tn;
}
void work(int *x,int xn,node *a,int n){
	if (xn==1){
		ans+=n-1;
		return;
	}
	int px=(xn%2==0?x[(xn>>1)-1]:x[xn>>1]);
	int lxn=(xn+1)>>1;
	int stnl=0,stnr=0;
	for (int i=0,j;i<n;i=j+1){
		for (j=i;j<n-1 && a[j+1].y==a[j].y;j++);
		int y=a[i].y;
		int lx=-inf,rx=inf;
		int ld=-1,rd=-1;
		for (int k=i;k<=j;k++)
			if (a[k].x<=px){
				lx=max(lx,a[k].x);
				if (a[k].x==lx) ld=k;
			}else{
				rx=min(rx,a[k].x);
				if (a[k].x==rx) rd=k;
			}
		int ly=inf,ry=inf;
		if (lx>-inf){
			while (stnl && a[stackl[stnl]].x<lx) --stnl;
			if (stnl && a[stackl[stnl]].x==lx){
				ly=a[stackl[stnl]].y;
				--stnl;
			}else
			if (stnl) ly=a[stackl[stnl]].y;
			stackl[++stnl]=ld;
		}
		if (rx<inf){
			while (stnr && a[stackr[stnr]].x>rx) --stnr;
			if (stnr && a[stackr[stnr]].x==rx){
				ry=a[stackr[stnr]].y;
				--stnr;
			}else
			if (stnr) ry=a[stackr[stnr]].y;
			stackr[++stnr]=rd;
		}
		if (lx>-inf){
			int tmp=0;
			int L=1,R=stnr,mid;
			while (L<=R){
				mid=(L+R)>>1;
				if (a[stackr[mid]].y<ly){
					tmp=max(tmp,stnr-mid+1);
					R=mid-1;
				}else L=mid+1;
			}
			ans+=tmp;
		}
		if (rx<inf){
			int tmp=0;
			int L=1,R=stnl,mid;
			while (L<=R){
				mid=(L+R)>>1;
				if (a[stackl[mid]].y<ry){
					tmp=max(tmp,stnl-mid+1);
					R=mid-1;
				}else L=mid+1;
			}
			ans+=tmp;
		}
		if (lx>-inf && rx<inf) --ans;
	}
//	printf("%d %lld\n",px,ans);
	int ln=split_a(a,n,px);
	work(x,lxn,a,ln);
	work(x+lxn,xn-lxn,a+ln,n-ln);
}
int main(){
	scanf("%d",&n);
	for (int i=0;i<n;i++) a[i].read();
	for (int i=0;i<n;i++) x[i]=a[i].x;
	sort(x,x+n);
	xn=unique(x,x+n)-x;
	sort(a,a+n);
	work(x,xn,a,n);
	printf("%I64d\n",ans);
	return 0;
}
