#include <stdio.h>
#include <string.h>
#include <algorithm>
#define P 100000000
using namespace std;
int a[1000],an;
int b[1000],bn;
int n,m;
int main(){
	scanf("%d%d",&n,&m);
	an=1;
	a[0]=1;
	for (int i=1;i<=n;i++){
		for (int j=0;j<an;j++) a[j]<<=1;
		for (int j=0;j<an;j++)
			if (a[j]>=P){
				a[j+1]+=a[j]/P;
				a[j]%=P;
			}
		if (a[an]>0) ++an;
	}
	bn=1;
	b[0]=1;
	for (int i=1;i<=m;i++){
		for (int j=0;j<bn;j++) b[j]<<=1;
		for (int j=0;j<bn;j++)
			if (b[j]>=P){
				b[j+1]+=b[j]/P;
				b[j]%=P;
			}
		if (b[bn]>0) ++bn;
	}
	for (int i=0;i<max(an,bn);i++) a[i]+=b[i];
	an=max(an,bn);
	for (int i=0;i<an;i++)
		if (a[i]>=P){
			a[i+1]+=a[i]/P;
			a[i]%=P;
		}
	if (a[an]) ++an;
	int k=2;
	for (int i=0;i<an;i++)
		if (a[i]>=k){
			a[i]-=k;
			break;
		}else{
			a[i+1]--;
			a[i]+=P;
			a[i]-=k;
			k=1;
		}
	printf("%d",a[an-1]);
	for (int i=an-2;i>=0;i--) printf("%08d",a[i]);
	puts("");
	return 0;
}