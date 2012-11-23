#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 10010

using namespace std;

struct node{
	int v,p;
	friend bool operator < (const node &x,const node &y){
		return x.v<y.v || (x.v==y.v && x.p<y.p);
	}
} a[maxn];
int h[maxn],s[maxn];
int n,A0,B0,m;
int ans;
int gcd(int x,int y){
	return y==0 ? x : gcd(y,x%y);
}
int main(){
	int i,j,k;
	scanf("%d %d %d",&n,&A0,&B0);
	m=gcd(n,gcd(A0,B0));
	n/=m;
	A0/=m;
	B0/=m;
	memset(h,0,sizeof(h));
	for (i=0;i<n;i++){
		a[i].p=i;
		a[i].v=(i*A0)%n;
		h[a[i].v]++;
	}
	sort(a,a+n);
	memset(s,-1,sizeof(s));
	for (ans=i=0;i<n;i++){
		k=(i*B0)%n;
		ans+=h[k];
		if (i==0 || a[i].v!=a[i-1].v) s[a[i].v]=i;
	}
	printf("%d\n",ans);
	for (i=0;i<n;i++){
		k=(i*B0)%n;
		if (s[k]>-1)
			for (j=s[k];j<n && a[j].v==k;j++) printf("%d %d\n",i*m,a[j].p*m);
	}
	return 0;
}
