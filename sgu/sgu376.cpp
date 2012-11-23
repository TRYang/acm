#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 1010
#define extra 20000000

using namespace std;

struct node{
	int w,r,p;
	int id;
	long long t;
	void read(){
		scanf("%d%d%d",&w,&r,&p);
		t=0;
	}
	friend bool operator < (const node &x,const node &y){
		return x.t<y.t || (x.t==y.t && x.p>y.p);
	}
} a[maxn];
int A[maxn],B[maxn];
int h[maxn];
int n,m;
bool cmp(int x,int y){
	return x>y;
}
int main(){
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;i++) a[i].read();
	for (int i=0;i<n;i++) a[i].id=i+1;
	for (int i=0;i<m;i++) scanf("%d",A+i);
	for (int i=0;i<n;i++) scanf("%d",B+i);
	for (int i=0;i<n;i++) a[i].t=extra-a[i].w;
	sort(a,a+n);
	for (int k=0;k<m;k++){
		for (int i=0;i<n;i++) h[i]=(3*A[k]+2*B[i])*(A[k]+B[i]);
		sort(h,h+n,cmp);
		for (int i=0;i<n;i++){
			a[i].t+=extra-a[i].r-h[i];
		}
		sort(a,a+n);
	}
	for (int i=0;i<n-1;i++) printf("%d ",a[i].id);
	printf("%d\n",a[n-1].id);
	return 0;
}
