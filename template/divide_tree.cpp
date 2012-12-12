#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 100010

using namespace std;

int t[maxn][20];
int lmax[maxn][20],lmin[maxn][20],rmax[maxn][20],rmin[maxn][20];
int a[maxn],v[maxn],b[maxn];
int n,m;
void make(int p,int l,int r){
	if (l==r) return;
	int m=(l+r)>>1,i,j,k;
	int mv=v[m];
	for (i=l,k=0;i<=r;k=t[i++][p]) t[i][p]=k+(a[i]<=mv);
	for (i=l,j=l-1,k=m;i<=r;i++){
		if (a[i]<=mv) j++;else k++;
		lmax[i][p]=j;
		rmax[i][p]=k;
	}
	for (i=r,j=m+1,k=r+1;i>=l;i--){
		if (a[i]<=mv) j--;else k--;
		lmin[i][p]=j;
		rmin[i][p]=k;
	}
	int bn=l;
	for (i=l;i<=r;i++)
		if (a[i]<=mv) b[bn++]=a[i];
	for (i=l;i<=r;i++)
		if (a[i]>mv) b[bn++]=a[i];
	for (i=l;i<=r;i++) a[i]=b[i];
	make(p+1,l,m);
	make(p+1,m+1,r);
}
int find(int p,int tl,int tr,int l,int r,int k){
	if (tl==tr) return v[l];
	int m=(tl+tr)>>1,tot= l==tl ? t[r][p] : t[r][p]-t[l-1][p];
	if (tot>=k) return find(p+1,tl,m,lmin[l][p],lmax[r][p],k);else
		return find(p+1,m+1,tr,rmin[l][p],rmax[r][p],k-tot);
}
int main(){
	int i,j,k;
	scanf("%d %d",&n,&m);
	for (i=1;i<=n;i++){
		scanf("%d",a+i);
		v[i]=a[i];
	}
	sort(v+1,v+n+1);
	make(0,1,n);
	for (;m>0;m--){
		scanf("%d %d %d",&i,&j,&k);
		printf("%d\n",find(0,1,n,i,j,k));
	}
	return 0;
}
