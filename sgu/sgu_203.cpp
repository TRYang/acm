#include <stdio.h>
#include <algorithm>
#define maxn 500010

using namespace std;

long long a[maxn];
int n;
long long ans;

bool cmp(long long x,long long y){
	return x>y;
}

int main(){
	int i,j,k;
	scanf("%d",&n);
	for (i=0;i<n;i++) scanf("%d",a+i);
	make_heap(a,a+n,cmp);
	ans=0;
	long long t1,t2;
	for (i=0;i<n-1;i++){
		t1=a[0];
		pop_heap(a,a+n-i,cmp);
		t2=a[0];
		pop_heap(a,a+n-i-1,cmp);
		ans+=t1+t2;
		a[n-2-i]=t1+t2;
		push_heap(a,a+n-i-1,cmp);
	}
	printf("%I64d\n",ans);
	return 0;
}
