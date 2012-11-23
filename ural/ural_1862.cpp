#include <stdio.h>
#include <string.h>
#define mod 1000000007
typedef long long LL;
LL l;
LL POW(LL x,LL y){
	LL ret=1;
	while (y){
		if ((y&1)>0) ret=(ret*x)%mod;
		x=(x*x)%mod;
		y>>=1;
	}
	return ret;
}
LL mod_mul(LL x,LL y,LL n){
	if (x==0) return 0;
	return (((x&1)*y)%n+(mod_mul(x>>1,y,n)<<1)%n)%n;
}
int main(){
	scanf("%lld",&l);
	LL ans=(POW(2,2*l)+POW(2,l))%mod;
	ans=mod_mul(ans,l-1,mod);
	ans-=POW(2,2*l)-POW(2,l+1);
	ans-=POW(2,2*l)-POW(2,l+1);
	ans%=mod;
	ans+=mod;
	ans%=mod;
	printf("%lld\n",ans);
	return 0;
}