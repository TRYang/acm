#include <stdio.h>
#include <algorithm>
#define maxn 15010

using namespace std;

struct node{
	int x,p;
	friend bool operator < (const node &x,const node &y){
		return x.x<y.x;
	}
} a[maxn];
int sum;
int n;
int main(){
	int i,j,k;
	scanf("%d",&n);
	for (i=sum=0;i<n;i++){
		scanf("%d %d",&a[i].x,&a[i].p);
		sum+=a[i].p;
	}
	sort(a,a+n);
	for (i=k=0;k<(sum+1)>>1;i++) k+=a[i].p;
	printf("%d.00000\n",a[i-1].x);
	return 0;
}
