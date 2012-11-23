#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

int pr[2000],pn;
int n,m;
int check(int x){
	for (int i=2;i*i<=x;i++)
		if (x%i==0) return 0;
	return 1;
}
long long work(){
	n--,m--;
	long long ret=(long long)n*m;
	for (int i=2;i<=n;i++){
		int tag=1,tot=0;
		int x=i;
		for (int j=0;j<pn && pr[j]*pr[j]<=x;j++)
			if (x%pr[j]==0){
				++tot;
				x/=pr[j];
				if (x%pr[j]==0){
					tag=0;
					break;
				}
			}
		if (tag){
			if (x>1) ++tot;
			long long c=n/i,d=m/i;
			if (tot%2==1) ret-=c*d;else ret+=c*d;
		}
	}
	return ret;
}
int main(){
	pn=0;
	for (int i=2;i<=1000;i++)
		if (check(i)) pr[pn++]=i;
	scanf("%d%d",&n,&m);
	if (n>m) swap(n,m);
	if (m==1) puts("0");else
	if (n==1) puts("1");else{
		printf("%lld\n",work()+2);
	}
	return 0;
}
