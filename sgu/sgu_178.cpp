#include <stdio.h>
long long n,tot;
int ans;
int check(long long k){
	tot=k;
	long long d=k+1;
	for (int i=0;i<k+1;i++){
		tot+=d;
		if (tot>=n) return 1;
		if (i<k) d<<=1;	
	}
	return 0;
}
int main(){
	int i;
	scanf("%I64d",&n);
	if (n==1) ans=0;else
	for (ans=1;!check(ans);ans++);
	printf("%d\n",ans);
	return 0;
}
