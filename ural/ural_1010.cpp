#include <stdio.h>
#define maxn 100010
long long y[maxn];
int p,n;

long long abs(long long x){return x>0 ? x : -x;}
int main(){
	int i,j,k;
	scanf("%d",&n);
	for (i=0;i<n;i++) scanf("%I64d",y+i);
	p=1;
	for (i=1;i<n-1;i++)
		if (abs(y[i+1]-y[i])>abs(y[p-1]-y[p])) p=i+1;
	printf("%d %d\n",p,p+1);
	return 0;
}
