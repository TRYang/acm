#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 100010

using namespace std;

struct node{
	int x,y,p,l,r;
	friend bool operator < (const node &x,const node &y){
		return x.x<y.x || (x.x==y.x && x.y>y.y);
	}
} a[maxn];
int d[maxn],c[maxn];
int h[maxn],hn;
int n;
int find1(int x){
	int l=0,r=hn,mid;
	while (l<=r){
		mid=(l+r)>>1;
		if (h[mid]<x){
			l=mid+1;
		}else r=mid-1;
	}
	return l-1;
}
int find2(int x){
	int l=0,r=hn,mid;
	while (l<=r){
		mid=(l+r)>>1;
		if (h[mid]>x){
			l=mid+1;
		}else r=mid-1;
	}
	return l-1;
}
int main(){
	int i,j,k;
	scanf("%d",&n);
	for (i=0;i<n;i++){
		scanf("%d %d",&a[i].x,&a[i].y);
		a[i].p=i+1;
	}
	sort(a,a+n);
	h[0]=-10000000;
	hn=0;
	for (i=0;i<n;i++){
		if (a[i].y>h[hn]){
			h[++hn]=a[i].y;
			a[i].l=hn-1;
		}else{
			k=find1(a[i].y);
			h[k+1]=a[i].y;
			a[i].l=k;
		}
	}
	h[0]=10000000;
	hn=0;
	for (i=n-1;i>=0;i--){
		if (a[i].y<h[hn]){
			h[++hn]=a[i].y;
			a[i].r=hn-1;
		}else{
			k=find2(a[i].y);
			h[k+1]=a[i].y;
			a[i].r=k;
		}
	}
	memset(d,0,sizeof(d));
	for (k=i=0;i<n;i++)
		if (a[i].l+a[i].r+1==hn){
			d[a[i].p]=1;
			k++;
		}
	printf("%d ",k);
	for (i=1;i<=n;i++)
		if (d[i]) printf("%d ",i);
	printf("\n");
	memset(d,0,sizeof(d));
	memset(c,0,sizeof(c));
	for (i=0;i<n;i++)
		if (a[i].l+a[i].r+1==hn) d[a[i].l]++;
	for (k=i=0;i<n;i++)
		if (a[i].l+a[i].r+1==hn && d[a[i].l]==1){
			c[a[i].p]=1;
			k++;
		}
	printf("%d ",k);
	for (i=1;i<=n;i++)
		if (c[i]) printf("%d ",i);
	printf("\n");
	return 0;
}
