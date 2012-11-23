#include <stdio.h>
#include <string.h>
#define maxn 100010
int a[maxn];
int n,m;
long long ans,tmp;
int main(){
	int i,j,k;
	memset(a,0,sizeof(a));
	scanf("%d %d",&n,&m);
	for (i=0;i<m;i++){
		scanf("%d %d",&j,&k);
		a[j]++;
		a[k]++;
	}
	ans=0;
	for (i=1;i<=n;i++){
		tmp=a[i];
		ans+=tmp*tmp;
	}
	printf("%I64d\n",ans);
	return 0;
}
