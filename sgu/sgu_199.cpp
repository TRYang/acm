#include <stdio.h>
#include <algorithm>
#include <string.h>
#define maxn 100010

using namespace std;

struct node{
	int s,b,p;
	friend bool operator < (const node &x,const node &y){
		return x.s<y.s || (x.s==y.s && x.b>y.b);
	}
} a[maxn];
int pre[maxn];
int b[maxn],bn;
int n;
int ans,ansp;
int find(int x){
	int l=1,r=bn,mid,res=0;
	while (l<=r){
		mid=(l+r)>>1;
		if (x>a[b[mid]].b){
			l=mid+1;
			res=mid;
		}else r=mid-1;
	}
	return res;
}
int main(){
	int i,j,k;
	scanf("%d",&n);
	for (i=0;i<n;i++){
		scanf("%d %d",&a[i].s,&a[i].b);
		a[i].p=i;
	}
	sort(a,a+n);
	pre[a[0].p]=-1;
	b[bn=1]=0;
	for (i=1;i<n;i++){
		k=find(a[i].b);
		if (k==0) pre[a[i].p]=-1;else pre[a[i].p]=a[b[k]].p;
		b[k+1]=i;
		if (k==bn) bn++;
	}
	printf("%d\n",bn);
	for (i=a[b[bn]].p;i!=-1;i=pre[i]) printf("%d ",i+1);printf("\n");
	return 0;
}
