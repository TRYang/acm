#include <stdio.h>
#include <algorithm>
#define maxn 16010

using namespace std;

struct node{
	int l,r;
	friend bool operator < (const node &x,const node &y){
		return x.l<y.l || (x.l==y.l && x.r>y.r);
	}
} a[maxn];
int n,ans;
int main(){
	int i,j,k;
	scanf("%d",&n);
	for (i=0;i<n;i++) scanf("%d %d",&a[i].l,&a[i].r);
	sort(a,a+n);
	k=a[0].r;
	for (i=1;i<n;i++)
		if (a[i].r<=k) ans++;else k=a[i].r;
	printf("%d\n",ans);
	return 0;
}
