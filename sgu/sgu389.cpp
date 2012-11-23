#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 100010
#define mod 1000000007
#define CHECKER

using namespace std;

long long fac[maxn],dfac[maxn];
char s[3][maxn];
int n;
long long POW(long long x,int y){
	long long ret=1;
	while (y){
		if (y&1) ret=(ret*x)%mod;
		x=(x*x)%mod;
		y>>=1;
	}
	return ret;
}
long long C(int n,int m){
	return ((fac[n]*dfac[n-m])%mod*dfac[m])%mod;
}
int main(){
	fac[0]=1;
	for (int i=1;i<maxn;i++) fac[i]=(fac[i-1]*i)%mod;
	for (int i=0;i<maxn;i++) dfac[i]=POW(fac[i],mod-2);
	for (int i=0;i<3;i++) scanf("%s",s[i]);
	n=strlen(s[0]);
	long long ans=0;
#ifndef CHECKER
	for (int mask=0;mask<(1<<n);mask++){
		int t1=0,t2=0,t3=0;
		for (int i=0;i<n;i++)
			if ((mask&(1<<i))>0){
				if (s[0][i]=='0') ++t1;
				if (s[1][i]=='0') ++t2;
				if (s[2][i]=='0') ++t3;
			}else{
				if (s[0][i]=='1') ++t1;
				if (s[1][i]=='1') ++t2;
				if (s[2][i]=='1') ++t3;
			}
		if (t1==t2 && t2==t3) ++ans;
	}
	printf("%d\n",ans);
#endif
	int tot=0;
	int t[3];
	memset(t,0,sizeof(t));
	for (int i=0;i<n;i++){
		if (s[0][i]==s[1][i] && s[0][i]==s[2][i]) ++tot;else
		if ((s[0][i]=='1' && s[1][i]=='0' && s[2][i]=='0') ||
			(s[0][i]=='0' && s[1][i]=='1' && s[2][i]=='1')){
			t[0]++;
		}
		if ((s[0][i]=='0' && s[1][i]=='1' && s[2][i]=='0') ||
			(s[0][i]=='1' && s[1][i]=='0' && s[2][i]=='1')){
			t[1]++;
		}
		if ((s[0][i]=='0' && s[1][i]=='0' && s[2][i]=='1') ||
			(s[0][i]=='1' && s[1][i]=='1' && s[2][i]=='0')){
			t[2]++;
		}
	}
//	for (int i=0;i<3;i++) printf("%d\n",t[i]);
	ans=0;
	int m=min(t[0],min(t[1],t[2]));
	for (int i=0;i<=m;i++){
		if ((t[0]-i)%2==1 || (t[1]-i)%2==1 || (t[2]-i)%2==1) continue;
		long long tmp=(C(t[0],(t[0]-i)>>1)*C(t[1],(t[1]-i)>>1))%mod*C(t[2],(t[2]-i)>>1)%mod;
		if (i>0) tmp=(tmp<<1)%mod;
		ans+=tmp;
		ans%=mod;
	}
	ans*=POW(2,tot);
	ans%=mod;
	printf("%d\n",ans);
	return 0;
}
