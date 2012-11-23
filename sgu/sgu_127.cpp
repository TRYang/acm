#include <stdio.h>
#include <algorithm>
#define maxn 8010

using namespace std;

int a[maxn];
int n,m;
int ans;
int main(){
	int i,j,k;
	scanf("%d %d",&m,&n);
	for (i=0;i<n;i++) scanf("%d",a+i);
	sort(a,a+n);
	ans=2;
	for (i=0;i<n;i=j+1){
		for (j=i;j<n-1 && a[j+1]/1000 == a[j]/1000;j++);
		k=j-i+1;
		ans+=(k-1)/m+1;
	}
	printf("%d\n",ans);
	return 0;
}
