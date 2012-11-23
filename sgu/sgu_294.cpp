#include <stdio.h>
#include <string.h>
#define maxn 200010
typedef long long LL;
const LL kk= (LL)100000000;
LL a[30000],ans[30000];
int an,ln;
int tot[maxn];
int n,m;
int gcd(int a,int b){return b==0 ? a : gcd(b,a%b);}
void Mul(LL p){
	int i;
	for (i=0;i<an;i++) a[i]<<=p;
	for (i=0;i<an;i++)
		if (a[i]>=kk){
			a[i+1]+=a[i]/kk;
			a[i]%=kk;
		}
	while (a[an]>0){
		a[an+1]+=a[an]/kk;
		a[an]%=kk;
		an++;
	}
}
void add_ans(){
	int i;
	if (an>ln) ln=an;
	for (i=0;i<an;i++) ans[i]+=a[i];
	for (i=0;i<ln;i++)
		if (ans[i]>=kk){
			ans[i+1]++;
			ans[i]-=kk;
		}
	if (ans[ln]>0) ln++;
}
int main(){
	int i,j,k;
	scanf("%d",&n);
	memset(tot,0,sizeof(tot));
	for (i=0;i<n;i++) tot[gcd(n,i)]++;
	m=n;
	for (i=0;i<=m;i++)
		if (tot[i]>1){
			tot[i+1]+=tot[i]>>1;
			tot[i]&=1;
			if (i==m) m++;
		}
	memset(a,0,sizeof(a));
	memset(ans,0,sizeof(ans));
	ln=0;
	an=1;
	a[0]=1;
	k=0;
	for (i=1;i<=m;i++)
		if (tot[i]>0){
			while (i-k>25){
				Mul(25);
				k+=25;
			}
			if (i>k) Mul(i-k);
			k=i;
			add_ans();
		}
	LL c=0;
	for (i=ln-1;i>=0;i--){
		ans[i]+=c*kk;
		c=ans[i]%n;
		ans[i]/=n;
	}
	while (ln>1 && ans[ln-1]==0) ln--;
	printf("%lld",ans[ln-1]);
	for (i=ln-2;i>=0;i--){
		if (ans[i]<10000000) printf("0");
		if (ans[i]<1000000) printf("0");
		if (ans[i]<100000) printf("0");
		if (ans[i]<10000) printf("0");
		if (ans[i]<1000) printf("0");
		if (ans[i]<100) printf("0");
		if (ans[i]<10) printf("0");
		printf("%lld",ans[i]);
	}
	printf("\n");
	return 0;
}
