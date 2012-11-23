#include <stdio.h>
long long t[14];
long long q,ans;
long long f(long long x){
	long long res=0;
	for (int i=1;i<14;i++) res+=x/t[i];
	return res;
}
int main(){
	int i,j,k;
	scanf("%d",&q);
	if (q==0){
		printf("1\n");
		return 0;
	}
	for (t[0]=1,i=1;i<14;i++) t[i]=t[i-1]*5;
	long long l,r,mid;
	l=1;r=t[12];
	while (l<=r){
		mid=(l+r)>>1;
		if (f(mid*5)>=q){
			ans=mid;
			r=mid-1;
		}else l=mid+1;
	}
	if (f(ans*5)==q) printf("%d\n",ans*5);else printf("No solution\n");
	return 0;
}
