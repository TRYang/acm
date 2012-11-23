#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 55
#define kk 10000

using namespace std;

struct bignum{
	int l,v[100];
	friend bignum operator + (const bignum &x,const bignum &y){
		bignum res;
		res.l=max(x.l,y.l);
		memset(res.v,0,sizeof(res.v));
		int i;
		for (i=0;i<res.l;i++) res.v[i]=x.v[i]+y.v[i];
		for (i=0;i<res.l;i++)
			if (res.v[i]>=kk) res.v[i+1]++,res.v[i]-=kk;
		if (res.v[res.l]>0) res.l++;
		return res;
	}
	friend bignum operator * (const bignum &x,const bignum &y){
		bignum res;
		res.l=x.l+y.l;
		memset(res.v,0,sizeof(res.v));
		int i,j,k;
		for (i=0;i<x.l;i++){
			k=0;
			for (j=0;j<y.l;j++){
				res.v[i+j]+=k+x.v[i]*y.v[j];
				k=res.v[i+j]/kk;
				res.v[i+j]%=kk;
			}
			if (k>0) res.v[i+y.l]+=k;
		}
		while (res.l>1 && res.v[res.l-1]==0) res.l--;
		return res;
	}
	void pr(){
		printf("%d",v[l-1]);
		for (int i=l-2;i>=0;i--){
			if (v[i]<1000) printf("0");
			if (v[i]<100) printf("0");
			if (v[i]<10) printf("0");
			printf("%d",v[i]);
		}
		printf("\n");
	}
} f[maxn][maxn<<1],G[2][maxn<<1];

int a[maxn],an;
int n,m;

bool cmp(int x,int y){
	return x>y;
}

bignum ch(int x){
	bignum res;
	res.l=1;
	memset(res.v,0,sizeof(res.v));
	res.v[0]=x;
	return res;
}

void work(int x){
	int i,j,k;
	an=0;
	for (i=0;i<n;i++)
		if (i%2==x) a[an++]=i+1;
	for (i=1;i<n;i++)
		if ((i+n-1)%2==x) a[an++]=n-i;
	sort(a,a+an,cmp);
	a[an]=0;
	for (i=1;i<=m;i++) f[an][i]=ch(0);
	f[an][0]=ch(1);
	for (i=an-1;i>=0;i--)
		for (j=0;j<=m && j<=a[i];j++){
			f[i][j]=f[i+1][j];
			if (j>0) f[i][j]=f[i][j]+(ch(a[i]-j+1)*f[i+1][j-1]);
		}
	for (i=0;i<=m;i++) G[x][i]=f[0][i];
}

int main(){
	int i,j,k;
	scanf("%d %d",&n,&m);
	if (m>2*n-2 && n>1) printf("0\n");else{
		work(0);
		work(1);
		bignum ans=ch(0);
		for (i=0;i<=m;i++) ans=ans+(G[0][i]*G[1][m-i]);
		ans.pr();
	}
	return 0;
}
