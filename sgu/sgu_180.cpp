#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 65638

using namespace std;

int a[maxn];
int t[maxn];
int n;
int x[maxn],xn;
long long ans;
int ask(int p){
	int res=0;
	for (;p>0;p-=(p&(p^(p-1)))) res+=t[p];
	return res;
}
void ins(int p){
	for (;p<=xn;p+=(p&(p^(p-1)))) t[p]++;
}
int main(){
	int i,j,k;
	scanf("%d",&n);
	for (i=0;i<n;i++){
		scanf("%d",a+i);
		x[i]=a[i];
	}
	sort(x,x+n);
	xn=unique(x,x+n)-x;
	memset(t,0,sizeof(t));
	for (i=n-1;i>=0;i--){
		a[i]=upper_bound(x,x+xn,a[i])-x;
		ans+=ask(a[i]-1);
		ins(a[i]);
	}
	printf("%I64d\n",ans);
	return 0;
}
