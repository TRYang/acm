#include <stdio.h>
long long l,r;
int k;
int calc(int x){
	int ret=0;
	while (x) ret+=x%10,x/=10;
	return ret;
}
int main(){
	scanf("%lld%lld%d",&l,&r,&k);
	int ans=0;
	for (int i=l,j;i<=r;i=j){
		int tot=0;
		for (j=i;tot<k && j<=r;tot+=calc(j++));
		if (tot>=k)
		++ans;
	}
	printf("%d\n",ans);
	return 0;
}
