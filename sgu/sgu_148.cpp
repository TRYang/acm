#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 15010

using namespace std;

int W[maxn],L[maxn],P[maxn];//data
int s[maxn];//sum of W
int x[maxn],xn;//coor
int t[maxn];//tree array
int n;
int ans,ansp;

void ins(int p,int v){
	for (;p<=xn;p+=(p&(p^(p-1)))) t[p]+=v;
}

int ask(int p){
	int res=0;
	for (;p>0;p-=(p&(p^(p-1)))) res+=t[p];
	return res;
}

int main(){
	int i,j,k;
	scanf("%d",&n);
	for (i=1;i<=n;i++) scanf("%d %d %d",W+i,L+i,P+i);
	for (s[0]=0,i=1;i<=n;i++) s[i]=s[i-1]+W[i];
	for (i=1;i<=n;i++) x[i-1]=s[i]-L[i];
	sort(x,x+n);
	xn=unique(x,x+n)-x;
	ans=1000000000;
	memset(t,0,sizeof(t));
	for (k=n;k>0;k--){
		ins(upper_bound(x,x+xn,s[k]-L[k])-x,P[k]);
		j=ask(upper_bound(x,x+xn,s[k-1])-x);
		if (j<ans){
			ans=j;
			ansp=k;
		}
	}
	for (i=ansp;i<=n;i++)
		if (s[i]-s[ansp-1]<=L[i]) printf("%d\n",i);
	return 0;
}
