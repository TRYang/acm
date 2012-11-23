#include <stdio.h>
#include <algorithm>
#include <string.h>
#define maxn 1010
#define kk 100000000

using namespace std;

struct bignum{
	int l,v[100];
	friend bignum operator + (const bignum &x,const bignum &y){
		bignum res;
		int i;
		res.l=max(x.l,y.l);
		memset(res.v,0,sizeof(res.v));
		for (i=0;i<res.l;i++) res.v[i]=x.v[i]+y.v[i];
		for (i=0;i<res.l;i++)
			if (res.v[i]>=kk) res.v[i+1]++,res.v[i]-=kk;
		if (res.v[res.l]>0) res.l++;
		return res;
	}
	friend bool operator < (const bignum &x,const bignum &y){
		if (x.l!=y.l) return x.l<y.l;
		for (int i=x.l-1;i>=0;i--){
			if (x.v[i]<y.v[i]) return 1;
			if (x.v[i]>y.v[i]) return 0;
		}
		return 0;
	}
	void pr(){
		printf("%d",v[l-1]);
		for (int i=l-2;i>=0;i--){
			if (v[i]<10000000) printf("0");
			if (v[i]<1000000) printf("0");
			if (v[i]<100000) printf("0");
			if (v[i]<10000) printf("0");
			if (v[i]<1000) printf("0");
			if (v[i]<100) printf("0");
			if (v[i]<10) printf("0");
			printf("%d",v[i]);
		}
		//printf("\n");
	}
} a[maxn];
int n;
char s[800];
int main(){
	int i,j,k;
	scanf("%d",&n);
	for (i=0;i<n;i++){
		scanf("%s",s);
		memset(a[i].v,0,sizeof(a[i].v));
		a[i].l=(strlen(s)-1)/8+1;
		k=a[i].l-1;
		int L=strlen(s);
		for (j=0;j<L;j++){
			if (j>0 && (L-j)%8==0) k--;
			a[i].v[k]=a[i].v[k]*10+(s[j]-'0');
		}
	}
	sort(a,a+n);
	k=0;
	for (i=0;i<n-2;i++)
		if (a[i+2]<(a[i]+a[i+1])){
			k=1;
			a[i].pr();
			printf(" ");
			a[i+1].pr();
			printf(" ");
			a[i+2].pr();
			printf("\n");
			break;
		}
	if (!k) printf("0 0 0\n");
	return 0;
}
