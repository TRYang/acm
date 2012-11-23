#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 110

using namespace std;

typedef long long LL;

int a[maxn];
int b[maxn];
int n,c,pt,t;
int check(LL limit){
	LL tot=0;
	int p=0;
	while (tot<limit && p<n){
		p++;
		b[p]=min((LL)a[p],limit-tot);
		tot+=b[p];
	}
	LL Time=0;
	while (p){
		Time+=(LL)(b[p]/c)*pt*p*2;
		int r=b[p]%c;
		if (r){
			b[p-1]+=r;
			Time+=2*pt;
		}
		--p;
	}
	return Time<=t;
}
int main(){
	scanf("%d%d%d%d",&n,&c,&pt,&t);
	for (int i=1;i<=n;i++) scanf("%d",a+i);
	LL L=0,R=0,mid;
	for (int i=1;i<=n;i++) R+=a[i];
	LL ans=0;
	while (L<=R){
		mid=(L+R)>>1;
		if (check(mid)){
			L=mid+1;
			ans=mid;
		}else R=mid-1;
	}
	printf("%I64d\n",ans);
	return 0;
}