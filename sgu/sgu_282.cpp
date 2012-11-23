#include <stdio.h>
#include <string.h>
#define maxn 55
typedef long long LL;
LL fac[maxn*maxn],dfac[maxn*maxn];
LL tot[maxn*maxn];
int g[maxn][maxn];
int a[maxn];
int n,m,q;
int gcd(int x,int y){return y==0?x:gcd(y,x%y);}
LL POW(LL x,LL y){
	if (y==0) return 1;
	if (y==1) return x%q;
	if (y%2==0){
		LL tmp=POW(x,y>>1);
		return (tmp*tmp)%q;
	}else return (POW(x,y-1)*x)%q;
}
void dfs(int N,int dm,int ln){
	if (N==0){
		int i,j,k,sum=0;
		for (i=0;i<ln;i++) sum+=a[i]>>1;
		for (i=0;i<ln;i++)
			for (j=i+1;j<ln;j++) sum+=g[a[i]][a[j]];
		LL v=fac[n];
		for (i=0;i<ln;i++) v=(v*dfac[a[i]])%q;
		for (i=0;i<ln;i++) v=(v*fac[a[i]-1])%q;
		for (i=0;i<ln;i=j+1){
			for (j=i;j<ln-1 && a[j+1]==a[j];j++);
			v=(v*dfac[j-i+1])%q;
		}
		tot[sum]=(tot[sum]+v)%q;
		return;
	}
	if (dm==0) return;
	if (N>=dm){
		a[ln]=dm;
		dfs(N-dm,dm,ln+1);
	}
	dfs(N,dm-1,ln);
}
int main(){
	int i,j,k;
	scanf("%d %d %d",&n,&m,&q);
	if (n==1){
		printf("1\n");
		return 0;
	}
	for (i=0;i<=n;i++)
		for (j=0;j<=n;j++) g[i][j]=gcd(i,j);
	fac[0]=1;
	for (i=1;i<=n*(n-1)>>1;i++) fac[i]=(fac[i-1]*i)%q;
	for (i=0;i<=n;i++) dfac[i]=POW(fac[i],q-2);
	dfac[n*(n-1)>>1]=POW(fac[n*(n-1)>>1],q-2);
	memset(tot,0,sizeof(tot));
	dfs(n,n,0);
	LL ans=0;
	for (i=1;i<=n*(n-1)>>1;i++) ans=(ans+tot[i]*POW(m,i))%q;
	ans=(ans*dfac[n])%q;
	printf("%lld\n",ans);
	return 0;
}
